#include<iostream>
#define vertexNumber 8
using namespace std;
 
class Graph{
    private:
        int adjacencyMatrix[vertexNumber][vertexNumber];
        bool* visited;
    public:
        Graph();
        void DFS(const int v);
        void DFS_visit(const int v);
        void printVertex(int v){
            // This function is just used to guarantee that you won't 
            // output the wrong format
            cout<<v<<" ";
        }
        bool isDirected();
}; 
Graph::Graph(){
    for(int i=0;i<vertexNumber;i++){
        for(int j=0;j<vertexNumber;j++){
            adjacencyMatrix[i][j]=0;
        }
    }
    adjacencyMatrix[0][2]=1; adjacencyMatrix[1][0]=1;
    adjacencyMatrix[1][4]=1; adjacencyMatrix[2][5]=1;
    adjacencyMatrix[2][6]=1; adjacencyMatrix[3][1]=1;
    adjacencyMatrix[4][7]=1; adjacencyMatrix[6][7]=1;
    adjacencyMatrix[7][3]=1; adjacencyMatrix[7][5]=1;
}
bool Graph::isDirected(){
    for (int i = 0; i < vertexNumber; i++)
    {
        for(int j = 0; i < vertexNumber; j++)
        {
            {
                if(adjacencyMatrix[i][j] != adjacencyMatrix[j][i])
                {
                    return true;
                }
            }
        }
    }
    return false;
}
void Graph::DFS(const int v){
    // Input v is used to set the start vertex
    visited = new bool[vertexNumber];
    fill(visited, visited + vertexNumber, false);
    if (!visited[v])
    {
        DFS_visit(v);
    }
    delete [] visited;
}
void Graph::DFS_visit(const int v){
    // Visit all previously unvisited vertices that are reachable from vertex v
    // When you find a new vertex, print it out
    printVertex(v);
    visited[v] = true;
    for (int j = 0; j < vertexNumber; j++)
    {
        if(adjacencyMatrix[v][j] == 1 && !visited[j])
        {
            DFS_visit(j);
        }
    }
    
}
int main(){
    Graph g; 
    int start;
    cin>>start;
    if(g.isDirected()){
        cout<<"Directed!"<<endl;
    }else{
        cout<<"Undirected!"<<endl;
    }
    g.DFS(start); 
    return 0;
}