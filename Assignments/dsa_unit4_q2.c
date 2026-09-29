#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

// Create a new BST node
Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newNode->key = value;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Insert into BST
Node* insert(Node* root, int value) {
    if (root == NULL) {
        return createNode(value);
    }
    if (value < root->key) {
        root->left = insert(root->left, value);
    } else if (value > root->key) {
        root->right = insert(root->right, value);
    }
    return root;
}

// Inorder traversal
void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->key);
        inorder(root->right);
    }
}

// Find node with minimum value in a subtree (inorder successor)
Node* findMin(Node* root) {
    while (root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Delete a key from the BST
Node* deleteNode(Node* root, int target, int *found) {
    if (root == NULL) {
        return NULL;
    }

    if (target < root->key) {
        root->left = deleteNode(root->left, target, found);
    } else if (target > root->key) {
        root->right = deleteNode(root->right, target, found);
    } else {
        // Node found
        *found = 1;

        // Case 1: Node with 0 children (Leaf node)
        if (root->left == NULL && root->right == NULL) {
            free(root);
            return NULL;
        }

        // Case 2: Node with 1 child
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // Case 3: Node with 2 children
        // Find inorder successor (smallest in the right subtree)
        Node* successor = findMin(root->right);

        // Copy successor's value to current node
        root->key = successor->key;

        // Delete the successor from right subtree
        root->right = deleteNode(root->right, successor->key, found);
    }
    return root;
}

void freeTree(Node* root) {
    if (root != NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    Node* root = NULL;
    int n, value, delKey;

    printf("Enter number of nodes: ");
    if (scanf("%d", &n) != 1 || n <= 0) {
        return 1;
    }

    printf("Enter %d values:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &value);
        root = insert(root, value);
    }

    printf("\nInorder traversal BEFORE deletion: ");
    inorder(root);
    printf("\n");

    printf("Enter node value to delete: ");
    scanf("%d", &delKey);

    int found = 0;
    root = deleteNode(root, delKey, &found);

    if (found) {
        printf("Node %d successfully deleted.\n", delKey);
        printf("Inorder traversal AFTER deletion : ");
        inorder(root);
        printf("\n");
    } else {
        printf("Node %d was not found in the tree.\n", delKey);
    }

    freeTree(root);
    return 0;
}