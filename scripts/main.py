import random
import time
import numpy as np
from matplotlib import pyplot as plt

seed = 0
random.Random(seed)


class Environment:
    def __init__(self, grid_size, cell_size=1, min_radius=16):
        self.grid_size = grid_size
        self.cell_size = cell_size
        self.min_radius = min_radius
        grid_shape = ((int)(grid_size[0] / cell_size), (int)(grid_size[1] / cell_size))
        self.grid = np.ones((grid_shape[0], grid_shape[1]))
        self.polygons = []
        # TODO make it to config
        self.add_random_obstacles(20, 64)

    def add_obstacle(self, position, max_radius, shape="polygon"):
        if shape == "circle":
            x, y = position
            radius = (int)(self.min_radius  + random.randint(0, max_radius - self.min_radius))
            for i in range(-radius, radius):
                for j in range(-radius, radius):
                    if np.sqrt(i**2 + j**2) < radius:
                        if x + i < 0 or x + i >= self.grid.shape[0] or y + j < 0 or y + j >= self.grid.shape[1]:
                            continue
                        self.grid[x + i, y + j] = 0
            self.polygons.append([position, radius, shape])
        if shape == "polygon":
            polygon = self.add_random_quadrilateral(position, max_radius)
            self.polygons.append([polygon, max_radius, shape])

    def plot(self):
        plt.imshow(self.grid, cmap='gray')
        plt.show()

    def add_random_obstacles(self, n, max_radius):
        for i in range(n):
            polygon_type = "circle" if random.random() < 0.5 else "polygon"
            x = random.randint(0, self.grid.shape[0])
            y = random.randint(0, self.grid.shape[1])
            self.add_obstacle([x, y], max_radius, polygon_type)

    def add_random_quadrilateral(self, position, max_radius, n=4):
        angles_init = np.linspace(0, 2*np.pi * (1 + 1/n), n + 1)
        min_angle = np.pi / 24
        polygon = []
        polygon_global = []
        for i in range(n):
            angle = random.uniform(angles_init[i] + min_angle, angles_init[i + 1] - min_angle)
            radius = (int)(self.min_radius  + random.randint(0, max_radius - self.min_radius))
            x = (int)(radius * np.cos(angle)) + max_radius
            y = (int)(radius * np.sin(angle)) + max_radius
            polygon.append([x, y])
        local_grid = np.ones((2 * max_radius, 2 * max_radius))

        x, y = np.meshgrid(np.arange(2 * max_radius), np.arange(2 * max_radius))
        inside = np.zeros(x.shape)
        for i in range(n):
            x1, y1 = polygon[i]
            x2, y2 = polygon[(i + 1) % n]
            slope = [(y2 - y1), (x2 - x1)]
            intercept = slope[1] * y1 - slope[0] * x1
            centre_sign = np.sign(slope[0] * max_radius + intercept - max_radius * slope[1])
            direction = (slope[0] * x + intercept - slope[1] * y) * centre_sign < 0
            inside = np.logical_or(inside, direction)
        local_grid = inside

        start_x, start_y = -min(0, position[0] - max_radius), -min(0, position[1] - max_radius)
        end_x = 2 * max_radius + min(0, self.grid.shape[0] - position[0] - 2*max_radius)
        end_y = 2 * max_radius + min(0, self.grid.shape[1] - position[1] - 2*max_radius)
        grid_start_x, grid_start_y = position[0] - radius + start_x, position[1] - radius + start_y
        grid_end_x, grid_end_y = grid_start_x + end_x - start_x, grid_start_y + end_y - start_y
        print(self.grid.shape, position, max_radius)
        print(grid_start_x, grid_start_y, grid_end_x, grid_end_y, start_x, start_y, end_x, end_y)

        self.grid[grid_start_x:grid_end_x, grid_start_y:grid_end_y] = np.logical_and(
            self.grid[grid_start_x:grid_end_x, grid_start_y:grid_end_y], local_grid[start_x:end_x, start_y:end_y])
        for point in polygon:
            x, y = point
            x = x - max_radius + position[0]
            y = y - max_radius + position[1]
            x, y = max(0, x), max(0, y)
            x, y = min(self.grid.shape[0] - 1, x), min(self.grid.shape[1] - 1, y)
            polygon_global.append([x, y])
        return polygon_global
    
    def get_grid(self):
        return self.grid

    def get_collision_dumb(self, position):
        return self.grid[position[0], position[1]] == 0

    def get_collision(self, position):
        for polygon in self.polygons:
            if polygon[2] == "circle":
                x, y = polygon[0]
                radius = polygon[1]
                if np.sqrt((x - position[0])**2 + (y - position[1])**2) < radius:
                    return True

class InteractivePlot:
    def __init__(self, env):
        self.env = env
        self.start = None
        self.end = None
        self.image = self.env.grid
        self.interactive_plot()

    def onclick(self, event):
        x, y = (int(event.xdata), int(event.ydata))
        if self.env.get_collision((x, y)):
            return
        if self.start is None:
            self.start = (int(event.xdata), int(event.ydata))
            self.refesh()
            print(f"Start: {self.start}")
        elif self.end is None:
            self.end = (int(event.xdata), int(event.ydata))
            self.refesh()
            print(f"End: {self.end}")

    def interactive_plot(self):
        self.fig, self.ax = plt.subplots()
        self.ax.imshow(self.env.grid, cmap='gray')
        self.fig.canvas.mpl_connect('button_press_event', self.onclick)
        self.ax.set_title("Click on the start (red) and end (green) points")
        self.fig.axes[0].get_xaxis().set_visible(False)
        self.fig.axes[0].get_yaxis().set_visible(False)
        plt.show()

    def refesh(self):
        if self.start is not None:
            self.ax.plot(self.start[0], self.start[1], 'r*', markersize=5)
        if self.end is not None:
            self.ax.plot(self.end[0], self.end[1], 'g*', markersize=5)
            self.ax.set_title("Close the plot to run the alogorithm...")
        plt.draw()
        plt.pause(0.001)
        plt.show()
        # TODO auto close the plot
        # if self.start is not None and self.end is not None:
        #     print("Closing the plot in 10 seconds")
        #     time.sleep(20)
        #     plt.close()

    def get_points(self):
        return self.start, self.end


if __name__ == "__main__":
    env = Environment((1000, 2000))
    plot = InteractivePlot(env)
    # time.sleep(5)
    start, end = plot.get_points()
    print(f"Start: {start}, End: {end}")
    while start is None or end is None:
        start, end = plot.get_points()
    print(f"Start: {start}, End: {end}")
    # env.plot()


