#ifndef __LAVELPARSER__
#define __LAVELPARSER__

#include "tinyxml.h"
#include <vector>
#include "Layer.h"
#include "Level.h"

class LevelParser
{
public:
	Level* ParseLevel(const char* levelFile, Scene* scene);

	void parseTextures(TiXmlElement* pTextureRoot);

	void parseObjectLayer(TiXmlElement* pObjectElement, Scene* scene);


private:
	void parseTilesets(TiXmlElement* pTilesetRoot, std::vector<Tileset>* pTilesets);
	void parseTileLayer(TiXmlElement* pTileElement, std::vector<Layer*>* pLayers, const std::vector<Tileset>* pTilesets, std::vector<Layer*>* pCollisionLayers, Scene* scene);
	void csvDataToVector(std::string orgText, std::vector<int>& vector);
	int m_tileSize;
	int m_width;
	int m_height;

	const std::string MAP_ROOT = "assets/maps/";


};
#endif // !__LAVELPARSER__