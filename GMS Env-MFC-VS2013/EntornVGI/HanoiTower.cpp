#include "stdafx.h"
#include "HanoiTower.h"


//TOWER STRUCTURE
HanoiTower::HanoiTower(float xPosition, float radius, float height) {
	this->xPosition = xPosition;
	this->radius = radius;
	this->height = height;
}

HanoiTower::~HanoiTower() {
	for (std::list<HanoiPiece*>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
		delete (*it);
	}
	pieces.clear();
}

void HanoiTower::Push(HanoiPiece* p) {
	pieces.push_back(p);
}

HanoiPiece* HanoiTower::Pop() {
	if (!pieces.empty()) {
		HanoiPiece* p = pieces.back();
		pieces.pop_back();
		return p;
	}
	else {
		return NULL;
	}
}

float HanoiTower::getHeight() {
	return height;
}

float HanoiTower::getZLastPeace() {
	return pieces.size() + 0.5;
}

float HanoiTower::getXPosition() {
	return xPosition;
}


void HanoiTower::Draw(GLuint texturID[NUM_MAX_TEXTURES]) {
	
	HanoiTower::DrawCylinder(radius, this->getHeight(), this->xPosition, texturID);
	//Pieces
	int i = 0;
	for (std::list<HanoiPiece*>::iterator it = pieces.begin(); it != pieces.end(); ++it) {
		glPushMatrix();
			glTranslatef(xPosition, 0, i + 0.5);
			(*it)->Draw(texturID);
		glPopMatrix();
		//increment counter
		i++;
	}
}

void HanoiTower::DrawCylinder(float radius, float height, float xPosition, GLuint texturID[NUM_MAX_TEXTURES]) {
	//Cylinder
	glPushMatrix();
		glPushMatrix();
			glColor3f(0.5f, 0.35f, 0.05f);
			glTranslatef(xPosition, 0, 0);
			glBindTexture(GL_TEXTURE_2D, texturID[2]);
			glutSolidCylinder(radius, height, 100, 100);
		glPopMatrix();
	glPopMatrix();
}
