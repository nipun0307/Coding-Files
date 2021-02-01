// AVL TREES and Transversals

//Inserting a node in AVL tree 

#include<stdio.h> 
#include<stdlib.h> 




// A utility function to get maximum of two integers 
int max(int a, int b) 
{ 
    return (a > b)? a : b; 
} 

// A tree node 
struct Node 
{ 
    int key; 
    struct Node *left; 
    struct Node *right; 
    struct Node *parent; 
    int height; 
    // int balfactor; // diff in heights of left and right subtrees 
}; 

void inOrder(struct Node *root) 
{ 
    if(root != NULL) 
    {   
        inOrder(root->left); 
        if(root->parent != NULL)
          printf("[%d, parent: %d, height: %d] \n", root->key, root->parent->key, root->height); 
        else
          printf("[%d,ROOT, height: %d] \n", root->key,root->height); 

        inOrder(root->right); 
    } 
}


void preOrder(struct Node *root) 
{ 
    if(root != NULL) 
    {  
        if(root->parent != NULL)
          printf("[%d, parent: %d, height: %d] \n", root->key, root->parent->key, root->height); 
        else
          printf("[%d,ROOT, height: %d] \n", root->key,root->height); 

        preOrder(root->left); 
        preOrder(root->right); 
    } 
}

// A utility function to get the height of the tree 
int height(struct Node *N) 
{ 
  if(N == NULL)
    return 0;
  return N->height;
} 
    
/* Helper function that allocates a new node with the given key and 
    NULL left and right pointers. */
struct Node* newNode(int key) 
{ 
  struct Node* node = (struct Node*) malloc(sizeof(struct Node)); 
  
  node->key = key;
  node->right = NULL;
  node->left = NULL;
  node->parent = NULL;
  node->height = 1;

  return(node);
} 
    
// Get Balance factor of node N 
int getBalance(struct Node *N) 
{ 
  if(N == NULL)
    return 0;
  return height(N->left) - height(N->right); 
  // Using the utility function is safer
  // for scenarios when a left and/or right child may be missing.
} 


struct Node* leftRotate(struct Node *z, struct Node *zp){

  struct Node *y = z->right;
  struct Node *T3 = y->left; 

  y->left = z;
  z->right = T3;
  if(T3 != NULL)
    T3->parent = z;

  y->parent = zp;
  z->parent = y;

  z->height = 1 + max(height(z->left),height(z->right)); 
  y->height = 1 + max(height(y->left),height(y->right)); 

  return y;  
}


struct Node* rightRotate(struct Node *z, struct Node *zp){

  struct Node *y = z->left;
  struct Node *T3 = y->right; 

  y->right = z;
  z->left = T3;
  if(T3 != NULL)
    T3->parent = z;

  y->parent = zp;
  z->parent = y;
  T3->parent = z;

  z->height = 1 + max(height(z->left),height(z->right)); 
  y->height = 1 + max(height(y->left),height(y->right)); 

  return y;  
}
  
struct Node* insert(struct Node* node, int key, struct Node* parent_node){

  if(node == NULL){
    struct Node *tmpnode = newNode(key);
    tmpnode->parent = parent_node;
    return tmpnode;
  }


  if(key == node->key){
    return node;
  }

  if(key < node->key){
    node->left = insert(node->left, key, node);
  }
  else{
    node->right = insert(node->right, key, node);
  }

  node->height = 1 + max(height(node->left),height(node->right)); 

  int balance = getBalance(node);

  if(balance > 1){
    if(key < node->left->key){
      // we need a right rotation (LL case)
      return(rightRotate(node,node->parent));
    }
    else{
      // we need a double rotation (LR case)
      // left rotate at y
      // back to LL case with x as the child and y as the grandchild.
      node->left = leftRotate(node->left,node);
      return(rightRotate(node,node->parent));
    }
  }
  
  if(balance < -1){
    if(key > node->right->key){
      // we need a left rotation (RR case)
      return(leftRotate(node,node->parent));
    }
    else{
      // we need a double rotation (RL case)
      // symmetric :)
      node->right = rightRotate(node->right,node);
      return(leftRotate(node,node->parent));
    }
  }

  return node; 

}
  
/* Driver program to test above function*/
int main() 
{ 
  struct Node *root = NULL; 
  int n,x;
  
  /* Constructing tree given in the above figure */
  
  printf("Enter the number of inputs to be inserted: ");
  scanf("%d",&n);
  for(int i=0;i<n;i++){
      printf("Enter an input: ");
      scanf("%d",&x);
      root=insert(root,x,NULL);
  }
  
  /*
  input to check LL: 15, 6, 23, 4, 7, 5
  input to check RR: 15, 6, 23, 21, 27, 25
  input to check LR: 15, 6, 23, 4, 7, 8
  input to check RL: 15, 6, 23, 21, 27, 20

  Thanks to Dhaiwat Kabaria for the suggestion! 
  */

  printf("\n\nInorder\n");
  inOrder(root); 
  printf("\n\nPreorder\n");
  preOrder(root); 
  return 0; 
} 