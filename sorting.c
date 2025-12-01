#include <stdio.h>

typedef struct {
    int key;
}element;


void bubblesort(element a[], int n){
    element tmp;
    int i,j;

    for(i=0; i< n-1; i++){
        for(j=0 ; j <n-1-i;j++){
            if(a[j].key>a[j+1].key){
                tmp = a[j];
                a[j] = a[j+1];
                a[j+1] = tmp;
            }
        }
    }
}

void selectionsort(int a[], int n){
    int i,j,min,temp;

    for(i=0; i < n-1; i++){
        min = i;

        for(j=i+1; j<n; j++){
            if(a[j] < a[min]){
                min = j;
            }
        }
        temp = a[i];
        a[i] = a[min];
        a[min] = temp;
    }
}

void quicksort(element a[], int left, int right){
    int pivot, i, j;
    element temp;
    if(left < right){
        i = left;
        j = right+1;
        pivot = a[left].key;
        do{
            do{
                i++;
            }while(a[i].key < pivot && i < right);
            do{
                j++;
            }while(a[j].key > pivot && j > left);
            if(i < j){
                SWAP(a[i], a[j], temp);
            }
        }while(i<j);

        SWAP(&a[left],&a[j],temp);

        quicksort(a,left,j-1);
        quicksort(a,j+1,right);
    }
}

void SWAP(element *x, element *y){
    element temp = *x;
    *x = *y;
    *y = temp;
}

element mergeList[100000];

void mergeSort(element a[], int left, int right){
    if(left >= right)
        return;
    int mid = (left + right)/2;
    mergeSort(a,left,mid);
    mergeSort(a,mid+1,right);
    merge(a,left,mid,right);
}

void merge(element initList[], int i, int m, int n){
    int j = m+1;
    int k = i;
    int t;
    int start = i;

    while(i <= m && j <= n){
        if(initList[i].key <= initList[j].key)
            mergeList[k++] = initList[i++];
        else
            mergeList[k++] = initList[j++];
    }

    if(i>m){
        for(t= j; t <=n ; t++){
            mergeList[k++] = initList[t];
        }
    }

    else{
        for(t=i; t<= m ; t++){
            mergeList[k++] = initList[t];
        }
    }

    for(t=start; t<=n; t++){
        initList[t] = mergeList[t];
    }
}

void adjust(element list[], int root, int n){
    int child, rootkey;
    element temp;
    temp = list[root];
    rootkey = list[root].key;
    child = 2 * root;
    while(child <= n){
        if(child < n && list[child].key < list[child+1].key){
            child++;
        }
        if(rootkey > list[child].key){
            break;
        }
        else{
            list[child/2] = list[child];
            child *= 2;
        }
    }
    list[child/2] = temp;
}

void heapsort(element list[], int n){
    int i,j;
    element temp;

    for(i=n/2 ; i>0; i--){
        adjust(list,i,n);
    }

    for(i= n-1; i>0; i--){
        SWAP(&list[1], &list[i+1], temp);
        adjust(list,1,i);
    }
}














