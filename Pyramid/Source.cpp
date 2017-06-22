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
	double height;
	struct vector normal;
};

bool isSamePoint(struct point p1, struct point p2);
bool isRealistic(struct pyramid p);
double getArea(struct pyramid p);
double getVolume(struct pyramid p);
int main(void)
{
	struct pyramid p1 = {
		{2, 0, 0},
		{2, 2, 0},
		2
	};
	if (isRealistic(p1)) {
		printf("The Area of p1 is: %.2f\n", getArea(p1));
		printf("The Volume of p1 is: %.2f", getVolume(p1));
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

//check if normal vector perpendicular with base surface, return true if it perpendicular
bool isPerpendicular(struct vector n, struct point baseP1, struct point baseP2)
{

}// end of isPerpendicular

//check if points can form pyramid
bool isRealistic(struct pyramid p)
{
	bool realistic = false;
	if (!isSamePoint(p.base_point1, p.base_point2) && p.height > 0 && isPerpendicular(p.normal, p.base_point1, p.base_point2))
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

 //calculate area from every surface
double getArea(struct pyramid p)
{
	double base_area;
	double surface_area;

	base_area = pow(getBaseLength(p.base_point1, p.base_point2), 2);
	surface_area = pythagor_equation(p.height, getBaseLength(p.base_point1, p.base_point2)/2)*getBaseLength(p.base_point1, p.base_point2) / 2;
	return 4 * surface_area + base_area;
}//end of getArea

 //calculate volume of pyramid
double getVolume(struct pyramid p)
{
	double base_area;
	double volume;

	base_area = pow(getBaseLength(p.base_point1, p.base_point2), 2);
	volume = (base_area * p.height) / 3;
	return volume;
}//end of getVolume

double getPerimeter(struct pyramid p)
{
	double triangle_height = pythagor_equation(p.height, getBaseLength(p.base_point1, p.base_point2) / 2);
	double base_length = getBaseLength(p.base_point1, p.base_point2);
	double triangle_side = pythagor_equation(triangle_height, base_length/2);
	return 4 * base_length + 4 * triangle_side;
}//end of getPerimeter

struct point getBasePoint3(struct pyramid p)
{
	//calculate base point3
}

struct point getBasePoint4(struct pyramid p)
{
	//calculate base point4
}

/*
Sokhavirith's tasks:
- complete fn isPerpendicular()
- complete fn getBasePoint3()
- complete fn getBasePoint4()
*/