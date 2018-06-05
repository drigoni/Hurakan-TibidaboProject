#include "stdafx.h"
#include "HanoiGame.h"

int HanoiGame::nKeyboard = 3;
int HanoiGame::n = 3;
float HanoiGame::radius = 1;
HanoiTower* HanoiGame::towers[3];
bool HanoiGame::isInit = false;
bool HanoiGame::isPause = false;
bool HanoiGame::isStart = false;
bool HanoiGame::isBackward = false;
std::list<::HanoiGame::Move*> HanoiGame::movesForward;
std::list<::HanoiGame::Move*> HanoiGame::movesBackward;
HanoiGame::Animation* HanoiGame::animation;
bool HanoiGame::isAnimation = false;

//constructor
HanoiGame::HanoiGame()
{
}
//destructor
HanoiGame::~HanoiGame()
{
	for (std::list<HanoiGame::Move*>::iterator it = movesForward.begin(); it != movesForward.end(); ++it) {
		delete (*it);
	}
	for (std::list<HanoiGame::Move*>::iterator it = movesBackward.begin(); it != movesBackward.end(); ++it) {
		delete (*it);
	}
	movesForward.clear();
	movesBackward.clear();

	delete towers[0];
	delete towers[1];
	delete towers[2];
}

void HanoiGame::Increment() {
	HanoiGame::nKeyboard++;
}

void HanoiGame::Decrement() {
	HanoiGame::nKeyboard--;
	if (HanoiGame::nKeyboard < 3)
		HanoiGame::nKeyboard = 3;
}

int HanoiGame::getN() {
	return HanoiGame::n;
}

int HanoiGame::getNKeyboard() {
	return HanoiGame::nKeyboard;
}

float HanoiGame::getSpace() {
	return (radius + 0.5 + (n - 1) * 0.5) * 2  +1 ;
}

float HanoiGame::getHeight() {
	return n + 1;
}

void HanoiGame::Init() {
	//clearing
	isStart = false;
	isPause = false;
	isBackward = false;
	isAnimation = false;
	n = nKeyboard;
	for (std::list<HanoiGame::Move*>::iterator it = movesForward.begin(); it != movesForward.end(); ++it) {
		delete (*it);
	}
	for (std::list<HanoiGame::Move*>::iterator it = movesBackward.begin(); it != movesBackward.end(); ++it) {
		delete (*it);
	}
	movesForward.clear();
	movesBackward.clear();
	delete towers[0];
	delete towers[1];
	delete towers[2];
	delete animation;
	
	

	//make towers
	towers[0] = new HanoiTower(-getSpace(), radius, getHeight());
	towers[1] = new HanoiTower(0, radius, getHeight());
	towers[2] = new HanoiTower(getSpace(), radius, getHeight());

	//push pieces in the first tower at the left
	for (int i = 0; i < n; i++) {
		float r = (float)(rand() % 256) / 256;
		float g = (float)(rand() % 256) / 256;
		float b = (float)(rand() % 256) / 256;
		//build at the opposite dimension.  
		float value = radius + (n - 1)*0.5 - (i * 0.5);
		towers[0]->Push(new HanoiPiece(n+1,value, new HanoiPiece::Color(r,g,b)));
	}

	//enable variable
	HanoiGame::isInit = true;
}


void HanoiGame::OnTimer() {
	if (!HanoiGame::isPause) {
		if (!isAnimation) {
			if (!HanoiGame::isBackward) {
				if (!movesForward.empty()) {
					HanoiGame::Move* move = movesForward.front();
					movesForward.pop_front();
					movesBackward.push_front(move);
					animation = new HanoiGame::Animation(move, HanoiGame::isBackward);
					HanoiGame::isAnimation = true;
				}
			}
			else {
				if (!movesBackward.empty()) {
					HanoiGame::Move* move = movesBackward.front();
					movesBackward.pop_front();
					movesForward.push_front(move);
					animation = new HanoiGame::Animation(move, HanoiGame::isBackward);
					HanoiGame::isAnimation = true;
				}
			}
		}
		else {
			HanoiGame::isAnimation = HanoiGame::animation->isAnimation;
		}
	}
}

void HanoiGame::Draw(GLuint texturID[NUM_MAX_TEXTURES]) {
	if (HanoiGame::isInit) {

		glPushMatrix();
		// Base
		glPushMatrix();
		glBindTexture(GL_TEXTURE_2D, texturID[1]);
		glColor3f(0.5f, 0.35f, 0.05f);
		glTranslatef(0, 0, -0.5);
		glScalef(getSpace() * 3, getSpace(), 1);
		glutSolidCube(1);
		glPopMatrix();

		// Towers
		for (int i = 0; i < 3; i++) {
			glPushMatrix();
			towers[i]->Draw(texturID);
			glPopMatrix();
		}

		if (HanoiGame::isAnimation ) {
			if (!HanoiGame::isPause)
				animation->Calculation();
			glPushMatrix();
			animation->Draw(texturID);
			glPopMatrix();
		}

		glPopMatrix();
	}
}



void HanoiGame::HanoiAlgorithm(int pieces, HanoiTower* from_rod, HanoiTower* to_rod, HanoiTower* aux_rod) {
	if (pieces == 1)
	{	
		movesForward.push_back(new HanoiGame::Move(from_rod, to_rod));
		return;
	}
	HanoiGame::HanoiAlgorithm(pieces - 1, from_rod, aux_rod, to_rod);
	movesForward.push_back(new HanoiGame::Move(from_rod, to_rod));
	HanoiGame::HanoiAlgorithm(pieces - 1, aux_rod, to_rod, from_rod);
}



//---------------------------------------------------
//----------------- MOVE ----------------------------
//---------------------------------------------------
HanoiGame::Move::Move(HanoiTower* t1, HanoiTower*  t2) {
	this->t1 = t1;
	this->t2 = t2;
}

HanoiTower* HanoiGame::Move::getT1() {
	return this->t1;
}
HanoiTower* HanoiGame::Move::getT2() {
	return this->t2;
}



//---------------------------------------------------
//----------------- ANIMATION -----------------------
//---------------------------------------------------
bool HanoiGame::Animation::isAnimation = false;

HanoiGame::Animation::~Animation() {
	delete piece;
}


HanoiGame::Animation::Animation(HanoiGame::Move* move, bool isBackward) {
	int counter = 0;
	this->move = move;
	this->isBackward = isBackward;

	//extract the piece from the tower
	if (!isBackward) {
		HanoiTower* t1 = move->getT1();
		piece = t1->Pop();
	}
	else {
		HanoiTower* t2 = move->getT2();
		piece = t2->Pop();
	}

	HanoiGame::Animation::isAnimation = true;
}

void HanoiGame::Animation::Calculation() {
	if (isAnimation) {
		float xStart = 0;
		float xEnd = 0;
		float zStart = 0;
		float zEnd = 0;
		float height = 0;
		HanoiTower* t1 = NULL;
		HanoiTower* t2 = NULL;

		if (!isBackward) {
			t1 = move->getT1();
			t2 = move->getT2();
		}
		else {
			//inverted
			t1 = move->getT2();
			t2 = move->getT1();
		}

		xStart = t1->getXPosition();
		xEnd = t2->getXPosition();
		zStart = t1->getZLastPeace() + 1;
		zEnd = t2->getZLastPeace() + 1;
		height = t1->getHeight() + 1;

		if (counter <= 33) {
			//step
			x = xStart;
			z = zStart;
			z += counter * (height - zStart) / 33;
		}
		else {
			if (counter <= 66) {
				//step
				x = xStart;
				z = height;
				if (xEnd < xStart)
					x -= (counter - 33) * abs((xEnd - xStart)) / 33;
				else
					x += (counter - 33) * abs((xEnd - xStart)) / 33;
			}
			else
			{
				if (counter <= 100) {
					//step
					x = xEnd;
					z = height;
					z -= (counter - 66) * (height - zEnd) / 33;
				}
				else {
					if (!isBackward) {
						HanoiTower* t2 = move->getT2();
						t2->Push(piece);
					}
					else {
						HanoiTower* t1 = move->getT1();
						t1->Push(piece);
					}
					isAnimation = false;
					piece = NULL;
				}
			}
		}
		counter++;
	}
}

void HanoiGame::Animation::Draw(GLuint texturID[NUM_MAX_TEXTURES]) {
	if (isAnimation) {
		//draw
		glPushMatrix();
		glTranslatef(x, 0, z);
		piece->Draw(texturID);
		glPopMatrix();
	}
}







