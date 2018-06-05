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
	static void Draw(GLuint texturID[NUM_MAX_TEXTURES]);
	static void Init();

	static void OnTimer();
	static void HanoiAlgorithm(int pieces, HanoiTower* l, HanoiTower* c, HanoiTower* r);

	class Move {
	public:
		Move(HanoiTower* t1, HanoiTower* t2);
		HanoiTower* getT1();
		HanoiTower* getT2();
	private:
		HanoiTower * t1;
		HanoiTower* t2;
	};

	class Animation {
	public:
		Animation(Move* move, bool isBackward);
		~Animation();
		static bool isAnimation;
		void Calculation();
		void Draw(GLuint texturID[NUM_MAX_TEXTURES]);
	private:
		float x, z;
		bool isBackward;
		int counter;
		Move * move;
		HanoiPiece* piece;

	};
private: 
	static int nKeyboard;
	static int n;
	static float radius;
	
	static std::list<HanoiGame::Move*> movesForward;
	static std::list<HanoiGame::Move*> movesBackward;
	static Animation* animation;
	static bool isAnimation;
};

