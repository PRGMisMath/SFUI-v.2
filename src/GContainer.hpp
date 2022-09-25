#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include "GWidget.hpp"
#include "GSystem.hpp"

class GWidget;

class GContainer {
public:
	GContainer();
	explicit GContainer(std::vector<GWidget*> components);
	void addComponent(GWidget* component);
	void removeComponent(GWidget* component);
	void clear();
	const std::vector<GWidget*>& getComponents() const;
	virtual GSystem& getSystem() = 0;
protected:
	std::vector<GWidget*> m_compounds;
};

#endif // !CONTAINER_HPP