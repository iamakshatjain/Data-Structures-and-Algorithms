//creating a new list after addition is easier here than adding to the previous list
//to add to the previous list it is difficult to maintain previous node information and insert nodes

#include<bits/stdc++.h>
#include<iostream>
using namespace std;

struct Node{
	int coeff;
	int power;
	Node* next;
};

Node* create_node(int coeff, int power){
	Node* node = (Node *)malloc(sizeof(Node));
	node->coeff = coeff;
	node->power = power;
	node->next = NULL;
	return node;
}

void display_polynomial(Node* poly){

	Node* itr = poly;
	while(itr!=NULL){
		if(itr->next!=NULL)
			cout<<itr->coeff<<"x^"<<itr->power<<" + ";
		else
			cout<<itr->coeff<<"x^"<<itr->power<<' ';

		itr = itr->next;
	}
	cout<<endl;
}

Node* add_polynomials(Node* poly1,Node* poly2){
	Node* polyR = NULL;
	Node* itr = polyR;//to point at polyR
	Node* itr1 = poly1;
	Node* itr2 = poly2;

	while(itr1!=NULL && itr2!=NULL){
		if(itr1->power > itr2->power){
			if(itr == NULL)
				itr = create_node(itr1->coeff,itr1->power);
			else{
				itr->next = create_node(itr1->coeff,itr1->power);
				itr = itr->next;
			}

			itr1 = itr1->next;
		}
		else if(itr1->power == itr2->power){
			if(itr == NULL)
				itr = create_node(itr1->coeff+itr2->coeff,itr1->power);
			else{
				itr->next = create_node(itr1->coeff+itr2->coeff,itr1->power);
				itr = itr->next;
			}

			itr1 = itr1->next;
			itr2 = itr2->next;
		}

		else{

			if(itr == NULL)
				itr = create_node(itr2->coeff,itr2->power);
			else{
				itr->next = create_node(itr2->coeff,itr2->power);
				itr = itr->next;
			}

			itr2 = itr2->next;
		}

		if(polyR == NULL){
			polyR = itr;
		}
	}

	if(itr1!=NULL){
		while(itr1!=NULL){

			if(itr == NULL)
				itr = create_node(itr1->coeff,itr1->power);
			else{
				itr->next = create_node(itr1->coeff,itr1->power);
				itr = itr->next;
			}

			itr1 = itr1->next;
		}
	}

	if(itr2!=NULL){
		while(itr2!=NULL){

			if(itr == NULL)
				itr = create_node(itr2->coeff,itr2->power);
			else{
				itr->next = create_node(itr2->coeff,itr2->power);
				itr = itr->next;
			}

			itr2 = itr2->next;
		}
	}

	return polyR;
}

int main(){

	Node* poly1 = NULL;
	Node* poly2 = NULL;
	Node* polyR = NULL;

	// first polynomial
	poly1 = create_node(5,3);
	poly1->next = create_node(4,1);
	poly1->next->next = create_node(3,0);
	display_polynomial(poly1);

	//second polynomial
	poly2 = create_node(7,3);
	poly2->next = create_node(4,1);
	poly1->next->next = create_node(3,0);
	display_polynomial(poly2);

	polyR = add_polynomials(poly1,poly2);

	display_polynomial(polyR);

	return 0;
}