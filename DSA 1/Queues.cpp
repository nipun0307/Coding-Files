// QUEUES

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

struct Node{
    int data;
    struct Node *next;
};

struct queue{
    struct Node *front, *rear;
};

struct queue *create (){
    struct queue *ptr=(struct queue*)malloc(sizeof(struct queue*));
    ptr -> front=NULL;
    ptr -> rear= NULL;
    return ptr;
};

void pop(struct queue* ptr){
    struct Node* temp =ptr->front;
    ptr->front=temp->next;
    free(temp);  
}

int peek(struct queue *ptr){
  return ptr->front->data;  
}

void push(struct queue *ptr, int data){
    struct Node* new_n=(struct Node*)malloc(sizeof(struct Node*));
    new_n->data=data;
    new_n->next=NULL;
    if(ptr -> rear!=NULL) ptr->rear->next=new_n;
    ptr->rear= new_n;
    if(ptr->front==NULL) ptr->front=new_n;
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n;
    scanf("%d",&n);
    int ideal[n],x;
    struct queue *call=create();
    for(int i=0;i<n;i++){
        scanf("%d",&x);
        push (call, x);
    }
    for(int i=0;i<n;i++) scanf("%d",&ideal[i]);
    
    int ans=n, point=0, temp; //the answer will be n (atleast)
    
    //if the element of the ideal array matched the order of tghe element of the linked list, 
    //increment the point (the index). 
    //If it doesnot match, keep on rotating and incrementing the point and pop off q.
    
    while(point!=n){
        if (ideal[point]==peek(call)){
            pop(call);
            point++;
        }
        else{
            temp=peek(call);
            push(call, temp);
            ans++;
            
        }
    }
    printf("%d", ans);
    
    return 0;
}