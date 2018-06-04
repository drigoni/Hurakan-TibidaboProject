#include "HanoiTower.h"

class HanoiGame
{
public:
	HanoiGame();
	~HanoiGame();
	//methods
	static void Increment();
	static void Decrement();
	static int getN();
	static int getNKeyboard();
	static float getHeight();
	static float getSpace();
	static void Keyboard(UINT nChar, UINT nRepCnt);
	static void Draw();
	static void Init();

	static void Start(int t = 10);
	static void Stop();
	static void HanoiAlgorithm(int pieces, HanoiTower* l, HanoiTower* c, HanoiTower* r);
private: 
	static int nKeyboard;
	static int n;
	static float radius;
	static HanoiTower* towers[3];
	static bool isInit;
	static bool isPause;
	static bool isStart;
};

