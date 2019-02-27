#ifndef HELPER_H
#define HELPER_H

using namespace std;

int randomInt(int range){
	return (rand() % range);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						//	GRID FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int** createGrid(int width, int height){
	int **grid;
	grid = new int *[height];
	for(int i = 0; i <height; i++){
    	grid[i] = new int[width];
    	for(int j = 0; j<width; j++)
    		grid[i][j] = 9999;
    }
    return grid;
}

int** copyGrid(int **inGrid, int width, int height){
	int **outGrid;
	outGrid = new int *[height];
	for(int i = 0; i <height; i++){
    	outGrid[i] = new int[width];
    	for(int j = 0; j<width; j++)
    		outGrid[i][j] = inGrid[i][j];
    }
    return outGrid;
}

void addWallToGrid(int **grid, int x, int y){
	grid[x][y] = -1;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						//	LIST FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool isInBounds(int num, int size){
	if(num >= 0 && num < size){
		return true;
	}
	return false;
}

bool isInList(Node * item, vector<Node *> list){
	for(int i = 0; i<list.size(); i++){
		//cout << item->state[0] << " , " << list[i]->state[0] << endl;
		if(item->cx == list[i]->cx && item->cy == list[i]->cy){
			return true;
		}
	}
	return false;
}

vector<Node *> removeIthNode(vector<Node *> list, int index){
	vector<Node *> new_list;
	for(int i = 0; i<list.size()-1; i++){
		if(i < index){
			new_list.push_back(list[i]);
		}
		else{
			new_list.push_back(list[i+1]);
		}
	}
	return new_list;
}

Node * getNextNode(vector<Node *> list, int * index){
	Node * next_node = list.front();
	*index = 0;
	return next_node;
}

void insertNodes(vector<Node *>* list1, vector<Node *> list2){
	for(int i = 0; i<list2.size(); i++){
		if(!isInList(list2[i], *list1)){
			list1->push_back(list2[i]);
		}
	}
}

void insertAllNodes(vector<Node *>* list1, vector<Node *> list2){
	for(int i = 0; i<list2.size(); i++){
		list1->push_back(list2[i]);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						//	PRINT FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



void printState (int ** state, int width, int height){
	cout << endl;
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			cout << state[j][i];
			if(j != width){
				if(state[j][i] > 99)
					cout << "   ";
				else if(state[j][i] > 9)
					cout << "    ";
				else
					cout << "     ";

			}
		}
		cout << "\n\n";
	}
	cout << endl;
}

void printMap (string ** state, int width, int height){
	cout << endl;
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			cout << state[j][i];
			if(j != width)
				cout << " ";
		}
		cout << "\n";
	}
	cout << endl;
}

void printNodeState(Node * node){
	cout << endl;
	for(int i = 0; i < node->height; i++){
		for(int j = 0; j < node->width; j++){
			cout << node->state[j][i];
			if(j != node->width){
				if(node->state[j][i] > 999)
					cout << "  ";
				else if(node->state[j][i] > 99)
					cout << "   ";
				else if(node->state[j][i] > 9)
					cout << "    ";
				else if(node->state[j][i] < 0)
					cout << "    ";
				else
					cout << "     ";

			}
		}
		cout << "\n\n";
	}
	cout << endl;
}



void printPath (Node * currnode){
	string ** output;
	int w = currnode->width;
	int h = currnode->height;

	output = new string *[h];
	for(int i = 0; i <h; i++){
    	output[i] = new string[w];
    }


    //fill in walls and blank spaces
    for(int i = 0; i < h; i++){
		for(int j = 0; j < w; j++){
			if(currnode->state[i][j] >= 0)
				output[i][j] = " ";
			if(currnode->state[i][j] == -1)
				output[i][j] = "X";
		}
	}

	//mark goal
    output[currnode->cx][currnode->cy] = "T";


	//draw path
	while(currnode->parent != NULL){
		output[currnode->parent->cx][currnode->parent->cy] = currnode->lastMove;
		currnode = currnode->parent;
	}

	//mark start
	output[currnode->cx][currnode->cy] = "S";

	printMap(output, w, h);

}
#endif