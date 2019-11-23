
#include "PPM.hpp"
#include "image.hpp"
ColorImage::ColorImage(uint16_t w, uint16_t h)
:Image<Color>(w,h){}

ColorImage::~ColorImage(){}
/*
void ColorImage::clear(Color& color){
	Image<Color>::clear(color);
}
*/
void ColorImage::writePPM(std::ofstream & os) const {
os << "P6\n#Image sauvegardée par JC\n" << width << " " << height << "\n255\n";
os.write((const char *) array, size_t(width * height * 3));
}

void ColorImage::writeTGA(std::ofstream & os, bool rle) {

	uint8_t tab1[4];
	tab1[0] = 0;
	tab1[1] = 0;
	tab1[3] = 0;

	if(rle)
		tab1[2] = 10;
	else
		tab1[2] = 2;

	uint16_t tab2[6];
	tab2[0] = 0;
	tab2[1] = 0;
	tab2[2] = 0;
	tab2[3] = 0;
	tab2[4] = width;
	tab2[5] = height;

	os.write((const char *)tab1, sizeof(tab1));
	os.write((const char *)tab2, sizeof(tab2));
	os.put(24);
	os.put(32);

	if(!rle){
		//std::cout << (uint16_t)array[15000].r << " " << (uint16_t)array[10000].g << " " << (uint16_t)array[10000].b << std::endl;
		for(int i = 0 ; i < width*height*3 ; ++i){
			uint8_t r = array[i].b;
			uint8_t b = array[i].r;

			os.put(r);
			os.put(array[i].g);
			os.put(b);

			//std::cout << "sekse" << std::endl;
		}
	}
	else{
			Color colAct;
			Color colPrev;
			uint8_t cpt = 0;

		for(int i = 0 ; i < width*height ; ++i){
			cpt = 0;
			std::cout << "nv for" << std::endl;
			colAct = array[i+1];
			colPrev = array[i];

			if(colPrev != colAct){
				std::cout << "cp1" << std::endl;
				int tempI = i;
				while(array[i] != array[i+1] && i < width*height && cpt < 127 && i%width < width-1){
					std::cout << "cpt: " << (unsigned int)cpt << std::endl;
					cpt = cpt+1;
					//std::cout << "chibrax" << std::endl;
					++i;
				}
				std::cout << "blblbl" << std::endl;
				if(cpt != 0){
					std::cout << "cp2" << std::endl;
				os.put(cpt);
				if((unsigned)cpt-1 == (unsigned)0b11101111)
					//std::cout << "prout" << std::endl;
				std::cout << "cpt RAW : " << (unsigned)cpt << std::endl;
				for(unsigned int k = tempI ; k <= tempI+(unsigned)cpt ; ++k){
					std::cout << ">" << k << "<     -   " << (unsigned)array[k].r << " , " << (unsigned)array[k].g << " , " << (unsigned)array[k].b << std::endl;
					os.put(array[k].b);
					os.put(array[k].g);
					os.put(array[k].r);
				}
				//++i;
			}
				

				cpt = 0;
			}
			else if(colPrev == colAct)
			{
				std::cout << "cp3" << std::endl;
				Color colIdem = colPrev;
				while(array[i] == colIdem && i < width*height && cpt < 127 && cpt < width && i%width != width-1){
					std::cout << "     -   " << (unsigned)array[i].r << " , " << (unsigned)array[i].g << " , " << (unsigned)array[i].b << std::endl;
					++cpt;
					++i;
				}
					std::cout << "     -   " << (unsigned)array[i].r << " , " << (unsigned)array[i].g << " , " << (unsigned)array[i].b << std::endl;
					std::cout << " ref    -   " << (unsigned)colIdem.r << " , " << (unsigned)colIdem.g << " , " << (unsigned)colIdem.b << std::endl;				
				uint8_t amettre = (0b10000000 | ((unsigned)(cpt-1)));
				std::cout << "amettre : " << (unsigned int)amettre << std::endl;
				if(amettre == 0b11111111){
					std::cout << (unsigned)cpt << std::endl;
					std::cout << " --------- TROUVEEEEEEEEEEEEEEEE ------------------" << std::endl << std::endl << std::endl << "id : " << (unsigned)i << std::endl;
				}

				os.put(amettre); // +1 ?
				std::cout << "cpt RLE : " << (unsigned)cpt << std::endl;
				
				os.put(colIdem.b);
				os.put(colIdem.g);
				os.put(colIdem.r);
				++i;
				cpt = 0;
				
			}
		}
	}

	//os.write((const char *) swapRGB(array, width, height), size_t(width * height * 3));
	//std::cout << (uint16_t)array[10000].r << " " << (uint16_t)array[10000].g << " " << (uint16_t)array[10000].b << std::endl;
}

ColorImage* ColorImage::readTGA(std::ifstream & is){

	//std::string s;
	uint8_t longIdentiField = is.get();
	if(longIdentiField > 255)
		throw std::runtime_error("Error in header - Wrong number of characters for Identification Field (should be between 0 and 255).");
	std::cout << "ID field : " << longIdentiField+1-1 << std::endl;
	uint8_t palette = is.get();
	if(palette != 0 && palette != 1)
		throw std::runtime_error("Error in header - Wrong Color Map Type (should be either 0 or 1).");

	std::cout << "palette ? " << palette+1-1 << std::endl;

	uint8_t TGAType = is.get();
	std::cout << "Type : " << TGAType+1-1 << std::endl;

	uint16_t longPal = 0;
	
	if(TGAType == 2){
		is.seekg(5, std::ios::cur);
	}

	else if(TGAType == 1){
		uint16_t PalOrigin = read16(is);
		longPal = read16(is);

		std::cout << PalOrigin << " ; " << longPal << std::endl;
		uint8_t entrySizePalette = is.get();
		std::cout << entrySizePalette+1-1 << " - " << std::endl;
	}
	else{
		throw std::runtime_error("This image is either not a TGA file or the TGA format it\'s using is not supported.");
	}
	
	uint16_t originX = read16(is);
	uint16_t originY = read16(is);
	uint16_t w = read16(is);
	uint16_t h = read16(is);

	std::cout << "origX : " << originX+1-1 << " origY : " << originY+1-1 << " w : " << w+1-1 << " h : " << h+1-1 << std::endl;
	uint8_t bitsPerPixel = is.get();
	std::cout << "bpp " << bitsPerPixel+1-1 << std::endl;
	/*if(bitsPerPixel != 24)
		throw std::runtime_error("Not an 8-bit pixel image.");*/

	uint8_t imageDescriptor = is.get();
	if(imageDescriptor != 32)
		throw std::runtime_error("Image descriptor byte is wrong or not supported.");

	std::cout << "bpp = " << bitsPerPixel+1-1 << " descriptor = " << imageDescriptor+1-1 << std::endl;
	/*if(bitsPerPixel != 24){
		std::cout << bitsPerPixel << std::endl;
		throw std::runtime_error("Not an 8-bits RGB TGA file.");
	}*/

	is.seekg(longIdentiField+longPal, std::ios::cur);


	ColorImage* ci = new ColorImage(w,h);

	if(TGAType == 1){
		if(bitsPerPixel == 8){
		uint8_t c8 = 0;
		std::cout << "size : " << sizeof(c8) << std::endl;
			for(int leCompteur = 0 ; leCompteur < w*h ; ++leCompteur){
				c8 = is.get();
				is.seekg(18+longIdentiField+c8*3, std::ios::beg);
				uint8_t b = is.get();
				uint8_t g = is.get();
				uint8_t r = is.get();
				ci->array[leCompteur] = Color(r, g, b);
				is.seekg(18+longIdentiField+longPal*3+leCompteur);
			}
		}

		else if(bitsPerPixel == 16){
			uint16_t c16 = 0;
			std::cout << "size : " << sizeof(c16) << std::endl;
			for(int leCompteur = 0 ; leCompteur < w*h ; ++leCompteur){
				c16 = read16(is);
				is.seekg(18+longIdentiField+c16*6, std::ios::beg);
				uint8_t b = is.get();
				uint8_t g = is.get();
				uint8_t r = is.get();
				ci->array[leCompteur] = Color(r, g, b);
				is.seekg(18+longIdentiField+longPal*6+leCompteur);
			}
		}

		else if(bitsPerPixel == 32){
			throw std::runtime_error("32-bit-per-pixel images are not supported.");
			/*uint32_t c32 = 0;
			std::cout << "size : " << sizeof(c32) << std::endl;
			for(int leCompteur = 0 ; leCompteur < w*h ; ++leCompteur){
				is.read((char *)c32, sizeof(c32));
				is.seekg(18+longIdentiField+c32*12, std::ios::beg);
				uint8_t b = is.get();
				uint8_t g = is.get();
				uint8_t r = is.get();
				ci->array[leCompteur] = Color(r, g, b);
				is.seekg(18+longIdentiField+longPal*12+leCompteur);
			}*/
		}

		
	
		


		/*for(int leCompteur = 0 ; leCompteur < w*h ; ++leCompteur){
			c = is.get();
			is.seekg(18+longIdentiField+c*3, std::ios::beg);
			uint8_t b = is.get();
			uint8_t g = is.get();
			uint8_t r = is.get();
			ci->array[leCompteur] = Color(r, g, b);
			is.seekg(18+longIdentiField+longPal*3+leCompteur);
		}*/
	}
	else{
	is.read((char*)ci->array,size_t(w*h)*3);
	for(int i = 0 ; i < w*h ; ++i){
		uint8_t r = ci->array[i].b;
		uint8_t b = ci->array[i].r;

		ci->array[i].r = r;
		ci->array[i].b = b;
	}
}
	

	return ci;
}

ColorImage* ColorImage::readPPM(std::ifstream & is){
std::string s;
getline(is,s);

if(s != "P6")
	throw std::runtime_error("Not a PPM file.");

skip_comments(is);
uint16_t w,h;
is >> w >> h;
is.get();
skip_comments(is);
uint16_t max_c;

is >> max_c;
if(max_c > 255)
	throw std::runtime_error("More than 8 bits image.");

std::cout << "Max : " << max_c << std::endl;
std::cout << "Largeur = " << w << std::endl;
std::cout << "Hauteur = " <<  h << std::endl;

is.get();
ColorImage* ci = new ColorImage(w,h);
is.read((char*)ci->array,size_t(w*h)*3);

return ci;
}

void ColorImage::display(){
	std::cout << std::endl;
	for(int i=0;i<height;++i){
		for(int j=0;j<width;++j){
			std::cout << "[" << array[i*width+j].r << " " << array[i*width+j].g << " " << array[i*width+j].b << "]";
		}
		std::cout << std::endl;
	}
}


