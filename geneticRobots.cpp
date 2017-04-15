#include <iostream>
#include <vector>
#include <algorithm>

//for random
#include <stdlib.h>

using namespace std;


const int BOARDSIZE = 196;
const int NUMBEROFBATTERIES = 58;
const int CHROMOSOMES = 11;
const int GENES = 200;
// there are 200 robots 
const int POPULATIONSIZE = 200;


class Robot
{
private:
	string geneticCode[GENES][CHROMOSOMES];
	int fitness;


public:
	Robot();

	void printGeneticCode();
	int getFitness();
	void setFitness(int fitLvl);
	string getGeneticCode(int g, int c);
	void setGeneticCode(int g, int c, string code);
	void resetFitness();
};


Robot::Robot()
{
	int seed = 0;
	int randDigit;

	fitness = 5;

	//big loop to iterate for each of the 24 genes
	for (int j = 0; j < GENES; j++)
	{
		for (int i = 0; i < CHROMOSOMES; i++)
		{
			
			if (i < 4)
			{

				randDigit = (rand()+seed++) % 4;
				if (randDigit == 0)
				{
					geneticCode[j][i] = "w";
				}

				else if (randDigit == 1)
				{
					geneticCode[j][i] = "*";
				}

				else if (randDigit == 2)
				{
					geneticCode[j][i] = "b";
				}

				else 
				{
					geneticCode[j][i] = "2";
				}
			}

			if (i == 4) 
			{
				randDigit = (rand() +seed++) % 4;
				if (randDigit == 0)
				{
					geneticCode[j][i] = "N";
				}

				else if (randDigit == 1)
				{
					geneticCode[j][i] = "E";
				}

				else if (randDigit == 2)
				{
					geneticCode[j][i] = "S";
				}

				else
				{
					geneticCode[j][i] = "W";
				}
			}

			if (i == 5)
			{
				geneticCode[j][i] = "0";
			}

			if (i > 5)
			{
				randDigit = (rand() +seed++) % 4;
				if (randDigit == 0)
				{
					geneticCode[j][i] = "M";
				}

				else if (randDigit == 1)
				{
					geneticCode[j][i] = "R";
				}

				else if (randDigit == 2)
				{
					geneticCode[j][i] = "L";
				}

				else
				{
					geneticCode[j][i] = "X";
				}
			}
		}
	}
}


void Robot::printGeneticCode()
{
	for (unsigned int i = 0; i < GENES;  i++)
	{
		for (unsigned int j = 0; j < CHROMOSOMES; j++)
		{
			cout << geneticCode[i][j];
		}
		cout << "\n";
	}
}

int Robot::getFitness()
{
	return fitness;
}

void Robot::setFitness(int fitLvl)
{
	if (fitLvl == 5)
	{
		fitness = fitness + 5;
	}
	else 
	{
		fitness = fitness - 1;
	}
}

void Robot::resetFitness()
{
	fitness = 5;
}


string Robot::getGeneticCode(int g, int c)
{
	return geneticCode[g][c];
}

void Robot::setGeneticCode(int g, int c, string code)
{
	geneticCode[g][c] = code;
}







class Board
{
private:
	string boardArray[BOARDSIZE];
	int position;

public:
	Board();
	void displayBoard();
	int getBoardPosition();
	void robotMaze(vector<Robot>&);

};

Board::Board()
{
	bool valid = 0;
	int randSquare;
	int seed = 0;
	srand(time(NULL));


	//start by making a blank board
	for (unsigned int i = 0; i < BOARDSIZE; i++)
	{
		boardArray[i] = "*";
	}

	//put in the walls
	//top row
	for (unsigned int i = 0; i < 14; i++)
	{
		boardArray[i] = "w";
	}

	//left row
	for (unsigned int i = 14; i < BOARDSIZE; i = i + 14)
	{
		boardArray[i] = "w";
	}

	//right row
	for (unsigned int i = 27; i < BOARDSIZE; i = i + 14)
	{
		boardArray[i] = "w";
	}

	//bottom row
	for (unsigned int i = 183; i < BOARDSIZE ; i++)
	{
		boardArray[i] = "w";
	}

	//place the batteries.  they can go anywhere except walls
	for (unsigned int i = 0; i < NUMBEROFBATTERIES; i++)
	{
		valid = 0;
		while (!valid)
		{
			valid = 1;
			randSquare = (rand() +seed++) % BOARDSIZE;
			if (boardArray[randSquare] != "*")
			{
				valid = 0;
			}

			else 
			{
				boardArray[randSquare] = "b";
			}
		}
	}

	//find the starting position for the robot on the board
	valid = 0;
	while (!valid)
	{
		position = (rand() +seed++) % BOARDSIZE;
		if (boardArray[position] != "w")
		{
			valid = 1;
		}

	}

}

void Board::displayBoard()
{
	int j = 0;

	for (int i = 0; i < BOARDSIZE; i++)
	{
		cout << boardArray[i];
		j++;
		if (j == 14)
		{
			cout << "\n";
			j = 0;	
		}
		
	}
}

int Board::getBoardPosition()
{
	return position;
}
	
//void Board::robotMaze(vector<Robot>& Robot, int i)
void Board::robotMaze(vector<Robot>& Robot)
{
	int moveCounter;
	int startingSpot = position;

	for (int j = 0; j < POPULATIONSIZE; j++)
	{
		position = startingSpot;
		string nPos = boardArray[position - 14];
		string ePos = boardArray[position + 1];
		string sPos = boardArray[position + 14];
		string wPos = boardArray[position - 1];
		string facing = "N";
		moveCounter = 0;
		for (int i = 0; i < GENES; i++)
		{
			if ((Robot[j].getGeneticCode(i,0) == nPos) || (Robot[j].getGeneticCode(i,0) == "2"))
			{
				if ((Robot[j].getGeneticCode(i,1) == ePos) || (Robot[j].getGeneticCode(i,1) == "2"))
				{
					if ((Robot[j].getGeneticCode(i,2) == sPos) || (Robot[j].getGeneticCode(i,2) == "2"))
					{
						if ((Robot[j].getGeneticCode(i,3) == wPos) || (Robot[j].getGeneticCode(i,3) == "2"))
						{
							if (Robot[j].getGeneticCode(i,4) == facing);
							{
								for (int z = 6; z < CHROMOSOMES; z++)
								{
									if (Robot[j].getGeneticCode(i,z) == "M")
									{
										if ((moveCounter < 25) && (Robot[j].getFitness() > 0))
										{
											moveCounter = moveCounter + 1;
											Robot[j].setFitness(1);
											if (facing == "N")
											{
												if (boardArray[position - 14] != "w")
												{
													position = position - 14;
												}
											}
											else if (facing == "E")
											{
												if (boardArray[position + 1] != "w")
												{
													position = position + 1;
												}
											}
											else if (facing == "S")
											{
												if (boardArray[position + 14] != "w")
												{
													position = position + 14;
												}
											}
											else 
											{
												if (boardArray[position - 1] != "w")
												{
													position = position - 1;
												}
											}
											if (boardArray[position] == "b")
											{
												Robot[j].setFitness(5);
											}
											nPos = boardArray[position - 14];
											ePos = boardArray[position + 1];
											sPos = boardArray[position + 14];
											wPos = boardArray[position - 1];
										}
									}

									if (Robot[j].getGeneticCode(i,z) == "R")
									{
										if ((moveCounter < 25) && (Robot[j].getFitness() > 0))
										{
											if (facing == "N")
											{
												facing = "E";
											}
											else if (facing == "E")
											{
												facing = "S";
											}
											else if (facing == "S")
											{
												facing = "W";
											}
											else
											{
												facing = "N";
											}
										}
									}

									if (Robot[j].getGeneticCode(i,z) == "L")
									{
										if ((moveCounter < 25) && (Robot[j].getFitness() > 0))
										{
											if (facing == "N")
											{
												facing = "W";
											}
											else if (facing == "E")
											{
												facing = "N";
											}
											else if (facing == "S")
											{
												facing = "E";
											}
											else
											{
												facing = "S";
											}
										}
									}
								}
							}

						}
					}
				}
			}
		}
	}

	double totalFitness;
	double avgFitness;

	for (int y = 0; y < POPULATIONSIZE; y++)
	{
		totalFitness += Robot[y].getFitness();
	}

	avgFitness = (totalFitness / POPULATIONSIZE);
	cout << avgFitness << "\n";


}


//prototype
bool compFit( Robot r1, Robot r2);
void mateAndDestroy(vector<Robot>& Robot);


//vector<Robot> robotVector;



int main()
{
	

	
	//this is the vector that will hold the robots
	vector<Robot> robotVector;

	//we begin by filling the vector with 200 randomly made robots
	for (int i = 0; i < POPULATIONSIZE; i++)
	{
		robotVector.push_back(Robot());
	}

	//create the first instance of the board, then run them through the maze
	Board * boardPtr = new Board;
	//Board Board;
	boardPtr->robotMaze(robotVector);


	for (int i = 0; i < 1000; ++i)
	{
		delete boardPtr;

		sort(robotVector.begin(), robotVector.end(), compFit);
		mateAndDestroy(robotVector);
		for (int j = 0; j < POPULATIONSIZE; j++)
		{
			robotVector[j].resetFitness();
		}
		
		Board * boardPtr = new Board;
		boardPtr->robotMaze(robotVector);
	}
		
	
}


bool compFit( Robot r1, Robot r2)
{
	return r1.getFitness() > r2.getFitness();
}

void mateAndDestroy(vector<Robot>& Robot)
{
	for (int i = 0; i < (POPULATIONSIZE/2); i++)
	{
		for (int j = 0; j < (GENES/2); j++)
		{
			for (int k = 0; k < CHROMOSOMES; k++)
			{
				Robot[i+100].setGeneticCode(j,k,Robot[i].getGeneticCode(j,k));
			}
		}
	}

	for (int i = 0; i < (POPULATIONSIZE/2); i=i+2)
	{
		for (int j = (GENES/2); j < GENES; j++)
		{
			for (int k = 0; k < CHROMOSOMES; k++)
			{
				Robot[i+101].setGeneticCode(j,k,Robot[i].getGeneticCode(j,k));
			}
		}
	}

	for (int i = 1; i < (POPULATIONSIZE/2); i=i+2)
	{
		for (int j = (GENES/2); j < GENES; j++)
		{
			for (int k = 0; k < CHROMOSOMES; k++)
			{
				Robot[i+99].setGeneticCode(j,k,Robot[i].getGeneticCode(j,k));
			}
		}
	}
}

