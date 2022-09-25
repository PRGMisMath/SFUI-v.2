#ifndef G_CURSOR_HPP

#include "GWidget.hpp"
#include "GAction.hpp"

class GSlider;
class GSliderAppear;
class DefSliderAppear;

class GSlider : public GWidget {
public:
	struct ValueRange {
		float minVal, maxVal, step;
	};

	GSlider(GContainer* parent, const ValueRange& valueRange = {0.f,100.f,1.f});
	GSlider(GContainer* parent, float minValue, float maxValue, float step);
	void onValueChange(GAction* valueChangeAction);
	const ValueRange& getValueRange();
	void setValueRange(const ValueRange& valueRange);
	void setValueRange(float minValue, float maxValue, float step);
	float getValue() const;
	void setValue(float value);
	virtual void setWidgetAppear(GWidgetAppear* appear, bool isNew = false);
	virtual void listen(const sf::Event& event);
private:
	void UpdateValuE();
private:
	struct ValueRange m_valueRange;
	int m_value;
	GAction* m_on_value_change;
};

class GSliderAppear : public GWidgetAppear {
public:
private:
	virtual float getValueFromGeometry(sf::Vector2f relPos) const = 0;

	virtual void update_value(float relValue) = 0;

	friend class GSlider;
};

class DefSliderAppear : public GSliderAppear {
public:
	enum GraphicalStates {
		Normal = 0, Hover = 1, Clicked = 2,
		DeclineFromOne = -1
	};

	DefSliderAppear(const sf::Color& backgroundColor = sf::Color::Blue);

	const sf::Color& getBackgroundColor(GraphicalStates states) const;
	void setBackgroundColor(const sf::Color& color, GraphicalStates states);
	sf::Shape* getSliderShape() const;
	void setSliderShape(sf::Shape* shape, bool isNew = false);
	const sf::Color& getOutlineColor() const;
	void setOutlineColor(const sf::Color& color);
	const sf::Color& getBorderColor() const;
	void setBorderColor(const sf::Color& color);
	float getBorderThickness() const;
	void setBorderThickness(float thickness);

	virtual bool withinWidgetBox(const sf::Vector2f& relPos) const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	virtual void on_link_with_widget(const GSystem* system);
	virtual float getValueFromGeometry(sf::Vector2f relPos) const;

	virtual void update_size(const sf::Vector2f& size);
	virtual void update_hover(bool hover);
	virtual void update_clicked(bool clicked);
	virtual void update_value(float relValue);
private:
	sf::RectangleShape m_boxRect;
	sf::Shape* m_slider;
	sf::Color m_backgroundColor[3];
	GraphicalStates m_states;

	bool p_needDeallocSlider;
};

#endif // G_CURSOR_HPP