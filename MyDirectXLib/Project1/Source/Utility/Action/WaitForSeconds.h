#pragma once
#include "AbstractAction.h"

namespace Action
{
	class WaitForSeconds
		: public AbstractAction
	{
	public:
		WaitForSeconds(float waitTime);
		~WaitForSeconds();

		virtual void init() override;
		virtual void update(float time) override;
		virtual void onSuspend() override;

		virtual Action::WaitForSeconds* clone() override;
	};
}