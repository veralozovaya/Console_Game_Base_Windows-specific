#include "ExampleGame.h"

void Bullet::render(PaintDevice& paintDevice) {
	paintDevice.set_char(m_Position, '|');
}

void Bullet::update(const int dt) {
	m_Lag += dt;
	const int quant = 50;
	if (m_Lag <= quant) return;
	m_Lag -= quant;
	m_Position.y()--;
}

Gun::Gun() {
	m_Body = {
		Vector2(5, 0),
		Vector2(5, 1),

		Vector2(4, 2),
		Vector2(4, 3),
		Vector2(4, 4),
		Vector2(6, 2),
		Vector2(6, 3),
		Vector2(6, 4),

		Vector2(3, 5),
		Vector2(7, 5),

		Vector2(2, 6),
		Vector2(5, 6),
		Vector2(8, 6),

		Vector2(1, 7),
		Vector2(5, 7),
		Vector2(9, 7),

		Vector2(0, 8),
		Vector2(1, 8),
		Vector2(2, 8),
		Vector2(8, 8),
		Vector2(9, 8),
		Vector2(10, 8),

		Vector2(3, 9),
		Vector2(7, 9),
		Vector2(3, 10),
		Vector2(7, 10),

		Vector2(4, 11),
		Vector2(6, 11),
		Vector2(4, 12),
		Vector2(5, 12),
		Vector2(6, 12),
	};
}

std::vector<Bullet> Gun::fire() {
	std::vector<Bullet> bulets;
	if (m_CooldownCenter == 0)
	{
		bulets.push_back(Bullet());
		bulets.back().m_Position = Vector2(m_Position.x() + 4, m_Position.y() + 1);

		bulets.push_back(Bullet());
		bulets.back().m_Position = Vector2(m_Position.x() + 6, m_Position.y() + 1);
		m_CooldownCenter = 300;
	}

	if (m_CooldownSide == 0)
	{
		bulets.push_back(Bullet());
		bulets.back().m_Position = Vector2(m_Position.x(), m_Position.y() + 7);
		bulets.push_back(Bullet());
		bulets.back().m_Position = Vector2(m_Position.x() + 10, m_Position.y() + 7);
		m_CooldownSide = 150;
	}

	return bulets;
}

void Gun::update(const int dt) {
	m_CooldownCenter -= dt;
	m_CooldownSide -= dt;
	if (m_CooldownCenter < 0) m_CooldownCenter = 0;
	if (m_CooldownSide < 0) m_CooldownSide = 0;

}

void Gun::render(PaintDevice& paintDevice) {
	for (const Vector2& point : m_Body) {
		paintDevice.set_char(Vector2(m_Position.x() + point.x(), m_Position.y() + point.y()), 0x2588);
	}
}

void Enemy::render(PaintDevice& paintDevice) {
	for (const Vector2& point : m_Enemys) {
		paintDevice.set_char(point, 0x25BC);
	}
}

void Enemy::update(const int dt) {
	m_Lag += dt;
	const int quant = 800;
	if (m_Lag <= quant) return;
	m_Lag -= quant;

	for (Vector2& point : m_Enemys) {
		point.y()++;
	}

	for (int i = 0; i < 20; ++i) {
		if (rand() % 2) {
			m_Enemys.push_back(Vector2(i, 0));
		}
	}
}

bool Enemy::hit(Vector2 point) {
	
	for (const Vector2& enemy : m_Enemys) {
		if (enemy == point) {
			return true;
		}
	}

	return false;
}

void Enemy::remove(Vector2 point) {
	for (int i = 0; i < m_Enemys.size(); ++i) {
		if (point.x() == m_Enemys[i].x() && point.y() == m_Enemys[i].y()) {
			for (int j = i; j < m_Enemys.size() - 1; ++j) {
				m_Enemys[j] = m_Enemys[j + 1];
			}
			m_Enemys.pop_back();
			return;
		}
	}
}

ExampleGame::ExampleGame() {
	paint_device().resize(Size(m_Width, m_Height));
	track_key(VK_LEFT);
	track_key(VK_RIGHT);

	m_Gun.m_Position = Vector2(m_Width / 2 - 2, m_Height - 14);
}

void ExampleGame::on_button_press(const int button) {
	switch (button)
	{
	case VK_LEFT:
	{
		m_Gun.m_Position.x()--;
		if (m_Gun.m_Position.x() < 0) m_Gun.m_Position.x() = 0;
		break;
	}

	case VK_RIGHT:
	{
		m_Gun.m_Position.x()++;
		if (m_Gun.m_Position.x() > m_Width - 11) m_Gun.m_Position.x() = m_Width - 11;
		break;
	}

	default:
		break;
	}
}

void ExampleGame::update(const int dt) {
	m_Enemy.update(dt);

	for (int i = 0; i < m_Bullets.size(); i++) {
		m_Bullets[i].update(dt);
	}
	
	for (int i = 0; i < m_Bullets.size(); i++) {
		if (m_Bullets[i].m_Position.y() < 0)
		{
			for (int j = i; j < m_Bullets.size() - 1; j++) {
				m_Bullets[j] = m_Bullets[j + 1];
			}
			m_Bullets.pop_back();
		}
	}

	for (int i = 0; i < m_Bullets.size(); i++) {
		if (m_Enemy.hit(m_Bullets[i].m_Position)) {
			m_Enemy.remove(m_Bullets[i].m_Position);

			for (int j = i; j < m_Bullets.size() - 1; ++j) {
				m_Bullets[j] = m_Bullets[j + 1];
			}
			m_Bullets.pop_back();
		}
	}

	m_Gun.update(dt);

	std::vector<Bullet> newBullets = m_Gun.fire();
	m_Bullets.insert(m_Bullets.end(), newBullets.begin(), newBullets.end());
}

void ExampleGame::render(PaintDevice& paintDevice) {
	for (Bullet& bullet : m_Bullets) {
		bullet.render(paintDevice);
	}

	m_Enemy.render(paintDevice);

	m_Gun.render(paintDevice);

}
