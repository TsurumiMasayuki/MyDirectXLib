#pragma once

	class PhysicsLayer
	{
	public:
		enum LayerEnum
		{
			None = 0,
			Player = 1,
			Block = 2,
			Magnet = 3,
		};

		static bool isHitLayer(LayerEnum layer1, LayerEnum layer2)
		{
			static const bool layerHitList[4][4] =
			{
				// None, Player, Block, Magnet,
				{ true, true, true, true },	//None
				{ true, false, true, true },	//Player
				{ true, true, false, true },	//Block
				{ true, true, true, true},	//Magnet
			};

			return layerHitList[(int)layer1][(int)layer2];
		}

	private:
		PhysicsLayer() {};
		~PhysicsLayer() {};
	};