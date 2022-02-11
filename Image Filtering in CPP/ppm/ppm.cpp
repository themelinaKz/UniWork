#include <iostream>
#include <fstream>
#include "ppm.h"
#include <string.h> 
using namespace std;

namespace math {

	float * ReadPPM(const char * filename, int * w, int * h) {
		int* max = 0;
		FILE* fr = fopen(filename, "rb");
		char p[3]; // 3 stands for "P"+"6"+"/0"
		if (fr == NULL) {
			cout << "File could not be opened.";
			return nullptr;
		}
		// formatted read of header
		fscanf(fr, "%s", p);

		//check the validity of the variables
		// check if it's a PPM image file
		if (strncmp(p, "P6", 3) != 0) {
			printf("not valid P value\n");
		}
		// read the rest header
		fscanf(fr, "%d\n ", w);
		fscanf(fr, "%d\n ", h);
		fscanf(fr, "%d\n ", &max);

		// allocate array for pixels
		int size = (*w) *(*h);
		unsigned char* pixels = new unsigned char[size * 3];

		// unformatted read of binary pixel data
		while (fread(pixels, sizeof(unsigned char), size * 3, fr)) { 
			fscanf(fr, "%s", pixels);
		}
		fclose(fr);

		// converting chars to float
		float* newbuf = new float[size * 3];
		for (int j = 0; j < size * 3; j++) {
			newbuf[j] = (float)pixels[j];
		}
		for (int i = 0; i < size * 3; i++) {
			newbuf[i] = newbuf[i] / 255.f; // to return the responding value in [0,1]
		}
		return newbuf;
	}

	bool WritePPM(const float * data, int w, int h, const char * filename) {
		ofstream myfile;
		myfile.open(filename, ios::out | ios::binary);
		if (!myfile.is_open()) {
			cout << "File could not be opened.";
			return 0;
		}
		// initialize file
		myfile << "P6\n" << w << "\n" << h << "\n255\n";
		// pass its pixel values
		for (int i = 0; i < 3 * w*h; i++) {
			unsigned char c = (unsigned char)(255.0f * data[i]); // scale back by multiplying with 255
			myfile.write((char*)&c, sizeof(c)); 
		}
		myfile.close();
		return 1;
	}
}