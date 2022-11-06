#include <iostream>
#include <cstdio>
#include <string>
#include <vector>
#include <ctime>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <Eigen/Dense>
#include <opencv2/core/eigen.hpp>

int main()
{
    Eigen::Matrix<double, 2, 1> X;
    Eigen::Matrix<double, 2, 2> A;
    Eigen::Matrix<double, 2, 2> P;
    Eigen::Matrix<double, 2, 2> Q;
    Eigen::Matrix<double, 2, 1> K;
    Eigen::Matrix<double, 1, 2> H;
    Eigen::Matrix<double, 1, 1> R;

    double data[55];
    freopen("../dollar.txt", "r", stdin);

    for(int i = 0; i < 30; ++i){
        double x;
        std::cin >> x;
        data[i] = x;
    }
    
    X << data[0], 0;
    A << 1, 1, 0, 1;
    H << 1, 0;
    Q << 2000, 0, 0, 100;
    R << 100;

    for (int i = 1; i < 30; ++i){
        Eigen::Matrix<double, 2, 1> X_k = A * X;
        P = A * P * A.transpose() + Q;

        K = P * H.transpose() * (H * P * H.transpose() + R).inverse();

        Eigen::Matrix<double, 1, 1> Z{data[i]};
        X = X_k + K * (Z - H * X_k);
        P = (Eigen::Matrix<double, 2, 2>::Identity() - K * H) * P;
    }

    for (int i = 1; i <= 10; ++i){
        X = A * X;
        std::cout << "day" << i << " " << X[0] << std::endl;
    }
    return 0;
}
