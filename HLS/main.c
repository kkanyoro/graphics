#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <math.h>

// STATE VARIABLES
float hue = 0.0f;        // 0.0 to 360.0 degrees
float lightness = 0.5f;  // 0.0 (Black) to 1.0 (White)
float saturation = 1.0f; // 0.0 (Grey) to 1.0 (Vivid)

// HLS TO RGB CONVERSION
float hue2rgb(float p, float q, float t) {
    if (t < 0.0f) t += 1.0f;
    if (t > 1.0f) t -= 1.0f;
    if (t < 1.0f / 6.0f) return p + (q - p) * 6.0f * t;
    if (t < 1.0f / 2.0f) return q;
    if (t < 2.0f / 3.0f) return p + (q - p) * (2.0f / 3.0f - t) * 6.0f;
    return p;
}

void getRGBfromHLS(float h, float l, float s, float* r, float* g, float* b) {
    float q, p;
    float h_normalized = h / 360.0f; // Convert 0-360 to 0.0-1.0

    if (s == 0.0f) {
        // Achromatic (Grey)
        *r = *g = *b = l;
    }
    else {
        // Chromatic calculation
        if (l < 0.5f) q = l * (1.0f + s);
        else          q = l + s - l * s;

        p = 2.0f * l - q;

        *r = hue2rgb(p, q, h_normalized + 1.0f / 3.0f);
        *g = hue2rgb(p, q, h_normalized);
        *b = hue2rgb(p, q, h_normalized - 1.0f / 3.0f);
    }
}

// INPUT HANDLING
void processInput(GLFWwindow* window) {
    float changeSpeed = 0.01f;
    float hueSpeed = 1.0f; // Hue moves faster (0-360 scale)

    int stateShift = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);

    // HUE (H)
    if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) {
        if (stateShift == GLFW_PRESS) hue -= hueSpeed;
        else                          hue += hueSpeed;
    }
    // Wrap Hue around 360
    if (hue > 360.0f) hue = 0.0f;
    if (hue < 0.0f)   hue = 360.0f;

    // LIGHTNESS (L)
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        if (stateShift == GLFW_PRESS) lightness -= changeSpeed;
        else                          lightness += changeSpeed;
    }
    // Clamp Lightness
    if (lightness > 1.0f) lightness = 1.0f;
    if (lightness < 0.0f) lightness = 0.0f;

    // SATURATION (S)
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if (stateShift == GLFW_PRESS) saturation -= changeSpeed;
        else                          saturation += changeSpeed;
    }
    // Clamp Saturation
    if (saturation > 1.0f) saturation = 1.0f;
    if (saturation < 0.0f) saturation = 0.0f;
}

int main(void) {
    GLFWwindow* window;

    if (!glfwInit()) return -1;

    window = glfwCreateWindow(800, 600, "Q3: HLS Colour Experiment", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // V-Sync

    // Setup 2D Orthographic view
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Dark Grey Background
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);

        // Convert Current HLS to RGB
        float r, g, b;
        getRGBfromHLS(hue, lightness, saturation, &r, &g, &b);

        // Print to Console
        printf("\rH: %03.1f | L: %.2f | S: %.2f  -->  RGB(%.2f, %.2f, %.2f)   ",
            hue, lightness, saturation, r, g, b);

        // Draw the Color Square
        glLoadIdentity();
        glColor3f(r, g, b);

        glBegin(GL_QUADS);
        glVertex2f(-0.5f, -0.5f);
        glVertex2f(0.5f, -0.5f);
        glVertex2f(0.5f, 0.5f);
        glVertex2f(-0.5f, 0.5f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}