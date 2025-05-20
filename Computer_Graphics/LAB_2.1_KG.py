import tkinter as tk
from tkinter import filedialog
from PIL import Image, ImageTk


class BMPImageViewer:
    def __init__(self, master):
        self.master = master
        master.title("BMP Image Viewer")

        self.image_path = None
        self.image = None
        self.photo = None
        self.scale_factor = 1.0

        self.canvas = tk.Canvas(master, width=400, height=300, bg='#d2d4c8')
        self.canvas.pack()

        self.create_menu()

    def create_menu(self):
        self.menubar = tk.Menu(self.master, bg='#b7b7a4', fg='black')

        self.filemenu = tk.Menu(self.menubar, tearoff=0, bg='#b7b7a4', fg='black')
        self.filemenu.add_command(label="Open", command=self.load_image)
        self.filemenu.add_command(label="Clear", command=self.clear_image)
        self.filemenu.add_separator()
        self.filemenu.add_command(label="Exit", command=self.master.quit)
        self.menubar.add_cascade(label="File", menu=self.filemenu)

        self.scalemenu = tk.Menu(self.menubar, tearoff=0, bg='#b7b7a4', fg='black')
        self.scale_var = tk.IntVar(value=1)

        self.scalemenu.add_radiobutton(label="50%", variable=self.scale_var, value=0, command=lambda: self.scale_image(0.5))
        self.scalemenu.add_radiobutton(label="100%", variable=self.scale_var, value=1, command=lambda: self.scale_image(1.0))
        self.scalemenu.add_radiobutton(label="150%", variable=self.scale_var, value=2, command=lambda: self.scale_image(1.5))
        self.scalemenu.add_radiobutton(label="200%", variable=self.scale_var, value=3, command=lambda: self.scale_image(2.0))
        self.menubar.add_cascade(label="Scale", menu=self.scalemenu, state=tk.DISABLED)

        self.master.config(menu=self.menubar)

    def load_image(self):
        self.image_path = filedialog.askopenfilename(filetypes=[("BMP files", "*.bmp")])
        if self.image_path:
            try:
                self.image = Image.open(self.image_path)
                self.scale_factor = 1.0
                self.scale_var.set(1)
                self.scale_image(self.scale_factor)
                self.menubar.entryconfig("Scale", state=tk.NORMAL)
            except Exception as e:
                print(f"Error loading image: {e}")
                tk.messagebox.showerror("Error", f"Could not load image:\n{e}")

    def clear_image(self):
        self.image_path = None
        self.image = None
        self.photo = None
        self.scale_factor = 1.0
        self.canvas.delete("all")
        self.canvas.config(width=400, height=300)
        self.menubar.entryconfig("Scale", state=tk.DISABLED)

    def scale_image(self, factor):
        if self.image:
            self.scale_factor = factor

            new_width = int(self.image.width * self.scale_factor)
            new_height = int(self.image.height * self.scale_factor)
            resized_image = self.image.resize((new_width, new_height), Image.LANCZOS)
            self.photo = ImageTk.PhotoImage(resized_image)

            self.canvas.delete("all")
            self.canvas.config(width=new_width, height=new_height)
            self.canvas.create_image(0, 0, anchor=tk.NW, image=self.photo)

            self.update_scale_menu()

    def update_scale_menu(self):
        for index, value in enumerate([0.5, 1.0, 1.5, 2.0]):
            if self.scale_factor == value:
                self.scale_var.set(index)


root = tk.Tk()
viewer = BMPImageViewer(root)
root.mainloop()
