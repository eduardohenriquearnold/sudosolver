#include "SudokuImg.h"

bool SudokuImg::parseImage(string path)
{
        Mat img = imread(path, CV_LOAD_IMAGE_GRAYSCALE);
        
        Mat p = processImg(img);
        imshow("processed Img", p);
        waitKey();
}

Mat SudokuImg::processImg(Mat i)
{        
        //Blur
        Mat smooth;
        GaussianBlur(i, smooth, Size(3,3), 2,2);
        
        //Canny
        Mat edges;
        Canny(smooth, edges, 0, 100);
                
        return edges;
}
