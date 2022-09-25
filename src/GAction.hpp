#ifndef ACTION_HPP
#define ACTION_HPP

#include<vector>
#include<map>
#include "GWidget.hpp"

class GAction {
public:
	virtual void operator()() = 0;
};

class GFoncAction : public GAction {
public:
	GFoncAction(void (*fonction)() = NULL);
	virtual void operator()();
private:
	void (*m_fonc)();
};

/** 
* @deprecated La classe nécessite une conversion de pointeur et n'est pas très élégante
* @brief Action permettant de passer le widget activateur en paramètre
*/
class GWidgetAction : public GAction {
public:
	GWidgetAction(void (*fonction)(GWidget*), GWidget* actionThrower);
	virtual void operator()();
private:
	void (*m_fonc)(GWidget*);
	GWidget* m_action_thrower;
};

#endif // !ACTION_HPP