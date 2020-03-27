//*****************************************
//  File: tmath.h
//  Project: Theodora
//  Author: Evan Hess
//  Date: 3/25/20
//
//  Purpose: Sets up math and physics
//  objects for game engine use.
//  
//  R0: 25-Mar-2020 - Original version
//*****************************************
#pragma once
#ifndef TMATH_H
#define TMATH_H

constexpr float PI = 3.141593; //Pi rounded

namespace tmath
{
	float clamp(float value, float min, float max);
	int lerp(float value, float min, float max);
	float lerpf(float value, float min, float max);
	int map(float value, float srcmin, float srcmax, float dstmin, float dstmax);
	float mapf(float value, float srcmin, float srcmax, float dstmin, float dstmax);
	float normalizef(float value, float min = 0, float max = 1);

	class Vector
	{
		public:
			Vector(int x = 0, int y = 0);
			Vector(float x, float y);
			~Vector();



			void setX(int x);
			void setX(float x);
			int getX();
			float getXf();

			void setY(int y);
			void setY(float y);
			int getY();
			float getYf();

			void setLength(int l);
			void setLength(float l);
			int getLength();
			float getLengthf();

			void setAngle(int radians);
			void setAngle(float radians);
			float getAngle();



			Vector operator+(Vector* v2);
			Vector operator+(Vector v2);
			void operator+=(Vector* v2);
			void operator+=(Vector v2);

			Vector operator-(Vector* v2);
			Vector operator-(Vector v2);
			void operator-=(Vector* v2);
			void operator-=(Vector v2);
			
			Vector operator*(int value);
			Vector operator*(float value);
			void operator*=(int value);
			void operator*=(float value);

			Vector operator/(int value);
			Vector operator/(float value);
			void operator/=(int value);
			void operator/=(float value);

		private:
			float x, y;
	};
}

#endif