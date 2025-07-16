#include "Game.h"

#include "Engine.h"
#include "Scene.h"
#include "Entity.h"
#include "RendererComponent.h"
#include "CameraComponent.h"
#include "CharacterController.h"
#include "CameraController.h"

Game::Game(Engine& engine)
{
	Scene* level1 = new Scene();

	/* Player */
	{
		Entity* player = new Entity("Player", nullptr, { 5.0f, -50.0f }, { 24.0f, 48.0f });
		level1->player = player;

		RendererComponent* rc = new RendererComponent();
		rc->entity = player;
		rc->texture = engine.renderer.LoadTexture("Textures/playersprite.png");
		rc->texture_area = { 0.0f, 0.0f, 32.0f, 64.0f };
		player->AddComponent(rc);

		CharacterController* ch = new CharacterController();
		ch->entity = player;
		ch->Init();
		player->AddComponent(ch);

		Entity* camera_ent = new Entity();
		camera_ent->name = "Camera";

		CameraComponent* cam = new CameraComponent();
		cam->entity = camera_ent;
		cam->SetAsMainCamera(engine);
		camera_ent->AddComponent(cam);

		CameraController* cam_controller = new CameraController();
		cam_controller->entity = camera_ent;
		cam_controller->target = player;
		camera_ent->AddComponent(cam_controller);

		level1->entities.push_back(player);
		level1->entities.push_back(camera_ent);
	}

	activeScene = level1;

	tile_system.CreateTilesArray(engine, *activeScene);
	tile_system.tiles_texture = engine.renderer.LoadTexture("Textures/tiles.png");

	item_system.InitItemRegistry();
}

Game::~Game()
{
	for (Scene* scene : scenes)
	{
		scene->Unload();
		delete scene;
	}
	scenes.clear();

	tile_system.DeleteTilesArray();
}

void Game::Update(Engine& engine)
{
	tile_system.Update(engine);
	activeScene->Update(engine, *this);
}