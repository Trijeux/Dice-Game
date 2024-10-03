#ifndef API_UI_UI_BUTTON_H
#define API_UI_UI_BUTTON_H

#include <functional> // Include for std::function
#include <string> // Include for std::string
#include <SFML/Graphics.hpp> // Include SFML graphics library

class UiButton final : public sf::Drawable, public sf::Transformable
{
private:
	sf::Font font_; // Font for the button text
	sf::Text button_text_; // Text displayed on the button

	sf::RectangleShape shape_;

	// Private method to check if mouse cursor is within the button area
	bool ContainsMouse(const sf::Event& event) const;

	// Private boolean indicating if building is on (purpose unclear from provided context)
	bool build_on_ = false;

public:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	// Public method to handle SFML events related to the button
	bool HandleEvent(const sf::Event& event);

	// Public method to create the button
	void CreateButton(sf::Vector2f pos, const sf::Vector2f size_shape, const std::string& text, int character_size, sf::Color color_text);

	// Public std::function callback for button click event
	std::function<void()> call_back_;
};

#endif // API_UI_UI_BUTTON_H
