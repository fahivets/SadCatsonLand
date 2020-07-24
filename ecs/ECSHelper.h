#ifndef ECSHELPER_H_INCLUDE
#define ECSHELPER_H_INCLUDE
#include "stdafx.h"

/*
    Implement a "component-based entity system" where
    components contain not only data, but also logic.
*/

struct Component;
class Entity;
class EntityManager;
class InputManager;

// Typedef for the component ID type
using ComponentID = std::size_t;

// A maximum number of components
constexpr std::size_t maxComponents{ 32 };

// Typedef an <std::bitset> for components
using ComponentBitset = std::bitset<maxComponents>;

// Typedef an <std::array> for components:
using ComponentArray = std::array<Component*, maxComponents>;

// Implement groups by giving a group bitset to every entity
// and storing entity pointers in the entity manager.

// Typedef for group type
using Group = std::size_t;

// A maximum number of groups
constexpr std::size_t maxGroups{ 32 };

// Typedef an <std::bitset> for groups
using GroupBitset = std::bitset<maxGroups>;

namespace HelperInternal
{
    inline ComponentID getUniqueComponentID() noexcept
    {
        /*
            @return ComponentID = std::size_t 
            
            Getting an unique ID every time when we calling this function
        */
        static ComponentID lastID{ 0u };
        return lastID++;
    }
}

template <typename T>
inline ComponentID getComponentTypeID() noexcept
{
    /*
        @return ComponentID = std::size_t
        
        Getting an unique ComponentID based upon the type passed.
    */

    // <static_assert> to make sure this function
    // is only called with types that inherit from <Component>.
    static_assert(std::is_base_of<Component, T>::value,
        "<Type> must inherit from Component.");

    static ComponentID typeID{ HelperInternal::getUniqueComponentID() };
    return typeID;
}


#endif  /*  end ECSHELPER_H_INCLUDE     */
