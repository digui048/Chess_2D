#include "Core/Log.h"
#include "Core/Map.h"

class Scene
{
public:
    Scene();
    ~Scene();

    bool CreateScene();

    bool Update();

private:
    Map *map;
};