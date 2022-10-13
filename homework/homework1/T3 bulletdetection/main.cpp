#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

bool cmp_bullet(Point2f p1, Point2f p2){
    return p1.x < p2.x;
}

vector<Point2f> bullet_current;

Mat bullet;
vector<vector<Point>> contours;
int pre_id = 0, pre_x = -1;

void label_bullet(){
    if(!bullet_current.size()) return;
    sort(bullet_current.begin(), bullet_current.end(), cmp_bullet);
    if(pre_x){
        if(bullet_current[0].x > pre_x) pre_id ++;
    }
    else{
        pre_id = 1;
    }

    pre_x = bullet_current[0].x;
    for(int i = 0; i < bullet_current.size(); ++i){
        putText(bullet, to_string(pre_id + i), Point2f(bullet_current[i].x + 20, bullet_current[i].y), FONT_HERSHEY_SIMPLEX, 0.75, Scalar{0, 0, 255}, 2);
    }
    return;
}

void check_contour(vector<Point> contour, int id){

    if(contourArea(contour) < 50) return;

    RotatedRect rect = minAreaRect(contour);
    double long_side = max(rect.size.height, rect.size.width), short_side = min(rect.size.height, rect.size.width);
    if(contourArea(contour) / rect.size.area() > 0.3 && long_side / short_side > 7.0 && long_side > 43){
        Point2f P[4];
        rect.points(P);
        for (int j = 0; j <= 3; j++)
        {
            line(bullet, P[j], P[(j + 1) % 4], Scalar{255, 255, 255}, 1);
        }

        circle(bullet, rect.center, 3, Scalar{0,0,255}, -1);
        bullet_current.push_back(rect.center);

        return;
    }
    if(contourArea(contour) / rect.size.area() < 0.3 && arcLength(contour, true) > 100){
        drawContours(bullet, contours, id, Scalar{255, 255, 255}, 1);

        Moments mu = moments(contour, true);
        Point2f contour_ct;
        contour_ct.x = mu.m10 / mu.m00;
        contour_ct.y = mu.m01 / mu.m00;

        circle(bullet, contour_ct, 3, Scalar{0,0,255}, -1);
        bullet_current.push_back(contour_ct);

        return;
    }


    return;
}

int main(){
    VideoCapture capture("../bullet.mp4");
    namedWindow("bullet");

    while(capture.read(bullet)){
        Mat bullet_grey;
        Mat bullet_result = Mat::zeros(bullet.size(), CV_8UC1);
        cvtColor(bullet, bullet_grey, COLOR_BGR2GRAY);
        Mat element = getStructuringElement(MORPH_RECT, Size(2,2));
        morphologyEx(bullet_grey, bullet_grey, MORPH_OPEN, element);
        threshold(bullet_grey, bullet_grey, 100, 255, THRESH_BINARY);

        vector<Vec4i> hierarchy;
        findContours(bullet_grey, contours, hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

        bullet_current.clear();
        for(int i = 0; i < contours.size(); ++i){
            check_contour(contours[i], i);
        }

        label_bullet();
        imshow("bullet", bullet);
        waitKey(70);
    }

    return 0;
}