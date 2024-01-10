#include "basicDS.h"
#include <map>
#include <set>
#include <algorithm>
#include <limits.h>
#include <vector>
#include<bits/stdc++.h>
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
bool GFG_DFS(vector<graphEdge*>  const& tree, int from, int to);

class Problem2 {
public:

	Problem2(Graph G);  //constructor
	~Problem2();        //destructor
	bool insert(int id, int s, Set D, int t, Graph &G, Tree &MTid);
	void stop(int id, Graph &G, Forest &MTidForest);
	void rearrange(Graph &G, Forest &MTidForest);
private:
	//Datamembers
	Graph g_sorted_edges;
	Forest active_trees;
	struct MC_request{
		int id;
		int s;
		Set D;
		int t;
		bool waiting; // if true then request is waiting.
		bool active;
	};
	std::map<int, MC_request*> MC_requests;
	struct Graph_Ext : Graph
	{
		vector<graphEdge*> parent_edges;
	};
	
	//Helper functions
	Graph constrained_graph(Graph & og_g, Graph_Ext & g, int t, Set D);
	bool kruskals_algo(Graph_Ext& reduced_graph, Tree& m_tree); //creates minimal spanning tree.
	void update_graph(Graph &G,Tree & m_tree, int t);
	void update_w_trees(Graph &G, Forest &F);
	bool is_cycle(vector<graphEdge*> const& tree, int from, int to);


	


};

Problem2::Problem2(Graph G) : active_trees{}, MC_requests{}, g_sorted_edges{G} {
	std::sort(begin(g_sorted_edges.E), end(g_sorted_edges.E), [](graphEdge const&lhs, graphEdge const&rhs){
		return lhs.ce < rhs.ce;
	});
}

Problem2::~Problem2() {
	/* Write your code here. */

}


Graph Problem2::constrained_graph(Graph& og_g, Graph_Ext& g, int t, Set D)
{
	for (int v: og_g.V) {
		if (std::find(std::begin(D.destinationVertices),std::end(D.destinationVertices), v) != (std::end(D.destinationVertices)))
		{
			g.V.push_back(v);
		}
	}
	for (graphEdge& e: og_g.E)
	{
		if(e.b >= t)
		{
			if (std::find(std::begin(D.destinationVertices),std::end(D.destinationVertices), e.vertex[0]) != std::end(D.destinationVertices) && 
			(std::find(std::begin(D.destinationVertices),std::end(D.destinationVertices), e.vertex[1]) != std::end(D.destinationVertices)))
			{
							g.parent_edges.push_back(&e);
			}
		}
	} 
	return (g);
}

bool Problem2::is_cycle(vector<graphEdge*> const& tree, int from, int to)
{
	GFG_DFS(tree, from, to);
	return true;
}


bool Problem2::kruskals_algo(Graph_Ext& reduced_graph, Tree& m_tree)
{
	/* 
	Needs to be reimplemented, 
	Now the source node is fucking it.
	Maybe faster way to solve it? 
	Kruskals?
	
	*/

	int V = reduced_graph.V.size();
	vector<graphEdge*> selected_edges{};
	std::vector<graphEdge*>::iterator it = std::begin(reduced_graph.parent_edges);
	std::set<int> included_vertices{};
	for (graphEdge* gE : reduced_graph.parent_edges)
	{
		std::cout << " reduced edges "<<  gE->vertex[0] << '-' << gE->vertex[1] << std::endl;
	}
	int i = 0;
	while ((selected_edges.size() < V-1) && (it != std::end(reduced_graph.parent_edges)))
	{
		graphEdge curr = *(*it);
		bool v_from{included_vertices.contains(curr.vertex[0])};
		bool v_to{included_vertices.contains(curr.vertex[1])};

		if (!v_from && !v_to)// && curr.vertex[1])
		{			
			selected_edges.push_back(*it);
			m_tree.E.push_back(treeEdge{curr.vertex[0], curr.vertex[1]});
			included_vertices.insert(curr.vertex[0]);
			included_vertices.insert(curr.vertex[1]);
			(*it)->b = (*it)->b - MC_requests[m_tree.id]->t;
		}else if(v_from && !v_to)
		{
			selected_edges.push_back(*it);
			m_tree.E.push_back(treeEdge{curr.vertex[0], curr.vertex[1]});
			included_vertices.insert(curr.vertex[1]);
			(*it)->b = (*it)->b - MC_requests[m_tree.id]->t;
		}else if(!v_from && v_to)
		{
			selected_edges.push_back(*it);
			m_tree.E.push_back(treeEdge{curr.vertex[0], curr.vertex[1]});
			included_vertices.insert(curr.vertex[0]);
			(*it)->b = (*it)->b - MC_requests[m_tree.id]->t;
		}else{
			if (!is_cycle(selected_edges, curr.vertex[0], curr.vertex[1]))
			{
				selected_edges.push_back(*it);
				m_tree.E.push_back(treeEdge{curr.vertex[0], curr.vertex[1]});
				(*it)->b = (*it)->b - MC_requests[m_tree.id]->t;

			}
		}
		it++;
		

	}
	std::cout << "Selected edges, size then edges : " << m_tree.E.size() << std::endl;
	for (graphEdge* gE : selected_edges)
	{
		std::cout << gE->vertex[0] << '-' << gE->vertex[1] << std::endl;
	}
	std::cout << "---------------------------------------------------" << std::endl;

	if(m_tree.E.size() < (V - 1))
	{
		for (graphEdge* gE : selected_edges)
		{
			gE->b = gE->b + MC_requests[m_tree.id]->t;
		}
		m_tree.E.clear();
		std::cout << "pop" << std::endl;
		print_graph(g_sorted_edges);
		return false;
	}
	print_graph(g_sorted_edges);
	return true;
}
void Problem2::update_graph(Graph &G,Tree& m_tree, int t)
{		
	for (treeEdge const& mt : m_tree.E)
	{	
		for(graphEdge& gE: G.E)
		{
			if ((gE.vertex[0] == mt.vertex[0] && gE.vertex[1] == mt.vertex[1])
			|| (gE.vertex[1] == mt.vertex[0] && gE.vertex[0] == mt.vertex[1]))
			{
				gE.b = gE.b - t;
				m_tree.ct = m_tree.ct + (t * gE.ce);
			}
		}
	}
}

bool Problem2::insert(int id, int s, Set D, int t, Graph &G, Tree &MTid) {
	/* Store your output graph and multicast tree into G and MTid */
	if(MC_requests[id] == nullptr)
	{
		MC_requests[id] = new MC_request{id, s, D, t, true, true}; //Init request as noncomplete
	} 
	Tree m_tree{};
	m_tree.s = s;
	m_tree.V.push_back(s);
	m_tree.id = id;
	if (std::find(std::begin(D.destinationVertices),std::end(D.destinationVertices), s) == (std::end(D.destinationVertices)))
	{
		D.destinationVertices.push_back(s);
	}
	Graph_Ext reduced_graph;
	constrained_graph(g_sorted_edges, reduced_graph, t, D); //creates a graph that only contains the edges with enough bandwith and dest vertices
	if(kruskals_algo(reduced_graph, m_tree)) //creates minimal spanning tree.
	{
		//update_graph(G, m_tree, t); //reduces the bandwith of the used edges.
		MC_requests[id]->waiting = false;
		active_trees.trees.push_back(m_tree);
		active_trees.size++;
		G = g_sorted_edges;
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



// A utility function to add an edge in an
// undirected graph.
void addEdge(vector<int> adj[], int u, int v)
{
    adj[u].push_back(v);
    adj[v].push_back(u);
}
 
// A utility function to do DFS of graph
// recursively from a given vertex u.
void DFSUtil(int u, vector<int> adj[],
                    vector<bool> &visited)
{
    visited[u] = true;
    cout << u << " ";
    for (int i=0; i<adj[u].size(); i++)
        if (visited[adj[u][i]] == false)
            DFSUtil(adj[u][i], adj, visited);
}
 
// This function does DFSUtil() for all 
// unvisited vertices.
void DFS(vector<int> adj[], int V)
{
    vector<bool> visited(V, false);
    for (int u=0; u<V; u++)
        if (visited[u] == false)
            DFSUtil(u, adj, visited);
}
 
// Driver code
bool GFG_DFS(vector<graphEdge*> const& tree, int from , int to) 
{
	int max_V = 101;
	// The below line may not work on all
    // compilers.  If it does not work on
    // your compiler, please replace it with
    // following
    // vector<int> *adj = new vector<int>[V];
    std::vector<int> adj[max_V];//Max amount ofvertices
 
    // Vertex numbers should be from 0 to 4.
	for (graphEdge* gE : tree)
	{
		    addEdge(adj, gE->vertex[0], gE->vertex[1]);
	}

    DFS(adj, max_V);
	return false;
}