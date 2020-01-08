/** -- Includes -- **/
#include "ComputerVision.h"
/**
 * @file computerVision.cpp
 * @brief reads in images of the board from the url provided 
 * 
 * this file determines board configuration from the image
 * @author Dishon Merkhai (dmerkhai)
 * @author Fraser Brown (fbrown5).
 * @bug no known bugs.
 */


using namespace std;
using namespace cv;

/** @brief constructor for the computer image class.
 *
 *  this just saves the the images url or path
 * makes an empty computer image class, no url or path
 *  
 *  @return computerVision object.
 */
ComputerVision::ComputerVision()
{
    imagePath = nullptr;
    isURL = false;
}

/** @brief constructor for the computer image class.
 *
 *  this just saves the the images url or path
 *
 *  @param inImagePath path to the image could be a url
 *  @param inIsURL indicates whether its a path to the file or the url, true if url
 *  @return computerVision object.
 */
ComputerVision::ComputerVision(char* inImagePath, bool inIsURL)
{
    imagePath = inImagePath;
    isURL = inIsURL;
}

/** @brief deconstructor for the computerVision class.
 *
 *  removes all images
 *
 *  @param none
 *  
 */
ComputerVision::~ComputerVision()
{
    if (!src.empty())
        src.release();
    if (!grey.empty())
        grey.release();
    if (!corners.empty())
        corners.release();
    if (!final.empty())
        final.release();
    // delete &currentBoard;
}
/** @brief gets the current board
 *  @param none 
 *  @return a board class
 */
Board ComputerVision::getBoard()
{    
    /**
    * No arguments, get image from IP webcam
    */
    if (isURL == true)
    {
        /**
         * Retrieving image from URL
         * May have to change in future depending on network
         */
        src = takePicture();
       
        /**
         *Succesful load of image
         */
        if (!src.empty())
        {    
            resize(src, src, src.size());
        }

        /**
         * Failed to load image
         */
        else 
        {
            cout << "failed to load image from path URL" << endl;
        }
    } 


   /** 
     * Picture path given load image
     */
    else
    {
        /**
         * Load image from path provided
         */
        src = imread(imagePath, IMREAD_UNCHANGED);

        /**
         * Successful load of image
         */
        if (!src.empty())
        {
            resize(src, src, src.size()); // resize image
        }

        /**
         * failed to load image
         */
        else
        {
            cout << "Failed to load image from given path" << endl;
        }
    }


    /** 
     * Copying source image for drawing lines and such
     */
    corners = src.clone();
    final = src.clone();


    /**
     * Cleaning image for finding corners and drawing squares
     */
    //! doesnt need to be grey!!!!!!!!!
    // cvtColor(src, grey, COLOR_BGR2GRAY);
    Board currentBoard(drawSquares(&final, &src, findCorners(&src, &corners)));

    /**
     * Showing images and exiting
     */
    imshow("Source Image", src);
    waitKey(0);
    imshow("Chessboard corners detection", corners);
    waitKey(0);
    imshow("Final image", final);
    // waitKey(0);
    return currentBoard;
}
/** @brief setting url path.
 *  @param inImagePath path to the image could be a url
 *  @param inIsURL indicates whether its a path to the file or the url, true if url
 *  @return void.
 */
void ComputerVision::setPath(char* inImagePath, bool inIsURL)
{
    imagePath = inImagePath;
    isURL = inIsURL;
}

/** @brief capture the buffer from the url curl command 
 *  taken from the internet required to read buffer
 *  @param ptr pointer to a a c string
 *  @param size_t size of buffer
 *  @param nmemb memory offset 
 *  @param *userdata information about currentboard
 */
cv::Mat ComputerVision::takePicture(int timeout)
{
    vector<uchar> stream;
    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, imagePath); //the img url
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeData); // pass the writefunction
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &stream); // pass the stream ptr to the writefunction
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout); // timeout if curl_easy hangs, 
    CURLcode res = curl_easy_perform(curl); // start curl
    curl_easy_cleanup(curl); // cleanup
    return imdecode(stream, -1); // 'keep-as-is'
}

/** @brief Function to retrieve the image as cv::Mat data type
 *  @param img_url url to the image
 *  @param timeout Timeout default is 10
 *  @return void.
 */
size_t ComputerVision::writeData(char *ptr, size_t size, size_t nmemb, void *userdata)
{
    vector<uchar> *stream = (vector<uchar>*)userdata;
    size_t count = size * nmemb;
    stream->insert(stream->end(), ptr, ptr + count);
    return count;
}

/** @brief finds corners of each individual square
 *  @param source  input image 
 *  @param destination output of the image with a grid of the 8 by 8 board
 *  @return vector of the board.
 */
vector<Point2f> ComputerVision::findCorners(Mat* source, Mat* destination)
{
    vector<Point2f> corners;
    bool found = findChessboardCorners(*source, Size(9,9), corners);
    
    /**
     * if it cannot read the board notify
     */
    if (!found)
    {
        cout << "Cannot find chessboard corners." << endl;
    }
    else
    {
        vector<Point2f> cornersTemp;
        findChessboardCorners(*source, Size(9, 9), cornersTemp);
        drawChessboardCorners(*destination, Size(9,9), corners, found);
    }
    return corners;
}

/** @brief draws the grid onto the input image 
 *  @param destination output of the image with a grid of the 8 by 8 board
 *  @param corners is the location of the corners
 *  @return void
 */
std::vector<Square*> ComputerVision::drawSquares(Mat* destination, Mat* source, vector<Point2f> corners)
{
    char letters[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'};
    char numbers[] = {'1', '2', '3', '4', '5', '6', '7', '8'};
    // Square boardOutput[64];
    vector<Square*> boardOutput;
    boardOutput.reserve(64);
    /**
     *writing to image
     */
    for (int x = 1; x <= 81; x++) {
        Point2f c1 = corners[x - 1];
        Point2f c2 = corners[x];
        Point2f c3 = corners[x + 8];
        Point2f c4 = corners[x + 9];
        vector<Point2f> contour{c1, c2, c3, c4};

        /**
         * right border
         */
        if (x % 9 == 0 && x != 81) 
        {
            line(*destination, c1, c3, Scalar(0, 255,0), 3, LINE_AA);
        } 
        
         /**
           * left border
           */ 
         else if (x == 1 || x == 10 || x == 19 || x == 28 || x == 37 || x == 46 || x == 55 || x == 64) 
         {
            line(*destination, c1, c3, Scalar(0, 255,0), 3, LINE_AA);

            line(*destination, c1, c2, Scalar(0, 255,0), 3, LINE_AA);
        } 

        /** 
         * vertical lines, horizontal lines, less than 72
         */
        else if (x < 72) 
        {
            line(*destination, c1, c3, Scalar(0, 255,0), 3, LINE_AA);
            line(*destination, c1, c2, Scalar(0, 255,0), 3, LINE_AA);
        } 
        /**
         * bottom horizontal
         */    
        else if ( x != 81) 
        {
            
            line(*destination, c1, c2, Scalar(0, 255,0), 3, LINE_AA);
        }

        /**
         * check entire board to see if corners are drawn outside of the 8 by 8 board
         */
        if (x <= 71 && x % 9 != 0) 
        {
            string position("");
            Rect bRect = boundingRect(contour);

            double centroidX = bRect.x + (bRect.width / 2);
            double centroidY = bRect.y + (bRect.height / 2);

            Point2f roi(centroidX, centroidY);
            int radius = 20;
            circle(*destination, roi, radius, Scalar(255, 0, 0), 1);
            
            /**
             * every if statment is a bounder check
             * ensures its labeling the 8 by 8 board in the inputed 9 by 9 board
             */
            if (x < 9) 
            {
                position += letters[x - 1];
                position += numbers[7];
                putText(*destination, position, roi, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255),1,LINE_AA);
            }
            else if (x < 18) 
            {
                position += letters[(x % 9) - 1];
                position += numbers[6];
                putText(*destination, position, roi, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255),1,LINE_AA);
            }
            else if (x < 27) 
            {
                position += letters[(x % 9) - 1];
                position += numbers[5];
                putText(*destination, position, roi, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255),1,LINE_AA);
            }
            else if (x < 36) 
            {
                position += letters[(x % 9) - 1];
                position += numbers[4];
                putText(*destination, position, roi, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255),1,LINE_AA);
            }
            else if (x < 45) 
            {
                position += letters[(x % 9) - 1];
                position += numbers[3];
                putText(*destination, position, roi, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255),1,LINE_AA);
            } 
            else if (x < 54) 
            {
                position += letters[(x % 9) - 1];
                position += numbers[2];
                putText(*destination, position, roi, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255),1,LINE_AA);
            }
            else if (x < 63) 
            {
                position += letters[(x % 9) - 1];
                position += numbers[1];
                putText(*destination, position, roi, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255),1,LINE_AA);
            } 
            else if (x < 72) 
            {
                position += letters[(x % 9) - 1];
                position += numbers[0];
                cout << "x is " << x << endl;
                putText(*destination, position, roi, FONT_HERSHEY_SIMPLEX, 0.5, Scalar(0,0,255),1,LINE_AA);
            }
            

            boardOutput.push_back(new Square(source, c1, c2, c3, c4, roi, position));

        }
    }

    return boardOutput;
}