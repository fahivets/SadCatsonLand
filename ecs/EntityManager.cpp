#include "stdafx.h"
#include "EntityManager.h"
#include "Entity.h"

void EntityManager::handleInput(const InputManager& input)
{
    for (auto& entity : m_entities)
    {
        entity->handleInput(input);
    }
}

void EntityManager::update(const float& deltaTime)
{
    // Update all "living" entities
    for (auto& entity : m_entities)
    {
        entity->update(deltaTime);
    }
}

void EntityManager::render(SDL_Renderer& rRender)
{
    for (auto& entity : m_entities)
    {
        entity->render(rRender);
    }
}

void EntityManager::refresh()
{
    // Remove entities with incorrect groups from the buckets
    for (auto id(0u); id < maxGroups; ++id)
    {
        auto& vector(m_groupedEntities[id]);

        vector.erase(std::remove_if(std::begin(vector), std::end(vector),
            [id](Entity* pEntity)
            {
                return !pEntity->isAlive() ||
                    !pEntity->hasGroup(id);
            }),
            std::end(vector));
    }

    // Cleaning up "dead" m_entities by using "erase-remove idiom".
    m_entities.erase(
        std::remove_if(std::begin(m_entities), std::end(m_entities),
            [](const std::unique_ptr<Entity>& rEntity)
            {
                return !rEntity->isAlive();
            }),
        std::end(m_entities));
}

void EntityManager::addToGroup(Entity* pEntity, Group group)
{
    /*
        @return void

        Add a group to an correct "group bucket" in entity
    */

    m_groupedEntities[group].emplace_back(pEntity);
}

Entity& EntityManager::addEntity()
{
    Entity* entity{ new Entity{*this} };
    std::unique_ptr<Entity> uPtr{ entity };

    m_entities.emplace_back(std::move(uPtr));

    return (*entity);
}

std::vector<Entity*>& EntityManager::getEntitiesByGroup(Group group)
{
    /*
        @return 

        Get entities that belong to a certain group
    */
    return (m_groupedEntities[group]);
}