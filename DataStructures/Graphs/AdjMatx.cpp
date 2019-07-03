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

//Check for existence of a sink : O(V)
int isSink(graph* g,int i){
	int n = g->v;
	//checking row i
	for(int c = 0;c<n;c++){
		if(g->adj[i][c])
			return 0;
	}

	//checking for ith column
	for(int r=0;r<n;r++){
		if(!g->adj[r][i] && r!=i){
			return 0;
		}
	}
	return 1;
}

int eliminate_non_sink(graph* g){
	int i,j;
	i = 0;
	j = 0;
	int n = g->v;
	while(i<n && j<n){
		if(g->adj[i][j] == 0)
			j++;
		else
			i++;
	}

	if(i>=n)
		return -1;
	if(!isSink(g,i))
		return -1;
	return i;
}


int main(){

	graph *g  = create_graph(6,5);
	g?cout<<"created":cout<<"not-created";
	cout<<endl;
	display_matx(g);
	int ans = eliminate_non_sink(g);
	if(ans == -1)
		cout<<"No sink exists"<<endl;
	else
		cout<<"sink : "<<ans<<endl;
	return 0;
}