# Grandmaster Pi

Grandmaster Pi is a chess bot that uses computer vision and machine learning to serve as a chess opponent on a physical chess board. This project was developed out of interest of matches played between real grandmasters and the AlphaZero engine.

<p align="center">
  <img src="https://i.imgur.com/B20pj8x.gif" alt="Before and After a real chess board being detected"/>
</p>

## Installation

To install the program, clone the repository:

```
git clone https://github.com/uoysip/grandmaster-pi.git
cd grandmaster-pi
```

The detection algorithm requires [OpenCV2](https://opencv.org/releases/), the project base directory includes a bash installation script ```install_opencv``` which installs the latest version of OpenCV2 for convenience.

## Building and Running the code

To test the chess board detection algorithm on a image, this can be done with the ```./DisplayImage [IMAGE]``` command, where _[IMAGE]_ is the file location of the chess board. An example execution would be:

```./DisplayImage ../images/chessboard1.jpg```

To run the game, use the same ```./DisplayImage [URL]``` command but instead of an image, supply a URL for the IP camera as an argument.
