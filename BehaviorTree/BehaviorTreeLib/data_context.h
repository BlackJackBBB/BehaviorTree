#pragma once
#include <type_traits>
#include <typeindex>
#include <memory>
#include <unordered_map>


class DataContext {
public:

	class ExpiredVariableException : public std::runtime_error {
	public:

		explicit ExpiredVariableException(const std::string& _Message) : runtime_error(_Message) {}


		explicit ExpiredVariableException(const char* _Message) : runtime_error(_Message) {}

	};


	class InvalidTemplateTypeException : public std::runtime_error {
	public:

		explicit InvalidTemplateTypeException(const std::string& _Message) : runtime_error(_Message) {}


		explicit InvalidTemplateTypeException(const char* _Message) : runtime_error(_Message) {}

	};


	DataContext();


	~DataContext();


	// Checks if variable with given name and type exists in context.
	bool containsVariable(const std::string& varName, const std::type_info& varType);


	// Checks if variable with given name.
	bool containsVariable(const std::string& varName);


	// Crates variable of type T from given name and constructor arguments and adds it to context.
	// Created variable is managed by context.
	// Returns flase if variable with same name exists in context, otherwise retruns true.
	template<typename T, typename... TArgs>
	bool createVariable(const std::string& varName, TArgs&&... ctorArgs) {

		static_assert(!std::is_pointer<T>::value, "Template typename T can not be pointer type");
		static_assert(!std::is_reference<T>::value, "Template typename T can not be reference type");
		static_assert(std::is_constructible<T, TArgs...>::value, "Template typename T can not be constructed from given arguments");
		
		if (this->containsVariable(varName)) 
			return false;
		
		_managedVariables.emplace(varName, std::make_pair(std::shared_ptr<void>(new T(std::forward<TArgs>(ctorArgs)...)), std::type_index(typeid(T))));
		
		return true;
	}


	// Creates variable of type T from given name and object, and adds it to context.
	// Created variable is unmanaged by context (managed outsife of context).
	// Returns flase if variable with same name exists in context, otherwise retruns true.
	template<typename T>
	bool addVariable(const std::string& varName, std::shared_ptr<T>& object) {

		static_assert(!std::is_rvalue_reference<decltype(object)>::value, "Given object can not be rvalue reference");

		if (this->containsVariable(varName))
			return false;

		_unmanagedVariables.emplace(varName, std::make_pair(std::forward<std::shared_ptr<T>&>(object), std::type_index(typeid(T))));

		return true;
	}


	// Find and get reference on variable of type T from context.
	// std::out_of_range exception is thrown if variable with given name is not found in context.
	// InvalidTemplateTypeException exception is thrown if template typename does not match finded variable type.
	// ExpiredVariableException exception is thrown if variable has expired (deleted by its owner).
	template<typename T>
	T& findVariable(const std::string& varName) {

		auto it1 = _managedVariables.find(varName);
		if (it1 != _managedVariables.end()) {

			if (std::get<static_cast<UnderlyingVariableInfoType>(VariableInfo::TYPE)>(it1->second) != typeid(T))
				throw std::runtime_error("Template typename does not match finded variable type");
			
			return *static_cast<T*>(std::get<static_cast<UnderlyingVariableInfoType>(VariableInfo::OBJECT)>(it1->second).get());
		}
		
		auto it2 = _unmanagedVariables.find(varName);
		if (it2 != _unmanagedVariables.end()) {
			
			if (std::get<static_cast<UnderlyingVariableInfoType>(VariableInfo::TYPE)>(it2->second) != typeid(T))
				throw InvalidTemplateTypeException("Template typename does not match finded variable type");

			if (std::get<static_cast<UnderlyingVariableInfoType>(VariableInfo::OBJECT)>(it2->second).expired()) {
				_unmanagedVariables.erase(it2);
				throw ExpiredVariableException("Unmanaged variable has expired because it is deleted by its owner");
			}

			return *static_cast<T*>(std::get<static_cast<UnderlyingVariableInfoType>(VariableInfo::OBJECT)>(it2->second).lock().get());
		}
		
		throw std::out_of_range("Variable with given name could not be finded");
		
	}


	// Find and remove variable with given name if it exists.
	// Returns true if variable exists, otherwise returns false.
	bool removeVariable(const std::string& varName);

private:

	enum class VariableInfo {
		OBJECT = 0,
		TYPE = 1
	};

	using UnderlyingVariableInfoType = std::underlying_type<VariableInfo>::type;

	std::unordered_map<std::string, std::pair<std::weak_ptr<void>, std::type_index>> _unmanagedVariables;
	std::unordered_map<std::string, std::pair<std::shared_ptr<void>, std::type_index>> _managedVariables;
	
};
