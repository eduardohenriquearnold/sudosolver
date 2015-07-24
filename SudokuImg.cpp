#include "SudokuImg.h"

bool SudokuImg::parseImage(string path)
{
        Mat img = imread(path, CV_LOAD_IMAGE_GRAYSCALE);
        
        Mat p = processImg(img);
        imshow("processed Img", p);
        waitKey();
        
        return true;
}

Mat SudokuImg::processImg(Mat i)
{
        //Enhance image by dividing it by closing result
        Mat closed, imp;
        morphologyEx(i, closed, MORPH_CLOSE, getStructuringElement(MORPH_ELLIPSE, Size(5,5)));
        closed.convertTo(closed, CV_32F);        

        i.convertTo(i, CV_32F);        
        divide(i, closed, imp);

        normalize(imp, imp, 0, 255, NORM_MINMAX);
        imp.convertTo(imp, CV_8U);
        
        //Threshold
        Mat binary;
        adaptiveThreshold(imp, binary, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY_INV, 19, 2);
                                                 
        //Get largest rectangle
        vector<contour> contours;
        findContours(binary.clone(), contours, CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE);        
        
        double area = 0;
        contour maxRect;
        for (contour& c : contours)
        {
                contour aprox;
                approxPolyDP(c, aprox, arcLength(c, true)*0.02, true);
                
                if (aprox.size() == 4 && isContourConvex(aprox))
                        if (contourArea(aprox) > area)
                        {
                                area = contourArea(aprox);
                                maxRect = aprox;
                        }
        }
        
        //Get mask and resulting image
        Mat res = Mat::zeros(i.size(), CV_8U);
        drawContours(res, vector<contour>(1,maxRect), -1, Scalar(255,255,255), -1);
        bitwise_and(imp, res, res);
        
        return res;        
}

Mat SudokuImg::getLines(Mat i, int d)
{
        //Sobel derivative
        Mat deriv;
        if (d==0)
                Sobel(i, deriv, CV_16S, 1, 0);
        else
                Sobel(i, deriv, CV_16S, 0, 2);
                
        convertScaleAbs(deriv, deriv);
        normalize(deriv, deriv, 0, 255, NORM_MINMAX);        
        
        //Binarize and closing operation
        Mat bin;
        threshold(deriv, bin, 0, 255, THRESH_BINARY+THRESH_OTSU);       
        
        Mat close, ker;
        if (d==0)
                ker = getStructuringElement(MORPH_RECT, Size(2,10));
        else
                ker = getStructuringElement(MORPH_RECT, Size(10,2));
        morphologyEx(bin, close, MORPH_CLOSE, ker);                
        
        //Fill regions
        vector<contour> contours;
        findContours(close, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
        
        Mat result = Mat::zeros(close.size(), CV_8U);
        for (contour& c : contours)
        {
                Rect r = boundingRect(c);
                if (d==1 && float(r.width)/r.height>5) 
                                drawContours(result, vector<contour>(1, c), 0, 255, -1);

                                
                if (d==0 && float(r.height)/r.width>5)
                                drawContours(result, vector<contour>(1, c), 0, 255, -1);
        }
        
        //Detect lines using Hough
        /*vector<Vec2f> lines;
        HoughLines(result, lines, 3, CV_PI/180*3, 500);        
        lines.erase(lines.begin()+9, lines.end());

        result = Mat::zeros(close.size(), CV_8U);
        for (Vec2f& l : lines)
        {
                float rho = l[0], theta = l[1];
                double a = cos(theta), b = sin(theta);
                double x0 = a*rho, y0 = b*rho;
                Point2f pt1(x0 - 1000*b, y0+1000*a);
                Point2f pt2(x0 + 1000*b, y0-1000*a);
                line(result, pt1, pt2, 255, 3);
        }*/
        
        //Final dilation
        morphologyEx(result, result, MORPH_DILATE, ker, Point(-1,-1), 2);
        return result;
                
}

contour SudokuImg::getGridPoints(Mat i)
{
        //Get horizontal and vertical lines to obtain intersection
        Mat linesX, linesY, intersec;
        linesX = getLines(i, 0);
        linesY = getLines(i, 1);
        bitwise_and(linesX, linesY, intersec);
        
        //Get Grid points by doing component analysis
        vector<contour> contours;
        findContours(intersec, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

        vector<Point> gPoints;
        for (contour& c : contours)
        {
                Moments m = moments(c);
                double x=m.m10/m.m00, y=m.m01/m.m00;
                gPoints.push_back(Point(x,y));
        }
        
        //Sort points
        auto compV = [](Point& p1, Point& p2) {return (p1.y<p2.y);};
        std::sort(gPoints.begin(), gPoints.end(), compV);
                
        int num = sqrt(gPoints.size());
        auto compH = [](Point& p1, Point& p2) {return (p1.x<p2.x);};
        for (int i=0; i<num; i++)
                std::sort(gPoints.begin()+num*i, gPoints.begin()+num*(i+1), compH);
                      
        return gPoints;
        
        /*
        //Debug
        imshow("lX", linesX);
        imshow("lY", linesY);
        imshow("int", intersec);
        
        i = Mat::zeros(i.size(), CV_8U);
        for (int j=0; j<gPoints.size(); j++)
                putText(i, to_string(j), gPoints[j], FONT_HERSHEY_PLAIN, 1, 255);

        waitKey();
        */
}
