#pragma once
#include "AbstractAction.h"
#include "Math\Vec3.h"

namespace Action
{
	class ScaleBy
		: public AbstractAction
	{
	public:
		ScaleBy(Vec3 scaleValue, float time);
		~ScaleBy();

		virtual void init() override;
		virtual void update(float time) override;
		virtual void onSuspend() override;
		virtual Action::AbstractAction * clone() override;

	private:
		Vec3 m_Origin;
		Vec3 m_DestSize;
	};
}