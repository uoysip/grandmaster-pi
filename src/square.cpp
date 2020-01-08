/** @file Square.cpp
 *  @brief Controls the square of the chess board.
 *
 *  This file determines when moving a piece what is the current
 *  status on the board
 *
 *  @author Hasan Ahmed (sahme339).
 *  @bug no known bugs.
 */

/** -- Includes -- **/
#include "Square.h"

using namespace std;
using namespace cv;

/** @brief The constructor class
 *
 *  This is the constructor class for the Square class.
 *
 * @param PLACEHOLDER
 */
Square::Square(Mat* _image, Point2f _topLeft, Point2f _topRight, Point2f _bottomLeft, Point2f _bottomRight, Point2f _roi, string _position, char _state) {
  // set corners of the square
  topLeft = _topLeft;
  topRight = _topRight;
  bottomLeft = _bottomLeft;
  bottomRight = _bottomRight;

  // set Range of Interest (ROI)
  roi = _roi;
  radius = 20;
  // set the position (e.g.: "c3", "d5", etc...)
  position = _position;

  // set the color of the square when there is no pieces on it
  emptyColor = roiColor(_image);
  // cout << "The Square at " << position << " has an empty color of: " << emptyColor << "." << endl;

  // set the state (current item on the square) [not required!]
  state = _state;
}

/**
*   @brief contructor to copy a square 
*  
*   @param square to copy
**/
Square::Square(const Square& s) {
  topLeft = s.topLeft;
  topRight = s.topRight;
  bottomLeft = s.bottomLeft;
  bottomRight = s.bottomRight;

  roi = s.roi;

  radius = s.radius;

  position = s.position;

  emptyColor = s.emptyColor;

  state = s.state;
}


/**
*   @brief simple setter function 
*  
*   @param state to set
**/
void Square::setState(char _state) {
  state = _state;
}

/**
*   @brief simple getter function 
*  
*   @preturn state 
**/
char Square::getState() {
  return state;
}

/**
*   @brief simple setter function 
*  
*   @param position to set
**/
void Square::setPosition(string _position) {
  position = _position;
}

/**
*   @brief simple getter function 
*  
*   @preturn position to get
**/
string Square::getPosition() {
  return position;
}

/**
*   @brief simple getter function 
*  
*   @return scalar represetning colour
**/
Scalar Square::getEmptyColor() {
  return emptyColor;
}

Point2f Square::getROI() {
  return roi;
}

/**
*   @brief creates a mask and gets the average colour in that mask 
*  
*   @param source file to find mask of
**/
Scalar Square::roiColor(Mat* src) {
  // cout << "The ROI for square " << position << " is roi.x = " << roi.x << ", roi.y = " << roi.y << endl;

  Rect r(roi.x, roi.y, radius * 2, radius * 2);
  // cout << " before rect image construct" << endl;
  Mat rectImg(*src, r);
  // cout << "...Done.. Creating mask:" << endl;
  Mat mask(rectImg.size(), rectImg.type(), Scalar::all(0));
  // cout << "...Done...creating circle:" << endl;
  circle(mask, Point(radius, radius), radius, Scalar::all(255), -1);
  Mat cropped = rectImg & mask;
  // Mat mask = Mat::zeros(src->size(), src->type(), Scalar::all(0));
  // circle(mask, roi, radius, Scalar(255, 0, 0), -1);
  Scalar average_raw = cv::mean(cropped);
  // may crash here, 0 should be 1, 1 should be 2, 2 should be 3
  // Scalar average((int)average_raw[0], (int)average_raw[1], (int)average_raw[2]);
  Scalar average((int)average_raw[0], (int)average_raw[1], (int)average_raw[2]);

  return average;
}

/*
  def roiColor(self, image):
    # Initialise mask
    maskImage = np.zeros((image.shape[0], image.shape[1]), np.uint8)
    # Draw the ROI circle on the mask
    cv2.circle(maskImage, self.roi, self.radius, (255, 255, 255), -1)
    # Find the average colorEdges
    # return the mean in reverse??????? why..
    average_raw = cv2.mean(image, mask=maskImage)[::-1]
    # Need int format so reassign variable
    average = (int(average_raw[1]), int(average_raw[2]), int(average_raw[3]))

    return average

 */
