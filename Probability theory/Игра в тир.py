import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle, Polygon
import numpy as np

def darts(size):
    x0 = 6
    y0 = 6
    R = 5
    side = np.sqrt(2 * np.pi * R ** 2)
    figsize = (5, 5)
    figur, ax = plt.subplots(figsize=figsize)


    ax.add_patch(Rectangle((0, 0), side, side, facecolor='gray'))

    diamond_vertices = [
        [x0, y0 + R],
        [x0 + R, y0],
        [x0, y0 - R],
        [x0 - R, y0]
    ]
    ax.add_patch(Polygon(diamond_vertices, facecolor='orange'))

    X = np.random.uniform(0, side, size)
    Y = np.random.uniform(0, side, size)
    plt.scatter(X, Y, marker='o', c='black', s=10)

    inside_rhombus = (np.abs(X - x0) + np.abs(Y - y0)) <= R
    inside = np.sum(inside_rhombus)
    prob = inside / size

    plt.title(f'Вероятность попадания: {prob:.3f}')
    plt.gca().set_aspect('equal')
    plt.show()

    return prob

result = darts(1000)
print(f"Оценка вероятности: {result}")