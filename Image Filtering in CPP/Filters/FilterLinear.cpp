#include <iostream>
#include <vector>
#include "Array.h"
#include "Vec3.h"
#include "Filter.h"
using namespace std;
using namespace math; 

/* FilterLinear is a filter that transforms each pixel of a PPM image as follows
 * p'(x,y) = a * p(x,y) + c
 * where a and c represent RGB values each */
class FilterLinear : public Filter {
	public:
		Vec3<float> a, c; // represents a pixel with 3 values for R G B

		// Constructors
		 FilterLinear() :Filter() { 
			a = Vec3<float>(0,0,0);
			c = Vec3<float>(0,0,0);
		 }
		 FilterLinear( Vec3<float> a,Vec3<float> c) :Filter() {
			 this->a = a;
			 this->c = c;
		 }
		 FilterLinear(const FilterLinear& f) :Filter(f) { 
			 a = f.a;
			 c = f.c;
		 }

		/* Filter operator that applies the Linear filter to the image 
		* \param image the image about to be filtered 
		* \returns filtered image*/
		 Image operator << (const Image & image) {
			 Image im = Image(image);
			 for (unsigned int i = 0; i < image.getWidth(); i++) {
				 for (unsigned int j = 0; j < image.getHeight(); j++) {
					 Vec3<float> v = image.getEntity(i, j);
					 v = a * v + c;
					 // v needs to be between 0 and 1
					 v = v.clampToLowerBound(0.0);
					 v = v.clampToUpperBound(1.0);
					 
					 im.setEntity(i, j, v);
				 }
			 }
			 return im;
		 }
};