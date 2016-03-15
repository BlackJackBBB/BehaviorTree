#pragma once
#include "ai\behavior.h"
#include <deque>


class DataContext;


namespace ai {

	namespace behavior_tree {

		class Node;

		class BehaviorTree : public IBehavior {
		public:

			explicit BehaviorTree(Node& rootNode, DataContext& dataContext);

			virtual ~BehaviorTree();

			BehaviorTree& enqueueNode(Node& node);

			DataContext& getDataContext() const;

		private:

			Node* _rootNode;
			DataContext* _dataContext;
			std::deque<Node*> _runningNodes;

			// Update behavior tree.
			virtual BehaviorTree& tick() override final;
			
			bool processNextNode();

		};

	}

}







