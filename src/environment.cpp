struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
    double distanceTo(Point p) {
        return sqrt(pow(x - p.x, 2) + pow(y - p.y, 2));
    }
};

struct Polygon {
    std::vector<Point> points;
    std::double radius;
    enum type {Circle, Polygon};
    type t;
    bool isInside(Point points) {
        if this->t == Circle {
            bool inside = true;
            double x0, y0 = this->points[0].x, this->points[0].y;
            double r = this->radius;
            if (pow(points.x - x0, 2) + pow(points.y - y0, 2) <= pow(r, 2)) {
                return true;
            }
        }
        else if this->t == Polygon {
            // TODO check logic
            int n = this->points.size();
            bool inside = false;
            for (int i = 0, j = n - 1; i < n; j = i++) {
                if (((this->points[i].y > points.y) != (this->points[j].y > points.y)) &&
                    (points.x < (this->points[j].x - this->points[i].x) * (points.y - this->points[i].y) / (this->points[j].y - this->points[i].y) + this->points[i].x)) {
                    inside = !inside;
                }
            }
            return inside;
        }
};

class Obstacle {
    public:
    // TODO make it a map
    void addObstaclePolygon(std::vector<std::pair<double, double>> points, double radius, std::string type) {
        Polygon p;
        p.radius = radius;
        p.t = type == "Circle" ? Polygon::Circle : Polygon::Polygon;
        for (auto point : points) {
            p.points.push_back(Point(point.first, point.second));
        }
        polygons.push_back(p);
    }

    void setEnvironmentLimits(double x_min, double x_max, double y_min, double y_max) {
        environment_limits.push_back(x_min);
        environment_limits.push_back(x_max);
        environment_limits.push_back(y_min);
        environment_limits.push_back(y_max);
    }

    bool isPointInObstacle(Point p) {
        if (p.x < environment_limits[0] || p.x > environment_limits[1]
             || p.y < environment_limits[2] || p.y > environment_limits[3]) {
            return true;
        }
        for (auto polygon : polygons) {
            if (polygon.isInside(p)) {
                return true;
            }
        }
        return false;
    }

    bool isPointInObstacle(std::vector<Point> points) {
        for (auto point : points) {
            if (isPointInObstacle(point)) return true;
        }
        return false;
    }

    bool isLineInObstacleBrute(Point p1, Point p2) {
        std::vector<Point> points;
        for (int i = 0; i < 100; i++) {
            points.push_back(Point(p1.x + i * (p2.x - p1.x) / 100, p1.y + i * (p2.y - p1.y) / 100));
        }
        return isPointInObstacle(points);
    }
};