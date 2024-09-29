#include <iostream>
#include "../include/primitives.h"
#include <random>
#include <cmath>
double MIN_X = 0.0, MAX_X = 10.0, MIN_Y = 0.0, MAX_Y = 10.0, START_X = 2.5, START_Y = 3.5, END_X = 5.5, END_Y = 7.5, STEP_SIZE = 0.7,NEIGHBOUR_RADIUS = 1.9,GOAL_THRES=1.0;
double MAX_DOUBLE1 = std::numeric_limits<double>::max();

std::array<double, 2> get_point_in_step_size(Point p, double x, double y) {
    double new_x, new_y;
    new_x = p.x + STEP_SIZE * ((p.x - x) / sqrt(pow((p.y-y),2)+ pow((p.x-x),2)));
    new_y = p.y + STEP_SIZE * ((p.y - y) / sqrt(pow((p.y-y),2)+ pow((p.x-x),2)));
    std::array<double, 2> new_points_arr = {new_x,new_y};
//    std::cout<<x<<" "<<y<<" "<<new_x<<" "<<new_y<<" "<<p.x<<" "<<p.y<<std::endl;
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

    int start_id= points.set(START_X,START_Y);
    points.set_cost(start_id, 0.0);
//    int end_id = points.set(END_X,END_Y);

    while(true) {
        double x = dis_X(gen);
        double y = dis_Y(gen);
        int closest_id = points.get_closest(x,y);
        std::array<double, 2> new_coords = get_point_in_step_size(points.get(closest_id), x, y);
        std::vector<Point> neighbours = points.get_neighbours(NEIGHBOUR_RADIUS, new_coords[0], new_coords[1]);
        double min_dist = MAX_DOUBLE1;
        int min_dist_id = 0;
        double curr_dist = 0;
        for(auto & neighbour : neighbours){
            curr_dist = points.get_cost(neighbour.id) + sqrt((pow(new_coords[0]-neighbour.x,2) + pow(new_coords[1]-neighbour.y,2)));
            if(curr_dist< min_dist){
                min_dist = curr_dist;
                min_dist_id = neighbour.id;
            }
        }
        int new_point_id = points.set(new_coords[0], new_coords[1]);
        edges.set_edge(min_dist_id,new_point_id);
        points.set_cost(new_point_id,min_dist);
        for(auto & neighbour : neighbours){
            curr_dist = min_dist + points.get_distance(neighbour.id, new_point_id);
//            std::cout<<curr_dist<<" "<<points.get_cost(neighbour.id)<<std::endl;
            if(curr_dist< points.get_cost(neighbour.id)){
                points.set_cost(neighbour.id, curr_dist);
                edges.change_id(new_point_id,neighbour.id);
            }
        }
        if (sqrt((pow(END_X - points.get(new_point_id).x, 2) + pow(END_Y - points.get(new_point_id).x, 2))) <
            GOAL_THRES)

            break;
        else {
            std::cout << sqrt((pow(END_X - points.get(new_point_id).x, 2) + pow(END_Y - points.get(new_point_id).x, 2)))
                                      << std::endl;
            std::cout<<x<<" "<<y<<" "<<new_coords[0]<<" "<<new_coords[1]<<std::endl;
        }

    }
    return 0;
}
