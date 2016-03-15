#include <pch.h>
#include <ai/behavior_tree/nodes/decorator_nodes/inverter_node.h>


using namespace ai::behavior_tree;


InverterNode::InverterNode() {}


InverterNode::~InverterNode() {}


void InverterNode::observerCallback() {

	switch (this->_childNode->getStatus()) {
		case Status::FAILURE:
			this->terminateNode(Status::SUCCESS);
			break;
		case Status::SUCCESS:
			this->terminateNode(Status::FAILURE);
			break;
		default: 
			break;
	}
}