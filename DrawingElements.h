#include "Viewer3D.h"
#include "typedefs.h"

class BSpline;
class PNtriangle;

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
