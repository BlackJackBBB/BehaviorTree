#include <pch.h>
#include <ai/behavior_tree/nodes/decorator_node.h>
#include <functional>
#include <ai/behavior_tree/behavior_tree.h>

using namespace ai::behavior_tree;


DecoratorNode::DecoratorNode() {}


DecoratorNode::~DecoratorNode() {

	delete _childNode;
}


std::vector<Node*> DecoratorNode::getChildNodes() {

	return std::vector<Node*> { _childNode };
}


DecoratorNode& DecoratorNode::setChildNode(Node* node) {

	// If node is attached to another tree.
	if (node->_behaviorTree != nullptr && node->_behaviorTree != this->_behaviorTree)
		throw std::exception();
	
	if (this->_behaviorTree != nullptr) {
		
		std::function<void(Node&)> traverse;
		traverse = [&](Node& root) {

			root._behaviorTree = this->_behaviorTree;

			for (auto& child : root.getChildNodes())
				traverse(*child);
		};

		traverse(*node);
	}

	_childNode = node;

	return *this;
}


void DecoratorNode::onRunning() {}


void DecoratorNode::onInitialization() {

	if (_childNode != nullptr) {
		_childNode->setStatus(Status::INVALID);
		_childNode->attachObserver(*this);
		_behaviorTree->enqueueNode(*_childNode);
	}
}


