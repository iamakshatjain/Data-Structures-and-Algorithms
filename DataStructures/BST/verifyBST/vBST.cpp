#include<bits/stdc++.h>
#include<limits.h>
#include<iostream>

using namespace std;

struct Node{
	int val;
	Node* parent;
	Node* left;
	Node* right;
};

Node* root = NULL;

Node* create_node(int val){
	Node* node = (Node *)malloc(sizeof(Node));
	node->parent = NULL;
	node->left = NULL;
	node->right = NULL;
	node->val = val;
	return node;
}

Node* create_BST(int val){
	if(root == NULL){
		root = create_node(val);
		return root;
	}
}

Node* add_node(int val){
	if(root == NULL){
		root = create_BST(val);
		return root;
	}

	Node* itr = root;
	Node* prev_itr;
	while(itr != NULL){

		prev_itr = itr;

		if(val <= itr->val ){
			itr = itr->left;
		}
		else{
			itr = itr->right;
		}
	}

	if(val <= prev_itr->val){
		prev_itr->left = create_node(val);
		prev_itr->left->parent = prev_itr;
		return prev_itr;
	}
	else{
		prev_itr->right = create_node(val);
		prev_itr->right->parent = prev_itr;
		return prev_itr;
	}
}


int isBST_util(Node* node, int min, int max){
	//if node is null return false
	if(node == NULL)
		return 1; //an empty tree is being considered a BST
		//if we reach some end that might suggest a tree

	if(node->val < min || node->val > max)
		return 0;

	return(isBST_util(node->left,min,node->val) && isBST_util(node->right,node->val+1,max));
}

int isBST(){
	return isBST_util(root,INT_MIN,INT_MAX);
}


int main(){
	
	//BST
	// int n;
	// cout<<"enter no. of nodes : ";
	// cin>>n;
	// for(int i=0;i<n;i++){
	// 	int val;
	// 	cin>>val;
	// 	if(add_node(val))
	// 		cout<<"node added"<<endl;
	// }

	//Not a BST
	create_BST(7);
	root->left = create_node(6);
	root->right = create_node(10);
	root->left->right = create_node(8);
	root->left->left = create_node(5);

	isBST()?cout<<"The tree is a BST":cout<<"not a BST";
	cout<<endl;

	return 0;
}