# OpenGL Shader Color Transformer

## 1. Overview

This application demonstrates real-time image processing using OpenGL shaders. It generates a procedural texture (a colorful checkerboard) on the CPU, uploads it to the GPU, and renders it onto a 2D quad.

The core feature is the ability to switch between different pixel-processing "modes" (Normal, Inverted, Grayscale) instantly using the keyboard. This showcases how **Fragment Shaders** can manipulate pixel data in parallel on the graphics card.

## 2. Controls

| Key       | Action             | Description                                                   |
| --------- | ------------------ | ------------------------------------------------------------- |
| **`1`**   | **Normal Mode**    | Displays the original RGB texture colors.                     |
| **`2`**   | **Invert Mode**    | Inverts the colors (like a photo negative).                   |
| **`3`**   | **Grayscale Mode** | Converts the image to black & white using weighted luminance. |
| **`ESC`** | **Exit**           | Closes the application window.                                |

## 3. Dependencies

To compile and run this program, you need the following libraries linked:

* **GLFW**: Handles window creation and keyboard input.
* **GLAD**: Loads OpenGL function pointers (Must be initialized before calling OpenGL functions).

## 4. Technical Implementation Details

### A. Texture Generation (The "Fix")

Instead of loading an external image file (like JPG/PNG), the program procedurally generates a 64x64 texture in memory.

**Key Implementation Note:**
The pixel data is allocated on the **Heap** using `malloc`. This prevents stack overflow errors and allows the image dimensions to be variable.

```c
// Dynamic allocation prevents stack overflow
unsigned char* data = (unsigned char*)malloc(width * height * 3);
// ... generate pixels ...
free(data); // Memory is released immediately after uploading to GPU

```

### B. The Fragment Shader (GLSL)

The "magic" happens in the Fragment Shader. It receives a `uniform int mode` variable from the CPU and uses `if/else` logic to determine the final color of every pixel.

* **Mode 1 (Invert):** `1.0 - color`
* Red (1.0, 0.0, 0.0) becomes Cyan (0.0, 1.0, 1.0).


* **Mode 2 (Grayscale):** Weighted Average
* Formula: `0.299*R + 0.587*G + 0.114*B`
* *Why these numbers?* The human eye is more sensitive to Green light than Blue. A simple average `(R+G+B)/3` would look unnatural; this formula matches human perception.



### C. The Render Loop

The application runs a continuous loop until the window is closed:

1. **Process Input:** Checks if keys 1, 2, or 3 are pressed.
2. **Clear Screen:** Resets the background color.
3. **Update Uniforms:** Sends the current `mode` integer to the active shader.
4. **Draw:** Renders the 2 triangles (the Quad) that display the texture.
5. **Swap Buffers:** Updates the display.

## 5. Geometry Data

The shape being drawn is a simple rectangle (Quad) made of two triangles.

* **Coordinates:** Normalized Device Coordinates (NDC) ranging from -1.0 to 1.0.
* **UV Mapping:** Texture coordinates map the bottom-left of the image (0,0) to the bottom-left of the rectangle.

## 6. How to Compile

Assuming you have GCC or Clang setup with the libraries:

```bash
gcc main.c glad.c -o shader_app -lglfw -ldl

```

*(Note: On Windows with Visual Studio, ensure the include/lib directories are linked properly in your project settings).*

---