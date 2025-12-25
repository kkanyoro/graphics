# HLS Colour Experiment

## 1. Project Overview

This program implements an interactive color mixer based on the **HLS (Hue, Lightness, Saturation)** color model. While OpenGL and monitors natively function using RGB (Red, Green, Blue), the HLS model is often more intuitive for human design. This tool allows the user to manipulate color properties perceptually (e.g., "make it brighter" or "make it more vivid") and calculates the corresponding RGB values in real-time.

## 2. Theoretical Concept

The program distinguishes between the machine-ready RGB model and the human-centric HLS model:

* **Hue (H):** The angular position on the color wheel ( to ).
*  = Red,  = Green,  = Blue.

* **Lightness (L):** The perceived brightness ( to ).
* Controls the spectrum from Black  Color  White.

* **Saturation (S):** The intensity or purity of the color ( to ).
* Controls the spectrum from Grey  Vivid Color.

## 3. Features

* **HLS to RGB Algorithm:** Implements the mathematical conversion logic to translate cylindrical HLS coordinates into Cartesian RGB coordinates for rendering.
* **Real-Time Visualization:** A large central viewport updates instantly to reflect the current color settings.
* **Data Feedback:** The console displays the live HLS input values alongside the resulting RGB output, aiding in understanding the relationship between the two models (e.g., observing how reducing Saturation to 0 results in equal R, G, and B values).

## 4. Controls

Users can adjust the three parameters bi-directionally using the keyboard.

| Key           | Action              | Effect                                  |
| ------------- | ------------------- | --------------------------------------- |
| **H**         | Increase Hue        | Spins the color wheel Clockwise         |
| **Shift + H** | Decrease Hue        | Spins the color wheel Counter-Clockwise |
| **L**         | Increase Lightness  | Tints the color towards White           |
| **Shift + L** | Decrease Lightness  | Shades the color towards Black          |
| **S**         | Increase Saturation | Makes the color more vivid              |
| **Shift + S** | Decrease Saturation | Washes the color out towards Grey       |

## 5. Implementation Details

### A. The Conversion Function (`getRGBfromHLS`)

Since OpenGL lacks native HLS support, a custom helper function was implemented.

1. **Normalization:** The Hue input () is normalized to a  range.
2. **Achromatic Check:** If Saturation is , the R, G, and B values are all set equal to Lightness (creating Grey).
3. **Chromatic Calculation:** If Saturation is , the code calculates temporary coefficients (`p` and `q`) based on Lightness, then calculates individual RGB channels by offsetting the Hue angle by  (Red) and  (Blue).

### B. Input Handling

* **Wrapping:** The Hue variable handles circular wrapping—if the user goes above , it resets to , and vice versa.
* **Clamping:** Lightness and Saturation are strictly clamped between  and  to ensure valid mathematical output.