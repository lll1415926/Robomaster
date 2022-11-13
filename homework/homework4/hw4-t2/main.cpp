#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "VO.cpp"

int main(){
    cv::FileStorage params("../camera.yaml", cv::FileStorage::READ);
    cv::Mat K = params["K"].mat();

    cv::Mat src_1 = cv::imread("../stereo-data/0_orig.jpg");
    cv::Mat dis_1 = cv::imread("../stereo-data/0_dpt.tiff", cv::IMREAD_ANYDEPTH);
    cv::Mat src_2 = cv::imread("../stereo-data/1_orig.jpg");
    cv::Mat dis_2 = cv::imread("../stereo-data/1_dpt.tiff", cv::IMREAD_ANYDEPTH);

    Mat r, t;
    find_PnP(src_1,dis_1,src_2,dis_2,K,r,t);
    process_Stitch_project(src_1, dis_1, src_2, dis_2, K, r, t, "result");
}
