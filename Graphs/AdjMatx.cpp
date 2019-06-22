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
		// g->adj[v][u] = 1; // to remove undirected graph
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

void DFS_Traverse(graph* g,int i,int d,int *count){
	cout<<"i :"<<i<<endl;
	if(i == d){
		*count++;
		cout<<"count :"<<*count<<endl;
	}
	for(int j=0;j<g->v;j++){
		if(g->adj[i][j]){
			DFS_Traverse(g,j,d,count);
		}
	}
}

void count_paths(graph *g,int s,int d){
	int count = 0;
	if(s==d){
		count++;
	}

	for(int i=0;i<g->v;i++){
		cout<<"count inside : "<<count<<endl;
		if(g->adj[s][i]){
			DFS_Traverse(g,i,d,&count);
		}
	}
}

int main(){

	graph *g  = create_graph(4,5);
	g?cout<<"created":cout<<"not-created";
	cout<<endl;
	display_matx(g);
	count_paths(g,0,1);
	return 0;
}