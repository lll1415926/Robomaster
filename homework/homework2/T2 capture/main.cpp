#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <Eigen/Dense>




cv::Mat src;
class camera{
public:
    camera(){
        this->cam_f << 400., 0., 190., 0.,
                    0., 400., 160., 0.,
                    0., 0., 1., 0.;
    }

    void set(double x1, double x2, double x3, Eigen::Quaterniond x4){
        cam_position << x1, x2, x3;
        q = x4;
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
    void set(double x1, double x2, double x3, Eigen::Matrix<double, 3, 4> x4){
        Eigen::Vector4d w4;
        w4 << x1, x2, x3, 1;
        Eigen::Vector3d u3 = x4 * w4;

        u3 /= u3(2, 0);
        ct.x = u3(0, 0);
        ct.y = u3(1, 0);
    }

    void draw(){
        cv::circle(src, ct, 2,cv::Scalar{255, 255,255},-1);
    }
private:
    cv::Point2d ct;
};


int main() {
    freopen("../points.txt", "r", stdin);

    src = cv::Mat::zeros(cv::Size(1500,1000),CV_8UC1);

    camera Cam;
    Cam.set(2., 2., 2.,Eigen::Quaterniond{-0.5,0.5, 0.5, -0.5});
    Eigen::Matrix<double, 3, 4> move_matrix = Cam.get_matrix();
    int point_sum;
    std::cin >> point_sum;
    point nw;
    for(int i = 1; i <= point_sum; ++i){
        double x, y, z;
        std::cin >> x >> y >> z;
        nw.set(x,y,z,move_matrix);
        nw.draw();
    }

    cv::imshow("point", src);
    cv::waitKey(0);

    cv::imwrite("../result.jpg", src);
    return 0;
}