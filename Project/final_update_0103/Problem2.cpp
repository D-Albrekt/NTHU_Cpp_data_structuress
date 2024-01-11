#include "basicDS.h"
#include <map>
#include <set>
#include <algorithm>
#include <limits.h>
#include <vector>
#include <stack>
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
	std::set<int> visited;
	std::stack<int> search_connections;
	search_connections.push(from);
	visited.insert(from);
	vector<graphEdge*> from_temp{tree};
	vector<graphEdge*> to_temp{tree};
	
	std::sort(begin(from_temp), end(from_temp), [](graphEdge* const& lhs, graphEdge* const&rhs){
		return lhs->vertex[0] < rhs->vertex[1];
	});
		std::sort(begin(to_temp), end(to_temp), [](graphEdge* const& lhs, graphEdge* const&rhs){
		return lhs->vertex[0] < rhs->vertex[1];
	});

	for (int i = 0; i < tree.size(); i++)
	{
		from = search_connections.top();
	 	search_connections.pop();
		for(graphEdge* gE : from_temp)
		{
			if (!visited.contains((gE)->vertex[1]) && gE->vertex[0] == from)
			{
				visited.insert(gE->vertex[1]);
				search_connections.push(gE->vertex[1]);
			}	
		}
		for(graphEdge* gE : to_temp)
		{
			if (!visited.contains((gE)->vertex[0]) && gE->vertex[1] == from)
			{
				visited.insert(gE->vertex[0]);
				search_connections.push(gE->vertex[0]);
			}	
		}
	}
	return visited.contains(to);
}


bool Problem2::kruskals_algo(Graph_Ext& reduced_graph, Tree& m_tree)
{
	int V = reduced_graph.V.size();
	vector<graphEdge*> selected_edges{};
	std::vector<graphEdge*>::iterator it = std::begin(reduced_graph.parent_edges);
	std::set<int> included_vertices{};
	int t = MC_requests[m_tree.id]->t;
	while ((selected_edges.size() < V-1) && (it != std::end(reduced_graph.parent_edges)))
	{
		graphEdge curr = *(*it);
		bool v_from{included_vertices.contains(curr.vertex[0])};
		bool v_to{included_vertices.contains(curr.vertex[1])};

		if (!v_from && !v_to)// Only else is needed, but this way could speed it uo since the is_cycle is a bit slow.
		{			
			selected_edges.push_back(*it);
			m_tree.E.push_back(treeEdge{curr.vertex[0], curr.vertex[1]});
			m_tree.ct = m_tree.ct + (t * (*it)->ce);
			included_vertices.insert(curr.vertex[0]);
			included_vertices.insert(curr.vertex[1]);
			(*it)->b = (*it)->b - t;
		}else if(v_from && !v_to)
		{
			selected_edges.push_back(*it);
			m_tree.E.push_back(treeEdge{curr.vertex[0], curr.vertex[1]});
			m_tree.ct = m_tree.ct + (t * (*it)->ce);
			included_vertices.insert(curr.vertex[1]);
			(*it)->b = (*it)->b - t;
		}else if(!v_from && v_to)
		{
			selected_edges.push_back(*it);
			m_tree.E.push_back(treeEdge{curr.vertex[0], curr.vertex[1]});
			m_tree.ct = m_tree.ct + (t * (*it)->ce);
			included_vertices.insert(curr.vertex[0]);
			(*it)->b = (*it)->b - t;
		}else{
			if (!is_cycle(selected_edges, curr.vertex[0], curr.vertex[1]))
			{
				selected_edges.push_back(*it);
				m_tree.E.push_back(treeEdge{curr.vertex[0], curr.vertex[1]});
				m_tree.ct = m_tree.ct + (t * (*it)->ce);
				(*it)->b = (*it)->b - t;
			}
		}
		it++;
		

	}
	if(m_tree.E.size() < (V - 1))
	{
		for (graphEdge* gE : selected_edges)
		{
			gE->b = gE->b + MC_requests[m_tree.id]->t;
		}
		m_tree.E.clear();
		m_tree.ct = 0;
		return false;
	}
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
		MTid = m_tree;
		return true;
	}
	MTid = m_tree;
	return false; 	/* You should return true or false according the insertion result */
}


void Problem2::update_w_trees(Graph &G, Forest &F)
{
	map<int, MC_request*>::iterator it;
	for (it = begin(MC_requests); it != end(MC_requests); it++)
	{
		if(it->second->waiting)
		{	
			Tree temp{};
			bool b{insert(it->second->id, it->second->s, it->second->D,it->second->t, G, temp)};
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
		update_graph(g_sorted_edges, curr_tree, -t); //The transaction cost of deleting a casting tree is neg.
		update_w_trees(g_sorted_edges, MTidForest);
	}
	MC_requests[id]->waiting = false;
	G = g_sorted_edges;
	MTidForest.size = MTidForest.trees.size();
	return;
}

void Problem2::rearrange(Graph &G, Forest &MTidForest) {
	/* Store your output graph and multicast tree forest into G and MTidForest
	   Note: Please include "all" active mutlicast trees in MTidForest. */

	/* Write your code here. */

	for (Tree tree : active_trees.trees)
	{
		if(MC_requests[tree.id]!= nullptr)
		{
			update_graph(g_sorted_edges, tree, -(MC_requests[tree.id]->t));
			MC_requests[tree.id]->waiting = true;
		}
	}
	active_trees.trees.clear();
	active_trees.size = 0;
	// Do insert from low to high, skip stopped.
	map<int, MC_request*>::iterator it;
	for (it = begin(MC_requests); it != end(MC_requests); it++)
	{
		if (it->second != nullptr)
		{
				Tree t;
				insert(it->second->id, it->second->s, it->second->D, it->second->t, g_sorted_edges, t);
		}
	}
	G=g_sorted_edges;
	MTidForest = active_trees;
	return;
}



