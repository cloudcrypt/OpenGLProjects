#include <iostream>
#include <fstream>

#include <math.h>

#include "RayTracer.h"
#include <fstream>


#define IMAGE_RESOLUTION	512
#define FIELD_OF_VIEW		55.0
#define MAX_TRACING_DEPTH	4
#define SUPER_SAMPLING		1

using std::ofstream;
using std::ifstream;

// store width and height of the render
const int width = IMAGE_RESOLUTION;
const int height = IMAGE_RESOLUTION;
const double fov = FIELD_OF_VIEW;

// Our ray tracer
RayTracer * rt;

int main(int argc, const char** argv){
	if (argc != 2) {
		cerr << "Usage: rayTracer <sceneType>" << endl;
		return 0;
	}
	if (argv[1] != "--default" && argv[1] != "--yours") {
		cerr << "Usage: rayTracer <sceneType>" << endl;
		return 0;
	}
	if (string(argv[1]) == "--default") {
		// Test scene with max depth of 4 and sampling of 1
		rt = new RayTracer(Scene::initTestScene(width, fov), MAX_TRACING_DEPTH, SUPER_SAMPLING);
	}
	else if (argv[1] == "--yours") {
		rt = new RayTracer(Scene::initCustomScene(width, fov), MAX_TRACING_DEPTH, SUPER_SAMPLING);
	}
    auto pixels = new float[width][height][4];
    for(int ctr = 0; ctr < height*width; ctr++){
    	int i = ctr % width;
    	int j = ctr / width;
    	Color rad = rt->calculate(i,j);
    	pixels[i][j][0] = rad.r; //Red
    	pixels[i][j][1] = rad.g; //Green
    	pixels[i][j][2] = rad.b; //Blue
    	pixels[i][j][3] = 1.0; //Alpha
    }
    // once we are done calculating, we will write to file.
    ofstream testimage;
	testimage.open("TestScene.ppm", ios::out);
	testimage << "P3" << endl;
	testimage << width << " " << height << endl;
	testimage << "255" << endl;
	for(int j = height-1; j >=0 ; j-- ) {
	    for(int i = 0; i< width; i++){
	        //for(int k = 0; k < 3; k++){
	             // normalize color value to 0-255.
	        	 // This assumes that the color values are in the
	        	 // range [0,1].
	        	int pixelColour = int(pixels[i][j][0]*255);
				testimage << pixelColour << " ";
				pixelColour = int(pixels[i][j][1] * 255);
				testimage << pixelColour << " ";
				pixelColour = int(pixels[i][j][2] * 255);
				testimage << pixelColour << "\n";
	        //}
	    }
	}
	testimage.close();
    return 0;   
}
