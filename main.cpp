#include <iostream>
#include <fstream>
#include "image.hpp"
#include "PPM.hpp"
#include "PGM.hpp"

using namespace std;

int main(int argc, char * argv[]){
if(argc != 3)
	return 0;

//uint16_t tcv = 320;
//uint16_t dcq = 240;
ifstream pic(argv[2], ios::binary);
cout << argv[2] << endl;

//ColorImage pi(240,320);
if(strcmp(argv[1],"-c") == 0){
ofstream pic2("ColorImage_new.ppm", ios::binary);
ofstream pic3("ColorImage_new3.ppm", ios::binary);
//Color coul(50, 200, 50);
ColorImage *ptr = new ColorImage(320,240);
//ColorImage *ptr2 = new ColorImage(320, 240);
ptr = ptr->readPPM(pic); // = ColorImage::readPPM(pic);
//ptr2 = ptr2->readPPM(pic);
//ptr->writePPM(pic2);
ColorImage * gdeImage = ptr->simpleScale(640, 480);
ColorImage * gdeImage2 = ptr->bilinearScale(640, 480);
//ptr->clear(coul);
gdeImage->writePPM(pic3);
gdeImage2->writePPM(pic2);
}

if(strcmp(argv[1],"-t") == 0){
ofstream pic2("Targa_new.tga", ios::binary);
ColorImage *ptr = new ColorImage(320,240);
ptr = ptr->readTGA(pic); // = ColorImage::readPPM(pic);
ptr->writeTGA(pic2);
}

else if(strcmp(argv[1],"-g") == 0){
	ofstream pic2("GrayImage_new3.pgm", ios::binary);
	ofstream pic3("GrayImage_new2.pgm", ios::binary);
	GrayImage *ptr = new GrayImage(320,240);
	ptr = ptr->readPGM(pic);
	//ptr->writePGM(pic2);
	GrayImage * gdeImage = ptr->bilinearScale(500, 370);
	GrayImage * gdeImage2 = ptr->simpleScale(500, 370);
	/*
	uint8_t cc = 200;
	ptr->fillRectangle(30, 80, 100, 40, cc);*/
	gdeImage->writePGM(pic3);
	gdeImage2->writePGM(pic2);
}

else{
	std::cout << "Usage : -c : Image couleur (PPM) / -g : Image N&B (PGM)" << std::endl;
	return 0;
}

//ptr->display();
/*
ColorImage img1(dcq,tcv);

img1.readPPM(pic);

img1.display();

img1.writePPM(pic2);
*/

}
