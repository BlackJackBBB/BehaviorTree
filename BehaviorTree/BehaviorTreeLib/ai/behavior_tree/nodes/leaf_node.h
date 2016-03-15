#pragma once
#include <ai/behavior_tree/node.h>

namespace ai {
	
	namespace behavior_tree {
		
		class LeafNode : public Node {
		public:

			virtual ~LeafNode();

			virtual std::vector<Node*> getChildNodes() override final;

		private:

			virtual void onRunning() override final;

			virtual void onInitialization() override;

			virtual void observerCallback() override final;

			virtual bool runCondition() = 0;

			virtual bool succeedCondition() = 0;

			virtual bool failCondition() = 0;

			virtual void operation() = 0;

		};

	}

}

