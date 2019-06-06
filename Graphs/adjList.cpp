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

int main(){
	graph *g  = create_graph(5,4);
	g?cout<<"created":cout<<"not-created";
	cout<<endl;
	add_edge(g,0,1);
	add_edge(g,0,3);
	add_edge(g,0,2);
	add_edge(g,1,2);
	add_edge(g,2,3);
	add_edge(g,3,4);
	add_edge(g,4,2);
	display_graph(g);
	cout<<endl;
	return 0;
}