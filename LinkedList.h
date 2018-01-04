//
// Created by isavillamiel on 12/7/17.
//

#ifndef PROJECT_9B_LINKEDLIST_H
#define PROJECT_9B_LINKEDLIST_H
#include <iostream>
#include "String.h"


using namespace std;

class Node {
public:
    String operand;
    int val;
    Node* next;

    Node(){
        operand = "nothing";
        val = 0;
        next = nullptr;
    }
};

class LinkedList {
private:
    int size;
    Node* root;
    void destroy();
    void copy(LinkedList& other);

public:
    LinkedList();
    LinkedList(LinkedList& other);
    ~LinkedList();
    LinkedList& operator=(LinkedList& other);

    void insert(int val);
    void remove(int val);
    bool find(int val);
    void print();
    void insert_end(int val);
    void insert_end(const char* operand);
    void insert(const char* operand);
    int length();
    int apply();
    String& applyO();
    bool isOp(){
        return (root->operand == "nothing")? false : true;
    };



};
LinkedList::LinkedList() {
    size = 0;
    root = NULL;
}

LinkedList::LinkedList(LinkedList& other) {
    copy(other);
}

LinkedList& LinkedList::operator=(LinkedList& other) {
    if (this != &other) {
        destroy();
        copy(other);
    }
    return *this;
}

LinkedList::~LinkedList() {
    destroy();
}
String& LinkedList::applyO(){
    String& ret = root->operand;
    root = root->next;
    return ret;
}
int LinkedList::apply(){                // returns int, deletes node prev
    int res = root->val;                 // changes root to be next
    root = root->next;
    return res;
}


void LinkedList::copy(LinkedList& other) {

    root = NULL;
    if (other.root == NULL)
        return;
    insert(other.root->val);
    Node* my_current = root;
    Node* other_current = other.root;
    while (other_current->next != NULL) {
        my_current->next = new Node();
        my_current->next->val = other_current->next->val;
        my_current = my_current->next;
        other_current = other_current->next;
    }
}

void LinkedList::destroy() {
    Node* prev;
    Node* current = root;
    while (current != NULL) {
        prev = current;
        current = current->next;
        delete prev;
    }
}
// use this one
void LinkedList::insert(int val) {
    Node* n = new Node();
    n->val = val;
    n->next = root;
    n->operand = "nothing";
    root = n;
    size++;
}
void LinkedList::insert(const char* operand) {
    Node* n = new Node();
    // how to properly copy operand
    n->operand = (String)operand;
    n->next = root;
    n->val = 0;
    root = n;
    size++;
}
int LinkedList::length(){
    return size;
}
void LinkedList::insert_end(const char* operand){
    Node* n = new Node();
    n->val = 0;
    n->operand = (String)operand;
    if (root == NULL) {
        root = n;
        return;
    }

    Node* nxt = root;
    while (nxt->next != NULL) {
        nxt = nxt->next;
    }
    nxt->next = n;

}
void LinkedList::insert_end(int val) {
    Node* n =   new Node();
    n->val = val;
    if (root == NULL) {
        root = n;
        return;
    }

    Node* nxt = root;
    while (nxt->next != NULL) {
        nxt = nxt->next;
    }
    nxt->next = n;
}

// Removes only the first element with the given value.
void LinkedList::remove(int val) {
    Node* prev = NULL;
    Node* current = root;
    while (current != NULL && current->val != val) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        // Element not in the list.
        return;
    }

    if (prev == NULL) {
        root = current->next;
    } else {
        prev->next = current->next;
    }

    size--;

    delete current;
}

void LinkedList::print() {
    Node *current = root;
    cout << "{";
    while (current != NULL) {
        cout << current->val << " ";
        current = current->next;
    }
    cout << "}" << endl;
}

bool LinkedList::find(int val) {
    for (Node *current = root; current != NULL; current = current->next) {
        if (current->val == val) {
            return true;
        }
    }
    return false;
}
#endif //PROJECT_9B_LINKEDLIST_H
