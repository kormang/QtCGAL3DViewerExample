#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include "DrawingElements.h"
#include "BSpline.h"
#include "PNtriangle.h"
#include "SubdivisionCurve.h"
#include "Mesh3Triangulation.h"

SurfaceMeshDrawingElement::SurfaceMeshDrawingElement(Surface_mesh* mesh) : mesh(mesh) {}
SurfaceMeshDrawingElement::~SurfaceMeshDrawingElement()
{
    delete mesh;
}

void SurfaceMeshDrawingElement::draw()
{
	glLineWidth(10.0f);
	glColor4f(0.5f, 0.0f, 0.0f, 0.5f);
	BOOST_FOREACH(Surface_mesh::Face_index f, faces(*mesh)) {
		glBegin(GL_LINE_LOOP);
		CGAL::Vertex_around_face_iterator<Surface_mesh> vbegin, vend;
		for (boost::tie(vbegin, vend) = vertices_around_face(mesh->halfedge(f), *mesh);
				vbegin != vend;
				++vbegin) {
			const Point_3& p = mesh->point(*vbegin);
			glVertex3f(p.x(), p.y(), p.z());
		}
		glEnd();
	}
}

BSplineDrawingElement::BSplineDrawingElement(BSpline* bspline): bspline(bspline) {}

BSplineDrawingElement::~BSplineDrawingElement()
{
    delete bspline;
}

void BSplineDrawingElement::draw()
{
    bspline->drawSplineCurve();
}

PNtriangleDrawingElement::PNtriangleDrawingElement(PNtriangle* pntriangle): pntriangle(pntriangle) {}

PNtriangleDrawingElement::~PNtriangleDrawingElement()
{
    delete pntriangle;
}

void PNtriangleDrawingElement::draw()
{
    pntriangle->drawTriangle();
}


SubdivisionCurveDrawingElement::SubdivisionCurveDrawingElement(SubdivisionCurve* subdivisionCurve): subdivisionCurve(subdivisionCurve) {}

SubdivisionCurveDrawingElement::~SubdivisionCurveDrawingElement()
{
    delete subdivisionCurve;
}

void SubdivisionCurveDrawingElement::draw()
{
    subdivisionCurve->drawSubdivisionCurve();
}

Mesh3TriangulationDrawingElement::Mesh3TriangulationDrawingElement(Mesh3Triangulation* mesh3): mesh3(mesh3) {}

Mesh3TriangulationDrawingElement::~Mesh3TriangulationDrawingElement()
{
    delete mesh3;
}

void Mesh3TriangulationDrawingElement::draw()
{
	mesh3->draw();
}
