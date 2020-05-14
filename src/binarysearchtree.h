#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <iostream>
using namespace std;
template <class keyType,class dataType>
class node{
public:
    node(){
        left = right = NULL;
    }
    node(keyType key,dataType data){
        this->key = key;
        this->data = data;
        left = right = NULL;
    }
    keyType key;
    dataType data;
    node* left;
    node* right;
};

template <class keyType,class dataType>
class BinarySearchTree
{
private:
    int sz, idx;
    node<keyType,dataType>* root;
    node<keyType,dataType>** arr;
    bool insertt(node<keyType,dataType>*& ptr,keyType key,dataType data){
        if(ptr==NULL){
            ptr = new node<keyType,dataType>(key,data);
            return true;
        }else if (ptr->key == key)
            return false;
        else if(key<ptr->key)
            return insertt(ptr->left,key,data);
        else
            return insertt(ptr->right,key,data);
    };
    bool isEmpty(node<keyType,dataType>*)const{
        return root;
    }

    void clear(node<keyType,dataType>*& ptr){
        if(ptr!=NULL){
           clear(ptr->left);
           clear(ptr->right);
           delete ptr;
        }
    }

    void inOrder(node<keyType,dataType>*& t){
        if (t){
            if(t->left) inOrder(t->left);
            *(arr+idx) = t;
            idx++;
            if(t->right)inOrder(t->right);
        }
    };
    node<keyType,dataType>* inOrderSuccessor(node<keyType,dataType>* rootNode, node<keyType,dataType>* nodeTofind) {
        if (!rootNode || !nodeTofind) return NULL;
        node<keyType,dataType>* successor = NULL;
        if (nodeTofind->right){
            successor = nodeTofind->right;
            while (successor->left) {
                successor = successor->left;
            }
        }
        else {
            while (rootNode) {
                if (nodeTofind->key < rootNode->key) {
                    successor = rootNode;
                    rootNode = rootNode->left;
                }
                else if (nodeTofind->key > rootNode->key) {
                    rootNode = rootNode->right;
                }
                else {
                    break;
                }
            }
        }
        return successor;
    };

    node<keyType,dataType>* getParent(node<keyType,dataType>*& ptr,node<keyType,dataType>*& parent, keyType key){
        if(ptr==NULL){
            return NULL;
        }else if(ptr->key==key){
            return parent;
        }else if(key<ptr->key){
            return getParent(ptr->left,ptr,key);
        }else{
            return getParent(ptr->right,ptr,key);
        }
    };
public:
    BinarySearchTree(){
        sz = 0;
        root = NULL;
        arr = NULL;
    };

    ~BinarySearchTree(){
        clear();
    };
    void clear(){
        if(root!=NULL)
            clear(root);
        sz = 0;
        root=NULL;
        idx=0;
        if(arr!=NULL){
            delete arr;
            arr=NULL;
        }
    }
    bool insert(keyType key,dataType data){
        if(insertt(root,key,data)==true){
            sz++;
            return true;
        }else{
            return false;
        }
    };

    bool isEmpty()const{
        return isEmpty(root);
    };

    bool search(keyType key){
        return searchAndReturnPointer(root,key) ? true:false;
    };

    node<keyType,dataType>* searchAndReturnPointer(node<keyType,dataType>*& ptr, keyType key){
        if(!ptr){
            return NULL;
        }else if (ptr->key == key)
            return ptr;
        else if(key<ptr->key)
            return searchAndReturnPointer(ptr->left, key);
        else
            return searchAndReturnPointer(ptr->right, key);
    };

    bool retrieve(const keyType key,dataType& data){
        node<keyType,dataType>* recievedData = searchAndReturnPointer(root,key);
        if(recievedData!=NULL){
            data=recievedData->data;
            return true;
        }else{
            return false;
        }
    };
    void printInorder(){
        inOrder();
        for(int i = 0; i<idx; i++){
            cout<<arr[i]->key.toStdString();
        }cout<<endl;
    }
    bool remove(keyType key){
        node<keyType,dataType>* dataPtr = searchAndReturnPointer(root,key);
        if(dataPtr!=NULL){
            bool doDelete;
            node<keyType,dataType>* dataPtrParent = NULL;
            dataPtrParent = getParent(root,dataPtrParent,key);
            if(dataPtr->left!=NULL && dataPtr->right!=NULL){
                node<keyType,dataType>* successor = inOrderSuccessor(root,dataPtr);
                node<keyType,dataType>* successorParent = NULL;
                successorParent = getParent(root,successorParent,successor->key);

                if(successor==NULL){
                    dataPtr=dataPtrParent->right;
                    dataPtrParent->right = NULL;
                }else{
                    dataPtr->data = successor->data;
                    dataPtr->key = successor->key;
                    dataPtr=successor;
                    if(dataPtr->right!=NULL){
                        dataPtr->key=dataPtr->right->key;
                        dataPtr->data=dataPtr->right->data;
                        dataPtr->right=dataPtr->right->right;
                        doDelete = false;
                    }else{
                        if(successorParent->left==dataPtr){
                            successorParent->left=NULL;
                        }else if(successorParent->right==dataPtr){
                            successorParent->right=NULL;
                        }
                        doDelete = true;
                    }
                }
            }else{
                node<keyType,dataType>* s;
                if(dataPtr->left!=NULL){
                    s=dataPtr->left;
                }else if(dataPtr->right!=NULL){
                    s=dataPtr->right;
                }else{
                    s=NULL;
                }
                if(dataPtrParent==NULL){
                    root=s;
                }else if(dataPtr==dataPtrParent->left){
                    dataPtrParent->left=s;
                }else{
                    dataPtrParent->right=s;
                }
                doDelete = true;
            }

            if(doDelete){
                delete dataPtr;
            }

            sz--;
            return true;
        }else{
            return false;
        }
    };

    int size(){return sz;}
    node<keyType,dataType>* getRoot(){
        return root;
    };

    void inOrder(){
        idx = 0;
        if(arr!=NULL){
            delete arr;
            arr=NULL;
        }
        arr = new node<keyType,dataType>*[sz];
        inOrder(root);
    };

    node<keyType,dataType>* operator[](int i){
        return *(arr+i);
    };
};

#endif // BINARYSEARCHTREE_H
