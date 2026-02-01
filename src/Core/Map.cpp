#include "Map.h"
#include "Core/Log.h"
#include "Core/TextureImporter.h"
#include "Core/Application.h"
#include "Core/Renderer.h"

Map::Map()
{
}

Map::~Map()
{
    for (auto &tileset : mapData.tilesets)
    {
        if (tileset->texture != nullptr)
        {
            SDL_DestroyTexture(tileset->texture);
            tileset->texture = nullptr;
        }

        delete tileset;
    }
    mapData.tilesets.clear();

    for (auto &layer : mapData.layers)
    {
        delete layer;
    }
    mapData.layers.clear();

    mapLoaded = false;
}

void Map::Load(std::string path, std::string mapFileName)
{
    this->mapFileName = mapFileName;
    mapPath = path;
    std::string mapPathName = mapPath + mapFileName;

    pugi::xml_parse_result result = mapFileXML.load_file(mapPathName.c_str());

    if (!result)
    {
        Log::Warn("Could not load map xml file {}. pugi error: {}", mapPathName, result.description());
        return;
    }

    mapData.width = mapFileXML.child("map").attribute("width").as_int();
    mapData.height = mapFileXML.child("map").attribute("height").as_int();
    mapData.tileWidth = mapFileXML.child("map").attribute("tilewidth").as_int();
    mapData.tileHeight = mapFileXML.child("map").attribute("tileheight").as_int();

    for (pugi::xml_node tilesetNode = mapFileXML.child("map").child("tileset"); tilesetNode != NULL; tilesetNode = tilesetNode.next_sibling("tileset"))
    {
        TileSet *tileSet = new TileSet();
        tileSet->firstGid = tilesetNode.attribute("firstgid").as_int();
        tileSet->name = tilesetNode.attribute("name").as_string();
        tileSet->tileWidth = tilesetNode.attribute("tilewidth").as_float();
        tileSet->tileHeight = tilesetNode.attribute("tileheight").as_float();
        tileSet->spacing = tilesetNode.attribute("spacing").as_int();
        tileSet->margin = tilesetNode.attribute("margin").as_int();
        tileSet->tileCount = tilesetNode.attribute("tilecount").as_int();
        tileSet->columns = tilesetNode.attribute("columns").as_int();

        std::string imgName = tilesetNode.child("image").attribute("source").as_string();
        tileSet->texture = TextureImporter::Load((mapPath + imgName));

        mapData.tilesets.push_back(tileSet);
    }

    for (pugi::xml_node layerNode = mapFileXML.child("map").child("layer"); layerNode != NULL; layerNode = layerNode.next_sibling("layer"))
    {
        MapLayer *mapLayer = new MapLayer();
        mapLayer->id = layerNode.attribute("id").as_int();
        mapLayer->name = layerNode.attribute("name").as_string();
        mapLayer->width = layerNode.attribute("width").as_int();
        mapLayer->height = layerNode.attribute("height").as_int();

        LoadProperties(layerNode, mapLayer->properties);

        for (pugi::xml_node tileNode = layerNode.child("data").child("tile"); tileNode != NULL; tileNode = tileNode.next_sibling("tile"))
        {
            mapLayer->tiles.push_back(tileNode.attribute("gid").as_int());
        }

        mapData.layers.push_back(mapLayer);
    }

    // Here goes the pieces that are going to be created
    // ......
    // ......
    // ......
    // ......
    Log::Info("Successfully parsed map XML file :{}", mapFileName);
    Log::Info("width : {} height : {}", mapData.width, mapData.height);
    Log::Info("tile_width : {} tile_height : {}", mapData.tileWidth, mapData.tileHeight);
    Log::Info("Tilesets-----");

    for (const auto &tileset : mapData.tilesets)
    {
        Log::Info("name : {} firstgid : {}", tileset->name, tileset->firstGid);
        Log::Info("tile width : {} tile height : {}", tileset->tileWidth, tileset->tileHeight);
        Log::Info("spacing : {} margin : {}", tileset->spacing, tileset->margin);
    }

    Log::Info("Layers-----");

    for (const auto &layer : mapData.layers)
    {
        Log::Info("id : {} name : {}", layer->id, layer->name);
        Log::Info("Layer width : {} Layer height : {}", layer->width, layer->height);
    }

    mapLoaded = true;
}

void Map::LoadProperties(pugi::xml_node &node, Properties &properties)
{
    for (pugi::xml_node propertieNode = node.child("properties").child("property"); propertieNode; propertieNode = propertieNode.next_sibling("property"))
    {
        Properties::Property *p = new Properties::Property();
        p->name = propertieNode.attribute("name").as_string();
        p->value = propertieNode.attribute("value").as_string();

        properties.propertyList.push_back(p);
    }
}

void Map::Update()
{
    if (mapLoaded)
    {
        for (const auto &mapLayer : mapData.layers)
        {
            if (mapLayer->properties.GetProperty("Draw") != NULL && mapLayer->properties.GetProperty("Draw")->value == "true")
            {
                for (int y = 0; y < mapLayer->height; ++y)
                {
                    for (int x = 0; x < mapLayer->width; ++x)
                    {
                        int gid = mapLayer->Get(x, y);

                        if (gid == 0)
                            continue;

                        TileSet *tileset = GetTileSetFromTileId(gid);
                        if (tileset == nullptr || tileset->texture == nullptr)
                            continue;

                        SDL_FRect srcRect = tileset->GetRect(gid);

                        Vector2D worldPos = MapToWorld(x, y);

                        SDL_FRect dstRect;
                        dstRect.x = worldPos.getX();
                        dstRect.y = worldPos.getY();
                        dstRect.w = (float)mapData.tileWidth;
                        dstRect.h = (float)mapData.tileHeight;

                        Application::GetInstance().GetRenderer()->DrawTexture(tileset->texture, &srcRect, &dstRect);
                    }
                }
            }
        }
    }
}

Vector2D Map::MapToWorld(int x, int y) const
{
    Vector2D ret;

    ret.setX((float)(x * mapData.tileWidth));
    ret.setY((float)(y * mapData.tileHeight));

    return ret;
}

Vector2D Map::WorldToMap(int x, int y)
{
    Vector2D ret(0.0f, 0.0f);
    ret.setX((float)(x / mapData.tileWidth));
    ret.setY((float)(y / mapData.tileHeight));

    return ret;
}

TileSet *Map::GetTileSetFromTileId(int gid) const
{
    TileSet *set = nullptr;
    for (const auto &tileset : mapData.tilesets)
    {
        set = tileset;
        if (gid >= tileset->firstGid && gid < tileset->firstGid + tileset->tileCount)
        {
            break;
        }
    }
    return set;
}
