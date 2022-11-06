#include <Eigen/Core>
#include <Eigen/Dense>
#include <opencv2/core/eigen.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <iostream>
#include "big_armor_scale.hpp"

int main() {
    std::vector< cv::Point2f > pw_c;
    pw_c.emplace_back(575.508, 282.175);
    pw_c.emplace_back(573.93,331.819);
    pw_c.emplace_back(764.518,337.652);
    pw_c.emplace_back(765.729,286.741);

    cv::Mat f_mat, c_mat;
    cv::FileStorage reader("../f_mat_and_c_mat.yml", cv::FileStorage::READ);
    reader["F"] >> f_mat;
    reader["C"] >> c_mat;

    cv::Mat r_vec, t_vec;
    cv::solvePnP(PW_BIG, pw_c, f_mat, c_mat, r_vec, t_vec);

    Eigen::Quaterniond q(-0.0816168, 0.994363, -0.0676645, -0.00122528);
    Eigen::Matrix3d q_matrix = q.matrix();
    Eigen::Vector3d t;
    cv::cv2eigen(t_vec, t);
    t = q_matrix * t;
    std::cout << t << std::endl;
}
