#include "GSlider.hpp"

GSlider::GSlider(GContainer* parent, const ValueRange& valueRange) :
	GWidget(parent),
	m_valueRange(valueRange), m_on_value_change(), m_value(0)
{
	this->setWidgetAppear(new DefSliderAppear(), true);
	this->setSize({ 100.f, 30.f });
}

GSlider::GSlider(GContainer* parent, float minValue, float maxValue, float step) :
	GWidget(parent),
	m_valueRange({ minValue, maxValue, step }), m_on_value_change(), m_value(0)
{
	this->setWidgetAppear(new DefSliderAppear(), true);
	this->setSize({ 100.f, 30.f });
}

void GSlider::onValueChange(GAction* valueChangeAction)
{
	m_on_value_change = valueChangeAction;
}

void GSlider::setValueRange(const GSlider::ValueRange& valueRange)
{
	m_valueRange = valueRange;
	m_value = 0;
	dynamic_cast<GSliderAppear*>(m_appear)->update_value(m_value);
}

void GSlider::setValueRange(float minValue, float maxValue, float step)
{
	m_valueRange.minVal = minValue; m_valueRange.maxVal = maxValue; m_valueRange.step = step;
	m_value = 0;
	dynamic_cast<GSliderAppear*>(m_appear)->update_value(m_value);
}

float GSlider::getValue() const
{
	return std::min(m_valueRange.maxVal, m_valueRange.minVal + m_valueRange.step * m_value);
}

void GSlider::setValue(float value)
{
	if (m_on_value_change != NULL)
		(*m_on_value_change)();
	if (value < m_valueRange.minVal)
		m_value = 0;
	else
		m_value = (std::min(value, m_valueRange.maxVal) - m_valueRange.minVal) / m_valueRange.step + .5f;
	this->UpdateValuE();
}

void GSlider::setWidgetAppear(GWidgetAppear* appear, bool isNew)
{
	GWidget::setWidgetAppear(appear, isNew);
	this->UpdateValuE();
}

void GSlider::listen(const sf::Event& event)
{
	GWidget::listen(event);
	
	switch (event.type) {
	case sf::Event::MouseButtonPressed:
		if (m_clicked)
			this->setValue(		/* Setting the value and updating the appear */
				dynamic_cast<GSliderAppear*>(m_appear)->getValueFromGeometry(		/* Getting the value from the shape of the appear */
					this->getInverseTransform().transformPoint(sf::Vector2f(event.mouseButton.x,event.mouseButton.y)) /* Getting the local coordinate */
				) * (m_valueRange.maxVal - m_valueRange.minVal) + m_valueRange.minVal
			);
		break;
	case sf::Event::MouseMoved:
		if (m_clicked)
			this->setValue(		/* Setting the value and updating the appear */
				dynamic_cast<GSliderAppear*>(m_appear)->getValueFromGeometry(		/* Getting the value from the shape of the appear */
					this->getInverseTransform().transformPoint(sf::Vector2f(event.mouseMove.x,event.mouseMove.y)) /* Getting the local coordinate */
				) * (m_valueRange.maxVal - m_valueRange.minVal) + m_valueRange.minVal
			);
		break;
	case sf::Event::KeyPressed:
		if (this->g_system->hasFocus(this))
			switch (event.key.code){
			case sf::Keyboard::Left:
				if (m_value > 0)
					--m_value;
				this->UpdateValuE();
				break;
			case sf::Keyboard::Right:
				if (m_value * m_valueRange.step < m_valueRange.maxVal - m_valueRange.minVal)
					++m_value;
				this->UpdateValuE();
				break;
			}
		break;
	}
}

void GSlider::UpdateValuE()
{
	dynamic_cast<GSliderAppear*>(m_appear)->update_value((this->getValue() - m_valueRange.minVal) / (m_valueRange.maxVal - m_valueRange.minVal));
}

const GSlider::ValueRange& GSlider::getValueRange()
{
	return m_valueRange;
}

bool DefSliderAppear::withinWidgetBox(const sf::Vector2f& relPos) const
{
	return m_boxRect.getLocalBounds().contains(relPos) || m_slider->getGlobalBounds().contains(relPos);
}

float DefSliderAppear::getValueFromGeometry(sf::Vector2f relPos) const
{
	return ((relPos.x <= 0) ? 0 : ((relPos.x >= m_boxRect.getSize().x) ? 1 : relPos.x / m_boxRect.getSize().x));
}

void DefSliderAppear::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_boxRect, states);
	target.draw(*m_slider, states);
}

void DefSliderAppear::on_link_with_widget(const GSystem* system) { /* Unused */ }

void DefSliderAppear::update_size(const sf::Vector2f& size)
{
	m_slider->setScale({ size.y / 10, size.y / 10 });
	m_boxRect.setSize(size);
}

void DefSliderAppear::update_hover(bool hover)
{
	m_boxRect.setFillColor(m_backgroundColor[(hover) ? Hover : Normal]);
}

void DefSliderAppear::update_clicked(bool clicked)
{
	m_boxRect.setFillColor(m_backgroundColor[(clicked) ? Clicked : Hover]);
}

void DefSliderAppear::update_value(float relValue)
{
	m_slider->setPosition({ relValue * m_boxRect.getSize().x, 0 });
}

DefSliderAppear::DefSliderAppear(const sf::Color& backgroundColor) :
	m_boxRect(), m_slider(),
	m_backgroundColor(), m_states(Normal),
	p_needDeallocSlider(true)
{
	m_boxRect.setOutlineThickness(2);
	this->setBackgroundColor(backgroundColor, DeclineFromOne);

	// Slider Points
	sf::ConvexShape* CSlider = new sf::ConvexShape(5);
	CSlider->setPoint(0, sf::Vector2f(-3, -3));
	CSlider->setPoint(1, sf::Vector2f(3, -3));
	CSlider->setPoint(2, sf::Vector2f(3, 9));
	CSlider->setPoint(3, sf::Vector2f(0, 12));
	CSlider->setPoint(4, sf::Vector2f(-3, 9));
	CSlider->setFillColor(sf::Color(230, 230, 230));
	CSlider->setOutlineColor(sf::Color(200, 200, 200));
	CSlider->setOutlineThickness(2);
	m_slider = CSlider;
}

const sf::Color& DefSliderAppear::getBackgroundColor(GraphicalStates states) const
{
	return m_backgroundColor[states];
}

void DefSliderAppear::setBackgroundColor(const sf::Color& color, GraphicalStates states)
{
	switch (states) {
	case DefSliderAppear::Normal:
	case DefSliderAppear::Hover:
	case DefSliderAppear::Clicked:
		m_backgroundColor[states] = color;
		break;
	case DefSliderAppear::DeclineFromOne:
		for (int i = 0; i < 3; ++i)
			m_backgroundColor[i] = sf::Color(std::min(color.r + 50 * i, 255), std::min(color.g + 50 * i, 255), std::min(color.b + 50 * i, 255));
		break;
	default:
		break;
	}
	m_boxRect.setFillColor(m_backgroundColor[m_states]);
}

sf::Shape* DefSliderAppear::getSliderShape() const
{
	return m_slider;
}

void DefSliderAppear::setSliderShape(sf::Shape* shape, bool isNew)
{
	if (p_needDeallocSlider) {
		delete m_slider;
	}
	m_slider = shape;
	p_needDeallocSlider = isNew;
}

const sf::Color& DefSliderAppear::getOutlineColor() const
{
	return m_boxRect.getOutlineColor();
}

void DefSliderAppear::setOutlineColor(const sf::Color& color)
{
	m_boxRect.setOutlineColor(color);
}

const sf::Color& DefSliderAppear::getBorderColor() const
{
	return m_boxRect.getOutlineColor();
}

void DefSliderAppear::setBorderColor(const sf::Color& color)
{
	m_boxRect.setOutlineColor(color);
}

float DefSliderAppear::getBorderThickness() const
{
	return m_boxRect.getOutlineThickness();
}

void DefSliderAppear::setBorderThickness(float thickness)
{
	m_boxRect.setOutlineThickness(thickness);
}