#pragma once
#include <vector>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <iostream>
#include "Component.h"

class Actor {
public:
    Actor() = default;
    ~Actor() = default;

    // disable copy so you don’t accidentally copy unique_ptr
    Actor(const Actor&) = delete;
    Actor& operator=(const Actor&) = delete;

    // allow moves if you really need them
    Actor(Actor&&) = default;
    Actor& operator=(Actor&&) = default;

    template<typename T, typename... Args>
    T* addComponent(Args&&... args) {
        // 1) make the component
        auto comp = std::make_unique<T>(std::forward<Args>(args)...);
        comp->setOwner(this);
        T* ptr = comp.get();

        // 2) move it into the vector
        components.emplace_back(std::move(comp));

        // 3) put pointer in lookup
        lookup[typeid(T)] = ptr;

        // 4) initialize
        ptr->init();
        return ptr;
    }

    template<typename T>
    T* getComponent() {
        auto it = lookup.find(typeid(T));
        if (it != lookup.end())
            return static_cast<T*>(it->second);
        return nullptr;
    }

    void update(float dt) {
        for (auto& c : components)
            c->update(dt);
    }

    void setY(float y) {
		
	}

private:
    std::vector<std::unique_ptr<Component>>          components;
    std::unordered_map<std::type_index, Component*>  lookup;
    int height, width;
};