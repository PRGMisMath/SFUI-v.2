#ifndef G_BUTTON_HPP
#define G_BUTTON_HPP

#include "GWidget.hpp"
#include "GWidgetAppear.hpp"
#include "GAction.hpp"

class GButton;
class GButtonAppear;
class DefButtonAppear;

class GButton : public GWidget {
public:
	GButton(GContainer* parent, const std::string& text = "");
	void onClick(GAction* clickAction);
	void click();
	const std::string& getText() const;
	void setText(const std::string& text);
	virtual void setWidgetAppear(GWidgetAppear* appear, bool isNew = false);
	virtual void listen(const sf::Event& event);
private:
	std::string m_text;
	GAction* m_on_click;
};

class GButtonAppear : public GWidgetAppear {
public:
private:
	virtual void update_text(const std::string& text) = 0;

	friend class GButton;
};

class DefButtonAppear : public GButtonAppear {
public:
	enum GraphicalStates {
		Normal = 0, Hover = 1, Clicked = 2,
		DeclineFromOne = -1
	};

	DefButtonAppear(const sf::Color& backgroundColor = sf::Color::Blue);

	const sf::Color& getBackgroundColor(GraphicalStates states) const;
	void setBackgroundColor(const sf::Color& color, GraphicalStates states);
	const sf::Color& getOutlineColor() const;
	void setOutlineColor(const sf::Color& color);
	const sf::Color& getTextColor() const;
	void setTextColor(const sf::Color& color);
	const sf::Color& getBorderColor() const;
	void setBorderColor(const sf::Color& color);
	float getBorderThickness() const;
	void setBorderThickness(float thickness);

	virtual bool withinWidgetBox(const sf::Vector2f& relPos) const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	virtual void update_size(const sf::Vector2f& size);
	virtual void update_text(const std::string& text);
	virtual void update_hover(bool hover);
	virtual void update_clicked(bool clicked);
	virtual void on_link_with_widget(const GSystem* system);

	void TextPosUpdatE();
private:
	sf::RectangleShape m_boxRect;
	sf::Text m_text;
	sf::Color m_backgroundColor[3];
	GraphicalStates m_states;
};

#endif // !G_BUTTON_HPP
