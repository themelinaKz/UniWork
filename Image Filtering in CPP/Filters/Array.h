#include <iostream>
#include <vector>
#include "../ppm/ppm.h"
using namespace std;

#ifndef ARRAY
#define ARRAY

namespace math {
	
	template <typename T> 
	class Array {
		public:
			vector<T> buffer;                 // Holds the image data.

			unsigned int width, height;			// width and height of the image (in pixels)
			
			//Constructors	                 
			Array(){
				width = height = 0;
			}
			Array(unsigned int width, unsigned int height) {
				this->width = width;
				this->height = height;
				this->buffer = vector<T>(width*height);
			}
			Array(unsigned int width, unsigned int height, const vector<T>  data_ptr) {
				this->width = width;
				this->height = height;
				buffer.clear(); // empty buffer from previous information
				buffer = data_ptr; //assign the values of data_ptr to buffer
				
			}
			Array(const Array &src) {
				width = src.width;
				height = src.height;
				buffer.clear(); // empty buffer from previous information
				buffer = src.buffer;
			}

			//destructor
			~Array<T>() {
				buffer.clear();
			}

			//getters
			const unsigned int getWidth() const { return width; }
			const unsigned int getHeight() const { return height; }

			/*! Returns pixel data at (x,y) 
			  \return NULL if x or/and y are out of bounds */
			T getEntity(unsigned int x, unsigned int y) const {
				if (x > width || y > height) return NULL; 
				return buffer.at(x + y * width); 
			}
			/*! Operator that returns pixel data at (i,j)
			  \return NULL if x or/and y are out of bounds */
			T operator() (int x, int y) {
				if (x > width || y > height) return NULL;
				return buffer[x + y * width];
			}

			/*! Copy assignment operator that assigns an Array<T> object to another 
			* \param right is the Array<T> object that is assigned to the caller object*/
			Array<T> & operator = (const Array<T> & right) { //const
				if (right.buffer.empty()) {
					this->buffer.clear();
					return *this;
				}
				else {
					if (this != &right) {
						width = right.getWidth();
						height = right.getHeight();
						buffer.clear();
						buffer = right.buffer;
					}
					return *this;
				}
			}

			/*! Sets the RGB values for an (x,y) pixel.
			*  \param x is the (zero-based) horizontal index of the pixel to set. 
			*  \param y is the (zero-based) vertical index of the pixel to set. 
			*  \param value is the new color for the (x,y) pixel.*/
			void setEntity(unsigned int x, unsigned int y, T & value) { // in responding with set_pixel from the previous assignment
				if (x > this->width) return;
				if (y > this->height) return;
				buffer[x + y * width] = value;
			}

			/*! Obtains a pointer to the internal data.*/
			vector<T> getRawDataPtr() { //returns the buffer
				return  this->buffer;
			}

			/*! Copies the image data from an external raw buffer to the internal image buffer.
			* \param data_ptr is the reference to the preallocated buffer from where to copy the data to the Array object.*/
			void setData(const T * & data_ptr) {
				if (data_ptr.empty() || width == 0 || height == 0) { //if variables are not valid then return nothing
					return;
				}
				buffer = data_ptr;
			}
	};
}
#endif