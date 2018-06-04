#include "stdafx.h"
#include "HanoiPiece.h"

//PIECE STRUCTURE
HanoiPiece::HanoiPiece(int n, float r, Color* color) {
	if (r > 0)
		this->r = r;
	else
		this->r = 1;

	this->color = color;
	this->n = n;
}

HanoiPiece::~HanoiPiece() {
	delete color;
}

float HanoiPiece::getR() {
	return this->r;
}

int HanoiPiece::getN() {
	return this->n;
}

void HanoiPiece::Draw() {
	HanoiPiece::DrawPiece(this->r, this->color);
}

void HanoiPiece::DrawPiece(float radius, Color* color) {
	glColor3f(color->getR(), color->getG(), color->getB());
	glScalef(radius,radius,1);
	//              X1  X2
	glutSolidTorus(0.5, 1.5/radius, 100, 100); //  radius*X2 -X1 = 1(1 equal to radius cylinder)
}


//---------------------------------------------------
//----------------- COLOR ---------------------------
//---------------------------------------------------
HanoiPiece::Color::Color() {
	this->r = 1;
	this->g = 1;
	this->b = 1;
}

HanoiPiece::Color::Color(float r, float g, float b) {
	if (r > 1)
		this->r = 1;
	else if (r < 0)
		this->r = 0;
	else
		this->r = r;

	if (g > 1)
		this->g = 1;
	else if (g < 0)
		this->g = 0;
	else
		this->g = g;

	if (b > 1)
		this->b = 1;
	else if (b < 0)
		this->b = 0;
	else
		this->b = b;
}

float HanoiPiece::Color::getR() {
	return this->r;
}

float HanoiPiece::Color::getG() {
	return this->g;
}

float HanoiPiece::Color::getB() {
	return this->b;
}