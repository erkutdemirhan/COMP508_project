
#include <cv.h> 
#include <highgui.h> 
#include <iostream>
#include "main.h"

int main(int argc, char** argv) {
		  cv::Mat input_image;

		  std::cout << "Initial version of the project" << std::endl;
		  input_image = cv::imread(LENNA_IMAGE_PATH, CV_LOAD_IMAGE_COLOR);

		  cv::imshow("Lenna", input_image);
		  cv::imwrite("./output_images/Lenna_output.jpg", input_image);
		  cv::waitKey(0);
}
