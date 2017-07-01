#include <stdio.h>
#include <stdbool.h>
#include <cmath>

struct point
{
	double x;
	double y;
	double z;
};

struct vector
{
	double i;
	double j;
	double k;
};
struct pyramid
{
	struct point base_point1;
	struct point base_point2;
	struct vector normal;
};

bool isSamePoint(struct point p1, struct point p2);
bool isRealistic(struct pyramid p);
double getArea(struct pyramid p);
double getVolume(struct pyramid p);
double getBaseLength(struct point p1, struct point p2);
double pythagor_equation(double a, double b);
double height(struct vector n);
double getPerimeter(struct pyramid p);
struct point getApex(struct pyramid p);
struct point getBasePoint3(struct pyramid p);
struct point getBasePoint4(struct pyramid p);
double vectorLength(struct vector nv);
struct point findTail(struct vector v, struct point startP);
struct vector getCrossProduct(struct vector u, struct vector v);
struct point getMidPoint(struct point p1, struct point p2);
int main(void)
{
	struct pyramid p1 = {
		{0, 0, 0},
		{4, 4, 0},
		{0, 0, 4}
	};
	/*struct vector u = { 0, 4, 3 };
	struct vector v = { 0, 3, 5 };
	printf("The cross product is: %.2f %.2f %.2f\n", getCrossProduct(u, v).i, getCrossProduct(u, v).j, getCrossProduct(u, v).k);
	printf("The length of u: %.2f\n", vectorLength(u));*/
	//my name: virith
	if (isRealistic(p1)) {
		printf("The Area of p1 is: %.2f\n", getArea(p1));
		printf("The Volume of p1 is: %.2f\n", getVolume(p1));
		printf("The apex of p1 is: %.2f %.2f %.2f\n", getApex(p1).x, getApex(p1).y, getApex(p1).z);
		printf("The p3 of p1 is: %.2f %.2f %.2f\n", getBasePoint3(p1).x, getBasePoint3(p1).y, getBasePoint3(p1).z);
		printf("The p4 of p1 is: %.2f %.2f %.2f", getBasePoint4(p1).x, getBasePoint4(p1).y, getBasePoint4(p1).z);
	}
	getchar();
	return 0;
}//end of main

bool isSamePoint(struct point p1, struct point p2)
{
	bool samePoint = false;
	if (p1.x == p2.x && p1.y == p2.y && p1.z == p2.z)
	{
		samePoint = true;
	}
	return samePoint;
}//end of check samePoint

//check if points can form pyramid
bool isRealistic(struct pyramid p)
{
	bool realistic = false;
	if (!isSamePoint(p.base_point1, p.base_point2) && height(p.normal) > 0)
	{
		realistic = true;
	}
	return realistic;
}//end of isRealistic

double getBaseLength(struct point p1, struct point p2)
{
	double digonal = pow(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2), 0.5);
	return digonal/pow(2, 0.5);
}//end of getBaseLength

double pythagor_equation(double a, double b)
{
	return pow(pow(a, 2) + pow(b, 2), 0.5);
}

struct vector getVector(struct point p1, struct point p2)
{
	double i = p2.x - p1.x;
	double j = p2.y - p1.y;
	double k = p2.z - p1.z;
	struct vector v = { i, j, k };
	return v;
}

double height(struct vector n) {
	return sqrt(pow(n.i, 2) + pow(n.j, 2) + pow(n.k, 2));
}

 //calculate area from every surface
double getArea(struct pyramid p)
{
	double base_area;
	double surface_area;

	base_area = pow(getBaseLength(p.base_point1, p.base_point2), 2);
	surface_area = pythagor_equation(height(p.normal), getBaseLength(p.base_point1, p.base_point2)/2)*getBaseLength(p.base_point1, p.base_point2) / 2;
	return 4 * surface_area + base_area;
}//end of getArea

 //calculate volume of pyramid
double getVolume(struct pyramid p)
{
	double base_area;
	double volume;

	base_area = pow(getBaseLength(p.base_point1, p.base_point2), 2);
	volume = (base_area * height(p.normal) /3);
	return volume;
}//end of getVolume

double getPerimeter(struct pyramid p)
{
	double triangle_height = pythagor_equation(height(p.normal), getBaseLength(p.base_point1, p.base_point2) / 2);
	double base_length = getBaseLength(p.base_point1, p.base_point2);
	double triangle_side = pythagor_equation(triangle_height, base_length/2);
	return 4 * base_length + 4 * triangle_side;
}//end of getPerimeter

struct point getMidPoint(struct point p1, struct point p2)
{
	double x = (p1.x + p2.x) / 2;
	double y = (p1.y + p2.y) / 2;
	double z = (p1.z + p2.z) / 2;

	struct point midPoint = {
		x, y, z
	};
	return midPoint;
}

struct point getApex(struct pyramid p)
{
	struct point midPoint = getMidPoint(p.base_point1, p.base_point2);
	return findTail(p.normal, midPoint);
}//end of getApex

struct point findTail(struct vector v, struct point startP) {
	double x = v.i + startP.x;
	double y = v.j + startP.y;
	double z = v.k + startP.z;
	struct point endPoint = {
		x, y, z
	};
	return endPoint;
}

struct vector getCrossProduct(struct vector u, struct vector v)
{
	double i = (u.j*v.k) - (u.k * v.j);
	double j = -1 * ((u.i *v.k) - (v.i* v.k));
	double k = (u.i * v.j) - (v.i * u.j);
	struct vector crossProduct = { i, j , k};
	return crossProduct;
}

struct point getBasePoint3(struct pyramid p)
{
	struct vector vDiagonal = getVector(p.base_point1, p.base_point2);
	struct vector vP3 = getCrossProduct(vDiagonal, p.normal);
	double lengthVP3 = vectorLength(vP3);
	double cont = (vectorLength(vDiagonal) / lengthVP3 * 2);
	double i = cont * vP3.i;
	double j = cont * vP3.j;
	double k = cont * vP3.k;
	struct vector vP3_final = { i, j, k };
	return findTail(vP3_final, getMidPoint(p.base_point1, p.base_point2));
}

struct point getBasePoint4(struct pyramid p)
{
	double x = -1 * getBasePoint3(p).x;
	double y = -1 * getBasePoint3(p).y;
	double z = -1 * getBasePoint3(p).z;
	return { x, y, z };
}

double vectorLength(struct vector nv) {
	return pow((pow(nv.i,2)+ pow(nv.j,2)+ pow(nv.k,2)),0.5);
}

/*
Sokhavirith's tasks:
- complete fn getApex()
- complete fn getBasePoint3()
- complete fn getBasePoint4()
*/