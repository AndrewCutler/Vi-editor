#pragma once
//typedef double TYPE;

template <class TYPE>
class Point {
public:
	Point();
	Point(TYPE, TYPE);
	void display();

	//getters
	TYPE getX() const;
	TYPE getY() const;

	//setters
	void setX(const int);
	void setY(const int);
	//double distance(Point);
private:
	TYPE mX;
	TYPE mY;
};
#include "Point.inl"