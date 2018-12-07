#include <iostream>
#include <vector>
#include <string>
#include <sstream>


using namespace std;
class Tree;
class TreeNode {
public:
    friend Tree;
    int data = 0;
    TreeNode *leftChild = 0;
    TreeNode *rightChild = 0;
};

class Tree {
public:
    TreeNode *root = 0;
    vector<int> container;
    int tmp = 0;

    void insert(const int data){
        TreeNode *newNode = new TreeNode;
        newNode -> data = data;
        TreeNode *current = root;
        TreeNode *currentParent = 0;

        while(current != nullptr){
            currentParent = current;
            if(newNode -> data < current -> data){
                current = current -> leftChild;
            }
            else if(newNode -> data > current -> data){
                current = current -> rightChild;
            }
            else{
                cout << "Element " << data << " already existed." << endl;
                return;
            }

        }

        if(currentParent == nullptr){
            root = newNode;
        }
        else if(newNode -> data < currentParent -> data){
            currentParent -> leftChild = newNode;
        }
        else{
            currentParent -> rightChild = newNode;
        }

    };

    vector<int> inorder_traversal(TreeNode *currentNode){
        if(currentNode){
            inorder_traversal(currentNode -> leftChild);
            //cout << currentNode -> data << endl;
            container.push_back(currentNode -> data);
            inorder_traversal(currentNode -> rightChild);
        }

        return container;

    };

    void inorderPrint(TreeNode *currentNode){
        if(currentNode){
            inorderPrint(currentNode -> leftChild);
            cout << currentNode -> data << endl;
            inorderPrint(currentNode -> rightChild);
        }
    }

    TreeNode* search_data(const int data){
        TreeNode *current = root;
        while(current && data != current -> data){
            if(data < current -> data){
                current = current -> leftChild;
            }
            else{
                current = current -> rightChild;
            }
        }

        return current;
    }

    int minelement(const int threshold){
        int accum = 0;
        vector<int> container = inorder_traversal(root);
        for(int i=0; i<container.size(); i++){
            accum += container[i];
            if(accum > threshold){
                return container[i];
            }
        }

        return 0;
    }


    void delete_node(const int data){
        TreeNode *current = root;
        TreeNode *deleteNode = 0;
        TreeNode *deleteNodeParent = 0;
        TreeNode *leftmost = 0;

        while(current && data != current -> data){
            deleteNodeParent = current;
            if(data < current -> data){
                current = current -> leftChild;
            }
            else{
                current = current -> rightChild;
            }

        }

        deleteNode = current;

        if(deleteNode == nullptr){
            cout << "No match." << endl;
            return;
        }

        if(!(deleteNode -> leftChild == nullptr || deleteNode -> rightChild == nullptr)){
            // find leftmost
            leftmost = deleteNode -> leftChild;
            while(leftmost -> rightChild){
                leftmost = leftmost -> rightChild;
            }
            deleteNode -> data = leftmost -> data;
            if(deleteNodeParent){
                deleteNodeParent = deleteNode;
                deleteNode = leftmost;
            }
            else{
                deleteNodeParent = deleteNode -> leftChild;
                deleteNode = leftmost;
            }

        }

        if(deleteNode == deleteNodeParent -> leftChild){
            if(deleteNode -> rightChild == nullptr){
                deleteNodeParent -> leftChild = deleteNode -> leftChild;
            }
            else{
                deleteNodeParent -> leftChild = deleteNode -> rightChild;
            }
        }
        else{
            if(deleteNode -> rightChild == nullptr){
                deleteNodeParent -> rightChild = deleteNode -> leftChild;
            }
            else{
                deleteNodeParent -> rightChild = deleteNode -> rightChild;
            }
        }

    }
};

int main()
{
    string inputs;
    Tree bst;
    vector<string> inputs_vector;
    int action=0, value=0;

    cout << "Please input the sequence of integer with blank separation (ex: 12 34 43 50 66 68): " << endl;
    getline(cin, inputs);

    stringstream stream(inputs);
    while(true) {
        int inp;
        stream >> inp;
        if(!stream){
            break;
        }
        bst.insert(inp);
    }
    cout << "===== Inorder traversal =====" << endl;
    bst.inorderPrint(bst.root);
    cout << "===== Inorder traversal =====" << endl;

    while(true){
        cout << "Please input pair of action and value: (0 = insert, 1 = delete, 2 = minelement)" << endl;
        cout << "Ex: \"insert 3\" = 0 3, \"delete 4\" = 1 4, \"minelement 91\" = 2 91" << endl;

        cin.clear();
        fflush(stdin);

        getline(cin, inputs);
        stringstream stream(inputs);
        stream >> action >> value;

        if(action == 0){
            cout << "===== Print Action =====" << endl;
            cout << "Insert value: " << value << endl;
            cout << "===== Print Action =====" << endl;
            bst.insert(value);
        }
        else if(action == 1){
            cout << "===== Print Action =====" << endl;
            cout << "Delete value: " << value << endl;
            cout << "===== Print Action =====" << endl;
            bst.delete_node(value);
        }
        else if(action == 2){
            cout << "===== Print Action =====" << endl;
            cout << bst.minelement(value) << endl;
            cout << "===== Print Action =====" << endl;
        }
        else{
            cout << "Action: " << action << " not found." << endl;
        }
    }

    system("pause");
    return 0;
}
