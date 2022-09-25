#include "GSystem.hpp"

#include<cassert>

GSystem::GSystem() :
	m_focus(), m_font()
{
#ifdef _WIN32 // Windows !!
	assert(m_font.loadFromFile("C:\\Windows\\Fonts\\Arial.ttf"));
#endif
}

void* GSystem::getFocus() const
{
	return m_focus;
}

bool GSystem::hasFocus(void* elem) const
{
	return m_focus == elem;
}

void GSystem::setFocus(void* elem)
{
	m_focus = elem;
}

const sf::Font* GSystem::getFont() const
{
	return &m_font;
}

void GSystem::setFontFromFile(const std::string& fileName)
{
	m_font.loadFromFile(fileName);
}

void GSystem::setFontFromMemory(const void* data, size_t sizeInBytes)
{
	m_font.loadFromMemory(data, sizeInBytes);
}

void GSystem::setFontFromStream(sf::InputStream& stream)
{
	m_font.loadFromStream(stream);
}
