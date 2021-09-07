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
    std::string img_path = "./assets/alaqsa_1.jpg";
    Mat alaqsa_img = imread(img_path, IMREAD_GRAYSCALE);
    resize(alaqsa_img, alaqsa_img, { 500, 500 }, 0, 0, INTER_NEAREST);

    // Histogram calculation
    MatND histogram;
    int hist_size = 256;
    const int* channel_numbers = {0};
    float hist_range[] = {0.0, 256.0};
    const float* channel_ranges = hist_range;
    int number_bins = hist_size;
    
    

    calcHist(&alaqsa_img, 1, 0, Mat(), histogram, 1, &number_bins, &channel_ranges);
    
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double)hist_w / hist_size);

    Mat hist_img(hist_h, hist_w, CV_8UC3, Scalar(0,0,0));

    normalize(histogram, histogram, 0, hist_img.rows, NORM_MINMAX, -1, Mat() );

    // Plotting histogram results as a line
    for( int i = 1; i < hist_size; i++ ){
        
        line(hist_img, 
            Point( bin_w*(i-1), hist_h - cvRound(histogram.at<float>(i-1)) ),
            Point( bin_w*(i), hist_h - cvRound(histogram.at<float>(i)) ),
            Scalar( 255, 0, 0), 2, 8, 0  );
    }

    imwrite("./assets/Alaqsa_resized.jpg", alaqsa_img);
    imwrite("./assets/hist_alaqsa_gray.jpg", hist_img);

    imshow("Alaqsa image", alaqsa_img );
    imshow("Histogram", hist_img );

    waitKey(0);
    return 0;
}