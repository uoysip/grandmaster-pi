#ifndef GAME_H
#define GAME_H
/** -- includes **/
#include <iostream>
#include <string.h>
#include "Board.h"
#include "ComputerVision.h"
#include <sstream>
#include "curl/curl.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

/** @file Game.h
 *  @brief Header file for the Game.cpp file.
 *
 *  This file is the header file for the Game.cpp file and declares the
 *  interface to parts of the operating system.
 *
 *  @author Fraser Brown (fbrown5).
 *  @bug no known bugs.
 */
class Game
{
	/** -- Access Specifier for Public -- **/
	public:
		/** --  empty Game constructor -- **/
		Game();
		/** --  detects player making a move -- **/
		std::string playerMove(cv::Mat* previous, cv::Mat* next, Board* board);
		/** --  detects computer move  -- **/
		std::string CPUMove(std::string playerMove);
		/** --  checks if computer output move is made on board -- **/
		bool checkCPUMove(cv::Mat* previous, cv::Mat* next, Board* board, std::string computerMove);
		/** --  detects a checkmate signalling gameover -- **/
		bool gameOver();
		/** --  checks if new game starts -- **/
		void newGame();
		/** --  takes move back if wrong one made -- **/
		void goBackMove();

	/** --  Access Specifier for Private -- **/
	private:
		/** --  allocates size properly -- **/
		static size_t WriteCallBack(void *contents, size_t size, size_t nmemb, void *userp);
		/** --  pieces together URL from packets -- **/
		std::string chessServerURL;
};

#endif
