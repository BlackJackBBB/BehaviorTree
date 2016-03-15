#pragma once
#include <ai/behavior_tree/nodes/decorator_node.h>


namespace ai {

	namespace behavior_tree {

		class SucceederNode : public DecoratorNode {
		public:

			explicit SucceederNode();

			virtual ~SucceederNode();

		private:

			virtual void observerCallback() override final;

		};

	}
}