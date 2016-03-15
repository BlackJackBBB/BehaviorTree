#include <pch.h>
#include <data_context.h>


DataContext::DataContext() {}


DataContext::~DataContext() {}


bool DataContext::containsVariable(const std::string& varName, const std::type_info& varType) {
	
	auto it1 = _managedVariables.find(varName);
	if (it1 != _managedVariables.end() && std::get<static_cast<UnderlyingVariableInfoType>(VariableInfo::TYPE)>(it1->second) == varType)
		return true;

	auto it2 = _unmanagedVariables.find(varName);
	if (it2 != _unmanagedVariables.end() && std::get<static_cast<UnderlyingVariableInfoType>(VariableInfo::TYPE)>(it2->second) == varType)
		return true;

	return false;
}


bool DataContext::containsVariable(const std::string& varName) {
	
	return _managedVariables.find(varName) != _managedVariables.end() || _unmanagedVariables.find(varName) != _unmanagedVariables.end();
}


bool DataContext::removeVariable(const std::string& varName) {
	
	if (_managedVariables.erase(varName) == 1)
		return true;

	if (_unmanagedVariables.erase(varName) == 1)
		return true;

	return false;
}
