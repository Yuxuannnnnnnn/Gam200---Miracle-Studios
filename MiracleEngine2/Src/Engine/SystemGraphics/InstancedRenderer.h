#include <glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "QuadMesh.h"

// instanced renderer, which will be used for partical in 250

class InstancedRenderer
{
private:
	GLuint _instanceBufferID;
	glm::mat4* modelMatrices;
	QuadMesh _quadmesh;

	glm::mat4 _proj;  // projection matrix

public:
	InstancedRenderer(int windowWidth = 800, int windowHeight = 600);
	void Update();
};