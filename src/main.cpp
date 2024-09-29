#include <iostream>
#include "../include/primitives.h"
#include <random>
#include <cmath>
double MIN_X = 0.0, MAX_X =100.0, MIN_Y = 0.0, MAX_Y = 100.0;
double START_X = 2.5, START_Y = 2.5, END_X = 85.5, END_Y = 90.5;
double STEP_SIZE = 1, NEIGHBOUR_RADIUS = 1.5, GOAL_THRES = 1.5;
double MAX_DOUBLE1 = std::numeric_limits<double>::max();
int MAX_ITER = 10000;

std::array<double, 2> get_point_in_step_size(Point p, double x, double y) {
    double new_x, new_y;
    new_x = p.x + STEP_SIZE * ((x - p.x) / sqrt(pow((p.y-y),2)+ pow((p.x-x),2)));
    new_y = p.y + STEP_SIZE * ((y - p.y) / sqrt(pow((p.y-y),2)+ pow((p.x-x),2)));
    std::array<double, 2> new_points_arr = {new_x, new_y};
    return new_points_arr;
}

int main() {
    std::random_device rd;  // Obtain a random seed
    std::mt19937 gen(rd()); // Initialize the generator
    std::uniform_real_distribution<> dis_X(MIN_X, MAX_X);
    std::uniform_real_distribution<> dis_Y(MIN_Y, MAX_Y);
    // Generate random x and y coordinates

    Points points;
    Edges edges;

    int start_id= points.set(START_X, START_Y);
    points.set_cost(start_id, 0.0);
    // int end_id = points.set(END_X,END_Y);
    double exit_distance = MAX_DOUBLE1;
    double min_distance = MAX_DOUBLE1;
    double iter = 0;

    while(exit_distance > GOAL_THRES) {
    // while(iter < MAX_ITER) {
        iter++;
        bool valid = false;
        std::array<double, 2> new_coords;
        while (not valid) {
            double x = dis_X(gen);
            double y = dis_Y(gen);
            int closest_id = points.get_closest(x, y);
            new_coords = get_point_in_step_size(points.get(closest_id), x, y);
            int new_closest_id = points.get_closest(new_coords[0], new_coords[1]);
            double closest_distance = sqrt(std::pow(new_coords[0] - points.get(new_closest_id).x, 2) +
                std::pow(new_coords[1] - points.get(new_closest_id).y, 2));
            if (closest_distance > STEP_SIZE*0.5) {
                if (new_coords[0] >= START_X && new_coords[0] <= END_X && new_coords[1] >= START_Y && new_coords[1] <= END_Y) {
                    valid = true;
                }
            }
        }
        std::vector<Point> neighbours = points.get_neighbours(NEIGHBOUR_RADIUS, new_coords[0], new_coords[1]);
        double min_dist = MAX_DOUBLE1;
        int min_dist_id = 0;
        for(auto & neighbour : neighbours){
            double curr_dist = points.get_cost(neighbour.id) + sqrt((pow(new_coords[0]-neighbour.x,2) + pow(new_coords[1]-neighbour.y,2)));
            if(curr_dist < min_dist){
                min_dist = curr_dist;
                min_dist_id = neighbour.id;
            }
        }
        int new_point_id = points.set(new_coords[0], new_coords[1]);
        edges.set_edge(min_dist_id, new_point_id);
        points.set_cost(new_point_id, min_dist);
        for(auto & neighbour : neighbours){
            double curr_dist = min_dist + points.get_distance(neighbour.id, new_point_id);
//            std::cout<<curr_dist<<" "<<points.get_cost(neighbour.id)<<std::endl;
            if(curr_dist < points.get_cost(neighbour.id)){
                points.set_cost(neighbour.id, curr_dist);
                edges.change_id(new_point_id, neighbour.id);
            }
        }
        exit_distance = sqrt(pow(END_X - points.get(new_point_id).x, 2) + pow(END_Y - points.get(new_point_id).y, 2));
        if (exit_distance < min_distance) {min_distance = exit_distance;}
        // std::cout << min_distance << " " << exit_distance << " " << x << " " << y << " " << new_coords[0] << " " << new_coords[1] <<std::endl;
        // std::cout << min_distance << " " << exit_distance << " " << new_coords[0] << " " << new_coords[1] <<std::endl;

    }
    std::cout << "===============" << std::endl;
    points.print_points();
    std::cout << "===============" << std::endl;
    edges.print_edges();
    return 0;
}
