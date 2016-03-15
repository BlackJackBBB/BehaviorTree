#pragma once
#include <ai/behavior_tree/nodes/decorator_node.h>


namespace ai {

	namespace behavior_tree {

		class UntilFailNode : public DecoratorNode {
		public:

			explicit UntilFailNode();

			virtual ~UntilFailNode();

		private:

			virtual void observerCallback() override final;

		};

	}
}