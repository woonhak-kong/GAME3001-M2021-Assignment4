#include "StateParser.h"
#include <iostream>
#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include "SoundManager.h"
#include "TextureID.h"

StateParser::StateParser()
{
}

StateParser::~StateParser()
{
}

bool StateParser::ParseState(const char* stateFile, std::string stateID)
{
    // create the XML document
    TiXmlDocument xmlDoc;
    // load the state file
    if (!xmlDoc.LoadFile(stateFile))
    {
        std::cerr << xmlDoc.ErrorDesc() << "\n";
        return false;
    }

    // get the root element
    TiXmlElement* pRoot = xmlDoc.RootElement();

    // pre declare the states root node
    TiXmlElement* pStateRoot = 0;

    // get this states root node and assign it to pStateRoot
    for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == stateID)
        {
            pStateRoot = e;
        }
    }

    // pre declare the texture root
    TiXmlElement* pTextureRoot = nullptr;

    // get the root of the texture elements
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("TEXTURES"))
        {
            pTextureRoot = e;
        }
    }
    // now parse the textures
    if (pTextureRoot != nullptr)
    {
        ParseTextures(pTextureRoot);
    }

	// sounds
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        if (e->Value() == std::string("SOUNDS"))
        {
            pTextureRoot = e;
        }
    }
    if (pTextureRoot != nullptr)
    {
        ParseSounds(pTextureRoot);
    }

    return true;
}

void StateParser::ParseTextures(TiXmlElement* pStateRoot)
{
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        bool tmp;
        std::string filenameAttribute = e->Attribute("filename");
        std::string idAttribute = e->Attribute("ID");
        TextureManager::Instance().load(filenameAttribute, idAttribute);
        std::cout << idAttribute << std::endl;
    	if (idAttribute == TextureID::ENEMY_HUMAN)
    	{
            Animation animation = Animation();
            Frame frame;
            const glm::vec2 size(64, 48);
            int startCul = 0;
            int startRow = 0;

            animation.name = TextureID::ENEMY_HUMAN_IDLE;
            startCul = 0;
            startRow = 1;
            for (int i = 0; i < 2; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * (startCul + i);
                frame.y = size.y * startRow;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(idAttribute, animation);
            animation.frames.clear();


            animation.name = TextureID::ENEMY_HUMAN_ATTACK;
            startCul = 0;
            startRow = 3;
            for (int i = 0; i < 4; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * (startCul + i);
                frame.y = size.y * startRow;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(idAttribute, animation);
            animation.frames.clear();

            animation.name = TextureID::ENEMY_HUMAN_FALL;
            startCul = 0;
            startRow = 0;
            for (int i = 0; i < 1; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * (startCul + i);
                frame.y = size.y * startRow;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(idAttribute, animation);
            animation.frames.clear();

            animation.name = TextureID::ENEMY_HUMAN_JUMP;
            startCul = 2;
            startRow = 0;
            for (int i = 0; i < 1; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * (startCul + i);
                frame.y = size.y * startRow;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(idAttribute, animation);
            animation.frames.clear();

            animation.name = TextureID::ENEMY_HUMAN_HIT;
            startCul = 5;
            startRow = 3;
            for (int i = 0; i < 4; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * (startCul + i);
                frame.y = size.y * startRow;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(idAttribute, animation);
            animation.frames.clear();

            animation.name = TextureID::ENEMY_HUMAN_DEAD;
            startCul = 5;
            startRow = 3;
            for (int i = 0; i < 4; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * (startCul + i);
                frame.y = size.y * startRow;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(idAttribute, animation);
            animation.frames.clear();

            animation.name = TextureID::ENEMY_HUMAN_RUN;
            startCul = 0;
            startRow = 2;
            for (int i = 0; i < 4; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * (startCul + i);
                frame.y = size.y * startRow;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(idAttribute, animation);
            animation.frames.clear();
    	}
        else if (idAttribute == TextureID::EXPLOSION1)
        {
            Animation animation = Animation();
            Frame frame;
            const glm::vec2 size(100, 100);
            int total = 0;

            animation.name = TextureID::EXPLOSION1;

            for (int i = 0; i < 8; ++i)
            {
            	for(int j = 0; j < 10; ++j)
            	{
                    frame.name = idAttribute;
                    frame.x = size.x * j;
                    frame.y = size.y * i;
                    frame.w = size.x;
                    frame.h = size.y;
                    animation.frames.push_back(frame);
                    if (total >= 70)
                        break;
                    total++;
            	}

            }
            TextureManager::Instance().setAnimation(idAttribute, animation);
            animation.frames.clear();
        }
        else if (idAttribute == TextureID::EXPLOSION2)
        {
	        Animation animation = Animation();
	        Frame frame;
	        const glm::vec2 size(100, 100);
	        int total = 0;

	        animation.name = TextureID::EXPLOSION2;

	        for (int i = 0; i < 7; ++i)
	        {
	            for (int j = 0; j < 10; ++j)
	            {
	                frame.name = idAttribute;
	                frame.x = size.x * j;
	                frame.y = size.y * i;
	                frame.w = size.x;
	                frame.h = size.y;
	                animation.frames.push_back(frame);
	                if (total >= 63)
	                    break;
	                total++;
	            }

	        }
	        TextureManager::Instance().setAnimation(idAttribute, animation);
	        animation.frames.clear();
        }
        else if (idAttribute == TextureID::BOSS1_ATTACK1)
        {
            Animation animation = Animation();
            Frame frame;
            const glm::vec2 size(250, 250);

            animation.name = TextureID::BOSS1_ATTACK1;

            for (int i = 0; i < 8; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * i;
                frame.y = 0;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(TextureID::BOSS1, animation);
            animation.frames.clear();
        }
        else if (idAttribute == TextureID::BOSS1_ATTACK2)
        {
            Animation animation = Animation();
            Frame frame;
            const glm::vec2 size(250, 250);

            animation.name = TextureID::BOSS1_ATTACK2;

            for (int i = 0; i < 8; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * i;
                frame.y = 0;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(TextureID::BOSS1, animation);
            animation.frames.clear();
        }
        else if (idAttribute == TextureID::BOSS1_DEAD)
        {
            Animation animation = Animation();
            Frame frame;
            const glm::vec2 size(250, 250);

            animation.name = TextureID::BOSS1_DEAD;

            for (int i = 0; i < 7; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * i;
                frame.y = 0;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(TextureID::BOSS1, animation);
            animation.frames.clear();
        }
        else if (idAttribute == TextureID::BOSS1_FALL)
        {
            Animation animation = Animation();
            Frame frame;
            const glm::vec2 size(250, 250);

            animation.name = TextureID::BOSS1_FALL;

            for (int i = 0; i < 2; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * i;
                frame.y = 0;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(TextureID::BOSS1, animation);
            animation.frames.clear();
        }
        else if (idAttribute == TextureID::BOSS1_IDLE)
        {

            Animation animation = Animation();
            Frame frame;
            const glm::vec2 size(250, 250);

            animation.name = TextureID::BOSS1_IDLE;

            for (int i = 0; i < 8; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * i;
                frame.y = 0;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(TextureID::BOSS1, animation);
            animation.frames.clear();
        }
        else if (idAttribute == TextureID::BOSS1_JUMP)
        {
            Animation animation = Animation();
            Frame frame;
            const glm::vec2 size(250, 250);

            animation.name = TextureID::BOSS1_JUMP;

            for (int i = 0; i < 2; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * i;
                frame.y = 0;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(TextureID::BOSS1, animation);
            animation.frames.clear();
        }
        else if (idAttribute == TextureID::BOSS1_RUN)
        {
            Animation animation = Animation();
            Frame frame;
            const glm::vec2 size(250, 250);

            animation.name = TextureID::BOSS1_RUN;

            for (int i = 0; i < 8; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * i;
                frame.y = 0;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(TextureID::BOSS1, animation);
            animation.frames.clear();
        }
        else if (idAttribute == TextureID::BOSS1_HIT)
        {
            Animation animation = Animation();
            Frame frame;
            const glm::vec2 size(250, 250);

            animation.name = TextureID::BOSS1_HIT;

            for (int i = 0; i < 3; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * i;
                frame.y = 0;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(TextureID::BOSS1, animation);
            animation.frames.clear();
        }
        else if (idAttribute == TextureID::DOOR)
        {
            Animation animation = Animation();
            Frame frame;
            const glm::vec2 size(32, 32);

            animation.name = TextureID::DOOR;

            for (int i = 0; i < 5; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * i;
                frame.y = 0;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(idAttribute, animation);
            animation.frames.clear();
        }
        else if (idAttribute == TextureID::SLASH_DARK)
        {
        std::cout << "aaaa" << std::endl;
            Animation animation = Animation();
            Frame frame;
            const glm::vec2 size(106, 32);

            animation.name = TextureID::SLASH_DARK;

            for (int i = 0; i < 3; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * i;
                frame.y = 0;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(TextureID::ATTACK_BOX, animation);
            animation.frames.clear();
        }
        else if (idAttribute == TextureID::SLASH_FIRE)
        {
            Animation animation = Animation();
            Frame frame;
            const glm::vec2 size(64, 24);

            animation.name = TextureID::SLASH_FIRE;

            for (int i = 0; i < 10; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * i;
                frame.y = 0;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(TextureID::ATTACK_BOX, animation);
            animation.frames.clear();
        }
        else if (idAttribute == TextureID::SLASH_LASER)
        {
            Animation animation = Animation();
            Frame frame;
            const glm::vec2 size(256, 256);

            animation.name = TextureID::SLASH_LASER;

            for (int i = 0; i < 7; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * i;
                frame.y = 0;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(TextureID::ATTACK_BOX, animation);
            animation.frames.clear();
        }
        else if (idAttribute == TextureID::SLASH_BASIC)
        {
            Animation animation = Animation();
            Frame frame;
            const glm::vec2 size(512, 432);

            animation.name = TextureID::SLASH_BASIC;

            for (int i = 0; i < 4; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * i;
                frame.y = 0;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(TextureID::ATTACK_BOX, animation);
            animation.frames.clear();
        }
        else if (idAttribute == TextureID::HIT_PARTICLE)
        {
            Animation animation = Animation();
            Frame frame;
            const glm::vec2 size(32, 32);

            animation.name = TextureID::HIT_PARTICLE;

            for (int i = 0; i < 3; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * i;
                frame.y = 0;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(idAttribute, animation);
            animation.frames.clear();
        }
        else if (idAttribute == TextureID::TRINKLE)
        {
            Animation animation = Animation();
            Frame frame;
            const glm::vec2 size(32, 32);

            animation.name = TextureID::TRINKLE;

            for (int i = 0; i < 4; ++i)
            {
                frame.name = idAttribute;
                frame.x = size.x * i;
                frame.y = 0;
                frame.w = size.x;
                frame.h = size.y;
                animation.frames.push_back(frame);
            }
            TextureManager::Instance().setAnimation(idAttribute, animation);
            animation.frames.clear();
        }

    }
}

void StateParser::ParseSounds(TiXmlElement* pStateRoot)
{
    for (TiXmlElement* e = pStateRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement())
    {
        std::string filenameAttribute = e->Attribute("filename");
        std::string idAttribute = e->Attribute("ID");
        std::string soundTypeString = e->Attribute("soundtype");
        const SoundType soundType = soundTypeString == "bgm" ? SoundType::SOUND_MUSIC : SoundType::SOUND_SFX;

        SoundManager::Instance().load(filenameAttribute, idAttribute, soundType);
    }
}
