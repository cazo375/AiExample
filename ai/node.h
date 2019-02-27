#ifndef NODE_H
#define NODE_H

#include <string>
#include <cstdlib>

using namespace std;

class Node {
public:
	int **state; 
	int cx;
	int cy;
	int width;
	int height;
	Node *parent;
	int path_cost;
	int depth;
	string lastMove;


	Node(int ** new_state, int w, int h){
		state = new_state;
		cx = 0;
		cy = 0;
		width = w;
		height = h;
		parent = NULL;
		path_cost = 0;
		depth = 0;
		lastMove = "";
	}

	Node(int ** new_state, int w, int h, int new_x, int new_y, Node * parent_node, int cost, int d, string lm){
		state = new_state;
		cx = new_x;
		cy = new_y;
		width = w;
		height = h;
		parent = parent_node;
		path_cost = cost;
		depth = d;
		lastMove = lm;
	}

	void setStartPosition(int new_x, int new_y){
		cx = new_x;
		cy = new_y;
		state[cx][cy] = 0;
	}

	bool checkGoal(int gx, int gy){
		if(cx == gx && cy == gy)
			return true;
		return false;
	}
};

#endif