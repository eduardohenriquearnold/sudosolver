#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>
#include "Solver.h"

using namespace std;
using namespace cv;

class SudokuImg : public Solver
{
        private:
                Mat processImg(Mat i);
                void getTiles(vector<Mat>& n);
                int  ocrResult(Mat& i);                                
                
        public:
                bool parseImage(string path);                
                
};
