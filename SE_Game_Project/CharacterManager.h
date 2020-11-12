
#pragma once

#include <string>
#include<glm/glm.hpp>
#include "InputManager.h"
#include "LevelManager.h"
#include "LevelManager.h"
#include "ZombieManager.h"

#include <vector>

using namespace std;


struct Player {
	string name = "Steve";
	int health = 100;
	bool isAlive = true ;
	glm::vec2 direction = glm::vec2(1,0);
	glm::vec2 position = glm::vec2(0,0);
	int money = 500;
};

class CharacterManager
{
	public:
		CharacterManager();
		~CharacterManager();
		string GetName();
		int GetHealth();

		void Damage(int amount);
		void SetName(string n);
		void init(InputManager& inputManager, LevelManager& levelManager, const glm::vec2& playerPos);
		void update();
		void tile_collision();
		bool is_player_alive();

		Player m_player;
		ZombieManager m_zombieManager;


	private:
		struct CollisionPosition {
			glm::vec2 position;
			bool didCollisionOccur = false;
		};

		// This should be half of player square dimensions
		const glm::vec2 dim = glm::vec2(25.0f);
		InputManager* m_inputManager = nullptr;
		LevelManager* m_levelManager = nullptr;
		std::vector<char> blacklistedChar;
		bool collisionCheck(char parameter);
		void perform_tile_collision(CollisionPosition* cp);
};

