#include "GWidget.hpp"

GWidget::GWidget(GContainer* parent) :
	m_size(), m_appear(NULL),
	g_system(&(parent->getSystem())),
	p_needDeallocAppear(true)
{
	parent->addComponent(this);
}

GWidget::~GWidget()
{
	if (p_needDeallocAppear)
		delete m_appear;
}

sf::Vector2f GWidget::getSize() const
{
	return this->m_size;
}

void GWidget::setSize(const sf::Vector2f size)
{
	this->m_size = size;
	m_appear->update_size(size);
}

GWidgetAppear* GWidget::getWidgetAppear() const
{
	return m_appear;
}

void GWidget::setWidgetAppear(GWidgetAppear* appear, bool isNew)
{
	if (p_needDeallocAppear) {
		delete m_appear;
	}
	m_appear = appear;
	appear->on_link_with_widget(g_system);
	appear->update_size(m_size);
	p_needDeallocAppear = isNew;
}

void GWidget::listen(const sf::Event& event)
{
	switch (event.type) {
	case sf::Event::MouseButtonPressed:
		if (this->WithinBoX(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
			g_system->setFocus(this);
			m_clicked = true;
			m_appear->update_clicked(true);
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (m_clicked) {
			m_clicked = false;
			m_appear->update_clicked(false);
		}
		break;
	case sf::Event::MouseMoved:
		if (!(m_hover == this->WithinBoX(sf::Vector2f(event.mouseMove.x, event.mouseMove.y)))) {
			m_hover = !m_hover;
			m_appear->update_hover(m_hover);
		}
		break;
	}
}

bool GWidget::WithinBoX(const sf::Vector2f& pos)
{
	return m_appear->withinWidgetBox(this->getInverseTransform().transformPoint(pos));
}
