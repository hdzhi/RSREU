import tkinter as tk
from tkinter import ttk
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg

def inner_newton(x, x_nodes, coeffs, direction="forward"):
    t = 1
    result = coeffs[0]
    n = len(x_nodes)

    if direction == "forward":
        for k in range(1, n):
            t *= x - x_nodes[k - 1]
            result += coeffs[k] * t
    elif direction == "backward":
        for k in range(1, n):
            t *= x - x_nodes[n - k]
            result += coeffs[k] * t

    return result


class NewtonInterpolatorGUI:
    def __init__(self, master):
        self.master = master
        master.title("Интерполяция Ньютона")

        self.a = 0
        self.b = 1
        self.n = 5

        self.n_label = ttk.Label(master, text="Количество узлов (n):")
        self.n_label.grid(row=0, column=0, padx=5, pady=5)

        self.n_entry = ttk.Entry(master)
        self.n_entry.insert(0, str(self.n))
        self.n_entry.grid(row=0, column=1, padx=5, pady=5)

        self.calculate_button = ttk.Button(master, text="Вычислить и построить графики", command=self.calculate_and_plot)
        self.calculate_button.grid(row=1, column=0, columnspan=2, padx=5, pady=10)

        self.figure, self.ax = plt.subplots(figsize=(8, 6))
        self.canvas = FigureCanvasTkAgg(self.figure, master=master)
        self.canvas.get_tk_widget().grid(row=2, column=0, columnspan=2, padx=5, pady=5)

        self.result_text = tk.Text(master, height=5, width=60)
        self.result_text.grid(row=3, column=0, columnspan=2, padx=5, pady=5)

        self.original_color = 'blue'
        self.forward_color = 'orange'
        self.backward_color = 'green'
        self.node_color = 'red'

    def f(self, x):
        return np.sin(np.pi * np.sin(np.pi * x))

    def forward_newton(self, x_nodes, y_nodes):
        n = len(x_nodes)
        diff_table = np.zeros((n, n))

        diff_table[:, 0] = y_nodes
        for j in range(1, n):
            for i in range(n - j):
                diff_table[i, j] = (diff_table[i + 1, j - 1] - diff_table[i, j - 1]) / (
                    x_nodes[i + j] - x_nodes[i]
                )

        coeffs = diff_table[0, :]

        # Возвращаем лямбда-функцию, которая вызывает inner_newton с правильными параметрами
        return lambda x: inner_newton(x, x_nodes, coeffs, direction="forward")

    def backward_newton(self, x_nodes, y_nodes):
        n = len(x_nodes)
        diff_table = np.zeros((n, n))

        diff_table[:, 0] = y_nodes
        for j in range(1, n):
            for i in range(n - 1, j - 1, -1):
                diff_table[i, j] = (diff_table[i, j - 1] - diff_table[i - 1, j - 1]) / (
                    x_nodes[i] - x_nodes[i - j]
                )

        coeffs = diff_table[n - 1, :]

        # Возвращаем лямбда-функцию, которая вызывает inner_newton с правильными параметрами
        return lambda x: inner_newton(x, x_nodes, coeffs, direction="backward")

    def calculate_and_plot(self):
        try:
            self.n = int(self.n_entry.get())
            if self.n <= 0:
                raise ValueError("Количество узлов должно быть положительным числом.")

            x_nodes = np.linspace(self.a, self.b, self.n)
            y_nodes = self.f(x_nodes)

            forward = self.forward_newton(x_nodes, y_nodes)
            backward = self.backward_newton(x_nodes, y_nodes)

            xs = np.linspace(self.a - 0.2, self.b + 0.2, 200)
            ys = self.f(xs)

            # Clear the previous plot
            self.ax.clear()

            self.ax.plot(xs, ys, "-", color=self.original_color, label="Original function")
            self.ax.plot(xs, [forward(x) for x in xs], "-", color=self.forward_color, label="Forward Newton Interpolation")
            self.ax.plot(xs, [backward(x) for x in xs], "--", color=self.backward_color, dashes=(5, 5), label="Backward Newton Interpolation")
            self.ax.scatter(x_nodes, y_nodes, c=self.node_color, label="Interpolation nodes")
            self.ax.legend()
            self.ax.set_title("Newton Interpolation")
            self.ax.set_xlabel("x")
            self.ax.set_ylabel("y")
            self.ax.grid(True)

            self.canvas.draw()

            # Display some results
            self.result_text.delete("1.0", tk.END)
            self.result_text.insert(tk.END, f"Количество узлов: {self.n}\n")
            self.result_text.insert(tk.END, f"Отрезок интерполирования: [{self.a}, {self.b}]\n")

        except ValueError as e:
            tk.messagebox.showerror("Ошибка", str(e))


root = tk.Tk()
gui = NewtonInterpolatorGUI(root)
root.mainloop()