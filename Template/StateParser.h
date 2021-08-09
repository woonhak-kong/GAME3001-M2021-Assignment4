#ifndef __STATEPARSER__
#define __STATEPARSER__

#include <string>
#include <vector>
#include "GameObject.h"
#include "tinyxml.h"

class StateParser
{
public:
	StateParser();
	~StateParser();

	bool ParseState(const char* stateFile, std::string stateID);


private:

	void ParseTextures(TiXmlElement* pStateRoot);
	void ParseSounds(TiXmlElement* pStateRoot);

};




#endif // !__STATEPARSER__
