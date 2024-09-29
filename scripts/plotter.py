import os
import csv
import numpy as np
import matplotlib.pyplot as plt


def read_old():
    data = []
    file = "data/points.csv"
    with open(file, "r") as f:
        reader = csv.reader(f)
        for row in reader:
            data_row = [(float)(string) for string in row[0].split(";")]
            data.append(data_row)
    points = np.array(points)
    x = points[:, 1]
    y = points[:, 2]
    idx = points[:, 0]

    file = "data/edges.csv"
    with open(file, "r") as f:
        reader = csv.reader(f)
        data = []
        for row in reader:
            data_row = [(int)(string) for string in row[0].split(";")]
            data.append(data_row)
    edges = np.array(edges)


if __name__ == "__main__":
    os.system("g++ -Iinclude -o rrt_star src/main.cpp src/primitives.cpp")
    os.system("./output_executable > data/data.csv")
    file = "data/tmp.csv"
    points = []
    edges = []
    with open(file, "r") as f:
        reader = csv.reader(f)
        index = 0
        for row in reader:
            if row[0] == "===============":
                index += 1
            else:
                if index == 1:
                    point = [(float)(string) for string in row[0].split(";")]
                    points.append(point)
                if index == 2:
                    edge = [(int)(string) for string in row[0].split(";")]
                    edges.append(edge)

    points = np.array(points)
    edges = np.array(edges)
    x = points[:, 1]
    y = points[:, 2]
    idx = points[:, 0]
    for edge in edges:
        start_idx = edge[1]
        end_idx = edge[2]
        plt.arrow(x[start_idx], y[start_idx], (x[end_idx] - x[start_idx])*0.9, (y[end_idx] - y[start_idx])*0.9, head_width=1.0, head_length=0.75, fc='r', ec='r')

    plt.scatter(x, y)
    plt.axis("equal")
    plt.show()

