#pragma once


namespace ai {

	class IBehavior {
	public:

		virtual ~IBehavior() {}

		virtual IBehavior& tick() = 0;

	};

}

