#pragma once
#ifndef __NODE_STATUS__
#define __NODE_STATUS__
enum class NodeStatus
{
	UNVISITED,
	OPEN,
	CLOSED,
	IMPASSABLE,
	GOAL,
	START,
	PATH
};
#endif // __NODE_STATUS__