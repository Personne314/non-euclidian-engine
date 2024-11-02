#pragma once



class EventManager {
public :

	EventManager();
	~EventManager();

	void pollEvents();

	bool isCloseRequested() const;

private :

	bool closeEvent;

};
