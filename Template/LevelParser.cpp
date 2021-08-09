#include "LevelParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "TileLayer.h"

#include <iostream>
#include <GLM/gtc/constants.hpp>

#include "Boss1.h"
#include "Config.h"
#include "Door.h"
#include "EnemyHuman1.h"
#include "EnemyKnight.h"
#include "EnemyType.h"
#include "GameObjectFactory.h"
#include "Napkin.h"
#include "ObjectLayer.h"
#include "Player.h"
#include "TextureID.h"

Level* LevelParser::ParseLevel(const char* levelFile, Scene* scene)
{
    Level* pLevel = new Level();
    // create a TinyXML document and load the map XML
    TiXmlDocument levelDocument;
    if(levelDocument.LoadFile(levelFile))
    {
        // get the root node
        TiXmlElement* pRoot = levelDocument.RootElement();
        pRoot->Attribute("tilewidth", &m_tileSize);
        pRoot->Attribute("width", &m_width);
        pRoot->Attribute("height", &m_height);

        scene->getNodeList().resize(m_height);
        for (auto& nodeList : scene->getNodeList())
        {
            nodeList.resize(m_width);
        }

        std::cout << "TileSize : " << m_tileSize << std::endl;
        std::cout << "Width : " << m_width << std::endl;
        std::cout << "Height: " << m_height << std::endl;
        Config::mapWidth = m_width * m_tileSize;
        Config::mapHeight = m_height * m_tileSize;

        // parse the tilesets
        for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
        {
            if (e->Value() == std::string("tileset"))
            {
                parseTilesets(e, pLevel->getTilesets());
            }
        }
        // parse any object layers
        for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
        {
            if (e->Value() == std::string("layer"))
            {
                parseTileLayer(e, pLevel->getLayers(), pLevel->getTilesets(), pLevel->getCollisionLayers(), scene);
            }
        }

        // parse object group
        for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
        {
            if (e->Value() == std::string("objectgroup"))
            {
                parseObjectLayer(e, scene);
            }
        }

        // we must parse the textures needed for this level, which have been added to properties
        for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
        {
            if (e->Value() == std::string("property"))
            {
                parseTextures(e);
            }
        }
    }
	else
    {
        std::cout << "TiXml load file fail\n";
    }

    // create the level object


    return pLevel;
}

void LevelParser::parseTextures(TiXmlElement* pTextureRoot)
{
    TextureManager::Instance().load(pTextureRoot -> Attribute("value"), pTextureRoot->Attribute("name"));
}

void LevelParser::parseObjectLayer(TiXmlElement* pObjectElement, Scene* scene)
{
    // create an object layer
    ObjectLayer* pObjectLayer = new ObjectLayer();
    //std::cout << pObjectElement->FirstChildElement()->Value() << std::endl;

    int widthOfTexture = 0, heightOfTexture = 0, realWidth = 0, realHeight = 0, maxHP = 0, power = 0;
    std::string ID = "";
    for (TiXmlElement* e = pObjectElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("properties"))
        {
            for (TiXmlElement* property = e->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
            {
                if (property->Value() == std::string("property"))
                {
                    if (property->Attribute("name") == std::string("realWidth"))
                    {
                        property->Attribute("value", &realWidth);
                    }
                    else if (property->Attribute("name") == std::string("realHeight"))
                    {
                        property->Attribute("value", &realHeight);
                    }
                    else if (property->Attribute("name") == std::string("widthOfTexture"))
                    {
                        property->Attribute("value", &widthOfTexture);
                    }
                    else if (property->Attribute("name") == std::string("heightOfTexture"))
                    {
                        property->Attribute("value", &heightOfTexture);
                    }
                    else if (property->Attribute("name") == std::string("maxHp"))
                    {
                        property->Attribute("value", &maxHP);
                    }
                    else if (property->Attribute("name") == std::string("power"))
                    {
                        property->Attribute("value", &power);
                    }
                    else if (property->Attribute("name") == std::string("id"))
                    {
                        ID = property->Attribute("value");
                    }
                }
            }
        }
        //std::cout << e->Value() << std::endl;
        if (e->Value() == std::string("object"))
        {
            int x, y;
            // get the initial node values type, x and y
            e->Attribute("x", &x);
            e->Attribute("y", &y);

            //GameObject* pGameObject = GameObjectFactory::Instance().create(e -> Attribute("type"));
            // get the property values
            /*for (TiXmlElement* properties = e->FirstChildElement();
                properties != NULL; properties = properties -> NextSiblingElement())
            {
                if (properties->Value() == std::string("properties"))
                {
                    for (TiXmlElement* property = properties -> FirstChildElement(); property != NULL; property = property -> NextSiblingElement())
                    {
                        if (property->Value() == std::string("property"))
                        {
                            if (property->Attribute("name") == std::string("realWidth"))
                            {
                                property->Attribute("value", &realWidth);
                            }
                            else if (property->Attribute("name") == std::string("realHeight"))
                            {
                                property->Attribute("value", &realHeight);
                            }
                            else if (property->Attribute("name") == std::string("maxHp"))
                            {
                                property->Attribute("value", &maxHP);
                            }
                            else if (property->Attribute("name") == std::string("power"))
                            {
                                property->Attribute("value", &power);
                            }
                            else if (property->Attribute("name") == std::string("teidxtureID"))
                            {
                                ID = property->Attribute("value");
                            }
                        }
                    }
                }
            }*/

        	// Todo implemeting characters.
            LoaderParams loader = LoaderParams(x, y, widthOfTexture, heightOfTexture, realWidth, realHeight, maxHP, power, ID);
            if (ID == "player")
            {
                Player* player = new Player(loader);
                scene->addChild(player, 4);
                scene->setPlayer(player);
            }
            else if (ID == "EnemyType::EnemyKnight")
            {
                scene->addChild(new EnemyKnight(loader),1);
            }
            else if (ID == "zombie")
            {
                scene->addChild(new EnemyHuman1(loader),4 );
            }
            else if (ID == EnemyType::Boss1)
            {
                scene->addChild(new Boss1(loader), 1);
            }
            else if (ID == EnemyType::DOOR)
            {
                Door* door = new Door(loader);
                scene->addChild(door, 1);
                scene->setDoor(door);
                door->setEnabled(false);
            }
           // pGameObject->load(new LoaderParams(x, y, width, height, textureID, numFrames, callbackID, animSpeed));
           // pObjectLayer->getGameObjects()->push_back(pGameObject);
        }
    }
    //pLayers->push_back(pObjectLayer);

}

void LevelParser::parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets)
{
    // first add the tileset to texture manager
    TextureManager::Instance().load(MAP_ROOT + pTilesetRoot -> FirstChildElement()->Attribute("source"), pTilesetRoot -> Attribute("name"));
    // create a tileset object
    Tileset tileset;
    pTilesetRoot->FirstChildElement()->Attribute("width", &tileset.width);  // image size
    pTilesetRoot->FirstChildElement()->Attribute("height", &tileset.height); // image size
    pTilesetRoot->Attribute("firstgid", &tileset.firstGridID);
    pTilesetRoot->Attribute("tilewidth", &tileset.tileWidth);
    pTilesetRoot->Attribute("tileheight", &tileset.tileHeight);
    pTilesetRoot->Attribute("spacing", &tileset.spacing);
    pTilesetRoot->Attribute("margin", &tileset.margin);
    tileset.name = pTilesetRoot->Attribute("name");
    tileset.numColumns = tileset.width / (tileset.tileWidth + tileset.spacing);  // total columns
    pTilesets->push_back(tileset);

    std::cout << "Source : " << pTilesetRoot->FirstChildElement()->Attribute("source") << "\n"
        << "Name : " << pTilesetRoot->Attribute("name") << "\n"
        << "Width : " << tileset.width << "\n"
        << "Height : " << tileset.height << "\n"
        << "Total Columns : " << tileset.numColumns << "\n"
        << "Firstgid : " << tileset.firstGridID << "\n"
        << "TileWidth : " << tileset.tileWidth << "\n"
        << "TileHeight : " << tileset.tileHeight << "\n"
        << "Spacing : " << tileset.spacing << "\n"
        << "Magin : " << tileset.margin << std::endl;
}

void LevelParser::parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*>* pLayers, const std::vector<Tileset>* pTilesets, std::vector<Layer*>* pCollisionLayers, Scene* scene)
{
    int width = 0;
    int height = 0;
    bool collidable = false;
    bool isTransparent = false;
    int layerOrder = 0;
    pTileElement->Attribute("width", &width);
    pTileElement->Attribute("height", &height);
    //TileLayer* pTileLayer = new TileLayer(m_tileSize, *pTilesets, height, width);
    TileLayer* pTileLayer = new TileLayer(m_tileSize, m_width, m_height, *pTilesets);
    // tile data
    std::vector<std::vector<int>> data;
    std::vector<int> ids;

    TiXmlElement* pDataNode = nullptr;
    for (TiXmlElement* e = pTileElement->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("properties"))
        {
            for (TiXmlElement* property = e->FirstChildElement(); property != NULL; property = property->NextSiblingElement())
            {
                if (property->Value() == std::string("property"))
                {
                    if (property->Attribute("name") == std::string("collidable"))
                    {
                        collidable = property->Attribute("value");
                    }
                    if (property->Attribute("name") == std::string("transparent"))
                    {
                        isTransparent = property->Attribute("value");
                    }
                    if (property->Attribute("name") == std::string("layer_order"))
                    {
                        property->Attribute("value", &layerOrder);
                    }
                }
            }
        }
		if (e->Value() == std::string("data"))
		{
			pDataNode = e;
		}
    }
    for (TiXmlNode* e = pDataNode->FirstChild(); e != NULL; e = e->NextSibling())
    {
        TiXmlText* text = e->ToText();
        std::string t = text->Value();
        //std::cout << "<Map String>\n" << t << std::endl;
        csvDataToVector(t, ids);
    }
    // uncompress zlib compression
    /*uLongf numGids = m_width * m_height * sizeof(int);
    std::vector<unsigned> gids(numGids);
    uncompress((Bytef*)&gids[0], &numGids, (const Bytef*)decodedIDs.c_str(), decodedIDs.size());*/


    std::vector<int> layerRow(m_width);

    for (int j = 0; j < m_height; j++)
    {
        data.push_back(layerRow);
    }

    for (int rows = 0; rows < m_height; rows++)
    {
        for (int cols = 0; cols < m_width; cols++)
        {
            data[rows][cols] = ids[rows * m_width + cols];
            //std::cout << data[rows][cols];

            scene->getNodeList()[rows][cols].m_x = cols * m_tileSize;
            scene->getNodeList()[rows][cols].m_y = rows * m_tileSize;
            scene->getNodeList()[rows][cols].m_nodeSize = m_tileSize;
        	if(collidable && ids[rows * m_width + cols] != 0)
				scene->getNodeList()[rows][cols].m_isCollidable = collidable;
        	if(isTransparent && ids[rows * m_width + cols] != 0)
				scene->getNodeList()[rows][cols].m_isTransparent = isTransparent;
        }
    }

    pTileLayer->setTileIDs(data);

    if (collidable)
    {

        //pCollisionLayers->push_back(pTileLayer);
    }
    std::cout << collidable <<" "<< isTransparent << std::endl;
    scene->addChild(pTileLayer, layerOrder);
    //pLayers->push_back(pTileLayer);



}

void LevelParser::csvDataToVector(std::string orgText, std::vector<int>& vector)
{
    std::string tmp;
    for (int i = 0; i < orgText.size(); i++)
    {

        if (orgText[i] != ',')
        {
            tmp += orgText[i];

        }
        else
        {
            vector.push_back(std::stoi(tmp));
            tmp.clear();
        }
    }
    vector.push_back(std::stoi(tmp));
}
