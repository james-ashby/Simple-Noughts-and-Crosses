#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
#include <cstdlib>
#include <stdlib.h>
#include <Windows.h>

using namespace std;

const int gameSize = 3; // Constant int declared to use for the dimensions of the array

// Read only functions for array (const)
void showBoard(const char board[][gameSize]); // Show board in console screen 
void checkTurn(const char board[][gameSize], char choice); // Check the players turn input through the array
void checkWinner(const char board[][gameSize], char noughtorcross); // Check the array for possible win
void drawCheck(const char board[][gameSize]); // Check the array for possible tie/draw


// Write functions for array (no const)
void updateBoard(char board[][gameSize], char player, char numberchoice, char noughtorcross); // Update the board with the turn choice values  
void resetBoard(char board[][gameSize]); // Reset the board to the default values of 1 to 9 

char board[gameSize][gameSize]; // Declare the array variable

// Game functions
void playGame(); // Main code for game sequence
void playerTurn(); // Player turn function
void computerTurn(); // Computer turn function - using Modulus to make a random choice
void changePlayer(); // Change turn function - change the turn between Player and Computer
void gameWin(const char noughtorcross); // Winner function - checks which player won, computer or player

// Declare necessary variables
int currentTurn = 1; 
int turnCount = 1;
int turnChoice;
char playerChoice; // The Char choice for the human player
char compChoice; // The Char choice for the computer 
char playerChar; // The Character of the player (nought or cross)
char compChar; // The Character of the computer (nought or cross)
string playerName;
bool gameWon = false;
bool turnCheck = false;


int main()
{
	bool loop = true;
	cout << "<< Welcome to Noughts and Crosses. >>" << endl << endl;
	cout << "Please enter your name : ";
	cin >> playerName; // Sets player name to whatever they input (No validation)

	while (loop == true)
	{
		char yesNo;
		resetBoard(board);
		playGame();
		cout << "Would you like to play again? (Y) (N)" << endl;
		cin >> yesNo;
		if (yesNo == 'N' || yesNo == 'n')
		{
			loop = false; // If the user inputs N, set the loop bool to be false, thus breaking out of the while loop and ending the program
			break;
		}
		system("CLS");
		
	}
	
}

void showBoard(const char board[][gameSize]) // Draw the board over 3 lines, with spaces inbetween the 3 values on each row and column.
{
	for (int c(0); c < 3; c++)
	{
		cout << "           ";
		for (int r(0); r < 3; r++)
		{
			cout << "  " << board[c][r] << "  ";
		}
		cout << endl << endl;
	}

}
void resetBoard(char board[][gameSize])  // Reset all values in the array to ({1,2,3},{4,5,6},{7,8,9})
{
	char boardNum = '-1';
	for (int c(0); c < 3; c++)
	{
		for (int r(0); r < 3; r++)
		{
			board[c][r] = boardNum;
			boardNum = boardNum + 1;
		}
	}
	gameWon = false; // Reset gameWon variable to false
	turnCount = 0; // Reset turn count to 0
}
void playGame()
{

	
	cout << "Would you like to go first or second? Please enter (1) or (2) : " << endl;
	cin >> turnChoice;
	if (cin.fail()) // Checks if the user has entered the correct data type, if the data type is not correct, ask again
	{
		cin.clear(); cin.ignore();
	}
	while (turnChoice != 1 && turnChoice != 2)  // Checks if the user has entered an integer that is not 1 or 2 (Extra validation to ensure that the user chooses 1 or 2)
	{
		cout << "Input error, please select either (1) or (2)" << endl;
		cout << "Would you like to go first or second? (1) or (2) : ";
		cin >> turnChoice;
		if (cin.fail())
		{
			cin.clear(); cin.ignore();
		}
		system("CLS");
	}
	if (turnChoice == 1)
	{
		currentTurn = 1; // If the player chooses to go first, the current turn is set to 1, which starts the game loop on the Player Turn (line 80)
		playerChar = 'X'; // Sets the player to Crosses
		compChar = 'O'; // Sets the computer to Noughts
		system("CLS");
		cout << "You are first, you are Crosses 'X' and the computer is Noughts '0'" << endl << endl;
		showBoard(board);
	}
	else if (turnChoice == 2)
	{
		currentTurn = 2; // If the player chooses to go second, the current turn is set to 2, which starts the game loop on the Computer Turn (line 89)
		playerChar = 'O'; // Sets the player to Noughts 
		compChar = 'X'; // Sets the computer to Crosses
		cout << "You are second, you are Noughts '0' and the computer is Crosses 'X'" << endl << endl;
	}
	while (gameWon == false) // While the game is not won or lost, do the following.
	{
		cout << "Turn " << turnCount << "." << endl << endl; // Output turn number
		if (currentTurn == 1) // Player Turn
		{
			playerTurn(); // Call the function for player inputs
			updateBoard(board, currentTurn, playerChoice, playerChar); // Update the board with the player input choice
			Sleep(250); // Wait 0.25 seconds.
			system("CLS");
			checkWinner(board, playerChar); // Check if the player has won
			drawCheck(board);
			cout << "Your last turn : " << endl;
		}
		else if (currentTurn == 2) // Computer Turn
		{
			computerTurn(); // Call the function for computer inputs
			updateBoard(board, currentTurn, compChoice, compChar); // Update the board with the computer input choice
			checkWinner(board, compChar); // Check if the computer has won
			drawCheck(board);
			Sleep(250);
		}
		changePlayer();
		Sleep(250);
		showBoard(board);
		turnCount++;
		Sleep(250);
	}
}
void updateBoard(char board[][gameSize], char currentplayer, char numberchoice, char noughtorcross)
{
	for (int c(0); c < 3; c++)
	{
		for (int r(0); r < 3; r++)
		{
			// If the updateBoard function is called on the Player's turn, depending on their choice (playerChoice), update a position in the array to their character (playerChar) 
			if (currentTurn == 1)
			{
				switch (numberchoice)
				{
				case '1': board[0][0] = noughtorcross; break;
				case '2': board[0][1] = noughtorcross; break;
				case '3': board[0][2] = noughtorcross; break;
				case '4': board[1][0] = noughtorcross; break;
				case '5': board[1][1] = noughtorcross; break;
				case '6': board[1][2] = noughtorcross; break;
				case '7': board[2][0] = noughtorcross; break;
				case '8': board[2][1] = noughtorcross; break;
				case '9': board[2][2] = noughtorcross; break;
				}
			}
			// If the updateBoard function is called on the Computer's turn, depending on the generated input (compChoice), update a position in the array to their character (compChar) 
			else if (currentTurn == 2)
			{
				switch (numberchoice)
				{
				case '1': board[0][0] = noughtorcross; break;
				case '2': board[0][1] = noughtorcross; break;
				case '3': board[0][2] = noughtorcross; break;
				case '4': board[1][0] = noughtorcross; break;
				case '5': board[1][1] = noughtorcross; break;
				case '6': board[1][2] = noughtorcross; break;
				case '7': board[2][0] = noughtorcross; break;
				case '8': board[2][1] = noughtorcross; break;
				case '9': board[2][2] = noughtorcross; break;
				}
			}
		}
	}
	cout << endl;
}
void checkWinner(const char board[][gameSize], char noughtorcross)
{
	// Row win checks
	if (board[0][0] == noughtorcross && board[0][1] == noughtorcross && board[0][2] == noughtorcross) gameWin(noughtorcross);
	if (board[1][0] == noughtorcross && board[1][1] == noughtorcross && board[1][2] == noughtorcross) gameWin(noughtorcross);
	if (board[2][0] == noughtorcross && board[2][1] == noughtorcross && board[2][2] == noughtorcross) gameWin(noughtorcross);

	// Column win checks
	if (board[0][0] == noughtorcross && board[1][0] == noughtorcross && board[2][0] == noughtorcross) gameWin(noughtorcross);
	if (board[0][1] == noughtorcross && board[1][1] == noughtorcross && board[2][1] == noughtorcross) gameWin(noughtorcross);
	if (board[0][2] == noughtorcross && board[1][2] == noughtorcross && board[2][2] == noughtorcross) gameWin(noughtorcross);
	// Diagonal win checks
	if (board[0][0] == noughtorcross && board[1][1] == noughtorcross && board[2][2] == noughtorcross) gameWin(noughtorcross);
	if (board[0][2] == noughtorcross && board[1][1] == noughtorcross && board[2][0] == noughtorcross) gameWin(noughtorcross);
	

}
void drawCheck(const char board[][gameSize])
{
	int drawCount = 0;
	for (int c(0); c < 3; c++)  // Check the board for Noughts and Crosses, add them up using drawCount variable
	{
		for (int r(0); r < 3; r++)
		{
			if (board[c][r] == 'X' || board[c][r] == 'O')
			{
				drawCount = drawCount + 1;
			}
		}
	}

	if (drawCount == 9) // If the amount of Noughts and Crosses in the array is equal to 9 (aka the board is filled), end the game and output to the users that it's a draw
	{
		gameWon = true;
		cout << "It's a draw!" << endl; 
	}
}
void gameWin(const char noughtorcross)
{
	if (currentTurn == 1 && playerChar == 'X') // If the game has been won on the player's turn and they are Crosses
	{
		gameWon = true;
		cout << "Congratulations " << playerName << "(Crosses), you win!" << endl;
	}
	else if (currentTurn == 1 && playerChar == 'O') // If the game has been won on the player's turn and they are Noughts
	{
		gameWon = true;
		cout << "Congratulations " << playerName << "(Noughts), you win!" << endl;
	}
	else if (currentTurn == 2 && compChar == 'X') // If the game has been won on the computer's turn and it is Crosses
	{
		gameWon = true;
		cout << "The computer (Crosses) wins!" << endl;
	}
	else if (currentTurn == 2 && compChar == 'O') // If the game has been won on the computer's turn and it is Noughts
	{
		gameWon = true;
		cout << "The computer (Noughts) wins!" << endl;
	}
}
void playerTurn()
{
	cout << playerName << " (" << playerChar << ") " << " enter your choice : ";
	cin >> playerChoice; 
	if (cin.fail()) // If the player did not enter an integer, force another input
	{
		cin.clear(); cin.ignore();
	}
	checkTurn(board, playerChoice); // Check the players turn using the checkTurn function, using the board array and the player's turn choice
	while (turnCheck == false) // If the number chosen was already occupied with a Nought or Cross, or the number input was above 9 or below 1, force another input
	{
		cout << "Input error, please select a space not occupied between 1 and 9:" << endl;
		cout << "Enter your choice : ";
		cin >> playerChoice;
		if (cin.fail())
		{
			cin.clear(); cin.ignore();
		}
		checkTurn(board, playerChoice);
	}
	turnCheck = false;
}
void checkTurn(const char board[][gameSize], char choice)
{
	for (int c(0); c < 3; c++) // Check through the array using the number choice of the space the player or computer wants to play for their turn
	{
		for (int r(0); r < 3; r++)
		{
			if (choice == board[c][r]) // If their choice is equal to a number still in the board, set the turnCheck variable to true 
			{
				turnCheck = true;
			}
		}
	}
} 
void computerTurn()
{
	srand(time(0)); //Seeds the pseudo-random number generator
	int compNum = rand() % 9 + 1; // Produce a random number between 0 and 8 and add 1, makes a random choice between 1 and 9. (VALIDATION NOT INCLUDED)
	compChoice = '0' + compNum; // To avoid bugs introduced by making the compNum variable directly assigned to the compChoice variable, compChoice is assigned '0' and compNum is added to it.
	checkTurn(board, compChoice);
	while (turnCheck == false) // If the turn check comes back false, force the computer to create a new random number to try
	{
		compNum = rand() % 9 + 1;
		compChoice = '0' + compNum;
		checkTurn(board, compChoice);
	}
	turnCheck = false; // reset the turnCheck variable for the next turn
	cout << "The computer has chosen : " << compChoice << endl;

}
void changePlayer() // Swap from player turn to computer turn
{
	if (currentTurn == 1)
	{
		currentTurn = 2;
	}
	else if (currentTurn == 2)
	{
		currentTurn = 1;
	}
}