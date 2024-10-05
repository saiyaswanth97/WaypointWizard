//
// Created by gsanthosh on 29/9/24.
//
#include <vector>
#ifndef RRT_STAR_SMOOTHER_H
#define RRT_STAR_SMOOTHER_H

std::pair<double, double> get_potential_field_cost(std::pair<double, double> current_point);
void get_new_path(std::vector<std::pair<double, double>> & path_points, double alpha, double beta, double w_potetntial, int iterations);
std::vector<std::pair<double,double>> interpolate_points(std::pair<double, double> start_point , std::pair<double, double> end_point);

#endif //RRT_STAR_SMOOTHER_H
