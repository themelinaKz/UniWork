#include "Vec3.h"
#include "Array.h"
#include "FilterGamma.cpp"
#include "FilterLinear.cpp"
#include "FilterBlur.cpp"
#include "Image.cpp"
#include "Filter.h"
#include <iostream>
#include <vector>
#include <string.h> 
#include "../ppm/ppm.h"
using namespace std;
using namespace math;

int main(int argc, char* argv[]) {
	math::Image im = Image();
	Vec3<float>* a= new Vec3<float>(); 
	Vec3<float>* c = new Vec3<float>(); 
	float g = 0.0;  
	string filename, path;

	try{
		path = argv[argc - 1];
		// if image is given as a relative path
		if (path.find("\\") != std::string::npos) { 
			filename = path.substr(path.find_last_of("/\\") + 1);
		}
		else
			filename = path;
	}
	catch(...){		
		return 0;
	}
	
	// filtered image's name
	string final = "filtered_";	
	final.append(filename);

	if (im.load(path, "PPM")) {
		for (int i = 1; i < argc-1; i++){
			// 1st argument is -f indicating that a filter follows
			if (strcmp(argv[i],"-f")==0) {
				// Linear filter
				if (strcmp(argv[i + 1],"linear")==0) {
					a = new Vec3<float>(atof(argv[i + 2]), atof(argv[i + 3]), atof(argv[i + 4]));
					c = new Vec3<float>(atof(argv[i + 5]), atof(argv[i + 6]), atof(argv[i + 7]));
					FilterLinear* fi = new FilterLinear(*a, *c);
					im = *fi << im;
					i += 7; // filter name argument plus a(3 digits) and c(3 digits)
					delete fi;
				}
				// Gamma filter
				else if (strcmp(argv[i+1],"gamma")==0) {
					g = atof(argv[i+2]); 
					FilterGamma* f = new FilterGamma(g);
					im = *f << im;
					i++;
					delete f;
				}
				// Blur filter
				else if (strcmp(argv[i + 1], "blur") == 0) {
					int N = (int)atof(argv[i + 2]);
					FilterBlur* fo = new FilterBlur(N);
					im = *fo << im;
					i++;
					delete fo;
				}
				else {
					cout << "invalid filter" << endl;
					system("PAUSE");
					return 0;
				}
			}
		}
		// save filtered image
		if (im.save(final, "ppm")) {}
	}
	
	system("Pause");
	delete a;
	delete c;
	return 0;
}


