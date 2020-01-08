#ifndef COMPUTER_VISION_H
#define COMPUTER_VISION_H
/** -- includes **/
#include <iostream>
#include <string.h>
#include <vector>
#include "Board.h"
#include "Square.h"
#include "curl/curl.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

/** @file computerVision.h
 *  @brief Header file for the computerVision.cpp file.
 *
 *  This file is the header file for the computerVision.cpp file and declares the
 *  interface to parts of the operating system.
 *
 *  @author Dishon Merkhai (dmerkhai).
 *  @bug no known bugs.
 */

class ComputerVision
{
   /** --  Access Specifier for public -- **/
	public:
    
    /** --  empty computerVision constructor -- **/
		ComputerVision();
		
    /** --  constructor for computerVision with file path -- **/
    ComputerVision(char* imagePath, bool isURL = true);
		
    /** -- computerVision deconstructor -- **/
    ~ComputerVision();
		
    /** --  function to get board -- **/
    Board getBoard();
		
    /** --  function to set image path -- **/
    void setPath(char* imagePath, bool isURL);
		
    /** --  Access Specifier for private -- **/
    cv::Mat takePicture(int timeout = 10);
	 	
  /** --  function to write Data to the image -- **/
	private: 

    /** --  function to retrive the image as cv::Mat object -- **/
	 	static size_t writeData(char* ptr, size_t size, size_t nmemb, void* userdata);
	 	
     /** --  function to find all boards indiviudal square corners -- **/
     std::vector<cv::Point2f> findCorners(cv::Mat* source, cv::Mat* destination);
	 	
     /** --  function to draw squares on board image -- **/
    std::vector<Square *> drawSquares(cv::Mat* destination, cv::Mat* source, std::vector<cv::Point2f> corners);

    /** --  variables for open cv -- **/
	 	cv::Mat src, grey, corners, final;
	 
    /** -- bool to determine if its a path or an image -- **/ 
    bool isURL;
	 	/** --  stores image path or url -- **/
    char* imagePath;

};
#endif