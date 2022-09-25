#ifndef G_WIDGET_APPEAR_HPP
#define G_WIDGET_APPEAR_HPP

#include<SFML/Graphics.hpp>
#include "GWidget.hpp"
#include "GSystem.hpp"

class GWidgetAppear : public sf::Drawable {
public:
	virtual bool withinWidgetBox(const sf::Vector2f& relPos) const = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
private:
	virtual void on_link_with_widget(const GSystem* system) = 0;

	virtual void update_size(const sf::Vector2f& size) = 0;
	virtual void update_hover(bool hover) = 0;
	virtual void update_clicked(bool clicked) = 0;


	friend class GWidget;
};

#endif // !WIDGET_APPEAR_HPP
