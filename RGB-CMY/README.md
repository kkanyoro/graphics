# RGB to CMY Conversion

## 1. Project Overview

This program is an interactive visualization tool designed to demonstrate the relationship between the **Additive Color Model (RGB)** used in digital displays and the **Subtractive Color Model (CMY)** used in printing. By adjusting the Red, Green, and Blue channels in real-time, the user can observe the mathematical inversion required to generate Cyan, Magenta, and Yellow.

## 2. Theoretical Concept

The program is built upon the principle of color inversion.

* **RGB (Additive):** Starts with black; light is added to create color.
* **CMY (Subtractive):** Starts with white; light is absorbed (subtracted) to create color.

The conversion formula implemented is:


## 3. Features

* **Split-Screen Visualization:**
* **Left Viewport:** Displays the RGB Source color.
* **Right Viewport:** Displays the converted CMY Result color.


* **Real-Time Console Feedback:** The program prints the exact float values for both models to the console (e.g., `RGB(1.0, 0.0, 0.0) --> CMY(0.0, 1.0, 1.0)`), allowing for numerical verification of the theory.
* **Clamping:** Input values are strictly clamped between `0.0` and `1.0` to prevent invalid color data.

## 4. Controls

The user manipulates the additive primary colors (Red, Green, Blue) using the keyboard.

| Key           | Action                   |
| ------------- | ------------------------ |
| **R**         | Increase Red intensity   |
| **Shift + R** | Decrease Red intensity   |
| **G**         | Increase Green intensity |
| **Shift + G** | Decrease Green intensity |
| **B**         | Increase Blue intensity  |
| **Shift + B** | Decrease Blue intensity  |

## 5. Implementation Details

### A. 2D Orthographic Projection

Unlike the 3D room in Question 1, this program utilizes `glOrtho` to create a flat 2D workspace. This ensures the color samples are rendered as perfect squares without perspective distortion.

### B. State Management

Three global float variables (`r`, `g`, `b`) store the current state. Every frame:

1. Input is processed to modify these variables.
2. The "Inverse" variables (`c`, `m`, `y`) are calculated.
3. `glTranslate` is used to position the two squares.
4. `glColor3f` is called with the respective variable sets to render the final result.