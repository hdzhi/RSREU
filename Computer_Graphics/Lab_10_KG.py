import tkinter as tk
from tkinter import ttk, messagebox
import math


class RotationApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Матрица поворота вокруг точки")

        self.create_widgets()

    def create_widgets(self):
        input_frame = ttk.LabelFrame(self.root, text="Параметры преобразования")
        input_frame.pack(padx=10, pady=10, fill="x")

        ttk.Label(input_frame, text="Центр поворота: А(a, b)").grid(row=0,
                                                                    column=0, sticky="w")
        ttk.Label(input_frame, text="a:").grid(row=0, column=1)
        self.a_entery = ttk.Entry(input_frame, width=10)
        self.a_entery.grid(row=0, column=2)
        ttk.Label(input_frame, text="b:").grid(row=0, column=3)
        self.b_entery = ttk.Entry(input_frame, width=10)
        self.b_entery.grid(row=0, column=4)

        ttk.Label(input_frame, text="Угол поворота (в градусах):").grid(row=1,
                                                                        column=0, sticky="w")
        self.angle_entery = ttk.Entry(input_frame, width=10)
        self.angle_entery.grid(row=1, column=2)

        ttk.Label(input_frame, text="Исходная точка (x, y):").grid(row=2,
                                                                   column=0, sticky="w")
        ttk.Label(input_frame, text="x:").grid(row=2, column=1)
        self.x_entery = ttk.Entry(input_frame, width=10)
        self.x_entery.grid(row=2, column=2)
        ttk.Label(input_frame, text="y:").grid(row=2, column=3)
        self.y_entery = ttk.Entry(input_frame, width=10)
        self.y_entery.grid(row=2, column=4)

        ttk.Button(input_frame, text="Вычислить", command=self.calculate).grid(
            row=3, column=0, columnspan=5, pady=5
        )

        matrix_frame = ttk.LabelFrame(self.root, text="Матрицы преобразования")
        matrix_frame.pack(padx=10, pady=10, fill="both", expand=True)

        self.matrix_text = tk.Text(matrix_frame, height=15, width=60)
        self.matrix_text.pack(padx=10, pady=5)

        self.result_label = ttk.Label(self.root, text="")
        self.result_label.pack(pady=5)


    def multiply_matrix(self, mat1, mat2):
        result = [[0 for _ in range(3)] for _ in range(3)]
        for i in range(3):
            for j in range(3):
                for k in range(3):
                    result[i][j] += mat1[i][k] * mat2[k][j]
        return result


    def multiply_matrix_vector(self, mat, vec):
        result = [0, 0, 0]
        for i in range(3):
            for j in range(3):
                result[i] += mat[i][j] * vec[j]
        return result


    def calculate(self):
        try:
            a = float(self.a_entery.get())
            b = float(self.b_entery.get())
            angle_deg = float(self.angle_entery.get())
            x = float(self.x_entery.get())
            y = float(self.y_entery.get())

            angle_rad = math.radians(angle_deg)
            cos_phi = math.cos(angle_rad)
            sin_phi = math.sin(angle_rad)

            T_minus_A = [
                [1, 0, 0],
                [0, 1, 0],
                [-a, -b, 1]
            ]

            R_phi = [
                [cos_phi, -sin_phi, 0],
                [sin_phi, cos_phi, 0],
                [0, 0, 1]
            ]

            T_A = [
                [1, 0, 0],
                [0, 1, 0],
                [a, b, 1]
            ]

            temp = self.multiply_matrix(T_minus_A, R_phi)
            final_matrix = self.multiply_matrix(temp, T_A)

            point = [x, y, 1]
            trans_point = self.multiply_matrix_vector(final_matrix, point)

            self.matrix_text.delete(1.0, tk.END)
            self.matrix_text.insert(tk.END, "Матрица переноса T_{-A}:\n")
            self.matrix_text.insert(tk.END, self.matrix_to_str(T_minus_A) + "\n\n")

            self.matrix_text.insert(tk.END, "Матрица поворота R_φ:\n")
            self.matrix_text.insert(tk.END, self.matrix_to_str(R_phi) + "\n\n")

            self.matrix_text.insert(tk.END, "Матрица переноса T_A:\n")
            self.matrix_text.insert(tk.END, self.matrix_to_str(T_A) + "\n\n")

            self.matrix_text.insert(tk.END, "Итоговая матрица преобразования:\n")
            self.matrix_text.insert(tk.END, self.matrix_to_str(final_matrix) + "\n")

            self.result_label.config(text=f"Преобразованная точка: ({trans_point[0]:.2f}, "
                                          f"{trans_point[1]:.2f})")

        except ValueError:
            messagebox.showerror("Ошибка", "Пожалуйста, введите корректные числовые значения")


    def matrix_to_str(self, matrix):
        return "\n".join([" ".join([f"{elem:8.4f}" for elem in row]) for row in matrix])


if __name__ == "__main__":
    root = tk.Tk()
    app = RotationApp(root)
    root.mainloop()