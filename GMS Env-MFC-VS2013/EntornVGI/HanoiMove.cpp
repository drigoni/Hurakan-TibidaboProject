#include "stdafx.h"
#include "HanoiMove.h"

HanoiMove::HanoiMove(HanoiTower* t1, HanoiTower*  t2) {
	this->t1 = t1;
	this->t2 = t2;
}

HanoiTower* HanoiMove::getT1() {
	return this->t1;
}
HanoiTower* HanoiMove::getT2() {
	return this->t2;
}
