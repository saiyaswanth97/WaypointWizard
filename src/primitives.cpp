//
// Created by gsanthosh on 28/9/24.
//

#include "../include/primitives.h"
#include <cmath>
double MAX_DOUBLE = std::numeric_limits<double>::max();

Points::Points() {
    last_id =0;
}

int Points::set(double x, double y) {

    Point p{} ;
    p.id = last_id++;
    // TODO logic error?
    p.cost = 0;
    p.x = x;
    p.y = y;

    points_list.insert(std::pair<int, Point>(p.id,p) );

    return p.id;
}

void Points::set_cost(int id, double cost) {
    points_list[id].cost  = cost;
}

Point Points::get(int id) {
    return points_list[id];
}

int Points::get_last_id() const {
    return last_id;
}

double Points::get_distance(int id_1, int id_2) {
    double distance = sqrt(pow(points_list[id_1].x - points_list[id_2].x ,2) + pow(points_list[id_1].y - points_list[id_2].y ,2));
    return distance;
}

double Points::get_cost(int id){
    return points_list[id].cost;
}

std::vector<Point> Points::get_neighbours(double thres_dist, double x , double y) {
    std::vector<Point> neighbouring_points;

    std::map<int , Point>::iterator it;

    for(it = points_list.begin(); it!=points_list.end(); it++){
        if(sqrt(pow(it->second.x - x ,2) + pow(it->second.y - y ,2))<=thres_dist){
            neighbouring_points.push_back(it->second);
        }
    }
    return neighbouring_points;
}

int Points::get_closest(double x, double y) {

    std::map<int , Point >::iterator it;
    int min_id = -1;
    double min_dist = MAX_DOUBLE;
    for(it = points_list.begin(); it!=points_list.end(); it++){

        double cur_dist = sqrt(pow(it->second.x - x ,2) + pow(it->second.y - y ,2));

        if(cur_dist< min_dist){
            min_dist = cur_dist;
            min_id = it->first;
        }
    }
    return min_id;
}

Edges::Edges() {
    last_edge_idx = 0;
}

int Edges::set_edge(int id_1, int id_2) {
    Edge e{} ;
    e.edge_index = last_edge_idx++;
    e.id_1 = id_1;
    e.id_2 = id_2;

    edge_list.insert(std::pair<int, Edge>(e.edge_index,e) );

    return e.edge_index;
}

void Edges::change_id(int new_id, int id_2) {
    std::map<int, Edge>::iterator it;

    for (it = edge_list.begin(); it != edge_list.end(); it++) {
        if (it->second.id_2 == id_2) {
            it->second.id_1 = new_id;
        }
    }
}


