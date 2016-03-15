#pragma once
#include <ai/behavior_tree/node.h>
#include <vector>


namespace ai {

	namespace behavior_tree {

		class CompositeNode : public Node {
		public:

			explicit CompositeNode();

			virtual ~CompositeNode();

			virtual std::vector<Node*> getChildNodes() override final;

			CompositeNode& addChildNode(Node* node);

			CompositeNode& addChildNode(const std::initializer_list<Node*>& nodes);

		protected:

			std::vector<Node*> _childNodes;

			virtual void onRunning() override;

			virtual void onInitialization() override;

		};

	}

}



