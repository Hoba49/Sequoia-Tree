#include "sequoia.h"

void Sequoia::insert(int x){
    //similar to avl insertion
    if (root == nullptr) root = new SequoiaNode(x);
    else root->insert(x);
    while(root->parent!=nullptr) root = root->parent;
    size++;
}
void Sequoia::remove(int x){
    //similar to avl deletion
    SequoiaNode* victim = root->search(x);
    if (victim == nullptr) return;
    else if (victim == root) root = victim->remove();
    else victim->remove();
    while(root->parent!=nullptr) root = root->parent;
    size--;
}





