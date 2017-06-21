#include <stdio.h>
#include <stdbool.h>
#include <cmath>

struct point
{
	double x;
	double y;
	double z;
};
struct pyramid
{
	struct point base_point1;
	struct point base_point2;
	double height;
};

double digonal_distance(struct point p1, struct point p2);
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
	//my name: virith
	if (isRealistic(p1)) {
		printf("The Area of p1 is: %f\n", getArea(p1));
		printf("The Volume of p1 is: %f", getVolume(p1));
	}
	getchar();
	return 0;
}//end of main

double digonal_distance(struct point p1, struct point p2)
{
	double distance = pow(pow(p2.x - p1.x,2) + pow(p2.y - p1.y,2) + pow(p2.z - p1.z, 2),0.5);
	return distance;
}//end of find digonal

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
	if (!isSamePoint(p.base_point1, p.base_point2) && p.height > 0)
	{
		realistic = true;
	}
	return realistic;
}//end of isRealistic

 //calculate area from every surface
double getArea(struct pyramid p)
{
	double base_area;
	double surface_area;
	double total_area;
	double base_vertex = digonal_distance(p.base_point1, p.base_point2) / pow(2, 0.5);

	base_area = pow(base_vertex, 2);
	surface_area = (pow(pow(p.height, 2) + pow(base_vertex/2, 2), 0.5)*base_vertex) / 2;

	total_area = 4 * surface_area + base_area;
	return total_area;
}//end of getArea

 //calculate volume of pyramid
double getVolume(struct pyramid p)
{
	double base_area;
	double volume;
	double base_vertex = digonal_distance(p.base_point1, p.base_point2) / pow(2, 0.5);

	base_area = pow(base_vertex, 2);
	volume = (base_vertex * p.height) / 3;
	return volume;
}//end of getVolume