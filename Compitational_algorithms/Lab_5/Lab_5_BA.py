import numpy as np
import tkinter as tk
from tkinter import ttk
from tkinter import messagebox
from matplotlib.figure import Figure
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg
import matplotlib.figure

# --- Task 1: Single ODE - Runge-Kutta Method ---

def f1(x, y):
    """
    Defines the ODE: (exp^x + 2)dy + (2*exp^x)dx  => dy/dx = -2*exp(x) / (exp(x) + 2)
    """
    return -2 * np.exp(x) / (np.exp(x) + 2)


def runge_kutta(f, x0, y0, xend, h):

    x_values = np.arange(x0, xend + h, h)  # Include xend in x_values
    y_values = [y0]

    for i in range(len(x_values) - 1):
        x = x_values[i]
        y = y_values[-1]
        k1 = h * f(x, y)
        k2 = h * f(x + h / 2, y + k1 / 2)
        k3 = h * f(x + h / 2, y + k2 / 2)
        k4 = h * f(x + h, y + k3)
        y_next = y + (k1 + 2 * k2 + 2 * k3 + k4) / 6
        y_values.append(y_next)

    return x_values, np.array(y_values)


def task1(h=0.2):
    """
    Solves and plots the ODE for Task 1 with different step sizes.
    """
    try:
        x0 = 0
        y0 = 1 / 9
        xend = 1.6

        fig = matplotlib.figure.Figure(figsize=(6, 4), dpi=100)  # Create a figure
        ax = fig.add_subplot(111)  # Add an axes to the figure

        # Calculate and plot for h
        x_h, y_h = runge_kutta(f1, x0, y0, xend, h)
        ax.plot(x_h, y_h, label=f'h = {h:.2f}')

        # Calculate and plot for 2h
        x_2h, y_2h = runge_kutta(f1, x0, y0, xend, 2 * h)
        ax.plot(x_2h, y_2h, label=f'2h = {2*h:.2f}')

        # Calculate and plot for h/2
        x_h_over_2, y_h_over_2 = runge_kutta(f1, x0, y0, xend, h / 2)
        ax.plot(x_h_over_2, y_h_over_2, label=f'h/2 = {h/2:.2f}')


        ax.set_xlabel('x')
        ax.set_ylabel('y')
        ax.set_title('Task 1: ODE Solution')
        ax.legend()
        ax.grid(True)
        return fig  # Return the Figure object

    except Exception as e:
        messagebox.showerror("Error", f"An error occurred during Task 1 calculation: {e}")
        return None


# --- Task 2: System of ODEs - Runge-Kutta Method ---

def f1_system(x, y1, y2):
    """
    Defines f1(x, y1, y2) for Task 2.
    """
    return 2 * np.sqrt(3 * x**2 + y1**2 + y1)


def f2_system(x, y1, y2):
    """
    Defines f2(x, y1, y2) for Task 2.
    """
    return np.sqrt(x**2 + y1**2 + y2)


def runge_kutta_system(f1, f2, a, y1_0, y2_0, b, h):
    """
    Solves a system of two ODEs using the 4th order Runge-Kutta method.

    Args:
        f1: The function representing dy1/dx = f1(x, y1, y2).
        f2: The function representing dy2/dx = f2(x, y1, y2).
        a: Initial x value.
        y1_0: Initial y1 value.
        y2_0: Initial y2 value.
        b: End x value.
        h: Step size.

    Returns:
        Tuple: (x_values, y1_values, y2_values)
    """
    x_values = np.arange(a, b + h, h)
    y1_values = [y1_0]
    y2_values = [y2_0]

    for i in range(len(x_values) - 1):
        x = x_values[i]
        y1 = y1_values[-1]
        y2 = y2_values[-1]

        # Runge-Kutta steps
        k1_1 = h * f1(x, y1, y2)
        k1_2 = h * f2(x, y1, y2)

        k2_1 = h * f1(x + h / 2, y1 + k1_1 / 2, y2 + k1_2 / 2)
        k2_2 = h * f2(x + h / 2, y1 + k1_1 / 2, y2 + k1_2 / 2)

        k3_1 = h * f1(x + h / 2, y1 + k2_1 / 2, y2 + k2_2 / 2)
        k3_2 = h * f2(x + h / 2, y1 + k2_1 / 2, y2 + k2_2 / 2)

        k4_1 = h * f1(x + h, y1 + k3_1, y2 + k3_2)
        k4_2 = h * f2(x + h, y1 + k3_1, y2 + k3_2)

        y1_next = y1 + (k1_1 + 2 * k2_1 + 2 * k3_1 + k4_1) / 6
        y2_next = y2 + (k1_2 + 2 * k2_2 + 2 * k3_2 + k4_2) / 6

        y1_values.append(y1_next)
        y2_values.append(y2_next)

    return x_values, np.array(y1_values), np.array(y2_values)


def task2(h=0.1):
    """
    Solves and plots the system of ODEs for Task 2 with different step sizes.
    """
    try:
        a = 0
        y1_0 = 1.2
        y2_0 = 1.2
        b = 2

        fig = matplotlib.figure.Figure(figsize=(6, 4), dpi=100)  # Create a figure
        ax = fig.add_subplot(111)  # Add an axes to the figure


        # Calculate and plot for h
        x_h, y1_h, y2_h = runge_kutta_system(f1_system, f2_system, a, y1_0, y2_0, b, h)
        ax.plot(x_h, y1_h, label=f'y1, h = {h:.2f}')
        ax.plot(x_h, y2_h, label=f'y2, h = {h:.2f}')

        # Calculate and plot for 2h
        x_2h, y1_2h, y2_2h = runge_kutta_system(f1_system, f2_system, a, y1_0, y2_0, b, 2 * h)
        ax.plot(x_2h, y1_2h, label=f'y1, 2h = {2*h:.2f}')
        ax.plot(x_2h, y2_2h, label=f'y2, 2h = {2*h:.2f}')

        # Calculate and plot for h/2
        x_h_over_2, y1_h_over_2, y2_h_over_2 = runge_kutta_system(f1_system, f2_system, a, y1_0, y2_0, b, h / 2)
        ax.plot(x_h_over_2, y1_h_over_2, label=f'y1, h/2 = {h/2:.2f}')
        ax.plot(x_h_over_2, y2_h_over_2, label=f'y2, h/2 = {h/2:.2f}')


        ax.set_xlabel('x')
        ax.set_ylabel('y')
        ax.set_title('Task 2: System of ODEs Solution')
        ax.legend()
        ax.grid(True)

        return fig # Return the Figure object

    except Exception as e:
        messagebox.showerror("Error", f"An error occurred during Task 2 calculation: {e}")
        return None


# --- Task 3: Second-Order Linear Homogeneous ODE ---

def solve_second_order_ode(a1, a2, a, y0, y1, xend, h):
    """
    Solves a second-order linear homogeneous ODE using the conversion to a system of first-order ODEs.
    y'' + a1*y' + a2*y = 0
    y(a) = y0
    y'(a) = y1

    Args:
        a1: Coefficient of y'.
        a2: Coefficient of y.
        a: Initial x value.
        y0: Initial y value (y(a)).
        y1: Initial y' value (y'(a)).
        xend: End x value.
        h: Step size.

    Returns:
        Tuple: (x_values, y_values, y_prime_values)
    """
    def f1_system(x, y, z):  # z = y'
        return z  # dy/dx = y'

    def f2_system(x, y, z):
        return -a1 * z - a2 * y  # dz/dx = y'' = -a1*y' - a2*y

    x_values = np.arange(a, xend + h, h)
    y_values = [y0]
    y_prime_values = [y1]

    for i in range(len(x_values) - 1):
        x = x_values[i]
        y = y_values[-1]
        z = y_prime_values[-1]

        # Runge-Kutta steps (for a system of two equations)
        k1_y = h * f1_system(x, y, z)
        k1_z = h * f2_system(x, y, z)

        k2_y = h * f1_system(x + h / 2, y + k1_y / 2, z + k1_z / 2)
        k2_z = h * f2_system(x + h / 2, y + k1_y / 2, z + k1_z / 2)

        k3_y = h * f1_system(x + h / 2, y + k2_y / 2, z + k2_z / 2)
        k3_z = h * f2_system(x + h / 2, y + k2_y / 2, z + k2_z / 2)

        k4_y = h * f1_system(x + h, y + k3_y, z + k3_z)
        k4_z = h * f2_system(x + h, y + k3_y, z + k3_z)

        y_next = y + (k1_y + 2 * k2_y + 2 * k3_y + k4_y) / 6
        z_next = z + (k1_z + 2 * k2_z + 2 * k3_z + k4_z) / 6

        y_values.append(y_next)
        y_prime_values.append(z_next)

    return x_values, np.array(y_values), np.array(y_prime_values)



def task3(h=0.2):
    """
    Solves the second-order ODE for Task 3 and plots the solution.
    """
    try:
        a1 = 2
        a2 = 5
        a = 1
        y0 = 0
        y1 = 0
        xend = 4  # Adjust as needed.

        fig = matplotlib.figure.Figure(figsize=(6, 4), dpi=100)  # Create a figure
        ax = fig.add_subplot(111)  # Add an axes to the figure

        # Calculate and plot for h
        x_h, y_h, yp_h = solve_second_order_ode(a1, a2, a, y0, y1, xend, h)
        ax.plot(x_h, y_h, label=f'h = {h:.2f}')

        # Calculate and plot for 2h
        x_2h, y_2h, yp_2h = solve_second_order_ode(a1, a2, a, y0, y1, xend, 2 * h)
        ax.plot(x_2h, y_2h, label=f'2h = {2*h:.2f}')

        # Calculate and plot for h/2
        x_h_over_2, y_h_over_2, yp_h_over_2 = solve_second_order_ode(a1, a2, a, y0, y1, xend, h/2)
        ax.plot(x_h_over_2, y_h_over_2, label=f'h/2 = {h/2:.2f}')

        ax.set_xlabel('x')
        ax.set_ylabel('y')
        ax.set_title('Task 3: Second-Order ODE Solution')
        ax.legend()
        ax.grid(True)

        return fig  # Return the Figure object

    except Exception as e:
        messagebox.showerror("Error", f"An error occurred during Task 3 calculation: {e}")
        return None



# --- GUI using Tkinter ---

def show_task_description(task_number):
    """Displays the problem statement in the text area using LaTeX."""
    description_text.delete("1.0", tk.END)  # Clear previous text

    if task_number == 1:
        description = r"""Задача 1: Решите задачу Коши методом Рунге-Кутта:
            (e^x + 2) dy/dx + 2e^x = 0, y(0) = 1/9, x ∈ [0, 1.6]"""
    elif task_number == 2:
        description = r"""Задача 2: Решите систему ОДУ методом Рунге-Кутта:
            dy1/dx = 2√(3x² + y1² + y1)
            dy2/dx = √(x² + y1² + y2)
            y1(0) = y2(0) = 1.2, x ∈ [0, 2]"""
    elif task_number == 3:
        description = r"""Задача 3: Решите ОДУ второго порядка:
            y'' + 2y' + 5y = 0, y(1) = 0, y'(1) = 0"""
    else:
        description = "Select a task to view its description."

    description_text.insert(tk.END, description)


def run_selected_task():
    """Runs the selected task and displays the plot."""
    selected_task = task_var.get()
    step_size = step_size_entry.get()

    try:
        h = float(step_size)
    except ValueError:
        messagebox.showerror("Error", "Invalid step size. Please enter a number.")
        return

    # Clear previous plot, if it exists
    for item in graph_frame.winfo_children():
        item.destroy()

    if selected_task == 1:
        fig = task1(h)
    elif selected_task == 2:
        fig = task2(h)
    elif selected_task == 3:
        fig = task3(h)
    else:
        messagebox.showinfo("Info", "Please select a task.")
        return

    if fig:
        canvas = FigureCanvasTkAgg(fig, master=graph_frame)
        canvas.draw()
        canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=1)
        #canvas._tkcanvas.pack(side=tk.TOP, fill=tk.BOTH, expand=1) #No longer needed


# --- GUI Setup ---

root = tk.Tk()
root.title("ODE Solver")

# Task Selection
task_var = tk.IntVar(value=1)  # Default selected task

task_frame = ttk.LabelFrame(root, text="Select Task")
task_frame.grid(row=0, column=0, padx=10, pady=10, sticky="ew")

task1_radio = ttk.Radiobutton(task_frame, text="Task 1", variable=task_var, value=1, command=lambda: show_task_description(1))
task1_radio.grid(row=0, column=0, padx=5, pady=5, sticky="w")

task2_radio = ttk.Radiobutton(task_frame, text="Task 2", variable=task_var, value=2, command=lambda: show_task_description(2))
task2_radio.grid(row=1, column=0, padx=5, pady=5, sticky="w")

task3_radio = ttk.Radiobutton(task_frame, text="Task 3", variable=task_var, value=3, command=lambda: show_task_description(3))
task3_radio.grid(row=2, column=0, padx=5, pady=5, sticky="w")

# Step Size Entry
step_size_frame = ttk.LabelFrame(root, text="Step Size (h)")
step_size_frame.grid(row=1, column=0, padx=10, pady=10, sticky="ew")

step_size_entry = ttk.Entry(step_size_frame, width=10)
step_size_entry.insert(0, "0.2")  # Default step size
step_size_entry.pack(side=tk.LEFT, padx=5, pady=5)

# Run Button
run_button = ttk.Button(root, text="Run Task", command=run_selected_task)
run_button.grid(row=2, column=0, padx=10, pady=10, sticky="ew")


# Task Description (Text Area)
description_frame = ttk.LabelFrame(root, text="Task Description")
description_frame.grid(row=0, column=1, rowspan=3, padx=10, pady=10, sticky="nsew")
description_text = tk.Text(description_frame, height=10, width=70, wrap=tk.WORD)
description_text.pack(padx=5, pady=5, fill=tk.BOTH, expand=True)
show_task_description(1)  # Show description for the default selected task

# Graph Frame
graph_frame = ttk.LabelFrame(root, text="Graph")
graph_frame.grid(row=0, column=2, rowspan=3, padx=10, pady=10, sticky="nsew")


# Configure column/row resizing
root.columnconfigure(2, weight=1)  # Make the graph frame expand
root.rowconfigure(2, weight=1)     # Make the Run button row expand (if needed)
root.rowconfigure(0, weight=1)
root.rowconfigure(1, weight=1)



root.mainloop()