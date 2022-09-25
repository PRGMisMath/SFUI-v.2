#include "GButton.hpp"

GButton::GButton(GContainer* parent, const std::string& text) :
	GWidget(parent), 
	m_text(), m_on_click()
{
	this->setWidgetAppear(new DefButtonAppear(), true);
	this->setSize({ 100.f, 30.f });
	this->setText(text);
}

void GButton::onClick(GAction* clickAction)
{
	m_on_click = clickAction;
}

void GButton::click()
{
	if (m_on_click != NULL)
		(*m_on_click)();
}

const std::string& GButton::getText() const
{
	return m_text;
}

void GButton::setText(const std::string& text)
{
	m_text = text;
	dynamic_cast<GButtonAppear*>(m_appear)->update_text(text);
}

void GButton::setWidgetAppear(GWidgetAppear* appear, bool isNew)
{
	GWidget::setWidgetAppear(appear, isNew);
	dynamic_cast<GButtonAppear*>(m_appear)->update_text(m_text);
}

void GButton::listen(const sf::Event& event)
{
	GWidget::listen(event);

	if (m_clicked && event.type == sf::Event::MouseButtonPressed)
		click();
}

DefButtonAppear::DefButtonAppear(const sf::Color& backgroundColor) :
	m_boxRect(), m_text(),
	m_backgroundColor(), m_states(Normal)
{
	m_text.setCharacterSize(26);
	m_text.setFillColor(sf::Color::Black);
	m_boxRect.setOutlineThickness(2);
	this->setBackgroundColor(backgroundColor, DeclineFromOne);
}

const sf::Color& DefButtonAppear::getBackgroundColor(GraphicalStates states) const
{
	return m_backgroundColor[states];
}

void DefButtonAppear::setBackgroundColor(const sf::Color& color, GraphicalStates states)
{
	switch (states) {
	case DefButtonAppear::Normal:
	case DefButtonAppear::Hover:
	case DefButtonAppear::Clicked:
		m_backgroundColor[states] = color;
		break;
	case DefButtonAppear::DeclineFromOne:
		for (int i = 0; i < 3; ++i)
			m_backgroundColor[i] = sf::Color(std::min(color.r + 50 * i, 255), std::min(color.g + 50 * i, 255), std::min(color.b + 50 * i, 255));
		break;
	default:
		break;
	}
	m_boxRect.setFillColor(m_backgroundColor[m_states]);
}

const sf::Color& DefButtonAppear::getOutlineColor() const
{
	return m_boxRect.getOutlineColor();
}

void DefButtonAppear::setOutlineColor(const sf::Color& color)
{
	m_boxRect.setOutlineColor(color);
}

const sf::Color& DefButtonAppear::getTextColor() const
{
	return m_text.getFillColor();
}

void DefButtonAppear::setTextColor(const sf::Color& color)
{
	m_text.setFillColor(color);
}

const sf::Color& DefButtonAppear::getBorderColor() const
{
	return m_boxRect.getOutlineColor();
}

void DefButtonAppear::setBorderColor(const sf::Color& color)
{
	m_boxRect.setOutlineColor(color);
}

float DefButtonAppear::getBorderThickness() const
{
	return m_boxRect.getOutlineThickness();
}

void DefButtonAppear::setBorderThickness(float thickness)
{
	m_boxRect.setOutlineThickness(thickness);
}

bool DefButtonAppear::withinWidgetBox(const sf::Vector2f& relPos) const
{
	return m_boxRect.getLocalBounds().contains(relPos);
}

void DefButtonAppear::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_boxRect, states);
	target.draw(m_text, states);
}

void DefButtonAppear::update_size(const sf::Vector2f& size)
{
	m_boxRect.setSize(size);
	this->TextPosUpdatE();
}

void DefButtonAppear::update_text(const std::string& text)
{
	m_text.setString(text);
	this->TextPosUpdatE();
}

void DefButtonAppear::update_hover(bool hover)
{
	m_states = (hover) ? Hover : Normal;
	m_boxRect.setFillColor(m_backgroundColor[m_states]);
}

void DefButtonAppear::update_clicked(bool clicked)
{
	m_states = (clicked) ? Clicked : Hover;
	m_boxRect.setFillColor(m_backgroundColor[m_states]);
}

void DefButtonAppear::on_link_with_widget(const GSystem* system)
{
	m_text.setFont(*(system->getFont()));
}

void DefButtonAppear::TextPosUpdatE()
{
	const float rel1TextSize = m_text.getLocalBounds().width / m_text.getCharacterSize();
	if (m_boxRect.getSize().y < 10 || m_boxRect.getSize().x < 6 * rel1TextSize + 4)
		m_text.setCharacterSize(0);
	else {
		m_text.setCharacterSize(std::min(m_boxRect.getSize().y - 4, (m_boxRect.getSize().x - 4) / rel1TextSize));
	}
	m_text.setPosition({ (m_boxRect.getSize().x - m_text.getLocalBounds().width) / 2.f, (m_boxRect.getSize().y - m_text.getCharacterSize()) / 2.f });
}
