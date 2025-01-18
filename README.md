# Blackjack Game

Welcome to the Blackjack game, a simple yet engaging card game between a player and a dealer. This project showcases fundamental game development concepts using C++.

## Features

- **Deck Management**: The game includes functions to create and shuffle a deck of 52 cards.
- **Gameplay**: Players can hit or stand, and the dealer follows standard Blackjack rules. The game calculates and displays the total points for both the player and the dealer.
- **Win Tracking**: The game keeps track of the number of games played and the player's wins.
- **Rules Display**: Players can view the rules of the game from a text file.
- **User-Friendly Menu**: A menu system allows players to start the game, view rules, and check win statistics.

## How to Play

1. **Start the Game**: Select the option to play from the menu.
2. **Gameplay**: The dealer and player are dealt cards. The player can choose to hit (draw another card) or stand (end their turn).
3. **Win Conditions**: The player wins if their total is 21 or if they have a higher total than the dealer without exceeding 21. The dealer wins if their total is higher than the player's without exceeding 21 or if the player exceeds 21.
4. **View Wins**: Players can view their win statistics from the menu.

## Getting Started

To get started with the Blackjack game, clone the repository and compile the `main.cpp` file using a C++ compiler. Execute the compiled binary to start the game.

```sh
git clone https://github.com/SlothCartel/Blackjack.git
cd Blackjack
g++ -o blackjack main.cpp
./blackjack