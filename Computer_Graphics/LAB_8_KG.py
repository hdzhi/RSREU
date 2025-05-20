import numpy as np
from PIL import Image, ImageTk
import tkinter as tk
from tkinter import filedialog, Scale, Label, Button


def rgb_to_hsl(r, g, b):
    r, g, b = r / 255.0, g / 255.0, b / 255.0
    max_val = max(r, g, b)
    min_val = min(r, g, b)
    l = (max_val + min_val) / 2.0

    if max_val == min_val:
        h = s = 0.0
    else:
        d = max_val - min_val
        s = d / (2.0 - max_val - min_val) if l > 0.5 else d / (max_val + min_val)

        if max_val == r:
            h = (g - b) / d + (6.0 if g < b else 0.0)
        elif max_val == g:
            h = (b - r) / d + 2.0
        else:
            h = (r - g) / d + 4.0
        h /= 6.0

    return h * 360.0, s, l


def hsl_to_rgb(h, s, l):
    h /= 360.0
    if s == 0:
        r = g = b = l
    else:
        q = l * (1 + s) if l < 0.5 else l + s - l * s
        p = 2 * l - q
        r = hue_to_rgb(p, q, h + 1 / 3)
        g = hue_to_rgb(p, q, h)
        b = hue_to_rgb(p, q, h - 1 / 3)
    return int(r * 255), int(g * 255), int(b * 255)


def hue_to_rgb(p, q, t):
    if t < 0:
        t += 1
    if t > 1:
        t -= 1
    if t < 1 / 6:
        return p + (q - p) * 6 * t
    if t < 1 / 2:
        return q
    if t < 2 / 3:
        return p + (q - p) * (2 / 3 - t) * 6
    return p


class HSLAdjuster:
    def __init__(self, root):
        self.root = root
        self.root.title("RGB to HSL Converter")

        # Set initial window size
        self.root.geometry("800x600")
        self.root.minsize(400, 300)

        # Configure grid weights for resizing
        self.root.grid_rowconfigure(1, weight=1)
        self.root.grid_columnconfigure(0, weight=1)

        # Create container frame for controls
        self.controls_frame = tk.Frame(self.root)
        self.controls_frame.grid(row=0, column=0, sticky="ew", padx=5, pady=5)

        # Create container frame for image with scrollbars
        self.image_frame = tk.Frame(self.root)
        self.image_frame.grid(row=1, column=0, sticky="nsew", padx=5, pady=5)

        # Add scrollbars
        self.canvas = tk.Canvas(self.image_frame, bg='gray')
        self.h_scroll = tk.Scrollbar(self.image_frame, orient="horizontal", command=self.canvas.xview)
        self.v_scroll = tk.Scrollbar(self.image_frame, orient="vertical", command=self.canvas.yview)
        self.canvas.configure(xscrollcommand=self.h_scroll.set, yscrollcommand=self.v_scroll.set)

        # Grid layout for scrollable area
        self.canvas.grid(row=0, column=0, sticky="nsew")
        self.v_scroll.grid(row=0, column=1, sticky="ns")
        self.h_scroll.grid(row=1, column=0, sticky="ew")

        self.image_frame.grid_rowconfigure(0, weight=1)
        self.image_frame.grid_columnconfigure(0, weight=1)

        # GUI Elements in controls frame
        self.load_button = Button(self.controls_frame, text="Load Image", command=self.load_image)
        self.load_button.grid(row=0, column=0, padx=5, pady=5)

        self.save_button = Button(self.controls_frame, text="Save Image", command=self.save_image, state=tk.DISABLED)
        self.save_button.grid(row=0, column=1, padx=5, pady=5)

        self.hue_label = Label(self.controls_frame, text="Hue Adjustment (0-360)")
        self.hue_label.grid(row=1, column=0, sticky="w")
        self.hue_scale = Scale(self.controls_frame, from_=0, to=360, orient=tk.HORIZONTAL, command=self.update_image)
        self.hue_scale.set(0)
        self.hue_scale.grid(row=2, column=0, columnspan=2, sticky="ew")

        self.saturation_label = Label(self.controls_frame, text="Saturation Adjustment (0-1)")
        self.saturation_label.grid(row=3, column=0, sticky="w")
        self.saturation_scale = Scale(self.controls_frame, from_=0, to=100, orient=tk.HORIZONTAL,
                                      command=self.update_image)
        self.saturation_scale.set(100)
        self.saturation_scale.grid(row=4, column=0, columnspan=2, sticky="ew")

        self.lightness_label = Label(self.controls_frame, text="Lightness Adjustment (0-1)")
        self.lightness_label.grid(row=5, column=0, sticky="w")
        self.lightness_scale = Scale(self.controls_frame, from_=0, to=100, orient=tk.HORIZONTAL,
                                     command=self.update_image)
        self.lightness_scale.set(50)
        self.lightness_scale.grid(row=6, column=0, columnspan=2, sticky="ew")

        # Image display variables
        self.image = None
        self.original_image = None
        self.display_image = None
        self.image_on_canvas = None
        self.image_id = None

        # Bind window resize event
        self.root.bind("<Configure>", self.on_window_resize)

    def load_image(self):
        file_path = filedialog.askopenfilename()
        if file_path:
            self.original_image = Image.open(file_path)
            self.image = self.original_image.copy()
            self.save_button.config(state=tk.NORMAL)
            self.display_scaled_image()

    def display_scaled_image(self):
        if self.image:
            # Get canvas size (minus scrollbars)
            canvas_width = self.canvas.winfo_width() - 4  # Small padding
            canvas_height = self.canvas.winfo_height() - 4

            # Calculate new size maintaining aspect ratio
            img_width, img_height = self.image.size
            ratio = min(canvas_width / img_width, canvas_height / img_height)
            new_width = int(img_width * ratio)
            new_height = int(img_height * ratio)

            # Resize image
            self.display_image = ImageTk.PhotoImage(
                self.image.resize((new_width, new_height), Image.LANCZOS)
            )

            # Update canvas
            self.canvas.delete("all")
            self.image_id = self.canvas.create_image(
                canvas_width // 2,
                canvas_height // 2,
                anchor=tk.CENTER,
                image=self.display_image
            )

            # Configure scroll region
            self.canvas.config(scrollregion=self.canvas.bbox("all"))

    def on_window_resize(self, event):
        self.display_scaled_image()

    def update_image(self, _=None):
        if self.original_image:
            hue_adj = self.hue_scale.get()
            sat_adj = self.saturation_scale.get() / 100.0
            light_adj = self.lightness_scale.get() / 100.0

            img_array = np.array(self.original_image)
            height, width, _ = img_array.shape
            adjusted_img = np.zeros_like(img_array)

            for y in range(height):
                for x in range(width):
                    r, g, b = img_array[y, x]
                    h, s, l = rgb_to_hsl(r, g, b)

                    # Apply adjustments
                    h = (h + hue_adj) % 360
                    s = min(max(s * sat_adj, 0.0), 1.0)
                    l = min(max(l * light_adj, 0.0), 1.0)

                    r, g, b = hsl_to_rgb(h, s, l)
                    adjusted_img[y, x] = [r, g, b]

            self.image = Image.fromarray(adjusted_img)
            self.display_scaled_image()

    def save_image(self):
        if self.image:
            file_path = filedialog.asksaveasfilename(
                defaultextension=".png",
                filetypes=[("PNG files", "*.png"), ("JPEG files", "*.jpg"), ("All files", "*.*")]
            )
            if file_path:
                self.image.save(file_path)


if __name__ == "__main__":
    root = tk.Tk()
    app = HSLAdjuster(root)
    root.mainloop()