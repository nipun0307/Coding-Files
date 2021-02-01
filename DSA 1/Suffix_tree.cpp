#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

#define a_size 26
int number_of_nodes= 0;

int chartoascii (char c){
    return (int)c -97;
}

struct node {
    struct node *children[a_size];
    struct node *parent;
    bool isend;
    char c;
};

struct node * newNode (char m){
    struct node *ptr = NULL;
    ptr=(struct node*)malloc(sizeof(struct node));
    ptr->isend=false;
    ptr->c=m;
    ptr->parent=NULL;
    for (int i=0; i<a_size; i++)
    ptr->children[i]=NULL;
    number_of_nodes++;
    return ptr;
}

struct node *insert (char *word, struct node *parent){
    int len= strlen(word);
    struct node *curr = parent;
    for (int i=0; i<len;i++){
        int j=chartoascii(word[i]);
        if (curr->children[j]) curr=curr->children[j];
        else{
            struct node *ptr=newNode(word[i]);
            curr->children[j]=ptr;
            ptr->parent=curr;
            curr=curr->children[j];
        }
    }
    curr->isend=true;
    return parent;
}

int m=0, flag=0;
char temp[500]={};
void comprefix(struct node *root){
    int i=0, x=0;
    for(int j=0; j<a_size;j++){
        if (root->children[j]!=NULL) {
            i++;
            x=j;
        }
    }
    if (i>1){
        return;
    }
    if(root->c=='A' && i==0) {flag=1;return;}
    if(root==NULL) return;
    else {
        temp[m]=root->children[x]->c;
        m++;
        root=root->children[x];
        comprefix(root);
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int n; scanf("%d",&n);
    char words[1000][500]={};
    struct node *root =newNode('A');
   
    for (int i=0; i<n;i++){
        scanf("%s", words[i]);
        root= insert (words[i], root);
    }
    comprefix(root);
    int len1=strlen(temp);
    if (len1==0 || flag==1) {printf("-1");return -1;}
    //printf("%c", root->c);
    for(int i=0; i<len1;i++){
        printf("%c", temp[i]);
    }
    
    
    return 0;
}