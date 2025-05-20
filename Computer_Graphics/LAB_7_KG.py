import tkinter as tk
from tkinter import filedialog, ttk
from PIL import Image, ImageTk, ImageEnhance, ImageFilter
import os


class ModernImageEditor:
    def __init__(self, root):
        self.root = root
        self.root.title("Modern Image Editor")
        self.root.geometry("1100x750")
        self.root.configure(bg='#2d2d2d')

        # Установка стиля для ttk
        self.style = ttk.Style()
        self.style.theme_use('clam')

        # Настройка цветов
        self.bg_color = '#2d2d2d'
        self.panel_color = '#3d3d3d'
        self.accent_color = '#4a6d7c'
        self.text_color = '#ffffff'
        self.slider_color = '#5a8ca8'

        # Конфигурация стилей
        self.style.configure('TFrame', background=self.bg_color)
        self.style.configure('TLabel', background=self.panel_color, foreground=self.text_color)
        self.style.configure('TButton', background=self.accent_color, foreground=self.text_color,
                             borderwidth=1, font=('Segoe UI', 10))
        self.style.map('TButton',
                       background=[('active', '#5a8ca8'), ('pressed', '#3a5d6c')])
        self.style.configure('TScale', background=self.panel_color, troughcolor='#4d4d4d',
                             foreground=self.text_color)

        self.image = None
        self.original_image = None
        self.display_image = None
        self.filename = None

        self.create_widgets()

    def create_widgets(self):
        # Верхняя панель с кнопками
        self.top_panel = ttk.Frame(self.root, padding=10)
        self.top_panel.pack(side=tk.TOP, fill=tk.X)

        # Кнопки с иконками (используем эмодзи как временные иконки)
        self.open_btn = ttk.Button(self.top_panel, text="📁 Открыть", command=self.open_image)
        self.open_btn.pack(side=tk.LEFT, padx=5)

        self.save_btn = ttk.Button(self.top_panel, text="💾 Сохранить", command=self.save_image)
        self.save_btn.pack(side=tk.LEFT, padx=5)

        # Разделитель
        ttk.Separator(self.top_panel, orient=tk.VERTICAL).pack(side=tk.LEFT, padx=10, fill=tk.Y)

        # Кнопка сброса
        self.reset_btn = ttk.Button(self.top_panel, text="🔄 Сбросить", command=self.reset_image)
        self.reset_btn.pack(side=tk.LEFT, padx=5)

        # Основная область
        self.main_panel = ttk.Frame(self.root)
        self.main_panel.pack(fill=tk.BOTH, expand=True)

        # Панель управления справа
        self.control_panel = ttk.Frame(self.main_panel, width=250, style='TFrame')
        self.control_panel.pack(side=tk.RIGHT, fill=tk.Y, padx=5, pady=5)

        # Заголовок панели управления
        controls_title = ttk.Label(self.control_panel, text="Настройки изображения",
                                   font=('Segoe UI', 11, 'bold'), style='TLabel')
        controls_title.pack(pady=(10, 15), fill=tk.X)

        # Создаем вкладки
        self.tab_control = ttk.Notebook(self.control_panel)
        self.tab_control.pack(fill=tk.BOTH, expand=True, padx=5, pady=5)

        # Вкладка "Основные"
        self.basic_tab = ttk.Frame(self.tab_control)
        self.tab_control.add(self.basic_tab, text="Основные")

        # Яркость
        self.create_slider_control(self.basic_tab, "Яркость", "brightness", 0, 2, 1)

        # Контрастность
        self.create_slider_control(self.basic_tab, "Контрастность", "contrast", 0, 2, 1)

        # Насыщенность
        self.create_slider_control(self.basic_tab, "Насыщенность", "saturation", 0, 2, 1)

        # Резкость
        self.create_slider_control(self.basic_tab, "Резкость", "sharpness", 0, 2, 1)

        # Область отображения изображения
        self.image_frame = ttk.Frame(self.main_panel)
        self.image_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True, padx=5, pady=5)

        # Холст с прокруткой
        self.canvas_container = ttk.Frame(self.image_frame)
        self.canvas_container.pack(fill=tk.BOTH, expand=True)

        self.canvas = tk.Canvas(self.canvas_container, bg='#3d3d3d', highlightthickness=0)
        self.canvas.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)

        # Полоса прокрутки
        self.scroll_y = ttk.Scrollbar(self.canvas_container, orient=tk.VERTICAL, command=self.canvas.yview)
        self.scroll_y.pack(side=tk.RIGHT, fill=tk.Y)
        self.scroll_x = ttk.Scrollbar(self.image_frame, orient=tk.HORIZONTAL, command=self.canvas.xview)
        self.scroll_x.pack(side=tk.BOTTOM, fill=tk.X)

        self.canvas.configure(yscrollcommand=self.scroll_y.set, xscrollcommand=self.scroll_x.set)
        self.canvas.bind('<Configure>', lambda e: self.canvas.configure(scrollregion=self.canvas.bbox("all")))

        # Статус бар
        self.status_bar = ttk.Frame(self.root, height=25)
        self.status_bar.pack(side=tk.BOTTOM, fill=tk.X)
        self.status_label = ttk.Label(self.status_bar, text="Готов к работе", relief=tk.SUNKEN)
        self.status_label.pack(fill=tk.X)

    def create_slider_control(self, parent, label_text, var_name, from_, to, default):
        """Создает стилизованный элемент управления с ползунком"""
        frame = ttk.Frame(parent)
        frame.pack(fill=tk.X, padx=5, pady=8)

        label = ttk.Label(frame, text=label_text, font=('Segoe UI', 9))
        label.pack(anchor=tk.W)

        slider_frame = ttk.Frame(frame)
        slider_frame.pack(fill=tk.X)

        # Ползунок
        slider = ttk.Scale(slider_frame, from_=from_, to=to, value=default,
                           command=self.update_image)
        slider.pack(fill=tk.X, expand=True)

        # Значение
        value_label = ttk.Label(slider_frame, text=str(default), width=4)
        value_label.pack(side=tk.RIGHT, padx=(5, 0))

        # Привязка изменения значения ползунка к обновлению метки
        slider.bind("<Motion>", lambda e, lbl=value_label: lbl.config(text=f"{slider.get():.1f}"))

        # Сохраняем ссылки на элементы
        setattr(self, f"{var_name}_slider", slider)
        setattr(self, f"{var_name}_value", value_label)

    def open_image(self):
        filetypes = [("Изображения", "*.jpg *.jpeg *.png *.bmp *.gif")]
        self.filename = filedialog.askopenfilename(title="Открыть изображение", filetypes=filetypes)

        if self.filename:
            try:
                self.image = Image.open(self.filename)
                self.original_image = self.image.copy()

                # Обновляем статус бар
                self.status_label.config(
                    text=f"Загружено: {os.path.basename(self.filename)} | Размер: {self.image.width}x{self.image.height}")

                # Масштабирование изображения для отображения
                self.display_image = self.resize_image(self.image)
                self.update_canvas()
            except Exception as e:
                self.status_label.config(text=f"Ошибка: {str(e)}")

    def resize_image(self, image):
        # Получаем размеры доступной области
        canvas_width = self.canvas.winfo_width() - 20
        canvas_height = self.canvas.winfo_height() - 20

        # Если холст еще не создан, используем стандартные размеры
        if canvas_width <= 1 or canvas_height <= 1:
            canvas_width = 800
            canvas_height = 600

        # Масштабируем изображение с сохранением пропорций
        img_width, img_height = image.size
        ratio = min(canvas_width / img_width, canvas_height / img_height)
        new_size = (int(img_width * ratio), int(img_height * ratio))
        return image.resize(new_size, Image.Resampling.LANCZOS)

    def update_canvas(self):
        if self.display_image:
            self.canvas.delete("all")
            tk_image = ImageTk.PhotoImage(self.display_image)

            # Сохраняем ссылку, чтобы изображение не удалилось сборщиком мусора
            self.canvas.image = tk_image

            # Создаем изображение в центре холста
            img_width = tk_image.width()
            img_height = tk_image.height()

            self.canvas.create_image(
                self.canvas.winfo_width() // 2,
                self.canvas.winfo_height() // 2,
                image=tk_image,
                anchor=tk.CENTER
            )

            # Обновляем область прокрутки
            self.canvas.configure(scrollregion=(
                0, 0,
                max(tk_image.width(), self.canvas.winfo_width()),
                max(tk_image.height(), self.canvas.winfo_height())
            ))

    def update_image(self, event=None):
        if self.image:
            try:
                # Создаем копию оригинального изображения для редактирования
                edited_image = self.original_image.copy()

                # Яркость
                brightness = self.brightness_slider.get()
                enhancer = ImageEnhance.Brightness(edited_image)
                edited_image = enhancer.enhance(brightness)

                # Контрастность
                contrast = self.contrast_slider.get()
                enhancer = ImageEnhance.Contrast(edited_image)
                edited_image = enhancer.enhance(contrast)

                # Насыщенность
                saturation = self.saturation_slider.get()
                enhancer = ImageEnhance.Color(edited_image)
                edited_image = enhancer.enhance(saturation)

                # Резкость
                sharpness = self.sharpness_slider.get()
                enhancer = ImageEnhance.Sharpness(edited_image)
                edited_image = enhancer.enhance(sharpness)

                self.image = edited_image
                self.display_image = self.resize_image(self.image)
                self.update_canvas()

                # Обновляем статус бар
                if self.filename:
                    self.status_label.config(
                        text=f"Редактирование: {os.path.basename(self.filename)} | Яркость: {brightness:.1f} | Контраст: {contrast:.1f}")
            except Exception as e:
                self.status_label.config(text=f"Ошибка при обработке: {str(e)}")

    def reset_image(self):
        if self.original_image:
            self.brightness_slider.set(1)
            self.contrast_slider.set(1)
            self.saturation_slider.set(1)
            self.sharpness_slider.set(1)
            self.image = self.original_image.copy()
            self.display_image = self.resize_image(self.image)
            self.update_canvas()
            self.status_label.config(text=f"Изображение сброшено: {os.path.basename(self.filename)}")

    def save_image(self):
        if self.image:
            filetypes = [
                ("JPEG files", "*.jpg;*.jpeg"),
                ("PNG files", "*.png"),
                ("BMP files", "*.bmp"),
                ("All files", "*.*")
            ]
            filename = filedialog.asksaveasfilename(
                title="Сохранить изображение как",
                filetypes=filetypes,
                defaultextension=".jpg"
            )

            if filename:
                try:
                    # Определяем формат из расширения файла
                    ext = os.path.splitext(filename)[1].lower()
                    if ext in ('.jpg', '.jpeg'):
                        self.image.save(filename, "JPEG", quality=95)
                    elif ext == '.png':
                        self.image.save(filename, "PNG")
                    elif ext == '.bmp':
                        self.image.save(filename, "BMP")
                    else:
                        self.image.save(filename + ".jpg", "JPEG", quality=95)

                    self.status_label.config(text=f"Изображение сохранено как {os.path.basename(filename)}")
                except Exception as e:
                    self.status_label.config(text=f"Ошибка при сохранении: {str(e)}")


if __name__ == "__main__":
    root = tk.Tk()

    # Установка иконки (если есть)
    try:
        root.iconbitmap(default='icon.ico')
    except:
        pass

    app = ModernImageEditor(root)
    root.mainloop()