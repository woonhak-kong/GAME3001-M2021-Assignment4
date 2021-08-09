#ifndef __LAYER__
#define __LAYER__
#include "DisplayObject.h"

class Layer : public DisplayObject
{
public:
	virtual void draw() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	virtual ~Layer() = default;
};


#endif // !__LAYER__

