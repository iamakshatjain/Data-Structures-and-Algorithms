#include<bits/stdc++.h>
#include<iostream>
using namespace std;

void swap(int a[], int i, int j){
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

int partition(int a[], int b[], int p, int r){
    int pivot = a[r];
    int i = p-1;
    for(int j=p; j<r; j++){
        if(a[j] <= pivot){
            i++;
            swap(a,i,j);
            swap(b,i,j);
        }
    }
    swap(a,i+1,r);
    swap(b,i+1,r);
    return i+1;
}

void quick_sort(int a[], int b[], int p, int r){
    if(p>r)
        return;
    int q = partition(a,b,p,r);
    quick_sort(a, b, p,q-1);
    quick_sort(a, b, q+1,r);
}
 
int maxIntervalCount(int start[], int fin[], int n){
    quick_sort(fin, start, 0, n - 1);
    int count = 1;
    int endT = fin[0];
    for(int i=1; i<n; i++){
        if(start[i] >= endT){
            count++;
            endT = fin[i];
        }
    }
    return count;
}

int main(){

    int str[] = {2, 10, 1, 5, 9, 7};
    int fin[] = {4, 12, 3, 6, 11, 8};

    int n = 6; //number of processes;
    
    int max_intervals = maxIntervalCount(str, fin, n);
    cout<<max_intervals<<endl;

    return 0;
}