#include <pch.h>
#include <ai/behavior_tree/nodes/composite_nodes/parallel_node.h>
#include <ai/behavior_tree/behavior_tree.h>


using namespace ai::behavior_tree;


ParallelNode::ParallelNode(unsigned short nSucceed, unsigned short nFail) : 
	_nSucceed(nSucceed),
	_nFail(nFail),
	_nCurrentSucceed(0), 
	_nCurrentFail(0) {}


ParallelNode::~ParallelNode() {}


void ParallelNode::onInitialization() {
	
	CompositeNode::onInitialization();

	for (auto it = this->_childNodes.rbegin(); it != this->_childNodes.rend(); ++it) {
		
		auto& child = *it;
		child->attachObserver(*this);
		this->_behaviorTree->enqueueNode(*child);
		_processingChildNodes.push_back(child);
	}
}


void ParallelNode::observerCallback() {
	
	for (unsigned short i = 0; i < _processingChildNodes.size(); i++) {

		switch (_processingChildNodes[i]->getStatus()) {

			case Status::FAILURE:
				_nCurrentFail++;
				_processingChildNodes.erase(_processingChildNodes.begin() + i--);
				break;
			case Status::SUCCESS: 
				_nCurrentSucceed++;
				_processingChildNodes.erase(_processingChildNodes.begin() + i--);
				break;
			default:
				break;
		}

		if (_nCurrentSucceed >= _nSucceed) {
			
			this->terminateNode(Status::SUCCESS);
			break;
		}

		if (_nCurrentFail >= _nFail) {
			
			this->terminateNode(Status::FAILURE);
			break;
		}
	}
}