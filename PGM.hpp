#ifndef GRYIMG
#define GRYIMG

#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cmath>
#include "image.hpp"
//class GrayImage;


class GrayImage : public Image<uint8_t>{

public:

GrayImage(uint16_t w, uint16_t h);

~GrayImage();

void writePGM(std::ofstream&) const;

//void clear(uint8_t& color = uint8_t(0)) override;


GrayImage* readPGM(std::ifstream& is);

GrayImage * simpleScale(uint16_t w, uint16_t h){
		GrayImage * retour = new GrayImage(w,h);
		double ratioW = ((double)(width)/w);
		double ratioH = ((double)(height)/h);

		for(uint16_t yp = 0 ; yp < h ; ++yp){
			for(uint16_t xp = 0 ; xp < w ; ++xp){
				double x = xp*ratioW;
				double y = yp*ratioH;

				uint16_t xtronc = (uint16_t)x;
				uint16_t ytronc = (uint16_t)y;
				retour->array[(yp*w)+xp] = array[((ytronc)*width)+xtronc];
			}
		}
		return retour;

	};

GrayImage * bilinearScale(uint16_t w, uint16_t h){
	GrayImage * retour = new GrayImage(w,h);
		double ratioW = ((double)(width)/w);
		double ratioH = ((double)(height)/h);

		for(uint16_t yp = 0 ; yp <= h ; ++yp){
			for(uint16_t xp = 0 ; xp <= w ; ++xp){
				double x = (xp*ratioW);
				double y = (yp*ratioH);

				uint16_t x1 = (uint16_t)x;
				uint16_t y1 = (uint16_t)yp;

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
		std::cout << "cp 2" << std::endl;
		return retour;
};

void display();


};

#endif