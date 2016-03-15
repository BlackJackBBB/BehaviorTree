#include <pch.h>
#include <ai/behavior_tree/behavior_tree.h>
#include <ai/behavior_tree/node.h>
#include <functional>


using namespace ai::behavior_tree;


BehaviorTree::BehaviorTree(Node& rootNode, DataContext& dataContext) : 
	_rootNode(&rootNode),
	_dataContext(&dataContext) {

	// If root node is attached to another tree.
	if (rootNode._behaviorTree != nullptr && rootNode._behaviorTree != this)
		throw std::exception();

	std::function<void(Node&)> traverse;
	traverse = [&](Node& root) {
		
		root._behaviorTree = this;

		for (auto& child : root.getChildNodes())
			traverse(*child);
	};

	traverse(rootNode);

	_runningNodes.push_back(&rootNode);
}


BehaviorTree::~BehaviorTree() {

	delete _rootNode;
}


BehaviorTree& BehaviorTree::enqueueNode(Node& node) {
	
	_runningNodes.push_front(&node);

	return *this;
}


DataContext& BehaviorTree::getDataContext() const {
	
	return *_dataContext;
}


BehaviorTree& BehaviorTree::tick() {

	// Insert tree end-of-update marker to queue.
	_runningNodes.push_back(nullptr);

	// Update nodes from queue until marker is reached.
	while (this->processNextNode())
		continue;

	return *this;
}


bool BehaviorTree::processNextNode() {

	auto currentNode = _runningNodes.front();
	_runningNodes.pop_front();

	// If end-of-update marker is reached stop processing.
	if (currentNode == nullptr)
		return false;

	// Process next running node.
	currentNode->process();

	// If node is succeeded or failed run observer if it exists, or enqueue node again.
	if (currentNode->getStatus() == Node::Status::FAILURE || currentNode->getStatus() == Node::Status::SUCCESS)
		currentNode->notifyObservers();
	else if (currentNode->getStatus() == Node::Status::RUNNING)
		_runningNodes.push_back(currentNode);

	return true;
}