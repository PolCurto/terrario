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
		rc->texture = engine.renderer.LoadTexture("Textures/playersprite.png");
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

	tile_system.CreateTilesArray();
	tile_system.tiles_texture = engine.renderer.LoadTexture("Textures/tiles.png");

	activeScene = level1;
}

Game::~Game()
{
	for (Scene* scene : scenes)
	{
		delete scene;
	}
	scenes.clear();

	tile_system.DeleteTilesArray();
}

void Game::Update(Engine& engine)
{
	tile_system.Update(engine);
	activeScene->Update(engine);
}