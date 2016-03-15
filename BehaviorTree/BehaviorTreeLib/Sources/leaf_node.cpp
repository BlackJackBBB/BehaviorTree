#include <pch.h>
#include <ai/behavior_tree/nodes/leaf_node.h>


using namespace ai::behavior_tree;


LeafNode::~LeafNode() {}


std::vector<Node*> LeafNode::getChildNodes() {
	
	return std::vector<Node*> {};
} 


void LeafNode::onRunning() {

	this->operation();

	if (succeedCondition() == true)
		this->setStatus(Status::SUCCESS);
	else if (failCondition() == true)
		this->setStatus(Status::FAILURE);
	else if (runCondition() == true)
		this->setStatus(Status::RUNNING);
}


void LeafNode::onInitialization() {}


void LeafNode::observerCallback() {}