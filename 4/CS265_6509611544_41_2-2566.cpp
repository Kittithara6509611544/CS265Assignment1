// Kittithara Sutthaphirom 6509611544
// Depth-First Search
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits.h>

using namespace std;

class Node{
public:

    string name;
    int h;
    int distance = INT_MAX;
    vector<Node*> path;

    struct adjacent {
        Node* node;
        int weight;
    };
    vector<adjacent> adj;

    Node(string name, int h){
        this->name = name;
        this->h = h;
    }
    
	static bool comparator(const adjacent &a, const adjacent &b) {
    	return a.node->name > b.node->name;
	}

    void addAdj(Node* node, int weight){
        adjacent a;
        a.node = node;
        a.weight = weight;
        adj.push_back(a);
        sort(adj.begin(), adj.end(), comparator);
    }
    
    void depthFirst(Node* goal){
    	int count = 0;
    	vector<Node*> stack;
    	vector<string> visited;
    	stack.push_back(this->adj.back().node);
    	Node* next = stack.back();
    	visited.push_back(stack.back()->name);
    	printf("Depth-First Search from %s to %s\n", this->name.c_str(), goal->name.c_str());
    	cout << this->name;
    	while(next != goal){
    		cout << " -> " << stack.back()->name;
    		next = stack.back();
    		visited.push_back(next->name);
    		stack.pop_back();
    		for(adjacent x: next->adj){
    			if(find(visited.begin(), visited.end(), x.node->name) != visited.end()) continue;
    			stack.push_back(x.node);
			}
			count++;
			if(count >= 30){
				cout << endl << "No solution Founded" << endl;
				break;
			}
		}
		cout << endl << "Done Depth-First Search" << endl;
	} // End of Depth-First
	
};


int main() {
    Node* s = new Node("S", 10);
    Node* a = new Node("A", 8);
    Node* b = new Node("B", 9);
    Node* c = new Node("C", 7);
    Node* d = new Node("D", 4);
    Node* e = new Node("E", 3);
    Node* f = new Node("F", 0);
    Node* g = new Node("G", 6);
    Node* h = new Node("H", 6);

    s->addAdj(a, 3);
    s->addAdj(b, 2);
    s->addAdj(c, 5);
	a->addAdj(c, 3);
	a->addAdj(g, 2);
	b->addAdj(a, 4);
	b->addAdj(d, 6);
	c->addAdj(b, 4);
	c->addAdj(h, 3);
	d->addAdj(e, 2);
	d->addAdj(f, 3);
	e->addAdj(f, 5);
	g->addAdj(d, 4);
	g->addAdj(e, 5);
	h->addAdj(a, 4);
	h->addAdj(d, 4);
	
	s->depthFirst(f); 		// Expected Output: S -> A -> C -> B -> D -> E -> F
    
    return 0;
}
