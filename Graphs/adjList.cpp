#include <bits/stdc++.h>
#include <iostream>
using namespace std;
//the graph below is an unweighted graph

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
			DFS(g,i,visited);//this loop comes into play when there are more than one connected component in the graph.
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

void initialize(int distance[],int parent[],int l){
	for(int i=0;i<l;i++){
		if(i==0){
			distance[i] = 0;
		}

		distance[i] = 100000;
		parent[i] = -1;
	}
}

void dijkastra_unweighted(graph *g,int source){
	//unweighted graph dijkastra works with a queue, a distance array and a parent array
	int distance[g->v];
	int parent[g->v];
	initialize(distance,parent,g->v);
	int queue[g->v];
	int f = -1;
	int r = -1;

	queue[++r] = source;
	f++;
	distance[source] = 0;
	while(f<=r){//O(V), since now the elements would arive only once
		int u = queue[f];//dequeue
		ListNode *itr = &(g->list[u]);
		itr=itr->next;
		while(itr->vertex!=g->list[u].vertex){//O(E) in total
			if(distance[itr->vertex] == 100000){
				parent[itr->vertex] = u;
				distance[itr->vertex] = distance[u]+1;
				queue[++r] = itr->vertex;//enqueue only the elements with INFINITE distance, this way elements come only once
			}
			itr = itr->next;
		}
		f++;
	}
	cout<<"ele    dist    par"<<endl;
	for(int i=0;i<g->v;i++){
		cout<<i<<'\t'<<distance[i]<<'\t'<<parent[i]<<endl;
	}
}

//Articulation points by tarjan's algorithm
int tme = 0;

void articulationUtil(int u,graph* g, int ap[],int visited[],int parent[],int disc[],int low[], int children[]){
	visited[u] = 1;//the node is now visited
	disc[u] = low[u] = ++tme;//discovery time and low is initiated

	ListNode* itr = &(g->list[u]);
	itr = itr->next;
	while(itr->vertex!=g->list[u].vertex){
		int v = itr->vertex;

		if(!visited[v]){
			parent[v] = u;
			children[u]++;
			articulationUtil(v,g,ap,visited,parent,disc,low,children);
			//after the return

			low[u] = min(low[v],low[u]);

			//case1 - if root
			if(parent[u] == -1 && children[u]>=2){
				ap[u] = 1;
			} 

			//case2 - if discovery time is less than low of adjacent vertex
			if(disc[u]<=low[v] && parent[u]!=-1){
				ap[u] = 1;
			}
		}

		else if(v != parent[u]){//like B and C in tushar roy's video
			low[u] = min(disc[v],low[u]);
		}
		itr = itr->next;
	}

}


void articulation_points(graph *g){
	int *ap = (int *)malloc(sizeof(int)*g->v);
	int visited[g->v];
	int parent[g->v];
	int disc[g->v];
	int low[g->v];
	int children[g->v];

	for(int i=0;i<g->v;i++){
		ap[i] = 0;
		visited[i] = 0;
		parent[i] = -1;
		disc[i] = -1;
		low[i] = -1;
		children[i] = 0;
	}

	for(int i=0;i<g->v;i++){
		if(!visited[i])
			articulationUtil(i,g,ap,visited,parent,disc,low,children);
	}

	//then here we print ap
	cout<<"Articulation Point : ";
	for(int i=0;i<g->v;i++){
		if(ap[i]==1)
			cout<<i<<' ';
	}
	cout<<endl;
}

int t_bridge = 0;

void bridge_util(int u,graph* g,int low[],int disc[],int parent[],int visited[]){
	visited[u] = 1;
	disc[u] = low[u] = ++t_bridge;

	ListNode* itr = &(g->list[u]);
	itr = itr->next;
	while(itr->vertex!=g->list[u].vertex){
		int v = itr->vertex;

		if(!visited[v]){
			parent[v] = u;
			bridge_util(v,g,low,disc,parent,visited);

			low[u] = min(low[u],low[v]);

			if(low[v] > disc[u])
				cout<<"( "<<u<<" , "<<v<<" )"<<endl;
		}
		else if(v != parent[u])
			low[u] = min(low[u],disc[v]);

		itr = itr->next;
	}
}

void bridge(graph* g){
	int low[g->v];
	int disc[g->v];
	int visited[g->v];
	int parent[g->v];

	for(int i=0;i<g->v;i++){
		visited[i] = 0;
		disc[i] = -1;
		low[i] = -1;
		parent[i] = -1;
	}

	cout<<"Bridges : "<<endl;
	for(int i=0;i<g->v;i++){
		if(!visited[i])
			bridge_util(i,g,low,disc,parent,visited);
	}
}


//Strongly connected components - TC: O(V+E) ; SC: O(V)
int top = -1;//this is the top of the stackendl
void post_order_traversal(graph* g,int u,int visited[],int postOrder[]){
	visited[u] = 1;

	ListNode* itr = &(g->list[u]);
	itr = itr->next;
	while(itr->vertex!=g->list[u].vertex){
		int v = itr->vertex;
		if(!visited[v])
			post_order_traversal(g,v,visited,postOrder);
		itr = itr->next;
	}
	postOrder[++top] = u;
}

void print_component(graph* g,int u, int visited[]){
	cout<<u<<' ';
	visited[u]=1;

	ListNode* itr = &(g->list[u]);
	itr = itr->next;
	while(itr->vertex!=g->list[u].vertex){
		if(!visited[itr->vertex])
			print_component(g,itr->vertex,visited);
		itr = itr->next;
	}
	return;
}

void ssc(graph *g){
	//first perform dfs
	//get elements on the basis of post-order traversal
	int visited[g->v] = {0};
	int postOrder[g->v] = {0};//rather than an array it is better to put to a stack otherwise we need to sort
	//we can also make the length of the postOrder one greater than g->v and we can use the first element as top

	for(int i=0;i<g->v;i++){
		if(!visited[i])
			post_order_traversal(g,i,visited,postOrder);
	}

	//reverse the graph : O(E)
	//we need to create a new graph

	graph*Gr = create_graph(g->v,g->e);
	
	//O(V+E)
	for(int i=0;i<g->v;i++){
		ListNode* itr = &(g->list[i]);
		itr=itr->next;
		while(itr->vertex!=g->list[i].vertex){
			add_edge(Gr,itr->vertex,i);
			itr = itr->next;
		}
	}
	//reversing is easier in adjacency matrix

	//pull element one by one out of the stack and peform dfs from them, all the reachable elements would get printed
	int visited2[Gr->v] = {0};
	while(top>=0){
		int u = postOrder[top];
		if(!visited2[u]){
			print_component(Gr,u,visited2);
			cout<<endl;
		}
		top--;
	}
}

int check_cycle_util(graph*g,int u,int visited[],int parent){
	visited[u] = 1;
	ListNode*itr = &(g->list[u]);
	itr = itr->next;
	while(itr->vertex!=g->list[u].vertex){
		int v = itr->vertex;
		if(!visited[v])
			return check_cycle_util(g,v,visited,u);
		else if(v != parent){
			return 1;
		}
		itr = itr->next;
	}
	return 0;
}

void detect_cycle_undirected(graph* g){
	int visited[g->v] = {0};

	for(int i=0;i<g->v;i++){//this would keep care for the disconnected components
		if(!visited[i]){
			if(check_cycle_util(g,i,visited,-1)){
				cout<<"cycle exists"<<endl;
				return;
			}
		}
	}

	cout<<"cycle doesn't exist"<<endl;
	return;	
}

//Detecting a cycle in a directed graph
//Time Complexity : O(V+E)
//Space Complexity : O(V)
bool flag = false;
void check_cycle_util_directed(graph* g,int u,int grey[],int black[]){
	if(!grey[u] && !black[u]){
		grey[u] = 1; 
	}
	else if(black[u] == 0){
		cout<<"cycle exists"<<endl;
		flag = true;
		return;
	}

	ListNode* itr = &(g->list[u]);
	itr = itr->next;
	while(itr->vertex!=g->list[u].vertex){
		int v = itr->vertex;
		check_cycle_util_directed(g,v,grey,black);
		itr = itr->next;
	}

	black[u] = 1;
	grey[u] = 0;
}

void detect_cycle_directed(graph* g){
	int black[g->v]={0};
	int grey[g->v]={0};

	for(int i=0;i<g->v;i++){
		if(!grey[i]&&!black[i]){
			check_cycle_util_directed(g,i,grey,black);	
		}
	}
	if(!flag)
		cout<<"cycle doesn't exist"<<endl;
}

int main(){
	graph *g  = create_graph(7,8);
	
	//this graph contains a cycle
	add_edge(g,0,1);
	add_edge(g,0,2);
	add_edge(g,1,3);
	add_edge(g,2,3);
	add_edge(g,4,3);
	add_edge(g,4,5);
	add_edge(g,5,6);
	// add_edge(g,6,4);
	detect_cycle_directed(g);
	return 0;
}