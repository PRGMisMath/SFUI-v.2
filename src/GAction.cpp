#include "GAction.hpp"

GFoncAction::GFoncAction(void(*fonction)()) :
	m_fonc(fonction)
{
}

void GFoncAction::operator()()
{
	if (m_fonc != NULL)
		m_fonc();
}

GWidgetAction::GWidgetAction(void(*fonction)(GWidget*), GWidget* actionThrower) :
	m_action_thrower(actionThrower), m_fonc(fonction)
{
}

void GWidgetAction::operator()()
{
	if (m_fonc != NULL)
		m_fonc(m_action_thrower);
}