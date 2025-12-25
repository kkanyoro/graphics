#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

// --- COLOR VARIABLES ---
// Start with Black
float r = 0.0f;
float g = 0.0f;
float b = 0.0f;

// --- INPUT HANDLING ---
void processInput(GLFWwindow* window) {
    float changeSpeed = 0.005f; // color change speed

    // Check if SHIFT is held down to decrease values
    int stateShift = glfwGetKey(window, GLFW_KEY_LEFT_SHIFT);

    // RED CONTROL
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        if (stateShift == GLFW_PRESS) r -= changeSpeed; // Shift+R = Decrease
        else                          r += changeSpeed; // R       = Increase
    }

    // GREEN CONTROL
    if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) {
        if (stateShift == GLFW_PRESS) g -= changeSpeed;
        else                          g += changeSpeed;
    }

    // --- BLUE CONTROL ---
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        if (stateShift == GLFW_PRESS) b -= changeSpeed;
        else                          b += changeSpeed;
    }

    // Keep values between 0.0 and 1.0
    if (r > 1.0f) r = 1.0f; if (r < 0.0f) r = 0.0f;
    if (g > 1.0f) g = 1.0f; if (g < 0.0f) g = 0.0f;
    if (b > 1.0f) b = 1.0f; if (b < 0.0f) b = 0.0f;

    // PRINT TO CONSOLE
    // Calculate CMY for display
    float c = 1.0f - r;
    float m = 1.0f - g;
    float y = 1.0f - b;

    // Carriage return (\r) overwrites the same line
    printf("\rRGB(%.2f, %.2f, %.2f)  -->  CMY(%.2f, %.2f, %.2f)   ", r, g, b, c, m, y);
}

int main(void) {
    GLFWwindow* window;

    if (!glfwInit()) return -1;

    window = glfwCreateWindow(800, 400, "Q2: RGB to CMY Converter", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable V-Sync

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -1.0, 1.0, -1.0, 1.0); // Make the window 4 units wide
    glMatrixMode(GL_MODELVIEW);

    while (!glfwWindowShouldClose(window)) {
        // Clear screen to Dark Grey
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);

        // CALCULATE CMY: inverse of RGB
        float c = 1.0f - r;
        float m = 1.0f - g;
        float y = 1.0f - b;

        // DRAW LEFT SQUARE (RGB)
        glLoadIdentity();
        glTranslatef(-1.0f, 0.0f, 0.0f); // Move Left

        glColor3f(r, g, b); // Set Color to user input
        glBegin(GL_QUADS);
        glVertex2f(-0.8f, -0.8f);
        glVertex2f(0.8f, -0.8f);
        glVertex2f(0.8f, 0.8f);
        glVertex2f(-0.8f, 0.8f);
        glEnd();

        // DRAW RIGHT SQUARE (CMY)
        glLoadIdentity();
        glTranslatef(1.0f, 0.0f, 0.0f); // Move Right

        glColor3f(c, m, y); // Set Color to calculated CMY
        glBegin(GL_QUADS);
        glVertex2f(-0.8f, -0.8f);
        glVertex2f(0.8f, -0.8f);
        glVertex2f(0.8f, 0.8f);
        glVertex2f(-0.8f, 0.8f);
        glEnd();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}