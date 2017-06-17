#include <stdio.h>
#include <stdool.h>

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

int main(void)
{

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
}

//check if points can form pyramid
bool isRealistic(struct pyramid p, double h)
{
	bool realistic = false;
	if (!isSamePoint(p.base_point1, p.base_point2) && h < 0)
	{
		realistic = true;
	}
	return realistic;

}//end of isRealistic

 //calculate area from every surface
double getArea(struct pyramid p, double height)
{

}//end of getArea

 //calculate volume of pyramid
double getVolume(struct pyramid p)
{

}//end of getVolume