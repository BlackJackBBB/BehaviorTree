#include <pch.h>
#include <ai/behavior_factory.h>


using namespace ai;


BehaviorFactory& BehaviorFactory::instance() {
	
	static BehaviorFactory factory;

	return factory;
}


IBehavior* BehaviorFactory::create(const std::string& id, DataContext& context) {
	
	auto it = _creators.find(id);

	if (it == _creators.end())
		return nullptr;

	return it->second(context);
}


int BehaviorFactory::registerCreator(const std::string& id, Creator& creator) {
	
	_creators.emplace(id, creator);
	
	return 1;
}


BehaviorFactory::BehaviorFactory() {}


BehaviorFactory::~BehaviorFactory() {}
