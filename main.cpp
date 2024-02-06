#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>
#include <fstream>
using namespace std;

//Constant counters for wins and gamesplayed
int GamesPlayed = 0;
int Wins = 0;

//struct to store the value of cards
struct Cards
{
    string suit;
    string value;
};

void MakeDeck(Cards deck[52],string* suitPtr, string* valuePtr)//Function to populate deck
{
    //Initialize counter
    int k = 0;

    //for loop to populate deck
    for (int i = 0 ; i < 4 ; i++)
    {

        for (int j = 0 ; j < 13 ; j++)
        {
            deck[k].value = *(valuePtr + j);
            deck[k].suit = *(suitPtr + i);
            k++;
        }
    }
}

void ShuffleDeck(Cards deck[52])//Function to shuffle cards
{
    //Initialize random number generator
    srand(time(0));

    //Sorting algorithm to shuffle cards by swapping cards randomly
    for (int t = 0 ; t < 52 ; t++)
    {
        Cards temp;

        int index = rand() % 51;

        temp.value = deck[t].value;
        temp.suit = deck[t].suit;
        deck[t].value = deck[index].value;
        deck[t].suit = deck[index].suit;
        deck[index].value = temp.value;
        deck[index].suit = temp.suit;
    }
}

int DetermineRank(string value, int total)//Function to determine the rank of a card
{
    int CardValue;

    //simple if-else-if statement to assign card values
    if (value == "ACE")
    {
        if (total < 10)
            CardValue = 11;
        else
            CardValue = 1;
    }
    else if (value == "2")
        CardValue = 2;
    else if (value == "3")
        CardValue = 3;
    else if (value == "4")
        CardValue = 4;
    else if (value == "5")
        CardValue = 5;
    else if (value == "6")
        CardValue = 6;
    else if (value == "7")
        CardValue = 7;
    else if (value == "8")
        CardValue = 8;
    else if (value == "9")
        CardValue = 9;
    else
        CardValue = 10;

    return CardValue;
}

void DisplayDealerHand(Cards deck[52], int DealerTotal)//Function to display dealer hand
{
    string Card, DealerCard2;

    //logic implemented to make sure the right card is drawn and to increment the dealers total
    cout << "\nDealer:" << endl;
    Card = deck[0].value + " of " + deck[0].suit;
    cout << Card << endl;
    DealerCard2 = deck[1].value + " of " + deck[1].suit;
    cout << DealerCard2 << endl;
    cout << "Total: " << DealerTotal << endl;
}

void PlayGame(Cards deck[52])//Function for playing the game
{
    int DealerTotal = 0, PlayerTotal = 0;
    string Card, DealerCard2;
    bool finished = false;
    int iCount = 0;

    //Display opening hands for both the dealer and the player
    cout << "------------" << endl;
    cout << "BLACKJACK" << endl;
    cout << "------------" << endl;
    cout << "\nDealer:" << endl;

    //Display first dealer card
    Card = deck[iCount].value + " of " + deck[iCount].suit;
    DealerTotal = DealerTotal + DetermineRank(deck[iCount].value, DealerTotal);
    iCount++;
    cout << Card << endl;

    //Get second dealer card but do not display it
    DealerCard2 = deck[iCount].value + " of " + deck[iCount].suit;
    DealerTotal = DealerTotal + DetermineRank(deck[iCount].value, DealerTotal);
    iCount++;
    cout << "--" << endl;

    //Get the first player card and display it
    cout << "\nPlayer:" << endl;
    Card = deck[iCount].value + " of " + deck[iCount].suit;
    PlayerTotal = PlayerTotal + DetermineRank(deck[iCount].value, PlayerTotal);
    iCount++;
    cout << Card << endl;
    Card = deck[iCount].value + " of " + deck[iCount].suit;
    PlayerTotal = PlayerTotal + DetermineRank(deck[iCount].value, PlayerTotal);
    iCount++;
    cout << Card << endl;
    cout << "Total: " << PlayerTotal << endl;

    //Prompt the user for their next action
    cout << "\nWould you like to Hit or Stand? (1-Hit/2-Stand) ";

    //while loop used for multiple actions
    while (finished == false)
    {
        //get player input
        string answer;
        cin >> answer;
        cout << endl;
        GamesPlayed++;

        if (answer != "1" && answer != "2")//Invalid input handling
        {
            cout << "Invalid input, try again!" << endl;
            cout << "\nWould you like to Hit or Stand? (1-Hit/2-Stand) ";
        }
        else if (answer == "1")//Hit action
        {
            //Additional while loop to make sure that player's action is legal
            while (PlayerTotal < 21)
            {
                Card = deck[iCount].value + " of " + deck[iCount].suit;
                PlayerTotal = PlayerTotal + DetermineRank(deck[iCount].value, PlayerTotal);
                iCount++;

                cout << Card << endl;
                cout << "Total: " << PlayerTotal << endl;

                if (PlayerTotal < 21)//Allow user to select an action
                {
                    cout << "Would you like to Hit or Stand? (1-Hit/2-Stand) ";
                    cin >> answer;
                    cout << endl;
                }

                if (answer == "2")
                {
                    break;
                }
            }

            //switch statement to display the winner
            if (PlayerTotal > 21)
            {
                DisplayDealerHand(deck, DealerTotal);

                cout << "\nDealer wins! Better luck next time!" << endl;
            }
            else if (PlayerTotal == 21)
            {
                DisplayDealerHand(deck, DealerTotal);

                if (PlayerTotal == DealerTotal)
                {
                    cout << "DRAW" << endl;
                }
                else if (PlayerTotal > DealerTotal)
                {
                    cout << "\nPlayer Wins! Congratulations!" << endl;
                    Wins++;
                }
            }
            else if (PlayerTotal > DealerTotal && PlayerTotal <= 21)
            {
                DisplayDealerHand(deck, DealerTotal);

                while (DealerTotal <= 16)
                {
                    cout << "\nDealer hits:" << endl;
                    Card = deck[iCount].value + " of " + deck[iCount].suit;
                    DealerTotal = DealerTotal + DetermineRank(deck[iCount].value, DealerTotal);
                    iCount++;

                    cout << Card << endl;
                    cout << "Total: " << DealerTotal << endl;
                }

                if (PlayerTotal > DealerTotal && PlayerTotal <= 21)
                {
                    cout << "\nPlayer Wins! Congratulations!" << endl;
                    Wins++;
                }
                else if (DealerTotal > PlayerTotal && DealerTotal <= 21)
                {
                    cout << "\nDealer wins! Better luck next time!" << endl;
                }
                else if (DealerTotal > 21 && PlayerTotal <= 21)
                {
                    cout << "\nPlayer Wins! Congratulations!" << endl;
                    Wins++;
                }
                else if (PlayerTotal > 21 && DealerTotal <= 21)
                {
                    cout << "\nDealer wins! Better luck next time!" << endl;
                }



            }
            else if (PlayerTotal < DealerTotal)
            {
                DisplayDealerHand(deck, DealerTotal);

                while (DealerTotal <= 16)
                {
                    cout << "\nDealer hits:" << endl;
                    Card = deck[iCount].value + " of " + deck[iCount].suit;
                    DealerTotal = DealerTotal + DetermineRank(deck[iCount].value, DealerTotal);
                    iCount++;

                    cout << Card << endl;
                    cout << "Total: " << DealerTotal << endl;
                }

                if (PlayerTotal > DealerTotal && PlayerTotal <= 21)
                {
                    cout << "\nPlayer Wins! Congratulations!" << endl;
                    Wins++;
                }
                else if (DealerTotal > PlayerTotal && DealerTotal <= 21)
                {
                    cout << "\nDealer wins! Better luck next time!" << endl;
                }
                else if (DealerTotal > 21 && PlayerTotal <= 21)
                {
                    cout << "\nPlayer Wins! Congratulations!" << endl;
                    Wins++;
                }
                else if (PlayerTotal > 21 && DealerTotal <= 21)
                {
                    cout << "\nDealer wins! Better luck next time!" << endl;
                }



            }
            finished = true;
        }
        //logic to deal with stand option
        else if (answer == "2")
        {
            DisplayDealerHand(deck, DealerTotal);

            //Reveal the dealers hand and determine the winner
            while (DealerTotal <= 16)
            {
                cout << "\nDealer hits:" << endl;
                Card = deck[iCount].value + " of " + deck[iCount].suit;
                DealerTotal = DealerTotal + DetermineRank(deck[iCount].value, DealerTotal);
                iCount++;

                cout << Card << endl;
                cout << "Total: " << DealerTotal << endl;
            }

            if (DealerTotal > 21)
            {
                cout << "\nDealer busts:" << endl;
                cout << "\nPlayer Wins! Congratulations!" << endl;
                Wins++;
                finished = true;
            }
            else
            {
                //Determine winner based on points
                if (PlayerTotal > DealerTotal && PlayerTotal <= 21)
                {
                    cout << "\nDealer stands: " << endl;
                    cout << "\nPlayer Wins! Congratulations!" << endl;
                    Wins++;
                }
                else if (DealerTotal > PlayerTotal && DealerTotal <= 21)
                {
                    cout << "\nDealer stands: " << endl;
                    cout << "\nDealer Wins! Better luck next time!" << endl;
                }
                else
                {
                    cout << "\nDealer stands: " << endl;
                    cout << "DRAW" << endl;
                }
                finished = true;
            }
        }


    }


}

void DisplayWins()//Function to diplay the win %
{
    cout << "-----------------------------------------------------" << endl;
    cout <<left << setw(20) << "Games Played:" << left << setw(20) << "Wins:" << left << setw(20) << "Win%:" << endl;
    cout << "-----------------------------------------------------" << endl;
    double winRate = (double)Wins / GamesPlayed * 100;
    cout << left << setw(20) << GamesPlayed << left << setw(20) << Wins << left << setw(20) << setprecision(2) << winRate << endl;
}

void DisplayRules(void)//Function to display the rules of the game
{
    string myText;

    //Read from the textfile
    ifstream MyReadFile("Rules.txt");

    // Use a while loop together with the getline() function to read the file line by line
    while (getline(MyReadFile, myText))
    {
        cout << myText << endl;
    }
    cout << endl;

    //Close the file
    MyReadFile.close();
}

void DisplayMenu(void)//Function to display the menu to the user
{
    string myText;
    cout << endl;

    //Read from the textfile
    ifstream MyReadFile("Menu.txt");

    // Use a while loop together with the getline() function to read the file line by line
    while (getline(MyReadFile, myText))
    {
        cout << myText << endl;
    }
    cout << endl;

    //Close the file
    MyReadFile.close();
}

int main()
{
    //Arrays containing values and suits for cards
    string arrSuits[4] = {"HEARTS", "CLUBS", "DIAMONDS", "SPADES"};
    string arrValues[13] = {"ACE", "2", "3", "4", "5", "6", "7", "8", "9", "10", "JACK", "QUEEN", "KING"};

    //array of the Cards struct
    Cards deck[52];

    string *suitPtr = arrSuits;
    string *valuePtr = arrValues;

    bool finished = false;
    int choice;

    //Heading
    cout << "Creative Project 2023\nEugene Holt\n45613192" << endl;
    cout << "\nWelcome to BlackJack Mania!" << endl;

    //do-while loop used to deal with user choices
    do
    {
        DisplayMenu();

        cout << "Select a menu option: ";
        cin >> choice;
        cout << endl;

        //while loop used for input validation
        while (choice < 1 || choice > 4)
        {
            cout << "Invalid input, try again!\n";
            cout << "\nSelect a menu option: ";
            cin >> choice;
            cout << endl;
        }

        //Switch statement used to deal with user choice
        switch (choice)
        {
            case 1:
                {
                    DisplayRules();
                    break;
                }
            case 2:
                {
                    //Populate the deck of cards
                    MakeDeck(deck, suitPtr, valuePtr);

                    //Shuffle the deck
                    ShuffleDeck(deck);

                    //Play the game
                    PlayGame(deck);
                    break;
                }
            case 3:
                {
                    DisplayWins();
                    break;
                }
            default:
                {
                    cout << "Thank you for playing!" << endl;
                    finished = true;
                    break;
                }

        }
    }while (finished == false);

    return 0;
}
