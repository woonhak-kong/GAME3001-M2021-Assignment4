#ifndef __LEVEL__
#define __LEVEL__

#include <string>
#include <vector>

#include "DisplayObject.h"
#include "Layer.h"

struct Tileset
{
	int firstGridID = 0;
	int tileWidth = 0;
	int tileHeight = 0;
	int spacing = 0;
	int margin = 0;
	int width = 0;
	int height = 0;
	int numColumns = 0;
	std::string name;
};

class Level : public DisplayObject
{
public:
	virtual ~Level();
	void update() override;
	void draw() override;

	void clean() override;

	std::vector<Tileset>* getTilesets();
	std::vector<Layer*>* getLayers();
	std::vector<Layer*>* getCollisionLayers();



private:
	friend class LevelParser;
	Level();


	std::vector<Tileset> m_tilesets;
	std::vector<Layer*> m_layers;
	std::vector<Layer*> m_collisionLayer;
};





#endif // !__LEVEL__