#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definition of a Binary Search Tree Node
typedef struct Node {
    int id;
    struct Node *left;
    struct Node *right;
} Node;

// Function to create a new node
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newNode->id = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a value into the BST
Node* insert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->id) {
        root->left = insert(root->left, value);
    } else if (value > root->id) {
        root->right = insert(root->right, value);
    } else {
        printf("ID %d already exists. Skipping duplicate.\n", value);
    }
    return root;
}

// Inorder Traversal: Left -> Root -> Right
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->id);
        inorder(root->right);
    }
}

// Preorder Traversal: Root -> Left -> Right
void preorder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->id);
        preorder(root->left);
        preorder(root->right);
    }
}

// Postorder Traversal: Left -> Right -> Root
void postorder(Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->id);
    }
}

// Function to search for a value in the BST
bool search(Node* root, int key) {
    if (root == NULL) {
        return false;
    }
    if (root->id == key) {
        return true;
    }
    if (key < root->id) {
        return search(root->left, key);
    }
    return search(root->right, key);
}

// Free allocated memory
void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    Node* root = NULL;
    int n, value, searchKey;

    printf("Enter the number of ID numbers to insert: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        printf("Invalid input.\n");
        return 1;
    }

    printf("Enter %d unique integer IDs:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insert(root, value);
    }

    printf("\n--- Traversal Results ---\n");
    printf("Preorder Traversal  : ");
    preorder(root);
    printf("\n");

    printf("Inorder Traversal   : ");
    inorder(root);
    printf("\n");

    printf("Postorder Traversal : ");
    postorder(root);
    printf("\n");

    printf("\nEnter an ID to search: ");
    scanf("%d", &searchKey);

    if (search(root, searchKey)) {
        printf("Result: ID %d exists in the system.\n", searchKey);
    } else {
        printf("Result: ID %d does not exist in the system.\n", searchKey);
    }

    freeTree(root);
    return 0;
}