/** @file Board.cpp
 *  @brief Makes board.
 *
 *  This file determines when moving a piece what is the current
 *  status on the board
 *
 *  @author Dishon Merkhai (dmerkhai)
 *  @bug no known bugs.
 */

/** -- Includes -- **/
#include "Board.h"
using namespace std;

/** @brief Create board.
 *
 *  This is creating the board with the 64 squares that were created in ComputerVision class.
 *
 */
Board::Board(std::vector<Square*> _board) {
  board = _board;
  promo = 0;
}

/** @brief destroys board.
 *
 *  this just destroys the board
 *
 */
Board::~Board() {}


/** @brief getting the board.
 *  @return vector of squares
 */
std::vector<Square *> Board::getBoard() {
  return board;
}

/** @brief getting the start board.
 *
 *  setting up the board for the start
 *  @return void.
 */
void Board::startBoard() {
  char black[] = {'r', 'n', 'b','q','k','b','n','r'};
  char white[] = {'R','N','B','Q','K','B','N','R'};

  for (int i = 0; i < 8; i ++) {
    board[8*i + 0]->setState(black[i]);
    board[8*i + 1]->setState('p');
    board[8*i + 2]->setState('.');
    board[8*i + 3]->setState('.');
    board[8*i + 4]->setState('.');
    board[8*i + 5]->setState('.');
    board[8*i + 6]->setState('P');
    board[8*i + 7]->setState(white[i]);
  }
}

/** @brief determine changes
 *
 *  determubes the squares that changed
 *
 *  @param cv::Mat* prev_img the previous image.
 *  @param cv::Mat* curr_img the current image.
 *  @return return sting for the change.
 */
std::string Board::determineChanges(cv::Mat* prev_img, cv::Mat* curr_img) {
  std::string move("");
  // cv::Mat curr_img_copy = curr_img->copy();

  Square* largestSquare = nullptr;
  Square* secondLargestSquare = nullptr;
  double largestDist = 0;
  double secondLargestDist = 0;
  std::vector<Square> stateChange;

  for (int i = 0; i < 64; i++) {
    cv::Scalar prevColor = board[i]->roiColor(prev_img);
    cv::Scalar currColor = board[i]->roiColor(curr_img);
    // cout << "The previous color for Square " << board.at(i)->getPosition() << ", is: " << prevColor << endl;
    // cout << "The current color for Square " << board.at(i)->getPosition() << ", is: " << currColor << endl;
    // cout << "The empty color for Square " << board.at(i)->getPosition() << ", is: " << board.at(i)->getEmptyColor() << endl;

    double sum = 0;
    for (int j = 0; j < 3; j++) {
      sum += pow((currColor[j] - prevColor[j]), 2);
    }

    double distance = sqrt(sum);

    if (distance > 25) {
      stateChange.push_back(*board.at(i));
    }
   
    
    if (distance > largestDist) {
      secondLargestSquare = largestSquare;
      secondLargestDist = largestDist;
      largestDist = distance;
      largestSquare = board.at(i);

    } else if (distance > secondLargestDist) {
      secondLargestDist = distance;
      secondLargestSquare = board.at(i);

    }
  }

  // if number of statechanges was 4, then castling happened
  if (stateChange.size() == 4) {
    Square squareOne = stateChange[0];
    Square squareTwo = stateChange[1];
    Square squareThree = stateChange[2];
    Square squareFour = stateChange[3];

    //comparing the previous board with the current board returns the move
    if ((squareOne.getPosition().compare("e1") == 0) || (squareTwo.getPosition().compare("e1") == 0) || (squareThree.getPosition().compare("e1") == 0) || (squareFour.getPosition().compare("e1") == 0)) {
      if ((squareOne.getPosition().compare("f1") == 0) || (squareTwo.getPosition().compare("f1") == 0) || (squareThree.getPosition().compare("f1") == 0) || (squareFour.getPosition().compare("f1") == 0)) {
        if ((squareOne.getPosition().compare("g1") == 0) || (squareTwo.getPosition().compare("g1") == 0) || (squareThree.getPosition().compare("g1") == 0) || (squareFour.getPosition().compare("g1") == 0)) {
          if ((squareOne.getPosition().compare("h1") == 0) || (squareTwo.getPosition().compare("h1") == 0) || (squareThree.getPosition().compare("h1") == 0) || (squareFour.getPosition().compare("h1") == 0)) {
            move += "e1,g1";
            return move;
          }
        }
      }
    }


    if ((squareOne.getPosition().compare("d1") == 0) || (squareTwo.getPosition().compare("d1") == 0) || (squareThree.getPosition().compare("d1") == 0) || (squareFour.getPosition().compare("d1") == 0)) {
      if ((squareOne.getPosition().compare("c1") == 0) || (squareTwo.getPosition().compare("c1") == 0) || (squareThree.getPosition().compare("c1") == 0) || (squareFour.getPosition().compare("c1") == 0)) {
        if ((squareOne.getPosition().compare("a1") == 0) || (squareTwo.getPosition().compare("a1") == 0) || (squareThree.getPosition().compare("a1") == 0) || (squareFour.getPosition().compare("a1") == 0)) {
            move += "e1,c1";
            return move;
        }
      }
    }

    if ((squareOne.getPosition().compare("e8") == 0) || (squareTwo.getPosition().compare("e8") == 0) || (squareThree.getPosition().compare("e8") == 0) || (squareFour.getPosition().compare("e8") == 0)) {
      if ((squareOne.getPosition().compare("f8") == 0) || (squareTwo.getPosition().compare("f8") == 0) || (squareThree.getPosition().compare("f8") == 0) || (squareFour.getPosition().compare("f8") == 0)) {
        if ((squareOne.getPosition().compare("g8") == 0) || (squareTwo.getPosition().compare("g8") == 0) || (squareThree.getPosition().compare("g8") == 0) || (squareFour.getPosition().compare("g8") == 0)) {
          if ((squareOne.getPosition().compare("h8") == 0) || (squareTwo.getPosition().compare("h8") == 0) || (squareThree.getPosition().compare("h8") == 0) || (squareFour.getPosition().compare("h8") == 0)) {
            move += "e8,g8";
            return move;
          }
        }
      }
    }


    if ((squareOne.getPosition().compare("d8") == 0) || (squareTwo.getPosition().compare("d8") == 0) || (squareThree.getPosition().compare("d8") == 0) || (squareFour.getPosition().compare("d8") == 0)) {
      if ((squareOne.getPosition().compare("c8") == 0) || (squareTwo.getPosition().compare("c8") == 0) || (squareThree.getPosition().compare("c8") == 0) || (squareFour.getPosition().compare("c8") == 0)) {
        if ((squareOne.getPosition().compare("a8") == 0) || (squareTwo.getPosition().compare("a8") == 0) || (squareThree.getPosition().compare("a8") == 0) || (squareFour.getPosition().compare("a8") == 0)) {
            move += "e8,c8";
            return move;
        }
      }
    }

  }

  // debug lines
  cout << "State change size: " << stateChange.size() << endl;
  for (int i = 0; i < stateChange.size(); i++) {
    cout << "state change " << i << " is " << stateChange.at(i).getPosition() << endl;
  }

  Square squareOne = *largestSquare;
  Square squareTwo = *secondLargestSquare;

  cout << "Square One's position is " << squareOne.getPosition() << "\n Square Two's position is " << squareTwo.getPosition() << endl;
  cv::Scalar oneCurr = squareOne.roiColor(curr_img);
  cv::Scalar twoCurr = squareTwo.roiColor(curr_img);

  double sumCurr1 = 0;
  double sumCurr2 = 0;
  
  for (int j = 0; j < 3; j++) {
      sumCurr1 += pow((oneCurr[j] - squareOne.getEmptyColor()[j]), 2);
      sumCurr2 += pow((twoCurr[j] - squareTwo.getEmptyColor()[j]), 2);

  }

  double distCurr1 = sqrt(sumCurr1);
  double distCurr2 = sqrt(sumCurr2);

  if (distCurr1 < distCurr2) {
    squareTwo.setState(squareOne.getState());
    squareOne.setState('.');

    // check for pawn promotion
    if (squareTwo.getState() == 'P' || squareTwo.getState() == 'p') {
      if ((squareOne.getPosition().at(1) == '2' && squareTwo.getPosition().at(1) == '1') || (squareOne.getPosition().at(1) == '7' && squareTwo.getPosition().at(1) == '8')) {
        promo = 1;
      }
    }
    
    move += squareOne.getPosition();
    move += ",";
    move += squareTwo.getPosition();
  } else {
    squareOne.setState(squareTwo.getState());
    squareTwo.setState('.');

    // check for pawn promotion
    if (squareTwo.getState() == 'P' || squareTwo.getState() == 'p') {
      if ((squareOne.getPosition().at(1) == '1' && squareTwo.getPosition().at(1) == '2') || (squareOne.getPosition().at(1) == '8' && squareTwo.getPosition().at(1) == '7')) {
        promo = 1;
      }
    }

    move += squareTwo.getPosition();
    move += ",";
    move += squareOne.getPosition();

  }

  cout << "The move was: " << move << "." << endl;
  return move;
}