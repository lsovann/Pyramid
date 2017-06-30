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
double normalLength(struct vector nv);
struct point findTail(struct vector v, struct point startP);
int main(void)
{
	struct pyramid p1 = {
		{0, 0, 0},
		{4, 4, 0},
		{1, 4, 0}
	};
	//my name: virith
	if (isRealistic(p1)) {
		printf("The Area of p1 is: %.2f\n", getArea(p1));
		printf("The Volume of p1 is: %.2f\n", getVolume(p1));
		printf("The apex of p1 is: %.2f %.2f %.2f", getApex(p1).x, getApex(p1).y, getApex(p1).z);

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

struct point getApex(struct pyramid p)
{
	double x = (p.base_point1.x + p.base_point2.x) / 2;
	double y = (p.base_point1.y + p.base_point2.y) / 2;
	double z = (p.base_point1.z + p.base_point2.z) / 2;

	struct point midPoint = {
		x, y, z
	};
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

struct point getBasePoint3(struct pyramid p)
{
	struct vector cross { //vector obtain from cross product of p1p2 and normal vector
		cross.i = (p.base_point2.x - p.base_point1.x)*(p.normal.i),
		cross.j = (p.base_point2.y - p.base_point1.y)*(p.normal.j),
		cross.k = (p.base_point2.z - p.base_point1.z)*(p.normal.k)

	};
	double unitCross = pow(pow(cross.i, 2) + pow(cross.j, 2) + pow(cross.k, 2), 0.5); //unit vector of the cross product
	struct vector unitVecCross {
		unitVecCross.i = cross.i / unitCross,
		unitVecCross.j = cross.j / unitCross,
		unitVecCross.k = cross.k / unitCross
	};
	/*Mid point*/
	double mid_x = p.base_point1.x + p.base_point2.x/ 2; 
	double mid_y = p.base_point1.y + p.base_point2.y / 2;
	double mid_z = p.base_point1.z + p.base_point2.z / 2;
	/* Mid point*/
	//find point 3 (takes unit vector of the cross product times half of the base length and add mid points)
	double point3_x = unitVecCross.i *(0.5)*getBaseLength(p.base_point1, p.base_point2) + mid_x;
	double point3_y = unitVecCross.j *(0.5)*getBaseLength(p.base_point1, p.base_point2)+mid_y;
	double point3_z = unitVecCross.k *(0.5)*getBaseLength(p.base_point1, p.base_point2) + mid_z;
	return { point3_x,point3_y,point3_z };
	//calculate base point3
}

struct point getBasePoint4(struct pyramid p)
{
	struct vector cross { //vector obtain from cross product of p1p2 and normal vector
		cross.i = (p.base_point2.x - p.base_point1.x)*(p.normal.i),
			cross.j = (p.base_point2.y - p.base_point1.y)*(p.normal.j),
			cross.k = (p.base_point2.z - p.base_point1.z)*(p.normal.k)

	};
	double unitCross = pow(pow(cross.i, 2) + pow(cross.j, 2) + pow(cross.k, 2), 0.5); //unit vector of the cross product
	struct vector unitVecCross {
		unitVecCross.i = cross.i / unitCross,
			unitVecCross.j = cross.j / unitCross,
			unitVecCross.k = cross.k / unitCross
	};
	/*Mid point*/
	double mid_x = p.base_point1.x + p.base_point2.x / 2;
	double mid_y = p.base_point1.y + p.base_point2.y / 2;
	double mid_z = p.base_point1.z + p.base_point2.z / 2;
	/* Mid point*/
	double point4_x = (-1)*(unitVecCross.i *(0.5)*getBaseLength(p.base_point1, p.base_point2)) + mid_x;
	double point4_y = (-1)*(unitVecCross.i *(0.5)*getBaseLength(p.base_point1, p.base_point2)) + mid_y;
	double point4_z = (-1)*(unitVecCross.i *(0.5)*getBaseLength(p.base_point1, p.base_point2)) + mid_z;
	return { point4_x,point4_y,point4_z };
	//calculate base point4
}

double normalLength(struct vector nv) {
	return pow((pow(nv.i,2), pow(nv.j,2), pow(nv.k,2)),0.5);
}

/*
Sokhavirith's tasks:
- complete fn getApex()
- complete fn getBasePoint3()
- complete fn getBasePoint4()
*/