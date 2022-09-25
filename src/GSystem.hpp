#ifndef G_SYSTEM_HPP
#define G_SYSTEM_HPP

#include<SFML/Graphics/Font.hpp>

class GSystem {
public:
	GSystem();
	void* getFocus() const;
	bool hasFocus(void* elem) const;
	void setFocus(void* elem);
	const sf::Font* getFont() const;
	void setFontFromFile(const std::string& fileName);
	void setFontFromMemory(const void* data, size_t sizeInBytes);
	void setFontFromStream(sf::InputStream& stream);
private:
	void* m_focus;
	sf::Font m_font;
};

#endif // !SYSTEM_HPP
