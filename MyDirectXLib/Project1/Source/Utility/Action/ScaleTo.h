#pragma once
#include "AbstractAction.h"
#include "Math\Vec3.h"

namespace Action
{
	class ScaleTo
		: public AbstractAction
	{
	public:
		ScaleTo(Vec3 scaleValue, float time);
		~ScaleTo();

		virtual void init() override;
		virtual void update(float time) override;
		virtual void onSuspend() override;
		virtual Action::AbstractAction * clone() override;

	private:
		Vec3 m_Origin;
		Vec3 m_DestSize;
	};
}