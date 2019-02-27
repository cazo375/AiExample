#ifndef SEARCH_H
#define SEARCH_H

#include "node.h"
#include "helper.h"

using namespace std;

Node * move(Node * currnode, int new_x, int new_y, string dir){
	int ** new_state = currnode->state;//copyGrid(currnode->state, currnode->width, currnode->height);
	new_state[new_x][new_y] = currnode->path_cost + 1;
	return new Node(new_state, currnode->width, currnode->height, new_x, new_y, currnode, currnode->path_cost + 1, currnode->depth +1, dir);
}

vector<Node *> expand(Node* currnode, vector<Node*>* seen_list){
	vector<Node *> new_nodes;
	int x = currnode->cx;
	int y = currnode->cy;
	int w = currnode->width;
	int h = currnode->height;
	int move_cost = currnode->path_cost + 1;

	if(isInBounds(x+1, w)){ // move right 
		if(move_cost < currnode->state[x+1][y]){
			new_nodes.push_back(move(currnode, x+1, y, ">"));
		}
	}
	if(isInBounds(x-1, w)){ // move left
		if(move_cost < currnode->state[x-1][y]){
			new_nodes.push_back(move(currnode, x-1, y, "<"));
		}
	}
	if(isInBounds(y+1, h)){ // move down
		if(move_cost < currnode->state[x][y+1]){
			new_nodes.push_back(move(currnode, x, y+1, "v"));
		}
	}
	if(isInBounds(y-1, h)){ // move up
		if(move_cost < currnode->state[x][y-1]){
			new_nodes.push_back(move(currnode, x, y-1, "^"));
		}
	}

	return new_nodes;
}

void DijkstraSearch(Node* head, int end_x, int end_y){
	vector<Node *> fringe;
	fringe.push_back(head);

	vector<Node *> visited_nodes;

	while(true){

		if(fringe.size() == 0){
			cout << "Fringe is empty" << endl;
			return;
		}

		int index;
		Node* currnode = getNextNode(fringe, &index);
		fringe = removeIthNode(fringe, index);
		
		if(currnode->checkGoal(end_x, end_y)){
			cout << "RESULT FOUND" << endl;
			printNodeState(currnode);
			cout << "depth: " << currnode->depth << endl;
			printPath(currnode);
			return;
		}

		if(!isInList(currnode, visited_nodes)){
			visited_nodes.push_back(currnode);
			insertNodes(&fringe, expand(currnode, &visited_nodes));

		}

	}
}

#endif