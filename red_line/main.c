#include <GL/glut.h>

void init(void) {
	glClearColor(1.0, 1.0, 1.0, 0.0); // Set clear color to white
	glMatrixMode(GL_PROJECTION); // Set projection parameters
	gluOrtho2D(0.0, 200.0, 0.0, 150.0);
}

void drawLine(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor(1.0, 0.0, 0.0); // Set line color to red
	glBegin(GL_LINES);
	glVertex2i(180, 15);
	glVertex2i(10, 145);
	glEnd();
	glFlush();
}

void myDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 0.0, 0.0); // Red color
	glBegin(GL_POLYGON);
	glVertex2i(50, 50);
	glVertex2i(50, 50);
	glVertex2i(150, 100);
	glVertex2i(150, 50);
}

int main()
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_)

}
