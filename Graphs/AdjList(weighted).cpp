#include<bits/stdc++.h>
#include<iostream>
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

int main(){
	graph *g;
	int v,e;
	// cout<<"enter vertex and edge count"<<endl;
	// cin>>v>>e;
	g = create_graph(5,6);
	(g==NULL)?cout<<"not-created":cout<<"created";
	cout<<endl;
	// display_graph(g);

	add_edge(g,0,1,4);
	add_edge(g,0,2,1);
	add_edge(g,2,1,2);
	add_edge(g,2,3,4);
	add_edge(g,1,4,4);
	add_edge(g,3,4,4);

	display_graph(g);
}