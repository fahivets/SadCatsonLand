#include "stdafx.h"
#include "Entity.h"

// Constructors
Entity::Entity(EntityManager& rManager) : m_rManager(rManager)
{}

// Functions
void Entity::handleInput(const InputManager& input)
{
    for (auto& component : m_components)
    {
        component->handleInput(input);
    }
}

void Entity::update(const float& deltaTime)
{
    for (auto& component : m_components)
    {
        component->update(deltaTime);
    }
}

void Entity::render(SDL_Renderer& rRender)
{
    for (auto& component : m_components)
    {
        component->render(rRender);
    }
}

// Some methods to control the lifetime of the entity
bool Entity::isAlive() const
{
    return (m_alive);
}

void Entity::destroy()
{
    m_alive = false;
}

// Methods for working with Groups
bool Entity::hasGroup(Group group) const noexcept
{
    return (m_groupBitset[group]);
}

void Entity::addGroup(Group group) noexcept
{
    m_groupBitset[group] = true;
    m_rManager.addToGroup(this, group);
}

void Entity::delGroup(Group group) noexcept
{
    m_groupBitset[group] = false;
}