#include "Viewer.h"
#include <OpenGL/gl.h>

using namespace std;

void Viewer::draw()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glPointSize(5.0f);
	glColor4f(0.0f, 0.5f, 0.5f, 0.5f);

	glLineWidth(10.0f);
	BOOST_FOREACH(Surface_mesh::Face_index f, faces(mesh)){
		glBegin(GL_LINE_LOOP);
		CGAL::Vertex_around_face_iterator<Surface_mesh> vbegin, vend;
		for(boost::tie(vbegin, vend) = vertices_around_face(mesh.halfedge(f), mesh);
				vbegin != vend;
				++vbegin){
			const Point_3& p = mesh.point(*vbegin);
			glVertex3f(p.x(), p.y(), p.z());
		}
		glEnd();
	}

	glPointSize(20.0f);
	glColor4f(1.0f, 0.2f, 0.0f, 0.5f);
	glBegin(GL_POINTS);
	for (int i = 0; i < points.size(); ++i)
	{
		glVertex3f(points[i].x(), points[i].y(), points[i].z());
	}
	glEnd();
	glDisable(GL_BLEND);

	glPointSize(10.0f);
	glColor3f(0.0f, 0.5f, 0.5f);
	glBegin(GL_POINTS);
	for (Surface_mesh::Vertex_index i : mesh.vertices())
	{
		const Point_3& p = mesh.point(i);
		glVertex3f(p.x(), p.y(), p.z());
	}
	glEnd();

	glEnable(GL_BLEND);
}

void Viewer::init()
{
	restoreStateFromFile();
}

void Viewer::initializeGL()
{
	QGLViewer::initializeGL();

	this->camera()->setZNearCoefficient(0.0001);
	this->camera()->setZClippingCoefficient(100.0);

	this->camera()->setPosition(qglviewer::Vec(17, 20, 20));
	this->camera()->lookAt(qglviewer::Vec(0, 0, 0));
}
