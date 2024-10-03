#include "graphics.h"

#include <iostream>

Graphics::Graphics()
{
	dice_one_texture_.loadFromFile("ressources/dice_one.png");
	dice_tow_texture_.loadFromFile("ressources/dice_tow.png");
	dice_three_texture_.loadFromFile("ressources/dice_three.png");
	dice_four_texture_.loadFromFile("ressources/dice_four.png");
	dice_five_texture_.loadFromFile("ressources/dice_five.png");
	dice_six_texture_.loadFromFile("ressources/dice_six.png");

	if (!font_.loadFromFile("ressources/kenvector_future.ttf")) {
		// Handle error: Unable to load font
	}

	text_choice_.setFont(font_);
	text_choice_.setFillColor(sf::Color::Yellow);

	text_bankroll_.setFont(font_);
	text_bankroll_.setFillColor(sf::Color::Yellow);

	text_win_or_lose_.setFont(font_);
	text_win_or_lose_.setFillColor(sf::Color::Yellow);

	text_invalid_bet_.setFont(font_);
	text_invalid_bet_.setFillColor(sf::Color::Yellow);
}


void Graphics::CreateButton(sf::RenderWindow& window)
{
	btn_one_.CreateButton(sf::Vector2f(window.getSize().x / 6, window.getSize().y / 2 + 175), sf::Vector2f(95, 50), "1", 30, sf::Color::Yellow);
	btn_tow_.CreateButton(sf::Vector2f(window.getSize().x / 6 + 100, window.getSize().y / 2 + 175), sf::Vector2f(95, 50), "2", 30, sf::Color::Yellow);
	btn_three_.CreateButton(sf::Vector2f(window.getSize().x / 6 + 200, window.getSize().y / 2 + 175), sf::Vector2f(95, 50), "3", 30, sf::Color::Yellow);
	btn_four_.CreateButton(sf::Vector2f(window.getSize().x / 6 + 300, window.getSize().y / 2 + 175), sf::Vector2f(95, 50), "4", 30, sf::Color::Yellow);
	btn_five_.CreateButton(sf::Vector2f(window.getSize().x / 6 + 100, window.getSize().y / 2 + 250), sf::Vector2f(95, 50), "5", 30, sf::Color::Yellow);
	btn_six_.CreateButton(sf::Vector2f(window.getSize().x / 6 + 200, window.getSize().y / 2 + 250), sf::Vector2f(95, 50), "6", 30, sf::Color::Yellow);

	btn_bet_one_.CreateButton(sf::Vector2f(window.getSize().x / 6, window.getSize().y / 2 + 175), sf::Vector2f(95, 50), "10", 30, sf::Color::Yellow);
	btn_bet_tow_.CreateButton(sf::Vector2f(window.getSize().x / 6 + 100, window.getSize().y / 2 + 175), sf::Vector2f(95, 50), "50", 30, sf::Color::Yellow);
	btn_bet_three_.CreateButton(sf::Vector2f(window.getSize().x / 6 + 200, window.getSize().y / 2 + 175), sf::Vector2f(95, 50), "100", 30, sf::Color::Yellow);
	btn_bet_four_.CreateButton(sf::Vector2f(window.getSize().x / 6 + 300, window.getSize().y / 2 + 175), sf::Vector2f(95, 50), "250", 30, sf::Color::Yellow);
	btn_bet_five_.CreateButton(sf::Vector2f(window.getSize().x / 6 + 100, window.getSize().y / 2 + 250), sf::Vector2f(95, 50), "500", 30, sf::Color::Yellow);
	btn_bet_six_.CreateButton(sf::Vector2f(window.getSize().x / 6 + 200, window.getSize().y / 2 + 250), sf::Vector2f(95, 50), "1000", 30, sf::Color::Yellow);

	btn_end_.CreateButton(sf::Vector2f(window.getSize().x / 6 + 150, window.getSize().y / 2 + 200), sf::Vector2f(95, 50), "Quit", 30, sf::Color::Yellow);

	btn_one_.call_back_ = [this]()
		{
			number_choice_ = 1;
			is_choice_ = false;
			is_bet_ = true;
		};
	btn_tow_.call_back_ = [this]()
		{
			number_choice_ = 2;
			is_choice_ = false;
			is_bet_ = true;
		};
	btn_three_.call_back_ = [this]()
		{
			number_choice_ = 3;
			is_choice_ = false;
			is_bet_ = true;
		};
	btn_four_.call_back_ = [this]()
		{
			number_choice_ = 4;
			is_choice_ = false;
			is_bet_ = true;
		};
	btn_five_.call_back_ = [this]()
		{
			number_choice_ = 5;
			is_choice_ = false;
			is_bet_ = true;
		};
	btn_six_.call_back_ = [this]()
		{
			number_choice_ = 6;
			is_choice_ = false;
			is_bet_ = true;
		};

	btn_bet_one_.call_back_ = [this]()
		{
			bet_choice_ = 1;
			is_bet_ = false;
			is_choice_ = true;
		};
	btn_bet_tow_.call_back_ = [this]()
		{
			bet_choice_ = 2;
			is_bet_ = false;
			is_choice_ = true;
		};
	btn_bet_three_.call_back_ = [this]()
		{
			bet_choice_ = 3;
			is_bet_ = false;
			is_choice_ = true;
		};
	btn_bet_four_.call_back_ = [this]()
		{
			bet_choice_ = 4;
			is_bet_ = false;
			is_choice_ = true;
		};
	btn_bet_five_.call_back_ = [this]()
		{
			bet_choice_ = 5;
			is_bet_ = false;
			is_choice_ = true;
		};
	btn_bet_six_.call_back_ = [this]()
		{
			bet_choice_ = 6;
			is_bet_ = false;
			is_choice_ = true;
		};

	text_invalid_bet_.setString("Invalid Bet");
	const sf::FloatRect text_invalid_bet = text_invalid_bet_.getLocalBounds();
	text_invalid_bet_.setOrigin(text_invalid_bet.left + text_invalid_bet.width / 2.0f, text_invalid_bet.top + text_invalid_bet.height / 2.0f);
	text_invalid_bet_.setPosition(window.getSize().x / 2, window.getSize().y - 50);
}

void Graphics::update_bankroll(sf::RenderWindow& window, int player_bankroll)
{
	text_bankroll_.setString("Bankroll : " + std::to_string(player_bankroll) + "$");
	const sf::FloatRect text_bankroll_rect = text_bankroll_.getLocalBounds();
	text_bankroll_.setOrigin(text_bankroll_rect.left + text_bankroll_rect.width / 2.0f, text_bankroll_rect.top + text_bankroll_rect.height / 2.0f);
	text_bankroll_.setPosition(225, window.getSize().y - 15);
}

int Graphics::HandleEventChoiceNumber(const sf::Event& event)
{
	number_choice_ = 0;
	if (is_choice_ && !is_bet_)
	{
		if (btn_one_.HandleEvent(event) ||
			btn_tow_.HandleEvent(event) ||
			btn_three_.HandleEvent(event) ||
			btn_four_.HandleEvent(event) ||
			btn_five_.HandleEvent(event) ||
			btn_six_.HandleEvent(event))
		{
			return number_choice_;
		}
	}
}

int Graphics::HandleEventChoiceBet(const sf::Event& event)
{
	bet_choice_ = 0;
	if (is_bet_ && !is_choice_)
	{
		if (btn_bet_one_.HandleEvent(event) ||
			btn_bet_tow_.HandleEvent(event) ||
			btn_bet_three_.HandleEvent(event) ||
			btn_bet_four_.HandleEvent(event) ||
			btn_bet_five_.HandleEvent(event) ||
			btn_bet_six_.HandleEvent(event))
		{
			return bet_choice_;
		}
	}
}

bool Graphics::HandleEventQuit(const sf::Event& event)
{
	return btn_end_.HandleEvent(event);
}

void Graphics::ChangeTextChoice(sf::RenderWindow& window)
{
	if (is_choice_)
	{
		text_choice_.setString("Choice Number");
	}

	if (is_bet_)
	{
		text_choice_.setString("Choice Bet");
	}


	const sf::FloatRect text_choice_rect = text_choice_.getLocalBounds();
	text_choice_.setOrigin(text_choice_rect.left + text_choice_rect.width / 2.0f, text_choice_rect.top + text_choice_rect.height / 2.0f);
	text_choice_.setPosition(window.getSize().x / 2, window.getSize().y / 2 + 100);
}

void Graphics::WinOrLose(sf::RenderWindow& window, int bet)
{
	if (is_win_)
	{
		text_win_or_lose_.setString("You Win " + std::to_string(bet) + "$");
	}

	if (is_lose_)
	{
		text_win_or_lose_.setString("You Lose " + std::to_string(bet) + "$");
	}

	const sf::FloatRect text_win_or_lose = text_win_or_lose_.getLocalBounds();
	text_win_or_lose_.setOrigin(text_win_or_lose.left + text_win_or_lose.width / 2.0f, text_win_or_lose.top + text_win_or_lose.height / 2.0f);
	text_win_or_lose_.setPosition(window.getSize().x / 2, window.getSize().y - 50);
}

void Graphics::ChoiceBetInvalid()
{
	is_bet_ = true;
	is_choice_ = false;
}

void Graphics::LoadImageDice(const int dice_number, sf::RenderWindow& window)
{
	switch (dice_number)
	{
	case 1:
	{
		dice_sprite_.setTexture(dice_one_texture_);
	}
	break;
	case 2:
	{
		dice_sprite_.setTexture(dice_tow_texture_);
	}
	break;
	case 3:
	{
		dice_sprite_.setTexture(dice_three_texture_);
	}
	break;
	case 4:
	{
		dice_sprite_.setTexture(dice_four_texture_);
	}
	break;
	case 5:
	{
		dice_sprite_.setTexture(dice_five_texture_);
	}
	break;
	case 6:
	{
		dice_sprite_.setTexture(dice_six_texture_);
	}
	break;
	default:
	{
		std::cout << "Error choice image";
	}
	}

	dice_sprite_.setOrigin(dice_sprite_.getGlobalBounds().width / 2, dice_sprite_.getGlobalBounds().height / 2);
	dice_sprite_.setPosition(window.getSize().x / 2, window.getSize().y / 4 + 45);
}

void Graphics::Draw(sf::RenderWindow& window)
{
	window.draw(dice_sprite_);

	if (is_choice_)
	{
		window.draw(btn_one_);
		window.draw(btn_tow_);
		window.draw(btn_three_);
		window.draw(btn_four_);
		window.draw(btn_five_);
		window.draw(btn_six_);
	}

	if (is_bet_)
	{
		window.draw(btn_bet_one_);
		window.draw(btn_bet_tow_);
		window.draw(btn_bet_three_);
		window.draw(btn_bet_four_);
		window.draw(btn_bet_five_);
		window.draw(btn_bet_six_);
	}

	if (is_end_)
	{
		window.draw(btn_end_);
	}

	if (is_choice_ || is_bet_)
	{
		window.draw(text_choice_);
	}

	window.draw(text_bankroll_);

	if (is_win_ || is_lose_)
	{
		window.draw(text_win_or_lose_);
	}

	if (is_invalid_bet_)
	{
		window.draw(text_invalid_bet_);
	}
}

