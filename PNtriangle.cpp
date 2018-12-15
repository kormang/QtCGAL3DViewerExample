#include "PNtriangle.h"


static double w(Point_3 i, Point_3 j, Point_3 n)
{
	Point_3 dv = Point_3(j.x() - i.x(), j.y() - i.y(), j.z() - i.z());
	return (dv.x()* n.x() + dv.y() * n.y() + dv.z() * n.z()); //dot
}

static Point_3 bb(Point_3 i, Point_3 j, Point_3 normal)
{
	double w2 = w(i, j, normal);
	return Point_3(
		(2.0 * i.x() + j.x() - w2 * normal.x()) / 3.0,
		(2.0 * i.y() + j.y() - w2 * normal.y()) / 3.0,
		(2.0 * i.z() + j.z() - w2 * normal.z()) / 3.0);
}

static double len(Point_3 p)
{
	return sqrt(p.x() * p.x() + p.y() * p.y() + p.z() * p.z());
}

static Point_3 normalize(Point_3 p)
{
	double ln = len(p);
	return Point_3(p.x() / ln, p.y() / ln, p.z() / ln);
}

static Point_3 nn(Point_3 i, Point_3 j)
{
	Point_3 dv = Point_3(j.x() - i.x(), j.y() - i.y(), j.z() - i.z());
	Point_3 vij = Point_3(
		2.0 * (dv.x() * (i.x() + j.x())) / len(dv) / len(dv),
		2.0 * (dv.y() * (i.y() + j.y())) / len(dv) / len(dv),
		2.0 * (dv.z() * (i.z() + j.z())) / len(dv) / len(dv));
	Point_3 nij = Point_3(
		i.x() + j.x() - vij.x() * dv.x(),
		i.y() + j.y() - vij.y() * dv.y(),
		i.z() + j.z() - vij.z() * dv.z());
	return normalize(nij);
}

void PNtriangle::calcPNcoefs()
{
	//Вычисление промежуточных нормалей
	n110 = nn(n200, n020);
	n101 = nn(n200, n002);
	n011 = nn(n020, n002);

	//Вычисление промежуточных вершин
	p210 = bb(p300, p030, n200);
	p120 = bb(p030, p300, n020);
	p021 = bb(p030, p003, n020);
	p012 = bb(p003, p030, n002);
	p201 = bb(p300, p003, n200);
	p102 = bb(p003, p300, n002);

	double Ex = (p210.x() + p120.x() + p021.x()
		+ p012.x() + p201.x() + p102.x()) / 6.0;
	double Ey = (p210.y() + p120.y() + p021.y()
		+ p012.y() + p201.y() + p102.y()) / 6.0;
	double Ez = (p210.z() + p120.z() + p021.z()
		+ p012.z() + p201.z() + p102.z()) / 6.0;

	double Vx = (p300.x() + p030.x() + p003.x()) / 3.0;
	double Vy = (p300.y() + p030.y() + p003.y()) / 3.0;
	double Vz = (p300.z() + p030.z() + p003.z()) / 3.0;

	p111 = Point_3(1.5 * Ex - 0.5 * Vx,
		1.5 * Ey - 0.5 * Vy,
		1.5 * Ez - 0.5 * Vz);
}

inline Point_3 PNtriangle::pointFromBarycentric(double u, double v, double w)
{
	return Point_3(
		(p300.x() * u + 3 * p210.x() * v + 3 * p201.x() * w) * u * u +
		(p030.x() * v + 3 * p120.x() * u + 3 * p021.x() * w) * v * v +
		(p003.x() * w + 3 * p012.x() * v + 3 * p102.x() * u) * w * w +
		6 * p111.x() * u * v * w,

		(p300.y() * u + 3 * p210.y() * v + 3 * p201.y() * w) * u * u +
		(p030.y() * v + 3 * p120.y() * u + 3 * p021.y() * w) * v * v +
		(p003.y() * w + 3 * p012.y() * v + 3 * p102.y() * u) * w * w +
		6 * p111.y() * u * v * w,

		(p300.z() * u + 3 * p210.z() * v + 3 * p201.z() * w) * u * u +
		(p030.z() * v + 3 * p120.z() * u + 3 * p021.z() * w) * v * v +
		(p003.z() * w + 3 * p012.z() * v + 3 * p102.z() * u) * w * w +
		6 * p111.z() * u * v * w
	);
}

inline Point_3 PNtriangle::normalFromBarycentric(double u, double v, double w)
{
	return Point_3(
		n200.x() * u * u + n020.x() * v * v + n002.x() * w * w +
		2 * n110.x() * u * v + 2 * n011.x() * v * w + 2 * n101.x() * u * w,

		n200.y() * u * u + n020.y() * v * v + n002.y() * w * w +
		2 * n110.y() * u * v + 2 * n011.y() * v * w + 2 * n101.y() * u * w,

		n200.z() * u * u + n020.z() * v * v + n002.z() * w * w +
		2 * n110.z() * u * v + 2 * n011.z() * v * w + 2 * n101.z() * u * w
	);
}


PNtriangle::PNtriangle(Point_3 p1, Point_3 p2, Point_3 p3,
	Point_3 n1, Point_3 n2, Point_3 n3, int tessellationLevel):
    p300(p1), p030(p2), p003(p3),
    n200(n1), n020(n2), n002(n3),
    tessellationLevel(tessellationLevel)
{
    calcPNcoefs();
}

PNtriangle::PNtriangle(Point_3 p1, Point_3 p2, Point_3 p3, int tessellationLevel):
    p300(p1), p030(p2), p003(p3),
    n200(normalize(p1)), n020(normalize(p2)), n002(normalize(p3)),
    tessellationLevel(tessellationLevel)
{
    calcPNcoefs();
}

inline void PNtriangle::drawPoint(double u, double v, double w)
{
    Point_3 p, n;
    p = pointFromBarycentric(u, v, w);
    n = normalFromBarycentric(u, v, w);
	glNormal3f(p.x(), p.y(), p.z());
	glVertex3f(n.x(), n.y(), n.z());
}

void PNtriangle::drawTriangle()
{
    double u, v, w;
	glColor3f(1.0, 0.9, 0.5);
    glBegin(GL_TRIANGLES);

    const int tesi = tessellationLevel + 1;
    float tes = static_cast<float>(tesi);

    for (int row = 0; row <= tessellationLevel; ++row) {
        for (int col = 0; col <= row; ++col) {
            // glBegin(GL_LINE_LOOP);
            drawPoint(
                (tesi - row)/tes,
                (row - col)/tes,
                (col)/tes
            );
            drawPoint(
                (tesi - row - 1)/tes,
                (row - col + 1)/tes,
                (col)/tes
            );
            drawPoint(
                (tesi - row - 1)/tes,
                (row - col)/tes,
                (col + 1)/tes
            );
        	// glEnd();
        }
        for (int col = 0; col < row; ++col) {
            drawPoint(
                (tesi - row)/tes,
                (row - col)/tes,
                (col)/tes
            );
            drawPoint(
                (tesi - row)/tes,
                (row - col - 1)/tes,
                (col + 1)/tes
            );
            drawPoint(
                (tesi - row - 1)/tes,
                (row - col)/tes,
                (col + 1)/tes
            );
        }
    }
    glEnd();
}
