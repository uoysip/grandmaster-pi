/** @file Driver.cpp
*  	@brief This is the main game Driver file.
*
*  	This file is the Driver file for the chess game.
*
*  	@author Dishon Merkhai (dmerkhai).
*  	@author Fraser Brown (fbrown5).
*
*  	@bug no known bugs.
*/

/** -- Includes -- **/
#include "Game.h"


using namespace std;
using namespace cv;

/** @brief This is the main function.
*
*  	When this program is ran a chess game is started.
*	Set-up to receive input from an IP webcam or an image from the computer.
*	
*	@param Expects two arguments:
* 	First being the path to the url or image on machine.
* 	Second is true or false indicating whether or not it is a URL.
* 
* 	@return void.
*/
int main(int argc, char** argv)
{   
	char t[] = "true";
	char f[] = "false";
	ComputerVision camera;
	Mat previousImage, currentImage, computerImage;
	Game game;
	String playerMove, computerMove;

	// Checking for argument validity
    if (argc != 3)
    {
    	cout << "Invalid number of arguments!" << endl;
    	cout << "Correct argument is ./Driver imagePath/URL true/false" << endl;
		exit(EXIT_FAILURE);
	}

	// Correct number of arguments creating camera object.
	else
	{
		if (strcmp(argv[2],t) == 0) 
			camera.setPath(argv[1], true);
		else if (strcmp(argv[2],f) == 0)
			camera.setPath(argv[1], false);
		else
		{
			cout << "Invalid argument 2" << endl;
			cout << "Expected 'true' or 'false'" << endl;
			exit(EXIT_FAILURE);
		}
	}
	game.newGame();

	cout << "Set up the board without any pieces for calibration..." << endl;
	cout << "Press enter when you are ready." << endl;
	getchar();

	// Take image to set values of ROI in chessboard
	Board board = camera.getBoard();

	cout << "When gameboard is setup press enter:" << endl;
	getchar();

	// Get image for before player move
	previousImage = camera.takePicture();

	
	while (!game.gameOver())
	{
		cout << "Waiting for player move..." << endl;
		getchar();
		
		// Get image for after player move
		currentImage = camera.takePicture();

		// cout << "Address" << &board.getBoard()[0]<< endl;
		// cout << "ROI " << board.getBoard()[0]->getROI() << endl;
		
		// Get computers move from server if blank then the move is invalid
		playerMove = game.playerMove(&previousImage, &currentImage, &board);

		computerMove = game.CPUMove(playerMove);



		// Checks if player made an invalid move
		// Makes them repeat until a valid move is made
		while (computerMove.compare("N,one") == 0)
		{
			game.goBackMove();
			cout << "Not a valid move try again." << endl;
			cout << "Press enter when done." << endl;
			getchar();
			currentImage = camera.takePicture();
			playerMove = game.playerMove(&previousImage, &currentImage, &board);
			computerMove = game.CPUMove(playerMove);
		}

		// Resetting images for before and after computer move
		previousImage = currentImage;


		cout << "Please move the Computer's Piece: " << computerMove << endl;
		cout << "Press enter when done." << endl;
		getchar();
		currentImage = camera.takePicture();


		while (!game.checkCPUMove(&previousImage, &currentImage, &board, computerMove))
		{
			cout << "That is not where the computer moved! It moved: " << computerMove << endl;
			cout << "Try again and press enter when done." << endl;
			getchar();
			currentImage = camera.takePicture();
		}

		previousImage = currentImage;
	}


	cout << "Hope you enjoyed playing!" << endl;

	return 1;
}
