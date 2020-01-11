#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h> 
#include <conio.h>
#include <windows.h>
#include <time.h>

using namespace std;



// ---------- FUNCTION PROTOTYPES ---------- \\


void displayMenu(int credit, bool &playSelected); // displays initial menu
void getLines(int &lines); // asks user how many lines they would like to bet on
void getBet(int credit, int &bet); // asks user for bet
void fillWheel(char wheel[7]); // fills wheels with characters
void shuffleWheel(char wheel[7]); // shuffles wheels in random order
void spinWheels(char wheelA[7], char wheelB[7], char wheelC[7], int credit, int bet, int lines, bool slowSpins); // checks for user input to stop wheels spinning
void displayWheels(char wheelA[7], char wheelB[7], char wheelC[7], int credit, int bet, int lines, bool slowSpins); // outputs wheels spinning
void slideArray(char wheel[7]); // goes through wheel arrays so they appear to spin
void checkWin(char wheelA[7], char wheelB[7], char wheelC[7], int lines, int &jCounter, int &wCounter, int &lCounter); // checks if columns have matched
void calculatePayout(int &credit, int bet, int &jCounter, int &wCounter, int &lCounter); // calculates payout depending on lines and bet
void showResults(char wheelA[7], char wheelB[7], char wheelC[7], int credit, bool &playSelected, int lines, int bet, int &jCounter, int &wCounter, int &lCounter, bool &slowSpins); // displays final wheel state and prize
void displayWheelResults(char wheelA[7], char wheelB[7], char wheelC[7], int credit, int lines, int bet); // displays final wheel state
void displayWin(int &jCounter, int &wCounter, int &lCounter); // displays prize won
void endScreen(); // if user quits



// ---------- PROGRAM ---------- \\


HANDLE hconsole;


void Set_Color(int fcolor, int bcolor = 0) // for setting console output colour
{
	// open i/o channel to console screen
	hconsole = CreateFile(TEXT("CONOUT$"), GENERIC_WRITE | GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_WRITE,
		0L, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0L);

	// this function sets the color of the console output
	SetConsoleTextAttribute(hconsole, (WORD)((bcolor << 4) |
		fcolor));
}


int main()
{

	// ---------- DECLARATIONS ---------- \\

	char wheelA[7], wheelB[7], wheelC[7]; // wheels for slot machine
	
	int credit = 100, bet = 0, lines = 0; // users items
	int jCounter = 0, wCounter = 0, lCounter = 0; // count of all wins

	bool playSelected = true; // if user has chosen to play
	bool slowSpins = false; // if user has chosen slow spins


	srand(time(NULL)); // seed for random number

	displayMenu(credit, playSelected); // displays initial menu

	while (playSelected) // only runs while user wants to play
	{
		getLines(lines); // asks user how many lines they would like to bet on
		getBet(credit, bet); // asks user for bet
		fillWheel(wheelA); // fills wheel A with characters
		fillWheel(wheelB); // fills wheel B with characters
		fillWheel(wheelC); // fills wheel C with characters
		shuffleWheel(wheelA); // shuffles wheel A in random order
		shuffleWheel(wheelB); // shuffles wheel B in random order
		shuffleWheel(wheelC); // shuffles wheel C in random order
		spinWheels(wheelA, wheelB, wheelC, credit, bet, lines, slowSpins); // checks for user input to stop wheels spinning
		checkWin(wheelA, wheelB, wheelC, lines, jCounter, wCounter, lCounter); // checks if columns have matched
		calculatePayout(credit, bet, jCounter, wCounter, lCounter); // calculates payout depending on lines and bet
		showResults(wheelA, wheelB, wheelC, credit, playSelected, lines, bet, jCounter, wCounter, lCounter, slowSpins); // displays final wheel state and prize
	}

	endScreen(); // displays if user chooses to quit

	return 0;
}



// ---------- USER INTERACTION ---------- \\


void displayMenu(int credit, bool &playSelected)
{
	bool flash = true; // flashes title

	while (flash == true) // flashes text
	{
		Set_Color(rand() % (14 - 1 + 1) + 1, 0); // sets colour to change randomly

		cout << endl;
		cout << " $$$$$$$$\\               $$\\  $$\\           $$\\      $$\\                  $$\\      $$\\ " << endl;
		cout << " $$  _____|              \\__| $$ |          $$$\\    $$$ |                 $$ |     \\__|" << endl;
		cout << " $$ |   $$$$$$\\ $$\\   $$\\$$\\$$$$$$\\         $$$$\\  $$$$ |$$$$$$\\  $$$$$$$\\$$$$$$$\\ $$\\$$$$$$$\\  $$$$$$\\ " << endl;
		cout << " $$$$$\\$$  __$$\\$$ |  $$ $$ \\_$$  _|        $$\\$$\\$$ $$ |\\____$$\\$$  _____$$  __$$\\$$ $$  __$$\\$$  __$$\\ " << endl;
		cout << " $$  __$$ |  \\__$$ |  $$ $$ | $$ |          $$ \\$$$  $$ |$$$$$$$ $$ /     $$ |  $$ $$ $$ |  $$ $$$$$$$$ |" << endl;
		cout << " $$ |  $$ |     $$ |  $$ $$ | $$ |$$\\       $$ |\\$  /$$ $$  __$$ $$ |     $$ |  $$ $$ $$ |  $$ $$   ____|" << endl;
		cout << " $$ |  $$ |     \\$$$$$$  $$ | \\$$$$  |      $$ | \\_/ $$ \\$$$$$$$ \\$$$$$$$\\$$ |  $$ $$ $$ |  $$ \\$$$$$$$\\ " << endl;
		cout << " \\__|  \\__|      \\______/\\__|  \\____/       \\__|     \\__|\\_______|\\_______\\__|  \\__\\__\\__|  \\__|\\_______|" << endl;
		cout << endl << endl << endl << endl;

		Set_Color(15, 0); // sets colour back to default

		cout << "                                     " << "Your current credit is: " << char(156) << credit << endl << endl; // displays current credit
		cout << "                                     " << "Press P to Play or Q to Quit."; // asks for key press

		if (_kbhit()) // checks key press
		{
			if (toupper(_getch()) == 'P') // if P key is pressed, play game
			{
				playSelected = true;
				break;
			}

			else if (toupper(_getch()) == 'Q') // if Q key is pressed, quit game
			{
				playSelected = false;
				break;
			}
		}

		Sleep(300);
		system("cls");
	}
}


void getLines(int &lines)
{
	cout << endl << endl << "                " << "How many lines would you like to bet on? Enter a number between 1 and 3: ";
	cin >> lines; //store lines to bet on

	while (lines <= 0 || lines > 3) // check lines is between 1 and 3
	{
		cout << endl << "                          " << "That is invalid. Please enter a value between 1 and 3: " << endl;
		cin >> lines;
	}
}


void getBet(int credit, int &bet)
{
	cout << endl << "                                        " << "Please enter your bet: ";
	cin >> bet; // stores bet

	while (bet <= 0 || bet > credit) // checks user has enough credit and bet is above 0
	{
		cout << endl << "                            " << "Your bet was invalid. Please enter a valid bet: ";
		cin >> bet;
	}
}


void endScreen()
{
	cout << endl << endl << "                                        " << "Thank you for playing!" << endl; // game has ended
}



// ---------- WHEELS ---------- \\


void fillWheel(char wheel[7])
{
	char symbols[7] = { '7', '0', 'X', '$', '?', '#', '+' }; // symbols to display on wheels

	for (int i = 0; i < 7; i++)
	{
		wheel[i] = symbols[i]; // fills wheel arrays with symbols
	}
}


void shuffleWheel(char wheel[7])
{
	for (int i = 0; i < 7; i++) // shuffles array so symbols are in random order
	{
		int random = rand() % 7;

		// generate a random position
		int temp = wheel[i];

		wheel[i] = wheel[random];

		wheel[random] = temp;
	}
}


void spinWheels(char wheelA[7], char wheelB[7], char wheelC[7], int credit, int bet, int lines, bool slowSpins)
{
	bool spinWheelA = true, spinWheelB = true, spinWheelC = true; // if wheels should spin
	bool gameRunning = true; // wheels spin while true

	system("cls");

	while (gameRunning)
	{
		displayWheels(wheelA, wheelB, wheelC, credit, bet, lines, slowSpins); // outputs wheels spinning

		if (spinWheelA && spinWheelB && spinWheelC) // all wheels spinning
		{
			if (_kbhit())
			{

				if (_getch() == ' ' || _getch() == 32)
				{
					spinWheelA = false; // stops first wheel spinning if spacebar has been pressed
				}
			}

			slideArray(wheelA); // spins wheel A
			slideArray(wheelB); // spins wheel B
			slideArray(wheelC); // spins wheel C
		}

		else if (!spinWheelA && spinWheelB && spinWheelC) // first wheel has stopped
		{
			if (_kbhit())
			{

				if (_getch() == ' ' || _getch() == 32)
				{
					spinWheelB = false; // stops second wheel spinning if spacebar has been pressed again
				}
			}

			slideArray(wheelB); // spins wheel B
			slideArray(wheelC); // spins wheel C
		}

		else if (!spinWheelA && !spinWheelB && spinWheelC) // third wheel spinning
		{
			if (_kbhit())
			{
				if (_getch() == ' ' || _getch() == 32)
				{
					spinWheelC = false; // stops third wheel spinning if spacebar has been pressed again
				}
			}

			slideArray(wheelC); // spins wheel C
		}

		else if (!spinWheelA && !spinWheelB && !spinWheelC)
		{
			gameRunning = false; // if all wheels have been stopped, stop game
		}

		Sleep(100);

		system("cls");
	}

	if (!gameRunning)
	{
		system("cls");

		cout << "Your current credit is: " << char(156) << credit << endl << endl; // displays current credit

		displayWheelResults(wheelA, wheelB, wheelC, credit, lines, bet); // displays final wheel state
	}
}


void slideArray(char wheel[7])
{
	// slides array one place so wheels appear to be spinning

	char temp = wheel[6];

	wheel[6] = wheel[5];
	wheel[5] = wheel[4];
	wheel[4] = wheel[3];
	wheel[3] = wheel[2];
	wheel[2] = wheel[1];
	wheel[1] = wheel[0];
	wheel[0] = temp;
}



// ---------- DISPLAYS ---------- \\


void displayWheels(char wheelA[7], char wheelB[7], char wheelC[7], int credit, int bet, int lines, bool slowSpins)
{
	// wheel output

	if (credit >= 0 && credit <= 9)
	{
		cout << "   " << "   " << "Your current credit is: " << char(156) << credit << "  " << "   " << "|" << "               " << "|" << "                      " << "PRIZES:" << "                     " << "|" << endl;
	}

	if (credit >= 10 && credit <= 99)
	{
		cout << "   " << "  " << "Your current credit is: " << char(156) << credit << "  " << "   " << "|" << "               " << "|" << "                      " << "PRIZES:" << "                     " << "|" << endl;
	}

	if (credit >= 100 && credit <= 999)
	{
		cout << "    " << " " << "Your current credit is: " << char(156) << credit << " " << "   " << "|" << "               " << "|" << "                      " << "PRIZES:" << "                     " << "|" << endl;
	}

	if (credit >= 1000 && credit <= 9999)
	{
		cout << "   " << " " << "Your current credit is: " << char(156) << credit << " " << "   " << "|" << "               " << "|" << "                      " << "PRIZES:" << "                     " << "|" << endl;
	}

	if (credit >= 10000 && credit <= 99999)
	{
		cout << "   " << "Your current credit is: " << char(156) << credit << " " << "   " << "|" << "               " << "|" << "                      " << "PRIZES:" << "                     " << "|" << endl;
	}

	cout << "-------------------------------------+" << "               " << "|" << "**************************************************" << "|" << endl;

	if (bet >= 1 && bet <= 9)
	{
		cout << "        " << "Betting " << char(156) << bet << " on " << lines << " lines." << "    " << "   " << "|" << "               " << "|" << "   " << "Match 3 columns - Jackpot! Win 10 times bet." << "   " << "|" << endl;
	}

	else if (bet >= 10 && bet <= 99)
	{
		cout << "      " << "Betting " << char(156) << bet << " on " << lines << " lines." << "  " << "   " << "|" << "               " << "|" << "   " << "Match 3 columns - Jackpot! Win 10 times bet." << "   " << "|" << endl;
	}

	else if (bet >= 100 && bet <= 999)
	{
		cout << "     " << "Betting " << char(156) << bet << " on " << lines << " lines." << "  " << "   " << "|" << "               " << "|" << "   " << "Match 3 columns - Jackpot! Win 10 times bet." << "   " << "|" << endl;
	}

	else if (bet >= 1000 && bet <= 9999)
	{
		cout << "     " << "Betting " << char(156) << bet << " on " << lines << " lines." << " " << "   " << "|" << "               " << "|" << "   " << "Match 3 columns - Jackpot! Win 10 times bet." << "   " << "|" << endl;
	}

	else if (bet >= 10000 && bet <= 99999)
	{
		cout << "    " << "Betting " << char(156) << bet << " on " << lines << " lines." << " " << "   " << "|" << "               " << "|" << "   " << "Match 3 columns - Jackpot! Win 10 times bet." << "   " << "|" << endl;
	}

	cout << "-------------------------------------+               " << "|" << "                                                  " << "|" << endl;
	cout << "                                                     " << "|" << "   " << "     " << "Match 2 columns - Win 5 times bet." << "     " << "   " << "|" << endl;
	cout << "                                                     " << "+" << "--------------------------------------------------" << "+" << endl << endl << endl << endl;

	Set_Color(rand() % (14 - 1 + 1) + 1, 0); // randomises colour of wheels while spinning

	cout << "                                           " << "+-----------------------+" << endl; //41
	cout << "                                           " << "|" << "       *" << "       *" << "       |" << endl;

	if (lines > 1)
	{
		cout << "                               " << ">->->->->" << "   " << "|" << "   " << wheelA[0] << "   " << "*" << "   " << wheelB[0] << "   " << "*" << "   " << wheelC[0] << "   " << "|" << "   " << "<-<-<-<-<" << endl;
	}

	else
	{
		cout << "                                           " << "|" << "   " << wheelA[0] << "   " << "*" << "   " << wheelB[0] << "   " << "*" << "   " << wheelC[0] << "   " << "|" << "      " << endl;
	}

	cout << "                                           " << "|" << "       *       *" << "       |" << endl;
	cout << "                               " << ">->->->->" << "   " << "|" << "   " << wheelA[1] << "   " << "*" << "   " << wheelB[1] << "   " << "*" << "   " << wheelC[1] << "   " << "|" << "   " << "<-<-<-<-<" << endl;
	cout << "                                           " << "|" << "       *       *" << "       |" << endl;

	if (lines == 3)
	{
		cout << "                               " << ">->->->->" << "   " << "|" << "   " << wheelA[2] << "   " << "*" << "   " << wheelB[2] << "   " << "*" << "   " << wheelC[2] << "   " << "|" << "   " << "<-<-<-<-<" << endl;
	}

	else
	{
		cout << "                                           " << "|" << "   " << wheelA[2] << "   " << "*" << "   " << wheelB[2] << "   " << "*" << "   " << wheelC[2] << "   " << "|" << "      " << endl;
	}

	cout << "                                           " << "|" << "       *" << "       *" << "       |" << endl;
	cout << "                                           " << "+-----------------------+" << endl << endl << endl;

	Set_Color(15, 0); // sets colour back to default for everything else

	cout << "                                     " << "Press the spacebar to stop the wheels!";

	if (!slowSpins)
	{
		Sleep(10); // spins rapidly
	}

	else
	{
		Sleep(500); // spins slower
	}
}


void showResults(char wheelA[7], char wheelB[7], char wheelC[7], int credit, bool &playSelected, int lines, int bet, int &jCounter, int &wCounter, int &lCounter, bool &slowSpins)
{
	char input = 'X'; // if users wants to play again

	cout << "Your current credit is: " << char(156) << credit << endl << endl;

	displayWheelResults(wheelA, wheelB, wheelC, credit, lines, bet); // displays final wheel state
	displayWin(jCounter, wCounter, lCounter); // tells user what they have won

	if (credit > 0) // checks user has credit
	{
		cout << endl << endl << "                          " << "Type P to Play Again, S to toggle Slow Spins or Q to Quit: ";
		cin >> input;
	}

	else // if user doesn't have credit, return to menu
	{
		playSelected = false;
		endScreen();
	}

	switch (input)
	{

	case 'P': case 'p':

		playSelected = true; // if user chooses to play again, run game again
		break;

	case 'S': case 's':

		if (slowSpins == false)
		{
			slowSpins = true; // turn slow spins on
		}

		else
		{
			slowSpins = false; // turn slow spins off
		}

		cout << endl << "                                              " << "Slow spins toggled.";
		break;


	case 'Q': case 'q':

		playSelected = false; // if user chooses to quit, quit game
		break;


	case 'X': case 'x':

		break;


	default:

		cout << "Invalid selection. Type P to Play Again or Q to Quit: " << endl; // makes sure input is valid
		cin >> input;
		break;
	}
}


void displayWheelResults(char wheelA[7], char wheelB[7], char wheelC[7], int credit, int lines, int bet)
{
	// displays final wheel state

	system("cls");

	if (credit >= 0 && credit <= 9)
	{
		cout << "   " << "   " << "Your current credit is: " << char(156) << credit << "  " << "   " << "|" << "               " << "|" << "                      " << "PRIZES:" << "                     " << "|" << endl;
	}

	if (credit >= 10 && credit <= 99)
	{
		cout << "   " << "  " << "Your current credit is: " << char(156) << credit << "  " << "   " << "|" << "               " << "|" << "                      " << "PRIZES:" << "                     " << "|" << endl;
	}

	if (credit >= 100 && credit <= 999)
	{
		cout << "    " << " " << "Your current credit is: " << char(156) << credit << " " << "   " << "|" << "               " << "|" << "                      " << "PRIZES:" << "                     " << "|" << endl;
	}

	if (credit >= 1000 && credit <= 9999)
	{
		cout << "   " << " " << "Your current credit is: " << char(156) << credit << " " << "   " << "|" << "               " << "|" << "                      " << "PRIZES:" << "                     " << "|" << endl;
	}

	if (credit >= 10000 && credit <= 99999)
	{
		cout << "   " << "Your current credit is: " << char(156) << credit << " " << "   " << "|" << "               " << "|" << "                      " << "PRIZES:" << "                     " << "|" << endl;
	}

	cout << "-------------------------------------+" << "               " << "|" << "**************************************************" << "|" << endl;

	if (bet >= 1 && bet <= 9)
	{
		cout << "        " << "Betting " << char(156) << bet << " on " << lines << " lines." << "    " << "   " << "|" << "               " << "|" << "   " << "Match 3 columns - Jackpot! Win 10 times bet." << "   " << "|" << endl;
	}

	else if (bet >= 10 && bet <= 99)
	{
		cout << "      " << "Betting " << char(156) << bet << " on " << lines << " lines." << "  " << "   " << "|" << "               " << "|" << "   " << "Match 3 columns - Jackpot! Win 10 times bet." << "   " << "|" << endl;
	}

	else if (bet >= 100 && bet <= 999)
	{
		cout << "     " << "Betting " << char(156) << bet << " on " << lines << " lines." << "  " << "   " << "|" << "               " << "|" << "   " << "Match 3 columns - Jackpot! Win 10 times bet." << "   " << "|" << endl;
	}

	else if (bet >= 1000 && bet <= 9999)
	{
		cout << "     " << "Betting " << char(156) << bet << " on " << lines << " lines." << " " << "   " << "|" << "               " << "|" << "   " << "Match 3 columns - Jackpot! Win 10 times bet." << "   " << "|" << endl;
	}

	else if (bet >= 10000 && bet <= 99999)
	{
		cout << "    " << "Betting " << char(156) << bet << " on " << lines << " lines." << " " << "   " << "|" << "               " << "|" << "   " << "Match 3 columns - Jackpot! Win 10 times bet." << "   " << "|" << endl;
	}

	cout << "-------------------------------------+               " << "|" << "                                                  " << "|" << endl;
	cout << "                                                     " << "|" << "   " << "     " << "Match 2 columns - Win 5 times bet." << "     " << "   " << "|" << endl;
	cout << "                                                     " << "+" << "--------------------------------------------------" << "+" << endl << endl << endl << endl;
	cout << "                                           " << "+-----------------------+" << endl; //41
	cout << "                                           " << "|" << "       *" << "       *" << "       |" << endl;

	if (lines > 1)
	{
		cout << "                               " << ">->->->->" << "   " << "|" << "   " << wheelA[0] << "   " << "*" << "   " << wheelB[0] << "   " << "*" << "   " << wheelC[0] << "   " << "|" << "   " << "<-<-<-<-<" << endl;
	}

	else
	{
		cout << "                                           " << "|" << "   " << wheelA[0] << "   " << "*" << "   " << wheelB[0] << "   " << "*" << "   " << wheelC[0] << "   " << "|" << "      " << endl;
	}

	cout << "                                           " << "|" << "       *       *" << "       |" << endl;
	cout << "                               " << ">->->->->" << "   " << "|" << "   " << wheelA[1] << "   " << "*" << "   " << wheelB[1] << "   " << "*" << "   " << wheelC[1] << "   " << "|" << "   " << "<-<-<-<-<" << endl;
	cout << "                                           " << "|" << "       *       *" << "       |" << endl;

	if (lines == 3)
	{
		cout << "                               " << ">->->->->" << "   " << "|" << "   " << wheelA[2] << "   " << "*" << "   " << wheelB[2] << "   " << "*" << "   " << wheelC[2] << "   " << "|" << "   " << "<-<-<-<-<" << endl;
	}

	else
	{
		cout << "                                           " << "|" << "   " << wheelA[2] << "   " << "*" << "   " << wheelB[2] << "   " << "*" << "   " << wheelC[2] << "   " << "|" << "      " << endl;
	}

	cout << "                                           " << "|" << "       *" << "       *" << "       |" << endl;
	cout << "                                           " << "+-----------------------+" << endl << endl;
}


void displayWin(int &jCounter, int &wCounter, int &lCounter)
{
	// tells user what they have won

	if (lCounter > 0 && jCounter == 0 && wCounter == 0) // if there has only been a loss
	{
		cout << endl << "                                   " << "You matched no columns and lost your bet!";
	}

	if (jCounter > 0) // if there has been a jackpot
	{
		cout << endl << "                                " << "You hit the jackpot! You win 10 times your bet!";
	}

	if (wCounter > 0) // if there has been a win
	{
		cout << endl << "                    " << "You matched columns! You win 5 times your bet for each line you matched!";
	}

	jCounter = 0, wCounter = 0, lCounter = 0; // resets counters back to 0 for next game
}



// ---------- PAYOUTS ---------- \\


void checkWin(char wheelA[7], char wheelB[7], char wheelC[7], int lines, int &jCounter, int &wCounter, int &lCounter)
{
	switch (lines)
	{
	case 1: // if betting on one line

		if (wheelA[1] == wheelB[1] == wheelC[1])
		{
			jCounter++; // increment jackpot counter
		}

		else if ((wheelA[1] == wheelB[1] || wheelA[1] == wheelC[1] || wheelB[1] == wheelC[1]) && !(wheelA[1] == wheelB[1] == wheelC[1]))
		{
			wCounter++; // increment win counter
		}

		else
		{
			lCounter++; // increment loss counter
		}

		break;


	case 2: // if betting on two lines

		if (wheelA[0] == wheelB[0] == wheelC[0])
		{
			jCounter++; // increment jackpot counter
		}

		else if ((wheelA[0] == wheelB[0] || wheelA[0] == wheelC[0] || wheelB[0] == wheelC[0]) && !(wheelA[0] == wheelB[0] == wheelC[0]))
		{
			wCounter++; // increment win counter
		}

		else
		{
			lCounter++; // increment loss counter
		}

		if (wheelA[1] == wheelB[1] == wheelC[1])
		{
			jCounter++; // increment jackpot counter
		}

		else if ((wheelA[1] == wheelB[1] || wheelA[1] == wheelC[1] || wheelB[1] == wheelC[1]) && !(wheelA[1] == wheelB[1] == wheelC[1]))
		{
			wCounter++; // increment win counter
		}

		else
		{
			lCounter++; // increment loss counter
		}

		break;


	case 3: // if betting on three lines

		if (wheelA[0] == wheelB[0] == wheelC[0])
		{
			jCounter++; // increment jackpot counter
		}

		else if ((wheelA[0] == wheelB[0] || wheelA[0] == wheelC[0] || wheelB[0] == wheelC[0]) && !(wheelA[0] == wheelB[0] == wheelC[0]))
		{
			wCounter++; // increment win counter
		}

		else
		{
			lCounter++; // increment loss counter
		}

		if (wheelA[1] == wheelB[1] == wheelC[1])
		{
			jCounter++; // increment jackpot counter
		}

		else if ((wheelA[1] == wheelB[1] || wheelA[1] == wheelC[1] || wheelB[1] == wheelC[1]) && !(wheelA[1] == wheelB[1] == wheelC[1]))
		{
			wCounter++; // increment win counter
		}

		else
		{
			lCounter++; // increment loss counter
		}

		if (wheelA[2] == wheelB[2] == wheelC[2])
		{
			jCounter++; // increment jackpot counter
		}

		else if ((wheelA[2] == wheelB[2] || wheelA[2] == wheelC[2] || wheelB[2] == wheelC[2]) && !(wheelA[2] == wheelB[2] == wheelC[2]))
		{
			wCounter++; // increment win counter
		}

		else
		{
			lCounter++; // increment loss counter
		}

		break;


	default:

		cout << "There was an error."; // if something breaks
		break;
	}
}


void calculatePayout(int &credit, int bet, int &jCounter, int &wCounter, int &lCounter)
{
	int jPrize = 10, wPrize = 5; // prize numbers


	if (jCounter > 0) // checks if there has been a jackpot
	{
		credit = credit + (bet * (jCounter * jPrize)); // adds jackpot payout to current creedit
	}

	if (wCounter > 0) // checks if there has been a jackpot
	{
		credit = credit + (bet * (wCounter * wPrize)); // adds win payout to current creedit
	}

	if (lCounter > 0) // checks if there has been a jackpot
	{
		credit = credit - (bet * lCounter); // deducts loss payout to current creedit
	}
}