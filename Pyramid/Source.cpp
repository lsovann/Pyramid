#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
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
double getDistance(struct point p1, struct point p2);
double pythagor_equation(double a, double b);
double getLengthOfVector(struct vector n);
double getPerimeter(struct pyramid p);
struct point getApex(struct pyramid p);
struct point getBasePoint3(struct pyramid p);
struct point getBasePoint4(struct pyramid p);
double getLengthOfVector(struct vector nv);
struct point getTail(struct vector v, struct point startP);
struct vector getCrossProduct(struct vector u, struct vector v);
struct point getMidPoint(struct point p1, struct point p2);
double getDotProduct(struct vector u, struct vector v);
struct vector getVector(struct point p1, struct point p2);
int main(int argc, char *argv[])
{
	double point1X, point1Y, point1Z;
	double point2X, point2Y, point2Z;
	double normalI, normalJ, normalK;
	printf("Input the coordinates of the following points (Ex: Enter : 1 2 3)\n");
	printf("Enter the coordinates of point 1 : ");
	scanf_s("%lf %lf %lf", &point1X, &point1Y, &point1Z);
	printf("Your point 1 coordinates (%.2f,%.2f,%.2f)\n", point1X, point1Y, point1Z);
	printf("Enter the coordinates of point 2 : ");
	scanf_s("%lf %lf %lf", &point2X, &point2Y, &point2Z);
	printf("Your point 2 coordinates (%.2f,%.2f,%.2f)\n", point2X, point2Y, point2Z);
	printf("Enter the normal vector of the pyramid : ");
	scanf_s("%lf %lf %lf", &normalI, &normalJ, &normalK);
	printf("Your normal vector is (%.2f,%.2f,%.2f)", normalI, normalJ, normalK);
	printf("\tPress any key to continue....\n");
	getchar();
	getchar();
	struct pyramid p1 = {
		{ point1X, point1Y, point1Z },
		{ point2X, point2Y, point2Z },
		{ normalI, normalJ, normalK }
	};
	FILE *fpOutput;
	if (argc != 2)
	{
		printf("Usage: %s\n", argv[0]);
		exit(1);
	}
	errno_t err;
	//if (!(fpOutput = fopen(argv[1], "a")))
	if ((
		err = fopen_s(&fpOutput, argv[1], "a")
		) != NULL)
	{
		printf("Cannot open file! %s", argv[1]);
		exit(2);
	}
	fprintf(fpOutput, "The Pyramid:\nBase Point1: (%f, %f, %f)\n", point1X, point1Y, point1Z);
	fprintf(fpOutput, "Base Point2: (%f, %f, %f)\n", point2X, point2Y, point2Z);
	fprintf(fpOutput, "Normal Vector: (%f, %f, %f)\n\n", normalI, normalJ, normalK);
	fprintf(fpOutput, "Result:\n");

	if (isRealistic(p1)) {

		fprintf(fpOutput, "Area(include all surface): %.2f unit square\n", getArea(p1));
		fprintf(fpOutput, "Volume: %.2f unit volume \n", getVolume(p1));
		fprintf(fpOutput, "Perimeter(include all vertex): %.2f unit distance \n", getPerimeter(p1));
		fprintf(fpOutput, "Apex coordinate: (%.2f, %.2f, %.2f)\n", getApex(p1).x, getApex(p1).y, getApex(p1).z);
		fprintf(fpOutput, "Base Point3: (%.2f, %.2f, %.2f)\n", getBasePoint3(p1).x, getBasePoint3(p1).y, getBasePoint3(p1).z);
		fprintf(fpOutput, "Base Point4: (%.2f, %.2f, %.2f)\n", getBasePoint4(p1).x, getBasePoint4(p1).y, getBasePoint4(p1).z);
		fprintf(fpOutput, "-------------------------------------------------------------------------------\n");

	}
	else
	{
		fprintf(fpOutput, "The pyramid is not realistic\n\n");
	}
	if (fclose(fpOutput) != 0) {
		printf("Error in closing file %s\n", argv[1]);
		exit(3);
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
	struct vector vDiagonal = getVector(p.base_point1, p.base_point2);
	if (!isSamePoint(p.base_point1, p.base_point2) && getLengthOfVector(p.normal) > 0 && getDotProduct(vDiagonal, p.normal) == 0) {
		realistic = true;
	}
	return realistic;
}//end of isRealistic

double getDistance(struct point p1, struct point p2)
{
	double digonal = pow(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2), 0.5);
	return digonal / pow(2, 0.5);
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

//calculate area from every surface
double getArea(struct pyramid p)
{
	double base_area;
	double surface_area;

	base_area = pow(getDistance(p.base_point1, p.base_point2), 2);
	surface_area = pythagor_equation(getLengthOfVector(p.normal), getDistance(p.base_point1, p.base_point2) / 2)*getDistance(p.base_point1, p.base_point2) / 2;
	return 4 * surface_area + base_area;
}//end of getArea

 //calculate volume of pyramid
double getVolume(struct pyramid p)
{
	double base_area;
	double volume;

	base_area = pow(getDistance(p.base_point1, p.base_point2), 2);
	volume = (base_area * getLengthOfVector(p.normal) / 3);
	return volume;
}//end of getVolume

double getPerimeter(struct pyramid p)
{
	double triangle_height = pythagor_equation(getLengthOfVector(p.normal), getDistance(p.base_point1, p.base_point2) / 2);
	double base_length = getDistance(p.base_point1, p.base_point2);
	double triangle_side = pythagor_equation(triangle_height, base_length / 2);
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
	return getTail(p.normal, midPoint);
}//end of getApex

struct point getTail(struct vector v, struct point startP) {
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
	double j = -1 * ((u.i *v.k) - (v.i* u.k));
	double k = (u.i * v.j) - (v.i * u.j);
	struct vector crossProduct = { i, j , k };
	return crossProduct;
}

struct point getBasePoint3(struct pyramid p)
{
	struct point midpoint = getMidPoint(p.base_point1, p.base_point2);

	struct vector vHalfDiagonal = getVector(midpoint, p.base_point2);
	struct vector vP3 = getCrossProduct(vHalfDiagonal, p.normal);

	struct point tmpP3 = getTail(vP3, midpoint);

	double lengthVP3 = getLengthOfVector(vP3);
	double cont = (getLengthOfVector(vHalfDiagonal) / lengthVP3);
	double i = cont * vP3.i;
	double j = cont * vP3.j;
	double k = cont * vP3.k;
	struct vector vP3_final = { i, j, k };
	return getTail(vP3_final, midpoint);
}

struct point getBasePoint4(struct pyramid p)
{
	struct point midpoint = getMidPoint(p.base_point1, p.base_point2);

	struct vector vHalfDiagonal = getVector(midpoint, p.base_point2);

	struct vector vP4 = getCrossProduct(p.normal, vHalfDiagonal);


	double lengthVP4 = getLengthOfVector(vP4);
	double cont = (getLengthOfVector(vHalfDiagonal) / lengthVP4);
	double i = cont * vP4.i;
	double j = cont * vP4.j;
	double k = cont * vP4.k;
	struct vector vP4_final = { i, j, k };
	return getTail(vP4_final, midpoint);
}

double getLengthOfVector(struct vector nv) {
	return pow((pow(nv.i, 2) + pow(nv.j, 2) + pow(nv.k, 2)), 0.5);
}
double getDotProduct(struct vector u, struct vector v) {
	return u.i*v.i + u.j*v.j + u.k*v.k;
}

/*
Sokhavirith's tasks:
- complete fn getApex()
- complete fn getBasePoint3()
- complete fn getBasePoint4()
*/