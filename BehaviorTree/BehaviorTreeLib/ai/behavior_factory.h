#pragma once
#include <unordered_map>
#include <data_context.h>
#include <functional>


namespace ai {

	class IBehavior;

	
	class BehaviorFactory {
	public:

		using Creator = std::function<IBehavior*(DataContext&)>;

		static BehaviorFactory& instance();

		~BehaviorFactory();

		IBehavior* create(const std::string& id, DataContext& context);

		int registerCreator(const std::string& id, Creator& creator);

	private:

		std::unordered_map<std::string, Creator> _creators;

		BehaviorFactory();

	};

}



