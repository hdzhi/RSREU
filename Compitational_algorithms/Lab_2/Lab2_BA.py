import tkinter as tk
from tkinter import ttk
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import math


class RootFindingGUI:
    def __init__(self, master):
        self.master = master
        master.title("Решение уравнения tan(x) = x")

        self.a_label = ttk.Label(master, text="Начало интервала (a):")
        self.a_label.grid(row=0, column=0, padx=5, pady=5, sticky="e")
        self.a_entry = ttk.Entry(master)
        self.a_entry.grid(row=0, column=1, padx=5, pady=5, sticky="w")
        self.a_entry.insert(0, "4.4")

        self.b_label = ttk.Label(master, text="Конец интервала (b):")
        self.b_label.grid(row=1, column=0, padx=5, pady=5, sticky="e")
        self.b_entry = ttk.Entry(master)
        self.b_entry.grid(row=1, column=1, padx=5, pady=5, sticky="w")
        self.b_entry.insert(0, "4.7")

        self.x0_label = ttk.Label(master, text="Начальное приближение (x0):")
        self.x0_label.grid(row=2, column=0, padx=5, pady=5, sticky="e")
        self.x0_entry = ttk.Entry(master)
        self.x0_entry.grid(row=2, column=1, padx=5, pady=5, sticky="w")
        self.x0_entry.insert(0, "4.55")

        self.epsilon_label = ttk.Label(master, text="Точность (epsilon):")
        self.epsilon_label.grid(row=3, column=0, padx=5, pady=5, sticky="e")
        self.epsilon_entry = ttk.Entry(master)
        self.epsilon_entry.grid(row=3, column=1, padx=5, pady=5, sticky="w")
        self.epsilon_entry.insert(0, "0.0001")

        self.method_label = ttk.Label(master, text="Метод:")
        self.method_label.grid(row=4, column=0, padx=5, pady=5, sticky="e")
        self.method = tk.StringVar(value="all")  # Default to showing all

        self.all_check = ttk.Radiobutton(master, text="Все методы", variable=self.method, value="all")
        self.all_check.grid(row=4, column=1, padx=5, pady=5, sticky="w")

        self.dichotomy_check = ttk.Radiobutton(master, text="Дихотомия", variable=self.method, value="dichotomy")
        self.dichotomy_check.grid(row=5, column=1, padx=5, pady=5, sticky="w")

        self.chord_check = ttk.Radiobutton(master, text="Хорд", variable=self.method, value="chord")
        self.chord_check.grid(row=6, column=1, padx=5, pady=5, sticky="w")

        self.newton_check = ttk.Radiobutton(master, text="Ньютона", variable=self.method, value="newton")
        self.newton_check.grid(row=7, column=1, padx=5, pady=5, sticky="w")

        self.modified_newton_check = ttk.Radiobutton(master, text="Модифицированный Ньютона", variable=self.method, value="modified_newton")
        self.modified_newton_check.grid(row=8, column=1, padx=5, pady=5, sticky="w")

        self.combined_check = ttk.Radiobutton(master, text="Комбинированный", variable=self.method, value="combined")
        self.combined_check.grid(row=9, column=1, padx=5, pady=5, sticky="w")

        self.iteration_check = ttk.Radiobutton(master, text="Итерационный", variable=self.method, value="iteration")
        self.iteration_check.grid(row=10, column=1, padx=5, pady=5, sticky="w")


        self.calculate_button = ttk.Button(master, text="Вычислить", command=self.calculate_and_display)
        self.calculate_button.grid(row=11, column=0, columnspan=2, padx=5, pady=5)


        self.result_text = tk.Text(master, height=15, width=60)
        self.result_text.grid(row=12, column=0, columnspan=2, padx=5, pady=5)


        self.fig, self.ax = plt.subplots()
        self.canvas = FigureCanvasTkAgg(self.fig, master=master)
        self.canvas.get_tk_widget().grid(row=0, column=2, rowspan=13, padx=5, pady=5)
        self.plot_function()


    def f(self, x):
        return math.tan(x) - x

    def f_derivative(self, x):
        return (1 / math.cos(x)**2) - 1

    def dichotomy_method(self, a, b, eps):
        if self.f(a) * self.f(b) >= 0:
            return None

        iterations = []
        while (b - a) / 2 > eps:
            c = (a + b) / 2
            iterations.append(c) # Store intermediate values
            if self.f(c) == 0:
                return c
            elif self.f(a) * self.f(c) < 0:
                b = c
            else:
                a = c
        return (a + b) / 2

    def chord_method(self, x0, x1, eps):
        iterations = []
        for _ in range(100):
            try:
                x2 = x1 - self.f(x1) * (x1 - x0) / (self.f(x1) - self.f(x0))
                iterations.append(x2)
            except ZeroDivisionError:
                return None
            if abs(x2 - x1) < eps:
                return x2
            x0, x1 = x1, x2
        return None

    def newton_method(self, x0, eps):
        iterations = []
        for _ in range(100):
            try:
                x1 = x0 - self.f(x0) / self.f_derivative(x0)
                iterations.append(x1)
            except ZeroDivisionError:
                return None
            if abs(x1 - x0) < eps:
                return x1
            x0 = x1
        return None

    def modified_newton_method(self, x0, eps):
        iterations = []
        f_derivative_x0 = self.f_derivative(x0)
        for _ in range(100):
            try:
                x1 = x0 - self.f(x0) / f_derivative_x0
                iterations.append(x1)
            except ZeroDivisionError:
                return None
            if abs(x1 - x0) < eps:
                return x1
            x0 = x1
        return None

    def combined_method(self, a, b, eps):
        iterations = []
        x0 = a
        x1 = b
        for _ in range(100):
            try:
                x_newton = x1 - self.f(x1) / self.f_derivative(x1)
                x_secant = x0 - self.f(x0) * (x1 - x0) / (self.f(x1) - self.f(x0))
                iterations.append((x_newton, x_secant))
            except ZeroDivisionError:
                return None

            if abs(x_newton - x_secant) < eps:
                return (x_newton + x_secant) / 2

            x0 = x_secant
            x1 = x_newton
        return None

    def iterative_method(self, x0, eps):
        iterations = []
        m = self.f_derivative(x0)

        for _ in range(100):
            try:
                x1 = x0 - (math.tan(x0) - x0) / m
                iterations.append(x1)
            except ValueError:
                return None
            if abs(x1 - x0) < eps:
                return x1
            x0 = x1
        return None

    def plot_function(self):
        """Plots the function and marks the root."""
        a = float(self.a_entry.get())
        b = float(self.b_entry.get())

        x_values = np.linspace(a-1, b+1, 400)
        y_values = [self.f(x) for x in x_values]

        self.ax.clear()
        self.ax.plot(x_values, y_values, label="f(x) = tan(x) - x")
        self.ax.axhline(0, color='black', linewidth=0.5, linestyle='--')
        self.ax.axvline(0, color='black', linewidth=0.5, linestyle='--')
        self.ax.set_xlabel('x')
        self.ax.set_ylabel('f(x)')
        self.ax.set_title('График функции f(x) = tan(x) - x')
        self.ax.legend()
        self.ax.grid(True)
        self.canvas.draw()


    def calculate_and_display(self):
        a = float(self.a_entry.get())
        b = float(self.b_entry.get())
        x0 = float(self.x0_entry.get())
        epsilon = float(self.epsilon_entry.get())

        method = self.method.get()
        self.result_text.delete("1.0", tk.END)  # Clear previous results
        output_text = ""

        if method == "all":
            # Дихотомия
            result = self.dichotomy_method(a, b, epsilon)
            output_text += "Дихотомия: "
            if result is not None:
                output_text += f"{result}\n"
            else:
                output_text += "Метод не сошелся.\n"

            # Хорд
            result = self.chord_method(x0, a, epsilon) #Corrected the inputs
            output_text += "Хорд: "
            if result is not None:
                output_text += f"{result}\n"
            else:
                output_text += "Метод не сошелся.\n"

            # Ньютона
            result = self.newton_method(x0, epsilon)
            output_text += "Ньютона: "
            if result is not None:
                output_text += f"{result}\n"
            else:
                output_text += "Метод не сошелся.\n"

            # Модифицированный Ньютона
            result = self.modified_newton_method(x0, epsilon)
            output_text += "Модифицированный Ньютона: "
            if result is not None:
                output_text += f"{result}\n"
            else:
                output_text += "Метод не сошелся.\n"

            # Комбинированный
            result = self.combined_method(a, b, epsilon)
            output_text += "Комбинированный: "
            if result is not None:
                output_text += f"{result}\n"
            else:
                output_text += "Метод не сошелся.\n"

            # Итерационный
            result = self.iterative_method(x0, epsilon)
            output_text += "Итерационный: "
            if result is not None:
                output_text += f"{result}\n"
            else:
                output_text += "Метод не сошелся.\n"

        else:  # Single method selected
            if method == "dichotomy":
                result = self.dichotomy_method(a, b, epsilon)
            elif method == "chord":
                result = self.chord_method(x0, a, epsilon) #Corrected the inputs
            elif method == "newton":
                result = self.newton_method(x0, epsilon)
            elif method == "modified_newton":
                result = self.modified_newton_method(x0, epsilon)
            elif method == "combined":
                result = self.combined_method(a, b, epsilon)
            elif method == "iteration":
                result = self.iterative_method(x0, epsilon)
            else:
                result = None

            output_text = f"{method}: "
            if result is not None:
                output_text += f"{result}\n"
            else:
                output_text += "Метод не сошелся.\n"

        self.result_text.insert(tk.END, output_text) 
        self.plot_function()


root = tk.Tk()
gui = RootFindingGUI(root)
root.mainloop()