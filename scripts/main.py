import random
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
        self.add_random_obstacles(10, 64)

    def add_obstacle(self, position, max_radius, shape="circle"):
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

    def plot(self):
        plt.imshow(self.grid, cmap='gray')
        plt.show()

    def add_random_obstacles(self, n, max_radius):
        for _ in range(n):
            position = (random.randint(0, self.grid.shape[0]), random.randint(0, self.grid.shape[1]))
            self.add_obstacle(position, max_radius)
    
    def get_grid(self):
        return self.grid

    def get_collision_dumb(self, position):
        return self.grid[position[0], position[1]] == 0

    def get_collision(self, position):
        for polygon in self.polygons:
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
        plt.draw()
        plt.pause(0.001)
        plt.show()


if __name__ == "__main__":
    env = Environment((1000, 2000))
    plot = InteractivePlot(env)
    # env.plot()


