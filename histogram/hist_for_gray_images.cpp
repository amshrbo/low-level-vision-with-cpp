#include <iostream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp>

// using namespace std;
// using namespace cv;

int main(){

    // Reading the image
    std::string virus_img_path = "./assets/virus.jpg";
    cv::Mat virus_img = cv::imread(virus_img_path, cv::IMREAD_GRAYSCALE);
    std::cout << virus_img_path;

    // Resizing it to (500, 500)
    cv::resize(virus_img, virus_img, { 500, 500 }, 0, 0, cv::INTER_NEAREST);

    cv::imshow("Virus image grayed and resized", virus_img);

    cv::waitKey(0);
    return 0;
}