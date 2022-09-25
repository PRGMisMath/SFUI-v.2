#include "GContainer.hpp"

GContainer::GContainer() :
	m_compounds()
{
}

GContainer::GContainer(std::vector<GWidget*> components) :
	m_compounds(components)
{
}

void GContainer::addComponent(GWidget* component)
{
	if (std::find(std::begin(m_compounds), std::end(m_compounds), component) == std::end(m_compounds))
		m_compounds.push_back(component);
}

void GContainer::removeComponent(GWidget* component)
{
	m_compounds.erase(std::find(std::begin(m_compounds), std::end(m_compounds), component));
}

void GContainer::clear()
{
	m_compounds.clear();
}

const std::vector<GWidget*>& GContainer::getComponents() const
{
	return m_compounds;
}
