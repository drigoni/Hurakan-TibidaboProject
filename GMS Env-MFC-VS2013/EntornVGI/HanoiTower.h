#include "HanoiPiece.h"
#include <list>

class HanoiTower {
public:
	HanoiTower(float xPosition, float radius, float height);
	~HanoiTower();

	float getHeight();
	float getZLastPeace();
	float getXPosition();

	void Push(HanoiPiece* p);
	HanoiPiece* Pop();

	void Draw(GLuint texturID[NUM_MAX_TEXTURES]);
	static void DrawCylinder(float radius, float height, float xPosition, GLuint texturID[NUM_MAX_TEXTURES]);

private:
	std::list <HanoiPiece*> pieces;
	float xPosition;
	float radius;
	float height;
};