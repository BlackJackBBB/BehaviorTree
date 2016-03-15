#include <pch.h>
#include <ai/behavior_tree/nodes/composite_node.h>
#include <vector>
#include <functional>


using namespace ai::behavior_tree;


CompositeNode::CompositeNode() {}


CompositeNode::~CompositeNode() {

	for (auto& node : _childNodes)
		delete node;
}


std::vector<Node*> CompositeNode::getChildNodes() {

	return _childNodes;
}


CompositeNode& CompositeNode::addChildNode(Node* node) {

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

	_childNodes.push_back(node);
	
	return *this;
}


CompositeNode& CompositeNode::addChildNode(const std::initializer_list<Node*>& nodes) {

	for (auto& node : nodes)
		addChildNode(node);

	return *this;
}


void CompositeNode::onRunning() {}


void CompositeNode::onInitialization() {
	
	for (auto& child : _childNodes)
		child->setStatus(Status::INVALID);
}