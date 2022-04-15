#include <windows.h>
#include <math.h>
#include <gl/gl.h>
#include <gl/glut.h> // (or others, depending on the system in use)

#define		PI	3.1415926

int			Width = 800;
int			Height = 800;

float		sun_radius = 50.0;
float		earth_radius = 15.0;
float		moon_radius = 5.0;

float		earthRotation = 0.0, moonRotation = 0.0;

float		earth_rotation_speed = 0.2;
float		moon_rotation_speed = 2;

void init(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1.0 * Width / 2.0, Width / 2.0, -1.0 * Height / 2.0, Height / 2.0);
}

void Draw_Circle(float c_radius) {
	float	delta;
	int		num = 36;

	delta = 2 * PI / num;
	glBegin(GL_POLYGON);
	for (int i = 0; i < num; i++)
		glVertex2f(c_radius * cos(delta * i), c_radius * sin(delta * i));
	glEnd();
}

void RenderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 0.0); // Set display-window color to black.

	earthRotation += earth_rotation_speed;
	moonRotation += moon_rotation_speed;

	// 태양 : 빨간색의 구 
	glPushMatrix();
	glColor3f(1.0, 0.0, 0.0);
	Draw_Circle(sun_radius);
	glRotatef(earthRotation, 0.0, 0.0, 1.0);

	// 지구 : 초록색의 구
	glTranslatef(300.0, 0.0, 0.0);
	glColor3f(0.0, 1.0, 0.0);
	Draw_Circle(earth_radius);
	glRotatef(moonRotation, 0.0, 0.0, 1.0);

	// 달   : 노랑색의 구 
	glTranslatef(30.0, 0.0, 0.0);
	glColor3f(1.0, 1.0, 0.0);
	Draw_Circle(moon_radius);

	glPopMatrix();

	glutSwapBuffers();
	glFlush();
}


void main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(Width, Height);
	glutCreateWindow("20172300 박주환 Solar System");
	init();
	glutDisplayFunc(RenderScene);
	glutIdleFunc(RenderScene);
	glutMainLoop();
}