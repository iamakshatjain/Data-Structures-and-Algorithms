#include <bits/stdc++.h>
#include <iostream>
using namespace std;

struct graph{
	int v;
	int e;
	int **adj;
};

//this creates an undirected graph
graph* create_graph(int v,int e){

	graph *g = (graph*)malloc(sizeof(graph));

	if(!g){
		cout<<"memory error"<<endl;
		return g;
	}

	g->v = v;
	g->e = e;
	g->adj = (int **)malloc(sizeof(int *)*v);
	for(int i=0;i<v;i++)
		g->adj[i] = (int *)malloc(sizeof(int)*v);

	for(int i=0;i<g->v;i++){
		for(int j=0;j<g->v;j++)
			g->adj[i][j] = 0;
	}
	//we do it for undirected graphs
	for(int i=0;i<g->e;i++){
		int u,v;
		cout<<"enter u & v : ";
		//here enter values ranging from 0 to v-1 
		cin>>u>>v;
		g->adj[u][v] = 1;
		g->adj[v][u] = 1;
	}

	return g;
}

void display_matx(graph *g){
	for(int i=0;i<g->v;i++){
		for(int j=0;j<g->v;j++)
			cout<<g->adj[i][j]<<' ';
		cout<<endl;
	}
}

void DFS_Traverse(graph* g,int i,int d,int v[]){
	// if(!v[i] && i == d){
	// 	return 1;
	// }
	// cout<<i<<' '<<d<<endl;
	v[i] = 1;

	for(int j=0;j<g->v;j++){
		if(g->adj[i][j] && !v[j]){
			DFS_Traverse(g,j,d,v);
		}
	}
}

int check_path(graph*g,int s,int d){
	int visited[g->v] = {0};
	visited[s] = 1;//we have visited the source
	if(s==d){
		return 1;
	}
	// cout<<s<<endl;
	for(int i=0;i<g->v;i++){
		if(g->adj[s][i] && !visited[i]){
			DFS_Traverse(g,i,d,visited);
				// return 1;
		}
	}

	if(visited[d] == 1){//this is probably the best way to check and also for any other vertex too
		return 1;		//checking for other vertex after traversal would take only O(1)
	}
}

int main(){

	graph *g  = create_graph(5,4);
	g?cout<<"created":cout<<"not-created";
	cout<<endl;
	display_matx(g);
	cout<<endl;
	check_path(g,2,3)?cout<<"path-exists":cout<<"path does not exist";
	cout<<endl;
	return 0;
}