#pragma once

#include "graphics/objects/camera.h"
#include "graphics/objects/shader.h"
#include "graphics/objects/vao.h"


class Game {
public :

	Game(int w, int h);
	~Game();

	void update();
	void render();

	bool getInitState() const;

private :

	bool m_initState;

	Camera m_camera;
	VAO m_vao;
	Shader m_shader;

};
