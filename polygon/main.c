#include <GL/glut.h>

void init(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0); // Set display-window color to white.
    glMatrixMode(GL_PROJECTION);      // Set projection parameters.
    gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void drawLine(void) {
    glClear(GL_COLOR_BUFFER_BIT);     // Clear display window.
    glColor3f(1.0, 0.0, 0.0);         // Set line color to red.
    glBegin(GL_LINES);
        glVertex2i(180, 15);          // Specify line-segment geometry.
        glVertex2i(10, 145);
    glEnd();
    glFlush();                        // Process all OpenGL routines as quickly as possible.
}

void mydisplay(){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2i(50, 50);
    glVertex2i(50, 100);
    glVertex2i(150,100);
    glVertex2i(150,50);
    glEnd();
    glFlush();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the display window

    // --- Red Quad ---
    glBegin(GL_QUADS);
        glColor3f(1.0f, 0.0f, 0.0f); // Red
        glVertex2f(20.0f, 10.0f);
        glVertex2f(80.0f, 10.0f);
        glVertex2f(80.0f, 70.0f);
        glVertex2f(20.0f, 70.0f);

    // --- Green Quad ---
        glColor3f(0.0f, 1.0f, 0.0f); // Green
        glVertex2f(30.0f, 20.0f);
        glVertex2f(90.0f, 20.0f);
        glVertex2f(90.0f, 80.0f);
        glVertex2f(30.0f, 80.0f);

    // --- Gray and White Rectangles ---
        glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
        glVertex2f(10.0f, 5.0f);
        glColor3f(1.0f, 1.0f, 1.0f); // White
        glVertex2f(50.0f, 5.0f);
        glColor3f(0.2f, 0.2f, 0.2f); // Dark Gray
        glVertex2f(50.0f, 30.0f);
        glColor3f(1.0f, 1.0f, 1.0f); // White
        glVertex2f(10.0f, 30.0f);
    glEnd();

    // --- Triangles ---
    glBegin(GL_TRIANGLES);
        glColor3f(0.0f, 0.0f, 1.0f); // Blue
        glVertex2f(110.0f, 30.0f);
        glVertex2f(170.0f, 30.0f);
        glVertex2f(140.0f, 80.0f);

        glColor3f(1.0f, 0.0f, 0.0f); // Red
        glVertex2f(120.0f, 40.0f);
        glColor3f(0.0f, 1.0f, 0.0f); // Green
        glVertex2f(180.0f, 40.0f);
        glColor3f(0.0f, 0.0f, 1.0f); // Blue
        glVertex2f(150.0f, 10.0f);
    glEnd();

    // --- Polygon ---
    glBegin(GL_POLYGON);
        glColor3f(1.0f, 1.0f, 0.0f); // Yellow
        glVertex2f(110.0f, 100.0f);
        glVertex2f(130.0f, 100.0f);
        glVertex2f(140.0f, 120.0f);
        glVertex2f(130.0f, 140.0f);
        glVertex2f(110.0f, 140.0f);
        glVertex2f(100.0f, 120.0f);
    glEnd();

    glFlush(); // Render now
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);                           // Initialize GLUT.
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);     // Set display mode.
    glutInitWindowPosition(50, 100);                 // Set top-left display-window position.
    glutInitWindowSize(400, 300);                    // Set display-window width and height.
    glutCreateWindow("An Example OpenGL Program");   // Create display window.
    init();                                          // Execute initialization procedure.
    glutDisplayFunc(display);                       // Send graphics to display window.
    glutMainLoop();                                  // Display everything and wait.
    return 0;
}
