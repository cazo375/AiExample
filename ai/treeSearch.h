#include "node.h"

struct AStarBook{
	vector<Node *> open;
	vector<Node *> closed;
};


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						//	PRODUCTION CONSTANTS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


string direction_list_regular_move_names [8] = {"UL", "U", "UR", "L", "R", "DL", "D", "DR"};
string direction_list_chess_move_names [8] = {"TL2D", "TR2D", "BL2D", "BR2D", "TL3D", "TR3D", "BL3D", "BR3D"};

int direction_list_regular_8 [8] = {-5, -4, -3, -1, 1, 3, 4, 5};
int direction_list_chess_8 [4] = {-6, -2, 2, 6};

int direction_list_regular_9 [8] = {-4, -3, -2, -1, 1, 2, 3, 4};
int direction_list_chess_9 [8] = {-5, -1, 1, 5, -7, -5, +5, +7};

int direction_list_regular_10 [8] = {-6, -5, -4, -1, 1, 4, 5, 6};
int direction_list_chess_10 [4] = {-7, -3, +3, +7};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						//	HELPER FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool isInBounds(int item, int size){
	if(item >= 0 && item < size){
		return true;
	}
	return false;
}

bool compareTwoIntArray(int* list1, int * list2, int size){
	for(int i = 0; i<size; i++){
		if(list1[i] != list2[i]){
			return false;
		}
	}
	return true;
}

bool isInList(Node * item, vector<Node *> list{
	for(int i = 0; i<list.size(); i++){
		//cout << item->state[0] << " , " << list[i]->state[0] << endl;
		if(item->cx == list[i]->cx && item->cy == list[i]->cy){
			return true;
		}
	}
	return false;
}

bool isInIntList(int * item, vector<int *> list, int size){
	for(int i = 0; i<list.size(); i++){
		//cout << item->state[0] << " , " << list[i]->state[0] << endl;
		if(compareTwoIntArray(item, list[i], size)){
			return true;
		}
	}
	return false;
}

int findIndex(int* arr, int item, int size){
	for(int i = 0; i<size; i ++){
		if(arr[i] == item){
			return i;
		}
	}
	return -1;
}

int findNodeIndex(vector<Node *> list, int * item, int size){
	for(int i = 0; i<list.size(); i ++){
		if(compareTwoIntArray(list[i]->state, item, size)){
			return i;
		}
	}
	return -1;
}

int * swap(int p1, int p2, int* list, int size){
	int * out = new int[size];
	for(int i=0; i<size; i++){
		if(i == p1){
			out[i] = list[p2];
		}
		else if(i == p2){
			out[i] = list[p1];
		}
		else{
			out[i] = list[i];
		}
	}
	return out;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						//	PRINT FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void printState (int * state, int size){
	string output;
	for(int i = 0; i < size; i++){
		cout << state[i];
		if(i < size-1){
			cout << " , ";
		}
	}
	//cout << endl;
}

void printNodeInfo(Node * node){
	if(node->action != NULL){
		cout << "Action: indices(" << node->action->index1 << ", " << node->action->index2 << ")   values: (" << node->action->value1 << ", " << node->action->value2 << ") move type: " << node->action->type << " Move Name: " << node->action->move << endl;
	}
	cout << "[";
	printState(node->state, node->state_length);
	cout << "]  depth: " << node->depth <<  endl;
}

void printNodePath (Node * currnode, int size){
	string output;
	Node * node = currnode;
	while(node->parent != NULL){
		printNodeInfo(node);
		node = node->parent;
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						//	STRATEGY FUNCTIONS
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int sumManhattanDistanceDisplacements(int * list, int size){
	int sum = 0;
	for(int i = 0; i < size; i++){
		if(list[i] != i){
			int index = findIndex(list, i, size);
			sum += abs(i - index);
		}
	}
	return sum;
}

int findShortestManhattenDistance(vector<Node *> list){
	int current_best = 99999;
	int index = -1;
	for(int i = 0; i<list.size(); i++){
		int this_distance = sumManhattanDistanceDisplacements(list[i]->state, list[i]->state_length);
		if(this_distance < current_best){
			current_best = this_distance;
			index = i;
		}
	}
	return index;
}

int countPeciesInOrder(int * list, int size){
	int count = 0;
	for(int i = 0; i < size; i++){
		if(list[i] == i){
			count = count + 1;
		}
	}
	return count;
}

int findMostInorder(vector<Node *> list){
	int current_best = 0;
	int index = -1;
	for(int i = 0; i<list.size(); i++){
		int this_distance = countPeciesInOrder(list[i]->state, list[i]->state_length);
		if(this_distance > current_best){
			current_best = this_distance;
			index = i;
		}
	}
	return index;
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

Node * getNextNode(vector<Node *> list, int * index, string strat){
	if(strat == "BFS"){
		Node * next_node = list.front();
		*index = 0;
		return next_node;
	}
	if("DFS"){
		Node * next_node = list.back();
		*index = list.size()-1;
		return next_node;
	}
	if("H1"){
		*index = findShortestManhattenDistance(list);
		Node * next_node = list[*index];
		return next_node;
	}
	if("H2"){
		*index = findMostInorder(list);
		Node * next_node = list[*index];
		return next_node;
	}
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						//	PRODUCTION
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void insertNodes(vector<Node *>* list1, vector<Node *> list2, int size){
	for(int i = 0; i<list2.size(); i++){
		if(!isInList(list2[i], *list1, size)){
			list1->push_back(list2[i]);
		}
	}
}

void insertAllNodes(vector<Node *>* list1, vector<Node *> list2, int size){
	for(int i = 0; i<list2.size(); i++){
		list1->push_back(list2[i]);
	}
}

Node * createSwap(int * new_state, int p1, int p2, Node* currnode, string move_type, int cost, int move_index, int size){
	string * dir_names;
	if(move_type == "Regular"){
		dir_names = direction_list_regular_move_names;
	}
	else if(move_type == "Chess"){
		dir_names = direction_list_chess_move_names;
	}
	Action * new_action = new Action;
	new_action->index1 = p1;
	new_action->index2 = p2;
	new_action->value1 = currnode->state[p1];
	new_action->value2 = currnode->state[p2];
	new_action->type = move_type;
	new_action->move = dir_names[move_index];
	Node* new_node = new Node(new_state, size, currnode, new_action, currnode->path_cost + cost, currnode->depth +1);
	return new_node;
}

vector<Node *> generateRegularMoves(Node* currnode, vector<int*>* seen_list, int* dir_list, int size){
	vector<Node *> new_nodes;
	int pos = findIndex(currnode->state, 0, size);
	for(int i = 0; i < 8; i++){
		int swap_pos = pos + dir_list[i];
		if(isInBounds(swap_pos, size)){
			int * new_state = swap(pos, swap_pos, currnode->state, size);
			if(!isInIntList(new_state, *seen_list, size)){
				seen_list->push_back(new_state);
				new_nodes.push_back(createSwap(new_state, pos, swap_pos, currnode, "Regular", 1, i, size));
			}
		}
	}
	return new_nodes;
}

vector<Node *> generateChessMoves(Node* currnode, vector<int*>* seen_list, int* dir_list, int size){
	vector<Node *> new_nodes;
	int dir_length = 4;
	if(size == 9){
		dir_length = 8;
	}
	for(int i = 0; i < size; i++){
		for(int j = 0; j < dir_length; j++){
			int swap_pos = i + dir_list[j];
			if(isInBounds(swap_pos, size)){
				if(currnode->state[i] != 0 && currnode->state[swap_pos] != 0 && currnode->state[i] == swap_pos && currnode->state[swap_pos] == i){
					int * new_state = swap(i, swap_pos, currnode->state, size);
					if(!isInIntList(new_state, *seen_list, size)){
						seen_list->push_back(new_state);
						new_nodes.push_back(createSwap(new_state, i, swap_pos, currnode, "Chess", 1, i, size));
					}
				}
			}
		}
	}	
	return new_nodes;
}

vector<Node *> expand(Node* currnode, vector<int*>* seen_list, int size){
	vector<Node *> new_nodes;
	int * dir_regular_list;
	int * dir_chess_list;
	if(size == 8){
		dir_regular_list = direction_list_regular_8;
		dir_chess_list = direction_list_chess_8;
	}
	else if (size == 9){
		dir_regular_list = direction_list_regular_9;
		dir_chess_list = direction_list_chess_9;
	}
	else if (size == 10){
		dir_regular_list = direction_list_regular_10;
		dir_chess_list = direction_list_chess_10;
	}
	vector<Node *> reg_nodes = generateRegularMoves(currnode, seen_list, dir_regular_list, size);
	vector<Node *> chess_nodes = generateChessMoves(currnode, seen_list, dir_chess_list, size);
	insertNodes(&new_nodes, reg_nodes, size);
	insertNodes(&new_nodes, chess_nodes, size);
	return reg_nodes;
}

//////////////////////////////////////////A Star attempt///////////////////////////////////////////////////////////////////

vector<Node *> generateRegularMovesAStar(Node* currnode, AStarBook * book, int* dir_list, int size){
	vector<Node *> new_nodes;
	int pos = findIndex(currnode->state, 0, size);
	for(int i = 0; i < 8; i++){
		int swap_pos = pos + dir_list[i];
		if(isInBounds(swap_pos, size)){
			int * new_state = swap(pos, swap_pos, currnode->state, size);
			int cost_component = countPeciesInOrder(new_state, size);
			int new_cost = currnode->path_cost + cost_component;
			//cout << "here" << endl;
			vector<Node *> open_list = book->open;
			vector<Node *> closed_list = book->closed;
			int index = findNodeIndex(open_list, new_state, size);
		
			if( index >= 0){
				Node * node = open_list[index];
				if(new_cost < node->path_cost){
					book->open = removeIthNode(open_list, index);
					new_nodes.push_back(createSwap(new_state, pos, swap_pos, currnode, "Regular", cost_component, i, size));
				}
			}
			else{
				index = findNodeIndex(closed_list, new_state, size);
			}
			if( index >= 0){
				Node * node = closed_list[index];
				if(new_cost < node->path_cost){
					book->closed = removeIthNode(closed_list, index);
					new_nodes.push_back(createSwap(new_state, pos, swap_pos, currnode, "Regular", cost_component, i, size));
				}
			}
			else{
				new_nodes.push_back(createSwap(new_state, pos, swap_pos, currnode, "Regular", cost_component, i, size));
			}
		}
	}
	return new_nodes;
}
vector<Node *> expandAStar(Node* currnode, AStarBook * book, int size){
	vector<Node *> new_nodes;
	int * dir_regular_list;
	int * dir_chess_list;
	if(size == 8){
		dir_regular_list = direction_list_regular_8;
		dir_chess_list = direction_list_chess_8;
	}
	else if (size == 9){
		dir_regular_list = direction_list_regular_9;
		dir_chess_list = direction_list_chess_9;
	}
	else if (size == 10){
		dir_regular_list = direction_list_regular_10;
		dir_chess_list = direction_list_chess_10;
	}
	vector<Node *> reg_nodes = generateRegularMovesAStar(currnode, book, dir_regular_list, size);
	//vector<Node *> chess_nodes = generateChessMoves(currnode, seen_list, dir_chess_list, size);
	insertAllNodes(&new_nodes, reg_nodes, size);
	//insertNodes(&new_nodes, chess_nodes, size);
	return reg_nodes;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
						//	MAIN SEARCH
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void treeSearch(int * problem, int * solution, string strategy, int  size){
	Node * head = new Node(problem, size, NULL, NULL, 0, 0);
	vector<Node *> fringe;
	fringe.push_back(head);

	vector<Node *> visited_nodes;
	vector<int *>percieved_states;
	percieved_states.push_back(head->state);
	
	while(true){

		if(fringe.size() == 0){
			cout << "Fringe is empty" << endl;
			return;
		}

		int index;
		Node* currnode = getNextNode(fringe, &index, strategy);
		fringe = removeIthNode(fringe, index);
		

		if(compareTwoIntArray(currnode->state, solution, size)){
			cout << "RESULT FOUND" << endl;
			printNodePath(currnode, size);
			cout << endl << "Inital Problem: ";
			printNodeInfo(head);
			cout << endl << "Solution Node: " << endl;
			printNodeInfo(currnode);
			return;
		}

		if(isInList(currnode, visited_nodes, size) == false){
			visited_nodes.push_back(currnode);
			insertNodes(&fringe, expand(currnode, &percieved_states, size), size);
			cout << "visited_nodes size = " << visited_nodes.size() << ", Fring size = " << fringe.size() << ", percieved_states = " << percieved_states.size() << endl;
		}
	}

}


void treeSearchAStar(int * problem, int * solution, string strategy, int  size){
	Node * head = new Node(problem, size, NULL, NULL, 0, 0);
	AStarBook * book_keeper = new AStarBook;
	book_keeper->open.push_back(head);

	while(true){

		if(book_keeper->open.size() == 0){
			cout << "Fringe is empty" << endl;
			return;
		}

		int index;
		Node* currnode = getNextNode(book_keeper->open, &index, strategy);
		book_keeper->open = removeIthNode(book_keeper->open, index);
		

		if(compareTwoIntArray(currnode->state, solution, size)){
			cout << "RESULT FOUND" << endl;
			printNodePath(currnode, size);
			cout << endl << "Inital Problem: ";
			printNodeInfo(head);
			cout << endl << "Solution Node: " << endl;
			printNodeInfo(currnode);
			return;
		}

		book_keeper->closed.push_back(currnode);
		insertAllNodes(&book_keeper->open, expandAStar(currnode,book_keeper, size), size);
			//insertNodes(&fringe, expand(currnode, &percieved_states, size), size);
		cout << "visited_nodes size = " << book_keeper->closed.size() << ", Fring size = " << book_keeper->open.size() << endl;
		
	}

}