#include <pch.h>
#include <ai/behavior_tree/nodes/decorator_nodes/succeeder_node.h>


using namespace ai::behavior_tree;


SucceederNode::SucceederNode() {}


SucceederNode::~SucceederNode() {}


void SucceederNode::observerCallback() {

	this->terminateNode(Status::SUCCESS);
}