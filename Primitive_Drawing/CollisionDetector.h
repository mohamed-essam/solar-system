#pragma once
#include"Shape.h"

class CollisionDetector
{
public:
	static void colliderPosition( Shape** shapes,  int shapesCount,const vec3& oldPosition, vec3& newPosition);
};

