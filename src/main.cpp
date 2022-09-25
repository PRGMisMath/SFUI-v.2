#include<SFML/Graphics.hpp>
#include "GUIHanler.hpp"
#include "GButton.hpp"
#include "GSlider.hpp"

void expand(GWidget* actionThrower) {
	actionThrower->setSize({ .9f * actionThrower->getSize().x,1.11f * actionThrower->getSize().y });
}

int main() {
	sf::RenderWindow wndw{ sf::VideoMode({800,300}), "Test" };
	GUIHandler gui{};
	GButton button{&gui, "Press"};
	button.setPosition({ 50.f, 50.f });
	button.onClick(new GWidgetAction(expand, &button));
	GSlider slider{ &gui };
	slider.setPosition({ 50.f, 200.f });

	while (wndw.isOpen()) {
		sf::Event event;
		while (wndw.pollEvent(event))
		{
			gui.listen(event);
			switch (event.type) {
			case sf::Event::Closed:
				wndw.close();
				break;
			default:
				break;
			}
		}
		wndw.clear(sf::Color::White);
		wndw.draw(gui);
		wndw.display();
	}
}