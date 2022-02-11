#include "Vec3.h"
#include "Array.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include "../ppm/ppm.h"
using namespace std;
#ifndef IMAGE
#define IMAGE

namespace math {
	
	class Image : public Array<Vec3<float>> {
		public:
			// Constructors
			Image() : Array() { }
			Image(unsigned int w, unsigned int h) :Array(w, h){ }
			Image(unsigned int w, unsigned int h, const vector<Vec3<float>> data_ptr) :Array(w, h, data_ptr){ }

			/*! Loads the image data from the specified file, if the extension of the filename matches the format string. 
			* If the Image object is initialized, its contents are wiped out before initializing it to the width, height and data
			* read from the file.
			* \param filename is the string of the file to read the image data from.
			* \param format specifies the file format according to which the image data should be decoded from the file.
			* Only the "ppm" format is a valid format string for now.
			* \return true if the loading completes successfully, false otherwise.*/
			bool load(const std::string & filename, const std::string & format) {
				const char* strfilename = filename.c_str();
				unsigned int* w = &width;
				unsigned int* h = &height;
				string LowerFormat = format;
				string LowerFilename = filename;

				// convert the two strings to lowercase to compare them without case sensitivity 
				for (int i = 0; i < format.length(); i++)
					LowerFormat[i] = tolower(LowerFormat[i]);
				for (int i = 0; i < filename.length(); i++)
					LowerFilename[i] = tolower(LowerFilename[i]);

				// check for "ppm" suffix
				if (LowerFilename.substr(LowerFilename.length() - 3) == LowerFormat.substr(0, LowerFilename.length() - 1)) { 
					if (!buffer.empty())
						buffer.clear();
					float* pointer = ReadPPM(strfilename, (int*)w, (int*)h);
					if (pointer == nullptr || *w == 0 || *h == 0 || w == nullptr || h == nullptr)
						return false;
					int j = 0;
					
					//Request for vector's capacity to be at least enough to contain n elements
					int s = width * height; 
					buffer = vector <Vec3<float>>(s); 
					buffer.reserve(width*height); // allocate memory for the buffer
					for (int i = 0; i < width*height; i++) {
						// get the data of pointer array and store them as RGB elements in another pointer array
						buffer[i][0]= pointer[j];
						buffer[i][1] = pointer[j + 1];
						buffer[i][2]= pointer[j + 2];
						j += 3;
					}
					delete[] pointer;
					return true;
				}
				return false;
			}

			/*! Stores the image data to the specified file, if the extension of the filename matches the format string.
			* Only the "ppm" extension is supported for now. The extension comparison should be case-insensitive. If the
			* Image object is not initialized, the method should return immediately with a false return value.
			* \param filename is the string of the file to write the image data to.
			* \param format specifies the file format according to which the image data should be encoded to the file.
			* Only the "ppm" format is a valid format string for now.
			* \return true if the save operation completes successfully, false otherwise.*/
			bool save(const std::string & filename, const std::string & format) {
				const char* strfilename = filename.c_str();
				string LowerFormat = format;
				string LowerFilename = filename;

				// convert the two strings to lowercase to compare them without case sensitivity 
				for (int i = 0; i < format.length(); i++)
					LowerFormat[i] = tolower(LowerFormat[i]);
				for (int i = 0; i < filename.length(); i++)
					LowerFilename[i] = tolower(LowerFilename[i]);

				if (LowerFilename.substr(LowerFilename.length() - 3) == LowerFormat.substr(0, LowerFilename.length() - 1)) { // ppm suffix
					int size = width * height * 3;
					int max = 255;
				
					float* newbuf = new float[size];
					int j = 0;
					// newbuf gets the values of r,g,b from the buffer
					for (int i = 0; i < width*height; i++) {
						newbuf[j] = buffer[i][0];
						newbuf[j + 1] = buffer[i][1];
						newbuf[j + 2] = buffer[i][2];
						j += 3;
					}
					const float* newbuf_const = newbuf;
				
					bool write = WritePPM(newbuf_const, (int)width, (int)height, strfilename);
					// dismiss the allocated memory
					delete[] newbuf, newbuf_const; 
					return write;
				}
				return false;
			}
	};
}
#endif // !IMAGE

