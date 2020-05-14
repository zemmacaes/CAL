/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <stack>
using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;


/****************** Provided structures  ********************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // list of outgoing edges
	bool visited;          // auxiliary field used by dfs and bfs
	int indegree;          // auxiliary field used by topsort
	bool processing;       // auxiliary field used by isDAG

	void addEdge(Vertex<T> *dest, double w);
	bool removeEdgeTo(Vertex<T> *d);
public:
	Vertex(T in);

    Vertex(Vertex<T> const &v);

    friend class Graph<T>;
};

template <class T>
class Edge {
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

	void dfsVisit(Vertex<T> *v,  vector<T> & res) const;
	Vertex<T> *findVertex(const T &in) const;
	bool dfsIsDAG(Vertex<T> *v) const;
//	void topVisit(Vertex<T> *v, vector<T> & res) const;
public:
	int getNumVertex() const;
	bool addVertex(const T &in);
	bool removeVertex(const T &in);
	bool addEdge(const T &sourc, const T &dest, double w);
	bool removeEdge(const T &sourc, const T &dest);
	vector<T> dfs() const;
	vector<T> bfs(const T &source) const;
	vector<T> topsort() const;

	int maxNewChildren(const T &source, T &inf) const;
	bool isDAG() const;

	Graph(Graph const &g);
    Graph() {}
};

/****************** Provided constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(T in): info(in), visited(false), indegree(0) {}

template <class T>
Edge<T>::Edge(Vertex<T> *d, double w): dest(d), weight(w) {}


template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/****************** 1a) addVertex ********************/

/*
 *  Adds a vertex with a given content/info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in) {
	// TODO (4 lines)
	// HINT: use the findVertex function to check if a vertex already exists
	if (findVertex(in) == nullptr) {
        this->vertexSet.push_back(new Vertex<T>(in));
        return true;
	}
	return false;
}

/****************** 1b) addEdge ********************/

/*
 * Adds an edge to a graph (this), given the contents of the source (sourc) and
 * destination (dest) vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, double w) {
	// TODO (6 lines)
	// HINT: use findVertex to obtain the actual vertices
	// HINT: use the next function to actually add the edge
	Vertex<T> *v1, *v2;
	v1 = findVertex(sourc);
	v2 = findVertex(dest);
	if (v1 == nullptr || v2 == nullptr) return false;
	v1->addEdge(v2, w);

	return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(Vertex<T> *d, double w) {
    d->indegree++;
	this->adj.push_back(Edge<T>(d, w));
}


/****************** 1c) removeEdge ********************/

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
	// TODO (5 lines)
	// HINT: Use "findVertex" to obtain the actual vertices.
	// HINT: Use the next function to actually remove the edge.
    Vertex<T> *v1, *v2;
    v1 = findVertex(sourc);
    v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr) return false;
    v2->indegree--;
    return v1->removeEdgeTo(v2);

}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdgeTo(Vertex<T> *d) {
	// TODO (6 lines)
	// HINT: use an iterator to scan the "adj" vector and then erase the edge.

    auto it = this->adj.begin();
	for (; it != this->adj.end(); it++) {
	    if (it->dest == d) {
	        it = this->adj.erase(it);
	        return true;
	    }
	}
	return false;
}

template<class T>
Vertex<T>::Vertex(Vertex<T> const &v) {
    this->info = v.info;
    for (auto edge : v.adj) {
        this->addEdge(edge.dest, edge.weight);
    }
    this->visited = v.visited;
    this->indegree = v.indegree;
    this->processing = v.processing;
}


/****************** 1d) removeVertex ********************/

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
	// TODO (10 lines)
	// HINT: use an iterator to scan the "vertexSet" vector and then erase the vertex.
	// HINT: take advantage of "removeEdgeTo" to remove incoming edges.
	Vertex<T> *v = findVertex(in);
	if (v == nullptr) return false;
	auto it = this->vertexSet.begin();
	for (; it != this->vertexSet.end(); it++) {
        (*it)->removeEdgeTo(v);
        if ((*it) == v) it = this->vertexSet.erase(it);
	}
	return true;
}


/****************** 2a) dfs ********************/

/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::dfs() const {
	// TODO (7 lines)
	vector<T> res;
    auto it = this->vertexSet.begin();

	for (; it != this->vertexSet.end(); it++) {
        dfsVisit(*it, res);
	}

	for (auto v : this->vertexSet) {
	    v->visited = false;
	}
	return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Updates a parameter with the list of visited node contents.
 */
template <class T>
void Graph<T>::dfsVisit(Vertex<T> *v, vector<T> & res) const {
    if (v->visited) return;
    res.push_back(v->info);
    v->visited = true;

    Vertex<T> *cur;
    for (auto edge : v->adj) {
        cur = edge.dest;
        dfsVisit(cur, res);
    }
}

/****************** 2b) bfs ********************/

/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 * Follows the algorithm described in theoretical classes.
 */
template <class T>
vector<T> Graph<T>::bfs(const T & source) const {
	// TODO (22 lines)
	// HINT: Use the flag "visited" to mark newly discovered vertices .
	// HINT: Use the "queue<>" class to temporarily store the vertices.
	vector<T> res;
	queue<Vertex<T> *> auxQueue;
	if (this->vertexSet.empty()) return vector<T>();

	auxQueue.push(this->vertexSet[0]);
	Vertex<T> * cur;
	while (!auxQueue.empty()) {
	    cur = auxQueue.front();
	    if (!cur->visited) {
            cur->visited = true;
            for (auto edge : cur->adj) {
                auxQueue.push(edge.dest);
            }
	        res.push_back(cur->info);
	    }
	    auxQueue.pop();
	}

	return res;
}

/****************** 2c) toposort ********************/

/*
 * Performs a topological sorting of the vertices of a graph (this).
 * Returns a vector with the contents of the vertices by topological order.
 * If the graph has cycles, returns an empty vector.
 * Follows the algorithm described in theoretical classes.
 */

template<class T>
vector<T> Graph<T>::topsort() const {
	// TODO (26 lines)
	vector<T> res;
	queue<Vertex<T> *> aux;
	Graph<T> copy(*this);
    for (auto vertex : copy.vertexSet) {
	    if (vertex->indegree == 0) aux.push(vertex);
	}
    while (!aux.empty()) {
        Vertex<T> * cur = aux.front();
        aux.pop();
        res.push_back(cur->info);
        for (auto edge : cur->adj) {
            edge.dest->indegree--;
            if (edge.dest->indegree == 0) {
                aux.push(edge.dest);
            }
        }
    }
    if (res.size() != this->vertexSet.size()) return vector<T>();
	return res;
}

//template <class T>
//void Graph<T>::topVisit(Vertex<T> *v, vector<T> & res) const {
//    if (v->visited) {
////        res.push_back(T());
//        return;
//    }
//
//    res.push_back(v->info);
//    v->visited = true;
//
//    Vertex<T> *cur;
//    for (auto edge : v->adj) {
//        cur = edge.dest;
//        topVisit(cur, res);
//        if (res.back() == T())
//            return;
//    }
//}

/****************** 3a) maxNewChildren (HOME WORK)  ********************/

/*
 * Performs a breadth-first search in a graph (this), starting
 * from the vertex with the given source contents (source).
 * During the search, determines the vertex that has a maximum number
 * of new children (adjacent not previously visited), and returns the
 * contents of that vertex (inf) and the number of new children (return value).
 */

template <class T>
int Graph<T>::maxNewChildren(const T & source, T &inf) const {
	// TODO (28 lines, mostly reused)
	return 0;
}

/****************** 3b) isDAG   (HOME WORK)  ********************/

/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */

template <class T>
bool Graph<T>::isDAG() const {
	// TODO (9 lines, mostly reused)
	// HINT: use the auxiliary field "processing" to mark the vertices in the stack.
	return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent not yet visited, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */
template <class T>
bool Graph<T>::dfsIsDAG(Vertex<T> *v) const {
	// TODO (12 lines, mostly reused)
	return true;
}

template<class T>
Graph<T>::Graph(Graph const &g) {
    for (auto vertex : g.vertexSet) {
        this->addVertex(vertex->info);
    }
    for (auto vertex : g.vertexSet) {
        for (auto edge : vertex->adj) {
            this->addEdge(vertex->info, edge.dest->info, edge.weight);
        }
    }
}

#endif /* GRAPH_H_ */
