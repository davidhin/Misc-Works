#pragma once
#include <stack>
#include <list>
#include <iostream>
#include <climits>
#include "printing.cpp"
#include "Edge.cpp"
#include "minHeap.cpp"

class Graph
{
private:
	int vertices;
	std::list<Edge>* adj;

public:
	Graph(int V);
	// Utility
	void addEdge(int v, int w, int dist);
	void display();
	Graph transpose();
	int getWeight(int v1, int v2);
	~Graph() { delete[] adj; } 
	void DAGUtil(int start, int* visited, bool* acyclic, int level, int weight);
	void DFSUtil(int start, bool* visited, int level, int weight); 
	void BIPUtil(int start, int* visited, int colour, bool* ans, int level, int weight);
	void TSUtil(int* mark, std::list<int>* sorted, int node, bool display, int level);
	void HDAGUtil(int* mark, std::list<int>* sorted, int node, bool* fail);
	void SCCUtil(int start, int* scc, std::list<std::pair<int,int>>* metaRelation, int* metaIndex); 
	
	// Algorithms
	void DFS(int start); // Depth first search
	void BFS(int start, bool showTree); // Breadth first search
	int DIJ(int start, int shortestDistTo); // Dijkstra's Algorithm
	int BF(int start); // Bellman-Ford algorithm
	bool DAG(); // Testing acyclicity for directed graphs
	bool BIP(); // Testing bipartiteness
	std::list<int>* TS(bool display); // Topological sort
	void HDAG(); // Hamiltonian Path in DAG
	void SCC();
};

Graph::Graph(int verticesIn)
{
	vertices = verticesIn;
	adj = new std::list<Edge>[vertices];
}

/**************************************************************/
/*			             UTILITY                              */
/**************************************************************/

int Graph::getWeight(int v1, int v2)
{
	std::list<Edge>::iterator i; 
	for (i = adj[v1-1].begin(); i != adj[v1-1].end(); ++i)
	{
		if ((*i).toNode == v2) return (*i).weight;
		else return -1;
	}	
}

void Graph::addEdge(int v1, int v2, int weightIn = 1)
{
	Edge temp(v2, weightIn);
	adj[v1-1].push_back(temp); // v1 - 1
}

void Graph::display()
{
	for (int i = 0; i < vertices; i++)
	{
		std::cout << "Node " << i+1 << ": ";	 // i + 1
		printListW(adj[i]);
	}
	std::cout << std::endl;
}

Graph Graph::transpose()
{
	Graph g(vertices);
	for (int j = 0; j < vertices; j++)
	{
		std::list<Edge>::iterator i;
		for (i = adj[j].begin(); i != adj[j].end(); i++)
			g.addEdge((*i).toNode,j+1);	
	}
	return g;
}

/**************************************************************/
/*			           DEPTH-FIRST SEARCH     				  */
/**************************************************************/

void Graph::DFSUtil(int start, bool* visited, int level = 0, int weight = 0)
{
	// Mark current node as visited
	visited[start-1] = true;
	printTree(start, level, weight);

	// Recur for all vertices adjacent to vertex
	std::list<Edge>::iterator i;
	for (i = adj[start-1].begin(); i != adj[start-1].end(); ++i)
		if (!visited[(*i).toNode-1])
			{
				level++;
				DFSUtil((*i).toNode, visited, level, (*i).weight);
				level--;
			}
}

// Depth first search
void Graph::DFS(int start = 1)
{
	// Mark all vertices as not visited
	bool* visited = new bool[vertices];
	for (int i = 0; i < vertices; i++)
		visited[i] = false;
	
	// Call recursive function
	DFSUtil(start, visited);
}

/**************************************************************/
/*			         BREADTH-FIRST SEARCH      				  */
/**************************************************************/

// Breadth first search
void Graph::BFS(int start, bool showTree = 0)
{
	// Create array to hold levels of ith element in adj
	int* levels = new int[vertices], curLevel = 0;
	for (int i = 0; i < vertices; i++)\
		levels[i] = -1;
	
	// Create a queue for BFS
	std::list<int> queue;

	// Mark the level of the current node and enqueue
	levels[start - 1] = curLevel;
	if (showTree) printTree(start, curLevel);
	queue.push_back(start);

	// 'i' will be used to get adjacent vertices of vertex
	std::list<Edge>::iterator i;

	while (!queue.empty())
	{
		start = queue.front();
		curLevel = levels[start-1] + 1;
		queue.pop_front();

		// Get all adjacent vertices of start and add to queue 	
		for (i = adj[start-1].begin(); i != adj[start-1].end(); ++i)
		{
			if (levels[(*i).toNode-1] == -1)
			{	
				levels[(*i).toNode-1] = curLevel;
				if (showTree) printTree((*i).toNode, curLevel, (*i).weight);
				queue.push_back((*i).toNode);
			}
		}
	}

	// Print final highlighted array	
	if (showTree) std::cout << std::endl;
	for (int i = 0; i < vertices; i++)
		if (levels[i] == -1) std::cout << "\033[1;30m" << levels[i] << "\033[0m "; 
		else std::cout << "\033[1;39m" << levels[i] << "\033[0m ";
	std::cout << std::endl;
}


/**************************************************************/
/*			             DIJKSTRA'S          				  */
/**************************************************************/

int Graph::DIJ(int start = 1, int shortestDistTo = 0)
{
	// Create min priority queue
	MinHeap pqueue;
	
	// Create array to hold distances assigned to vertices
	int* dists = new int[vertices];
	for (int i = 0; i < vertices; i++)
		dists[i] = -1;
	// Determines whether the node has been visited
	bool vis[vertices] = {0};

	// Add the initial node with distance 0 to pqueue
	std::pair<int, int> temp(start, 0);
	dists[start-1] = 0;
	pqueue.push_back(temp);
	printArr(dists, vertices);
	std::cout << std::endl;
	
	// i will be used to get adjacent vertices of vertex
	std::list<Edge>::iterator i;
	
	while (!pqueue.empty()) 
	{
		// Assign minimum of queue to top and pop off
		std::pair<int, int> top = pqueue.front();
		pqueue.pop_front();

		// If visited, no point in exploring adjacent vertices	
		if (vis[top.first]) continue;
		vis[top.first] = true;
	
		std::cout << "Current Dist: " << top.second << std::endl;	
		std::cout << "Node " << top.first << ": ";	 // i + 1
		printListW(adj[top.first-1]);

		// for all vertices adjacent to top
		int* highlight = hlArray(vertices);
		for (i = adj[top.first-1].begin(); i != adj[top.first-1].end(); ++i)
		{
			temp.first = (*i).toNode;
			temp.second = (*i).weight + top.second;
			// If the new dist l(u,v) < old dist
			// Update distance array
 			// Insert node into pqueue
			if (!vis[temp.first] && temp.second < dists[temp.first-1] || dists[temp.first-1] == -1) 
			{ 
				dists[temp.first-1] = temp.second;
				highlight[temp.first-1] = 1; 
				pqueue.push_back(temp);
			}
		}
		printArr(dists, vertices, highlight);
 
		pqueue.display();
		std::cout << std::endl;
	}

	return dists[shortestDistTo - 1];
}


/**************************************************************/
/*			             BELLMAN-FORD          				  */
/**************************************************************/

// Bellman-Ford: returns -1 if no -ve weight cycle, else returns 1
int Graph::BF(int start = 1)
{	
	// Create array to hold distances assigned to vertices
	int* dists = new int[vertices], k = 1;
	for (int i = 0; i < vertices; i++)
		dists[i] = -1;
	
	// Determines whether the node has been visited
	bool vis[vertices] = {0};

	// Add the initial node with distance 0
	std::pair<int, int> temp(start, 0);
	dists[start-1] = 0;
	vis[0] = 1;
	
	// i will be used to get adjacent vertices of vertex
	std::list<Edge>::iterator i;
	
	// for all vertices adjacent to jth node
	bool update = 1; 
	while (update)
	{
		update = 0;
/**/	std::cout << "Iteration " << k << std::endl;
	
		for(int j = 0; j < vertices; j++)
		{
			int* highlight = hlArray(vertices); // cyan highlight
			int curDist = 0;

			// If the node has changed since last iteration,
			// perform update, else skip the node
			if (vis[j] == 1) curDist = dists[j];
			else continue;

			for (i = adj[j].begin(); i != adj[j].end(); ++i)
			{
				vis[j] = 0;
				temp.first = (*i).toNode;
				temp.second = (*i).weight + curDist;
				if (temp.second < dists[temp.first-1] || dists[temp.first-1] == -1) 
				{ 
					dists[temp.first-1] = temp.second;
					vis[temp.first-1] = 1;
					highlight[temp.first-1] = 1;  // cyan highlight
					update = 1; // dists has been updated
				}
			}
/**/		printArr(dists, vertices, highlight);
		}
		k++; if (k == vertices) break;
/**/	std::cout << std::endl;	
	}

	// Negative weight cycle check
	if (update == 1) return 1;
	else return -1;

//	printArr(dists, vertices);
}

/**************************************************************/
/*			             ACYCLICITY          				  */
/**************************************************************/

void Graph::DAGUtil(int start, int* visited, bool* acyclic, int level = 0, int weight = 0)
{
	// Mark current node as grey
	visited[start-1] = 1;
	printTree(start, level, weight);

	// Recur for all vertices adjacent to vertex
	std::list<Edge>::iterator i;
	for (i = adj[start-1].begin(); i != adj[start-1].end(); ++i)
		if (visited[(*i).toNode-1] != 2)
			{
				// If next node is grey, cycle exists
				if (visited[(*i).toNode-1] == 1) { *acyclic = false;  continue; }  
				level++;
				DAGUtil((*i).toNode, visited, acyclic, level, (*i).weight);
				level--;
			}

	// Mark node as black
	visited[start-1] = 2;
}

// Checking acyclicity: return true if graph does not contain cycle (is acyclic)
bool Graph::DAG()
{
	// 0 = white, 1 = grey, 2 = black
	// Mark all vertices as white
	int* visited = new int[vertices];
	for (int i = 0; i < vertices; i++)
		visited[i] = 0;
	
	bool* acyclic = new bool;
	// Call recursive function
	for (int i = 1; i <= vertices; i++)
	{
		*acyclic = true;
		if (visited[i-1] == 0)
		{ 
			DAGUtil(i, visited, acyclic); 
			if (*acyclic == false) return false;
		}
	}

	delete[] visited, acyclic;
	return true;
}

/**************************************************************/
/*			          TESTING BIPARTITENESS         		  */
/**************************************************************/

// colour: 1 = white, -1 = black
void Graph::BIPUtil(int start, int* visited, int colour, bool* ans, int level = 0, int weight = 0)
{
	// Mark current node as current colour (white or black)
	visited[start-1] = colour;
	printTree(start, level, weight);

	// Recur for all vertices adjacent to vertex
	std::list<Edge>::iterator i;
	for (i = adj[start-1].begin(); i != adj[start-1].end(); ++i)
	{
		// Graph not bipartite
		if (visited[(*i).toNode-1] == colour) 
		{
			*ans = false;
			return;
		}
	
		// If next node uncoloured, recurse over it	
		if (visited[(*i).toNode-1] == 0)
		{
			level++;
			BIPUtil((*i).toNode, visited, colour*-1, ans, level, (*i).weight);
			if (!(*ans)) return;
			level--;
		}
	}
}

bool Graph::BIP()
{
	// Mark all vertices as not visited
	int* visited = new int[vertices];
	for (int i = 0; i < vertices; i++)
		visited[i] = 0;

	// Points to whether it is bipartite	
	bool* ans = new bool;

	// Call recursive function
	for (int i = 0; i < vertices; i++)
	{
		*ans = true;	
		if (visited[i] == 0)
		{
			BIPUtil(i+1, visited, 1, ans);
			if(!(*ans)) return false;
		}
	}

	return true;
	std::cout << std::endl;
}

/**************************************************************/
/*			          TOPOLOGICAL SORT         				  */
/**************************************************************/

void Graph::TSUtil(int* mark, std::list<int>* sorted, int node, bool display, int level = 0)
{
	// Display help (not related to algo)
	if (display) printTree(node+1, level, 0);
	
	// If node is permanent, return
	if (mark[node] == 2) return;

	// If node is temp, this means not DAG
	if (mark[node] == 1) { return; }
	
	// Mark node as temporary
	mark[node] = 1;

	// Recur on each adjacent node
	std::list<Edge>::iterator i;
	for (i = adj[node].begin(); i != adj[node].end(); ++i)
	{
		level++;
		TSUtil(mark, sorted, (*i).toNode-1, display, level);	
		level--;
	}

	// Mark node as permanent
	mark[node] = 2;

	// Add node to head of sorted list
	sorted->push_front(node+1);
	
	if (display) std::cout << "Add " << node + 1 << " to list. \n";
	for (auto v : *sorted)
	if (display) std::cout << (v == node+1 ? "\033[1;33m" : "") << v << "\033[0m ";
	if (display) std::cout << std::endl;
}

std::list<int>* Graph::TS(bool display = true)
{
	// 0 = unmarked, 1 = temp mark, 2 = permenant mark
	int* mark = new int[vertices];
	for (int i = 0; i < vertices; i++)
		mark[i] = 0;
	std::list<int>* sorted = new std::list<int>;

	for (int i = 0; i < vertices; i++)
	{
		if (sorted->size() == vertices) break;
		if (mark[i] == 0) 
		{
			TSUtil(mark, sorted, i, display);
			if (display) std::cout << std::endl;
		} 
	}

	if (display) for (auto v : *sorted)
	std::cout << v << " ";
	if (display) std::cout << std::endl;
	delete[] mark;
	return sorted;
}

/**************************************************************/
/*			       HAMILTONIAN PATH IN DAG                    */
/**************************************************************/
/* Very similar to topological sort */

void Graph::HDAGUtil(int* mark, std::list<int>* sorted, int node, bool* fail)
{
	// If node is permanent, return
	if (mark[node] == 2) return;
	// If node is temp, this means not DAG 
	if (mark[node] == 1) { *fail = true; return; }
	
	// Mark node as temporary
	mark[node] = 1;

	// Recur on each adjacent node
	std::list<Edge>::iterator i;
	for (i = adj[node].begin(); i != adj[node].end(); ++i)
		HDAGUtil(mark, sorted, (*i).toNode-1, fail);	
	if (*fail) return;

	// Mark node as permanent
	mark[node] = 2;

	// If current node goes to start of sorted list 
	bool success = false;
	for (i = adj[node].begin(); i != adj[node].end(); ++i)
		if ((*i).toNode == sorted->front()) 
		{
			success = true; 
			break; 
		}

	// Else, a sink has been found which does not join to Hamiltonian path
	if (!success && sorted->size() > 0) 
	{
		std::cout << "FAIL";
		*fail = true;
		return;
	}

	// Add node to Hamiltonian path
	std::cout << "Added " << node + 1 << " to Hamiltonian Path. ";
	sorted->push_front(node+1);
	
	// Print
	for (auto v : *sorted)
	std::cout << (v == node+1 ? "\033[1;33m" : "") << v << "\033[0m ";
	std::cout << std::endl;
}

void Graph::HDAG()
{
	// 0 = unmarked, 1 = temp mark, 2 = permenant mark
	int* mark = new int[vertices];
	for (int i = 0; i < vertices; i++)
		mark[i] = 0;
	std::list<int>* sorted = new std::list<int>;
	bool* fail = new bool;
	*fail = false;

	// For every node, run HDAGUtil	
	for (int i = 0; i < vertices; i++)
	{
		if (*fail) break;
		if (sorted->size() == vertices) break;
		if (mark[i] == 0) 
		{
			HDAGUtil(mark, sorted, i, fail);
			if (*fail) std::cout << std::endl;
		} 
	}

	// Final print
	for (auto v : *sorted)
	std::cout << v << " ";
	std::cout << std::endl;

	std::cout << "\n---------------------------\n\n";

	delete fail;
	delete[] mark, sorted;
}

/**************************************************************/
/*			       STRONGLY CONNECTED COMPONENTS              */
/**************************************************************/
	
void Graph::SCCUtil(int start, int* scc, 
		std::list<std::pair<int, int>>* metaRelation, int* metaIndex) 
{
	// Mark current node as visited
	scc[start] = *metaIndex;

	// Recur for all vertices adjacent to vertex
	std::list<Edge>::iterator i;
	for (i = adj[start].begin(); i != adj[start].end(); ++i)
	{
		if (scc[(*i).toNode-1] == -1)
			SCCUtil((*i).toNode-1, scc, metaRelation, metaIndex);
		else if (*metaIndex != scc[(*i).toNode-1])
		{
			std::pair<int, int> temp(scc[(*i).toNode-1], *metaIndex);
			metaRelation->push_back(temp);
		}
	}
}

//http://rosalind.info/glossary/algo-strongly-connected-component/ 
void Graph::SCC()
{
	// Topological sort
	std::list<int>* sorted = this->TS(false);
	
	// Hold edges between meta components
	std::list<std::pair<int, int>>* metaRelation = new std::list<std::pair<int,int>>;
	
	// Hold which metacomponent a node belongs to
	int* scc = new int[vertices], *mIndex = new int; 
	*mIndex = 1;
	for (int i = 0; i < vertices; i++)
		scc[i] = -1;
	
	// Print
	std::cout << "Topologically sorted: ";
	for (auto v : *sorted)
	std::cout << v << " ";
	std::cout << std::endl;

	// Get a transposed version of graph
	Graph transposed = transpose();
	
	// Recursive function
	while (!sorted->empty())
	{
		if (scc[sorted->front()-1] == -1) 
		{
			std::cout << "DFS on transposed from " << sorted->front() << ": ";
			transposed.SCCUtil(sorted->front()-1, scc, metaRelation, mIndex);
			*mIndex += 1;
			printArr2(scc, vertices, *mIndex-1);
		}
		sorted->pop_front();		
	}
	
	// Metagraph
	std::cout << "\nMeta Graph:\n";
	Graph metaGraph(*mIndex-1);
	std::list<std::pair<int, int> >::iterator i;
	for (i = metaRelation->begin(); i != metaRelation->end(); i++)
		metaGraph.addEdge((*i).first, (*i).second);
	metaGraph.display();
	
	delete sorted, mIndex, metaRelation;
	delete[] scc;
}


