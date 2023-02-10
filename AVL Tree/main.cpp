#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

class avlt {
public:
    int key;
    avlt* left;
    avlt* right;
    int height;
};
// returns height of the tree or the node
int avltHeight(avlt* x) {
    if(x == NULL) return 0;
        return x->height;
}
// returns greater value out of two integers
int greaterInt(int k, int l) {
    if(k > l) return k;
        return l;
}
// dynamically allocate avlt object (i.e. create a new node for the tree)
avlt* newNode(int k) {
    avlt* temp = new avlt;
    temp->key = k;
    temp->left = temp->right = NULL;
    temp->height = 1;
    return temp;
}
// starting from a node, x, travels to the right-most node and returns that node (i.e the maxium value in that tree or subtree)
avlt* findMax(avlt* x) {
    avlt* temp = x;
    while(temp->right != NULL) {
        temp = temp->right;
    }
    return temp;
}
// returns BF of a node, x (i.e. Balance Factor of node, x)
int getBF(avlt* x) {
    if (x == NULL)
        return 0;
    return avltHeight(x->left) - avltHeight(x->right);
}
/* rotateRight(avlt* y)
    rotate the subtree with the root == y
    then return the new root
*/
avlt* rotateRight(avlt* y) {
    avlt* x = y->left;
    avlt* xR = x->right;

    // Rotate the nodes
    x->right = y;
    y->left = xR;
    
    // Update the heights on the nodes
    y->height = greaterInt( avltHeight(y->left), avltHeight(y->right) ) + 1;
    x->height = greaterInt( avltHeight(x->left), avltHeight(x->right) ) + 1;
    
    // Return new root
    return x;
}
/* rotateLeft(avlt* x)
    rotate the subtree with the root == x
    then return the new root
*/
avlt* rotateLeft(avlt* x) {
    avlt* y = x->right;
    avlt* yL = y->left;
    
    // Rotate the nodes
    y->left = x;
    x->right = yL;

    // Update the heights on the nodes
    x->height = greaterInt( avltHeight(x->left), avltHeight(x->right) ) + 1;
    y->height = greaterInt( avltHeight(y->left), avltHeight(y->right) ) + 1;

    // Return new root
    return y;
} 
/* insertAvlt(avlt* x, int k)
Insert the node with value k in the tree with a root of x then balance the tree if needed.
    - Perform insertion for a bst (recursive method)
    - Update height on the node
    - If the node is unbalanced, rotate the subtree
        { There are four cases for rotation: (Left Left), (Right Right), (Left Right), (Right Left) }
    - Then return the new root
*/
avlt* insertAvlt(avlt* x, int k) {
    // Create New node if x is empty
    if(x == NULL)       return(newNode(k));

    // Recursive method to perform insertion for a bst
    if(k < x->key)      x->left = insertAvlt(x->left, k);
    else if(k > x->key) x->right = insertAvlt(x->right, k);
    else                return x;

    // Update height
    x->height = 1 + greaterInt( avltHeight(x->left), avltHeight(x->right) );
 
    // Get the balance factor
    int bf = getBF(x);
 
    // If unbalanced, rotate
    // (Left Left)
    if(bf > 1 && k < x->left->key) return rotateRight(x);
 
    // (Right Right)
    if(bf < -1 && k > x->right->key) return rotateLeft(x);
 
    // (Left Right)
    if(bf > 1 && k > x->left->key) {
        x->left = rotateLeft(x->left);
        return rotateRight(x);
    }
 
    // (Right Left)
    if(bf < -1 && k < x->right->key) {
        x->right = rotateRight(x->right);
        return rotateLeft(x);
    }
 
    return x;
}
/*  removeAvlt(avlt* x, int k)
Remove the node with value k in the tree with a root of x then balance the tree if needed.
    - Perform deletion for a bst
    - Update height on the node
    - If the node is unbalanced, rotate the subtree
        { There are four cases for rotation: (Left Left), (Right Right), (Left Right), (Right Left) }
    - Then return the new root
*/
avlt* removeAvlt(avlt* x, int k) { 
    // Perform deletion for a bst
    if(x == NULL) return x;
 
    // If k is smaller than the x->key, it is in the left-subtree
    if(k < x->key) x->left = removeAvlt(x->left, k);
 
    // If k is greater than the x->key, it is in the right subtree
    else if(k > x->key) x->right = removeAvlt(x->right, k);
 
    // If k is equal to x->key
    else {
        // If x has a single child or if it is a leaf
        if( (x->left == NULL) || (x->right == NULL) ) {
            avlt* temp = NULL;
            if(x->left == NULL)      temp = x->right;
            else if(x->left != NULL) temp = x->left;

            // If x is a leaf
            if(temp == NULL) {
                temp = x;
                x = NULL;
            } else          // If x has a child
            *x = *temp;     // Copy the contents of the child
            delete temp;    // free the allocated heap memory for temp
        } else {
            // x with two children
            avlt* temp = findMax(x->left);
            x->key = temp->key;
            x->left = removeAvlt(x->left, temp->key);
        }
    }
 
    // If the tree had only one node
    // then return
    if(x == NULL) return x;
 
    // Update height
    x->height = 1 + greaterInt( avltHeight(x->left), avltHeight(x->right) );
 
    // Check if the node is unbalanced, and rotate if it is unbalanced
    int bf = getBF(x);
 
    // (Left Left)
    if(bf > 1 && getBF(x->left) >= 0) return rotateRight(x);
 
    // (Right Right)
    if(bf < -1 && getBF(x->right) <= 0) return rotateLeft(x);    

    // (Left Right)
    if(bf > 1 && getBF(x->left) < 0) {
        x->left = rotateLeft(x->left);
        return rotateRight(x);
    }

    // (Right Left)
    if(bf < -1 && getBF(x->right) > 0) {
        x->right = rotateRight(x->right);
        return rotateLeft(x);
    }
 
    return x;
}
void inOrderT(avlt* x) {
    if(x == NULL) return;
    inOrderT(x->left);
    cout << x->key << " ";
    inOrderT(x->right);
}
void preOrderT(avlt* x) {
    if(x == NULL) return;
    cout << x->key << " ";
    preOrderT(x->left);
    preOrderT(x->right);
}
void postOrderT(avlt* x) {
    if(x == NULL) return;
    postOrderT(x->left);
    postOrderT(x->right);
    cout << x->key << " ";
}
int main() {
    /*
    // An instruction is combined with a character 'A' or 'D' and followed by x~xxx digits, 
    // Or "PRE", "POST", "IN"
        LOOP(input-string-vector[i] until the end of the vector)
        at vector[i].. do..
            if instruction starts with 'A' and followed by some digits
                call insert(root, digits)
            if instruction starts with 'D' and followed by some digits
                call delete(root, digits)
            if instruction is either "POST", "PRE", "IN"
            if root is empty
                print empty
                else if instruction is "POST"
                    call postOrderT(root)
                else if instruction is "PRE"
                    call preOrderT(root)
                else
                    call inOrderT(root)
    */
    // Store all inputs in a vector string
    string inputStr = "";
    string token;
    vector <string> tokens;
    getline(cin, inputStr);
    stringstream ss(inputStr);
    while(getline(ss, token, ' ')) {    // Reads a line from ss until ' ' is reached and assignes it to token
        tokens.push_back(token);        // Push token to the string vector, populate vector "tokens"
    }   

    string dataStr; // digits in string
    int dataInt;    // digits in int   
    unsigned int i = 0;
    avlt* root = NULL;

    while(i < tokens.size()) {
        if(tokens.at(i) == "POST" || tokens.at(i) == "PRE" || tokens.at(i) == "IN") {
            if(root == NULL) cout << "EMPTY" << endl;
            else if (tokens.at(i) == "POST") postOrderT(root);
            else if (tokens.at(i) == "PRE") preOrderT(root);
            else inOrderT(root);
        } else {
            dataStr.append( tokens.at(i).begin()+1,tokens.at(i).end() );
            dataInt = stoi ( dataStr );
            if(tokens.at(i)[0] == 'A') {
                root = insertAvlt(root, dataInt);
            } else /*if(tokens.at(i)[0] == 'D')*/ {
                root = removeAvlt(root, dataInt);
            } 
        }
        i++;
        dataStr = "";
    }

return 0;
}