#pragma once

#include <list>
#include <string>
#include <vector>
#include <SDL3/SDL.h>
#include "Utils/Vector2D.h"
#include "pugixml.hpp"

struct Properties
{
    struct Property
    {
        std::string name;
        std::string value;
    };

    std::list<Property *> propertyList;

    ~Properties()
    {
        for (const auto &property : propertyList)
        {
            delete property;
        }

        propertyList.clear();
    }

    Property *GetProperty(const char *name)
    {
        for (const auto &property : propertyList)
        {
            if (property->name == name)
            {
                return property;
            }
        }

        return nullptr;
    }
};

struct MapLayer
{
    int id;
    std::string name;
    int width;
    int height;
    std::vector<int> tiles;
    Properties properties;

    unsigned int Get(int i, int j) const
    {
        return tiles[(j * width) + i];
    }
};

struct TileSet
{
    int firstGid;
    std::string name;
    float tileWidth;
    float tileHeight;
    int spacing;
    int margin;
    int tileCount;
    int columns;
    SDL_Texture *texture;

    SDL_FRect GetRect(unsigned int gid)
    {
        SDL_FRect rect = {0.0f};

        int relativeIndex = gid - firstGid;
        rect.w = tileWidth;
        rect.h = tileHeight;
        rect.x = margin + (tileWidth + spacing) * (relativeIndex % columns);
        rect.y = margin + (tileHeight + spacing) * (relativeIndex / columns);

        return rect;
    }
};

struct MapData
{
    int width;
    int height;
    int tileWidth;
    int tileHeight;
    std::list<TileSet *> tilesets;
    std::list<MapLayer *> layers;
};

class Map
{
public:
    Map();
    ~Map();

    void Load(std::string path, std::string mapFileName);
    void LoadProperties(pugi::xml_node &node, Properties &properties);

    void Update();

    Vector2D MapToWorld(int x, int y) const;
    Vector2D WorldToMap(int x, int y);

    TileSet *GetTileSetFromTileId(int gid) const;

private:
    bool mapLoaded;
    MapData mapData;
    pugi::xml_document mapFileXML;

    std::string mapFileName;
    std::string mapPath;
};