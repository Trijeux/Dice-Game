#include "ui_button.h"  // Include the UiButton header file


void UiButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();  // Apply the button's transform to the render states

    target.draw(shape_, states);  // Draw the button's sprite
    target.draw(button_text_, states);  // Draw the button's text
}

// Check if the mouse click event is inside the button's bounds
bool UiButton::ContainsMouse(const sf::Event& event) const
{
    // Calculate mouse position relative to button's position
    const float mouse_x = static_cast<float>(event.mouseButton.x) - getPosition().x;
    const float mouse_y = static_cast<float>(event.mouseButton.y) - getPosition().y;

    // Check if the mouse position is inside the button's global bounds
    if (shape_.getGlobalBounds().contains(mouse_x, mouse_y)) {
        return true;
    }
    else {
        return false;
    }
}

// Handle events for the UiButton
bool UiButton::HandleEvent(const sf::Event& event)
{
    // Check for mouse button released event
    if (event.type == sf::Event::MouseButtonPressed) {
        // If the mouse click is inside the button
        if (ContainsMouse(event))
        {
            // Scale down the button slightly
            //setScale(getScale().x / 0.9f, getScale().y / 0.9f);

            // Check if it was a left mouse button click
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                // Execute callback function if set
                if (call_back_) {
                    call_back_();
                }
            }
        }
    }

    //// Check for mouse button pressed event
    //if (event.type == sf::Event::MouseButtonPressed)
    //{
    //    // If the mouse click is inside the button
    //    if (ContainsMouse(event))
    //    {
    //        // Scale down the button slightly and set build_on flag
    //        setScale(0.9f * getScale().x, 0.9f * getScale().y);
    //        build_on_ = true;
    //    }
    //}

    // Check if the mouse is currently inside the button
    if (ContainsMouse(event)) {
        return true;
    }
    else {
        return false;
    }
}

// Create a new UiButton with specified parameters
void UiButton::CreateButton(const sf::Vector2f pos, const sf::Vector2f size_shape,const std::string& text, const int character_size, const sf::Color color_text)
{
    if (!font_.loadFromFile("ressources/kenvector_future.ttf")) {
        // Handle error: Unable to load font
    }

    button_text_.setFont(font_);  // Set the font for the button text
    button_text_.setString(text);  // Set the text content
    setPosition(pos);  // Set the button's position
    button_text_.setCharacterSize(character_size);  // Set the character size of the text
    button_text_.setFillColor(color_text);  // Set the color of the text

    shape_.setSize(size_shape);
    shape_.setOrigin(shape_.getGlobalBounds().width / 2.0f, shape_.getGlobalBounds().height / 2.0f);  // Set the origin of the sprite to its center
    shape_.setFillColor(sf::Color::Black);  // Set the color of the sprite

    // Set the origin of the text to its center
    const sf::FloatRect text_rect = button_text_.getLocalBounds();
    const sf::FloatRect shape_rect = shape_.getGlobalBounds();
	button_text_.setOrigin(text_rect.left + text_rect.width / 2.0f, text_rect.top + text_rect.height / 2.0f);
    button_text_.setPosition(shape_rect.left + shape_rect.width / 2.0f, shape_rect.top + shape_rect.height / 2.0f);

    

    setScale(1, 1);  // Set the initial scale of the button

    build_on_ = false;
}
