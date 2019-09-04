#include "graphicsystem.h"

void GraphicSystem::Init()
{

	//GAME_ENGINE::Init();
//
//
//	_proj = glm::ortho(-(float)windowWidth / 2, (float)windowWidth / 2, -(float)windowHeight / 2, (float)windowHeight / 2);
//
//	Player player(40.0f, { 0.0f, -200.0f }, { 0.0f, 0.0f }, 0.0f, { 1.0f, 0.0f,0.0f });
//	Enemy enemy(40.0f, { 100.0f, 0.0f }, { 0.0f, 0.0f }, 0.0f, { 0.0f, 1.0f,0.0f });
//	enemy._type = ENEMY;
//	engine->_objectlist.push_back(player);
//	engine->_objectlist.push_back(enemy);
//
//	Enemy enemy2(40.0f, { 100.0f, 200.0f }, { 0.0f, 0.0f }, 0.0f, { 0.0f, 1.0f,0.0f });
//	enemy2._type = ENEMY;
//	engine->_objectlist.push_back(enemy2);
//	Enemy enemy3(40.0f, { -100.0f, 0.0f }, { 0.0f, 0.0f }, 0.0f, { 0.0f, 1.0f,0.0f });
//	enemy3._type = ENEMY;
//	engine->_objectlist.push_back(enemy3);
//	Enemy enemy4(40.0f, { .0f, 220.0f }, { 0.0f, 0.0f }, 0.0f, { 0.0f, 1.0f,0.0f });
//	enemy4._type = ENEMY;
//	engine->_objectlist.push_back(enemy4);
//}
//
//void GraphicSystem::Update()
//{
//	GLfloat verts[] =
//	{
//		-0.5f,  0.5f,
//		-0.5f, -0.5f,
//		 0.5f,  -0.5f,
//
//		 0.5f,  0.5f,
//		 0.5f, -0.5f,
//		 -0.5f, 0.5f,
//	};
//
//	GLuint myBufferID;
//	 generate buffer
//	glGenBuffers(1, &myBufferID);
//	 tell opengl its array
//	glBindBuffer(GL_ARRAY_BUFFER, myBufferID);
//	 gl_element_array_buffer
//
//	glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
//
//	glEnableVertexAttribArray(0);
//
//	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, 0);
//
//	GLuint shader = CreateShader(vertexShader, fragmentShader);
//
//

}
void GraphicSystem::Update()
{
	//for (size_t i = 0; i < engine->_objectlist.size(); i++)
	//{
	//	if (engine->_objectlist[i]._type == ENEMY)
	//	{
	//		engine->_objectlist[i]._posCurr._x = engine->_objectlist[i]._posCurr._x + 300 * 0.016f;
	//		if (engine->_objectlist[i]._posCurr._x > 480)
	//			engine->_objectlist[i]._posCurr._x = -480;
	//	}

	//	if (engine->_objectlist[i]._type == BULLET)
	//	{
	//		engine->_objectlist[i]._posCurr._y = engine->_objectlist[i]._posCurr._y + 1.0f;
	//		for (size_t j = 0; j < engine->_objectlist.size(); j++)
	//		{
	//			if (engine->_objectlist[j]._type != ENEMY)
	//				continue;

	//			if (CollisionIntersection_RectRect(engine->_objectlist[i]._boundingbox, Vec2{}, engine->_objectlist[j]._boundingbox, Vec2{}))
	//			{
	//				engine->_objectlist.erase(std::begin(engine->_objectlist) + j);
	//			}
	//		}
	//	}



	//	engine->_objectlist[i]._boundingbox.min._x = (float)(engine->_objectlist[i]._posCurr._x - (0.5 * engine->_objectlist[i]._scale));
	//	engine->_objectlist[i]._boundingbox.min._y = (float)(engine->_objectlist[i]._posCurr._y - (0.5 * engine->_objectlist[i]._scale));
	//	//boundingRict_max = BOUNDING_RECT_SIZE * instance->scaie + instance->pos				  i
	//	engine->_objectlist[i]._boundingbox.max._x = (float)(engine->_objectlist[i]._posCurr._x + (0.5 * engine->_objectlist[i]._scale));
	//	engine->_objectlist[i]._boundingbox.max._y = (float)(engine->_objectlist[i]._posCurr._y + (0.5 * engine->_objectlist[i]._scale));

	//	glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(engine->_objectlist[i]._posCurr._x, engine->_objectlist[i]._posCurr._y, 0));
	//	glm::mat4 model = translate * glm::scale(glm::mat4(1.0f), glm::vec3(engine->_objectlist[i]._scale, engine->_objectlist[i]._scale, 1.0f));

	//	glm::mat4 mvp = _proj * model;

	//	int location = glGetUniformLocation(shader, "u_Color");
	//	glUniform4f(location, engine->_objectlist[i]._color._r, engine->_objectlist[i]._color._g, engine->_objectlist[i]._color._b, 1.0f);

	//	location = glGetUniformLocation(shader, "u_MVP");
	//	glUniformMatrix4fv(location, 1, GL_FALSE, &mvp[0][0]);

	//	glDrawArrays(GL_TRIANGLES, 0, 6);
	//}
}
void GraphicSystem::Exit()
{

}