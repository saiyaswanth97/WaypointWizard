//
// Created by gsanthosh on 29/9/24.
//
#include "../include/smoother.h"
#include "iostream"
int main() {
    // Elasticity parameters
    double alpha = 0.0075;  // Stretching weight
    double beta = 0.0;   // Bending weight
    int iterations = 1000;  // Number of iterations for smoothing
    double w_potential = 0.001;

    // Define a vector of pairs of doubles
    std::vector<std::pair<double, double>> path_points;

    // Add some pairs to the vector

    for(int i=1;i<=100;i++){
        path_points.emplace_back(i, i);
    }


    for (const auto& p : path_points) {
        std::cout << "(" << p.first << ", " << p.second << ")" << std::endl;
    };

    get_new_path(path_points, alpha,beta, w_potential, iterations);

    for (const auto& p : path_points) {
        std::cout << "(" << p.first << ", " << p.second << ")" << std::endl;
    };

//    std::vector<std::pair<double,double>> results =  interpolate_points(path_points[1], path_points[10]);
//
//    for(auto & result : results){
//        std::cout<<result.first<<" "<<result.second<<std::endl;
//    }



    return 0;
}