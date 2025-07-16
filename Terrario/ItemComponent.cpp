#include "ItemComponent.h"

#include "Entity.h"
#include "Game.h"
#include "Scene.h"
#include "CharacterController.h"

void ItemComponent::Update(Engine& engine, Game& game)
{
	if (abs(entity->position.x - game.activeScene->player->position.x) < entity->size.x &&
		abs(entity->position.y - game.activeScene->player->position.y) < entity->size.y)
	{
		//DebugLog("ITEM COLLISION");
		CharacterController* player = game.activeScene->player->GetComponent<CharacterController>();
		player->AddItem(item_id);
		game.activeScene->RemoveEntity(entity);
	}
}