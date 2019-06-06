#include <bits/stdc++.h>
#include <iostream>
using namespace std;

struct graph{
	int v;
	int e;
	int **adj;
};

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

int main(){

	graph *g  = create_graph(5,4);
	g?cout<<"created":cout<<"not-created";
	display_matx(g);
	cout<<endl;
	return 0;
}