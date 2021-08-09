#ifndef __GAME_OBJECT_FACTORY__
#define __GAME_OBJECT_FACTORY__

#include <string>
#include "GameObject.h"
#include <map>

class BaseCreator
{
public:
	virtual GameObject* createGameObject() const = 0;
	virtual ~BaseCreator() {}
};

class GameObjectFactory
{
public:

	virtual ~GameObjectFactory();

	static GameObjectFactory& Instance()
	{
		static GameObjectFactory instance;
		return  instance;
	}

	bool registerType(std::string typeID, BaseCreator* pCreator);
	GameObject* create(std::string typeID);

private:
	GameObjectFactory() = default;

	std::map<std::string, BaseCreator*> m_creators;

};

#endif // !__GAME_OBJECT_FACTORY__