#pragma once
#include "AbstractAction.h"
#include "Math\Vec3.h"

namespace Action
{
	class MoveTo
		: public AbstractAction
	{
	public:
		MoveTo(Vec3 destination, float time);
		~MoveTo();

		virtual void init() override;
		virtual void update(float time) override;
		virtual void onSuspend() override;
		virtual Action::MoveTo* clone() override;

	private:
		Vec3 m_Origin;
		Vec3 m_Destination;
	};
};