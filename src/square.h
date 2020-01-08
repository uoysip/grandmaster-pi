/** @file Square.h
 *  @brief Header file for the Square.cpp file.
 *
 *  This file is the header file for the Square.cpp file and declares the
 *  interface to parts of the operating system.
 *
 *  @author Hasan Ahmed (sahme339).
 *  @bug no known bugs.
 */
#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>
#include <string.h>
#include <utility>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

extern int validMoveBoard [8] [8];
class Square
{

/** -- public access Specifier -- **/
public:

    /** -- constructor for square -- **/
    Square(cv::Mat* _image, cv::Point2f _topLeft, cv::Point2f _topRight, cv::Point2f _bottomLeft, cv::Point2f _bottomRight, cv::Point2f _roi, std::string _position, char _state = '.');

    /** -- constructor for square to copy a square -- **/
    Square(const Square& s);   
   
    /** --setting state for square -- **/   
    void setState(char _piece);
    
    /** -- getting state of square -- **/
    char getState();
    
    /** -- setting thee position of the piece -- **/
    void setPosition(std::string _position);
    
    /** -- getting squares with no piece -- **/
    cv::Scalar getEmptyColor();
    
    /** -- getting the position -- **/
    std::string getPosition();
    
    /** -- making mask -- **/
    cv::Scalar roiColor(cv::Mat* src);
    
    /** -- getting mask -- **/
    cv::Point2f getROI();

/** -- private access Specifier -- **/
private:

    /** -- ints for column and rows -- **/
    int col;
    int row;

    /** -- opencv variables -- **/
    cv::Mat image;
    cv::Point2f topLeft, topRight, bottomLeft, bottomRight;
    cv::Point2f roi;
    int radius;

    /** -- squares position -- **/
    std::string position;

    /** -- state of square -- **/
    char state;
    cv::Scalar emptyColor;


};

#endif
