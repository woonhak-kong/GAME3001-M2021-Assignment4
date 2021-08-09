#ifndef __TILELAYER__
#define __TILELAYER__

#include "Layer.h"
#include <vector>
#include "Level.h"
#include "glm/vec2.hpp"

class TileLayer : public Layer
{
public:
	virtual ~TileLayer();

	//TileLayer(int tileSize, const std::vector<Tileset>& tilesets, int row, int column);
	TileLayer(int tileSize, int mapWidth, int mapHeight, const std::vector<Tileset>& tilesets);
	virtual void update() override;
	virtual void draw() override;
	void clean() override;

	void setTileIDs(const std::vector<std::vector<int>>& data);
	void setTileSize(int tileSize);

	int getTileSize() const;

	glm::vec2 getPosition() const;
	Tileset getTilesetByID(int tileID);
	std::vector<std::vector<int>>& getTileIDs();
private:

	int m_numColumns;
	int m_numRows;
	int m_tileSize;
	int m_mapWidth;
	int m_mapHeight;

	glm::vec2 m_position;
	glm::vec2 m_velocity;

	const std::vector<Tileset>& m_tilesets;
	std::vector<std::vector<int>> m_tileIDs;


};



#endif // !__TILELAYER__