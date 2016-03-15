#include <pch.h>
#include <ai/behavior_tree/nodes/composite_nodes/sequence_node.h>
#include <ai/behavior_tree/behavior_tree.h>


using namespace ai::behavior_tree;


SequenceNode::SequenceNode() : _processingChildNode(this->_childNodes.end()) {}


SequenceNode::~SequenceNode() {}


void SequenceNode::onInitialization() {

	if (this->_childNodes.size() > 0)
		_processingChildNode = this->_childNodes.begin();

	CompositeNode::onInitialization();

	(*_processingChildNode)->attachObserver(*this);
	this->_behaviorTree->enqueueNode(**_processingChildNode);
}


void SequenceNode::observerCallback() {

	auto& currentChild = **_processingChildNode;

	if (currentChild.getStatus() == Status::FAILURE) 
		this->terminateNode(Status::FAILURE);
	else if (++_processingChildNode == this->_childNodes.end()) 
		this->terminateNode(Status::SUCCESS);
	else {
		(*_processingChildNode)->attachObserver(*this);
		this->_behaviorTree->enqueueNode(**_processingChildNode);
	}
		
}