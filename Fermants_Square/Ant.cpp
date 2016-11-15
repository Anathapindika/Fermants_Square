#include "stdafx.h"
#include "Ant.h"
#include "Grid.h"
#include <iostream>
#include <numeric>
#include <math.h>

using namespace std;

Ant::Ant() {

}

Ant::Ant(Grid& grid, int reach, int nmb)
{

	this->x = grid.startx;
	this->y = grid.starty;
	this->reach = reach;
	step = 0;
	this->nmb = nmb;
	time = 0;
	pheromone = 2;
	food = false;
	straightx = 0;
	straighty = 0;

	eyex = 0;
	eyey = 0;
	eyewalk = true;

	manhattenx = grid.startx;
	manhatteny = grid.starty;
	manhatten = 0;


	for (int i = 0; i < 4; i++) {
		smell[i] = 0.0;
	}
	history = 10;
}

void Ant::updatePheromomone() {
	if (food) { pheromone = 2 - time / 50.0; }
	else { pheromone = 1 - time / 50.0; }
	if (pheromone < 0) { pheromone = 0; }
}

void Ant::dAnt()
{
	delete[] smell;
}

void Ant::move0nf(Grid& grid) {

	if (history == 2) {
		int rnd = rand() % 2;
		if (rnd) {
			move1nf(grid);
		}
		else {
			move3nf(grid);
		}
		return;
	}

	grid.f0t[y][x] += pheromone;
	grid.df0[grid.duststep][y][x] += pheromone;
	y -= 1;
	history = 0;
}

void Ant::move1nf(Grid& grid) {

	if (history == 3) {
		int rnd = rand() % 2;
		if (rnd) {
			move0nf(grid);
		}
		else {
			move2nf(grid);
		}
		return;
	}
	grid.f1t[y][x] += pheromone;
	grid.df1[grid.duststep][y][x] += pheromone;

	x += 1;
	history = 1;
}

void Ant::move2nf(Grid& grid) {

	if (history == 0) {
		int rnd = rand() % 2;
		if (rnd) {
			move1nf(grid);
		}
		else {
			move3nf(grid);
		}
		return;
	}
	grid.f2t[y][x] += pheromone;
	grid.df2[grid.duststep][y][x] += pheromone;
	y += 1;
	history = 2;
}

void Ant::move3nf(Grid& grid) {

	if (history == 1) {
		int rnd = rand() % 2;
		if (rnd) {
			move0nf(grid);
		}
		else {
			move2nf(grid);
		}
		return;
	}
	grid.f3t[y][x] += pheromone;
	grid.df3[grid.duststep][y][x] += pheromone;
	x -= 1;
	history = 3;
}


void Ant::move0f(Grid& grid) {

	if (history == 2) {
		int rnd = rand() % 2;
		if (rnd) {
			move1f(grid);
		}
		else {
			move3f(grid);
		}
		return;
	}

	y -= 1;
	grid.f2t[y][x] += pheromone;
	grid.df2[grid.duststep][y][x] += pheromone;
	history = 0;
}

void Ant::move1f(Grid& grid) {

	if (history == 3) {
		int rnd = rand() % 2;
		if (rnd) {
			move0f(grid);
		}
		else {
			move2f(grid);
		}
		return;
	}

	x += 1;
	grid.f3t[y][x] += pheromone;
	grid.df3[grid.duststep][y][x] += pheromone;
	history = 1;
}

void Ant::move2f(Grid& grid) {

	if (history == 0) {
		int rnd = rand() % 2;
		if (rnd) {
			move1f(grid);
		}
		else {
			move3f(grid);
		}
		return;
	}

	y += 1;
	grid.f0t[y][x] += pheromone;
	grid.df0[grid.duststep][y][x] += pheromone;
	history = 2;
}

void Ant::move3f(Grid& grid) {

	if (history == 1) {
		int rnd = rand() % 2;
		if (rnd) {
			move0f(grid);
		}
		else {
			move2f(grid);
		}
		return;
	}

	x -= 1;
	grid.f0t[y][x] += pheromone;
	grid.df0[grid.duststep][y][x] += pheromone;
	history = 3;
}


void Ant::smellnf(Grid& grid, float cut) {


	
	
	smell[0] = cut*grid.f0nf[y][x];
	smell[0] += grid.f0nf[y - 1][x];
	smell[0] += grid.f0nf[y - 1][x + 1];
	smell[0] += grid.f0nf[y - 1][x - 1];

	smell[1] = cut*grid.f1nf[y][x];
	smell[1] += grid.f1nf[y][x + 1];
	smell[1] += grid.f1nf[y + 1][x + 1];
	smell[1] += grid.f1nf[y - 1][x + 1];

	smell[2] = cut*grid.f2nf[y][x];
	smell[2] += grid.f2nf[y + 1][x];
	smell[2] += grid.f2nf[y + 1][x + 1];
	smell[2] += grid.f2nf[y + 1][x - 1];

	smell[3] = cut*grid.f3nf[y][x];
	smell[3] += grid.f3nf[y][x - 1];
	smell[3] += grid.f3nf[y + 1][x - 1];
	smell[3] += grid.f3nf[y - 1][x - 1];

}

void Ant::smellf(Grid& grid, float cut) {

	smell[0] = cut*grid.f2f[y - 1][x];
	smell[0] += grid.f2f[y - 2][x];
	smell[0] += grid.f2f[y - 2][x + 1];
	smell[0] += grid.f2f[y - 2][x - 1];

	smell[1] = cut*grid.f3f[y][x + 1];
	smell[1] += grid.f3f[y][x + 2];
	smell[1] += grid.f3f[y - 1][x + 2];
	smell[1] += grid.f3f[y + 1][x + 2];

	smell[2] = cut*grid.f0f[y + 1][x];
	smell[2] += grid.f0f[y + 2][x];
	smell[2] += grid.f0f[y + 2][x - 1];
	smell[2] += grid.f0f[y + 2][x + 1];

	smell[3] = cut*grid.f1f[y][x - 1];
	smell[3] += grid.f1f[y][x - 2];
	smell[3] += grid.f1f[y + 1][x - 2];
	smell[3] += grid.f1f[y -1][x - 2];

}

void Ant::show() {
	cout << "Ant nmb:" << nmb << "\tcomponent:" << x << "\tY-component:" << y << "\t" << "Food:" << food << endl;
}

/*
void Ant::moveRandomf(Grid& grid) {


	int rnd = rand() % 6;

	if (rnd == history + 3 % 5) {
		rnd += rand() % 5;
		rnd = rnd % 5;
	}

	if (rnd == 0) {
		move0f(grid);
	}
	else if (rnd == 1) {
		move1f(grid);
	}
	else if (rnd == 2) {
		move2f(grid);
	}
	else if (rnd == 3) {
		move3f(grid);
	}
	else if (rnd == 4) {
		move4f(grid);
	}
	else {
		move5f(grid);
	}
}

void Ant::moveRandomnf(Grid& grid) {

	int rnd = rand() % 6;

	if (rnd == history + 3 % 5) {
		rnd += rand() % 5;
		rnd = rnd % 5;
	}

	if (rnd == 0) {
		move0nf(grid);
	}
	else if (rnd == 1) {
		move1nf(grid);
	}
	else if (rnd == 2) {
		move2nf(grid);
	}
	else if (rnd == 3) {
		move3nf(grid);
	}
}
*/

void Ant::moveStraightnf(Grid& grid, int straight) {
	int nSmell = accumulate(smell, smell + 4, 0);
	//nsmell = smell[0] + smell[1] + smell[2] + smell[3] + smell[4] + smell[5];

	if (!straightx && !straighty) {
		findeStraight(straight);
		//cout << "Now   NMB:" << nmb << "   straights: " << straight0 << "  " << straight1 << "  " << straight2 << endl;
	}

	int rndx = 0;
	int rndy = 0;

	if (straightx) {
		rndx = rand() % abs(straightx);
	}
	if (straighty) {
		rndy = rand() % abs(straighty);
	}


	if (rndx > rndy) {
		moveStraightxnf(grid);
	}
	else if (rndy > rndx) {
		moveStraightynf(grid);
	}

	else {
		if (abs(straightx) > abs(straighty)) {
			moveStraightxnf(grid);
		}
		else if (abs(straighty) > abs(straightx)) {
			moveStraightynf(grid);
		}

		else {
			int whichway = rand() % 2;
			if (whichway) {
				moveStraightxnf(grid);
			}
			else {
				moveStraightynf(grid);
			}
		}
	}
}


void Ant::moveStraightxnf(Grid& grid) {
	if (straightx > 0) {
		move1nf(grid);
		straightx -= 1;
	}

	else {
		move3nf(grid);
		straightx += 1;
	}
}

void Ant::moveStraightynf(Grid& grid) {
	if (straighty > 0) {
		move0nf(grid);
		straighty -= 1;
	}

	else {
		move2nf(grid);
		straighty += 1;
	}
}



void Ant::moveStraightf(Grid& grid, int straight) {
	int nSmell = accumulate(smell, smell + 6, 0);
	//nsmell = smell[0] + smell[1] + smell[2] + smell[3] + smell[4] + smell[5];

	if (!straightx && !straighty) {
		findeStraight(straight);
		//cout << "Now   NMB:" << nmb << "   straights: " << straight0 << "  " << straight1 << "  " << straight2 << endl;
	}

	int rndx = 0;
	int rndy = 0;

	if (straightx) {
		rndx = rand() % abs(straightx);
	}
	if (straighty) {
		rndy = rand() % abs(straighty);
	}


	if (rndx > rndy) {
		moveStraightxf(grid);
	}
	else if (rndy > rndx) {
		moveStraightyf(grid);
	}

	else {
		if (abs(straightx) > abs(straighty)) {
			moveStraightxf(grid);
		}
		else if (abs(straighty) > abs(straightx)) {
			moveStraightyf(grid);
		}

		else {
			int whichway = rand() % 2;
			if (whichway) {
				moveStraightxf(grid);
			}
			else {
				moveStraightyf(grid);
			}
		}
	}
}


void Ant::moveStraightxf(Grid& grid) {
	if (straightx > 0) {
		move1f(grid);
		straightx -= 1;
	}

	else {
		move3f(grid);
		straightx += 1;
	}
}

void Ant::moveStraightyf(Grid& grid) {
	if (straighty > 0) {
		move0f(grid);
		straighty -= 1;
	}

	else {
		move3f(grid);
		straighty += 1;
	}
}

void Ant::findeStraight(int straight) {
	int rnd;
	straight = rand() % straight + 2;
	rnd = rand() % straight;
	straightx = rnd;
	straighty = straight - rnd;

	rnd = rand() % 4;
	if (rnd == 0) {
		straightx = -straightx;
	}
	else if (rnd == 1) {
		straighty = -straighty;
	}
	else if (rnd == 2) {
		straightx = -straightx;
		straighty = -straighty;
	}
	
}

void Ant::moveSmellnf(Grid& grid, float nSmell) {

	float prob0 = smell[0] / nSmell;
	float prob1 = prob0 + smell[1] / nSmell;
	float prob2 = prob1 + smell[2] / nSmell;
	float prob3 = prob2 + smell[3] / nSmell;

	float rnd = rand() / (float)(RAND_MAX);

	straightx = straighty = 0;

	if (rnd < prob0) {
		move0nf(grid);
		//cout << "Go 0  " << nmb << "   " << x << "   " << y << endl;
	}
	else if (rnd < prob1) {
		move1nf(grid);
		//cout << "Go 1  " << nmb << "   " << x << "   " << y << endl;
	}
	else if (rnd < prob2) {
		move2nf(grid);
		//cout << "Go 2  " << nmb << "   " << x << "   " << y << endl;
	}
	else {
		move3nf(grid);
		//cout << "Go 3  " << nmb << "   " << x << "   " << y << endl;
	}
}

void Ant::moveSmellf(Grid& grid, float nSmell) {

	float prob0 = smell[0] / nSmell;
	float prob1 = prob0 + smell[1] / nSmell;
	float prob2 = prob1 + smell[2] / nSmell;
	float prob3 = prob2 + smell[3] / nSmell;

	//cout << endl << endl << "Auswertung mit FOOD" << endl;
	//cout << smell[0] << "\t" << smell[1] << "\t" << smell[2] << "\t" << smell[3] << "\t" << smell[4] << "\t" << smell[5] << "\t\t" << nSmell << endl;
	//cout << prob0 << "\t" << prob1 << "\t" << prob2 << "\t" << prob3 << "\t" << prob4 << "\t" << prob5 << endl;

	float rnd = rand() / (float)(RAND_MAX);

	straightx = straighty = 0;

	if (rnd < prob0) {
		move0f(grid);
		//cout << "Go 0  " << nmb << "   " << x << "   " << y << endl;
	}
	else if (rnd < prob1) {
		move1f(grid);
		//cout << "Go 1  " << nmb << "   " << x << "   " << y << endl;
	}
	else if (rnd < prob2) {
		move2f(grid);
		//cout << "Go 2  " << nmb << "   " << x << "   " << y << endl;
	}
	else {
		move3f(grid);
		//cout << "Go 3  " << nmb << "   " << x << "   " << y << endl;
	}

}
int Ant::antimanhatten() {

	int dx;
	int dy;
	dx = abs(x - manhattenx);
	dy = abs(y - manhatteny);
	manhattenx = x;
	manhatteny = y;



	manhatten = dx + dy - sqrt(dx*dx + dy*dy) + manhatten;

	int gain = manhatten;
	manhatten -= gain;

	return gain;

}

void Ant::move(Grid& grid, float cut, float threshold, int straight) {
	float nSmell;
	int distance;
	updatePheromomone();
	eye();
	eyex = x;
	eyey = y;
	int gain = 0;

	if (food) {
		threshold /= 4;
		distance = distancef(grid);
		if (distance>40) {
			for (int i = 0; i < reach + gain; i++) {
				smellf(grid, cut);
				nSmell = accumulate(smell, smell + 4, 0);

				if (nSmell >= threshold) {
					moveSmellf(grid, nSmell);
				}
				else {
					moveStraightf(grid, straight);
				}
				if (i == reach + gain - 1) {
					gain = antimanhatten();
				}
			}
		}
		else {
			for (int i = 0; i < reach + gain; i++) {
				smellf(grid, cut);
				nSmell = accumulate(smell, smell + 4, 0);

				if (nSmell >= threshold) {
					moveSmellf(grid, nSmell);
				}
				else {
					moveStraightf(grid, straight);
				}
				distance = distancef(grid);
				if (distance < 15) {
					goalwalkf(grid);
					cout << "Found Start!  " << pheromone << endl;
					manhattenx = x;
					manhatteny = y;
					return;
				}
				if (i == reach + gain - 1) {
					gain = antimanhatten();
				}
			}
		}
	}
	else {
		distance = distancenf(grid);
		if (distance > 40) {
			for (int i = 0; i < reach + gain; i++) {
				smellnf(grid, cut);
				nSmell = accumulate(smell, smell + 4, 0);

				if (nSmell >= threshold) {
					moveSmellnf(grid, nSmell);
				}
				else {
					moveStraightnf(grid, straight);
				}
				if (i == reach + gain - 1) {
					gain = antimanhatten();
				}
			}
		}
		else {

			for (int i = 0; i < reach + gain; i++) {
				smellnf(grid, cut);
				nSmell = accumulate(smell, smell + 4, 0);


				if (nSmell >= threshold) {
					moveSmellnf(grid, nSmell);
				}
				else {
					moveStraightnf(grid, straight);
				}
				distance = distancenf(grid);
				if (i == reach + gain - 1) {
					gain = antimanhatten();
				}

				if (distance < 15) {
					goalwalknf(grid);
					manhattenx = x;
					manhatteny = y;
					return;
				}
			}
		}
	}
	time += 1;
	step = 0;
}

int Ant::distancenf(Grid& grid) {
	int xx = abs(x - grid.foodx);
	int yy = abs(y - grid.foody);
	return xx + yy;
}

int Ant::distancef(Grid& grid) {
	int xx = abs(x - grid.startx);
	int yy = abs(y - grid.starty);
	return xx + yy;
}

void Ant::eye() {
	int xx = abs(x - eyex);
	int yy = abs(y - eyey);
	if (xx + yy < 3) {
		eyewalk = false;
	}
	else {
		eyewalk = false;
	}
}

void Ant::goalwalknf(Grid& grid) {
	int dx = x - grid.foodx;
	int dy = y - grid.foody;
	cout << "Food " << pheromone << endl;

	while (dx || dy) {
		if (abs(dx) >= abs(dy)) {
			if (dx > 0) {
				move3nf(grid);
			}
			else {
				move1nf(grid);
			}
		}
		else {
			if (dy > 0) {
				move0nf(grid);
			}
			else {
				move2nf(grid);
			}
		}
		dx = x - grid.foodx;
		dy = y - grid.foody;
	}
	food = true;
	time = 0;
	history = 10;
}

void Ant::goalwalkf(Grid& grid) {
	int dx = x - grid.startx;
	int dy = y - grid.starty;

	while (dx || dy) {
		if (abs(dx) >= abs(dy)) {
			if (dx > 0) {
				move3f(grid);
			}
			else {
				move1f(grid);
			}
	}
		else {
			if (dy > 0) {
				move0f(grid);
			}
			else {
				move2f(grid);
			}
		}

		
		dx = x - grid.startx;
		dy = y - grid.starty;
	}
	food = false;
	time = 0;
	history = 10;
}