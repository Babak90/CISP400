/*****************************************************************************************************
Bonus Features:  Prints message based on grade received, saves grades to a txt file, 
gives the option to save the scores listed in ascending order, gives option to print previous scores,
validates user input so they must enter at least 1 test score
******************************************************************************************************/

#include <iostream>
#include <string>
#include <fstream>
//algorithm is needed for sort()
#include <algorithm> 


using namespace std;


//Function prototypes



class GPAAna
{
private:
	double inGrade();
	double totalPossible();
	double percent();
public:
	void fillData()
	
	
};

void sortArray(GPAAna *percent, int numScores);
void dispAvg(GPAAna *percent, int numScores);

int main()
{ 
	//GPAAna *pGrade = NULL;
	//GPAAna *totalPossible = NULL;
	//GPAAna *percent = NULL;


	int numScores;

	// welcome message
	cout << "Welcome to Babak's GPA analyzer. \nThis program will take in your scores, list them and display your letter grade.\n\n";

	
	//this asks the user how many scores they are going to enter and makes sure they enter at least 1 score (can't enter 0 or negatives)
	while(true)
	{
		cout << "How many scores do you wish to process? ";
		cin >> numScores;
		if (numScores < 1)
		{
			cout << "You must enter at least 1 score.\n\n";
			
		}
		else 
			break;
	}


	GPAAna *pGrade = new GPAAna[numScores];
	

	//get the scores from the user
	for (int count = 0; count < numScores; count++)
	{
		cout << "Enter score #" << (count + 1) << ": ";
		while (true)
		{
			cin >> pGrade[count].inGrade;
			if (pGrade[count]->inGrade == 0 || pGrade[count]->inGrade > 0)
				break;
			else
				cout << "Error! You cannot input negative numbers for test scores.\n\n";
				cout << "Enter score #" << (count + 1) << ": ";
		}


		cout << "Out of how many total possible points?: ";
		while (true)
		{
			cin >> pGrade[count]->totalPossible;
			if (pGrade[count]->totalPossible == 0 || pGrade[count]->totalPossible > 0)
				break;
			else
				cout << "Error! You cannot input negative numbers for the total possible points.\n\n";
				cout << "Out of how many possible points?: ";
		}
		

		pGrade[count]->percent = (pGrade[count]->inGrade / pGrade[count]->totalPossible) * 100;
		cout << "You scored " << pGrade[count]->percent << "%\n\n";
	}

	sortArray(pGrade[count]->percent, numScores);
	dispAvg(pGrade[count]->percent, numScores);


	return 0;
}

//this is a function to sort the scores in ascending order and display them
void GPAAna::sortArray(GPAAna *array, int numScores)
{
	sort(array.percent, array.percent + numScores);
	cout << "Here are your scores listed in ascending order:\n";
    for (int i = 0; i != numScores; ++i)
        cout << array[i].percent << "%\n";

    //this asks the user if they wish to save the sorted list to a txt file
    string save;
    fstream listfile;
    cout << "\nWould you like to print these scores to a text file? (y/n) ";
    cin >> save;
    if (save == "y" || save == "Y")
    	listfile.open("scoresinascendingorder.txt");
		for (int i = 0; i != numScores; ++i)
        	listfile << array[i].percent << "%\n";
		listfile.close();

}


//this is a function to calculate the average score and display its corresponding letter grade then saves the data in a txt file
void GPAAna::dispAvg(GPAAna *array, int numScores)
{
	double cumTotal = 0.00;
	double avgScore = 0.00;
	string letterGrade = "";

	//calculating the average score
	for (int i = 0; i != numScores; ++i)
		cumTotal = cumTotal + array[i].percent;
	avgScore = cumTotal/numScores;
	cout << "\nYour average score is " << avgScore << "%\n";

	//maps the scores into a letter grade
	if (avgScore < 60)
		letterGrade = "F",
		cout << "That is an " << letterGrade << "\nFailing. Are you even trying?\n";

	else if (avgScore < 70)
		letterGrade = "D",
		cout << "That is a " << letterGrade << "\nPoor performance. A tutor may help you increase your scores.\n";

	else if (avgScore < 80)
		letterGrade = "C",
		cout << "That is a " << letterGrade << "\nSatisfactory. You are passing, but you should make an attempt to increase your scores.\n";

	else if (avgScore < 90)
		letterGrade = "B",
		cout << "That is a " << letterGrade << "\nGood job. You are doing well but there is still room for improvement.\n";

	else 
		letterGrade = "A",
		cout << "That is an " << letterGrade << "\nExcellent! Keep up the good work!\n";

	fstream resultfile;
	resultfile.open("avgscores.txt", fstream::app);
	resultfile << "Your average score is " << avgScore << "%\n";
	resultfile << "That is a(n) "<< letterGrade << "\n\n";
	resultfile.close();

	
	
}

// Peer Review Summary Form
// Complete and attach to the bottom of your source file and turn in to D2L.
//
// Reader: Parag Raval
// Recorder: Ryan Wallace
//
// Approx Time for this asignment: 12 hours
// Use the following ranking for the following:
// 5 - Sophisticated, 4 - Highly Competent, 3 - Competent, 2 - Not Yet Competent, 1 - Unacceptable 
// Solution Fit with Client Needs: 
// User Friendliness: 
// Comments and Documentation: 
// Overall Score: 