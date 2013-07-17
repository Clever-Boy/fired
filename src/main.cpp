#include <SFML/Graphics.hpp>

int main() {
	// After take the settings from config file (resolution and fullscreen)
	sf::RenderWindow App(sf::VideoMode(1024, 600, 32), "Name get from define", sf::Style::Fullscreen);

	while(App.IsOpened()) {
		App.Clear();
		App.Display();
	}

	return EXIT_SUCCESS;
}
