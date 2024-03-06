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
	struct comp4PQueue{
		bool operator()(const adjacent &a, const adjacent &b){
		return a.weight > b.weight;
		}
	};
	struct comp4Greedy{
		bool operator()(const adjacent &a, const adjacent &b){
		return a.node->h > b.node->h;
		}
	};
	struct comp4aStar{
		bool operator()(const adjacent &a, const adjacent &b){
			if(a.weight+a.node->h == b.weight+b.node->h) return a.node->name > b.node->name;
		else return a.weight+a.node->h > b.weight+b.node->h;
		}
	};


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
    	printf("\nBreadth-First Search from %s to %s\n", this->name.c_str(), goal->name.c_str());
    	cout << this->name;
    	while(next != goal){
    		next = queue.front();
    		auto back = &queue.back();
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
		cout << endl << "Done Breadth-First Search" << endl << endl;
	} // End of Breadth-First
	
	void uniformCost(Node* goal){
		int count = 0, sum = 0;
		Node* next = nullptr;
		priority_queue<adjacent, vector<adjacent>, comp4PQueue> pq;
		vector<string> visited;
		for(adjacent x: adj){
			pq.push(x);
			visited.push_back(x.node->name);
		}
		printf("\nUniform Cost Search from %s to %s\n", this->name.c_str(), goal->name.c_str());
    	cout << this->name;
		while(!pq.empty()){
			next = pq.top().node;
			sum += pq.top().weight;
			pq.pop();
			cout << " -> " << next->name;
    		visited.push_back(next->name);
			for(adjacent x: next->adj){
    			if(find(visited.begin(), visited.end(), x.node->name) != visited.end()) continue;
    			pq.push(x);
			}
			if(next == goal) break;
			count++;
			if(count >= 30){
				cout << endl << "No solution Founded" << endl;
				break;
			}
		}
		cout << endl << "Done Uniform Cost Search with " << sum << " cost(s)" << endl << endl;
	} // End of Uniform Cost
	
	void greedyBestFirst(Node* goal){
		int count = 0, sum = 0;
		Node* next = nullptr;
		priority_queue<adjacent, vector<adjacent>, comp4Greedy> pq;
		vector<string> visited;
		for(adjacent x: adj){
			pq.push(x);
			visited.push_back(x.node->name);
		}
		printf("\nGreedy Best-First Search from %s to %s\n", this->name.c_str(), goal->name.c_str());
    	cout << this->name;
		while(!pq.empty()){
			next = pq.top().node;
			sum += pq.top().weight;
			pq.pop();
			cout << " -> " << next->name;
    		visited.push_back(next->name);
			for(adjacent x: next->adj){
    			if(find(visited.begin(), visited.end(), x.node->name) != visited.end()) continue;
    			pq.push(x);
			}
			if(next == goal) break;
			count++;
			if(count >= 30){
				cout << endl << "No solution Founded" << endl;
				break;
			}
		}
		cout << endl << "Done Greedy Best-First Search with " << sum << " cost(s)" << endl << endl;
	} // End of Greedy Best-First
	
	void aStar(Node* goal){
		int count = 0, sum = 0;
		Node* next = nullptr;
		priority_queue<adjacent, vector<adjacent>, comp4aStar> pq;
		vector<string> visited;
		for(adjacent x: adj){
			pq.push(x);
			visited.push_back(x.node->name);
		}
		printf("\nA* Search from %s to %s\n", this->name.c_str(), goal->name.c_str());
    	cout << this->name;
		while(!pq.empty()){
			next = pq.top().node;
			sum += pq.top().weight;
			pq.pop();
			cout << " -> " << next->name;
    		visited.push_back(next->name);
			for(adjacent x: next->adj){
    			if(find(visited.begin(), visited.end(), x.node->name) != visited.end()) continue;
    			pq.push(x);
			}
			if(next == goal) break;
			count++;
			if(count >= 30){
				cout << endl << "No solution Founded" << endl;
				break;
			}
		}
		cout << endl << "Done A* Search with " << sum << " cost(s)" << endl << endl;
	} // End of A*

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
	s->breadthFirst(f); 	// Expected Output: S -> A -> B -> C -> G -> D -> H -> E -> F
	s->uniformCost(f);		// Expected Output: S -> B -> A -> G -> D -> E -> F, sum = 16
	s->greedyBestFirst(f); 	// Expected Output: S -> C -> H -> D -> F, sum = 15
	s->aStar(f); 			// Expected Output: S -> A -> G -> D -> F, sum = 12
    
    return 0;
}
