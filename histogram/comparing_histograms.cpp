#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>


using namespace cv;

int main(){

    // Reading the two images
    std::string img1_path = "./assets/alaqsa_1.jpg";
    std::string img2_path = "./assets/alaqsa_2.jpg";    

    Mat img1 = imread(img1_path, IMREAD_GRAYSCALE);
    Mat img2 = imread(img2_path, IMREAD_GRAYSCALE);


    // calculating histograms for the two images
    float range[] = { 0, 256 }; //the upper boundary is exclusive
    const float* histRange[] = { range };
    int histSize = 256;

    Mat hist_1, hist_2;

    calcHist(&img1, 1, 0, Mat(), hist_1, 1, &histSize, histRange);
    calcHist(&img2, 1, 0, Mat(), hist_2, 1, &histSize, histRange);

    // Normalizing the histograms
    normalize(hist_1, hist_1, 1.0);
    normalize(hist_2, hist_2, 1.0);

    // comparing the two histograms
    double correlation = compareHist(hist_1, hist_2, HISTCMP_CORREL);
    double intersection = compareHist(hist_1, hist_2, HISTCMP_INTERSECT);
    double chisquare = compareHist(hist_1, hist_2, HISTCMP_CHISQR);
    
    // printing the results
    std::cout << "The Correlation between imgs is: " << correlation << std::endl;
    std::cout << "The Intersection between imgs is: " << intersection << std::endl;
    std::cout << "The Chisquare between imgs is: " << chisquare << std::endl;

    return 0;
}

// comparing_histograms.cpp