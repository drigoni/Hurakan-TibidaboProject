#include "HanoiPiece.h"
#include <list>

class HanoiTower {
public:
	HanoiTower(float xPosition, float radius, float height);
	~HanoiTower();

	float getHeight();
	void Push(HanoiPiece* p);
	HanoiPiece* Pop();

	void Draw();
	static void DrawCylinder(float radius, float height, float xPosition);
private:
	std::list <HanoiPiece*> pieces;
	float xPosition;
	float radius;
	float height;
};