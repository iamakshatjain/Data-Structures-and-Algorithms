#include<bits/stdc++.h>
#include<limits.h>
#include<iostream>
#define INF INT_MAX
#define NIL -1

using namespace std;

struct ListNode{
	int vertex;
	int weight;
	ListNode* next;
};

struct graph{
	int v;
	int e;
	ListNode* list;
};

graph* create_graph(int v,int e){
	graph *g = (graph *)malloc(sizeof(graph));
	if(g==NULL){
		cout<<"Memory error"<<endl;
		return g;
	}

	g->v = v;
	g->e = e;
	g->list = (ListNode *)malloc(sizeof(ListNode)*v);//List of ListNode(Not pointers)

	for(int i=0;i<v;i++){
		g->list[i].vertex = i;
		g->list[i].next = &(g->list[i]);//the end of each list points back to the begining
		g->list[i].weight = 0;
	}
	return g;
}

void display_graph(graph* g){
	cout<<"vertex count : "<<g->v<<endl;
	cout<<"edge count : "<<g->e<<endl;
	for(int i=0;i<g->v;i++){
		ListNode* itr = &(g->list[i]);
		cout<<itr->vertex<<':'<<itr->weight<<' ';
		itr = itr->next;
		while(itr->vertex!=g->list[i].vertex){
			cout<<itr->vertex<<':'<<itr->weight<<' ';
			itr = itr->next;
		}
		cout<<endl;
	}	
}

void add_edge(graph *g,int u,int v,int weight){
	ListNode* itr = &(g->list[u]);
	while(itr->next!=&(g->list[u])){
		itr = itr->next;
	}

	ListNode* node = (ListNode *)malloc(sizeof(ListNode));
	node->vertex = v;
	node->weight = weight;
	node->next = &(g->list[u]);

	itr->next = node;
}

void initialize(int d[],int p[],int done[],graph* g){
	for(int i=0;i<g->v;i++){
		d[i] = -1;
		p[i] = -1;
		done[i] = 0;
	}
	return;
}

int completed(int d[],graph* g){
	for(int i=0;i<g->v;i++){
		if(d[i]==0)
			return 0;
	}
	return 1;
}

int find_min(int d[],graph* g,int done[]){
	int min = -1;
	for(int i=0;i<g->v;i++){
		if(min == -1 && d[i]!=-1 && done[i]==0)
			min = i;

		if(min!=-1 && d[i]<d[min] && d[i]!=-1 && done[i]==0)
			min = i;
	}
	return min;
}

int cost(int u,int v,graph* g){
	ListNode* itr = &(g->list[u]);
	itr = itr->next;
	while(itr->vertex!=v){
		// if(!done[itr->vertex]){
		// 	relax(u,itr->vertex,distance,parent,g);
		// }
		itr = itr->next;
	}
	return itr->weight;
}

void relax(int u,int v,int distance[],int parent[],graph* g){
	if(distance[u]+cost(u,v,g) < distance[v] || distance[v] == -1){
		parent[v] = u;
		distance[v] = distance[u]+cost(u,v,g);
	}
}

void dijkastra(graph *g,int source){
	int distance[g->v];
	int parent[g->v];
	int done[g->v];
	initialize(distance,parent,done,g);
	distance[source] = 0;
	cout<<"initialized"<<endl;
	//we could implement a queue here
	while(!completed(done,g)){//this condition also is O(v)
		cout<<"looping"<<endl;
		int u = find_min(distance,g,done);//this would takeO(v)
		cout<<"minimum : "<<u<<endl;
		ListNode* itr = &(g->list[u]);
		itr = itr->next;
		while(itr->vertex!=g->list[u].vertex){
			if(!done[itr->vertex]){
				relax(u,itr->vertex,distance,parent,g);
			}
			itr = itr->next;
		}
		done[u] = 1;
	}

	cout<<"ele\tdist\tpar"<<endl;
	for(int i=0;i<g->v;i++){
		cout<<i<<'\t'<<distance[i]<<'\t'<<parent[i]<<endl;
	}
}

void initialize_bellman_ford(int d[],int par[],graph* g){
	for(int i=0;i<g->v;i++){
		d[i] = INF;//we can't use -1 here as negative edges would be handeled
		par[i] = -1;
	}
}

//returns 1 if not relaxed and return 0 if relaxed : this is to check negative cycle
int relax(int u, int v,int wt,graph* g,int distance[],int parent[]){
	// cout<<u<<' '<<v<<endl;

	if(distance[u]!=INF){//here -1 is used to represent infinity
		if(distance[u]+wt<distance[v]){
			distance[v] = distance[u]+wt;
			parent[v] = u;
			return 0;
		}
	}
	return 1;
}


//returns 1 if negative edge cycle
int bellman_ford(graph* g,int source){
	//distance parent 
	int distance[g->v];
	int parent[g->v];
	initialize_bellman_ford(distance,parent,g);
	distance[source] = 0;

	//here we don't care for the order of checking but we just keep on checking 
	int u,v;
	for(int j=0;j<g->v-1;j++){//O(n^3)
		for(int i=0;i<g->v;i++){//to traverse through all edges
			ListNode* itr = &(g->list[i]);
			u = itr->vertex;
			itr = itr->next;
			while(itr->vertex!=g->list[i].vertex){
				// cout<<itr->vertex<<' ';
				v = itr->vertex;
				relax(u,v,itr->weight,g,distance,parent);
				itr = itr->next;
			}
		}
		// cout<<"done "<<j+1<<" times"<<endl;
	}

	for(int j=0;j<g->v-1;j++){//O(n^3)
		for(int i=0;i<g->v;i++){//to traverse through all edges
			ListNode* itr = &(g->list[i]);
			u = itr->vertex;
			itr = itr->next;
			while(itr->vertex!=g->list[i].vertex){
				// cout<<itr->vertex<<' ';
				v = itr->vertex;
				int res = relax(u,v,itr->weight,g,distance,parent);
				if(res==0){
					cout<<"Negative-edge-cycle present"<<endl;
					return 1;
				}
				itr = itr->next;
			}
		}
	}

	cout<<"ele\tdist\tpar"<<endl;
	for(int i=0;i<g->v;i++){
		cout<<i<<'\t'<<distance[i]<<'\t'<<parent[i]<<endl;
	}
	return 0;
	//this doesn't require any done array
}

void initialize_prims(int k[],int par[],int d[],graph* g){
	for(int i=0;i<g->v;i++){
		k[i] = INF;
		par[i] = -1;
		d[i] = 0;
	}
}

void prims(graph* g){
	int source = 0;
	//here due to no need of finding minimum distance there is no effect source node.
	//also due to undirected graph it doesn't matter what is the source.
	int key[g->v];
	int parent[g->v];
	int done[g->v];
	initialize_prims(key,parent,done,g);

	key[source] = 0;
	while(!completed(done,g)){//we can use this from the dijkastra
		int u = find_min(key,g,done);//this all can be done with priority queue
		ListNode* itr = &(g->list[u]);
		itr = itr->next;
		while(itr->vertex!=g->list[u].vertex){
			if(key[itr->vertex]>itr->weight && !done[itr->vertex]){//here we must also take care that we don't overwrite an already done vertex
				key[itr->vertex] = itr->weight;
				parent[itr->vertex] = u;
			}
			itr=itr->next;
		}
		done[u] = 1;
	}

	cout<<"ele\tkey\tpar"<<endl;
	for(int i=0;i<g->v;i++){
		cout<<i<<'\t'<<key[i]<<'\t'<<parent[i]<<endl;
	}
}

//compute all pair shortest path
//Time Complexity - O(V^3)
//Space Complexity - O(V^2)

initialize_floyd_warshall(graph* g,int** distance,int** path){
	int v = g->v;
	for(int i=0;i<v;i++){
		for(int j=0;j<v;j++){
			if(i==j){
				distance[i][j] = 0;
				path[i][j] = NIL;
			}
			else{
				distance[i][j] = INF;
				path[i][j] = NIL;
			}
		}
	}

	// for(int i=0;i<v;i++){
	// 	for(int j=0;j<v;j++){
	// 		cout<<distance[i][j]<<' ';
	// 	}
	// 	cout<<endl;
	// }

	// for(int i=0;i<v;i++){
	// 	for(int j=0;j<v;j++){
	// 		cout<<path[i][j]<<' ';
	// 	}
	// 	cout<<endl;
	// }
}

void floyd_warshall(graph* g){
	int** distance;
	int** path;

	distance = (int **)malloc(sizeof(int *)*g->v);
	path = (int **)malloc(sizeof(int *)*g->v);

	for(int i=0;i<g->v;i++){
		distance[i] = (int *)malloc(sizeof(int)*g->v);
		path[i] = (int *)malloc(sizeof(int)*g->v);
	}

	initialize_floyd_warshall(g,distance,path);

	for(int u=0;u<g->v;u++){
		ListNode* itr = &(g->list[u]);
		itr = itr->next;
		while(itr->vertex!=g->list[u].vertex){
			int v = itr->vertex;
			distance[u][v] = itr->weight;
			path[u][v] = u;
			itr = itr->next;
		}
	}


	for(int k=0;k<g->v;k++){
		for(int i=0;i<g->v;i++){
			for(int j=0;j<g->v;j++){
				if(distance[i][k] != INF && distance[k][j] != INF && distance[i][j] > distance[i][k] + distance[k][j]){
					distance[i][j] = distance[i][k] + distance[k][j];
					path[i][j] = path[k][j];
				}
			}
		}
	}

	cout<<endl;
	cout<<"Distance Matrix"<<endl;
	for(int i=0;i<g->v;i++){
		for(int j=0;j<g->v;j++){
			if(distance[i][j] == INF)
				cout<<'I'<<' ';
			else
				cout<<distance[i][j]<<' ';
		}
		cout<<endl;
	}

	cout<<endl;
	cout<<"Path Matrix"<<endl;
	for(int i=0;i<g->v;i++){
		for(int j=0;j<g->v;j++){
			if(distance[i][j] == INF)
				cout<<'N'<<' ';
			else
				cout<<path[i][j]<<' ';
		}
		cout<<endl;
	}
}

int main(){
	graph *g;
	int v,e;
	g = create_graph(4,4);
	(g==NULL)?cout<<"not-created":cout<<"created";
	cout<<endl;

	//graph on gfg
	add_edge(g,0,1,5);
	add_edge(g,0,3,10);
	add_edge(g,1,2,3);
	add_edge(g,2,3,1);
	display_graph(g);
	floyd_warshall(g);
	return 0;
}