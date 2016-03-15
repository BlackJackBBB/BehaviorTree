#include <pch.h>
#include <ai/behavior_tree/nodes/decorator_nodes/repeater_node.h>


using namespace ai::behavior_tree;


RepeaterNode::RepeaterNode(bool isFinite, size_t nRepetitions) : 
	_isFinite(isFinite), 
	_nRepetitions(nRepetitions),
	_repetitionNo(0) {}


RepeaterNode::~RepeaterNode() {}


void RepeaterNode::onInitialization() {
	
	DecoratorNode::onInitialization();

	_repetitionNo = 0;
}


void RepeaterNode::observerCallback() {

	if (!_isFinite || (++_repetitionNo < _nRepetitions)) 
		DecoratorNode::onInitialization();
	else 
		this->terminateNode(this->_childNode->getStatus());
}