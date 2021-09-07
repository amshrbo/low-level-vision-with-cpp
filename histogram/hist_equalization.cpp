#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/fast_math.hpp>
#include <opencv2/core/hal/interface.h>

// using namespace std;
using namespace cv;

int main(){

    // Reading the image
    std::string img_path = "./assets/virus.jpg";
    Mat virus_img = imread(img_path, IMREAD_GRAYSCALE);
    resize(virus_img, virus_img, { 500, 500 }, 0, 0, INTER_NEAREST);

    Mat hist_equalized;

    equalizeHist(virus_img, hist_equalized);
    
    imwrite("./assets/virus_hist_equalized.jpg", hist_equalized);
    
    imshow("virus image", virus_img);
    imshow("Histogram Equalization", hist_equalized);

    waitKey(0);
    return 0;
}