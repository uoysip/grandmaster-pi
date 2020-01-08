#include "Game.h"
#include <stdio.h>
using namespace std;
using namespace cv;

/** @file Game.cpp
*   @brief This file is a helper file for Driver to process the CPU logic
*   @author dmerkhai
*   @author fbrown5
*   @bugs no known bugs
*/

/**
* @brief constructor, connects to server for computer logic
*/
Game::Game()
{
	chessServerURL = "http://b92ade93.ngrok.io/";
}



/**
* @brief detects state change / player movement
* @returns Returns a string representation of the players move
* @param previous, current, board
* Format "a2,a4"
*/
string Game::playerMove(Mat* previous, Mat* current, Board* board)
{
	return (board->determineChanges(previous, current));
}

/**
* @brief Get string representation of the move from the AI
* @param playerMove
* @returns readBuffer
* Format "a2,a4"
*/
string Game::CPUMove(string playerMove)
{
	CURL *curl;
	CURLcode res;
	string readBuffer, outURL, intermediate;

	  /** Taking the input and cutting it into strings **/
    vector <string> tokens;
    stringstream stream(playerMove);
    while(getline(stream, intermediate, ','))
    {
        tokens.push_back(intermediate);
    }

    /** URL to send request to **/
    outURL = chessServerURL + "move_coordinates_2?from=" + tokens[0] + "&to=" + tokens[1];

  /** Setting up get request for server and sending **/
	curl = curl_easy_init();
	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, outURL.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);
	}
	readBuffer.insert(2, ",");

	/** This should be removed after testing **/
	// cout << "Computer's move is: " << readBuffer << "." << endl;
	return readBuffer;

}

/**
* @brief checks the move made to be what the computer outputted
* @param previous, next, board, computerMove
* @returns whether or not the last computer move is equivalent to what determineChanges returns.
*/
bool Game::checkCPUMove(Mat* previous, Mat* next, Board* board, string computerMove)
{
	if (board->determineChanges(previous, next).compare(computerMove) == 0)
		return true;

	return false;
}

/**
* @brief Asks server if there is a checkmate and if so returns true and ends game.
* @returns bool if checkmate has occured
* @param none 
*/
bool Game::gameOver()
{
	CURL *curl;
	CURLcode res;
	string readBuffer;
	string outURL = chessServerURL + "is_game_over";
	/** setting up get request for server and sending **/
	curl = curl_easy_init();
	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, outURL.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		/** This should be removed after testing **/
		std::cout << "Game is over? " << readBuffer << std::endl;
	}

	if (readBuffer != "abcd")
		return false;
	else
		return true;
}

/**
* @brief This sets up a new game
* @param none
* @return string of new game being started
*/
void Game::newGame()
{
	CURL *curl;
	CURLcode res;
	string readBuffer;
	string outURL = chessServerURL + "new_game";

	/** setting up get request for server and sending **/
	curl = curl_easy_init();
	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, outURL.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		/** This should be removed after testing **/
		std::cout << "New game! " << readBuffer << std::endl;
	}

}

/**
* @brief used to move piece back if user moves it wrong
* @param none
* @returns none
*/
void Game::goBackMove()
{
	CURL *curl;
	CURLcode res;
	string readBuffer;
	string outURL = chessServerURL + "go_back";

	/** setting up get request for server and sending **/
	curl = curl_easy_init();
	if(curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, outURL.c_str());
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallBack);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		/** This should be removed after testing **/
		std::cout << "New game! " << readBuffer << std::endl;
	}
}

/**
* @brief creates stream to get URL from packets and decodes to form
* @param contents, size, nmemb, userp
* @returns allocated size
*/
size_t Game::WriteCallBack(void *contents, size_t size, size_t nmemb, void *userp)
{
	cout<< "here"<<endl;
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}
