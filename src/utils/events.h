#pragma once



class EventManager {
public :

	EventManager();
	~EventManager();

	void pollEvents();

	void setMouseMode(bool relative);

	bool isCloseRequested() const;

private :

	bool m_closeEvent;

	bool m_relative;
	float m_dx;
	float m_dy;

	bool left;
	bool right;
	bool forward;
	bool backward;

};
