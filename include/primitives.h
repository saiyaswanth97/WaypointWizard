//
// Created by gsanthosh on 28/9/24.
//
#include <iostream>
#include <map>
#include <vector>
#ifndef RRT_STAR_POINT_H
#define RRT_STAR_POINT_H

#endif //RRT_STAR_POINT_H

struct Point{
    double x;
    double y;
    double cost;
    // TODO change this to unsigned int
    int id;
};

class Points{
    private:
        int last_id;
        std::map<int, Point> points_list;
    public:
        explicit Points();
        int set(double x, double y);
        void set_cost(int id, double cost);

        Point get(int id);
        std::vector<Point> get_neighbours(double thres_dist, double x ,double y);
        int get_closest(double x, double y);
        double get_distance(int id_1, int id_2);
        int get_last_id() const;
        double get_cost(int id);
        void print_points();
};

struct Edge{
    int id_1;
    int id_2;
    int edge_index;
};

class Edges : public Points{
    private:
        int last_edge_idx;
        std::map<int, Edge> edge_list;

    public:
        Edges();
        int set_edge(int id_1, int id_2);
        void change_id(int new_id , int id_2);
        void print_edges();
};
