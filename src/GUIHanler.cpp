#include "GUIHanler.hpp"

GSystem& GUIHandler::getSystem()
{
    return m_system;
}

void GUIHandler::listen(sf::Event event)
{
    for (GWidget* widget : m_compounds)
        widget->listen(event);
}

void GUIHandler::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    sf::RenderStates wStates;
    for (GWidget* widget : m_compounds) {
        wStates = states;
        wStates.transform *= widget->getTransform();
        widget->m_appear->draw(target, wStates);
    }
}
