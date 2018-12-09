#pragma once
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/Surface_mesh.h>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef K::Point_3 Point_3;
typedef std::vector<Point_2> Points;
typedef std::vector<Point_3> Points3;
typedef CGAL::Surface_mesh<Point_3> Surface_mesh;
