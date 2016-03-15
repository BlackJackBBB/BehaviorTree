#include <pch.h>
#include <ai/behavior_tree/nodes/decorator_nodes/until_fail_node.h>


using namespace ai::behavior_tree;


UntilFailNode::UntilFailNode() {}


UntilFailNode::~UntilFailNode() {}


void UntilFailNode::observerCallback() {

	if (this->_childNode->getStatus() == Status::FAILURE) 
		this->terminateNode(Status::SUCCESS);
	else 
		this->onInitialization();
}

