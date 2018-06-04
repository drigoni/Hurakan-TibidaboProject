#include "stdafx.h"
#include "HanoiGame.h"

int HanoiGame::nKeyboard = 3;
int HanoiGame::n = 3;
float HanoiGame::radius = 1;
HanoiTower* HanoiGame::towers[3];
bool HanoiGame::isInit = false;
bool HanoiGame::isPause = false;
bool HanoiGame::isStart = false;

//constructor
HanoiGame::HanoiGame()
{
}
//destructor
HanoiGame::~HanoiGame()
{
}

//keyboard method
void HanoiGame::Keyboard(UINT nChar, UINT nRepCnt) {
	if (nChar == VK_DOWN)
		HanoiGame::Decrement();
	
	if (nChar == VK_UP)
		HanoiGame::Increment();

	if (nChar == VK_SPACE)
	{
		HanoiGame::Init();
	}

	if (nChar == VK_F5)
	{
		HanoiGame::Start();
	}

	if (nChar == VK_PAUSE)
	{
		HanoiGame::Stop();
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

void HanoiGame::Start(int t) {
	if (isInit) {
		HanoiGame::HanoiAlgorithm(n, towers[0], towers[2], towers[1]);
		isStart = true;
	}
}

void HanoiGame::Stop() {

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



void HanoiGame::HanoiAlgorithm(int pieces, HanoiTower* l, HanoiTower* c, HanoiTower* r) {
	if (pieces == 1)
	{	
		HanoiPiece* p = l->Pop();
		c->Push(p);
		return;
	}
	HanoiGame::HanoiAlgorithm(pieces - 1, l, r, c);
	HanoiPiece* p = l->Pop();
	c->Push(p);
	return;
	HanoiGame::HanoiAlgorithm(pieces - 1, r, c, l);
}





