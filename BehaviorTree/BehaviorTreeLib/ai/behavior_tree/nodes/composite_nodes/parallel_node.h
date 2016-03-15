#pragma once
#include <ai/behavior_tree/nodes/composite_node.h>


namespace ai {

	namespace behavior_tree {

		class ParallelNode : public CompositeNode {
		public:

			explicit ParallelNode(unsigned short nSucceed, unsigned short nFail);

			virtual ~ParallelNode();

		private:

			std::vector<Node*> _processingChildNodes;
			const unsigned short _nSucceed;
			const unsigned short _nFail;
			unsigned short _nCurrentSucceed;
			unsigned short _nCurrentFail;

			virtual void onInitialization() override final;

			virtual void observerCallback() override final;

		};

	}

}