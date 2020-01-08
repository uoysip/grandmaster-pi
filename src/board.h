/** @file Board.h
 *  @brief Header file for the Board.cpp file.
 *
 *  This file is the header file for the Board.cpp file and declares the
 *  interface to parts of the operating system.
 *
 *  @author Dishon Merkhai (dmerkhai).
 *  @bug no known bugs.
 */
/** -- Includes -- **/
#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <string.h>
#include <utility>
#include <cstring>
#include <cmath>
#include "Square.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>





class Board
{
    /** --  Access Specifier for Private -- **/
    private:
      std::vector<Square*> board;
      bool promo;

    /** -- Access Specifier for Protected -- **/
    protected:

    /** --  Access Specifier for Public -- **/
    public:

      /** --  Call Board -- **/
      Board(std::vector<Square*> _board);
      
      /** --  deconstructor -- **/
      ~Board();
      /** --  getter for Board -- **/
      std::vector<Square*> getBoard();


      /** --  deleting piece off the board -- **/
      void deletePiece(int col, int row);
      void startBoard();


      /** -- Check if the current board configuration matches the initial board configuration -- **/
      bool checkBoard();

      /** -- finding the changes between the previous board and current board -- **/
      std::string determineChanges(cv::Mat* prev_img, cv::Mat* curr_img);

    
};

#endif
