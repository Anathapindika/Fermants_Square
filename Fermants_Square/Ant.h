#pragma once
class Ant
{
	friend class Grid;

public:
	Ant();
	Ant(Grid& grid, int reach, int nmb);
	void show();
	void dAnt();

	int x;										//X-position
	int y;										//Y-position
	int eyex;
	int eyey;
	bool eyewalk;

	int nmb;									//which ant it is
	bool food;									//Food/no Food			
	int time;									//How many time-steps since reaching Food/Nest
	int reach;									//How many foot-steps per time-step
	int step;									//wich step in reach
	int history;								//what directions took in a time-step
	float* smell = new float[4];				//which direction ant smells pheromone
	int straightx;								//Where the Ant decided to go in 0
	int straighty;								//Where the Ant decided to go in 1

	int Ant::antimanhatten();
	int manhattenx;
	int manhatteny;
	float manhatten;

	float pheromone;

	void move(Grid& grid, float cut, float threshold, int straight);
	void eye();

	void moveStraightnf(Grid& grid, int straight);
	void findeStraight(int straight);
	void moveStraightxnf(Grid& grid);
	void moveStraightynf(Grid& grid);

	void moveStraightf(Grid& grid, int straight);
	void moveStraightxf(Grid& grid);
	void moveStraightyf(Grid& grid);

	void moveSmellnf(Grid& grid, float nSmell);
	void moveSmellf(Grid& grid, float nSmell);



	void move0f(Grid& grid);
	void move1f(Grid& grid);
	void move2f(Grid& grid);
	void move3f(Grid& grid);

	void move0nf(Grid& grid);
	void move1nf(Grid& grid);
	void move2nf(Grid& grid);
	void move3nf(Grid& grid);

	void smellf(Grid& grid, float cut);
	void smellnf(Grid& grid, float cut);

	int distancef(Grid& grid);
	int distancenf(Grid& grid);

	void updatePheromomone();

	void goalwalknf(Grid& grid);
	void goalwalkf(Grid& grid);

};