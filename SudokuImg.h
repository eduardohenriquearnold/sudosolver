#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <opencv2/opencv.hpp>

#include "Solver.h"
#include "OCR.h"

#define contour vector<Point>

using namespace std;
using namespace cv;

class SudokuImg : public Solver
{
        private:
                Size cSize;
                OCR ocr;
                
                Mat processImg(Mat i);
                Mat getLines(Mat i, int d);
                contour getGridPoints(Mat i);
                Mat getCharPatch(Mat img, contour& gdPts, int i, int j);
                
        public:
                SudokuImg() : cSize(30,30), ocr("ocr.xml", cSize) {};
                bool parseImage(string path);                
                void trainOCR(string path);             //path must be the target to image. A file containing the text description of the Sudoku must exist in the same directory with the same name and no extension.
};
