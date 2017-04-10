// Babak Adeli
// CISP 400 
// Due: 11/14/2016
// Hokeemon

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Bonus Greets user based on time of day
// Bonus Created a function to clear the screen
// Bonus uses try throw block for input validation
// Bonus created a function to have the user press enter to continue.  this pauses the game and lets the user read the content
// Bonus option to make the hokeemon fight
// Bonus displays pokemon moods
// Bonus counts how many turns hokeemon was happy

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



#include <iostream>

//for random
#include <stdlib.h>

using namespace std;





//function prototypes
void clearScreen();
void greetUser();
void pressEnter(string begCont);
void upDate();

//global variables
string userSelect;
string ignore;

//happy starts at 0 turns
int pikaHappy = 0;
int mewHappy = 0;


//bool to loop the menu while user wants to play
bool exitProgram = 0;



class Creature
{
private:
	void passTime();
protected:
	string name;
	int hunger;
	int boredom;
	string talk;
	static int j;


public:
	
	//accessor functions
	string getName();
	int getHunger();
	int getBoredom();
	string getTalk();

	//mutator function
	void setName(string cName);
	void setHunger(int cBore);
	void setBoredom(int cBore);
	void setTalk(string cTalk);

	//constructor function
	Creature();

	void listen();
	void play();
	void feed();
	void classUpDate();
	
};

int Creature::j=1;

Creature::Creature()
{
	setName("");
	setBoredom(0);
	setHunger(0);
	setTalk("");
}

//accessor functions
string Creature::getName()
{
	return name;
}

int Creature::getHunger()
{
	return hunger;
}

int Creature::getBoredom()
{
	return hunger;
}

string Creature::getTalk()
{
	return talk;
}

//mutator functions
void Creature::setName(string cName)
{
	name = cName;
}

void Creature::setHunger(int cHung)
{
	hunger = cHung;
}

void Creature::setBoredom(int cBore)
{
	boredom = cBore;
}

void Creature::setTalk(string cTalk)
{
	talk = cTalk;
}


//listen function
void Creature::listen()
{
	//the creature talks
	clearScreen();
	//display the hokeemons talk
	cout << talk << "\n";
	//display the hokeemons hunger
	cout << "The hokeemon's hunger level is " << hunger << "\n";
	//display the hokemons boredom
	cout << "The hokeemon's boredom level is " << boredom << "\n";
	// bonus displays hokeemon moods based on boredom
	cout << "This hokeemon is ";

	if (boredom < 5)
	{
		cout << "happy!\n";
	}
	else if ((boredom > 4) && (boredom < 10))
	{
		cout << "OK.\n";
	}
	else if ((boredom > 9) && (boredom < 15))
	{
		cout << "frustrated.\n";
	}
	else 
	{
		cout << "MAD!\n";
	}



	pressEnter("continue");
}

//play function
void Creature::play()
{
	//boredom is decremented by 4 each time it is played with
	const int BOREDECREMENT = 4;

	clearScreen();
	cout << talk << "\n";
	cout << "The hokeemon had so much fun! It is clearly less bored now.\n";
	boredom = boredom - BOREDECREMENT;

	//boredom can't be below 0
	if (boredom < 0)
	{
		boredom = 0;
	}

	upDate();

	pressEnter("continue");
}


void Creature::feed()
{
	//hunger is decremented by 4 each time it eats
	const int HUNGDECREMENT = 4;

	clearScreen();
	cout << talk << "\n";
	cout << "The hokeemon gobbled that right up! It must have been hungry.\n";
	hunger = hunger - HUNGDECREMENT;

	//hunger can't be below 0
	if (hunger < 0)
	{
		hunger = 0;
	}
	upDate();

	pressEnter("continue");
}

void Creature::classUpDate()
{
	passTime();
}



void Creature::passTime()
{
	hunger = hunger + 1;
	boredom = boredom + 1;

	if (hunger > 9)
	{
		clearScreen();
		cout << "Oh no... looks like my beloved " << name << " has died of starvation!\n";
		cout << "I am so sad. *SNIFFLE* I need to be alone. *SNIFFLE* Its time for you to go now.\n";
		exitProgram = 1;
	}
}





//Pikachu child
class Pikachu : public Creature
{
public:
	Pikachu();
};

// Pikachu constructor
Pikachu::Pikachu()
{
	//maximum boredom and hunger values are 9
	const int MAXSTARTBOREHUNG = 9;
	
	//name the creature 
	setName("Pikachu");
	//name = "Pikachu";

	//get the random starting hunger value
	srand(time(NULL)+j++);
	setHunger((rand() +j++) % MAXSTARTBOREHUNG);

	//get the random starting boredom value
	srand(time(NULL)+j++);
	setBoredom ((rand() +j++) % MAXSTARTBOREHUNG);

	//what pikachu says
	setTalk("Pika....CHU!");
	
}



//MewTwo child
class MewTwo : public Creature
{
public:
	MewTwo();
};



// MewTwo constructor
MewTwo::MewTwo()
{
	//maximum boredom and hunger values are 9
	const int MAXSTARTBOREHUNG = 9;
	
	//name the creature
	name = "MewTwo";

	//get the random starting hunger value
	srand(time(NULL)+j++);
	setHunger((rand() +j++) % MAXSTARTBOREHUNG);

	//get the random starting boredom value
	srand(time(NULL)+j++);
	setHunger((rand() +j++) % MAXSTARTBOREHUNG);

	//what mewtwo says
	setTalk("I am MewTwo.  The greatest Hokeemon of them all!");
}







//instantiate the child classes, making the hokeemon
Pikachu Pikachu;
MewTwo MewTwo;


int main()
{

	//boolean to get valid input from the user
	bool inputValid;
	

	//start by greeting the user
	greetUser();

	while (!exitProgram)
	{
		//print the main menu
		clearScreen();
		cout << "************************************************************************ \n";
		cout << "MAIN MENU\n";
		cout << "************************************************************************ \n";
		cout << "Enter (1) to listen to the Hokeemon\n";
		cout << "Enter (2) to play with the Hokeemon\n";
		cout << "Enter (3) to feed the Hokeemon\n";
		cout << "Enter (4) to make the Hokeemon fight\n";
		cout << "Enter (5) to quit\n";
		cout << "************************************************************************ \n";
		inputValid = 0;
		
		//imput validation to for the menu
		while (!inputValid)
		{
			inputValid = 1;
			// bonus try throw block
				try
			{
				//get the selection from the user
				getline(cin, userSelect);

				if ( (stoi(userSelect) < 0) || (stoi(userSelect) > 5) )
				{
					throw 1;
				}
			} 
			catch (...)
			{
				cout << "Error.  Please select a valid option.\n";
				inputValid = 0;
			}
		}



		//user selects to listen to hokeemon
		if (userSelect == "1")
		{
			clearScreen();

			//find out which hokeemon user wants to listen to
			cout << "Would you like to listen to Pikachu or MewTwo?\n";
			cout << "(Enter (1) for Pikachu or (2) for MewTwo)\n";
			getline(cin, userSelect);

			if (userSelect == "1")
			{
				Pikachu.listen();
			}

			else if (userSelect == "2")
			{
				MewTwo.listen();
			}

			else
			{
				cout << "That is not a valid option.\n";
				pressEnter("continue");
			}


		}

		//user selects to play with hokeemon
		else if (userSelect == "2")
		{
			clearScreen();

			//find out which hokeemon user wants to listen to
			cout << "Would you like to play with Pikachu or MewTwo?\n";
			cout << "(Enter (1) for Pikachu or (2) for MewTwo)\n";
			getline(cin, userSelect);

			if (userSelect == "1")
			{
				Pikachu.play();
			}

			else if (userSelect == "2")
			{
				clearScreen();
				cout << "MewTwo: Hahaha silly human. MewTwo does not play.\n";
				pressEnter("continue");
			}

			else
			{
				cout << "That is not a valid option.\n";
				pressEnter("continue");
			}


		}
		//user selects to feed the hokeemon
		else if (userSelect == "3")
		{
			clearScreen();

			//find out which hokeemon user wants to listen to
			cout << "Would you like to feed the Pikachu or MewTwo?\n";
			cout << "(Enter (1) for Pikachu or (2) for MewTwo)\n";
			getline(cin, userSelect);

			if (userSelect == "1")
			{
				Pikachu.feed();
			}

			else if (userSelect == "2")
			{
				MewTwo.feed();
			}

			else
			{
				cout << "That is not a valid option.\n";
				pressEnter("continue");
			}


		}

		// bonus to make the hokeemon fight
		else if (userSelect == "4")
		{
			clearScreen();
			cout << "So you're going to make the hokeemon fight, huh?  I'd strongly advise against it.\n";
			pressEnter("continue");
			cout << "OK, OK, if you insist!  Just remember, I warned you.\n";
			pressEnter("continue");
			cout << "When Babak isn't looking, let the Pikachu out.\n";
			pressEnter("open Pikachu's cage");
			cout << "Pikachu: Pika Pika!!\n";
			cout << "Ok, now carefully let the MewTwo out.\n I... uhhh... need to go now.  You're on your own from here kid.\n";
			pressEnter("release the MewTwo");
			cout << "MewTwo: Grave mistake human. Haha.\n";
			cout << "(The MewTwo has destroyed everything.  The world belongs to him now.  Game Over)\n";
			pressEnter("continue");
			exitProgram = 1;

		}

		// user exits the program
		else if (userSelect == "5")
		{
			cout << "Thanks for playing. Come visit the Hokeemon again soon!\n";
			exitProgram = 1;
		}

	}
	cout << "The Pikachu was happy for " << pikaHappy << " turns.\n";
	cout << "The MewTwo was happy for " << mewHappy << " turns.\n";
}
	



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

// bonus function to greet the user based on time of day
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
	cout << "Welcome to Babak's Hokeemon!\n";
	cout << "Play, listen to, and feed rare and not so rare Hokeemon.\n";
	cout << "Make sure to keep them alive by feeding them.... and remember, they do have feelings.\n\n";
	pressEnter("begin");
}


void upDate()
{
	

	// bonus counts how many turns hokeemon was happy
	if (Pikachu.getBoredom() < 5)
	{
		pikaHappy = pikaHappy + 1;
	}

	if (MewTwo.getBoredom() < 5)
	{
		mewHappy = mewHappy + 1;
	}

	Pikachu.classUpDate();
	MewTwo.classUpDate();
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
