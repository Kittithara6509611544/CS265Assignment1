// Kittithara Sutthaphirom 6509611544
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Node{
public:

    string name;
    int h;

    struct adjecent {
        Node* node;
        int weight;
    };
    vector<adjecent> adj;

    Node(string name, int h){
        this->name = name;
        this->h = h;
    }
    
	static bool comparator(const adjecent &a, const adjecent &b) {
    	return a.node->name > b.node->name;
	}
    
    void addAdj(Node* node, int weight){
        adjecent a;
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
    	cout << "Depth-First Search from " << this->name << " to " << goal->name << endl;
    	cout << this->name;
    	while(next != goal){
    		cout << " -> " << stack.back()->name;
    		next = stack.back();
    		visited.push_back(next->name);
    		stack.pop_back();
    		for(adjecent x: next->adj){
    			if(find(visited.begin(), visited.end(), x.node->name) != visited.end()) continue;
    			stack.push_back(x.node);
			}
			count++;
			if(count >= 30){
				cout << endl << "No solution Founded" << endl;
				break;
			}
		}
		cout << endl << "Done Depth-First Search" << endl << endl;
	} // End of Depth-First
	
	void breadthFirst(Node* goal){
    	int count = 0;
    	queue<Node*> queue;
    	vector<string> visited;
    	for(int x=adj.size()-1;x>=0;x--){
    		queue.push(adj[x].node);
    		visited.push_back(adj[x].node->name);
		}
    	Node* next = nullptr;
    	cout << "Breadth-First Search from " << this->name << " to " << goal->name << endl;
    	cout << this->name;
    	while(next != goal){
    		next = queue.front();
    		for(adjecent x: next->adj){
    			if(find(visited.begin(), visited.end(), x.node->name) != visited.end()) continue;
    			queue.push(x.node);
    			visited.push_back(x.node->name);
			}
    		cout << " -> " << queue.front()->name;
    		queue.pop();
			count++;
			if(count >= 30){
				cout << endl << "No solution Founded" << endl;
				break;
			}
		}
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
	
	s->depthFirst(f);
	s->breadthFirst(f);
    
    return 0;
}
