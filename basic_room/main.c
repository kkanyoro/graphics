#define _CRT_SECURE_NO_WARNINGS

#include <windows.h> 
#include <GLFW/glfw3.h>
#include <GL/glu.h> 
#include <math.h>
#include <stdio.h>
#include <stdbool.h>

// --- CAMERA VARIABLES ---
float cameraX = 0.0f, cameraY = 1.75f, cameraZ = 5.0f;
float cameraAngle = 0.0f;  // Yaw
float cameraPitch = 0.0f;  // Pitch
float moveSpeed = 0.5f;   // Walking Speed
float turnSpeed = 0.03f;   // Keyboard turning speed

// MOUSE VARIABLES
bool firstMouse = true;
float lastX = 400.0f;      // Approximately center of screen
float lastY = 300.0f;
float mouseSensitivity = 0.002f;

// ROOM DIMENSIONS
const float ROOM_SIZE = 30.0f;
const float WALL_HEIGHT = 7.0f;

// MOUSE CALLBACK FUNCTION
// Runs automatically whenever you move the mouse
void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = (float)xpos;
        lastY = (float)ypos;
        firstMouse = false;
    }

    float xoffset = (float)xpos - lastX;
    float yoffset = lastY - (float)ypos; // Reversed: Y coords go from bottom to top
    lastX = (float)xpos;
    lastY = (float)ypos;

    cameraAngle += xoffset * mouseSensitivity;
    cameraPitch += yoffset * mouseSensitivity;

    // Clamp Pitch to stop from flipping over
    if (cameraPitch > 1.5f) cameraPitch = 1.5f;
    if (cameraPitch < -1.5f) cameraPitch = -1.5f;
}

// INPUT HANDLING (Keyboard)
void processInput(GLFWwindow* window) {
    // EXIT
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);

    // MOVING (W/A/S/D)
    float dx = sinf(cameraAngle) * moveSpeed;
    float dz = -cosf(cameraAngle) * moveSpeed;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        cameraX += dx;
        cameraZ += dz;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        cameraX -= dx;
        cameraZ -= dz;
    }
    // Strafe Left (A)
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        cameraX -= cosf(cameraAngle) * moveSpeed;
        cameraZ -= sinf(cameraAngle) * moveSpeed;
    }
    // Strafe Right (D)
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        cameraX += cosf(cameraAngle) * moveSpeed;
        cameraZ += sinf(cameraAngle) * moveSpeed;
    }

    // Arrow keys for turning
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) cameraAngle -= turnSpeed;
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) cameraAngle += turnSpeed;
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) cameraPitch += turnSpeed;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) cameraPitch -= turnSpeed;
}

// DRAWING FUNCTIONS
void drawFloorAndCeiling() {
    // Floor (Brown)
    glColor3f(0.55f, 0.40f, 0.25f);
    glBegin(GL_QUADS);
    glVertex3f(-ROOM_SIZE, 0.0f, -ROOM_SIZE);
    glVertex3f(ROOM_SIZE, 0.0f, -ROOM_SIZE);
    glVertex3f(ROOM_SIZE, 0.0f, ROOM_SIZE);
    glVertex3f(-ROOM_SIZE, 0.0f, ROOM_SIZE);
    glEnd();

    // Ceiling (White)
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
    glVertex3f(-ROOM_SIZE, WALL_HEIGHT, -ROOM_SIZE);
    glVertex3f(ROOM_SIZE, WALL_HEIGHT, -ROOM_SIZE);
    glVertex3f(ROOM_SIZE, WALL_HEIGHT, ROOM_SIZE);
    glVertex3f(-ROOM_SIZE, WALL_HEIGHT, ROOM_SIZE);
    glEnd();
}

void drawSolidWall(float x1, float z1, float x2, float z2) {
    glColor3f(0.96f, 0.96f, 0.86f); // Cream
    glBegin(GL_QUADS);
    glVertex3f(x1, 0.0f, z1);
    glVertex3f(x2, 0.0f, z2);
    glVertex3f(x2, WALL_HEIGHT, z2);
    glVertex3f(x1, WALL_HEIGHT, z1);
    glEnd();
}

void drawWallWithDoor(float x1, float z1, float x2, float z2) {
    float wallLength = sqrtf(powf(x2 - x1, 2.0f) + powf(z2 - z1, 2.0f));

    float doorWidthPercent = 6.0f / wallLength;
    float doorL = 0.5f - (doorWidthPercent / 2.0f);
    float doorR = 0.5f + (doorWidthPercent / 2.0f);
    float doorH = 5.0f;

    float dx = x2 - x1;
    float dz = z2 - z1;

    // Walls (Cream)
    glColor3f(0.96f, 0.96f, 0.86f);
    // Left Piece
    glBegin(GL_QUADS);
    glVertex3f(x1, 0.0f, z1);
    glVertex3f(x1 + dx * doorL, 0.0f, z1 + dz * doorL);
    glVertex3f(x1 + dx * doorL, WALL_HEIGHT, z1 + dz * doorL);
    glVertex3f(x1, WALL_HEIGHT, z1);
    glEnd();

    // Right Piece
    glBegin(GL_QUADS);
    glVertex3f(x1 + dx * doorR, 0.0f, z1 + dz * doorR);
    glVertex3f(x2, 0.0f, z2);
    glVertex3f(x2, WALL_HEIGHT, z2);
    glVertex3f(x1 + dx * doorR, WALL_HEIGHT, z1 + dz * doorR);
    glEnd();

    // Top Piece
    glBegin(GL_QUADS);
    glVertex3f(x1 + dx * doorL, doorH, z1 + dz * doorL);
    glVertex3f(x1 + dx * doorR, doorH, z1 + dz * doorR);
    glVertex3f(x1 + dx * doorR, WALL_HEIGHT, z1 + dz * doorR);
    glVertex3f(x1 + dx * doorL, WALL_HEIGHT, z1 + dz * doorL);
    glEnd();

    // Door (Dark Chocolate Brown)
    glColor3f(0.35f, 0.20f, 0.10f);
    glBegin(GL_QUADS);
    glVertex3f(x1 + dx * doorL, 0.0f, z1 + dz * doorL);
    glVertex3f(x1 + dx * doorR, 0.0f, z1 + dz * doorR);
    glVertex3f(x1 + dx * doorR, doorH, z1 + dz * doorR);
    glVertex3f(x1 + dx * doorL, doorH, z1 + dz * doorL);
    glEnd();
}

void drawWallWithWindow(float x1, float z1, float x2, float z2) {
    float wallLength = sqrtf(powf(x2 - x1, 2.0f) + powf(z2 - z1, 2.0f));
    float winWidthPercent = 12.0f / wallLength;
    float winL = 0.5f - (winWidthPercent / 2.0f);
    float winR = 0.5f + (winWidthPercent / 2.0f);
    float winB = 1.0f;
    float winT = 5.0f;

    float dx = x2 - x1;
    float dz = z2 - z1;

    glColor3f(0.96f, 0.96f, 0.86f); // Cream

    // Bottom
    glBegin(GL_QUADS);
    glVertex3f(x1, 0.0f, z1);
    glVertex3f(x2, 0.0f, z2);
    glVertex3f(x2, winB, z2);
    glVertex3f(x1, winB, z1);
    glEnd();

    // Top
    glBegin(GL_QUADS);
    glVertex3f(x1, winT, z1);
    glVertex3f(x2, winT, z2);
    glVertex3f(x2, WALL_HEIGHT, z2);
    glVertex3f(x1, WALL_HEIGHT, z1);
    glEnd();

    // Left Side
    glBegin(GL_QUADS);
    glVertex3f(x1, winB, z1);
    glVertex3f(x1 + dx * winL, winB, z1 + dz * winL);
    glVertex3f(x1 + dx * winL, winT, z1 + dz * winL);
    glVertex3f(x1, winT, z1);
    glEnd();

    // Right Side
    glBegin(GL_QUADS);
    glVertex3f(x1 + dx * winR, winB, z1 + dz * winR);
    glVertex3f(x2, winB, z2);
    glVertex3f(x2, winT, z2);
    glVertex3f(x1 + dx * winR, winT, z1 + dz * winR);
    glEnd();

    // Window Glass
    glColor3f(0.6f, 0.8f, 0.9f);
    glBegin(GL_QUADS);
    glVertex3f(x1 + dx * winL, winB, z1 + dz * winL);
    glVertex3f(x1 + dx * winR, winB, z1 + dz * winR);
    glVertex3f(x1 + dx * winR, winT, z1 + dz * winR);
    glVertex3f(x1 + dx * winL, winT, z1 + dz * winL);
    glEnd();
}

int main(void) {
    GLFWwindow* window;
    if (!glfwInit()) return -1;

    window = glfwCreateWindow(800, 600, "Q1: 3D Room Walkthrough", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable V-Sync

    // SETUP MOUSE
    // Hide the cursor and lock it to the window
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    // Call the function when mouse moves
    glfwSetCursorPosCallback(window, mouse_callback);


    // Setup 3D Perspective
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        // CLEAR SCREEN
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        // INPUT
        processInput(window);

        // CAMERA (View Transformation)
        float lookX = cameraX + sinf(cameraAngle);
        float lookY = cameraY + tanf(cameraPitch); // Look Up/Down
        float lookZ = cameraZ - cosf(cameraAngle);

        gluLookAt(cameraX, cameraY, cameraZ,  // Eye
            lookX, lookY, lookZ,        // Look At
            0.0f, 1.0f, 0.0f);          // Up

        // DRAW SCENE
        drawFloorAndCeiling();

        // BACK WALL (Door)
        drawWallWithDoor(-ROOM_SIZE, -ROOM_SIZE, ROOM_SIZE, -ROOM_SIZE);

        // FRONT WALL (Solid)
        drawSolidWall(-ROOM_SIZE, ROOM_SIZE, ROOM_SIZE, ROOM_SIZE);

        // LEFT WALL (Window)
        drawWallWithWindow(-ROOM_SIZE, ROOM_SIZE, -ROOM_SIZE, -ROOM_SIZE);

        // RIGHT WALL (Solid)
        drawSolidWall(ROOM_SIZE, -ROOM_SIZE, ROOM_SIZE, ROOM_SIZE);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}