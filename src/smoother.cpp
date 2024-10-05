//
// Created by gsanthosh on 29/9/24.
//
#include "../include/smoother.h"
#include <cmath>
#include <iostream>

double OBS_X = 50 , OBS_Y = 50, OBS_THRES = 5, DIST_THRES = 4.0;
int NUM_POINTS = 10;
std::vector<std::pair<double,double>> interpolate_points(std::pair<double, double> start_point , std::pair<double, double> end_point){
    std::vector<std::pair<double,double>> result;

    for (int i = 1; i <=NUM_POINTS; ++i) {
        double t = static_cast<double>(i) / (NUM_POINTS+1);
        double x = start_point.first + t * (end_point.first - start_point.first);
        double y = start_point.second + t * (end_point.second - start_point.second);
        result.emplace_back(x, y);
    }

    return result;
}
std::pair<double, double> get_potential_field_cost(std::pair<double, double> current_point){
    std::pair<double, double> cost;
    double x= current_point.first;
    double y= current_point.second;

    if (std::abs(x-OBS_X)<OBS_THRES  && std::abs(y-OBS_Y)<OBS_THRES) {
        cost.first =  std::pow(std::abs(x - OBS_X)-OBS_THRES , 2);
        cost.second =  std::pow(std::abs(y - OBS_Y)-OBS_THRES , 2);
    }

    return cost;
}

void get_new_path(std::vector<std::pair<double, double>> &path_points, double alpha, double beta, double w_potential, int iterations) {
    double force_x;
    double force_y;
    std::pair<double, double> potential_cost = {0.0, 0.0};

    for (int j = 0; j < iterations; j++) {
        for (int i = 1; i < path_points.size() - 1; i++) {
            potential_cost = get_potential_field_cost(path_points[i]);
            force_x = alpha * pow(path_points[i + 1].first - path_points[i].first, 2) +
                      beta * ((path_points[i + 1].first - path_points[i].first * 2 + path_points[i - 1].first));
            force_y = alpha * pow(path_points[i + 1].second - path_points[i].second, 2) +
                      beta * ((path_points[i + 1].second - path_points[i].second * 2 + path_points[i - 1].second));

            path_points[i].first =
                    path_points[i].first + (force_x + w_potential * potential_cost.first);
            path_points[i].second =
                    path_points[i].second + (force_y + w_potential * potential_cost.second);

        }
        int k = 0;
        while (k < path_points.size() - 1) {
            double distance = std::sqrt(std::pow(path_points[k].first - path_points[k + 1].first, 2) +
                                        std::pow(path_points[k].second - path_points[k + 1].second, 2));
            std::vector<std::pair<double, double>> result;
            if (distance > DIST_THRES) {
                result = interpolate_points(path_points[k], path_points[k + 1]);
                path_points.insert(path_points.begin() + k + 1, result.begin(), result.end());
                k += result.size() + 1;
            } else {
                k++;
            }
            std::cout << path_points.size() << " " << k << std::endl;
        }
    }
}