#include "Engine.h"
#include <chrono>

Engine::ErrorCode Engine::run() {
	ErrorCode errorCode = ErrorCode::success;

	std::chrono::system_clock::time_point lastUpdate = std::chrono::system_clock::now();
	std::chrono::system_clock::duration lag(0);
	const std::chrono::system_clock::duration timeQuantum(std::chrono::milliseconds(15));

	while (!end()) {
		// Handle input
		//============================================
		uppdateInput();
		//============================================

		//Logic Update
		//============================================
		std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
		lag += now - lastUpdate;
		lastUpdate = now;
		while (lag >= timeQuantum) {
			lag -= timeQuantum;
			update(std::chrono::duration_cast<std::chrono::milliseconds>(timeQuantum).count());
		}
		//============================================

		// Render part
		//============================================
		if (!m_PaintDevice.ready())
		{
			errorCode = ErrorCode::paint_device_not_ready;
			break;
		}
		m_PaintDevice.clear();
		render(m_PaintDevice);
		m_PaintDevice.render();
		//============================================
	}

	return errorCode;
}

void Engine::uppdateInput() {
	for (const int& key : m_TrackedKeys) {
		const SHORT keyState = GetKeyState(key);
		const bool isDown = keyState & 0x8000;

		const std::set<int>::const_iterator keyItr = m_PressedKeys.find(key);
		if (isDown && keyItr == m_PressedKeys.end()) {
			m_PressedKeys.insert(key);
			on_button_press(key);
		}
		else if (!isDown && keyItr != m_PressedKeys.end()) {
			m_PressedKeys.erase(keyItr);
		}
	}
}

void Engine::track_key(const int key) {
	m_TrackedKeys.insert(key);
}

void Engine::untrack_key(const int key) {
	const std::set<int>::const_iterator keyItr = m_TrackedKeys.find(key);
	if (keyItr != m_TrackedKeys.end())
	{
		m_TrackedKeys.erase(keyItr);
	}
}
