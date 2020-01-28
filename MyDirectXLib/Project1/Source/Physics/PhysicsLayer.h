#pragma once

	class PhysicsLayer
	{
	public:
		enum LayerEnum
		{
			None = 0,
			Player = 1,
		};

		static bool isHitLayer(LayerEnum layer1, LayerEnum layer2)
		{
			static const bool layerHitList[2][2] =
			{
							// None, Player
				/*None*/	{ true, true, },
				/*Player*/	{ true, false,}	
			};

			return layerHitList[(int)layer1][(int)layer2];
		}

	private:
		PhysicsLayer() {};
		~PhysicsLayer() {};
	};