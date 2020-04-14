#include "TestSplatNode.h"
#include "Utility\Random.h"
#include "Utility\Timer.h"

#include "Component\Graphics\SpriteRenderer.h"
#include "Component\ActionManager.h"

#include "Utility\Random.h"
#include "Utility\Action\Actions.h"
#include "Utility\Action\EasingActions.h"

const float TestSplatNode::minSize = 1.0f;

TestSplatNode::TestSplatNode(IGameMediator * pGameMediator, float destSize, const Vec2 & direction)
	: GameObject(pGameMediator),
	m_DestSize(destSize),
	m_Direction(direction),
	m_CreateChild(true)
{
	Random random;
	m_pTimer = new Timer(0.05f);
}

TestSplatNode::~TestSplatNode()
{
	delete m_pTimer;
}

void TestSplatNode::start()
{
	setSize(Vec3(0.0f, 0.0f, 1.0f));

	auto renderer = new SpriteRenderer(this);
	//レイヤーを水しぶき用にセット
	renderer->setGraphicsLayer(GraphicsLayer::Splash);
	renderer->setTextureByName("CircleFill");
	renderer->setColor(Color(0.25f, 0.3f, 0.8f, 1.0f));

	//サイズ変更用Actionをセット
	auto actionManager = new Action::ActionManager(this);
	actionManager->enqueueAction(new Action::ScaleTo(Vec3(m_DestSize, m_DestSize, 1.0f), 0.1f));
}

void TestSplatNode::update()
{
	if (minSize >= m_DestSize ||
		!m_CreateChild)
		return;

	m_pTimer->update();

	if (m_pTimer->isTime())
	{
		m_CreateChild = false;

		Vec2 splatPos = m_Direction * (m_DestSize * 0.5f);

		auto pSplat = new TestSplatNode(m_pGameMediator, m_DestSize * 0.6f, m_Direction);
		pSplat->setPosition(getPosition() + splatPos.toVec3());
	}
}