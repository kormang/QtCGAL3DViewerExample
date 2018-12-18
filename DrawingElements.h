#include "Viewer3D.h"
#include "typedefs.h"

class BSpline;
class PNtriangle;
class SubdivisionCurve;
class Mesh3Triangulation;

class SurfaceMeshDrawingElement : public DrawingElement
{
    Surface_mesh* mesh;
public:
	SurfaceMeshDrawingElement(Surface_mesh* mesh);
	~SurfaceMeshDrawingElement();
    void draw();
};

class BSplineDrawingElement : public DrawingElement
{
    BSpline* bspline;
public:
    BSplineDrawingElement(BSpline* bspline);
    ~BSplineDrawingElement();
    void draw();
};

class PNtriangleDrawingElement : public DrawingElement
{
    PNtriangle* pntriangle;
public:
    PNtriangleDrawingElement(PNtriangle* pntriangle);
    ~PNtriangleDrawingElement();
    void draw();
};

class SubdivisionCurveDrawingElement : public DrawingElement
{
    SubdivisionCurve* subdivisionCurve;
public:
    SubdivisionCurveDrawingElement(SubdivisionCurve* subdivisionCurve);
    ~SubdivisionCurveDrawingElement();
    void draw();
};

class Mesh3TriangulationDrawingElement : public DrawingElement
{
    Mesh3Triangulation* mesh3;
public:
    Mesh3TriangulationDrawingElement(Mesh3Triangulation* mesh3);
    ~Mesh3TriangulationDrawingElement();
    void draw();
};
