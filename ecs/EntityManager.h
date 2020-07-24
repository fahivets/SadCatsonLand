#ifndef ENTITYMANAGER_H_INCLUDE
#define ENTITYMANAGER_H_INCLUDE
#include "ECSHelper.h"
#include "managers/ResourceHolder.h"
#include "managers/InputManager.h"

class Entity;

class EntityManager
{
public:
    // Constructor/Destructor
    EntityManager() = default;
    ~EntityManager() = default;

    // Functions
 //   void handleInput(const Uint8* keys);
    void handleInput(const InputManager& input);
    void update(const float& deltaTime);
    void render(SDL_Renderer& rRender);

    void refresh();
    void addToGroup(Entity* pEntity, Group group);
    Entity& addEntity();

    std::vector<Entity*>& getEntitiesByGroup(Group group);

private:
	std::vector<std::unique_ptr<Entity>> m_entities;
    std::array<std::vector<Entity*>, maxGroups> m_groupedEntities;

};

#endif  /*  end ENTITYMANAGER_H_INCLUDE     */