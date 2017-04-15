

// Babak Adeli
// CISP 400 
// Due: 10/10/2016
// Inventory Inquisitor

// BONUS - list entire inventory
// BONUS - total number of items in inventory
// BONUS - doesn't allow the user to enter two items with the same description
// BONUS - calculates the total wholesale cost of all items in the inventory
// BONUS - calculates the total retail cost of items in the inventory
// BONUS - asks the user to confirm changes before saving into the inventory
// BONUS - created my own clearScreen function



#include <iostream>
#include <string>
#include <fstream>
#include <vector> 
#include <algorithm>


using namespace std;



//this is the struct of my items
struct item
{
	string description;
	string quantity;
	string wholesaleCost;
	string retailCost;
	string dateAdded; 
};


//function prototypes
void openRead();
void greetUser();
void printInventory();
void addNewItem();
void editItem();
void displayAny();
void clearScreen();
void totalItems();
void totalWholeSale();
void totalRetail();


//temp struct to get data from file
item tempStruct;
		
//initializing the vector or items so data storage will be dynamic
std::vector<item> itemVector;

//string to place the ignored input.  "press enter to continue"
string ignore;

//creates a place to put the data file
fstream itemfile;

//temporary place to get the users menu selection
string userSelect;

//string to identify what a user searches for
string searchFor;


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
		cout << "Enter (1) to view the entire inventory.\n";
		cout << "Enter (2) to display any record in the inventory\n";
		cout << "Enter (3) to add a new item to the inventory.\n";
		cout << "Enter (4) to change or edit any item in the inventory.\n";
		cout << "Enter (5) to calculate the total quantity of all items in the inventory.\n";
		cout << "Enter (6) to calculate the total wholesale cost of all items in the inventory.\n";
		cout << "Enter (7) to calculate the total retail cost of all items in the inventory.\n";
		cout << "Enter (8) to exit the program.\n";

		//get the command from the user
		getline(cin, userSelect);

		//view the inventory
		if (userSelect == "1")
		{
			printInventory();
		}

		//view any record in inventory
		else if (userSelect == "2")
		{
			displayAny();
		}

		//add a new item to the inventory
		else if (userSelect == "3")
		{
			
			addNewItem();
		}

		//change or edit any item in the inventory
		else if (userSelect == "4")
		{
			//edit the inventory
			editItem();
		}

		else if (userSelect == "5")
		{
			totalItems();
		}

		else if (userSelect == "6")
		{
			totalWholeSale();
		}

		else if (userSelect == "7")
		{
			totalRetail();
		}

		//close the program
		else if (userSelect == "8")
		{
			itemfile.open("inventory.txt");

			for (unsigned int i = 0; i < itemVector.size(); i++)
			{
				cout << "\n";
				itemfile << itemVector[i].description << "\n";
				itemfile << itemVector[i].quantity << "\n";
				itemfile << itemVector[i].wholesaleCost << "\n";
				itemfile << itemVector[i].retailCost << "\n";
				itemfile << itemVector[i].dateAdded << "\n";
			}

			itemfile.close();

			clearScreen();
			cout << "Have a nice day!";

			exit = 1;
		}

		
		//error if they didn't enter anything
		else if (userSelect == "")
		{
			clearScreen();
			cout << "Error! You must select an option. Please try again. Press enter to continue.\n\n";
			getline(cin, ignore);
		}

		//error if they put in anything else
		else 
		{

			clearScreen();
			cout << "Error! " << userSelect << " is not a valid option. Please try again. Press enter to continue.\n\n";
			getline(cin, ignore);

		}
	}
}




void greetUser()
{
	clearScreen();
	cout << "Welcome to Babak's Inventory Inquisitor!\n";
	cout << "This is the inventory management that the world needed.\n";
	cout << "You'll be able to manage an inventory of any type.\n\n";
	cout << "Press enter to begin.\n";
	getline(cin, ignore);
	clearScreen();
}



void openRead()
{
	
	//opens the data file into itemfile
	itemfile.open("inventory.txt");

	if (itemfile.is_open())
	{
		//puts itemfile into the tempstruct 
		while(getline (itemfile,tempStruct.description))
		{
			getline (itemfile,tempStruct.quantity);
			getline (itemfile,tempStruct.wholesaleCost);
			getline (itemfile,tempStruct.retailCost);
			getline (itemfile,tempStruct.dateAdded);
			//puts the tempstruct into the vector
			itemVector.push_back(tempStruct);
		}
		//close the file
		itemfile.close();
	}
}



void printInventory()
{

	//clear the screen
	clearScreen();

	//prints the inventory vector line by line
	for (unsigned int i = 0; i < itemVector.size(); i++)
	{
		cout << "\n";
		cout << "Description: " << itemVector[i].description << "\n";
		cout << "Quantity: " << itemVector[i].quantity << "\n";
		cout << "Wholesale Cost: " << itemVector[i].wholesaleCost << "\n";
		cout << "Retail Cost: " << itemVector[i].retailCost << "\n";
		cout << "Date Added: " << itemVector[i].dateAdded << "\n";
	}

	//once the user is finished looking at the inventory, they can press enter to return to the main menu
	cout << "\nPress Enter to return to the main menu.\n";
	getline(cin, ignore);
	clearScreen();

}



void addNewItem()
{
	string saveCancel;
	bool inputValid = 0;

	

	while(!inputValid)
	{
		inputValid = 1;

		clearScreen();
		cout << "Enter the new item description:\n";
		getline(cin, tempStruct.description);

		for (unsigned int i = 0; i < itemVector.size(); i++)
		{
			if (tempStruct.description == itemVector[i].description)
			{
				clearScreen();
				cout << "Error! There is already an item in the inventory with same description.\n";
				cout << "Please enter a unique item description.\n\n";
				cout << "Press enter to continue.\n";
				getline(cin, ignore);
				inputValid = 0;
			}
		}
	}


	clearScreen();
	cout << "Enter the quantity of " << tempStruct.description << ":\n";
	getline(cin, tempStruct.quantity);

	clearScreen();
	cout << "Enter the wholesale cost of " << tempStruct.description << ":\n";
	getline(cin, tempStruct.wholesaleCost);

	clearScreen();
	cout << "Enter the retail cost of " << tempStruct.description << ":\n";
	getline(cin, tempStruct.retailCost);

	clearScreen();
	cout << "Enter today's date (mm/dd/yyyy) :\n";
	getline(cin, tempStruct.dateAdded);

	
	inputValid = 0;
	while (!inputValid)
	{
		inputValid = 1;

		clearScreen();
		cout << "Here is the new item you have added: \n\n";
		cout << "Description: " << tempStruct.description << "\n";
		cout << "Quantity: " << tempStruct.quantity << "\n";
		cout << "Wholesale Cost: " << tempStruct.wholesaleCost << "\n";
		cout << "Retail Cost: " << tempStruct.retailCost << "\n";
		cout << "Date Added: " << tempStruct.dateAdded << "\n\n";

		cout << "Is this correct? Press (1) to save or (2) to cancel.\n";
		getline (cin, saveCancel);

		if (saveCancel == "1")
		{
			//save temp to the vector
			itemVector.push_back(tempStruct);
		}

		else if (saveCancel == "2")
		{
			//the new item is still in temp but doesn't get saved to the vector.  it will be overwritten by the next item
			cout << tempStruct.description << " has not been saved. Press enter to return to the main menu.\n";
			
		}

		else
		{
			cout << "Error! That is not a valid option.  Please try again.\n\n";
			inputValid = 0;
		}
	}


}

void editItem()
{
	bool exit = 0;

	//clear screen
	clearScreen();

	//searchFor is the item they are going to edit
	cout << "Which item would you like to edit? \n(If the item description does not match exactly you will be returned to the main menu)\n";
	getline(cin, searchFor);

	//for loop to find the matching index in the vector
	for (unsigned int i = 0; i < itemVector.size(); i++)
	{
		if (itemVector[i].description == searchFor)
		{
			

			while(!exit)
			{
				exit = 1;

				clearScreen();
				cout << "Here is the item you wish to edit: \n\n";
				cout << "Description: " << itemVector[i].description << "\n";
				cout << "Quantity: " << itemVector[i].quantity << "\n";
				cout << "Wholesale Cost: " << itemVector[i].wholesaleCost << "\n";
				cout << "Retail Cost: " << itemVector[i].retailCost << "\n";
				cout << "Date Added: " << itemVector[i].dateAdded << "\n\n";

				//place changes in temp before saving to the vector
				tempStruct = itemVector[i];

				cout << "Enter (1) to edit the description\n";
				cout << "Enter (2) to edit the quantity\n";
				cout << "Enter (3) to edit the wholesale cost\n";
				cout << "Enter (4) to edit the retail cost\n";
				cout << "Enter (5) to edit the date added to the inventory\n";
				cout << "Enter (6) to cancel and return to the main menu\n";
				getline(cin, userSelect);
				clearScreen();

				//the user wishes to edit the description
				if (userSelect == "1")
				{
					cout << "Enter the new description for the item:\n";
					getline(cin, tempStruct.description);
				}

				//user wishes to edit quantity
				else if (userSelect == "2")
				{
					cout << "Enter the new quantity for the item:\n";
					getline(cin, tempStruct.quantity);
				}

				//user wishes to edit the wholesale cost
				else if (userSelect == "3")
				{
					cout << "Enter the new wholesale cost of the item:\n";
					getline(cin, tempStruct.wholesaleCost);
				}

				//user wishes to edit the retail cost
				else if (userSelect == "4")
				{
					cout << "Enter the new retail cost of the item:\n";
					getline(cin, tempStruct.retailCost);
				}

				//user wishes to edit the date added
				else if (userSelect == "5")
				{
					cout << "Enter the new date added for the item:\n";
					getline(cin, tempStruct.dateAdded);
				}

				//user exits
				else if (userSelect == "6")
				{
					break;
				}

				//user left this part blank
				else if (userSelect == "")
				{
					cout << "Error! You must select an option. Please try again. Press enter to continue.\n";
					getline(cin, ignore);
					exit = 0;
				}

				//else input error
				else
				{
					cout << "Error! " << userSelect << " is not a valid option. Please try again. Press enter to continue.\n";
					getline(cin, ignore);
					exit = 0;
				}



			}

			//show the user the changes you have made
			clearScreen();
			cout << "Here is the item after the changes:\n\n";
			cout << "Description: " << tempStruct.description << "\n";
			cout << "Quantity: " << tempStruct.quantity << "\n";
			cout << "Wholesale Cost: " << tempStruct.wholesaleCost << "\n";
			cout << "Retail Cost: " << tempStruct.retailCost << "\n";
			cout << "Date Added: " << tempStruct.dateAdded << "\n\n";

			//ask th user to either save to cancel
			cout << "Enter (1) to save these changes or (2) to cancel.\n";
			getline(cin, userSelect);

			//user chose to save
			if (userSelect == "1")
			{
				//saves the tempstruct into the vector
				itemVector[i] = tempStruct;
			}

			//user doesnt' save.  the vector is unchanged
			else if (userSelect == "2")
			{
				break;
			}

			//user left this part blank
			else if (userSelect == "")
			{
				cout << "Error! You must select an option. Please try again. Press enter to continue.\n";
				getline(cin, ignore);
				exit = 0;
			}

			//else input error
			else
			{
				cout << "Error! " << userSelect << " is not a valid option. Please try again. Press enter to continue.\n";
				getline(cin, ignore);
				exit = 0;
			}
		}
	}
}



void displayAny()
{
	//ask the user which item they would like to display
	clearScreen();
	cout << "Which item would you like to display? \n(If the item description does not match exactly you will be returned to the main menu)\n";
	getline(cin, searchFor);

	for (unsigned int i = 0; i < itemVector.size(); i++)
	{
		if (itemVector[i].description == searchFor)
		{
			clearScreen();
			//cout << "Here is the item you wish to edit: \n\n";
			cout << "Description: " << itemVector[i].description << "\n";
			cout << "Quantity: " << itemVector[i].quantity << "\n";
			cout << "Wholesale Cost: " << itemVector[i].wholesaleCost << "\n";
			cout << "Retail Cost: " << itemVector[i].retailCost << "\n";
			cout << "Date Added: " << itemVector[i].dateAdded << "\n\n";
		}
	}
	cout << "\nPress Enter to return to the main menu.\n";

	getline(cin, ignore);
}


void clearScreen()
{
	cout << string(100, '\n');
}


void totalItems()
{
	clearScreen();

	int totalQuantity = 0;

	for (unsigned i = 0; i < itemVector.size(); i++)
	{
		
		int incrementQuantity;
		incrementQuantity = stoi(itemVector[i].quantity);

		totalQuantity = totalQuantity + incrementQuantity;
	}

	cout << "There is a total of " << totalQuantity << " items in the inventory.\n\n";

	cout << "\nPress Enter to return to the main menu.\n";
	getline(cin, ignore);

}

void totalWholeSale()
{
	clearScreen();

	double totalWholeSale = 0.00;

	for (unsigned i = 0; i < itemVector.size(); i++)
	{
		double incrementWholeSale;
		incrementWholeSale = (stod(itemVector[i].wholesaleCost) * (stod(itemVector[i].quantity)) );

		totalWholeSale = totalWholeSale + incrementWholeSale;
	}

	cout << "The total Whole Sale cost of all items in the inventory is $" << totalWholeSale << ".\n\n";

	cout << "\nPress Enter to return to the main menu.\n";
	getline(cin, ignore);
}


void totalRetail()
{
	clearScreen();

	double totalRetail = 0.00;

	for (unsigned i = 0; i < itemVector.size(); i++)
	{
		double incrementRetail;
		incrementRetail = (stod(itemVector[i].retailCost) * (stod(itemVector[i].quantity)) );

		totalRetail = totalRetail + incrementRetail;
	}

	cout << "The total retail cost of all items in the inventory is $" << totalRetail << ".\n\n";

	cout << "\nPress Enter to return to the main menu.\n";
	getline(cin, ignore);
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
