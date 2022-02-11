#include <iostream>
#include <vector>
#include "Array.h"
#include "Vec3.h"
#include "Filter.h"
using namespace std;
using namespace math;

/* FilterBlur is a filter that transforms each pixel of a PPM image as follows
 * p'(x,y) = SUM<m=-N/2..N/2> { SUM<n=-N/2..N/2> { p(x+M,y+n) * f(m+N/2, n+N/2)) } }
 * where N is the degree of blur and f is an NxN array. 
 * In simple words, FilterBlur reads an NxN pixel space with (x,y) pixel being 
 * the center of this space, and sets (x,y) pixel's color to be the sum of all colors
 * of the NxN area with a weight of 1/N^2. */
class FilterBlur : public Filter , public Array<float> {
	public:
		int N; // the degree of blur
		Array<float> f; // NxN array of pixels

		// Constructors
		FilterBlur(int n) :Filter(), Array(n,n) {
			N = n;
			const float &function  = 1.0/(N*N);
			float *fu = const_cast<float*>(&function);
			f = Array<float>(N ,N);
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					f.setEntity(i, j, *fu);
				}
			}
		}
		FilterBlur(const FilterBlur& fe) :Filter(fe), Array(fe) { 
			N = fe.N;
			f = fe.f;
		}

		/* Filter operator that applies the Blur filter to the image 
		* \param image the image about to be filtered 
		* \returns filtered image*/
		Image operator << (const Image & image) {
			Image im = Image(image);
			for ( int i = 0; i <image.getWidth(); i++) {
				for ( int j = 0; j <image.getHeight(); j++) { 
					Vec3<float> sum = Vec3<float>(); // initialized to 0,0,0
					for (int m = -N / 2; m < N / 2; m++) {
						for (int n = -N/2; n < N / 2; n++) {
							if (j + n < image.getHeight() && i+m<image.getWidth()) {
								Vec3<float> current = image.getEntity(i + m, j + n);
								sum += current * f(m + N / 2, n + N / 2);
								// sum should be between 0 and 1
								sum = sum.clampToLowerBound(0.0); 
								sum = sum.clampToUpperBound(1.0);
							}
						}
					}
					im.setEntity(i, j, sum);
				}
			}
			return im;
		}
};