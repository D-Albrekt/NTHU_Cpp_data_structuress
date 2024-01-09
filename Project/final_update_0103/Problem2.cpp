#include "basicDS.h"
#include <array>
#include <algorithm>
#define Max_Calls 100000
/* You can add more functions or variables in each class. 
   But you "Shall Not" delete any functions or variables that TAs defined. */

void print_graph(Graph const& G)
{
	std::cout << "Format From - To, available b, limit be, cost ce" << std::endl;
	for (graphEdge const& gE : G.E)
	{
		std::cout << gE.vertex[0] << '-' << gE.vertex[1] << ", " << gE.b << ", " << gE.be << ", " << gE.ce << std::endl;
	}
}

class Problem2 {
public:

	Problem2(Graph G);  //constructor
	~Problem2();        //destructor
	bool insert(int id, int s, Set D, int t, Graph &G, Tree &MTid);
	void stop(int id, Graph &G, Forest &MTidForest);
	void rearrange(Graph &G, Forest &MTidForest);
private:
	//Helper functions
	Graph constrained_graph(Graph const& g, int t, Set D);
	int min_cost(int cost[], bool included[], int size);
	void update_edge_cost(Graph const& reduced_graph, bool included[], int cost[], int parent[],  int curr);
	bool prims_algo(Graph const& reduced_graph, Tree& m_tree); //creates minimal spanning tree.
	void update_graph(Graph &G,Tree & m_tree, int t);
	void update_w_trees(Graph &G, Forest &F);

	
	//Datamembers
	Forest active_trees;
	struct MC_request{
		int id;
		int s;
		Set D;
		int t;
		bool waiting; // if true then request is waiting.
		bool active;
	};
	std::array<MC_request*, Max_Calls> MC_requests;

};

Problem2::Problem2(Graph G) : active_trees{}, MC_requests{} {
	/* Write your code here. */
	
}

Problem2::~Problem2() {
	/* Write your code here. */

}


Graph Problem2::constrained_graph(Graph const& og_g, int t, Set D)
{
	Graph g;
	for (int v: og_g.V) {
		if (std::find(std::begin(D.destinationVertices),std::end(D.destinationVertices), v) != (std::end(D.destinationVertices)))
		{
			g.V.push_back(v);
		}
	}
	for (graphEdge e: og_g.E)
	{
		if(e.b >= t)
		{
			if (std::find(std::begin(D.destinationVertices),std::end(D.destinationVertices), e.vertex[0]) != std::end(D.destinationVertices) && 
			(std::find(std::begin(D.destinationVertices),std::end(D.destinationVertices), e.vertex[1]) != std::end(D.destinationVertices)))
			{
							g.E.push_back(e);
			}
		}
	} 
	return g;
}
int Problem2::min_cost(int cost[], bool included[], int size){
	int min_value = INT_MAX;
	int min_index;
 
    for (int v = 0; v < size; v++)
        if (included[v] == false && cost[v] < min_value)
        {
			min_value = cost[v];
			min_index = v;
		} 
    return min_index;
}
void Problem2::update_edge_cost(Graph const& reduced_graph, bool included[], int cost[], int parent[], int curr)
{
	for (graphEdge e: reduced_graph.E)
	{
		if((e.vertex[0] == (curr + 1) && included[e.vertex[1] - 1]== false && e.ce < cost[e.vertex[1] - 1])) //If edge is v - u
		{
			parent[e.vertex[1] - 1] = curr;
			cost[e.vertex[1] - 1] = e.ce;
		}
		else if((e.vertex[1] == (curr + 1) && included[e.vertex[0] - 1] == false && e.ce < cost[e.vertex[0] - 1])) //If edge is u - v
		{
			parent[e.vertex[0] - 1] = curr;
			cost[e.vertex[0] - 1] = e.ce;
		}
	}
}
bool Problem2::prims_algo(Graph const& reduced_graph, Tree& m_tree)
{
	int source{m_tree.s - 1};
	int V = reduced_graph.V.size();
	bool included[V]; //An array with all included elements. 
	std::fill(included, included + V, false); //Nothing included from start
	int cost[V]; //The cost to reach each vertex
	std::fill(cost, cost + V, INT_MAX); //Init cost is infinite.
	int parent[V];
	parent[source] = -1;
	cost[source] = 0; //Cost to itself is zero, so this node is always chosen first.
	//Create parent & set init values. Determine what index to worked with.

	for (int edges = 0; edges < (V - 1); edges++)//Needs V-1 edges to connect V vertices.
	{
		int u = min_cost(cost, included, V); //min cost return index with mincost
		std::cout << "u is: " << u << std::endl;
		if (u < -1 || u > 100) {return false;} 
		included[u] = true; //  include min cost.
		update_edge_cost(reduced_graph, included, cost, parent, u);
	}
	for(int vertex = 0; vertex < V; vertex++)
	{
		if(cost[vertex] > 100)
		{
			return false;
		}
	}
	for (int vertex = 0; vertex < V; vertex++)
	{
		if (parent[vertex] != -1 && !(parent[vertex] < -1 || parent[vertex] > 100))
		{
			m_tree.V.push_back(vertex);
			if (vertex > parent[vertex])
			{
				m_tree.E.push_back(treeEdge{parent[vertex], vertex});
			}else{
				m_tree.E.push_back(treeEdge{vertex, parent[vertex]});
			}
		}
	}
	return true;
}
void Problem2::update_graph(Graph &G,Tree& m_tree, int t)
{		
	for (treeEdge mt : m_tree.E)
	{	
		for(graphEdge& gE: G.E)
		{
			if ((gE.vertex[0] == mt.vertex[0] + 1 && gE.vertex[1] == mt.vertex[1] + 1)
			|| (gE.vertex[1] == mt.vertex[0] + 1 && gE.vertex[0] == mt.vertex[1] + 1))
			{
				gE.b = gE.b - t;
				m_tree.ct = m_tree.ct + (t * gE.ce);
			}
		}
	}
}

bool Problem2::insert(int id, int s, Set D, int t, Graph &G, Tree &MTid) {
	/* Store your output graph and multicast tree into G and MTid */
	
	/* Write your code here. */
	std::cout << "-------------Start of insert-----------------" << std::endl;
	if(MC_requests[id] == nullptr)
	{
		MC_requests[id] = new MC_request{id, s, D, t, true, true}; //Init request as noncomplete
	} 
	Tree m_tree{};
	m_tree.s = s;
	m_tree.V.push_back(s - 1);
	m_tree.id = id;

	Graph reduced_graph = constrained_graph(G, t, D); //creates a graph that only contains the edges with enough bandwith and dest vertices
	if(prims_algo(reduced_graph, m_tree)) //creates minimal spanning tree.
	{
		update_graph(G, m_tree, t); //reduces the bandwith of the used edges.
		MC_requests[id]->waiting = false;
		active_trees.trees.push_back(m_tree);
		active_trees.size++;
		return true;
	}
	return false; 	/* You should return true or false according the insertion result */
}


void Problem2::update_w_trees(Graph &G, Forest &F)
{
	for (int i = 1; i < MC_requests.size(); i++)
	{
		if(MC_requests[i] == nullptr) {break;}
		if(MC_requests[i]->waiting)
		{	
			Tree temp{};
			bool b{insert(MC_requests[i]->id, MC_requests[i]->s, MC_requests[i]->D,MC_requests[i]->t, G, temp)};
			if (b)
			{
				F.trees.push_back(temp);
			}
		}

	}
}
void Problem2::stop(int id, Graph &G, Forest &MTidForest) {
	/* Store your output graph and multicast tree forest into G and MTidForest
	   Note: Please "only" include mutlicast trees that you added nodes in MTidForest. */
	
	/* Write your code here. */

	std::cout << "------------- Start of Stop ------------------" << std::endl;
	MC_requests[id]->active = false;
	Tree curr_tree;
	if(!MC_requests[id]->waiting)
	{
		for (Tree& tree : active_trees.trees)
		{
			if (tree.id == id)
			{
				curr_tree = tree;
				break;
			}
		}
	
		int t = MC_requests[id]->t; //The transaction cost of deleting a casting tree is neg.
		update_graph(G, curr_tree, -t); //The transaction cost of deleting a casting tree is neg.
		update_w_trees(G, MTidForest);
	}
	MC_requests[id]->waiting = false;
	return;
}

void Problem2::rearrange(Graph &G, Forest &MTidForest) {
	/* Store your output graph and multicast tree forest into G and MTidForest
	   Note: Please include "all" active mutlicast trees in MTidForest. */

	/* Write your code here. */

	print_graph(G);
	for (Tree tree : active_trees.trees)
	{
		if(MC_requests[tree.id]->active)
		{
			update_graph(G, tree, -(MC_requests[tree.id]->t));
			MC_requests[tree.id]->waiting = true;
		}
	}
	active_trees.trees.clear();
	active_trees.size = 0;
	print_graph(G);
	// Do insert from low to high, skip stopped.
	for(int i = 0; i < MC_requests.size(); i++)
	{
		if (MC_requests[i] != nullptr)
		{
			if (MC_requests[i]->active)
			{
				Tree t;
				insert(MC_requests[i]->id, MC_requests[i]->s, MC_requests[i]->D, MC_requests[i]->t, G, t);
				MTidForest.trees.push_back(t);
				MTidForest.size++;
			}
		}
	}
	return;
}
