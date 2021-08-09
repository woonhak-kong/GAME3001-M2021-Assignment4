#include "TileLayer.h"

#include "Camera.h"
#include "Game.h"
#include "TextureManager.h"
#include "Config.h"

TileLayer::~TileLayer()
{
}

//TileLayer::TileLayer(int tileSize, const std::vector<Tileset>& tilesets, int row, int column) :
//	m_tileSize(tileSize),
//	m_tilesets(tilesets),
//	m_numColumns(column),
//	m_numRows(row),
//	m_position(0, 0),
//	m_velocity(0, 0)
//{
//	m_numColumns = (Config::SCREEN_WIDTH / m_tileSize);
//	m_numRows = (Config::SCREEN_HEIGHT / m_tileSize);
//}

TileLayer::TileLayer(int tileSize, int mapWidth, int mapHeight, const std::vector<Tileset>& tilesets):
	m_tileSize(tileSize),
	m_tilesets(tilesets),
	m_numColumns(0),
	m_numRows(0),
	m_position(0, 0),
	m_velocity(0, 0)
{
	m_numColumns = mapWidth;
	m_numRows = mapHeight;
	m_mapWidth = mapWidth;
	m_mapHeight = mapHeight;
}

void TileLayer::update()
{
	m_position += m_velocity;
	//m_velocity.x = 1;
}

void TileLayer::draw()
{
	int x, y, x2, y2 = 0;
	glm::vec2 cameraPosition = Camera::Instance().getPosition();
	
	x = m_position.x / m_tileSize;
	y = m_position.y / m_tileSize;
	x2 = int(m_position.x) % m_tileSize;
	y2 = int(m_position.y) % m_tileSize;
	//std::cout << "x = " << x << "   x2 = " << x2 << std::endl;
	for (int i = 0; i < m_numRows; i++)
	{
		for (int j = 0; j < m_numColumns; j++)
		{
			int id = 0;
			int row = i + y;
			int column = j + x;
			if (row < m_tileIDs.size() && column < m_tileIDs[row].size())
			{
				id = m_tileIDs[row][column];
			}
			else
			{
				id = 0;
			}
			// if outside the viewable area then skip the tile
			if (((j * m_tileSize) - x2) - cameraPosition.x < -m_tileSize ||
				((j * m_tileSize) - x2) - cameraPosition.x > Config::SCREEN_WIDTH ||
				((i * m_tileSize) - y2) - cameraPosition.y < -m_tileSize ||
				((i * m_tileSize) - y2) - cameraPosition.y > Config::SCREEN_HEIGHT)
			{
				continue;
			}

			if (id == 0)
			{
				continue;
			}
			Tileset tileset = getTilesetByID(id);
			id--;
			//TextureManager::Instance().drawTile(tileset.name, tileset.margin, tileset.spacing, (j * m_tileSize) - x2, (i * m_tileSize) - y2, m_tileSize,
			//	m_tileSize, (id - (tileset.firstGridID - 1)) / tileset.numColumns, (id - (tileset.firstGridID - 1)) % tileset.numColumns);
			// draw the tile into position while offsetting its x position by
				// subtracting the camera position
			TextureManager::Instance().drawTile(tileset.name,tileset.margin, tileset.spacing, ((j * m_tileSize) - x2) - cameraPosition.x, ((i * m_tileSize) - y2) - cameraPosition.y,
				m_tileSize, m_tileSize, (id - (tileset.firstGridID -1)) / tileset.numColumns, (id - (tileset.firstGridID - 1)) % tileset.numColumns);
		}
		//std::cout << SDL_GetError();
	}
}

void TileLayer::clean()
{
}

void TileLayer::setTileIDs(const std::vector<std::vector<int>>& data)
{
	m_tileIDs = data;
}

void TileLayer::setTileSize(int tileSize)
{
	m_tileSize = tileSize;
}

int TileLayer::getTileSize() const
{
	return m_tileSize;
}

glm::vec2 TileLayer::getPosition() const
{
	return m_position;
}

Tileset TileLayer::getTilesetByID(int tileID)
{
	for (int i = 0; i < m_tilesets.size(); i++)
	{
		if (i + 1 <= m_tilesets.size() - 1)
		{
			if (tileID >= m_tilesets[i].firstGridID && tileID < m_tilesets[i +
				1].firstGridID)
			{
				return m_tilesets[i];
			}
		}
		else
		{
			return m_tilesets[i];
		}
	}
	std::cout << "did not find tileset, returning empty tileset\n";
	Tileset t;
	return t;
}

std::vector<std::vector<int>>& TileLayer::getTileIDs()
{
	return m_tileIDs;
}
