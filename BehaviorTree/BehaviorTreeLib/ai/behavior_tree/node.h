#pragma once
#include <observer.h>


namespace ai {

	namespace behavior_tree {

		class BehaviorTree;


		class Node : public Observable, public IObserver {

			friend class CompositeNode;
			friend class DecoratorNode;
			friend class LeafNode;
			friend class BehaviorTree;

		public:

			enum class Status {
				SUCCESS,
				FAILURE,
				RUNNING,
				INVALID
			};

			Node();

			virtual ~Node();

			virtual std::vector<Node*> getChildNodes() = 0;

			Node& process();

			Status getStatus() const;

			Node& setStatus(Status status);

		protected:

			BehaviorTree* _behaviorTree;

			void terminateNode(Node::Status resultStatus);

		private:

			Status _status;

			virtual void onRunning() = 0;

			virtual void onInitialization() = 0;

		};

	}

}