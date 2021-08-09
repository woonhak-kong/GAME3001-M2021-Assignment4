#include "Level.h"

Level::Level()
{
}

Level::~Level()
{
	Level::clean();
}

void Level::update()
{
    for (int i = 0; i < m_layers.size(); i++)
    {
        m_layers[i]->update();
    }
}

void Level::draw()
{
    for (int i = 0; i < m_layers.size(); i++)
    {
        m_layers[i]->draw();
    }
}

void Level::clean()
{
	for (auto& layer : m_layers)
	{
        delete layer;
        layer = nullptr;
	}
}


std::vector<Tileset>* Level::getTilesets()
{
    return &m_tilesets;
}

std::vector<Layer*>* Level::getLayers()
{
    return &m_layers;
}

std::vector<Layer*>* Level::getCollisionLayers()
{
    return &m_collisionLayer;
}
