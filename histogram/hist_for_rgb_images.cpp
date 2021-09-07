#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/core/fast_math.hpp>
#include <opencv2/core/hal/interface.h>
// #include <vector>

// using namespace std;
using namespace cv;

int main(){

    // Reading the image
    std::string img_path = "./assets/alaqsa_1.jpg";
    Mat alaqsa_img = imread(img_path, IMREAD_COLOR);
    resize(alaqsa_img, alaqsa_img, { 500, 500 }, 0, 0, INTER_NEAREST);

    // dividing it into 3 channels
    std::vector<Mat> bgr_planes;
    split(alaqsa_img, bgr_planes); // splitting the image into b, g, and r

    // Histogram calculation
    Mat b_histogram, g_histogram, r_histogram;
    int hist_size = 256;
    const int* channel_numbers = {0};
    float hist_range[] = {0.0, 256.0};
    const float* channel_ranges = hist_range;
    int number_bins = hist_size;

    calcHist(&bgr_planes[0], 1, 0, Mat(), b_histogram, 1, &number_bins, &channel_ranges);
    calcHist(&bgr_planes[1], 1, 0, Mat(), g_histogram, 1, &number_bins, &channel_ranges);
    calcHist(&bgr_planes[2], 1, 0, Mat(), r_histogram, 1, &number_bins, &channel_ranges);
    
    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double)hist_w / hist_size);

    Mat hist_img(hist_h, hist_w, CV_8UC3, Scalar(0,0,0));

    normalize(b_histogram, b_histogram, 0, hist_img.rows, NORM_MINMAX, -1, Mat() );
    normalize(g_histogram, g_histogram, 0, hist_img.rows, NORM_MINMAX, -1, Mat() );
    normalize(r_histogram, r_histogram, 0, hist_img.rows, NORM_MINMAX, -1, Mat() );

    // Plotting histogram results as a line
    for( int i = 1; i < hist_size; i++ ){
        
        // The blue histogram line
        line(hist_img, 
            Point( bin_w*(i-1), hist_h - cvRound(b_histogram.at<float>(i-1)) ),
            Point( bin_w*(i), hist_h - cvRound(b_histogram.at<float>(i)) ),
            Scalar( 255, 0, 0), 2, 8, 0  );

        // The blue histogram line
        line(hist_img, 
            Point( bin_w*(i-1), hist_h - cvRound(g_histogram.at<float>(i-1)) ),
            Point( bin_w*(i), hist_h - cvRound(g_histogram.at<float>(i)) ),
            Scalar( 0, 255, 0), 2, 8, 0  );

        // The blue histogram line
        line(hist_img, 
            Point( bin_w*(i-1), hist_h - cvRound(r_histogram.at<float>(i-1)) ),
            Point( bin_w*(i), hist_h - cvRound(r_histogram.at<float>(i)) ),
            Scalar( 0, 0, 255), 2, 8, 0  );
    }

    imwrite("./assets/Alaqsa_resized_bgr.jpg", alaqsa_img);
    imwrite("./assets/hist_alaqsa_bgr.jpg", hist_img);

    imshow("Alaqsa image", alaqsa_img );
    imshow("Histogram", hist_img );

    waitKey(0);
    return 0;
}