#include "Scene.h"

Scene::Scene()
{
}

Scene::~Scene()
{
    delete map;
}

bool Scene::CreateScene()
{
    map = new Map();
    map->Load("assets/Maps/", "Chessboard.tmx");
    return true;
}

bool Scene::Update()
{
    map->Update();

    return true;
}
