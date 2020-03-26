#include "tmath.h"

using namespace tmath;


float tmath::clamp(float value, float min, float max)
{
	value = fmaxf(value, min);
	return fminf(value, max);
}

int tmath::lerp(float value, float min, float max)
{
	return int((max - min) * value + min);
}

float tmath::lerpf(float value, float min, float max)
{
	return (max - min) * value + min;
}

int tmath::map(float value, float srcmin, float srcmax, float dstmin, float dstmax)
{
	return lerp(normalizef(value, srcmin, srcmax), dstmin, dstmax);
}

float tmath::mapf(float value, float srcmin, float srcmax, float dstmin, float dstmax)
{
	return lerp(normalizef(value, srcmin, srcmax), dstmin, dstmax);
}

float tmath::normalizef(float value, float min, float max)
{
	return (value - min) / (max - min);
}

//***VECTOR CLASS***

Vector::Vector(int x, int y)
{
	this->x = float(x);
	this->y = float(y);
}

Vector::Vector(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector::~Vector()
{
	
}

//X properties-----------------------------------

void Vector::setX(int x)
{
	this->x = float(x);
}

void Vector::setX(float x)
{
	this->x = x;
}

int Vector::getX()
{
	return int(x);
}

float Vector::getXf()
{
	return x;
}

//Y properties-----------------------------------

void Vector::setY(int y)
{
	this->y = float(y);
}

void Vector::setY(float y)
{
	this->y = y;
}

int Vector::getY()
{
	return int(y);
}

float Vector::getYf()
{
	return y;
}

//Length properties------------------------------

void Vector::setLength(int l)
{
	float angle = getAnglef();
	x = cosf(angle) * l;
	y = sinf(angle) * l;
}

void Vector::setLength(float l)
{
	float angle = getAnglef();
	x = cosf(angle) * l;
	y = sinf(angle) * l;
}

int Vector::getLength()
{
	return int(sqrtf(x * x + y * y));
}

float Vector::getLengthf()
{
	return sqrtf(x * x + y * y);
}

//Angle properties-------------------------------

void Vector::setAngle(int radians)
{
	float length = getLengthf();
	x = cosf(float(radians)) * length;
	y = sinf(float(radians)) * length;
}

void Vector::setAngle(float radians)
{
	float length = getLengthf();
	x = cosf(radians) * length;
	y = sinf(radians) * length;
}

int Vector::getAngle()
{
	return int(atan2f(y, x));
}

float Vector::getAnglef()
{
	return atan2f(y, x);
}

//Overloaded operators---------------------------

Vector Vector::operator+(Vector* v2)
{
	return Vector(this->x + v2->getXf(), this->y + v2->getYf());
}

Vector Vector::operator+(Vector v2)
{
	return Vector(this->x + v2.getXf(), this->y + v2.getYf());
}

void Vector::operator+=(Vector* v2)
{
	this->x += v2->getXf();
	this->y += v2->getYf();
}

void Vector::operator+=(Vector v2)
{
	this->x += v2.getXf();
	this->y += v2.getYf();
}



Vector Vector::operator-(Vector* v2)
{
	return Vector(this->x - v2->getXf(), this->y - v2->getYf());
}

Vector Vector::operator-(Vector v2)
{
	return Vector(this->x - v2.getXf(), this->y - v2.getYf());
}

void Vector::operator-=(Vector* v2)
{
	this->x += v2->getXf();
	this->y += v2->getYf();
}

void Vector::operator-=(Vector v2)
{
	this->x -= v2.getXf();
	this->y -= v2.getYf();
}



Vector Vector::operator*(int value)
{
	return Vector(this->x * value, this->y * value);
}

Vector Vector::operator*(float value)
{
	return Vector(this->x * value, this->y * value);
}

void Vector::operator*=(int value)
{
	this->x *= value;
	this->y *= value;
}

void Vector::operator*=(float value)
{
	this->x *= value;
	this->y *= value;
}



Vector Vector::operator/(int value)
{
	return Vector(this->x / value, this->y / value);
}

Vector Vector::operator/(float value)
{
	return Vector(this->x / value, this->y / value);
}

void Vector::operator/=(int value)
{
	this->x /= value;
	this->y /= value;
}

void Vector::operator/=(float value)
{
	this->x /= value;
	this->y /= value;
}

//***END VECTOR CLASS***