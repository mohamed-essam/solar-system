#include "CollisionDetector.h"
#include<windows.h>

void CollisionDetector::colliderPosition( Shape ** shapes,int shapesCount, const vec3 & oldPosition, vec3 & newPosition)
{
	for (int i = 0; i < shapesCount; i++)//collision detection
	{
		double radius = shapes[i]->getScale().x;
		vec4 center = shapes[i]->getModelMatrix() * vec4(0.0f, 0.0f, 0.0f, 1.0f);
		vec4 temporary = vec4(newPosition, center.w) - center;
		
		if (!shapes[i]->isSkyBox() && length(temporary) < radius + 0.5f)
		{
			mciSendString("play crash from 0", 0, 0, 0);
			temporary = normalize(temporary);
			temporary *= (radius + 0.75f);
			temporary += center;
			newPosition.x = temporary.x;
			newPosition.y = temporary.y;
			newPosition.z = temporary.z;
			
		}
		else if (shapes[i]->isSkyBox() && length(temporary) > radius - 0.5f)
		{
			mciSendString("play crash from 0", 0, 0, 0);
			temporary = normalize(temporary);
			temporary *= (radius - 0.75f);
			temporary += center;
			newPosition.x = temporary.x;
			newPosition.y = temporary.y;
			newPosition.z = temporary.z;
		}
	}
}
