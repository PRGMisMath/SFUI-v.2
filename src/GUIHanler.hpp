#ifndef GUI_HANDLER_HPP
#define GUI_HANDLER_HPP

#include<SFML/Graphics.hpp>
#include<vector>
#include "GContainer.hpp"
#include "GWidget.hpp"
#include "GSystem.hpp"

class GWidget;

class GUIHandler : public GContainer, public sf::Drawable {
public:
	virtual GSystem& getSystem();
	void listen(sf::Event event);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	GSystem m_system;
};

#endif // !GUI_HANDLER_HPP
