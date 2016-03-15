#pragma once
#include <ai/behavior_tree/nodes/composite_node.h>


namespace ai {

	namespace behavior_tree {

		class SelectorNode : public CompositeNode {
		public:

			explicit SelectorNode();

			virtual ~SelectorNode();

		private:

			std::vector<Node*>::iterator _processingChildNode;

			virtual void onInitialization() override final;

			virtual void observerCallback() override final;

		};

	}

}