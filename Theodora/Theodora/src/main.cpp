#include <iostream>
#include <SDL.h>
#include "tmath.h"

const float PI = 3.141593; //Pi rounded

int main(int argc, char** argv)
{
	tmath::Vector v1 = tmath::Vector(10, 4);

	v1 *= 2;

	printf("X: %f\nY: %f\nAngle: %f\nLength: %f\n", v1.getXf(), v1.getYf(), v1.getAnglef(), v1.getLengthf());

	return 0;
}