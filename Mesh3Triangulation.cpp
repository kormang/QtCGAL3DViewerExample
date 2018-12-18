#define GL_SILENCE_DEPRECATION
#include <OpenGL/gl.h>
#include "Mesh3Triangulation.h"

// To avoid verbose function and named parameters call
using namespace CGAL::parameters;

Mesh3Triangulation::Mesh3Triangulation(const char* filename) : success(false)
{
    CGAL::Image_3 image;
    if(!image.read(filename)){
        std::cerr << "Error: Cannot read file " <<  filename << std::endl;
        return;
    }

    Mesh_domain domain = Mesh_domain::create_labeled_image_mesh_domain(image);
    // Mesh criteria
    Mesh_criteria criteria(facet_angle=30, facet_size=6, facet_distance=4,
                            cell_radius_edge_ratio=3, cell_size=8);
    c3t3 = CGAL::make_mesh_3<C3t3>(domain, criteria);

    success = true;
}

Mesh3Triangulation::operator bool() const
{
    return success;
}

void Mesh3Triangulation::draw()
{
	glLineWidth(10.0f);
	glColor4f(0.5f, 0.0f, 0.0f, 0.5f);

/*
	BOOST_FOREACH(c3t3::Face_index f, faces(*c3t3)) {
		glBegin(GL_LINE_LOOP);
		CGAL::Vertex_around_face_iterator<C3t3> vbegin, vend;
		for (boost::tie(vbegin, vend) = vertices_around_face(mesh->halfedge(f), *mesh);
				vbegin != vend;
				++vbegin) {
			const Point_3& p = mesh->point(*vbegin);
			glVertex3f(p.x(), p.y(), p.z());
		}
		glEnd();
	}
*/
    glBegin(GL_TRIANGLES);
    Tr& tr = c3t3.triangulation();
    for (Tr::Facet_iterator it = tr.facets_begin(); it != tr.facets_end() ; it++ ) {
        // add_point_in_face(fh->first->vertex((fh->second+1)%4)->point());
        // add_point_in_face(fh->first->vertex((fh->second+2)%4)->point());
        // add_point_in_face(fh->first->vertex((fh->second+3)%4)->point());

        // for ( int ti = 0 ; ti < 4 ; ti++ ) {
        //     for ( int i = 0 ; i < 3 ; i++ ) {
        //         Point_3 point = cit->vertex((ti+i)%4)->point();

        //     }
        // }

        for (int i = 1; i <= 3; ++i) {
            it->first->vertex((it->second + i)%4)->point();
            // glVertex3f(p.x(), p.y(), p.z());
        }
    }
    glEnd();

    // for (Tr::Face_index f : tr.faces()) {
    //     glBegin(GL_LINE_LOOP);
    //     for (Tr::Vertex_index i : tr.vertices_around_face()) {
    //         const Point_3& p = mesh.point(i);
    //         glVertex3f(p.x(), p.y(), p.z());
    //     }
    //     glEnd();
    // }

}