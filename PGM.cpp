
#include "PGM.hpp"
#include "image.hpp"
GrayImage::GrayImage(uint16_t w, uint16_t h)
:Image<uint8_t>(w,h){}

GrayImage::~GrayImage(){}
/*
GrayImage::clear(T& color){
	Image<uint8_t>::clear(T);
}
*/
void GrayImage::writePGM(std::ofstream & os) const {
os << "P5\n#Image sauvegardée par JC\n" << width << " " << height << "\n255\n";
os.write((const char *) array, size_t(width * height));
}

GrayImage* GrayImage::readPGM(std::ifstream & is){
std::string s;
getline(is,s);

if(s != "P5")
	throw std::runtime_error("Not a PGM file.");

skip_comments(is);
uint16_t w,h;
is >> w >> h;
is.get();
skip_comments(is);
uint16_t max_c;

is >> max_c;
if(max_c > 255)
	throw std::runtime_error("More than 8 bits image.");

std::cout << "Max : " << max_c;
std::cout << "w = " << w << " h = " << h;
//is.get();
is.get();
GrayImage* ci = new GrayImage(w,h);
/*for(int i=0;i<h;++i){
		for(int j=0;j<w;++j){
			is.read((char*)ci->array[i*w+j], 3)
//array[i*w+j].r << " " << array[i*w+j].g << " " << array[i*width+j].b << "]";
		}
		//std::cout << std::endl;
	}*/
is.read((char*)ci->array,size_t(w*h));
return ci;
}

void GrayImage::display(){
	std::cout << std::endl;
	for(int i=0;i<height;++i){
		for(int j=0;j<width;++j){
			std::cout << "[" << array[i*width+j] << " ] ";
		}
		std::cout << std::endl;
	}
}
