#include "Game.h"

#include "Engine.h"
#include "Scene.h"
#include "Entity.h"
#include "RendererComponent.h"
#include "CameraComponent.h"
#include "CharacterController.h"

Game::Game(Engine& engine)
{
	Scene* level1 = new Scene();

	/* Player */
	{
		Entity* player = new Entity();
		player->name = "Player";
	
		RendererComponent* rc = new RendererComponent();
		rc->entity = player;
		rc->texture = engine.renderer.LoadTexture("playersprite.png");
		player->AddComponent(rc);

		CharacterController* ch = new CharacterController();
		ch->entity = player;
		player->AddComponent(ch);

		CameraComponent* cam = new CameraComponent();
		cam->entity = player;
		cam->SetAsMainCamera(engine);
		player->AddComponent(cam);


		level1->entities.push_back(player);
	}

	/* Blocks */
	// Block 1
	{
		Entity* block = new Entity();
		block->name = "block";

		RendererComponent* rc = new RendererComponent();
		rc->entity = block;
		block->AddComponent(rc);
		block->position.x = -200.0f;
		block->position.y = -300.0f;
		level1->entities.push_back(block);
	}

	// Block 2
	{
		Entity* block = new Entity();
		block->name = "block2";

		RendererComponent* rc = new RendererComponent();
		rc->entity = block;
		rc->parallaxFactor = 1.5f;
		block->AddComponent(rc);
		block->position.x = 300.0f;
		block->position.y = 100.0f;
		level1->entities.push_back(block);
	}

	activeScene = level1;
}

Game::~Game()
{
	for (Scene* scene : scenes)
	{
		delete scene;
	}
	scenes.clear();
}

void Game::Update(Engine& engine)
{
	activeScene->Update(engine);
}