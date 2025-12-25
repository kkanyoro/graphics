# 3D Room Walkthrough

## 1. Project Overview

This program demonstrates the construction of a 3D architectural environment using OpenGL. It features a furnished room with a door and a window, rendered in a perspective projection. The primary objective is to implement a first-person camera system that allows the user to navigate the space interactively using keyboard and mouse controls.

## 2. Features

* **3D Geometry Construction:** A room built from geometric primitives (`GL_QUADS`), featuring distinct floor, ceiling, and wall sections.
* **Complex Modeling:** Implementation of "tiling" logic to create holes for doors and windows by constructing the wall from multiple sub-panels rather than a single solid plane.
* **First-Person Navigation:** A comprehensive camera system supporting movement (Walking/Strafing) and looking (Yaw/Pitch).
* **Physics & Constraints:**
* Pitch clamping (limiting vertical vision to +/- 85 degrees) to prevent camera flipping.
* Movement speed normalization using V-Sync to ensuring consistent walking speed across different hardware.


* **Aesthetics:** A "furnished wood" and "cream wall" color palette to simulate a realistic interior.

## 3. Controls

The program uses a standard WASD + Mouse control scheme similar to modern First-Person simulations.

| Input           | Action                              |
| --------------- | ----------------------------------- |
| **Mouse**       | Look Around (Up, Down, Left, Right) |
| **W**           | Move Forward                        |
| **S**           | Move Backward                       |
| **A**           | Strafe Left                         |
| **D**           | Strafe Right                        |
| **Up Arrow**    | Look Up (Keyboard alternative)      |
| **Down Arrow**  | Look Down (Keyboard alternative)    |
| **Left Arrow**  | Turn Left (Keyboard alternative)    |
| **Right Arrow** | Turn Right (Keyboard alternative)   |
| **Esc**         | Exit the Program                    |

## 4. Implementation Details

### A. Geometric Modeling

The room is defined by a `ROOM_SIZE` constant (50.0 units).

* **The Shell:** The Floor and Ceiling are large single quads stretched across the X/Z plane.
* **The Door & Window:** Unlike standard 3D modeling software where boolean operations cut holes, raw OpenGL requires constructing walls *around* the empty space.
* *The Door Wall* is constructed of 3 pieces: Left Panel, Right Panel, and Top Header.
* *The Window Wall* is constructed of 4 pieces: Bottom Sill, Top Lintel, Left Side, and Right Side.
* Linear Interpolation is used to calculate the vertices dynamically to ensure the openings remain centered regardless of room size.



### B. Camera System (The Mathematics)

The camera does not physically move; instead, the world transformation is updated relative to the "Eye" position.

* **Movement:** Trigonometry is used to convert the facing angle (`cameraAngle`) into X and Z coordinate shifts:
* `dx = sin(angle) * speed`
* `dz = -cos(angle) * speed`


* **Looking:** The `gluLookAt()` function is driven by spherical coordinates. The target "LookAt" point is calculated every frame based on the user's Yaw and Pitch inputs.

### C. Color Palette

RGB values were tuned to represent materials:

* **Floor:** `(0.55, 0.40, 0.25)` - Medium Brown Wood.
* **Walls:** `(0.96, 0.96, 0.86)` - Cream / Off-White.
* **Door:** `(0.35, 0.20, 0.10)` - Dark Chocolate Brown.
* **Window Glass:** `(0.6, 0.8, 0.9)` - Transparent Blue tint.

---