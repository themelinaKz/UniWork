#include <iostream>
#include <vector>
#include <math.h>
#include "Array.h"
#include "Vec3.h"
#include "Filter.h"
using namespace std;
using namespace math;

/* FilterGamma is a filter that transforms each pixel of a PPM image as follows
 * p'(x,y) = p(x,y) ^ g
 * where g a float number between 0.5 and 2 */
class FilterGamma : public Filter {
	public:
		float g = 0.5; // number between 0.5 and 2 (default: 0.5)

		// Constructors
		FilterGamma():Filter() { 
			g = 0.5;
		}
		FilterGamma(float g) :Filter() {  
			if (0.5 <= g && g <= 2) { this->g = g;	}
			else { g = 0.5;	}
		}
		FilterGamma(const FilterGamma& f) :Filter(f) {
			if (0.5 <= g && g <= 2) { g = f.g; }
			else { g = 0.5;	}		
		}

		/* Filter operator that applies the Gamma filter to the image 
		* \param image the image about to be filtered
		* \returns filtered image*/
		Image operator << (const Image & image) {
			Image im = Image(image);
			for (unsigned int i = 0; i < image.getWidth(); i++) {
				for (unsigned int j = 0; j < image.getHeight(); j++) {
					Vec3<float> v = image.getEntity(i, j);
					v.x = pow(v.x, g);
					v.y = pow(v.y, g);
					v.z = pow(v.z, g);
					// v should be between 0 and 1
					v = v.clampToLowerBound(0.0); 
					v = v.clampToUpperBound(1.0);
					im.setEntity(i, j, v);
				}
			}
			return im;
		}
};