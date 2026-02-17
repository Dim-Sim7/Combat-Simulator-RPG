#pragma once
#include <vector>
/*
This container stores loot polymorphically using std::unique_ptr<Loot> rather than
std::vector<Loot> to avoid object slicing. In C++, polymorphic behavior is only
preserved through indirection (pointers or references); storing derived objects by
value would discard their derived state and behavior. std::unique_ptr expresses
exclusive ownership of each loot object by the container, ensures correct lifetime
management via RAII, and guarantees that the appropriate derived destructors are
called through Loot’s virtual destructor. This design allows the container to hold
heterogeneous loot types while maintaining type safety, correct virtual dispatch,
and automatic cleanup.
*/
#include "lootable.h"
#include <memory>
class Container {
public:


    template<typename T, typename... Args>
    void add(Args&&... args) {
        contents.push_back(std::make_unique<T>(std::forward<Args>(args)...));
    }

    //Usage:
    //Container c          c.add<ItemLoot>(... )



protected:
    std::vector<std::unique_ptr<Lootable>> contents;
};