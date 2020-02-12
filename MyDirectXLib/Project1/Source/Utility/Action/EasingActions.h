#pragma once
#include "AbstractAction.h"
#include "Math\Easing.h"
#include "Utility\Timer.h"

namespace Action
{
	//イージング系Actionのベース
	template<float EASE_FUNC(float)>
	class EaseAction
		: public AbstractAction
	{
	public:
		EaseAction(AbstractAction* pTargetAction) : m_pTargetAction(pTargetAction) {};
		~EaseAction() { delete m_pTargetAction; }

		virtual void init() override
		{
			m_pTargetAction->setUser(m_pUser);
			m_pTargetAction->baseInit();

			m_pTimer->setMaxTime(m_pTargetAction->getActionTime());
			m_pTimer->reset();
		}

		virtual void update(float time) override
		{
			m_pTargetAction->update(EASE_FUNC(time));
		}

		virtual void onSuspend() override
		{
			m_pTargetAction->onSuspend();
		}

		virtual bool isEnd() override
		{
			return m_pTimer->isTime();
		}

		virtual EaseAction<EASE_FUNC>* clone() override
		{
			return new EaseAction<EASE_FUNC>(m_pTargetAction->clone());
		}

	private:
		AbstractAction* m_pTargetAction;
	};

	//各Easing関数に対応したAction

	using EaseInSine = EaseAction<Easing::easeInSine>;
	using EaseOutSine = EaseAction<Easing::easeOutSine>;
	using EaseInOutSine = EaseAction<Easing::easeInOutSine>;

	using EaseInQuad = EaseAction<Easing::easeInQuad>;
	using EaseOutQuad = EaseAction<Easing::easeOutQuad>;
	using EaseInOutQuad = EaseAction<Easing::easeInOutQuad>;

	using EaseInCubic = EaseAction<Easing::easeInCubic>;
	using EaseOutCubic = EaseAction<Easing::easeOutCubic>;
	using EaseInOutCubic = EaseAction<Easing::easeInOutCubic>;

	using EaseInQuart = EaseAction<Easing::easeInQuart>;
	using EaseOutQuart = EaseAction<Easing::easeOutQuart>;
	using EaseInOutQuart = EaseAction<Easing::easeInOutQuart>;

	using EaseInQuint = EaseAction<Easing::easeInQuint>;
	using EaseOutQuint = EaseAction<Easing::easeOutQuint>;
	using EaseInOutQuint = EaseAction<Easing::easeInOutQuint>;

	using EaseInExpo = EaseAction<Easing::easeInExpo>;
	using EaseOutExpo = EaseAction<Easing::easeOutExpo>;
	using EaseInOutExpo = EaseAction<Easing::easeInOutExpo>;

	using EaseInCirc = EaseAction<Easing::easeInCirc>;
	using EaseOutCirc = EaseAction<Easing::easeOutCirc>;
	using EaseInOutCirc = EaseAction<Easing::easeInOutCirc>;

	using EaseInBack = EaseAction<Easing::easeInBack>;
	using EaseOutBack = EaseAction<Easing::easeOutBack>;
	using EaseInOutBack = EaseAction<Easing::easeInOutBack>;

	using EaseInElastic = EaseAction<Easing::easeInElastic>;
	using EaseOutElastic = EaseAction<Easing::easeOutElastic>;
	using EaseInOutElastic = EaseAction<Easing::easeInOutElastic>;

	using EaseInBounce = EaseAction<Easing::easeInBounce>;
	using EaseOutBounce = EaseAction<Easing::easeOutBounce>;
	using EaseInOutBounce = EaseAction<Easing::easeInOutBounce>;
}