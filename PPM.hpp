#ifndef COLIMG
#define COLIMG

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include "image.hpp"
//class Color;


class ColorImage : public Image<Color>{


public:

ColorImage(uint16_t w, uint16_t h);

~ColorImage();

//void clear(Color& color = (Color & coul = Color(0)) override;

void writeTGA(std::ofstream&, bool rle = true);

ColorImage * readTGA(std::ifstream & is);

uint16_t read16(std::ifstream & is){ // dedi Tristan <3
	uint8_t u1, u2;

	u1 = is.get();
	u2 = is.get();

	uint16_t u = ((uint16_t)u2 << 8) | u1;

	return u;
};

Color * swapRGB(Color * array, uint16_t w, uint16_t h, bool comment = false){
	//std::cout << "w : " << w << " h : " << h << std::endl;
	Color * nvtab = new Color[w*h];
	uint16_t prod = w*h*3;
	std::cout << "produit : " << prod << std::endl;
	for(uint16_t i = 0 ; i < prod ; ++i){
		nvtab[i].r = array[i].b;
		nvtab[i].g = array[i].g;
		nvtab[i].b = array[i].r;
		if(comment){
		std::cout << (uint16_t)array[i].r << " " << (uint16_t)array[i].g << " " << (uint16_t)array[i].b << std::endl;
		std::cout << (uint16_t)nvtab[i].r << " " << (uint16_t)nvtab[i].g << " " << (uint16_t)nvtab[i].b << std::endl;
	}
	}
	return nvtab;
}


void writePPM(std::ofstream&) const;

ColorImage* readPPM(std::ifstream& is);

ColorImage * simpleScale(uint16_t w, uint16_t h){
		ColorImage * retour = new ColorImage(w,h); // 640 480
		double ratioW = (double)(width)/w; // 0.5
		double ratioH = (double)(height)/h; // 0.5
 std::cout << " Ratio w = " << ratioW << " h = " << ratioH << std::endl;
		for(uint16_t yp = 0 ; yp < h ; ++yp){
			for(uint16_t xp = 0 ; xp < w ; ++xp){
				double x = (xp*ratioW); // 0.5
				double y = (yp*ratioH); // 0

				uint16_t xtronc = (uint16_t)x; // 0 ou 1
				uint16_t ytronc = (uint16_t)y;// 0
				retour->array[(yp*w)+xp] = array[((ytronc)*width)+xtronc];
			}
		}
		return retour;

	};

ColorImage * bilinearScale(uint16_t w, uint16_t h){
	ColorImage * retour = new ColorImage(w,h);
		double ratioW = ((double)(width)/w);
		double ratioH = ((double)(height)/h);

		for(uint16_t yp = 0 ; yp < h ; ++yp){
			for(uint16_t xp = 0 ; xp < w ; ++xp){
				double x = (xp*ratioW);
				double y = (yp*ratioH);

				uint16_t x1 = (uint16_t)x;
				uint16_t y1 = (uint16_t)y;

				double lambda = x - x1;
				double mu = y - y1;

				uint16_t xp1 = (x1+1 >= width ? x1 : x1+1);
				uint16_t yp1 = (y1+1 >= height ? y1 : y1+1);

				retour->array[(yp*w)+xp] = ((1-lambda)*(1-mu)*array[(y1*width)+x1])
											+((1-lambda)*mu*array[(yp1*width)+x1])
											+(lambda*(1-mu)*array[((y1)*width)+xp1])
											+(lambda*mu*array[((yp1)*width)+xp1]);
			}
		}
		//std::cout << "cp 2" << std::endl;
		return retour;
};

void display();


};
/*
struct TGAheader{
public:
	char id;
	char palette;
	char type;

	int debPalette;
	int taillePal;
	char tailleColPal;

	int x;
	int y;

	int width;
	int height;

	char max_c;

	char other;

}*/

#endif
