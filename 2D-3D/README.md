# OpenGL Texture Mapping Assignment

This project demonstrates the implementation of **Texture Mapping** on a 3D object (a cube) using C++ and Legacy OpenGL. It was created as part of a computer graphics assignment to showcase the loading, binding, and rendering of 2D textures onto 3D geometry.

## Features
* **Texture Loading:** Parses standard image files (`.jpg`, `.png`) into raw pixel data using the `stb_image` library.
* **OpenGL Rendering:** Maps the loaded texture coordinates (UVs) to the 3D vertex coordinates of a cube.
* **Memory Management:** Handles the transfer of pixel data from CPU RAM to GPU VRAM and properly frees resources.
* **Static View:** Displays the cube at a fixed 3D isometric angle to clearly show the texturing on three faces simultaneously.

## Dependencies
To build and run this project, you need the following:
* **C++ Compiler** (Visual Studio, GCC, or Clang)
* **GLFW 3** (Windowing and Input library)
* **stb_image.h** (Single-header image loading library, included in source)

## Project Structure
* `main.cpp` - The main source code containing the OpenGL rendering loop and logic.
* `stb_image.h` - Header-only library used to load images.
* `container2.jpeg` - The sample image used for the texture.
* `.gitignore` - Configuration to exclude build artifacts from version control.

## How to Build and Run

### Visual Studio (Windows)
1.  Open your project solution.
2.  Ensure `GLFW` is correctly linked in your project settings:
    * **Include Directories:** Path to `glfw/include`
    * **Library Directories:** Path to `glfw/lib`
    * **Input Linker:** `glfw3.lib`, `opengl32.lib`
3.  Place `container2.jpeg` in the same directory as your source code (or where the executable is built).
4.  Build and Run (Ctrl + F5).

### Command Line (g++)
If you are compiling manually via terminal:
```bash
g++ main.cpp -o assignment1 -lglfw3 -lopengl32 -lgdi32
./assignment1
```

## Usage

When the program starts, a window will open displaying the textured cube.

  * The view is currently locked to a specific angle to demonstrate the mapping on top, front, and side faces.
  * **To Enable Rotation:** Open `main.cpp`, comment out the `glLoadIdentity()` line, and uncomment the `glRotatef` line inside the loop.

