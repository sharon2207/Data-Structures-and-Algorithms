#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure
struct Node {
    int patientID;
    char name[50];
    struct Node *left, *right;
    int height; // for AVL
};

// Create a new node
struct Node* createNode(int id, char name[]) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->patientID = id;
    strcpy(newNode->name, name);
    newNode->left = newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

// ---------------- BST FUNCTIONS ----------------

int checkDuplicate(struct Node* root, int id) {
    if (root == NULL) return 0;
    if (root->patientID == id) return 1;
    if (id < root->patientID) return checkDuplicate(root->left, id);
    else return checkDuplicate(root->right, id);
}

struct Node* insertBST(struct Node* root, int id, char name[]) {
    if (root == NULL)
        return createNode(id, name);
    if (id < root->patientID)
        root->left = insertBST(root->left, id, name);
    else if (id > root->patientID)
        root->right = insertBST(root->right, id, name);
    else {
        printf("?? Duplicate ID (%d) not allowed!\n", id);
        return root;
    }
    return root;
}

struct Node* minValueNode(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

struct Node* deleteBST(struct Node* root, int id) {
    if (root == NULL) {
        printf("?? Tree is empty or ID not found.\n");
        return root;
    }

    if (id < root->patientID)
        root->left = deleteBST(root->left, id);
    else if (id > root->patientID)
        root->right = deleteBST(root->right, id);
    else {
        // Found node
        if (root->left == NULL) {
            struct Node* temp = root->right;
            printf("? Deleted Patient ID: %d\n", root->patientID);
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            printf("? Deleted Patient ID: %d\n", root->patientID);
            free(root);
            return temp;
        }
        struct Node* temp = minValueNode(root->right);
        root->patientID = temp->patientID;
        strcpy(root->name, temp->name);
        root->right = deleteBST(root->right, temp->patientID);
    }
    return root;
}

struct Node* searchBST(struct Node* root, int id) {
    if (root == NULL)
        return NULL;
    if (root->patientID == id)
        return root;
    if (id < root->patientID)
        return searchBST(root->left, id);
    return searchBST(root->right, id);
}

void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d - %s\n", root->patientID, root->name);
        inorder(root->right);
    }
}

void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d - %s\n", root->patientID, root->name);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d - %s\n", root->patientID, root->name);
    }
}

// ---------------- AVL FUNCTIONS ----------------

int height(struct Node* n) {
    return (n == NULL) ? 0 : n->height;
}

int getBalance(struct Node* n) {
    return (n == NULL) ? 0 : height(n->left) - height(n->right);
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

struct Node* insertAVL(struct Node* node, int id, char name[]) {
    if (node == NULL)
        return createNode(id, name);

    if (id < node->patientID)
        node->left = insertAVL(node->left, id, name);
    else if (id > node->patientID)
        node->right = insertAVL(node->right, id, name);
    else {
        printf("?? Duplicate ID (%d) not allowed in AVL Tree!\n", id);
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    // LL
    if (balance > 1 && id < node->left->patientID)
        return rightRotate(node);

    // RR
    if (balance < -1 && id > node->right->patientID)
        return leftRotate(node);

    // LR
    if (balance > 1 && id > node->left->patientID) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL
    if (balance < -1 && id < node->right->patientID) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// ---------------- TIME COMPLEXITY ----------------

void compareComplexity() {
    printf("\n--- Time Complexity Comparison ---\n");
    printf("Operation\tBST (Avg)\tBST (Worst)\tAVL (All cases)\n");
    printf("Insertion\tO(log n)\tO(n)\t\tO(log n)\n");
    printf("Deletion\tO(log n)\tO(n)\t\tO(log n)\n");
    printf("Search\t\tO(log n)\tO(n)\t\tO(log n)\n\n");
}

// ---------------- MAIN MENU ----------------

int main() {
    struct Node *bstRoot = NULL, *avlRoot = NULL;
    int choice, ch, id;
    char name[50];
    struct Node* found;

    while (1) {
        printf("\nMain Menu:\n");
        printf("1. Work with Binary Search Tree (BST)\n");
        printf("2. Work with AVL Tree\n");
        printf("3. Compare Time Complexities\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("?? Invalid input! Please enter a number.\n");
            while (getchar() != '\n'); // clear buffer
            continue;
        }

        switch (choice) {
        case 1:
            while (1) {
                printf("\n--- BST Menu ---\n");
                printf("1. Insert Patient\n");
                printf("2. Delete Patient\n");
                printf("3. Search Patient\n");
                printf("4. Display (Inorder/Preorder/Postorder)\n");
                printf("5. Back to Main Menu\n");
                printf("Enter choice: ");
                if (scanf("%d", &ch) != 1) {
                    printf("?? Invalid input!\n");
                    while (getchar() != '\n');
                    continue;
                }

                if (ch == 1) {
                    printf("Enter Patient ID (positive number): ");
                    scanf("%d", &id);
                    if (id <= 0) {
                        printf("?? Invalid ID. Must be a positive integer.\n");
                        continue;
                    }
                    printf("Enter Patient Name: ");
                    scanf(" %[^\n]", name);
                    if (strlen(name) == 0) {
                        printf("?? Name cannot be empty.\n");
                        continue;
                    }
                    if (checkDuplicate(bstRoot, id))
                        printf("?? Patient ID already exists!\n");
                    else
                        bstRoot = insertBST(bstRoot, id, name);
                } 
                else if (ch == 2) {
                    if (bstRoot == NULL) {
                        printf("?? Tree is empty.\n");
                        continue;
                    }
                    printf("Enter ID to delete: ");
                    scanf("%d", &id);
                    bstRoot = deleteBST(bstRoot, id);
                } 
                else if (ch == 3) {
                    if (bstRoot == NULL) {
                        printf("?? Tree is empty.\n");
                        continue;
                    }
                    printf("Enter ID to search: ");
                    scanf("%d", &id);
                    found = searchBST(bstRoot, id);
                    if (found)
                        printf("? Found: %d - %s\n", found->patientID, found->name);
                    else
                        printf("? Patient not found!\n");
                } 
                else if (ch == 4) {
                    int t;
                    printf("1. Inorder\n2. Preorder\n3. Postorder\n");
                    printf("Enter choice: ");
                    scanf("%d", &t);
                    if (t == 1) inorder(bstRoot);
                    else if (t == 2) preorder(bstRoot);
                    else if (t == 3) postorder(bstRoot);
                    else printf("?? Invalid option!\n");
                } 
                else if (ch == 5)
                    break;
                else
                    printf("?? Invalid choice!\n");
            }
            break;

        case 2:
            while (1) {
                printf("\n--- AVL Menu ---\n");
                printf("1. Insert Patient\n");
                printf("2. Display Patients\n");
                printf("3. Back to Main Menu\n");
                printf("Enter choice: ");
                scanf("%d", &ch);

                if (ch == 1) {
                    printf("Enter Patient ID: ");
                    scanf("%d", &id);
                    if (id <= 0) {
                        printf("?? Invalid ID. Must be positive.\n");
                        continue;
                    }
                    printf("Enter Patient Name: ");
                    scanf(" %[^\n]", name);
                    if (strlen(name) == 0) {
                        printf("?? Name cannot be empty.\n");
                        continue;
                    }
                    avlRoot = insertAVL(avlRoot, id, name);
                } 
                else if (ch == 2) {
                    int t;
                    printf("1. Inorder\n2. Preorder\n3. Postorder\n");
                    printf("Enter choice: ");
                    scanf("%d", &t);
                    if (t == 1) inorder(avlRoot);
                    else if (t == 2) preorder(avlRoot);
                    else if (t == 3) postorder(avlRoot);
                    else printf("?? Invalid option!\n");
                } 
                else if (ch == 3)
                    break;
                else
                    printf("?? Invalid choice!\n");
            }
            break;

        case 3:
            compareComplexity();
            break;

        case 4:
            printf("Exiting...\n");
            exit(0);

        default:
            printf("?? Invalid choice. Try again.\n");
        }
    }
    return 0;
}

