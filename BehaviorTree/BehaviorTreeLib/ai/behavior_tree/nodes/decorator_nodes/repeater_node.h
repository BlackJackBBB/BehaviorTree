#pragma once
#include <ai/behavior_tree/nodes/decorator_node.h>


namespace ai {

	namespace behavior_tree {

		class RepeaterNode : public DecoratorNode {
		public:

			explicit RepeaterNode(bool isFinite = false, size_t nRepetitions = 0);

			virtual ~RepeaterNode();

		private:

			bool _isFinite;
			size_t _nRepetitions;
			size_t _repetitionNo;

			virtual void observerCallback() override final;

			virtual void onInitialization() override final;

		};

	}
}