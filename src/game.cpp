#include "game.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "maths/quaternion.h"



Game::Game(int w, int h) : m_initState(false), m_camera(glm::vec3(0,6,0), Quaternion(glm::vec3(0,0,1), -3.1415/2), w,h),
m_shader("GameData/shaders/shader.vert", "GameData/shaders/shader.frag", {{0, "in_Vertex"}}) {
	m_initState = true;

	float vertices[] = {
		-1,0,-1,
		1, 0, 1,
		1, 0,-1,
		-1,0,-1,
		-1,0, 1,
		1, 0, 1,
	};
	int sizes[] = {3};
	void *data[] = {vertices};
	int ids[] = {0};
	int types[] = {GL_FLOAT};
	m_vao.pushData(data, sizes, ids, types, 6, 1);

}

Game::~Game() {}



void Game::update() {
	//m_camera.rotation(Quaternion(glm::vec3(1,0,0), 0.005));
	//m_camera.translate(glm::vec3(0.0,0,0.004));
}

void Game::render() {

	m_shader.glUse();
		m_vao.glBind();

			glUniformMatrix4fv(
				m_shader.getUniformLocation("projection"), 1, GL_FALSE, 
				glm::value_ptr(m_camera.getProjection())
			);

			glUniformMatrix4fv(
				m_shader.getUniformLocation("modelview"), 1, GL_FALSE, 
				glm::value_ptr(m_camera.getModelView())
			);

			glDrawArrays(GL_TRIANGLES, 0, m_vao.getSize());

		m_vao.glUnbind();
	m_shader.glUnuse();

}



bool Game::getInitState() const {
	return m_initState;
}
