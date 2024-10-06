#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <vector>
#include <cmath>
#include <string>

struct Point {
    double x, y;
    Point(double x, double y);
    double distanceTo(Point p);
};

struct Polygon {
    std::vector<Point> points;
    double radius;
    enum type {Circle, Polygon};
    type t;
    bool isInside(Point point);
};

class Obstacle {
public:
    void addObstaclePolygon(std::vector<std::pair<double, double>> points, double radius, std::string type);
    void setEnvironmentLimits(double x_min, double x_max, double y_min, double y_max);
    bool isPointInObstacle(Point p);
    bool isPointInObstacle(std::vector<Point> points);
    bool isLineInObstacleBrute(Point p1, Point p2);

private:
    std::vector<Polygon> polygons;
    std::vector environment_limits;
};

#endif // ENVIRONMENT_H