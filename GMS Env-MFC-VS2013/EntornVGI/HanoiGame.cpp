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
	n = nKeyboard;
	for (std::list<HanoiGame::Move*>::iterator it = movesForward.begin(); it != movesForward.end(); ++it) {
		delete (*it);
	}
	for (std::list<HanoiGame::Move*>::iterator it = movesBackward.begin(); it != movesBackward.end(); ++it) {
		delete (*it);
	}
	delete towers[0];
	delete towers[1];
	delete towers[2];

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
		if (!HanoiGame::isBackward){
			if (!movesForward.empty()) {
				HanoiGame::Move* move = movesForward.front();
				movesForward.pop_front();
				HanoiTower* t1 = move->getT1();
				HanoiPiece* p = t1->Pop();
				HanoiTower* t2 = move->getT2();
				t2->Push(p);
				movesBackward.push_back(move);
			}
		}
		else {
			if (!movesBackward.empty()) {
				HanoiGame::Move* move = movesBackward.front();
				movesBackward.pop_front();
				HanoiTower* t2 = move->getT2();
				HanoiPiece* p = t2->Pop();
				HanoiTower* t1 = move->getT1();
				t1->Push(p);
				movesForward.push_back(move);
			}
		}
	}
}

void HanoiGame::Draw() {
	if (HanoiGame::isInit) {
		glPushMatrix();
		// Base
		glPushMatrix();
		glColor3f(0.5f, 0.35f, 0.05f);
		glTranslatef(0, 0, -0.5);
		glScalef(getSpace() * 3, getSpace(), 1);
		glutSolidCube(1);
		glPopMatrix();

		// Towers
		for (int i = 0; i < 3; i++) {
			glPushMatrix();
			towers[i]->Draw();
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







