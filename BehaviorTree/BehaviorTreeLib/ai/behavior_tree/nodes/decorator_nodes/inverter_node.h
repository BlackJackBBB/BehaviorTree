#pragma once
#include <ai/behavior_tree/nodes/decorator_node.h>


namespace ai {
	
	namespace behavior_tree {
		
		class InverterNode : public DecoratorNode {
		public:

			explicit InverterNode();

			virtual ~InverterNode();

		private:

			virtual void observerCallback() override final;

		};

	}

}