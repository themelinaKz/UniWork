//#pragma once
#include <iostream>
#include <vector>
#include "Array.h"
#include "Vec3.h"
#include "Image.cpp"
using namespace std;
using namespace math;

#ifndef FILTER
#define FILTER

class Filter {
	public:
		// Constructors
		Filter() {  }
		Filter(const Filter& f) { 
			*this = f;
		}

		/* Applies filter to image */
		Image virtual operator << (const Image & image) = 0;
};
#endif
