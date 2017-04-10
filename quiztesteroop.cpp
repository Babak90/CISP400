// Babak Adeli
// CISP 400 
// Due: 9/7/2016
// Resubmitted: 9/26/2016
// HW 2

/*//////////////////////////////////////////////////////////////////////////////////////////////////////
Bonus 1: Prints message based on score received. ASCII art saying good job! if the user gets 100%
Bonus 2: Saves the scores in a text file
Bonus 3: Asks the user if they wish to see previous test scores and displays them if the user wants
Bonus 4: Greets user based on time of day

*//////////////////////////////////////////////////////////////////////////////////////////////////////



#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//this is the questions class
class questions
{
public:
  string quest;
  string answa;
  string answb;
  string answc;
  string answd;
  string correct;
  
};

//function prototype
void timeOfDayGreeting();

int main()

{
	//declaring a temp struct to get input from the txtfile
	questions tempq = {
		"",
		"",
		"",
		"",
		"",
		"",
	};

	//initializing my vector and variables
	vector<questions> vecq;
	std::string response;
  	string compare = "0";
  	int totalasked = 0;
  	int gotright = 0;
  	int error = 0;
  	double percent = 0.00;

	//opening up the txt file
	ifstream questfile;
	questfile.open("questions.txt");

	//loop to put the txtfile into temp, then into the vector vecq. close the file when done
	if (questfile.is_open())
  	{
    	while (getline(questfile,tempq.quest))
    	{
      		getline (questfile,tempq.answa);
      		getline (questfile,tempq.answb);
      		getline (questfile,tempq.answc);
      		getline (questfile,tempq.answd);
      		getline (questfile,tempq.correct);
      		vecq.push_back(tempq);
   		}
    	questfile.close();
  	}

	
  	//shuffling the questions
  	srand(time(NULL));
  	random_shuffle(vecq.begin(),vecq.end());

  //greets user
  timeOfDayGreeting();

  //Welcome message
	cout << "Welcome to Babak's Multiple Choice Test!!!\n";
	cout << "Can you correctly answer them all?\n";
	cout << "Lets find out now! Good luck :)\n"; 

  	

 	//displays the questions and answers, then prompts for the answer
  	for (unsigned int i=0; i < vecq.size(); i++) {
  		cout << '\n';
  		cout << "Question "<< i + 1 << '\n';
  		cout << vecq[i].quest << '\n';
  		cout << vecq[i].answa << '\n';
  		cout << vecq[i].answb << '\n';
  		cout << vecq[i].answc << '\n';
  		cout << vecq[i].answd << '\n';
      cout << "Select: ";
  		//getline (cin, response);
  		do 
  		{
  			error = 0;
  			getline (cin, response);
  			if (response == "a"|| response == "A")
       		{
           		compare = "1";
      		}
       		else if (response == "b"|| response == "B")
       		{
           		compare = "2";
       		}
       		else if (response == "c"|| response == "C")
       		{
           		compare = "3";
       		}
       		else if (response == "d"|| response == "D")
       		{
           		compare = "4";
       		}
       		else
       		{
           		cout << "Error! Please select a valid option. (a, b, c, or d)\n";
              cout << "Select: ";
           		error = 1;
       		}
  		} while (error == 1);     



       	//this compares the user's answer with the correct answer and keeps track
		if (compare == vecq[i].correct)
  		{
  			totalasked++;
  			gotright++;
        cout << "Correct!\n";
  		}
  		else 
  		{
  			totalasked++;
        cout << "Incorrect, the right answer is " << vecq[i].correct << "\n";
  		};
  		

    };

    percent = (double (gotright) / double (totalasked) * 100);

    //dislays the results
    cout << "\nYou have answered " << gotright << " out of " << totalasked << " correctly.\n";
    cout << "That is "<< percent << "%!\n";

    //stores the performance in a txt file
  

  fstream resultfile;
	resultfile.open("quizresults.txt", fstream::app);
	//resultfile << "You have answered " << gotright << " out of " << totalasked << " correctly.\n";
	resultfile << "You scored "<< percent << "%!\n\n";
  resultfile.close();

  //displays message based on score
  if (percent < 50 ){
    cout << "You did terribly\n";
  }
  if (percent == 100){
    cout << "  ________                  .___      ____.     ___.  ._. \n";
    cout << "  /  _____/  ____   ____   __| _/     |    | ____|_ |__| |\n";
    cout << " /   |  ___ /  _ | /  _ | / __ |      |    |/  _ || __ | |\n";
    cout << " |    |_|  (  <_> |  <_> ) /_/ |  /|__|    (  <_> ) |_| ||\n";
    cout << "  |______  /|____/ |____/|____ |  |________||____/|___  /_\n";
    cout << "         |/                   |/                      |/|/\n";
  }
  if ( percent > 50 && percent < 100){
    cout << "Is that your best shot?\n";
  }

  //this asks the user if they would like to see the past scores to compare
  cout << "Would you like to see the previous scores? (y/n)";
  getline (cin, response);
  if (response == "y"|| response == "Y"){
    string tempstring;
    resultfile.open("quizresults.txt");
    while (!resultfile.eof()){
      getline(resultfile, tempstring);
      cout << tempstring << "\n";
      }
    }
   resultfile.close();
 


	return 0;
}

//Bonus: greets user based on time of day
void timeOfDayGreeting()
{
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
    cout << "Morning! Or should I say Night?\n";
  
  //Between 5 AM and 12 Noon
    else if (hourNumber < 12)
      cout << "Morning!" << endl;
    
    //Between 12 Noon and 5 PM
  else if (hourNumber < 17)
    cout << "Afternoon!\n";

  //Between 5 PM and midnight
    else
      cout << "Evening!\n";

  cout << "\n";
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
