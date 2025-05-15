#pragma once
#include "Component.h"
#include "TileMap.h"

/// A simple component that just holds a pointer to the TileMap
class MapComponent : public Component {
public:
    /// You must pass in the world’s TileMap when you construct it
    MapComponent(TileMap* world_)
        : tileMap(world_)
    {}

    /// No special init/update needed here
    void init() override {}
    void update(float) override {}

    /// Expose the map to whoever needs it
    TileMap* getMap() const { return tileMap; }

private:
    TileMap* tileMap;
};