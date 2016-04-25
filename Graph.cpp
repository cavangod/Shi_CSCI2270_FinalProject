#include "Graph.h"
#include <vector>
#include <iostream>
#include <queue>
#include <limits.h>
#include <algorithm>
using namespace std;

Graph::Graph()
{

}

Graph::~Graph()
{
    //dtor
}

void Graph::addEdge(string v1, string v2, int weight)
{
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == v1){
            for(int j = 0; j < vertices.size(); j++){
                if(vertices[j].name == v2 && i != j){
                    adjVertex av;
                    av.v = &vertices[j];
                    av.weight = weight;
                    vertices[i].adj.push_back(av);
                }
            }
        }
    }
}

void Graph::addVertex(string n)
{
    bool found = false;
    for(int i = 0; i < vertices.size(); i++){
        if(vertices[i].name == n){
            found = true;
            cout<<vertices[i].name<<" found."<<endl;
        }
    }
    if(found == false){
        vertex v;
        v.name = n;
        v.district = -1;
        v.visited = false;
        v.parent = NULL;
        v.ID = vertices.size();
        vertices.push_back(v);

    }
}

void Graph::displayEdges()
{
    for(int i = 0; i < vertices.size(); i++){
        cout<< vertices[i].district <<":" <<vertices[i].name<<"-->";
        for(int j = 0; j < vertices[i].adj.size(); j++){
            cout<<vertices[i].adj[j].v->name;
            if (j != vertices[i].adj.size()-1)
                cout<<"***";
        }
        cout<<endl;
    }
}

void Graph::assignDistricts()
{
    // Starting district num
    int distID = 1;
    // For each of the vertices
    for(int i = 0; i < vertices.size(); i++)
    {
        // Only consider a vertex that has not been assigned a district.
        if (vertices[i].district == -1)
        {
            // Run breadth first traversal and assign each node in the network to this district.
            BFTraversalLabel(vertices[i].name,distID);
            distID++;
        }

    }
}

void Graph::BFTraversalLabel(std::string startingCity, int distID)
{
  queue<vertex*> q;
  // Label all as unvisited.
  for(int i = 0; i < vertices.size(); i++)
  {
    vertices[i].visited = false;
  }
  // Find the starting node and enqueue it.
  for(int i = 0; i < vertices.size(); i++)
  {
      if (vertices[i].name == startingCity)
      {
          // set current vertex to be visited.
          vertices[i].visited = true;
          q.push(&vertices[i]);
          vertices[i].district = distID;
          break;
      }
  }
 // Now do the rest of the search.
 while (q.empty() != true)
 {
     vertex * u = q.front();
     q.pop();

     for(int i = 0; i < u->adj.size(); i++)
     {
         if (u->adj[i].v->visited == false)
         {
             u->adj[i].v->visited = true;
             u->adj[i].v->district = distID;
             q.push(u->adj[i].v);
         }
     }
 }
}

void Graph::shortestPath(std::string startingCity, std::string endingCity){
    for(int i = 0; i < vertices.size(); i++)
  {
    vertices[i].visited = false;
  }
    bool found = false;
    vertex * start = findVertex(startingCity);
    vertex * end = findVertex(endingCity);
    if (start == NULL || end == NULL)
    {
        cout << "One or more cities doesn't exist" << endl;
        return;
    }
    if (end->district != start->district)
    {
        cout << "No safe path between cities" << endl;
        return;
    }
    if (end->district == -1 || start->district == -1)
    {
        cout << "Please identify the districts before checking distances" << endl;
        return;
    }

    start->visited = true;
    start->distance = 0;
    queue<vertex*> q;
    q.push(start);
    vertex *foundVertex = NULL;
    while(q.empty()==false){
        vertex* n = q.front();
        q.pop();
        for(int x = 0; x < n->adj.size(); x++){
            if(n->adj[x].v->visited == false){
                n->adj[x].v->visited = true;
                n->adj[x].v->distance = n->distance + 1;
                n->adj[x].v->parent = n;
                if(n->adj[x].v->name == endingCity){
                    foundVertex = n->adj[x].v;
                    found = true;
                    break;
                }else{
                    q.push(n->adj[x].v);
                }
            }
        }
    }
    if(found == true){
        cout<<foundVertex->distance;
        vertex *temp = foundVertex;
        vector<string> names;
        while(temp != NULL){
            names.push_back(temp->name);
            temp = temp->parent;
        }
        for(int x = names.size()-1; x >= 0; x--){
            cout<<","<<names[x];
        }
        cout<<endl;
    }
}

void Graph::shortestDis(std::string startingCity, std::string endingCity){
    for(int i = 0; i < vertices.size(); i++)
  {
    vertices[i].visited = false;
  }
    vertex *start = new vertex;
    start = NULL;
    for (size_t i=0;i<vertices.size();i++){
        if(startingCity==vertices[i].name) start = &vertices[i];
    }
    //cout<<start->name;
    vertex *end = new vertex;
    end = NULL;
    for (size_t i=0;i<vertices.size();i++){
        if(endingCity==vertices[i].name) end = &vertices[i];
    }
    //cout<<end->name;
    if(start==NULL||end==NULL){
        cout << "One or more cities doesn't exist" << endl;
    }
    else if (start->district==-1||end->district==-1){
        cout << "Please identify the districts before checking distances" << endl;
    }
    else if(start->district!=end->district){
        cout << "No safe path between cities" << endl;
    }
    else{/*
        //cout<<"---------------------";
        for (size_t i=0;i<vertices.size();i++){
            vertices[i].visited = false;
            for (size_t y=1;y<vertices[i].adj.size();y++){
                vertices[i].adj[y].v->visited = false;
            }
        }*/
        start->visited = true;
        start->distance = 0;
        vector<vertex*> Queue;
        Queue.push_back(start);
        
        while(end->visited!=true){
            int min=100000;
            int dis=0;
            vertex *solved;
            vertex *n;
            vertex *find;
            //cout<<Queue.size()<<endl;
            for(int y = 0;y<Queue.size();y++){
                n = Queue[y];
                //cout<<n->name;
                for(int x = 0; x<n->adj.size();x++){
					//cout<<n->adj.size()<<endl;
                    //find = findVertex(n->adj[x].v->name);
                    find = n->adj[x].v;
                    if(find->visited!=true){
                        dis = n->adj[x].weight+n->distance;
                        cout<<dis<<endl;
                        if(dis<=min){
                            //solved = findVertex(n->adj[x].v->name);
                            solved = n->adj[x].v;
                            min = dis;
                            solved->previous = n;
                        }
                        if(n->adj[x].v->name == endingCity){
                            solved->distance = min;
                            solved->visited = true;
                            Queue.push_back(solved);
                            break;
                        }
                    }
                }
            }
            //cout<<solved->name;
            //cout<<"---------------------";
            //solved->previous = n;
            solved->distance = min;
            solved->visited = true;
            Queue.push_back(solved);
        }
        
        vertex *out = new vertex;
        int mun = 0;
        for(int x = 0;x<Queue.size();x++){
            if(Queue[x]->name==endingCity){
                out = Queue[x];
                mun = out->distance;
            }
        }
        
        std::vector<string> Queue1;
        Queue1.push_back(out->name);
        while(out->previous->name!=startingCity){
            for(int x = 0;x<Queue.size();x++){
                if(Queue[x]->name==out->previous->name){
                    out = Queue[x];
                    Queue1.push_back(out->name);
                }
            }
        }
        cout<<mun<<",";
        Queue1.push_back(startingCity);
        vector<string>::iterator iter;
        for( iter = Queue1.end()-1; iter != Queue1.begin(); iter-- )
        {
            cout << *iter <<",";
        }
        cout <<endingCity<<endl;
        
        
    }
}

void Graph::roundTrip(std::string startingCity){

}
vertex * Graph::findVertex(std::string name)
{
    for(int i = 0; i < vertices.size(); i++)
    {
        if (vertices[i].name == name)
            return &vertices[i];
    }
    return NULL;
}


