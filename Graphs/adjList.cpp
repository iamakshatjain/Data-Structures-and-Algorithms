#include <bits/stdc++.h>
#include <iostream>
using namespace std;

//Node of the adjacency list
struct ListNode{
	int vertex;
	ListNode* next;
};

//implementation using adjacency list
struct graph{
	int v;
	int e;
	ListNode *list;//this would be an array of linked lists
};

graph* create_graph(int v,int e){
	graph* g = (graph *)malloc(sizeof(graph));
	if(!g){
		cout<<"memory-error"<<endl;
		return g;
	}

	g->v = v;
	g->e = e;

	//creating the list
	g->list = (ListNode *)malloc(sizeof(ListNode)*v);
	//initializing the list
	for(int i=0;i<v;i++){
		g->list[i].vertex = i;
		g->list[i].next = g->list+i;//the end of each list points back to the begining
	}

	return g;
}

//here u and v lies from 0 to g->v
void add_edge(graph* g,int u,int v){
	if(u == v){
		cout<<"same vertex"<<endl;
		return;
	}

	//here the list is not made of pointers so we need ampersand
	ListNode* i = &(g->list[u]);
	// cout<<i->vertex<<endl;
	//because, the end of each list points back to the begining
	while(i->next->vertex!=g->list[u].vertex){
		i = i->next;
	}

	ListNode *node = (ListNode *)malloc(sizeof(ListNode));
	node->vertex = v;
	node->next = i->next;

	//attaching the node
	i->next = node;
}

void display_graph(graph* g){
	cout<<"vertices : "<<g->v<<endl;
	cout<<"edges : "<<g->e<<endl;
	for(int u = 0;u<g->v;u++){
		ListNode* i = &(g->list[u]);
		cout<<i->vertex<<' ';
		i = i->next;
		while(i->vertex!=g->list[u].vertex){
			cout<<i->vertex<<' ';
			i = i->next;
		}
		cout<<endl;
	}

}

void DFS(graph *g,int i,int v[]){//this is actually the function to visit the nodes
	// if(v[i]!=0)
		// return;
	v[i] = 1;//this node is now visited
	cout<<g->list[i].vertex<<' ';
	ListNode *itr = &(g->list[i]);//this ith node is now visited
	itr = itr->next;
	while(itr->vertex != g->list[i].vertex){//traverse through all the adjacent nodes
		if(v[itr->vertex]==0)//if any adjacent node is not visited
			DFS(g,itr->vertex,v);//we visit the node 
		itr = itr->next;
	}
}

void DFS_Traversal(graph *g){
	cout<<endl;
	int visited[g->v] = {0};//all elements initialized to zero
	for(int i = 0;i<g->v;i++){//for each vertex apply dfs
		if(visited[i]==0)//this would actually be true once. It traverse all elements in one starting node.
			DFS(g,i,visited);
	}
	cout<<endl;
}

//we also need to implement a queue
void BFS(graph *g,int v[],int w){
	int u;

	int q[g->v];
	int f = -1;
	int r = -1;

	// if(f<=r && r<g->v-1){
	q[++r] = w;
	if(f==-1)
		f++;
	// }

	while(f<=r){//we dequeue when the queue is not empty
		u = q[f];//dequeue
		if(v[u] == 1){//very important condition
			f++;
			continue;
		}

		v[u] = 1;
		cout<<g->list[u].vertex<<' ';

		//this node is now visited
		ListNode* itr = &(g->list[u]);
		itr = itr->next;
		while(itr->vertex != g->list[u].vertex){
			if (!v[itr->vertex])
			{
				r++;
				q[r] = itr->vertex;
			}
			itr = itr->next;
		}
		f++;
	}


}

void BFS_Traversal(graph *g){
	cout<<endl;
	int visited[g->v] = {0};

	for(int i=0;i<g->v;i++){
		if(!visited[i]){
			BFS(g,visited,i);
		}
	}
}

//O(V+E)
void Topological_sort(graph *g){
	cout<<endl;
	//first step is to find the indegree
	int indcount = 0;
	int indegree[g->v] = {0};
	for(int i=0;i<g->v;i++){
		ListNode* itr = &(g->list[i]);
		itr = itr->next;
		while(itr->vertex!=g->list[i].vertex){
			indegree[itr->vertex]++;
			indcount++;
			if(indcount>g->e){
				cout<<"maybe undirected/cycle"<<endl;
				return;
			}
			itr = itr->next;
		}
	}

	int queue[2*g->v];//2*g->v because there may be a chance of cycle
	int f = -1;
	int r = -1;
	int counter = 0;

	for(int i = 0;i<g->v;i++){
		if(indegree[i]==0){
			queue[++r] = i;
			if(f==-1)
				f++;
		}	
	}

	while(f<=r){
		int u = queue[f];//dequeue
		cout<<u<<' '; 
		++counter;

		if(counter != g->v){
			cout<<"maybe cycle present!"<<endl;
			break;
		}

		ListNode* itr = &(g->list[u]);
		itr = itr->next;
		while(itr->vertex!=g->list[u].vertex){
			indegree[itr->vertex]--;
			if(indegree[itr->vertex] == 0){
				queue[++r] = itr->vertex;//enqueue
			}
			itr = itr->next;
		}
	
		f++;
	}
	cout<<endl;
}


int main(){
	graph *g  = create_graph(8,16);
	g?cout<<"created":cout<<"not-created";
	cout<<endl;

	add_edge(g,0,1);
	add_edge(g,1,2);
	add_edge(g,2,3);
	add_edge(g,1,7);
	add_edge(g,2,4);
	add_edge(g,4,7);
	add_edge(g,4,5);
	add_edge(g,4,6);

	add_edge(g,1,0);
	add_edge(g,2,1);
	add_edge(g,3,2);
	add_edge(g,7,1);
	add_edge(g,4,2);
	add_edge(g,7,4);
	add_edge(g,5,4);
	add_edge(g,6,4);

	// add_edge(g,0,3);
	// add_edge(g,0,4);
	// add_edge(g,1,3);
	// add_edge(g,2,4);
	// add_edge(g,4,7);
	// add_edge(g,3,5);
	// add_edge(g,3,6);
	// add_edge(g,3,7);
	// add_edge(g,4,6);
	// BFS_Traversal(g);
	Topological_sort(g);
	// display_graph(g);
	cout<<endl;
	return 0;
}