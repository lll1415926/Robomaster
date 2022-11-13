#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>

int main() {
    cv::namedWindow("result", cv::WINDOW_NORMAL);
    cv::resizeWindow("result", 800, 600);

    cv::Mat src_1 = cv::imread("../9407.png");
    cv::Mat src_2 = cv::imread("../9408.png");

    cv::Mat gry_1, gry_2;
    cv::cvtColor(src_1, gry_1, cv::COLOR_BGR2GRAY);
    cv::cvtColor(src_2, gry_2, cv::COLOR_BGR2GRAY);


    cv::Ptr <cv::ORB> orb = cv::ORB::create();

    std::vector <cv::KeyPoint> feature_pt_1, feature_pt_2;
    orb->detect(gry_1, feature_pt_1);
    orb->detect(gry_2, feature_pt_2);

    cv::Mat descriptors_1, descriptors_2;
    orb->compute(gry_1, feature_pt_1, descriptors_1);
    orb->compute(gry_2, feature_pt_2, descriptors_2);


    cv::BFMatcher matcher(cv::NORM_HAMMING);
    std::vector <cv::DMatch> pairs;
    matcher.match(descriptors_1, descriptors_2, pairs);

    std::vector <cv::DMatch> good;
    double min_dist = 100000;
    for(auto &match:pairs){
        if(match.distance < min_dist) min_dist = match.distance;
    }
    for(auto &match:pairs){
        if(match.distance < std::max(min_dist * 2, 30.0)) good.push_back(match);
    }

    cv::Mat show;
    cv::drawMatches(src_1, feature_pt_1, src_2, feature_pt_2,good, show);

    cv::imshow("result", show);
    cv::waitKey(0);
}
