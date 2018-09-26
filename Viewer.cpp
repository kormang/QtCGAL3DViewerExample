#include "Viewer.h"
#include <OpenGL/gl.h>



using namespace std;

void Viewer::draw()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < result.size(); ++i)
	{
		glVertex3f(result[i].x(), result[i].y(), 0);
	}
	glEnd();

	glPointSize(3.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_POINTS);
	for (int i = 0; i < points.size(); ++i)
	{
		glVertex3f(points[i].x(), points[i].y(), 0);
	}
	glEnd();
}

void Viewer::init()
{
	restoreStateFromFile();
}
