#include "Application.hpp"

#include <chrono>
#include <memory>
#include <vector>

#include "force_provider.hpp"
#include "force_providers.hpp"

using namespace std::chrono;

constexpr const int width = 320;
constexpr const int height = 240;
constexpr const auto simulation_time_step = 16ms;

application::application()
	: m_window(sf::VideoMode(width, height), "Sketch")
  , m_world(width, height) {
}

application::~application() {}

void application::run() {
	// Create initial set of balls
	std::vector<std::shared_ptr<ball>> balls;
	balls.push_back(std::make_shared<ball>(13.0f, 13.0f, 10.0f));
	balls.push_back(std::make_shared<ball>(45.0f, 13.0f, 5.0f));

	// Add balls to the world
	for (const auto& ball : balls) {
		m_world.add_ball(ball);
	}

	// Add forces to the world
	auto gravity = std::make_shared<gravity_force>(true);
	m_world.add_force_provider(gravity);
	auto wind = std::make_shared<wind_force>();
	m_world.add_force_provider(wind);
	auto friction = std::make_shared<friction_force>(true);
	m_world.add_force_provider(friction);
	auto attractor = std::make_shared<point_attractor_force>();
	m_world.add_force_provider(attractor);

	std::chrono::high_resolution_clock timer;
	auto last_time = timer.now();
	auto accumulated_time = 0ns;
	while (m_window.isOpen()) {
		sf::Event ev;
		while (m_window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) {
				m_window.close();
			}
			if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left) {
				auto mouse_position = sf::Mouse::getPosition(m_window);
				auto b = std::make_shared<ball>(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y), static_cast<float>((rand() + 1) % 20));
				balls.push_back(b);
				m_world.add_ball(b);
			}
			if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Right) {
				attractor->is_active() = true;
			}
			if (ev.type == sf::Event::MouseButtonReleased && ev.mouseButton.button == sf::Mouse::Right) {
				attractor->is_active() = false;
			}
			if (ev.type == sf::Event::MouseMoved) {
				auto mouse_position = sf::Mouse::getPosition(m_window);
				attractor->point().x = mouse_position.x;
				attractor->point().y = mouse_position.y;
			}
			if (ev.type == sf::Event::KeyPressed) {
				if (ev.key.code == sf::Keyboard::G) {
					gravity->is_active() = !gravity->is_active();
				}
				if (ev.key.code == sf::Keyboard::W) {
					wind->is_active() = !wind->is_active();
				}
				if (ev.key.code == sf::Keyboard::F) {
					friction->is_active() = !friction->is_active();
				}
			}
		}

		auto now = timer.now();
		auto elapsed = duration_cast<nanoseconds>(now - last_time);
		last_time = now;

		accumulated_time += elapsed;
		while (accumulated_time >= simulation_time_step) {
			m_world.update(duration_cast<duration<float>>(simulation_time_step).count());
			accumulated_time -= simulation_time_step;
		}

		m_window.clear();

		for (const auto& ball : balls) {
			m_window.draw(*ball);
		}

		m_window.display();
	}
}
