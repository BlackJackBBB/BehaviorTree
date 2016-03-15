#include <pch.h>
#include <ai/behavior_tree/node.h>


using namespace ai::behavior_tree;


Node::Node() : 
	_behaviorTree(nullptr),
	_status(Status::INVALID) {}


Node::~Node() {}


Node& Node::process() {

	if (_status == Status::INVALID)
		this->onInitialization();

	this->onRunning();

	return *this;
}



Node::Status Node::getStatus() const {
	
	return _status;
}


Node& Node::setStatus(Status status) {

	_status = status;

	return *this;
}


void Node::terminateNode(Node::Status resultStatus) {
	
	for (auto& child : this->getChildNodes())
		child->detachObserver(*this);

	this->setStatus(resultStatus);
	this->notifyObservers();
}