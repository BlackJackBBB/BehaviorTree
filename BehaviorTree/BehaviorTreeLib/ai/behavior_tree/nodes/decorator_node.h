#pragma once
#include <ai/behavior_tree/node.h>
#include <vector>


namespace ai {

	namespace behavior_tree {

		class DecoratorNode : public Node {
		public:

			explicit DecoratorNode();

			virtual ~DecoratorNode();

			virtual std::vector<Node*> getChildNodes() override final;

			DecoratorNode& setChildNode(Node* node);

		protected:

			Node* _childNode;

			virtual void onInitialization() override;

		private:

			virtual void onRunning() override;

		};

	}

}


