#include "CameraComponent.h"

#include "Engine.h"
#include "Entity.h"

void CameraComponent::SetAsMainCamera(Engine& engine)
{
	engine.renderer.camera = this;
}
