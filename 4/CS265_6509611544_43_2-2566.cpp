// Kittithara Sutthaphirom 6509611544
// Uniform Cost Search
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
	struct comp4PQueueDist{
		bool operator()(const adjacent &a, const adjacent &b){
		return a.node->distance > b.node->distance;
		}
	};

    void addAdj(Node* node, int weight){
        adjacent a;
        a.node = node;
        a.weight = weight;
        adj.push_back(a);
        sort(adj.begin(), adj.end(), comparator);
    }
    
	void uniformCost(Node* goal){
		int count = 0;
		Node* next = nullptr;
		priority_queue<adjacent, vector<adjacent>, comp4PQueueDist> pq;
		vector<string> visited;
		adjacent tmp;
		tmp.node = this;
		tmp.weight = 0;
		this->distance = 0;
		pq.push(tmp);
		printf("\nUniform Cost Search from %s to %s\n", this->name.c_str(), goal->name.c_str());
    	
		while(!pq.empty()){
			next = pq.top().node;
			pq.pop();
			next->path.push_back(next);
			visited.push_back(next->name);
			
			if(next == goal){ // Print path
				for(Node* x: next->path){
					cout << x->name;
					if(x != goal) cout << " -> ";
				}
				goto out;
			} // End print path
			else{
				for(adjacent x: next->adj){
					if(x.weight + next->distance < x.node->distance){
						x.node->distance = x.weight + next->distance;
						if(find(visited.begin(), visited.end(), x.node->name) != visited.end()) continue;
						pq.push(x);
						for(Node* y: next->path){
							x.node->path.push_back(y);
						}
					}
				}
			}
			
			count++;
			if(count >= 30){
				cout << endl << "No solution Founded" << endl;
				break;
			}
		}
out:	
	cout << endl << "Done Uniform Cost Search with " << goal->distance << " cost(s)" << endl;
	} // End of Uniform Cost

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
	
	s->uniformCost(f);		// Expected Output: S -> B -> A -> G -> D -> E -> F, sum = 16
    
    return 0;
}
