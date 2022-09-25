#ifndef G_PANEL_HPP
#define G_PANEL_HPP

#include "GWidget.hpp"
#include "GWidgetAppear.hpp"

class GPanel : public GContainer, public GWidget {
private:
	sf::FloatRect m_abs_view;
	sf::View m_panel_view;
};

#endif // !G_PANEL_HPP
