#ifndef G_WIDGET_HPP
#define G_WIDGET_HPP

#include<SFML/Graphics.hpp>
#include "GContainer.hpp"
#include "GWidgetAppear.hpp"
#include "GSystem.hpp"

class GContainer;

class GWidget : public sf::Transformable {
public:
	GWidget() = delete;
	GWidget(GContainer* parent);
	~GWidget();
	sf::Vector2f getSize() const;
	void setSize(const sf::Vector2f size);
	GWidgetAppear* getWidgetAppear() const;
	virtual void setWidgetAppear(GWidgetAppear* appear, bool isNew = false); // \param[in] isNew : Vrai si la `WidgetAppear` passé a été créé à l'aide de `new` et doit être désallouer
	virtual void listen(const sf::Event& event);
protected:
	bool WithinBoX(const sf::Vector2f& pos);
protected:
	sf::Vector2f m_size;
	bool m_hover, m_clicked;

	GWidgetAppear* m_appear;
	GSystem* g_system;

	bool p_needDeallocAppear;

	friend class GUIHandler;
};

#endif // !WIDGET_HPP
