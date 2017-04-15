// Babak Adeli
// CISP 400 
// Due: 11/28/2016
// Characters of the West

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Bonus Greets user based on time of day
// Bonus Created a function to clear the screen
// Bonus created a function to have the user press enter to continue.  this pauses the game and lets the user read the content
// Bonus cardsharp gets 52 when he cheats, best card in the game

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#include <iostream>

//for random
#include <stdlib.h>

#include <vector>

using namespace std;

//function prototypes
void clearScreen();
void greetUser();
void pressEnter(string begCont);
void playGame();
void shootout();

//vector of used cards
std::vector<int> usedCardVec;

//global variables
string userSelect;
string ignore;
bool shootOut;


//list of random first and last names for the characters
const int numOfNames = 10;
string randFirstNames[numOfNames] = { "Billy", "Jon", "Jimmy", "Frankie", "Woody", "Buzz", "Speedy", "Donald", "Sheldon" } ;
string randLastNames[numOfNames] = { "QuickShot", "Lazy", "TheKid", "WoodPecker", "LightYear", "HalfWit", "Bandit", "Duck", "TheDrunk" };



//abstract parent person class
class Person
{
protected:
	string firstName;
	string lastName;
	int gamesWon;
	static int randomSeed;
public:
	//constructor function
	Person();

	//destructor function
	~Person();

	//accessor functions
	string getFirstName();
	string getLastName();
	int getGamesWon();

	//mutator functions
	void setFirstName(string fName);
	void setLastName(string lName);
	void wonGame();
	void playerDied();

	//show();
	//drink();	
};

//for random seed
int Person::randomSeed = 1;


//constructor
Person::Person()
{
	//get a random first name
	srand(time(NULL)+randomSeed++);
	int fNameNumber = (rand()+randomSeed++) % (numOfNames - 1);
	setFirstName(randFirstNames[fNameNumber]);

	//get a random last name
	srand(time(NULL)+randomSeed++);
	int lNameNumber = (rand()+randomSeed++) % (numOfNames - 1);
	setLastName(randLastNames[lNameNumber]);

	//start games won at zero
	gamesWon = 0;
}

//destructor function
Person::~Person() {}


//accessors
string Person::getFirstName()
{
	return firstName;
}

string Person::getLastName()
{
	return lastName;
}

int Person::getGamesWon()
{
	return gamesWon;
}

//mutators
void Person::setFirstName(string fName)
{
	firstName = fName;
}

void Person::setLastName(string lName)
{
	lastName = lName;
}

void Person::wonGame()
{
	gamesWon = gamesWon + 1;
}

void Person::playerDied()
{
	//get a random first name
	srand(time(NULL)+randomSeed++);
	int fNameNumber = (rand()+randomSeed++) % (numOfNames - 1);
	setFirstName(randFirstNames[fNameNumber]);

	//get a random last name
	srand(time(NULL)+randomSeed++);
	int lNameNumber = (rand()+randomSeed++) % (numOfNames - 1);
	setLastName(randLastNames[lNameNumber]);

	//start games won at zero
	gamesWon = 0;
}



//gunslinger child
class Gunslinger : public Person
{
private:
	int notches;
public:
	Gunslinger();
	int getNotces();
	void incrementNotches();
	int draw();
	int play();
};

//constructor function 
Gunslinger::Gunslinger()
{
	//start off at 0 notches
	notches = 0;
}

int Gunslinger::getNotces()
{
	return notches;
}

//when gunslinger kills someone, he gets a notch
void Gunslinger::incrementNotches()
{
	notches += 1;
}

//get the gunslingers draw value
int Gunslinger::draw()
{
	srand(time(NULL)+randomSeed++);
	int drawValue = (rand()+randomSeed++) % 10 + 1;
	return drawValue;
}

int Gunslinger::play()
{
	bool valid = 0;
	int cardDealt;

	while(!valid)
	{
		valid = 1;
		srand(time(NULL)+randomSeed++);
		cardDealt = (rand()+randomSeed++) % 52 + 1;

		for (unsigned int i = 0; i < usedCardVec.size(); i++)
		{
			if (to_string(usedCardVec[i]) == to_string(cardDealt))
			{
				valid = 0;
			}
		}

	}
	usedCardVec.push_back(cardDealt);
	return cardDealt;
}


//pokerplayer child
class PokerPlayer : public Person
{
public:
	int play();
};

int PokerPlayer::play()
{
	bool valid = 0;
	int cardDealt;

	while(!valid)
	{
		valid = 1;
		srand(time(NULL)+randomSeed++);
		cardDealt = (rand()+randomSeed++) % 52 + 1;

		for (unsigned int i = 0; i < usedCardVec.size(); i++)
		{
			if (to_string(usedCardVec[i]) == to_string(cardDealt))
			{
				valid = 0;
			}
		}

	}
	usedCardVec.push_back(cardDealt);
	return cardDealt;
}

class CardSharp : public Person
{
public:
	int draw();
	int play();	
};

int CardSharp::draw()
{
	srand(time(NULL)+randomSeed++);
	int drawValue = (rand()+randomSeed++) % 15 + 5;
	return drawValue;
}

int CardSharp::play()
{
	bool valid = 0;
	int cardDealt;
	int checkCheat;
	bool cheated = 0;

	//25% of the time, cardsharp cheats.  this checks for 25%
	srand(time(NULL)+randomSeed++);
	checkCheat = (rand()+randomSeed++) % 4 + 1;

	//25% of the time, checkcheat will be 1
	if (to_string(checkCheat) == "1")
	{
		//don't deal a new card
		valid = 1;
		cheated = 1;
		shootOut = 1;

		//sort the vector
		//sort(usedCardVec.begin(), usedCardVec.end())

		//cardsharp cheats and takes the largest card used
		//cardDealt = usedCardVec.end();

		// bonus  make it the largest card possible (pulls out a fake 52 so it doesn't come from the deck)
		cardDealt = 52;

		//return the card

		return cardDealt;

	}

	

	while(!valid)
	{
		valid = 1;
		srand(time(NULL)+randomSeed++);
		cardDealt = (rand()+randomSeed++) % 52 + 1;

		for (unsigned int i = 0; i < usedCardVec.size(); i++)
		{
			if (to_string(usedCardVec[i]) == to_string(cardDealt))
			{
				valid = 0;
			}
		}

	}
	//only add card to used card vec if he didn't cheat
	if (!cheated)
		{
			usedCardVec.push_back(cardDealt);
		}
	return cardDealt;
}

//bartender child
class Bartender : public Person
{
public:
	void draw();
	int play();
};

void Bartender::draw()
{
	clearScreen();
	cout << firstName << " " << lastName << " poured a round of drinks.\n";
	//pressEnter("continue");
}

int Bartender::play()
{
	bool valid = 0;
	int cardDealt;

	while(!valid)
	{
		valid = 1;
		srand(time(NULL)+randomSeed++);
		cardDealt = (rand()+randomSeed++) % 52 + 1;

		for (unsigned int i = 0; i < usedCardVec.size(); i++)
		{
			if (to_string(usedCardVec[i]) == to_string(cardDealt))
			{
				valid = 0;
			}
		}

	}
	usedCardVec.push_back(cardDealt);
	return cardDealt;
}








int main()
{
	greetUser();
	playGame();
	

}

void playGame()
{
	bool gameOver = 0;
	int gunCard, pokerCard, sharpCard, barCard;

	//start by creating four characters
	Gunslinger Gunslinger;
	PokerPlayer PokerPlayer;
	CardSharp CardSharp;
	Bartender Bartender;

	//introduce them to the user
	clearScreen();
	cout << Gunslinger.getFirstName() << " " << Gunslinger.getLastName() << " has joined the game.\n";
	cout << PokerPlayer.getFirstName() << " " << PokerPlayer.getLastName() << " has joined the game.\n";
	cout << CardSharp.getFirstName() << " " << CardSharp.getLastName() << " has joined the game.\n";
	cout << Bartender.getFirstName() << " " << Bartender.getLastName() << " has joined the game.\n\n";
	pressEnter("continue");

	//start the game
	while (!gameOver)
	{
		//turn shootout off
		shootOut = 0;

		int pourRound;

		//rand(time(NULL));
		srand(time(NULL));
		pourRound = (rand()) % 10 + 1;



		if ( to_string(pourRound) == "7" );
		{
			Bartender.draw();
			pressEnter("continue");
		}

		// each player gets a card
		gunCard = Gunslinger.play();
		pokerCard = PokerPlayer.play();
		sharpCard = CardSharp.play();
		barCard = Bartender.play();

		//display the cards
		clearScreen();
		cout << Gunslinger.getFirstName() << " " << Gunslinger.getLastName() << " has drawn the " << gunCard << ".\n";
		cout << PokerPlayer.getFirstName() << " " << PokerPlayer.getLastName() << " has drawn the " << pokerCard << ".\n";
		cout << CardSharp.getFirstName() << " " << CardSharp.getLastName() << " has drawn the " << sharpCard << ".\n";
		cout << Bartender.getFirstName() << " " << Bartender.getLastName() << " has drawn the " << barCard << ".\n\n";
		pressEnter("continue");
		clearScreen();



		//gunslinger wins
		if ( (gunCard > pokerCard) && (gunCard > sharpCard) && (gunCard > barCard) )
		{
			Gunslinger.wonGame();
			cout << Gunslinger.getFirstName() << " " << Gunslinger.getLastName() << " has won the round.\n";
		}

		else if ( (pokerCard > gunCard) && (pokerCard > sharpCard) && (pokerCard > barCard) )
		{
			PokerPlayer.wonGame();
			cout << PokerPlayer.getFirstName() << " " << PokerPlayer.getLastName() << " has won the round.\n";
		}

		else if ( (sharpCard > gunCard) && (sharpCard > pokerCard) && (sharpCard > barCard) )
		{
			CardSharp.wonGame();
			cout << CardSharp.getFirstName() << " " << CardSharp.getLastName() << " has won the round.\n";

		}

		else 
		{
			Bartender.wonGame();
			cout << Bartender.getFirstName() << " " << Bartender.getLastName() << " has won the round.\n";
		}

		pressEnter("continue");


		if (shootOut)
		{
			if ( Gunslinger.draw() > CardSharp.draw() )
			{
				cout << "Uh oh! Looks like something smells fishy.\n";
				cout << Gunslinger.getFirstName() << " " << Gunslinger.getLastName() << " has caught " << CardSharp.getFirstName() << " " << CardSharp.getLastName() << " cheating!\n";
				cout << "Looks like its going to be an old fashioned shoot out!  Let's see who wins.\n";
				cout << "Pew Pew!  Bang! Bang!\n\n";
				pressEnter("continue");
				clearScreen();

				//~Gunslinger();

				cout << "It looks like " << Gunslinger.getFirstName() << " " << Gunslinger.getLastName() << " is a goner.\n";
				cout << "Let's see who is going to take his spot in the game.\n";
				pressEnter("continue");
				clearScreen();

				Gunslinger.playerDied();

				//Gunslinger Gunslinger;
				cout << Gunslinger.getFirstName() << " " << Gunslinger.getLastName() << " has joined the game.\n";
			}

			else if ( Gunslinger.draw() < CardSharp.draw() )
			{
				cout << "Uh oh! Looks like something smells fishy.\n";
				cout << Gunslinger.getFirstName() << " " << Gunslinger.getLastName() << " has caught " << CardSharp.getFirstName() << " " << CardSharp.getLastName() << " cheating!\n";
				cout << "Looks like its going to be an old fashioned shoot out!  Let's see who wins.\n";
				cout << "Pew Pew!  Bang! Bang!\n\n";
				pressEnter("continue");
				clearScreen();

				//~CardSharp();

				cout << "It looks like " << CardSharp.getFirstName() << " " << CardSharp.getLastName() << " is a goner.\n";
				cout << "Let's see who is going to take his spot in the game.\n";
				pressEnter("continue");
				clearScreen();

				CardSharp.playerDied();

				//CardSharp CardSharp;
				cout << CardSharp.getFirstName() << " " << CardSharp.getLastName() << " has joined the game.\n\n";
			}
		}






		cout << "The Score: \n";
		cout << "----------------------------\n";
		cout << Gunslinger.getFirstName() << " " << Gunslinger.getLastName() << ": " << Gunslinger.getGamesWon() << "\n";
		cout << PokerPlayer.getFirstName() << " " << PokerPlayer.getLastName() << ": " << PokerPlayer.getGamesWon() << "\n";
		cout << CardSharp.getFirstName() << " " << CardSharp.getLastName() << ": " << CardSharp.getGamesWon() << "\n";
		cout << Bartender.getFirstName() << " " << Bartender.getLastName() << ": " << Bartender.getGamesWon() << "\n\n";
		pressEnter("continue");

		if ( usedCardVec.size() > 48 )
		{
			gameOver = 1;
		}


	} //ends the while loop

	//decide on the winner
	clearScreen();
	if ( (Gunslinger.getGamesWon() > PokerPlayer.getGamesWon()) && (Gunslinger.getGamesWon() > CardSharp.getGamesWon()) && (Gunslinger.getGamesWon() > Bartender.getGamesWon()) )
	{
		cout << "The winner is " << Gunslinger.getFirstName() << " " << Gunslinger.getLastName() << "\n";
	}

	else if ( (PokerPlayer.getGamesWon() > Gunslinger.getGamesWon()) && (PokerPlayer.getGamesWon() > CardSharp.getGamesWon()) && (PokerPlayer.getGamesWon() > Bartender.getGamesWon()) )
	{
		cout << "The winner is " << PokerPlayer.getFirstName() << " " << PokerPlayer.getLastName() << "\n";
	}

	else if ( (CardSharp.getGamesWon() > Gunslinger.getGamesWon()) && (CardSharp.getGamesWon() > PokerPlayer.getGamesWon()) && (CardSharp.getGamesWon() > Bartender.getGamesWon()) )
	{
		cout << "The winner is " << CardSharp.getFirstName() << " " << CardSharp.getLastName() << "\n";
	}

	else if ( (Bartender.getGamesWon() > Gunslinger.getGamesWon()) && (Bartender.getGamesWon() > PokerPlayer.getGamesWon()) && (Bartender.getGamesWon() > CardSharp.getGamesWon()) ) 
	{
		cout << "The winner is " << Bartender.getFirstName() << " " << Bartender.getLastName() << "\n";
	}

	else 
	{
		cout << "It's a tie!\n";
	}

	pressEnter("continue");

	cout << "Thanks for playing\n";


} // ends the function




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





















// bonus function to clear the screen
void clearScreen()
{
	cout << string(100, '\n');
}

// bonus function to get the user to press enter to continue
void pressEnter(string begCont)
{
	cout << "Press enter to " << begCont << ".\n";
	getline(cin, ignore);
	clearScreen();
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
	cout << "Welcome to Babak's Characters of the West.\n";
	cout << "Watch as the the sharpest shooters in the wild west gather 'round for a game of cards.\n";
	cout << "Just make sure to keep your hat on!\n\n";
	pressEnter("begin");
}