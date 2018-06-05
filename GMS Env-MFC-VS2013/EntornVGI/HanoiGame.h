#include "HanoiTower.h"
#include <gl\GL.h>

class HanoiGame
{
public:
	HanoiGame();
	~HanoiGame();
	static bool isInit;
	static bool isPause;
	static bool isStart;
	static bool isBackward;
	static HanoiTower* towers[3];

	//methods
	static void Increment();
	static void Decrement();
	static int getN();
	static int getNKeyboard();
	static float getHeight();
	static float getSpace();
	static void Draw();
	static void Init();

	static void OnTimer();
	static void HanoiAlgorithm(int pieces, HanoiTower* l, HanoiTower* c, HanoiTower* r);

	class Move {
	public:
		Move(HanoiTower* t1, HanoiTower* t2);
		HanoiTower* getT1();
		HanoiTower* getT2();
	private:
		HanoiTower* t1;
		HanoiTower* t2;
	};
private: 
	static int nKeyboard;
	static int n;
	static float radius;
	
	static std::list<HanoiGame::Move*> movesForward;
	static std::list<HanoiGame::Move*> movesBackward;
};

