#include "ItemComponent.h"

#include "Entity.h"
#include "Game.h"
#include "Scene.h"
#include "CharacterController.h"

void ItemComponent::Update(Engine& engine, Game& game)
{
	//Vector2 desired_position = entity->position;
	//desired_position.y = entity->position.y + 500.0f * (engine.timer.delta_time / 1000.0f);
	//bool collision = game.tile_system.CheckForTiles({ desired_position }, entity->size);
	//if (!collision) entity->position = desired_position;

	Entity* player = game.activeScene->player;
	if ((entity->position.x + entity->size.x / 2 > player->position.x - player->size.x / 2 &&
		entity->position.x - entity->size.x / 2 < player->position.x + player->size.x / 2 &&
		entity->position.y + entity->size.y / 2 > player->position.y - player->size.y / 2 &&
		entity->position.y - entity->size.y / 2 < player->position.y + player->size.y / 2))
	{
		CharacterController* player = game.activeScene->player->GetComponent<CharacterController>();
		player->AddItem(item_id);
		game.activeScene->RemoveEntity(entity);
	}
}