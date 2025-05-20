import tkinter as tk
from tkinter import Canvas
import random
from PIL import Image, ImageTk, ImageDraw


class CoralFractal:
    def __init__(self, master):
        self.master = master
        master.title("Генератор фрактала Коралл")

        # Диапазон значений для точек
        self.MIN_X = -6
        self.MAX_X = 6
        self.MIN_Y = 0
        self.MAX_Y = 10

        # Количество точек для отрисовки
        self.POINT_NUMBER = 200000

        # Вероятности использования различных преобразований
        self.PROBABILITY = [0.40, 0.15, 0.45]

        # Матрица коэффициентов для Coral фрактала
        self.FUNC_COEF = [
            # a          b           c           d          e          f
            [0.307692, -0.531469, -0.461538, -0.293706, 5.401953, 8.655175],  # 1-я функция
            [0.307692, -0.076923, 0.153846, -0.447552, -1.295248, 4.152990],  # 2-я функция
            [0.000000, 0.545455, 0.692308, -0.195804, -4.893637, 7.269794]  # 3-я функция
        ]

        # Создаем холст
        self.width = 800
        self.height = 600
        self.canvas = Canvas(master, width=self.width, height=self.height, bg='black')
        self.canvas.pack(fill=tk.BOTH, expand=True)

        # Создаем изображение для рисования
        self.image = Image.new("RGB", (self.width, self.height), "black")
        self.draw = ImageDraw.Draw(self.image)

        # Запускаем отрисовку
        self.draw_coral()

        # Привязываем изменение размера окна
        master.bind("<Configure>", self.on_resize)

    def on_resize(self, event):
        # Обновляем размеры при изменении окна
        if event.widget == self.master:
            self.width = event.width
            self.height = event.height
            self.canvas.config(width=self.width, height=self.height)
            self.redraw()

    def redraw(self):
        # Перерисовываем фрактал при изменении размера
        self.image = Image.new("RGB", (self.width, self.height), "black")
        self.draw = ImageDraw.Draw(self.image)
        self.draw_coral()

    def draw_coral(self):
        # Масштабирующие коэффициенты
        scale_x = self.width / (self.MAX_X - self.MIN_X)
        scale_y = self.height / (self.MAX_Y - self.MIN_Y)

        xtemp, ytemp = 0, 0
        coral_color = (255, 127, 80)  # Coral цвет в RGB

        for _ in range(self.POINT_NUMBER):
            # Выбор преобразования
            num = random.random()
            numF = 0
            for j in range(3):
                num -= self.PROBABILITY[j]
                if num <= 0:
                    numF = j
                    break

            # Вычисление новых координат
            coef = self.FUNC_COEF[numF]
            x = coef[0] * xtemp + coef[1] * ytemp + coef[4]
            y = coef[2] * xtemp + coef[3] * ytemp + coef[5]

            xtemp, ytemp = x, y

            # Преобразование координат в пиксели
            px = int(xtemp * scale_x + self.width / 2)
            py = int(ytemp * scale_y)

            # Отрисовка точки (только если попадает в границы изображения)
            if 0 <= px < self.width and 0 <= py < self.height:
                self.draw.point((px, py), fill=coral_color)

        # Отображаем изображение на холсте
        self.photo = ImageTk.PhotoImage(self.image)
        self.canvas.create_image(0, 0, image=self.photo, anchor=tk.NW)


def main():
    root = tk.Tk()
    root.geometry("800x600")
    app = CoralFractal(root)
    root.mainloop()


if __name__ == "__main__":
    main()