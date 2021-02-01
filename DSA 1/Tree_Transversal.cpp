//Binary Tree and Transversals

#include <stdio.h>
#include <stdlib.h>

struct node{
    int data;
    struct node *right_child;
    struct node *left_child;
};

struct node *new_node (int x){
    struct node *ptr;
    ptr=(struct node*)malloc(sizeof(struct node));
    ptr->data=x;
    ptr->left_child=NULL;
    ptr->right_child=NULL;
    
    return ptr;
}

struct node* insert(int x, struct node*root){
    if (root==NULL){
        return new_node (x);
    }
    if (x>root->data)
        root->right_child=insert(x, root->right_child);
    else if (x< root->data)
        root->left_child=insert(x, root->left_child);
    return root;
}

int find_min(struct node *root){
    if (root==NULL){
        return -1;
    }
    else if(root->left_child != NULL){
        return find_min(root->left_child);
    }
    return root->data;
    
}

void inOrder (struct node *root){
    if (root!=NULL){
        inOrder(root->left_child);
        printf("%d ",root->data);
        inOrder(root->right_child);
    }
}
struct node* deletep(int x, struct node* root){
    if(root==NULL)
        return NULL;
    if (x<root->data)
        root->left_child=deletep(x,root->left_child);
    else if (x>root->data)
        root->right_child=deletep (x, root->right_child);
    else{
        if (root->left_child==NULL && root->right_child==NULL)
        {
            free(root);
            root=NULL;
        }
        else if(root->left_child==NULL || root->right_child==NULL)
        {
            //Node to be deleted has a left child or a right child,
            //but not both
            struct node *temp;
            if (root->left_child==NULL)
                //no left child; parent 
                //should point to right child
                temp=root->right_child;
            else
                temp=root->left_child;
            free (root);
            return temp;
            
        }
        else
        {
            //Node to be deleted has both a left and a right child
            int temp= find_min(root->right_child);
            root->data= temp;
            root->right_child=deletep (temp,root->right_child);
        }
    }
    return root;
}

int main(void){
    
    struct node* root;
    root= new_node(50);
    printf("The root is declared as 50\n");
    
    int n;
    printf("Enter the number of nodes to be inserted: ");
    scanf("%d",&n);
    while(n--){
        int z;
        printf("Enter the value: ");
        scanf("%d", &z);
        insert(z,root);
    }
    
    inOrder(root);
    
    printf("\n");
    inOrder (root);
    printf("\nMin: %d\n\n",find_min(root));
    
    return 0;
}