// Babak Adeli
// CISP 400 
// Due: 10/31/2016
// BlackJack

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Bonus There is a wagering system
// Bonus The suite of each card is displayed
// Bonus Greets user based on time of day
// Bonus Created a seperate clear screen function
// Bonus Uses recursion ask the user to hit or stay
// Bonus Allows for repeated gameplay when the user runs out of money
// Bonus Makes sure no card is repeated
// Bonus Aces can be ones or elevens
/////////////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

using namespace std;

class Card
{
private:
	string cardName;
	int cardValue;
	string cardSuite;

public:
	
	//constructor
	Card();

	//overload constructor
	Card(string cardName, int cVal, string cSuite);

	//deconstructor
	~Card();

	//accessor functions
	string getCardName();
	int getCardValue();
	string getCardSuite();

	//mutator functions
	void setCardName(string cName);
	void setCardValue(int cVal);
	void setCardSuite(string cSuite);
};

//global variables
//string to place the ignored input.  "press enter to continue"
string ignore;

//temp variables to pass through into the class from multiple functions
string cName;
int cVal;
string cSuite;

//place to store user's menu selections
string userSelect;

//keeps track of the users total
int userScore;

//keeps track of the dealer's total
int dealersScore;

//the user stargs with $100
int userPocket = 100;

//how much the user wagers
int wager;

//bool duplicateCard;

//vector of used cards
std::vector<Card> usedCardVec;

//vector of user's cards
std::vector<Card> usersHandVec;

//vector of dealer's hand
std::vector<Card> dealersHandVec;



//function prototypes
void clearScreen();
void greetUser();
void startNewGame();
void dealCard();
void displayHand();
void hitOrStary();
void win();
void lose();
void dealCompCard();
void dealersTurn();




int main()
{
	//bool to exit or not exit program
	bool exit = 0;

	//get the wager from the user
	string wagerString;

	clearScreen();
	greetUser();

	while (!exit)
	{
		//print the main menu
		clearScreen();
		cout << "************************************************************************ \n";
		cout << "MAIN MENU\n";
		cout << "************************************************************************ \n";
		cout << "Enter (1) to play.\n";
		cout << "Enter (2) to exit.\n";
		cout << "************************************************************************ \n";
		cout << "You currently have: $" << userPocket << "\n";

		//get the selection from the user
		getline(cin, userSelect);

		//start new game
		if (userSelect == "1")
		{
			clearScreen();

			//show them how much they have and ask for the wager
			cout << "You currently have: $" << userPocket << "\n\n";
			cout << "How much do you wager?\n$";
			getline(cin, wagerString);
			wager = stoi(wagerString);

			startNewGame();
		}

		else if (userSelect == "2")
		{
			exit = 1;
		}

	}

}









//constructor function to blank
Card::Card()
{
	cardName = "";
	cardValue = 0;
	cardSuite = "";
}

//overload constructor
Card::Card(string cName, int cVal, string cSuite)
{
	cardName = cName;
	cardValue = cVal;
	cardSuite = cSuite;
}

//deconstructor function
Card::~Card(){}


//accessor functions
string Card::getCardName()
{
	return cardName;
}

int Card::getCardValue()
{
	return cardValue;
}

string Card::getCardSuite()
{
	return cardSuite;
}

//mutator functions
void Card::setCardName(string cName)
{
	cardName = cName;
}

void Card::setCardValue(int cVal)
{
	cardValue = cVal;
}

void Card::setCardSuite(string cSuite)
{
	cardSuite = cSuite;
}



//function to clear the screen
void clearScreen()
{
	cout << string(100, '\n');
}

void greetUser()
{
	clearScreen();
	long timeSeconds;

    //Get the current time
  	time (&timeSeconds);

    //Convert the time into string format
  	string seconds = ctime(&timeSeconds);

 	//Extract the hour info
 	string hour = seconds.substr(11, 2);

  	//Convert hour into an unsigned integer (we will need it for comparision)
  	unsigned hourNumber = stoi(hour);

  
 	cout <<  "\nGood ";

 	//Between midnight and 5 AM
	if (hourNumber < 5) 
    	{
    		cout << "Morning! Or should I say Night?\n";
    	}
  
  	//Between 5 AM and 12 Noon
    else if (hourNumber < 12)
    {
    	cout << "Morning!" << endl;
    }
    
    //Between 12 Noon and 5 PM
  	else if (hourNumber < 17)
    {
    	cout << "Afternoon!\n";
    }

 	 //Between 5 PM and midnight
    else
    {
    	cout << "Evening!\n";
    }

    //welcome message
 	cout << "\n";
	cout << "Welcome to Babak's Game of BlackJack!\n";
	cout << "Get as close as you can to 21 without busting.\n";
	cout << "Can you beat the computer?  Lets find out now!\n\n";
	cout << "Press enter to begin.\n";
	getline(cin, ignore);
	clearScreen();
}

void startNewGame()
{
	clearScreen();
	//start the user at zero
	userScore = 0;

	//clear all of the vectors
	usedCardVec.clear();
	usersHandVec.clear();
	dealersHandVec.clear();

	//dealer gets a card
	dealCompCard();
	cout << "test1";

	//deal two cards
	dealCard();
	dealCard();

	//display the user's hand
	displayHand();

	//check for blackjack
	if (userScore == 21)
	{
		cout << "BlackJack! ";
		win();
		return;
	}
	
	else 
	{
		hitOrStary();
	}



	//check for a bust
	if (userScore > 21)
	{
		cout << "Bust! ";
		lose();
		return;
	}



	//after the user stays, the dealer takes his turn
	dealersTurn();

	//return if busted
	if (dealersScore > 21)
	{
		return;
	}

	//show the hand
	displayHand();

	if (userScore > dealersScore)
	{
		win();
		return;
	}

	else if (userScore < dealersScore)
	{
		lose();
		//return();
	}

	else
	{
		cout << "Its a push!\n\n";
		cout << "Press enter to continue.\n";
		getline(cin, ignore);
		//return();
	}

}



void dealCard()
{
	//to make sure the card isn't duplicated
	cout << "test";
	bool duplicateCard = 1;

	while (duplicateCard)
	{
		duplicateCard = 0;
	
		//shuffles for the 13 types of cards ace-king
		srand(time(NULL));
		int randVal = rand() % 13 + 1;

		//shuffles for the 4 suites spades, clubs, hearts, diamonds
		srand(time(NULL));
		int randSuite = rand() % 3;


		//assigns a value and name to the card
		if (randVal == 1)
		{
			cName = "Ace";
			cVal = 11;
		}

		else if (randVal == 11)
		{
			cName = "Jack";
			cVal = 10;
		}

		else if (randVal == 12)
		{
			cName = "Queen";
			cVal = 10;
		}

		else if (randVal == 13)
		{
			cName = "King";
			cVal = 10;
		}

		else 
		{
			cName = to_string(randVal);
			cVal = randVal;
		}

		//assigns a suit to the card
		if (randSuite == 0)
		{
			cSuite = "Spades";
		}

		else if (randSuite == 1)
		{
			cSuite = "Clubs";
		}

		else if (randSuite == 2)
		{
			cSuite = "Hearts";
		}

		else 
		{
			cSuite = "Diamonds";
		}


		//check to make sure the card hasn't been assigned already
		for (unsigned int i = 0; i < usedCardVec.size(); i++)
		{
			if ((usedCardVec[i].getCardName() == cName) && (usedCardVec[i].getCardSuite() == cSuite))
			{
				duplicateCard = 1;
			}
		}
	}


	//save it if it hasn't been duplicated

	//creates a new instance of the card class
	Card newCard(cName, cVal, cSuite);

	//puts the new card into the user's hand
	usersHandVec.push_back(newCard);

	//also puts it in the used card vector so it cant be used again
	usedCardVec.push_back(newCard);

	//tell the user what they have been dealt
	clearScreen();
	cout << "You have been dealt the " << cName << " of " << cSuite << ".\n";
	cout << "Press enter to continue.\n";
	getline(cin, ignore);
}




void displayHand()
{
	userScore = 0;
	dealersScore = 0;

	clearScreen();

	//display the dealer's card
	cout << "-------------------------\n";
	cout << "The dealer is showing:\n\n";
	for (unsigned int i = 0; i < dealersHandVec.size(); i ++)
	{
		//display the dealers cards
		cout << dealersHandVec[i].getCardName() << " of " << dealersHandVec[i].getCardSuite() << "\n";

		//count the cards
		dealersScore = dealersScore + dealersHandVec[i].getCardValue();
	}
	
	cout << "-------------------------\n";


	//display the user's hand hand
	cout << "Your hand is:\n\n";
	
	for (unsigned int i = 0; i < usersHandVec.size(); i++)
	{
		//display each card at a time
		cout << usersHandVec[i].getCardName() << " of " << usersHandVec[i].getCardSuite() << "\n";

		//count the cards while we are looping
		userScore = userScore + usersHandVec[i].getCardValue();
	}

	cout << "-------------------------\n\n";
	//display the dealer's and user's total
	cout << "The dealer's total is " << dealersScore << "\n";
	cout << "Your total is " << userScore << "\n\n";
}



void hitOrStary()
{
	//string to ask if the user wants to hit or stay
	string hitStay;

	clearScreen();
	displayHand();

	cout << "Would you like to hit or stay? (Enter (h) to hit or (s) to stay)\n";
	getline(cin, hitStay);

	//the user stays
	if ((hitStay == "s") || (hitStay == "S"))
	{
		return;
	}

	//the user hits
	else if ((hitStay == "h") || (hitStay == "H"))
	{
		//deal them another card
		dealCard();

		//display their hand after they are dealt a new card
		clearScreen();
		displayHand();


		//check for a bust
		if (userScore > 21)
		{
			//look for aces
			for (unsigned int i = 0; i < usersHandVec.size(); i++)
			{
				//turn the aces into ones
				if (usersHandVec[i].getCardValue() == 11)
				{
					usersHandVec[i].setCardValue(1);
				}
			}

			//recalculate users score
			userScore = 0;
			for (unsigned int i = 0; i < usersHandVec.size(); i++)
			{
				userScore = userScore + usersHandVec[i].getCardValue();
			}

			displayHand();


			//return them if they are still busted
			if (userScore > 21)
			{

				return;
			}
		}

		//recur hit or stay
		hitOrStary();
	}

	//the user enters something else
	else
	{
		cout << "That is not a valid choice. Please try again.\n";
		cout << "Press enter to continue.\n";
		getline(cin, ignore);

		hitOrStary();
	}

}

//message they receive if they wins
void win()
{
	userPocket = userPocket + wager;
	cout << "You win $" << wager << "!\n";
	cout << "\nPress Enter to continue.\n";
	getline(cin, ignore);
}


//message they receive if they lose
void lose()
{
	userPocket = userPocket - wager;
	cout << "You lose $" << wager << "!\n";
	cout << "\nPress Enter to continue.\n";
	getline(cin, ignore);


	//replenish their funds if they run out of money so they can keep playing
	if (userPocket == 0)
	{
		clearScreen();
		cout << "Uh oh... you are all out of cash.\n";
		cout << "Maybe you shouldn't take that trip to Vegas after all.\n";
		cout << "Look, I'll let you borrow some money. But, you better pay me back or else...\n";
		cout << "(Babak gave you $100!)\n";
		cout << "\nPress Enter to continue.\n";
		getline(cin, ignore);

		userPocket = 100;

	}
}



void dealCompCard()
{
	//to make sure the card isn't duplicated
	bool duplicateCard = 1;


	while (duplicateCard)
	{
		duplicateCard = 0;

		//shuffles for the 13 types of cards ace-king
		srand(time(NULL));
		int randVal = rand() % 13 + 1;

		//shuffles for the 4 suites Spades, clubs, hearts, diamonds
		srand(time(NULL));
		int randSuite = rand() % 3;
	



		//assigns a value and name to the card
		if (randVal == 1)
		{
			cName = "Ace";
			cVal = 11;
		}

		else if (randVal == 11)
		{
			cName = "Jack";
			cVal = 10;
		}

		else if (randVal == 12)
		{
			cName = "Queen";
			cVal = 10;
		}

		else if (randVal == 13)
		{
			cName = "King";
			cVal = 10;
		}

		else 
		{
			cName = to_string(randVal);
			cVal = randVal;
		}

		//assigns a suit to the card
		if (randSuite == 0)
		{
			cSuite = "Spades";
		}

		else if (randSuite == 1)
		{
			cSuite = "Clubs";
		}

		else if (randSuite == 2)
		{
			cSuite = "Hearts";
		}

		else 
		{
			cSuite = "Diamonds";
		}


		//check to make sure the card hasn't been assigned already
		for (unsigned int i = 0; i < usedCardVec.size(); i++)
		{
			if ((usedCardVec[i].getCardName() == cName) && (usersHandVec[i].getCardSuite() == cSuite))
			{
				duplicateCard = 1;
			}
		}
	}

	

	//save it if it hasn't been duplicated
	
	//creates a new instance of the card class
	Card newCard(cName, cVal, cSuite);

	//puts the new card into the dealer's hand
	dealersHandVec.push_back(newCard);

	//also puts it in the used card vector so it cant be used again
	usedCardVec.push_back(newCard);

	//tell the user what they have been dealt
	clearScreen();
	cout << "The dealer has been dealt the " << cName << " of " << cSuite << ".\n";
	cout << "Press enter to continue.\n";
	getline(cin, ignore);
	return;
}


void dealersTurn()
{
	dealersScore = 0;

	for (unsigned int i = 0; i < dealersHandVec.size(); i ++)
	{
		//count the cards
		dealersScore = dealersScore + dealersHandVec[i].getCardValue();
	}
	
	while (dealersScore < 17)
	{
		dealCompCard();
		dealersScore = 0;

		for (unsigned int i = 0; i < dealersHandVec.size(); i ++)
		{
			dealersScore = dealersScore + dealersHandVec[i].getCardValue();
		}
	}

	if (dealersScore > 21)
	{
		clearScreen();
		cout << "The dealer busts! ";
		win();
	}

}

// Peer Review Summary Form
// Complete and attach to the bottom of your source file and turn in to D2L.
//
// Reader: Ryan Wallace
// Recorder: Parag Raval
// Other: 
//
// Approx Time for this asignment: 12 hours
// Use the following ranking for the following:
// 5 - Sophisticated, 4 - Highly Competent, 3 - Competent, 2 - Not Yet Competent, 1 - Unacceptable 
// Solution Fit with Client Needs: 5
// User Friendliness: 5
// Comments and Documentation: 5 
// Overall Score: 5
