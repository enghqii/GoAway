#pragma once

class camera{
private:
	float x,y;
public:
	camera();
	void SetXY(float _x,float _y);
	float&  GetX();
	float&  GetY();
	void XPlus(float x);
};