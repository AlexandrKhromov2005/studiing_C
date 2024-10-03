#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    int val;
    struct node * right;
    struct node * left;
} node_t;

node_t *create_node(int val) {
    node_t *new_node = (node_t *) malloc(sizeof(node_t));
    new_node->val = val;
    new_node->left = NULL;
    new_node->right = NULL;

    return new_node;
}

void insert(node_t **root, int val){
    if (*root == NULL) {
        *root = create_node(val);
        return;
    }

    if (val < (*root)->val){
        insert(&((*root)->left), val);
    } else {
        insert(&((*root)->right), val);
    }
}

void print_tree(node_t *root, int space) {
    if (root == NULL) return;

    space += 5;

    print_tree(root->right, space);

    for (int i = 5; i < space; i++) {
        printf(" ");
    }
    printf("%d\n", root->val);

    print_tree(root->left, space);
}

void find(node_t *root, int val){ 
    static int route = 0;
    route = route * 10 + root->val;
    if (root->val == val){
        printf("here route for your value: %d\n", route);
        return;
    } else {
        if (val < root->val){
            find(root->left, val);
        } else {
            find(root->right, val);
        }
    }
}

void in_order_traversal(node_t *root) {
    if (root == NULL) return;
    in_order_traversal(root->left);
    printf("%d ", root->val);
    in_order_traversal(root->right);
}

int main() {
    node_t *root = NULL;
    int values[] = {10, 5, 15, 3, 7, 13, 17, 1, 4, 6, 8, 12, 14, 16, 18};
    int n = sizeof(values) / sizeof(values[0]);

    for (int i = 0; i < n; i++){
        insert(&root, values[i]);
    }

    print_tree(root, 0);

    find(root, 6);

    in_order_traversal(root);
    
    return 0;
}