#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <Eigen/Dense>
#include <ctime>
#include <random>

#define Pi acos(-1)

cv::Mat img_show, img_blur;


int get_rand(int min, int max){
    return (rand() % (max - min + 1)) + min;
}

class camera{
public:
    camera(){
        this->cam_f << 1., 0., 0., 0.,
                0., 1., 0., 0.,
                0., 0., 1., 0.;
    }

    void set(double x1, double x2, double x3, const Eigen::Quaterniond& x4){
        cam_position << x1, x2, x3;
        q = x4;
    }

    void move_camera(double angle){
        double angle_rad = angle * Pi / 360;
        Eigen::Quaterniond x1 = {cos(angle_rad), 0, -sin(angle_rad), 0};
        Eigen::Matrix3d x1_matrix = x1.matrix();
        cam_position =  x1_matrix * cam_position;

        double rotate_rad = acos(q.w()) + angle_rad;
        Eigen::Quaterniond x2 = {cos(rotate_rad), 0, sin(rotate_rad), 0};
        q = x2;

    }

    Eigen::Matrix<double, 3, 4> get_matrix(){
        Eigen::Matrix4d converter = Eigen::Matrix4d::Zero();
        Eigen::Matrix3d q_matrix = q.matrix();
        converter(3, 3) = 1.;
        converter.block(0, 0, 3, 3) = q_matrix.transpose().cast<double>();
        converter.block(0, 3, 3, 1) = -q_matrix.transpose().cast<double>() * cam_position;
        return cam_f * converter;
    }

private:
    Eigen::Vector3d cam_position;
    Eigen::Quaterniond q;
    Eigen::Matrix<double, 3, 4> cam_f;
};

class point{
public:
    struct point_real{
        double x, y, z;
        int r;
        cv::Scalar color;
    };
    point_real point{};

    void get(const Eigen::Matrix<double, 3, 4>& x1){
        Eigen::Vector4d w4;
        w4 << point.x, point.y, point.z, 1;
        Eigen::Vector3d u3 = x1 * w4;

        point_camera.x = u3(0, 0);
        point_camera.y = u3(1, 0);
        //std::cout << point_camera.x << " " << point_camera.y << std::endl;
    }

    void set(double x1, double x2, double x3, int x4, double x5, double x6, double x7){
        point.x = x1;
        point.y = x2;
        point.z = x3;
        point.r = x4;
        point.color = cv::Scalar{x5, x6, x7};
    }

    void draw(){
        cv::circle(img_show, point_camera, int(point.r),cv::Scalar(point.color),-1);
    }
private:
    cv::Point point_camera;
};

point set_real(const cv::Point& pt, int r){
    point pt_real;
    pt_real.point.x = pt.x + (double)(rand()) / RAND_MAX + 1000;
    pt_real.point.y = pt.y + (double)(rand()) / RAND_MAX;
    pt_real.point.z = get_rand(-1000, 1000) + (double)(rand()) / RAND_MAX;
    pt_real.point.r = r;
    pt_real.point.color = cv::Scalar{get_rand(225, 255) + (double)(rand()) / RAND_MAX, get_rand(225, 255) + (double)(rand()) / RAND_MAX,get_rand(225, 255) + (double)(rand()) / RAND_MAX};
    return pt_real;
}

void get_point(){
    cv::Mat src = cv::imread("../logo.jpg");
    cv::cvtColor(src, src, cv::COLOR_BGR2GRAY);
    cv::threshold(src,src,100,255,cv::THRESH_BINARY);
    std::vector< std::vector<cv::Point> > contours;
    std::vector< cv::Vec4i > hierachy;
    cv::findContours( src, contours, hierachy, cv::RETR_LIST, cv::CHAIN_APPROX_NONE);
    //获得轮廓周围区域
    cv::Mat src_blur;
    cv::blur(src, src_blur, cv::Size(200, 100));
    int heigth = src.rows;
    int width = src.cols;
    for (int row = 0; row < heigth; row++) {
        for (int col = 0; col < width; col++) {
            int gray = src.at<uchar>(row,col);
            src.at<uchar>(row,col) = 255-gray;
        }
    }
    src_blur = src_blur & src;
    cv::drawContours(src_blur, contours, -1, cv::Scalar{0,0,0},1);
    freopen("../point.txt","w",stdout);
    std::vector< point > logo_point;
    //生成轮廓周围的点
    for (int row = 0; row < heigth; row++) {
        for (int col = 0; col < width; col++) {
            int gray = src_blur.at<uchar>(row,col);
            if(gray > 60){
                if((double)(rand()) / RAND_MAX >= 0.995) logo_point.push_back(set_real(cv::Point(col, row), get_rand(1, 4)));
            }
            else if (gray > 0){
                if((double)(rand()) / RAND_MAX >= 0.999) logo_point.push_back(set_real(cv::Point(col, row), get_rand(1, 3)));
            }
            else if((double)(rand()) / RAND_MAX >= 0.9999) logo_point.push_back(set_real(cv::Point(col, row), get_rand(1, 2)));
        }
    }
    //生成轮廓上的点
    for(auto & contour : contours){
        for(int i = 0; i < contour.size();){

            int r = get_rand(1, 7);

            logo_point.push_back(set_real(contour[i], r));
            i += get_rand(r + 1, r + 15);
        }
    }
    std::cout << logo_point.size() << std::endl;
    for(auto & points : logo_point){
        std:: cout << points.point.x << " " << points.point.y << " " << points.point.z << " " << points.point.r << " " << points.point.color[0] << " " << points.point.color[1] << " " << points.point.color[2] << std::endl;
    }
    fclose(stdout);
}

double get_angle(int t){
    if(t <= 50) return 0.0002 * t;
    return 0.0019 * t - 0.085;
}

int main() {
    srand(time(0));
    //get_point()随机生成点并保存到文件“point.txt”中
    //get_point();

    cv::namedWindow("video");
    cv::VideoWriter writer("../result.avi", cv::VideoWriter::fourcc('M', 'J', 'P', 'G'), 50, cv::Size(944, 534), true);

    freopen("../point.txt", "r", stdin);
    std::vector< point > out_point;
    int point_sum;
    std::cin >> point_sum;
    for(int i = 0; i < point_sum; ++i){
        double x1, x2, x3, c1, c2, c3;
        int r;
        std:: cin >> x1 >> x2 >> x3 >> r >> c1 >> c2 >> c3;

        point nw;
        nw.set(x1, x2, x3, r, c1, c2, c3);
        out_point.push_back(nw);
    }
    fclose(stdin);

    camera Cam;
    Cam.set(1000.,0.,0.,Eigen::Quaterniond{1.,0.,0.,0.});
    for(int i = 0; i <= 250; ++i){
        Cam.move_camera(get_angle(i));
    }

    for(int i = 250; i >= 0; --i){
        Cam.move_camera(-get_angle(i));
        Eigen::Matrix<double, 3, 4> trans_mat = Cam.get_matrix();
        img_show = cv::Mat::zeros(cv::Size(944,534),CV_8UC3);

        for(int i = 0; i < point_sum; ++i){
            out_point[i].get(trans_mat);
            out_point[i].draw();
        }
        //模拟光晕
        cv::blur(img_show,img_show, cv::Size(4,4));

        writer << img_show;
    }

    writer.release();
    return 0;
}