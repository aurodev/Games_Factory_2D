#include "ComponentSprite.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/rotate_vector.hpp>
#include "Application.h"
#include "SceneModule.h"

ComponentSprite::ComponentSprite(GameObject& gameObject, const char* componentName, COMPONENT_TYPE type) :
	Component(gameObject, componentName, type)
{
    vertices[0].pos = { 0.0f, 0.0f };
	vertices[1].pos = { 10.0f, 0.0f };
	vertices[2].pos = { 10.0f, 10.0f };
	vertices[3].pos = { 0.0f, 10.0f };

	vertices[0].color = vertices[1].color = vertices[2].color = vertices[3].color = { 1.0f, 1.0f, 1.0f, 1.0f };

	SetPivot((vertices[0].pos.x + vertices[1].pos.x + vertices[2].pos.x + vertices[3].pos.x) / 3,
		(vertices[0].pos.y + vertices[1].pos.y + vertices[2].pos.y + vertices[3].pos.y) / 3);

	App->sceneModule->spritesNum++;
	App->sceneModule->updateSceneVertices = true;
}

ComponentSprite::~ComponentSprite()
{
	App->sceneModule->spritesNum--;
}

void ComponentSprite::SetTexture(Texture& texture)
{
	spriteTexture = &texture;
}

Texture* ComponentSprite::GetTexture() const
{
	return spriteTexture;
}

void ComponentSprite::SetVertices(std::array<Vertex, 4> vertices)
{
	for (int i = 0; i < 4; i++)
	{
		this->vertices[i] = vertices[i];
	}
}

std::array<Vertex, 4> ComponentSprite::GetVertices() const
{
	return vertices;
}

void ComponentSprite::UpdateVerticesPositions(float x, float y)
{
	for (int i = 0; i < 4; i++)
	{
		vertices[i].pos.x += x;
		vertices[i].pos.y += y;
	}
}

void ComponentSprite::UpdateVerticesRotation(float angle)
{
	for (int i = 0; i < 4; i++)
	{
		vertices[i].pos -= pivot;
		glm::vec2 newRotation = glm::rotate(vertices[i].pos, angle);
		vertices[i].pos = newRotation;
		vertices[i].pos += pivot;
	}
}

void ComponentSprite::UpdateVerticesScale(float x, float y)
{
	for (int i = 0; i < 4; i++)
	{
		vertices[i].pos.x *= x;
		vertices[i].pos.y *= y;
	}
}

void ComponentSprite::SetPivot(float x, float y)
{
	pivot.x = x;
	pivot.y = y;
}

glm::vec2 ComponentSprite::GetPivot() const
{
	return pivot;
}
