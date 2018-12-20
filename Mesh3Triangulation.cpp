#define CGAL_USE_BASIC_VIEWER
#define QT_NO_KEYWORDS
#define GL_SILENCE_DEPRECATION
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
#include "Mesh3Triangulation.h"
#include <CGAL/draw_triangulation_3.h>
#include <cmath>

#include <QPushButton>

// To avoid verbose function and named parameters call
using namespace CGAL::parameters;

Mesh3Triangulation::Mesh3Triangulation(const char* filename) :
success(false)
{
    CGAL::Image_3 image;
    std::cerr << "reading..." << std::endl;
    if(!image.read(filename)){
        std::cerr << "Error: Cannot read file " <<  filename << std::endl;
        return;
    }

    Mesh_domain domain = Mesh_domain::create_labeled_image_mesh_domain(image);
    // Mesh criteria
    Mesh_criteria criteria(facet_angle=30, facet_size=6, facet_distance=4,
                            cell_radius_edge_ratio=3, cell_size=8);
    std::cerr << "making mesh..." << std::endl;
    c3t3 = CGAL::make_mesh_3<C3t3>(domain, criteria);
    std::cerr << "done!" << std::endl;

    success = true;
}

Mesh3Triangulation::operator bool() const
{
    return success;
}

void Mesh3Triangulation::draw()
{
	glLineWidth(1.0f);
	glColor4f(0.5f, 0.0f, 0.0f, 0.5f);

    // Completely slow implementation!!!
    Tr& tr = c3t3.triangulation();
    for (Tr::Finite_edges_iterator it = tr.finite_edges_begin(); it != tr.finite_edges_end() ; it++ ) {


        Point_3 p1 = Point_3(it->first->vertex((it->second + 1) % 3)->point());
        Point_3 p2 = Point_3(it->first->vertex((it->second + 2) % 3)->point());

        // All hacky just to make it work

        if (abs(p2.x()) + abs(p2.y()) + abs(p2.z()) <= 0.05f
            || abs(p1.x()) + abs(p1.y()) + abs(p1.z()) <= 0.05f) {
            continue;
        }

        glBegin(GL_LINES);
        glVertex3f(p1.x() / 100.0f, p1.y() / 100.0f, p1.z() / 100.0f);
        glVertex3f(p2.x() / 100.0f, p2.y() / 100.0f, p2.z() / 100.0f);
        glEnd();

    }

}

QWidget* Mesh3Triangulation::createVisualisationWindow(QWidget* parent)
{
    using namespace CGAL;
    return new SimpleTriangulation3ViewerQt<Tr, DefaultColorFunctorT3>(parent, c3t3.triangulation());
}
