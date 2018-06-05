#include "HanoiTower.h"

class HanoiMove {
public:
	HanoiMove(HanoiTower* t1 = NULL, HanoiTower* t2 = NULL);
	HanoiTower* getT1();
	HanoiTower* getT2();
private:
	HanoiTower * t1;
	HanoiTower* t2;
};