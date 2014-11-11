#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "Leap.h"
using namespace Leap;

class Sphere {
public:
	Sphere() {
		center.x = center.y = center.z = 0.0;
		radius = 0.0;
		grabbed = false;
	}

	void setCenter(const Vector& other) {
		center.x = other.x;
		center.y = other.y;
		center.z = other.z;
	}

	Vector getCenter() const {
		return center;
	}

	void setRadius(float r) {
		radius = r;
	}

	float getRadius() const {
		return radius;
	}

	void setGrab(bool g) {
		grabbed = g;
	}

	bool isGrabbed() const {
		return grabbed;
	}

private:
	Vector center;
	float radius;
	bool grabbed;
};

#endif