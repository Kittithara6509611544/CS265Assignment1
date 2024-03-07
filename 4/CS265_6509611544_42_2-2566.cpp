// Kittithara Sutthaphirom 6509611544
// Breadth-First Search
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

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
	static bool comparatorForNode(const Node* a, const Node* b) {
    	return a->name > b->name;
	}

    void addAdj(Node* node, int weight){
        adjacent a;
        a.node = node;
        a.weight = weight;
        adj.push_back(a);
        sort(adj.begin(), adj.end(), comparator);
    }
    
	void breadthFirst(Node* goal){
    	int count = 0;
    	queue<Node*> queue;
    	vector<string> visited;
    	for(int x=adj.size()-1;x>=0;x--){
    		queue.push(adj[x].node);
    		visited.push_back(adj[x].node->name);
		}
    	Node* next = nullptr;
    	printf("\nBreadth-First Search from %s to %s\n", this->name.c_str(), goal->name.c_str());
    	cout << this->name;
    	while(next != goal){
    		next = queue.front();
    		Node** back = &queue.back();
    		cout << " -> " << queue.front()->name;
    		queue.pop();
    		visited.push_back(next->name);
    		for(adjacent x: next->adj){
    			if(find(visited.begin(), visited.end(), x.node->name) != visited.end()) continue;
    			queue.push(x.node);
			}
			sort(back, &queue.back(), comparatorForNode);
			count++;
			if(count >= 30){
				cout << endl << "No solution Founded" << endl;
				break;
			}
		}
		cout << endl << "Done Breadth-First Search" << endl;
	} // End of Breadth-First
	
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
	
	s->breadthFirst(f); 	// Expected Output: S -> A -> B -> C -> G -> D -> H -> E -> F
    
    return 0;
}
