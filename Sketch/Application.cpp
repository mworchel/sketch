#include "Application.hpp"

#include <chrono>
#include <memory>
#include <vector>

#include "force_provider.hpp"
#include "force_providers.hpp"

using namespace std::chrono;

const int width = 320;
const int height = 240;

constexpr const auto simulation_time_step = 16ms;

application::application()
	: _window(sf::VideoMode(width, height), "MyApp") {
	_world = std::make_unique<world>(width, height);
}

application::~application() {}

void application::run() {
	// Create balls
	std::vector<std::shared_ptr<ball>> balls;
	balls.push_back(std::make_shared<ball>(13.0f, 13.0f, 10.0f));
	balls.push_back(std::make_shared<ball>(45.0f, 13.0f, 5.0f));

	// Add balls to the world
	for (const auto& ball : balls) {
		_world->add_ball(ball);
	}

	// Add a gravity force to the world
	auto gravity = std::make_shared<gravity_force>(true);
	_world->add_force_provider(gravity);
	auto wind = std::make_shared<wind_force>();
	_world->add_force_provider(wind);
	auto friction = std::make_shared<friction_force>(true);
	_world->add_force_provider(friction);
	auto attractor = std::make_shared<point_attractor_force>();
	_world->add_force_provider(attractor);

	std::chrono::high_resolution_clock timer;
	auto last_time = timer.now();
	auto accumulated_time = 0ns;
	while (_window.isOpen()) {
		sf::Event ev;
		while (_window.pollEvent(ev)) {
			if (ev.type == sf::Event::Closed) {
				_window.close();
			}
			if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Left) {
				auto mouse_position = sf::Mouse::getPosition(_window);
				auto b = std::make_shared<ball>(static_cast<float>(mouse_position.x), static_cast<float>(mouse_position.y), static_cast<float>((rand() + 1) % 20));
				balls.push_back(b);
				_world->add_ball(b);
			}
			if (ev.type == sf::Event::MouseButtonPressed && ev.mouseButton.button == sf::Mouse::Right) {
				attractor->is_active() = true;
			}
			if (ev.type == sf::Event::MouseButtonReleased && ev.mouseButton.button == sf::Mouse::Right) {
				attractor->is_active() = false;
			}
			if (ev.type == sf::Event::MouseMoved) {
				auto mouse_position = sf::Mouse::getPosition(_window);
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
			_world->update(duration_cast<duration<float>>(simulation_time_step).count());
			accumulated_time -= simulation_time_step;
		}

		_window.clear();

		for (const auto& ball : balls) {
			_window.draw(*ball);
		}

		_window.display();
	}
}
