import tkinter as tk
import tkinter.messagebox as messagebox
import numpy as np

def make_diagonally_dominant(A, b=None):
    A = np.copy(A)
    if b is not None:
        b = np.copy(b)

    n = len(A)

    for i in range(n):
        max_row = i
        max_val = abs(A[i, i])
        for r in range(i + 1, n):
            if abs(A[r, i]) > max_val:
                max_val = abs(A[r, i])
                max_row = r

        if max_row != i:
            A[[i, max_row]] = A[[max_row, i]]
            if b is not None:
                b[[i, max_row]] = b[[max_row, i]]

        for j in range(n):
            if i != j:
                factor = round(A[j, i] / A[i, i], 1)
                A[j] -= factor * A[i]
                if b is not None:
                    b[j] -= factor * b[i]

    if b is not None:
        return A, b
    else:
        return A

def inverse_matrix(A):
    A = np.copy(A)
    n = len(A)

    ident_matr = np.zeros((n, n))
    for i in range(n):
        ident_matr[i, i] = 1

    arg_matrix = np.zeros((n, 2 * n))
    for i in range(n):
        for j in range(n):
            arg_matrix[i, j] = A[i, j]
            arg_matrix[i, j + n] = ident_matr[i, j]

    for i in range(n):
        max_row = i
        max_val = abs(arg_matrix[i, i])
        for r in range(i + 1, n):
            if abs(arg_matrix[r, i]) > max_val:
                max_val = abs(arg_matrix[r, i])
                max_row = r

        arg_matrix[[i, max_row]] = arg_matrix[[max_row, i]]
        arg_matrix[i] = arg_matrix[i] / arg_matrix[i, i]

        for j in range(n):
            if i != j:
                arg_matrix[j] -= arg_matrix[j, i] * arg_matrix[i]

    return arg_matrix[:, n:]

def determinant_matrix(A):
    A = np.copy(A)
    n = len(A)
    det = 1

    for i in range(n):
        max_row = i
        max_val = abs(A[i, i])
        for r in range(i + 1, n):
            if abs(A[r, i]) > max_val:
                max_val = abs(A[r, i])
                max_row = r

        if i != max_row:
            A[[i, max_row]] = A[[max_row, i]]
            det *= -1
        el = A[i, i]
        if el == 0:
            return 0
        det *= el
        A[i] = A[i] / el

        for j in range(i + 1, n):
            A[j] -= A[j, i] * A[i]

    return det

def norm(A):
    maximum = 0

    for i in range(len(A)):
        summ = 0

        for j in range(len(A)):
            summ += abs(A[i][j])

        if summ > maximum:
            maximum = summ

    return maximum

def solve(A, b, eps):
    n = len(A)
    x = np.copy(b)
    iterations = 0
    prev_x = np.array([np.inf] * n)

    while sum(abs(x - prev_x)) > eps:
        prev_x = x
        nx = np.zeros(n)

        for i in range(n):
            for j in range(n):
                if i != j:
                    nx[i] += A[i][j] * x[j]

        for i in range(n):
            nx[i] = (b[i] - nx[i]) / A[i][i]
        x = nx
        iterations += 1

    return x, iterations

def calculate():
    try:
        # Read matrix A from input fields
        a_values = []
        for i in range(matrix_size):
            row_values = []
            for j in range(matrix_size):
                value = float(a_entries[i][j].get())
                row_values.append(value)
            a_values.append(row_values)
        A = np.array(a_values)

        # Read vector b from input fields
        b_values = []
        for i in range(matrix_size):
            value = float(b_entries[i].get())
            b_values.append(value)
        b = np.array(b_values)

        eps = 1e-4 # Default epsilon value

        # Perform calculations
        new_A, new_b = make_diagonally_dominant(A, b)
        x, iterations = solve(new_A, new_b, eps)
        det_A = determinant_matrix(A)
        norma_a = norm(A)
        inv_A = inverse_matrix(A)
        norma_inv_A = norm(inv_A)
        condition_number = norma_a * norma_inv_A


        # Update result labels
        for i in range(matrix_size):
            x_labels[i].config(text=f"{x[i]:.4f}")
        determinant_label.config(text=f"{det_A:.4f}")
        condition_number_label.config(text=f"{condition_number:.4f}")


    except ValueError:
        messagebox.showerror("Ошибка", "Пожалуйста, введите корректные числовые значения.")
    except np.linalg.LinAlgError:
        messagebox.showerror("Ошибка", "Невозможно вычислить обратную матрицу (матрица вырождена).")
    except Exception as e:
         messagebox.showerror("Ошибка", f"Произошла ошибка: {e}")

# Main window
root = tk.Tk()
root.title("Решение системы уравнений")
root.configure(bg="#f0f0f0")
root.geometry("500x500") # Increased window size

# Input data frame
input_frame = tk.Frame(root, bg="#f0f0f0")
input_frame.pack(pady=10)

matrix_size = 4
a_entries = []
b_entries = []

# Default A and b values (from the original code)
default_A = np.array([
    [6.1, 6.2, -6.3, 6.4],
    [1.1, -1.5, 2.2, -3.8],
    [5.1, -5.0, 4.9, -4.8],
    [1.8, 1.9, 2.0, -2.1]
])

default_b = np.array([6.5, 4.2, 4.7, 2.2])

# Matrix A labels and entries
for i in range(matrix_size):
    row_a = []
    for j in range(matrix_size):
        label_text = f"a{i+1}{j+1}:"
        label = tk.Label(input_frame, text=label_text, width=5, bg="#f0f0f0")
        label.grid(row=i, column=j*2, padx=2, pady=2)
        entry = tk.Entry(input_frame, width=5)
        entry.grid(row=i, column=j*2+1, padx=2, pady=2)
        entry.insert(0, str(default_A[i][j])) # Inserting default value
        row_a.append(entry)
    a_entries.append(row_a)

# Vector b labels and entries
for i in range(matrix_size):
    label_text = f"b{i+1}:"
    label = tk.Label(input_frame, text=label_text, width=3, bg="#f0f0f0")
    label.grid(row=i, column=matrix_size*2, padx=2, pady=2)
    entry = tk.Entry(input_frame, width=5)
    entry.grid(row=i, column=matrix_size*2+1, padx=2, pady=2)
    entry.insert(0, str(default_b[i])) # Inserting default value
    b_entries.append(entry)

# Result Frame
result_frame = tk.Frame(root, bg="#f0f0f0")
result_frame.pack(pady=10)

# Solution labels
x_labels = []
for i in range(matrix_size):
    label = tk.Label(result_frame, text=f"x{i+1}:", width=3, bg="#f0f0f0")
    label.grid(row=i, column=0, padx=2, pady=2)
    x_result = tk.Label(result_frame, text="", width=10, bg="white", relief="sunken")
    x_result.grid(row=i, column=1, padx=2, pady=2)
    x_labels.append(x_result)

# Calculate button
calculate_button = tk.Button(root, text="Вычислить", command=calculate, bg="#4CAF50", fg="white")
calculate_button.pack(pady=10)

# Other Results
determinant_label_txt = tk.Label(root, text="Определитель:", bg="#f0f0f0")
determinant_label_txt.pack()
determinant_label = tk.Label(root, text="", bg="white", relief="sunken", width=20)
determinant_label.pack()

condition_number_label_txt = tk.Label(root, text="Число обусловленности:", bg="#f0f0f0")
condition_number_label_txt.pack()
condition_number_label = tk.Label(root, text="", bg="white", relief="sunken", width=20)
condition_number_label.pack()

root.mainloop()
