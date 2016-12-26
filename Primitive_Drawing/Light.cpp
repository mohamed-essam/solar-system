#include "Light.h"


Light::Light(GLuint ambientColorId, GLuint lightColorId, GLuint lightPositionID, glm::vec3 ambientColor, glm::vec3 lightColor, glm::vec3 lightPosition)
{
	applyLight( ambientColorId,  lightColorId,  lightPositionID, ambientColor, lightColor, lightPosition);
}

void Light::applyLight(GLuint ambientLightColorID, GLuint lightColorID, GLuint lightPositionID, glm::vec3 ambientColor, glm::vec3 lightColor, glm::vec3 lightPosition)
{
	glUniform3f(lightColorID, lightColor.x, lightColor.y, lightColor.z);
	glUniform3f(lightPositionID, lightPosition.x, lightPosition.y, lightPosition.z);
	glUniform3f(ambientLightColorID, ambientColor.x, ambientColor.y, ambientColor.z);

}
Light::~Light()
{
}
