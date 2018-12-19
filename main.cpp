#include <iostream>

using namespace std;


class binarySearchTree;
class treeNode{
private:
    friend binarySearchTree;
    treeNode *leftChild = 0;
    treeNode *rightChild = 0;
    treeNode *parent = 0;
    int leftSize = 0;
    int key = 0;
};

class binarySearchTree{
public:
    treeNode *root = 0;
    void inorderTraversal(treeNode *current){
        if(current){
            inorderTraversal(current -> leftChild);
            current -> leftSize = leftSize(current);
            cout << "treeNode key: " << current -> key << " leftSize: " << current -> leftSize << endl;
            inorderTraversal(current -> rightChild);
        }

    };

    int leftSize(treeNode *current){
        if(current == nullptr){
            return 0;
        }

        return 1 + leftSize(current -> leftChild);
    };

    void insertNode(const int key){
        treeNode *currentNode = root;
        treeNode *currentNodeParent = 0;
        treeNode *newNode = new treeNode;
        newNode -> key = key;
        newNode -> leftSize = 1;

        while(currentNode != nullptr){
            currentNodeParent = currentNode;
            if(key > currentNode -> key){
                currentNode = currentNode -> rightChild;
            }
            else if(key < currentNode -> key){
                currentNode = currentNode -> leftChild;
            }
            else{
                cout << "Element " << key << " already existed." << endl;
                return;
            }
        }
        newNode -> parent = currentNodeParent;
        if(currentNodeParent == nullptr){
            root = newNode;
        }
        else if(key > currentNodeParent -> key){
            currentNodeParent -> rightChild = newNode;
        }
        else{
            currentNodeParent -> leftChild = newNode;
        }

    };

    void transplant(treeNode *current, treeNode *replaced){
        if(current -> parent == nullptr){
            root = replaced;
        }
        else if(current == current -> parent -> leftChild){
            current -> parent -> leftChild = replaced;
        }
        else{
            current -> parent -> rightChild = replaced;
        }

        if(replaced != nullptr){
            replaced -> parent = current -> parent;
        }

    };

    treeNode *findMin(treeNode *current){
        treeNode *minNode = 0;
        while(current -> leftChild != nullptr){
            minNode = current;
            current = current -> leftChild;
        }
        return minNode;

    };

    void deleteNode(const int key){
        // find delete node
        treeNode *current = root;
        treeNode *deleteNode = 0;
        treeNode *y = 0;

        while(current){
            if(current -> key < key){
                current = current -> rightChild;
            }
            else if(current -> key > key){
                current = current -> leftChild;
            }
        }

        deleteNode = current;

        if(deleteNode == nullptr){
            cout << "No match." << endl;
            return;
        }

        if(deleteNode -> leftChild == nullptr){
            transplant(deleteNode, deleteNode -> rightChild);
        }
        else if(deleteNode -> rightChild == nullptr){
            transplant(deleteNode, deleteNode -> leftChild);
        }
        else{
            y = findMin(deleteNode -> rightChild);
            if(y -> parent != deleteNode){
                transplant(y, y -> parent);
                y -> rightChild = deleteNode -> rightChild;
                y -> rightChild -> parent = y;
            }
            transplant(deleteNode, y);
            y -> leftChild = deleteNode -> leftChild;
            y -> leftChild -> parent = y;
        }


    };

    int getRank(int r){
        treeNode *current = root;
        while(current){
            if(r < current -> leftSize){
                current = current -> leftChild;
            }
            else if(r > current -> leftSize){
                r -= current -> leftSize;
                current = current -> rightChild;
            }
            else{
                cout << current -> key << endl;
                return current -> key;
            }
        }

        return 0;
    };

    int avg(const int x, const int y){
        int sum = 0;
        for(int i=x;i<=y;i++){
            sum += getRank(i);
        }
        return sum / (y - x + 1);

    };
};



int main()
{

    binarySearchTree tree;
//    tree.inorderTraversal(tree.root);
    tree.insertNode(20);
    tree.insertNode(17);
    tree.insertNode(36);
    tree.insertNode(14);
    tree.insertNode(22);
    tree.insertNode(48);
    tree.insertNode(28);
    tree.inorderTraversal(tree.root);
    cout << tree.avg(2, 4) << endl;
    tree.inorderTraversal(tree.root);
    return 0;
}
