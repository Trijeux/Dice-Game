#include "game.h"

#include <iostream>
#include <random>
#include <thread>
#include <windows.h>

#define FORITCH true

Game::Game()
{
	HWND consoleWindow = GetConsoleWindow();
	ShowWindow(consoleWindow, SW_SHOW);

	char is_yes = NULL;
	bool valid_replay_choice = false;

	std::cout << "Welcome to the dice game" << std::endl << std::endl;

	window_.create(sf::VideoMode(450, 700), "Dice Game");

	graphics_.CreateButton(window_);

	do
	{

		std::cout << "Do you want to play in console (Y/y , N/n): ";

#if !FORITCH
			std::cin >> is_yes;
#endif

#if FORITCH
			is_yes = 'n';
#endif

		system("cls");

		if (is_yes == 'Y' || is_yes == 'y' || is_yes == 'N' || is_yes == 'n')
		{
			valid_replay_choice = true;
		}
		else
		{
			std::cout << "Between invalid" << std::endl << std::endl;
		}
	} while (!valid_replay_choice);

	if (is_yes == 'N' || is_yes == 'n')
	{
		sfml_enable_ = true;
		HWND consoleWindow = GetConsoleWindow();
		ShowWindow(consoleWindow, SW_HIDE);
	}
}

void Game::gameloop()
{
	while (window_.isOpen())
	{
		do
		{
			if (sfml_enable_)
			{
				sf::Event event;
				while (window_.pollEvent(event))
				{
					if (ChoiceNumber(event) && !choice_number_lock_ && !graphics_.is_end_)
					{
						choice_number_lock_ = true;
						choice_bet_lock_ = false;
						std::cout << std::endl << std::endl << "Number : " << choice_number_;
					}
					else if (ChoiceBet(event) && !choice_bet_lock_ && !graphics_.is_end_)
					{
						choice_bet_lock_ = true;
						choice_number_lock_ = false;
						ChangeBetInPrice(event);
						if (choice_bet_lock_)
						{
							std::cout << std::endl << "Bet : " << bet_ << std::endl;
							DiceRoll();
							ComparePlayerChoice();
						}
					}

					if (player_bankroll_ <= 0)
					{
						graphics_.is_end_ = true;
						graphics_.is_bet_ = false;
						graphics_.is_choice_ = false;
						if (graphics_.HandleEventQuit(event))
						{
							ReplayOrNot();
						}
					}


					if (event.type == sf::Event::Closed)
					{
						window_.close();
						replay_ = false;
					}
				}


				window_.clear(sf::Color::Blue);

				graphics_.ChangeTextChoice(window_);

				graphics_.update_bankroll(window_, player_bankroll_);

				graphics_.Draw(window_);

				window_.display();
			}

			if (!sfml_enable_)
			{
				ChoiceNumber();

				ChoiceBet();

				DiceRoll();

				ComparePlayerChoice();

				if (player_bankroll_ <= 0)
				{
					ReplayOrNot();
				}
			}

		} while (replay_);
	}
}

void Game::ChoiceNumber()
{
	bool valid_player_choice_number = false;

	//Ask the player number
	do
	{
		std::cout << "Choose a number between 1 and 6 : ";
		std::cin >> player_choice_number_;

		system("cls");

		//Check if player input is valid
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Between invalid" << std::endl << std::endl;
		}
		else
		{
			int checker_number = 1;
			bool valid_number = false;
			do
			{
				if (player_choice_number_ == checker_number)
				{
					valid_number = true;
					valid_player_choice_number = true;
				}
				else if (checker_number >= 6)
				{
					valid_number = true;
					std::cout << "Between invalid" << std::endl << std::endl;
				}
				checker_number++;
			} while (!valid_number);
		}

	} while (!valid_player_choice_number);
}

bool Game::ChoiceNumber(sf::Event event)
{
	int choice_test = 0;
	choice_test = graphics_.HandleEventChoiceNumber(event);

	int checker_number = 1;
	bool valid_number = false;

	if (choice_test > 0)
	{
		do
		{
			if (choice_test == checker_number)
			{
				valid_number = true;
				graphics_.is_lose_ = false;
				graphics_.is_win_ = false;
				choice_number_ = choice_test;
				return true;
			}
			else if (checker_number >= 6)
			{
				valid_number = true;
			}
			checker_number++;
		} while (!valid_number);
	}
	return false;
}

void Game::ChoiceBet()
{
	bool valid_player_choice_bet = false;

	//Ask the player bet
	do
	{
		std::cout << "if you win you double the bet and if you lose you lose the bet" << std::endl << std::endl;

		std::cout << "Your bankroll : " << player_bankroll_ << "$" << std::endl;
		std::cout << "Choose a number between 10$(1), 50$(2), 100$(3), 250$(4), 500$(5) or 1000$(6) : ";
		std::cin >> player_choice_bet_;

		system("cls");

		//Check if player input is valid
		if (std::cin.fail())
		{
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Between invalid" << std::endl << std::endl;
		}
		else
		{
			int checker_bet = 1;
			bool valid_bet = false;
			do
			{
				if (player_choice_bet_ == checker_bet)
				{
					valid_bet = true;
					valid_player_choice_bet = true;
				}
				else if (checker_bet >= 6)
				{
					valid_bet = true;
					std::cout << "Between invalid" << std::endl << std::endl;
				}
				checker_bet++;
			} while (!valid_bet);
		}

	} while (!valid_player_choice_bet);

	SaveChoice();
}

bool Game::ChoiceBet(sf::Event event)
{
	int choice_test = 0;
	choice_test = graphics_.HandleEventChoiceBet(event);


	//Ask the player bet
	int checker_bet = 1;
	bool valid_bet = false;

	if (choice_test > 0)
	{
		do
		{
			if (choice_test == checker_bet)
			{
				valid_bet = true;
				choice_bet_ = choice_test;
				graphics_.is_invalid_bet_ = false;
				return true;
			}
			else if (checker_bet >= 6)
			{
				valid_bet = true;
			}
			checker_bet++;
		} while (!valid_bet);
	}

	return false;
}

void Game::ChangeBetInPrice()
{
	bet_ = 0;

	switch (choice_bet_)
	{
	case 1:
	{
		bet_ = 10;
	}
	break;
	case 2:
	{
		bet_ = 50;
	}
	break;
	case 3:
	{
		bet_ = 100;
	}
	break;
	case 4:
	{
		bet_ = 250;
	}
	break;
	case 5:
	{
		bet_ = 500;
	}
	break;
	case 6:
	{
		bet_ = 1000;
	}
	break;
	default:
	{
		std::cout << "Error choice bet" << std::endl;
		EXIT_FAILURE;
	}
	}
}

void Game::ChangeBetInPrice(sf::Event event)
{
	bet_ = 0;

	switch (choice_bet_)
	{
	case 1:
	{
		bet_ = 10;
	}
	break;
	case 2:
	{
		bet_ = 50;
	}
	break;
	case 3:
	{
		bet_ = 100;
	}
	break;
	case 4:
	{
		bet_ = 250;
	}
	break;
	case 5:
	{
		bet_ = 500;
	}
	break;
	case 6:
	{
		bet_ = 1000;
	}
	break;
	default:
	{
		std::cout << "Error choice bet" << std::endl;
		EXIT_FAILURE;
	}
	}

	if (bet_ > player_bankroll_)
	{
		choice_bet_lock_ = false;
		graphics_.ChoiceBetInvalid();
		graphics_.is_invalid_bet_ = true;
	}
}

void Game::SaveChoice()
{
	//Save Choice player
	choice_number_ = player_choice_number_;
	choice_bet_ = player_choice_bet_;


	ChangeBetInPrice();


	if (bet_ <= player_bankroll_)
	{
		std::cout << "You play " << choice_number_ << std::endl;
		std::cout << "You bet " << bet_ << "$" << std::endl;
	}
	else
	{
		std::cout << "you can't bet what you don't have!!!" << std::endl << std::endl;
		ChoiceBet();
	}


	//std::this_thread::sleep_for(std::chrono::seconds(1));
}

void Game::DiceRoll()
{
	bool good_rand;

	//Roll Die
	do
	{
		result_ = 0;

		std::random_device rand;
		std::uniform_int_distribution<int> nb_rand{ 1,  6 };

		result_ = nb_rand(rand);

		if (result_ <= 0 || result_ > 6)
		{
			good_rand = false;
		}
		else
		{
			good_rand = true;
		}

	} while (!good_rand);

	if (sfml_enable_)
	{
		graphics_.LoadImageDice(result_, window_);
	}
}

void Game::ComparePlayerChoice()
{
	std::cout << std::endl;

	//Compare with player choice
	if (result_ == choice_number_)
	{
		std::cout << "The result is " << result_ << std::endl;
		std::cout << "You win : " << bet_ * 2 << "$" << std::endl << std::endl;

		if (sfml_enable_)
		{
			graphics_.is_win_ = true;
			graphics_.WinOrLose(window_, bet_ * 2);
		}

		player_bankroll_ += bet_ * 2;
		std::cout << "You bankroll : " << player_bankroll_ << "$";
	}
	else
	{
		std::cout << "The result is " << result_ << std::endl;
		std::cout << "You lost : " << bet_ << "$" << std::endl << std::endl;

		if (sfml_enable_)
		{
			graphics_.is_lose_ = true;
			graphics_.WinOrLose(window_, bet_);
		}

		player_bankroll_ -= bet_;
		std::cout << "You bankroll : " << player_bankroll_ << "$";
	}

	std::cout << std::endl << std::endl;

}

void Game::ReplayOrNot()
{
	if (!sfml_enable_)
	{
		bool valid_replay_choice = false;

		//Ask the player if they should play again
		do
		{
			std::cout << "Do you want to play again Yes [Y/y] or No [N/n] : ";
			std::cin >> player_choice_replay_;
			system("cls");
			if (player_choice_replay_ == 'Y' || player_choice_replay_ == 'y' || player_choice_replay_ == 'N' || player_choice_replay_ == 'n')
			{
				valid_replay_choice = true;
			}
			else
			{
				std::cout << "Between invalid" << std::endl << std::endl;
			}
		} while (!valid_replay_choice);

		if (player_choice_replay_ == 'N' || player_choice_replay_ == 'n')
		{
			replay_ = false;
			window_.close();
		}
	}

	if (sfml_enable_)
	{
		replay_ = false;
		window_.close();
	}

	player_bankroll_ = 1000;
}
