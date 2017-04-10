// Babak Adeli
// CISP 400 
// Due: 10/17/2016
// To Do List

/////////////////////////////////////////////////////////////////////////////////////////////////////
// Bonus 1: Displays new information to user and asks them to confirm before saving
// Bonus 2: Saves data in a text file and loads it into the program upon booting
// Bonus 3: There is a description field for the user to elaborate on the task
// Bonus 4: Greets user based on time of day
// Bonus 5: Created a seperate clear screen function

/////////////////////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
//#include <algorithm>

using namespace std;


class Task
{
private:
	string taskName;
	string taskDescription;
	string dueDate;

public:

	//constructor
	Task();

	//overload constructor
	Task(string tName, string tDesc, string dDate);

	//deconstructor
	~Task();


	//accessor functions
	string getTaskName();
	string getTaskDescription();
	string getDueDate();


	//mutator functions
	void setTaskName (string tName);
	void setTaskDescription (string tDescription);
	void setDueDate (string dDate);
};



//function prototypes
void clearScreen();
void greetUser();
void openRead();
void printList();
void addNewTask();
void deleteTask();
void saveToFile();


//temp variables to pass through into the class from multiple functions
string tName;
string tDesc;
string dDate;

//creates a place to put the data file
fstream itemFile;

//string to place the ignored input.  "press enter to continue"b
string ignore;

//temporary place to get the users menu selection
string userSelect;

//this will be the vector of objects (the to do list)
std::vector<Task> vecT;



int main()
{
	bool exit = 0;

	greetUser();
	openRead();


	while (!exit)
	{
		//print the menubar
		clearScreen();
		cout << "************************************************************************ \n";
		cout << "MAIN MENU\n";
		cout << "************************************************************************ \n";
		cout << "Enter (1) to view the to do list.\n";
		cout << "Enter (2) to add a new item to the to do list.\n";
		cout << "Enter (3) to delete a task from the to do list.\n";
		cout << "Enter (4) to exit the program.\n";

		//get the command from the user
		getline(cin, userSelect);

		//view the inventory
		if (userSelect == "1")
		{
			printList();
		}

		else if (userSelect == "2")
		{
			addNewTask();
		}

		else if (userSelect == "3")
		{
			deleteTask();
		}

		else if (userSelect == "4")
		{
			clearScreen();
			cout << "\nThank you for using Babak's To Do List.  Goodbye.\n";
			exit = 1;
		}

		else
		{
			clearScreen();
			cout << "Error! That is not a valid option. Please try again. Press enter to continue.\n\n";
			getline(cin, ignore);
		}



	}
}

//constructor function, initializes everyting to blank
Task::Task()
{
	taskName = "";
	taskDescription = "";
	dueDate = "";
}

//overload function for task
Task::Task(string tName, string tDesc, string dDate)
{
	taskName = tName;
	taskDescription = tDesc;
	dueDate = dDate;
}

//deconstructor function
Task::~Task(){}


//accessor functions
string Task::getTaskName() 
{ 
	return taskName; 
}

string Task::getTaskDescription()
{ 
	return taskDescription; 
}

string Task::getDueDate()
{ 
	return dueDate; 
}

//mutator functions
void Task::setTaskName (string tName)
{
	taskName = tName;
}

void Task::setTaskDescription (string tDesc)
{
	taskDescription = tDesc;
}

void Task::setDueDate (string dDate)
{
	dueDate = dDate;
}




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

 	cout << "\n";
	cout << "Welcome to Babak's To Do List!\n";
	cout << "Never forget to complete a task again.\n\n";
	cout << "Press enter to begin.\n";
	getline(cin, ignore);
	clearScreen();
}


void openRead()
{
	//ifstream itemFile;

	//check if file is already open. If so, then close it.
	if (itemFile.is_open())
		itemFile.close();

	//opens the txt file into itemFile
	itemFile.open("todolist.txt");

	while (getline(itemFile, tName))
	{
		getline(itemFile, tDesc);
		getline(itemFile, dDate);
		
		//makes a new instance of the class
		Task newTask(tName, tDesc, dDate);

		//puts the object into the vector
		vecT.push_back(newTask);
	}
}

void printList()
{
	//clear the screen
	clearScreen();

	//prints the inventory vector line by line
	for (unsigned int i = 0; i < vecT.size(); i++)
	{
		cout << "\n";
		cout << "Task Name: " << vecT[i].getTaskName() << "\n";
		cout << "Task Description: " << vecT[i].getTaskDescription() << "\n";
		cout << "Due Date: " << vecT[i].getDueDate() << "\n";
	}

	//once the user is finished looking at the inventory, they can press enter to return to the main menu
	cout << "\nPress Enter to return to the main menu.\n";
	getline(cin, ignore);
	clearScreen();

}

void addNewTask()
{

	string saveCancel;
	bool inputValid = 0;

	clearScreen();
	cout << "Enter the new task name:\n";
	getline(cin, tName);

	clearScreen();
	cout << "Enter the task description:\n";
	getline(cin, tDesc);

	clearScreen();
	cout << "Enter the due date (mm/dd/yyyy) :\n";
	getline(cin, dDate);

	while(!inputValid)
	{
		inputValid = 1;

		clearScreen();
		cout << "Here is the new task you have added: \n\n";
		cout << "Name: " << tName << "\n";
		cout << "Description: " << tDesc << "\n";
		cout << "Due Date: " << dDate << "\n\n";

		cout << "Is this correct? Press (1) to save or (2) to cancel.\n";
		getline (cin, saveCancel);

		if (saveCancel == "1")
		{
			//save temp to the vector
			Task newTask(tName, tDesc, dDate);
			vecT.push_back(newTask);
			
		}

		else if (saveCancel == "2")
		{
			//the new item is still in temp but doesn't get saved to the vector.  it will be overwritten by the next item
			cout << tName << " has not been saved. Press enter to return to the main menu.\n";
			
		}

		else
		{
			cout << "Error! That is not a valid option.  Please try again.\n\n";
			inputValid = 0;
		}
	}
	saveToFile();
}

void deleteTask()
{
	clearScreen();
	string deleteName;

	cout << "Enter task to delete:\n";
	getline(cin, deleteName);

	for (unsigned int i = 0; i < vecT.size(); i++)
	{
		if (vecT[i].getTaskName() == deleteName)
		{
			vecT.erase(vecT.begin() + i);
		}
	}
	saveToFile();
}


void saveToFile()
{
	if (itemFile.is_open())
		itemFile.close();


	itemFile.open("todolist.txt");

		for (unsigned int i = 0; i < vecT.size(); i++)
		{
			cout << "\n";
			itemFile << vecT[i].getTaskName() << "\n";
			itemFile << vecT[i].getTaskDescription() << "\n";
			itemFile << vecT[i].getDueDate() << "\n";
		}

		itemFile.close();
}

// Peer Review Summary Form
// Complete and attach to the bottom of your source file and turn in to D2L.
//
// Reader: Ryan Wallace
// Recorder: Parag Raval
//
// Approx Time for this asignment: 12 hours
// Use the following ranking for the following:
// 5 - Sophisticated, 4 - Highly Competent, 3 - Competent, 2 - Not Yet Competent, 1 - Unacceptable 
// Solution Fit with Client Needs: 5
// User Friendliness: 5
// Comments and Documentation: 5 
// Overall Score: 5