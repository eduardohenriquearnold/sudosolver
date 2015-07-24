#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "Solver.h"

#define contour vector<Point>

using namespace std;
using namespace cv;

class SudokuImg : public Solver
{
        private:
                Mat processImg(Mat i);
                Mat getLines(Mat i, int d);
                contour getGridPoints(Mat i);
                int  ocrResult(Mat& i);      
                void trainOCR();
                
        public:
                bool parseImage(string path);                
                
};
