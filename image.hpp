#ifndef IMG_COLOR
#define IMG_COLOR
#include <iostream>


template <class T>
class  Image{
	protected:
	uint16_t width;
	uint16_t height;
	T * array;
	
	public:
	
	Image<T>(uint16_t w, uint16_t h)
	:width(w), height(h), array(nullptr){
		array = new T [w*h];
		}
	
	Image<T>(const Image<T>& img)
	:width(img.width), height(img.height), array(img.array){};
	
	~Image<T>(){delete [] array;}
	
	void clear(T color = T(0)){
	for(int i=0;i<width*height;++i)
		array[i] = color;
};


	
	void rectangle(int x, int y, uint16_t w, uint16_t h, T color){
		for(int i = x ; i < x+w ; ++i){
			array[y*width+i] = color;
			array[(y+h)*width+(i+1)] = color;
		}

		for(int j = y ; j < y+h ; ++j){
			array[x+((j+1)*width)] = color;
			array[x+w+(j*width)] = color;
		}

	};
	
	void fillRectangle(int x, int y, uint16_t w, uint16_t h, T color){
		for(int j = 0; j<h;++j){
			for(int i = x ; i < x+w ; ++i){
				array[y*width+i+(j*width)] = color;
				//array[((y+h)*width+(i+1))+j] = color;
			}
		}



	};

	void skip_line(std::istream & file){
		char reading;
file.get(reading);
while(reading != '\n'){
	file.get(reading);
}
};


	void skip_comments(std::istream & file){
		char reading;
file.get(reading);

while(reading == '#'){
	skip_line(file);
	file.get(reading);
}
file.putback(reading);
	}
	
};



class  Color{
public:
uint8_t r,g,b;
inline  Color(uint8_t  _r=0,uint8_t  _g=0,uint8_t  _b=0)
:r(_r) ,g(_g) ,b(_b)
{}
friend  Color  operator*(double  alpha,const  Color&color){
	return Color(color.r*alpha, color.g*alpha, color.b*alpha);
};
friend  Color  operator+(const  Color& c1,const  Color& c2){
	return Color(c1.r+c2.r, c1.g+c2.g, c1.b+c2.b);
};
friend bool operator==(const Color& c1, const Color& c2){
	return (c1.r == c2.r && c1.g == c2.g && c1.b == c2.b);
};
friend bool operator!=(const Color& c1, const Color& c2){
	return (c1.r != c2.r || c1.g != c2.g || c1.b != c2.b);
};
};

#endif
