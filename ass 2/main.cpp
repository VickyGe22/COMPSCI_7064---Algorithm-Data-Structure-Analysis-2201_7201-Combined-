#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <cstddef>
#include <sstream>


//AVL Tree NODE structure setting
struct Node {
    int data;
    Node* left;
    Node* right;
    int height;

    Node(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

class AVLTree {
    private:
        Node* root;

        int get_height(Node* node) {
            if (!node) {
                return 0;
            }
            return node->height;
        }

        int balanceFactor(Node* node) {
            if (!node) {
                return 0;
            }
            return get_height(node->left) - get_height(node->right);
        }

        Node* minValueNode(Node* node) {
            Node* current = node;
            while (current->left != nullptr)
                current = current->left;

            return current;
        }

        Node* maxValueNode(Node* node) {
            Node* current = node;
            while (current->right != nullptr)
                current = current->right;

            return current;
        }

        void updateHeight(Node* node) {
            node->height = 1 + std::max(get_height(node->left), get_height(node->right));
        }


        Node* search(int key){
            Node* x = root;
            while (x != nullptr && key != x->data){
                if (key < x->data){
                    x = x->left;
                } else {
                    x = x->right;
                }
            }

            return x;
        }

        Node* leftRotate(Node* node) {
            Node* B = node->right;
            Node* Y = B->left;

            B->left = node;
            node->right = Y;

            updateHeight(node);
            updateHeight(B);

            return B;
        }

        Node* rightRotate(Node* node) {
            Node* A = node->left;
            Node* Y = A->right;

        A->right = node;
        node->left = Y;

        updateHeight(node);
        updateHeight(A);

        return A;
    }

        Node* insert(Node* root, int key) {
            if (!root) return new Node(key);

            if (key < root->data)
                root->left = insert(root->left, key);
            else if (key > root->data)
                root->right = insert(root->right, key);
            else
                return root;

            updateHeight(root);

            // check balance factor
            int bf = balanceFactor(root);

            if (bf > 1) {
                if (key < root->left->data) {
                    return rightRotate(root);
                } else if (key > root->left->data) {
                    root->left = leftRotate(root->left);
                    return rightRotate(root);
                }
            }

            if (bf < -1) {
                if (key > root->right->data) {
                    return leftRotate(root);
                } else if (key < root->right->data) {
                    root->right = rightRotate(root->right);
                    return leftRotate(root);
                }
            }

            return root;
        } 

        Node* deleteNode(Node* root, int key) {
            
            if (!root) return root;

            if (key < root->data)
                root->left = deleteNode(root->left, key);
            else if (key > root->data)
                root->right = deleteNode(root->right, key);
            else {
                if ((!root->left) || (!root->right)) {
                    Node* temp = root->left ? root->left : root->right;

                    if (!temp) {
                        temp = root;
                        root = nullptr;
                    } else {
                        *root = *temp;
                    }
                    delete temp;
                } else {
                    Node* temp = maxValueNode(root->left);
                    root->data = temp->data;
                    root->left = deleteNode(root->left, temp->data);
                }
            }

            if (!root) return root;

            updateHeight(root);

            int bf = balanceFactor(root);

            if (bf > 1) {
                if (balanceFactor(root->left) >= 0) {
                    return rightRotate(root);
                } else {
                    root->left = leftRotate(root->left);
                    return rightRotate(root);
                }
            }

            if (bf < -1) {
                if (balanceFactor(root->right) <= 0) {
                    return leftRotate(root);
                } else {
                    root->right = rightRotate(root->right);
                    return leftRotate(root);
                }
            }

            return root;
        }


        void printPreOrder(Node* node, std::vector<int>& result) {
            if (node) {
                result.push_back(node->data);
                printPreOrder(node->left, result);
                printPreOrder(node->right, result);
            }
        }

        void printInOrder(Node* node, std::vector<int>& result) {
            if (node) {
                printInOrder(node->left, result);
                result.push_back(node->data);
                printInOrder(node->right, result);
            }
        }

        void printPostOrder(Node* node, std::vector<int>& result) {
            if (node) {
                printPostOrder(node->left, result);
                printPostOrder(node->right, result);
                result.push_back(node->data);
            }
        }

    public:
        AVLTree() : root(nullptr) {}

        void insert(int key) {
            root = insert(root, key);
        }

        void remove(int key) {
            root = deleteNode(root, key);
        }

        std::vector<int> printPreOrder() {
            std::vector<int> result;
            printPreOrder(root, result);
            return result;
        }

        std::vector<int> printInOrder() {
            std::vector<int> result;
            printInOrder(root, result);
            return result;
        }

        std::vector<int> printPostOrder() {
            std::vector<int> result;
            printPostOrder(root, result);
            return result;
        }


};

int main() {
    AVLTree avltree;

    std::string line;
    getline(std::cin, line);

    std::istringstream iss(line); //extract space-separated values (words or tokens) from the input line
    std::string move; //store individual tokens (like "A1", "D3", "PRE", etc.)
    while (iss >> move) {
        if (move[0] == 'A') {
            int value = stoi(move.substr(1));
            avltree.insert(value);
        } else if (move[0] == 'D') {
            int value = stoi(move.substr(1));
            avltree.remove(value);
        } else {
            std::vector<int> result;
            if (move == "PRE") result = avltree.printPreOrder();
            else if (move == "IN") result = avltree.printInOrder();
            else if (move == "POST") result = avltree.printPostOrder();

            if (result.empty()) {
                std::cout << "EMPTY" << std::endl;
            } else {
                for (size_t i = 0; i < result.size(); i++) {
                    std::cout << result[i] << (i + 1 == result.size() ? '\n' : ' ');
                }
            }
            break;
        }
    }

    return 0;
}




// You are asked to use C++ to implement 
// • Binary Tree Traversal
// • AVL Tree Insertion and Deletion

// 2 Submission Guideline

// You should start your program by initializing an empty AVL tree. 
// Your program takes one line as input.  - input数量在1-100之间
// The input line contains n “modification moves” separated by spaces (1 ≤ n ≤ 100). 

// The available modification moves are
// • Aint (Character A followed by an int value between 1 and 100):  A表示插入后接需要插入的数
//  A3 means insert value 3 into the AVL tree. If 3 is already in the tree, do nothing.

// • Dint (Character D followed by an int value between 1 and 100): D表示删除后接需要删除的数
// D3 means delete value 3 into the AVL tree. If 3 is not in the tree, do nothing.

// Your input is then followed by exactly one finishing move (PRE or POST or IN): 结束要求
// If the finishing move is PRE, then you should print out the tree (in its current situation) in pre-order. 
// If the tree is empty, print out EMPTY. Otherwise, print out the values separated by spaces. 
// POST and IN are handled similarly.



// You don’t need to worry about invalid inputs. 

// Sample input 1: A1 A2 A3 IN
// Sample output 1: 1 2 3
// Sample input 2: A1 A2 A3 PRE
// Sample output 2: 2 1 3 
// Sample input 3: A1 D1 POST 
// Sample output 3: EMPTY
