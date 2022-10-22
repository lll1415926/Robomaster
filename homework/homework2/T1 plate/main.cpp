#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>

int h_min = 105, h_max = 125, s_min = 127, s_max = 232, v_min = 0, v_max = 255;
cv::Mat src;

cv::Mat get_background(){
    cv::Mat src_hsv, result_background;
    cv::cvtColor(src, src_hsv, cv::COLOR_BGR2HSV);
    cv::inRange(src_hsv, cv::Scalar(h_min, s_min, v_min), cv::Scalar(h_max, s_max, v_max), result_background);

    return result_background;
}

bool cmp_point_x(const cv::Point &x1, const cv::Point& x2) {
    return x1.x < x2.x;
}

void to_front(const std::vector<cv::Point> &contour){
    std::vector<cv::Point> approx_contour;
    cv::approxPolyDP(cv::Mat(contour), approx_contour, 10, true);

    cv::Mat out = src.clone();
    for(int i = 0; i< approx_contour.size();++i){
        cv::line(out,approx_contour[i],approx_contour[(i + 1) % 4],cv::Scalar{0,0,255},1);
    }

    sort(approx_contour.begin(), approx_contour.end(), cmp_point_x);
    if(approx_contour[0].y > approx_contour[1].y) std::swap(approx_contour[0],approx_contour[1]);
    if(approx_contour[2].y > approx_contour[3].y) std::swap(approx_contour[2],approx_contour[3]);

    cv::Point2f from_point[4] = { approx_contour[0],approx_contour[1],approx_contour[2],approx_contour[3]};
    cv::Point2f to_point[4] = {cv::Point(0,0), cv::Point(0,140), cv::Point(440,0), cv::Point(440,140)};

    cv::Mat result;
    cv::Mat trans_matrix = getPerspectiveTransform(from_point, to_point);
    cv::warpPerspective(src,result,trans_matrix,cv::Size(440, 140));

    cv::imwrite("../result.jpg", result);
    cv::imshow("plate", out);
    cv::imshow("result",result);
    cv::waitKey(0);
}

int main(){
    cv::namedWindow("plate");
    cv::namedWindow("result");
    src = cv::imread("../plate.png");

    cv:: Mat plate = get_background();

    cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(20, 20));
    cv::morphologyEx(plate, plate, cv::MORPH_CLOSE, element);
    element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(7, 7));
    cv::morphologyEx(plate, plate, cv::MORPH_OPEN, element);


    std::vector< std::vector<cv::Point> > contours;
    std::vector< cv::Vec4i > hierachy;

    cv::findContours( plate, contours, hierachy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
    for(auto & contour : contours){
        double area = cv::contourArea(contour);
        cv::RotatedRect rect = cv::minAreaRect(contour);
        int long_side = std::max(rect.size.width, rect.size.height), short_side = std::min(rect.size.width, rect.size.height);
        float ratio;
        ratio = long_side / short_side;

        if(area > 10000 && ratio > 1.5 && ratio < 5){
            to_front(contour);
        }
    }
    return 0;
}