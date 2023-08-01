#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <chrono>
#include <receipt_nn.hpp>

using namespace cv;

ReceiptDetect receiptDetect;

int main(int argc, char **argv)
{
    std::string img_path = argv[1];
    LOG(INFO) << img_path;

    Mat img = imread(img_path);

    Mat output_frame;
    img.convertTo(output_frame, CV_32F);

    Mat img_dst;
    resize(output_frame, img_dst, Size(200, 200), 0, 0, cv::INTER_LANCZOS4);

    unsigned char *dataMat = img_dst.data;
    receiptDetect.detect_receipt((char *)dataMat);

    return 0;
}