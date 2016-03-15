#include <pch.h>
#include <ai/behavior_tree/nodes/composite_nodes/selector_node.h>
#include <ai/behavior_tree/behavior_tree.h>


using namespace ai::behavior_tree;


SelectorNode::SelectorNode() : _processingChildNode(this->_childNodes.end()) {}


SelectorNode::~SelectorNode() {}


void SelectorNode::onInitialization() {

	if (this->_childNodes.size() > 0)
		_processingChildNode = this->_childNodes.begin();

	CompositeNode::onInitialization();

	(*_processingChildNode)->attachObserver(*this);
	this->_behaviorTree->enqueueNode(**_processingChildNode);
}


void SelectorNode::observerCallback() {
	
	auto& currentChild = **_processingChildNode;
	
	if (currentChild.getStatus() == Status::SUCCESS) 
		this->terminateNode(Status::SUCCESS);
	else if (++_processingChildNode == this->_childNodes.end()) 
		this->terminateNode(Status::FAILURE);
	else {
		(*_processingChildNode)->attachObserver(*this);
		this->_behaviorTree->enqueueNode(**_processingChildNode);
	}
}

