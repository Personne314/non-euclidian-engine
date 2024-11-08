#include "game.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "maths/quaternion.h"



Game::Game(SDL_Window *window, int w, int h) : m_initState(false), 
m_camera(glm::vec3(0,6,0), glm::vec3(0,0,0), w,h),
m_shader("GameData/shaders/shader.vert", "GameData/shaders/shader.frag", {{0, "in_coord"}}), 
post_process("GameData/shaders/post_outline.vert", "GameData/shaders/post_outline.frag", {{0, "in_coord"}, {1, "in_tex_coord"}}), 
m_renderer(window, w,h) {
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
	m_camera.rotation(Quaternion(glm::vec3(0,1,0), 0.005));
	//m_camera.translate(glm::vec3(0.0,0.1,0));
}

void Game::render() {

	m_renderer.glBind();
	m_renderer.clear();

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

	m_renderer.glUnbind();


	m_renderer.postProcess(post_process);


	m_renderer.glSwapWindow();

}



bool Game::getInitState() const {
	return m_initState;
}
