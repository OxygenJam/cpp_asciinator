//All formulas are credited to the
//Wikipedia article of Grayscale
//https://en.wikipedia.org/wiki/Grayscale#Converting_color_to_grayscale

//This program serves to convert
//an image pixel by pixel into
//grayscale then into ASCII art.

//Zird Triztan E. Driz
//Larger grayscale
//var grayscaleAscii = `$@B%8&WM#*oahkbdpqwmZO0QLCJUYXzcvunxrjft/\|()1{}[]?-_+~<>i!lI;:,"^\`'. `;

//Smaller grayscale 
//var grayscaleAscii = " .:-=+*#%@";

#include "pch.h"
#include <iostream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <string>
#include <conio.h>
#include <fstream>
#include <cmath>

using namespace cv;
using namespace std;

char toGrayAscii(float rgb[]);

float grayLinear(float rgb[]);

float grayGamma(float linear);

float toColorSRGB(float color);

float toColorLinear(float csrgb);

string ImageToASCII(string filepath, int dimension);

int main()
{
	string imgpath = "./images/";
	string filename, result;
	int dimension;
	cout << "Please input the filename: ";
	cin >> filename;
	cout << "Input dimension: ";
	cin >> dimension;

	try {
		result = ImageToASCII(imgpath + filename, dimension);

		filename = filename.substr(0, filename.find(".")) + ".txt";

		string outputpath = "./output/";
		fstream file;

		file.open(outputpath + filename, fstream::out | fstream::in | fstream::app);
		file << result;
		file.close();

	}
	catch (Exception& err) {

		cout << err.what();
		return 1;
	}
	return 0;
	
}


//Computes the C linear of the respective C SRGB
float toColorLinear(float csrgb) {

	if (csrgb <= 0.04045) {
		csrgb = csrgb / 12.92;
	}
	else if (csrgb > 0.04045) {
		csrgb = pow(((csrgb + 0.055) / 1.055), 2.4);
	}

	return csrgb;
}

//Computes the respective C SRGB color in range [0,1]
float toColorSRGB(float color) {
	
	float csrgb = ceil((color / 255) * 100);

	csrgb = csrgb / 100;

	return toColorLinear(csrgb);
}

//Reapply gamma settings to the color
float grayGamma(float linear) {

	if (linear > 0.0031308) {
		return ((1.055) * (pow(linear, (1 / 2.4)))) - 0.055;
	}
	else {
		return 12.92 * linear;
	}
}

//Computes the C SRGB 
float grayLinear(float rgb[]) {
	float r, g, b, sum;

	r = (0.2126 * toColorSRGB(rgb[0]));
	g = (0.7152 * toColorSRGB(rgb[1]));
	b = (0.0722 * toColorSRGB(rgb[2]));

	sum = r + g + b;

	return sum;

}

//Retrieves the appropriate grayscale ASCII character
char toGrayAscii(float rgb[]) {

	//Larger grayscale
	//string grayscaleAscii = " .'`^\",:;Il!i><~+_-?][}{1)(|/tfjrxnuvczXYUJCLQ0OZmwqpdbkhao*#MW&8%B@$";

	//Smaller grayscale
	string grayscaleAscii = " .:-=+*#%@";

	float clinear, ylinear;

	clinear = grayLinear(rgb);

	ylinear = 1 - grayGamma(clinear);

	int index = floor(ylinear * grayscaleAscii.length());

	index = (index > 0) ? index - 1 : 0;

	return grayscaleAscii[index];
}

//Start converting pixels color channel data to ASCII
string ImageToASCII(string filepath, int dimension) {
	
	string ascii;

	if (haveImageReader(filepath)) {

		Mat img = imread(filepath);
		Mat resz;
		resize(img, resz, Size(dimension, dimension));
		int width, height;

		width = resz.cols;
		height = resz.rows;

		for (int y = 0; y < width; y++) {

			for (int x = 0; x < height; x++) {

				Vec3b intensity = resz.at<Vec3b>(y, x);
				float blue = intensity.val[0];
				float green = intensity.val[1];
				float red = intensity.val[2];

				float rgb[3] = { red, green, blue };
				ascii += toGrayAscii(rgb);

				if (x == (width - 1)) {
					
					ascii += "\n";
				}
			}
		}
		
	}
	else
	{
		throw "Can't read image file, must have not be supported or is invalid.";
	}

	return ascii;
}