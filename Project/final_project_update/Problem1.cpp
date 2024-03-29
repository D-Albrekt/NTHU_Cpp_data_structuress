#include "basicDS.h"
#include <array>

/* You can add more functions or variables in each class. 
   But you "Shall Not" delete any functions or variables that TAs defined. */

#define Max_Calls 100000 //Max fc calls 

void print_graph(Graph const& G)
{
	std::cout << "Format From - To, available b, limit be, cost ce" << std::endl;
	for (graphEdge const& gE : G.E)
	{
		std::cout << gE.vertex[0] << '-' << gE.vertex[1] << ", " << gE.b << ", " << gE.be << ", " << gE.ce << std::endl;
	}
}

class Problem1 {
public:

	Problem1(Graph G);  //constructor
	~Problem1();        //destructor
	void insert(int id, int s, Set D, int t, Graph &G, Tree &MTid);
	void stop(int id, Graph &G, Forest &MTidForest);
	void rearrange(Graph &G, Forest &MTidForest);
private:
	int min_cost(int cost[], bool included[], int size);
	Graph constrained_graph(Graph const& g, int t);
	void prims_algo(Graph const& reduced_graph, Tree& m_tree); //creates minimal spanning tree.
	void update_graph(Graph &G,Tree & m_tree, int t);
	void update_edge_cost(Graph const& reduced_graph, bool included[], int cost[], int parent[],  int curr);
	
	void update_p_trees(Graph &G, Forest &F);
	//Data members
	Forest MT_forest;
	Forest MT_partial_forest;
	struct MC_request{
		int id;
		int s;
		Set D;
		int t;
		bool partial; // if true then req not fulfilled.
		bool active;
	};
	std::array<MC_request*, Max_Calls> MC_requests;
	
};

Problem1::Problem1(Graph G) : MT_forest{}, MT_partial_forest{}, MC_requests{} {}
Problem1::~Problem1() {
	/* Write your code here. */

}
Graph Problem1::constrained_graph(Graph const& og_g, int t)
{
	Graph g;
	for (int v: og_g.V) {
		g.V.push_back(v);
	}
	for (graphEdge e: og_g.E)
	{
		if(e.b >= t)
		{
			g.E.push_back(e);
		}
	} 
	return g;
}

//min_cost returns the index of the vertex with the min cost yet not-connected vertex.
int Problem1::min_cost(int cost[], bool included[], int size){
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
void Problem1::update_edge_cost(Graph const& reduced_graph, bool included[], int cost[], int parent[], int curr)
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
void Problem1::prims_algo(Graph const& reduced_graph, Tree& m_tree)
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
		if (u < -1 || u > 100) {break;} //There is no connecting edges
		included[u] = true; //  include min cost.
		update_edge_cost(reduced_graph, included, cost, parent, u);
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
}
void Problem1::update_graph(Graph &G,Tree& m_tree, int t)
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
void Problem1::insert(int id, int s, Set D, int t, Graph &G, Tree &MTid) {
	/* Store your output graph and multicast tree into G and MTid */
	std::cout << "-------------Start of insert-----------------" << std::endl;
	MC_requests[id] = new MC_request{id, s, D, t, true, true}; //Init request as partial
	Tree m_tree{};
	m_tree.s = s;
	m_tree.V.push_back(s - 1);
	m_tree.id = id;

	Graph reduced_graph = constrained_graph(G, t); //creates a graph that only contains the edges with enough bandwith
	prims_algo(reduced_graph, m_tree); //creates minimal spanning tree.
	update_graph(G, m_tree, t); //reduces the bandwith of the used edges.
	if(m_tree.E.size() == D.size - 1) 
	{
		MC_requests[id]->partial = false;
		MT_forest.trees.push_back(m_tree);
		MT_forest.size++;
	}
	else{
		MT_partial_forest.trees.push_back(m_tree);
		MT_partial_forest.size++;
	}
	
	std::cout << "Size of the " << id << ":s tree is " << m_tree.E.size() << " with the cost " << m_tree.ct << std::endl;
	return;
}

void Problem1::update_p_trees(Graph &G, Forest &F)
{
	for (Tree& mt : MT_partial_forest.trees)
	{
		int original_size = mt.E.size();
		Graph reduced_graph = constrained_graph(G, MC_requests[mt.id]->t);
		int V = reduced_graph.V.size();
		bool included[V]; //An array with all included elements. 
		std::fill(included, included + V, false); //Nothing included from start
		int cost[V]; //The cost to reach each vertex
		std::fill(cost, cost + V, INT_MAX); //Init cost is infinite.
		int parent[V];
		for (int V : mt.V)
		{
			included[V] = true;
			cost[V] = 0;
			parent[V] = -1;
		}
		for (int i = 0; i < V; i ++)
		{
			if (included[i]){
				update_edge_cost(reduced_graph, included, cost, parent, i);
			}
		}
		for (int V : G.V)
		{
			if (!included[V]){
				update_edge_cost(reduced_graph, included, cost, parent, V);
			}			
		}
		for (int edges = (mt.E.size() - 1); edges < (V - 1); edges++)//Needs V-1 edges to connect V vertices.
		{
			int u = min_cost(cost, included, V); //min cost return index with mincost
			if (u < -1 || u > 100) {break;} //There is no connecting edges
			included[u] = true; //  include min cost.
			update_edge_cost(reduced_graph, included, cost, parent, u);
		}
		update_graph(G, mt, -MC_requests[mt.id]->t);
		for (int vertex = 0; vertex < V; vertex++)
		{
			if (parent[vertex] != -1 && !(parent[vertex] < -1 || parent[vertex] > 100))
			{
				mt.V.push_back(vertex);
				if (vertex > parent[vertex])
				{
					mt.E.push_back(treeEdge{parent[vertex], vertex});
				}else{
					mt.E.push_back(treeEdge{vertex, parent[vertex]});
				}
			}
		}
		update_graph(G, mt, MC_requests[mt.id]->t);
		if (original_size < mt.E.size())
		{
			F.size++;
			F.trees.push_back(mt);
			std::cout << "Size of the " << mt.id << ":s tree is " << mt.E.size() << " Cost is: " << mt.ct << std::endl;

		}


	}
}
void Problem1::stop(int id, Graph &G, Forest &MTidForest) {
	std::cout << "------------- Start of Stop ------------------" << std::endl;
	/* Store your output graph and multicast tree forest into G and MTidForest
	   Note: Please "only" include mutlicast trees that you added nodes in MTidForest. */

	/* Write your code here. */
	MC_requests[id]->active = false;
	Tree curr_tree;
	if(MC_requests[id]->partial)
	{
		for (Tree& tree : MT_partial_forest.trees)
		{
			if (tree.id == id){curr_tree = tree;}
		}
	}else{
		for (Tree& tree : MT_forest.trees)
			{
				if (tree.id == id){curr_tree = tree;}
			}
	}
	int t = MC_requests[id]->t; //The transaction cost of deleting a casting tree is neg.
	update_graph(G, curr_tree, -t); //The transaction cost of deleting a casting tree is neg.
	update_p_trees(G, MTidForest);
	
	return;
}

void Problem1::rearrange(Graph &G, Forest &MTidForest) {
	std::cout << "_---------------- Start of Rearrange ------------------_" << std::endl;
	/* Store your output graph and multicast tree forest into G and MTidForest
	   Note: Please include "all" active mutlicast trees in MTidForest. */

	/* Write your code here. */
	// Stopp all - Free bandwith
	print_graph(G);
	for (Tree tree : MT_forest.trees)
	{
		if(MC_requests[tree.id]->active)
		{
			update_graph(G, tree, -(MC_requests[tree.id]->t));
			MC_requests[tree.id]->partial = true;
		}
	}
	for (Tree tree : MT_partial_forest.trees)
	{
		if(MC_requests[tree.id]->active)
		{
			update_graph(G, tree, -(MC_requests[tree.id]->t));
		}
	}
	MT_forest.trees.clear();
	MT_forest.size = 0;
	MT_partial_forest.trees.clear();
	MT_partial_forest.size = 0;
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
