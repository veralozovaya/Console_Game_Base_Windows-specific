#pragma once

#include "Engine.h"
#include <vector>

class Bullet {
public:
	void render(PaintDevice& paintDevice);
	void update(const int dt);

	Vector2 m_Position;
	int m_Lag = 0;
};

class Gun {
public:
	Gun();
	std::vector<Bullet> fire();
	void render(PaintDevice& paintDevice);
	void update(const int dt);

	Vector2 m_Position;
	std::vector<Vector2> m_Body;

	int m_CooldownCenter = 0;
	int m_CooldownSide = 0;
}; 

class Enemy {
public:
	void render(PaintDevice& paintDevice);
	void update(const int dt);
	int m_Lag = 0;
	bool hit(Vector2 point);
	void remove(Vector2 point);
	Vector2 first() const { return m_Enemys.front(); }
	bool empty() const { return m_Enemys.empty(); }
private:
	std::vector<Vector2> m_Enemys;
};

class ExampleGame : public Engine {
public:
	ExampleGame();
private:
	virtual bool end() const { return !m_Enemy.empty() && m_Enemy.first().y() >= m_Height; }
	virtual void on_button_press(const int button);
	virtual void update(const int dt);
	virtual void render(PaintDevice& paintDevice);

	const size_t m_Width = 20;
	const size_t m_Height = 40;
	Gun m_Gun;
	std::vector<Bullet> m_Bullets;
	Enemy m_Enemy;
};
