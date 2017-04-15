


#include <iostream>   // For console input/output

#include <fstream>     // For file operations

#include <string>        // For strings

#include <cstdlib>      // For rand and srand

#include <ctime>        // For time() for seed

#include <vector>       // For vector operations

#include <algorithm> // For find

#include <iterator> // For begin, end

#include <new>                      // For the bonus Re-play feature



using namespace std;



// Define constants and variables

const unsigned max_sq = 8;    // Max number of squares in the game - 1

const string performancefilename = "performance.txt";

bool computer_turn = 0;          // 1 means computer's turn, 0 means human's turn

bool game_ended = 0; // Whether the game has ended

string h_char = "O";    // Human's selected character

string c_char = "X";    // Computer's selected character

string who_won = "";  // Who won the game

vector<short> available_squares;        // List of available squares

int number_of_times_played = 0;

int number_of_times_you_won = 0;

int number_of_times_computer_won = 0;

int number_of_times_tied = 0;





// Function prototypes

// All these 3 functions are for the bonus feature of storing

// and reading the past results

void create_performancefile();

void read_past_results();

void store_results();



// Class definition

class TicTacToe_Board

// Defines the game board & stores the current status

{

            private:

                        string board_array[max_sq]; //Stores the game status in an array



            public:

                        TicTacToe_Board();

                        bool set_board_array(unsigned sq_num, string sq_choice);

                        void get_board_display();

                        void get_board_array();

                        string get_array(unsigned sq_num); // For debug: See an individual element of the array

                        bool get_won();

};

TicTacToe_Board::TicTacToe_Board()

// Constructor funciton to initialize the array with 1-9 digits

// Create an empty Tic_Tac_Toe board

{

            for (unsigned i=0; i <= max_sq; i++)

            {

                        board_array[i] = to_string(i+1);

            }



// Clear the available squares array

            available_squares.clear();

}

// Bonus: A function to help debug, to see the status of individual squares in the game

string TicTacToe_Board::get_array(unsigned sq_num)

{

            return board_array[sq_num];

}

void TicTacToe_Board::get_board_display()

// Displays the current board

{

// Bonus: Ascii based visual grid layout

//  1 | 2 | 3

// ---+---+---

//  4 | 5 | 6

// ---+---+---

//  7 | 8 | 9



            for (unsigned i=0; i < 3; i++)

            {

                        cout << " " + board_array[3*i] + " | " + board_array[3*i+1] + " | " + board_array[3*i+2] << endl;



                        if (i < 2)

                                    cout << "---+---+---" << endl;

            }

            cout << endl;

}

void TicTacToe_Board::get_board_array()

// Gets unfilled square numbers from the board

// and puts them into the available_squares array

{

            available_squares.clear();

            for (unsigned i=0; i <= max_sq; i++)

            {

                        if ((board_array[i] != h_char) && (board_array[i] != c_char))

                                    available_squares.push_back(i);

            }

}

bool TicTacToe_Board::set_board_array(unsigned sq_num, string sq_choice)

// Sets a square of the game board with X or O,

// Checks if the users has won based on the latest move

// and returns 1 if won, 0 otherwise.

{

            board_array[sq_num] = sq_choice;



            return get_won();

}

bool TicTacToe_Board::get_won()

// Returns 1 if won, 0 otherwise

// Checks rows, columns and diagonals

{

            bool won = 0;

            for (unsigned i=0; i < 3; i++)

            {

                        if (

                        // Check rows & columns

                        ((board_array[3*i] == board_array[3*i+1]) && (board_array[3*i] == board_array[3*i+2])) ||

                        ((board_array[i] == board_array[i+3]) && (board_array[i] == board_array[i+6])))

                                    won = 1;

            }

            //Check diagonals

            if (

            ((board_array[0] == board_array[4]) && (board_array[0] == board_array[8])) ||

            ((board_array[2] == board_array[4]) && (board_array[2] == board_array[6])))

                        won = 1;



            return won;

}

TicTacToe_Board tictactoe_board;

// Creates tictactoe_board as an instance of TicTacToe_Board class



int main()

{

            // Function prototypes

            void make_computers_move();           // Makes computer's move

            unsigned get_humans_choice(); // Gets the user's move

            void time_of_the_day_greetings(); // Greets the user with the time of the day



// Display the Game Instructions

            // Program Greeting

            //"Clear" the screen for aesthetics (by sending 50 blank lines to the console)

            cout << string(50, '\n');



            // Bonus

            // Create a file to store/retrive past game results

            create_performancefile();



            // Bonus

            //Greet the user based on the time of the day

            time_of_the_day_greetings();



            cout << "Ready to have some fun?  How about a game of good old Tick Tack Toe!" << endl;

            cout << "And you do not even need a paper, a pen, or even another person, as you play with the computer!" << endl << endl;

            cout << "Rules:" << endl;

            cout << "You first pick whether you want to play as X or O." << endl;

            cout << "Then the computer randomly decideds who goes first." << endl;

            cout << "On your turn, pick any square not used so far." << endl;

            cout << "Whoever first gets his symbol across any row, column or a diagonal wins." << endl;

            cout << "Let the game begin!" << endl << endl;



// Bonus: Let the user pick his/her symbol

            bool input_invalid = 1;

            while(input_invalid)

            {

                        input_invalid = 0;



                       cout << "Pick either X or O as your play symbol." << endl;

                        cout << "Enter either X or O: ";



                        string user_input;

                        cin >> user_input;

                        if ((user_input == "o") || (user_input == "O"))

                        {

                                    h_char = "O";

                                    c_char = "X";

                        }

                        else if ((user_input == "x") || (user_input == "X"))

                        {

                                    h_char = "X";

                                    c_char = "O";

                        }

                        else

                        {

                                    input_invalid = 1;

                                    cout << user_input << " is not a valid choice. Let's try again." << endl;

                        }

            }

            cout << "Great!  You chose \"" << h_char << "\" as your place character." << endl;

            cout << "The computer will use \"" << c_char << "\" as its play character." << endl << endl;



            bool play_again = 1;

            while (play_again)

            {

                        // Determine who goes first

                        // Create a seed using time(0)

                        srand(time(0));

                        // Randomize who goes firts

                        computer_turn = rand() % 2;

                        if (computer_turn)

                                    cout << "This time the Computer gets to go first!" << endl;

                                    // No need to display the board as yet

                        else

                        {

                                    cout << "This time You get to go first!" << endl;

                                    tictactoe_board.get_board_display();

                        }

                        game_ended = false;



                        while (!game_ended)

                        {

                                    // Get the list of still available slots

                                    tictactoe_board.get_board_array();



                                    if (!available_squares.size())

                                    {

                                                // It's a tie!

                                                game_ended = 1;

                                                cout << "It's a tie!" << endl << endl;

                                                who_won = "Tie";

                                                read_past_results();

                                                break;

                                    }

                                    if (computer_turn)

                                    {

                                                make_computers_move();

                                    }

                                    else

                                    {

                                                unsigned sq_num = get_humans_choice();

                                                bool won = tictactoe_board.set_board_array(sq_num, h_char);

                                                // Display the board

                                                tictactoe_board.get_board_display();



                                                if (won)

                                                {

                                                            // Human Won

                                                            cout << "Congratulation!! You won!" << endl;

                                                            // Bonus: Ascii graphics to congratulate the user on his/her win

                                                            cout << " __ __   ___   __ __      __    __   ___   ____   __  __ " << endl;

                                                            cout << "|  |  | /   \\ |  |  |    |  |__|  | /   \\ |    \\ |  ||  |" << endl;

                                                            cout << "|  |  ||     ||  |  |    |  |  |  ||     ||  _  ||  ||  |" << endl;

                                                            cout << "|  ~  ||  O  ||  |  |    |  |  |  ||  O  ||  |  ||__||__|" << endl;

                                                            cout << "|___, ||     ||  :  |    |  `  '  ||     ||  |  | __  __ " << endl;

                                                            cout << "|     ||     ||     |     \\      / |     ||  |  ||  ||  |" << endl;

                                                            cout << "|____/  \\___/  \\__,_|      \\_\\_/    \\___/ |__|__||__||__|" << endl;

                                                            who_won = "User";

                                                            read_past_results();

                                                            game_ended =1;

                                                }

                                    }

                                    // Swith turns

                                    computer_turn = !computer_turn;

                        }
                        //Display the past results

                        cout << "******************************************************" << endl;

                        cout << "Here is the running score of all the games played so far:" << endl;

                        cout << "******************************************************" << endl;

                        cout << "Total number of games played    : " << number_of_times_played << endl;

                        cout << "Number of times the user won    : " << number_of_times_you_won << endl;

                        cout << "Number of times the computer won: " << number_of_times_computer_won << endl;

                        cout << "Number of times there was a tie : " << number_of_times_tied << endl;

                        cout << "******************************************************" << endl << endl;



                        cout << endl << "How about a re-match?" << endl;

                        cout << "Would you like to play again?" << endl;



                        input_invalid = 1;

                        while(input_invalid)

                        {

                                    input_invalid = 0;



                                    cout << "Enter either Y or N: ";



                                    string user_input;

                                    cin >> user_input;

                                    if ((user_input == "y") || (user_input == "Y"))

                                    {

                                                play_again = 1;

                                                // Destroy the object tictactoe_board by calling

                                                // the deconstructor

                                                tictactoe_board.~TicTacToe_Board();

                                                // Create a new instance for the new game

                                                // (The constructcor is called automaticaclly)

                                                new (&tictactoe_board) TicTacToe_Board();

                                                cout << endl;

                                                break;

                                    }

                                    else if ((user_input == "n") || (user_input == "N"))

                                    {

                                                play_again = 0;

                                                break;

                                    }

                                    else

                                    {

                                                input_invalid = 1;

                                                cout << user_input << " is not a valid choice. Let's try again." << endl;

                                    }

                        }

            }

            cout << "Goodbye!" << endl;

            return 0;

}



void make_computers_move()

// Makes the computer's move, checks for a win, and if won,

// displays the current and past results

{

            // Randomly select a number to help select an available square

            srand(time(0));

            // Picks a random number from the available_squares array

            unsigned sq_num = available_squares[rand() % available_squares.size()];

            cout << "The computer chose : " << sq_num +1 << endl;

            bool won = tictactoe_board.set_board_array(sq_num, c_char);

            // Display the board

            tictactoe_board.get_board_display();

            if (won)

                                    {

                                                // Computer Won

                                                cout << "The Computer won!" << endl;

                                                who_won = "Computer";

                                                read_past_results();

                                                game_ended = 1;

                                    }

}



unsigned get_humans_choice()

// Gets the human's move, checks for a win, and if won,

// displays the current and past results

{

            string user_input;

            bool input_invalid = 1;

            unsigned human_choice;



            while (input_invalid)

            {

                        cout << "The available squares:";

                        for (unsigned i = 0; i < available_squares.size(); i++)

                                    cout << " " << available_squares[i]+1;

                        cout << endl;

                        cout << "Your Move (pick a number for your chosen move): ";

                        cin >> user_input;



                        // Bonus: Offer help

                        if (user_input == "?")

                        {

                                    cout << endl << "You can pick any availabe square to play your move." << endl;

                                    cout << "To pick an available square, enter the digit in that square." << endl;

                                    cout << "If a square already has either O or X, you cannot pick them again." << endl << endl;

                        }

                        else

                        {

                                    for (unsigned i = 0; i < available_squares.size(); i++)

                                    {

                                                if (user_input == to_string(available_squares[i]+1))

                                                {

                                                            input_invalid = 0;

                                                            break;

                                                }

                                    }

                                    if (input_invalid)

                                                cout << "That is not a valid input!" << endl;

                        }

            }



            // "Clear" the screen for aesthetics (by sending 50 blank lines to the console)

            cout << string(50, '\n');s

            human_choice = stoi(user_input);

            cout << "You Chose :" << human_choice << endl;

            return human_choice - 1;

}



void time_of_the_day_greetings()

// Greets the user based on the time of the day

{

            long time_seconds;

            //Get the current time

            time (&time_seconds);

            //Convert the time into string format

            string seconds = ctime(&time_seconds);

            //Extract the hour info

            string hour = seconds.substr(11, 2);

            //Convert hour into an unsigned integer (we will need it for comparision)

            unsigned hour_number = stoi(hour);



            //Start with "Good ", common to all the intended greetings

            cout << endl << "Good ";

            if (hour_number < 5)

                        //Between midnight and 5 AM

                        cout << "Grief! What are you doing here SO late? :-)" << endl;

            else if (hour_number < 12)

                        //Between 5 AM and 12 Noon

                        cout << "Morning!" << endl;

            else if (hour_number < 17)

                        //Between 12 Noon and 5 PM

                        cout << "Afternoon!" << endl;

            else

                        //Between 5 PM and midnight

                        cout << "Evening!" << endl;



            cout << endl;



            return;

}

void create_performancefile()

// Initialized the game results in a file called "performance.txt"

{

            ofstream performancefile;



            // If the file is already open, close it first.

            if (performancefile)

                        performancefile.close();



            performancefile.open(performancefilename.c_str(),std::ofstream::app);

            //The "app" part opens the file for append vs just overwriting it.

            if (!performancefile)

            //"performance.txt" did not open successfully

            //Since the user has nothing to do with saving data in this file,

            //it would be very user-unfriendly to throw an error that the file

            //did not open.  So no error message is shown.

            //This part of the program execution is intentionally kept at the last, so that the

            //program skip this feature in case of an error, and the user still gets the

            //full functionality he/she expects from this program.

            //

            //Future improvement: Automatically notify the admin that there was an issue.

            {

                        return;

            }

            else

            {

                        performancefile << 0 << endl << 0 << endl << 0 << endl << 0 << endl;

                        // number_of_times_played = 0

                        // number_of_times_you_won = 0

                        // number_of_times_computer_won = 0

                        // number_of_times_tied = 0

                        performancefile.close();

                        return;

            }

}



void read_past_results()

// Reads the past game results from a file called "performance.txt"

{

            string line_read;

            ifstream performancefile;



            // If the file is already open, close it first.

            if (performancefile)

                  performancefile.close();



            performancefile.open(performancefilename);

            if (!performancefile)

            //"performance.txt" did not open successfully

            //Since the user has nothing to do with reading data from this file,

            //it would be very user-unfriendly to throw an error that the file

            //did not open.  So no error message is shown.

            //This part of the program execution is intentionally kept at the last, so that the

            //program can skip this feature in case of an error, and the user still gets the

            //full functionality he/she expects from this program.

            //

            //Future improvement: Automatically notify the admin that there was an issue.

            {

                        return;

            }

            else

            {

                        // file opened successfully

                        performancefile >> line_read;

                        number_of_times_played = stoi(line_read) + 1;



                        performancefile >> line_read;

                        number_of_times_you_won = stoi(line_read) + (who_won == "User");



                        performancefile >> line_read;

                        number_of_times_computer_won = stoi(line_read) + (who_won == "Computer");



                        performancefile >> line_read;

                        number_of_times_tied = stoi(line_read) + (who_won == "Tie");



                        performancefile.close();

                        store_results();



                        return;

            }

}



void store_results()

// Stores the game results in a file called "performance.txt"

{

            ofstream performancefile;



            // If the file is already open, close it first.

            if (performancefile)

                        performancefile.close();



            performancefile.open(performancefilename.c_str());

            //The "app" part opens the file for append vs just overwriting it.

            if (!performancefile)

            //"performance.txt" did not open successfully

            //Since the user has nothing to do with saving data in this file,

            //it would be very user-unfriendly to throw an error that the file

            //did not open.  So no error message is shown.

            //This part of the program execution is intentionally kept at the last, so that the

            //program skip this feature in case of an error, and the user still gets the

            //full functionality he/she expects from this program.

            //

            //Future improvement: Automatically notify the admin that there was an issue.

            {

                        return;

            }

            else

            {

                        performancefile << number_of_times_played << endl;

                        performancefile << number_of_times_you_won << endl;

                        performancefile << number_of_times_computer_won << endl;

                        performancefile << number_of_times_tied << endl;

                        performancefile.close();

                        return;

            }

}
