#include"camera.h"
#include <windows.h>

camera::camera(){
	x = 0;
	y = 0;
}

void camera::SetXY(float _x, float _y){
	x = _x;
	y = _y;
}

float& camera::GetX(){
	if(x < 0)
		x = 0;
	return x;
}

float& camera::GetY(){
	return y;
}

void camera::XPlus(float n){
	x += n ;
}
