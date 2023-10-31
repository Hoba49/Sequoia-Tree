#include "sequoia.h"
//Similar to avl insertion but different fixbalance
void SequoiaNode::insert(int x){
    //TODO: modify from basic BST insertion
    if (x < value){
        //Left
        if (left == nullptr){
            left = new SequoiaNode(x);
            left->parent = this;
            this->fixBalanceInsert();
        }
        else left->insert(x);
    }
    else{
        //Right
        if (right == nullptr){
            right = new SequoiaNode(x);
            right->parent = this;
            this->fixBalanceInsert();
        }
        else right->insert(x);
    }
}
//similar to avl deletion but different fixbalance
SequoiaNode* SequoiaNode::remove(){
    //TODO: modify BST node remove
    SequoiaNode* root = nullptr;
    //Leaf deletion
    if (left == nullptr && right == nullptr){
        if (parent == nullptr) root = nullptr;
        else if (parent->left == this) parent->left = nullptr;
        else parent->right = nullptr;
        delete this;
    }
    //Single child deletion
    else if((left != nullptr && right == nullptr) || (right != nullptr && left == nullptr)){
        SequoiaNode* child;
        if (left != nullptr) child = left;
        else child = right;

        child->parent = parent;
        if (parent == nullptr) root = child;
        else if (parent->left == this) parent->left = child;
        else parent->right = child;
        left = right = nullptr;
        delete this;
    }
    else //double child deletion
    {
        //Swap node is max(lhs)
        SequoiaNode* swap = left;
        while (swap->right != nullptr) swap = swap->right;
        //Swap data values between swap & victim
        int temp = swap->value;
        swap->value = value;
        value = temp;
        //Delete swap node (0 or 1 children)
        swap->remove();
    }
    if(parent!=nullptr) parent->fixBalanceRemove();
    return root;
}

//fixing balance after insertion based on Sequoia tree rules
void SequoiaNode::fixBalanceInsert(){
    updateHeight();
    //if both children are null make recursive call to parent
    if(right == nullptr || left== nullptr){
        if(parent != nullptr) parent->fixBalanceInsert();
        return;
    }
    //if not tall check for case 1 and 2
    if(!isTall()){
        //case 1
        if(right->height > left->height){
            left->rotateRight();
            //parent->updateHeight();
            //parent->fixBalanceInsert();
        }
        //case 2
        else if(left->height >= right->height){
            right->rotateLeft();
            //parent->updateHeight();
           // parent->fixBalanceInsert();
        }
    }
    //perform recursive call on parent if it's not null
    if(parent!=nullptr) parent->fixBalanceInsert();
}

//fixing balance after deletion based on Sequoia tree rules
void SequoiaNode::fixBalanceRemove(){
    updateHeight();
    //if not tall check for cases 1 and 2
    if(!isTall()){
        //case 1
        if(right->height > left->height){
            left->rotateRight();
            parent->updateHeight();
            //return;
        }
        //case 2
        else if(left->height >= right->height){
            right->rotateLeft();
            parent->updateHeight();
            //return;
        }
    }
    if(parent!=nullptr) parent->fixBalanceRemove();

}

//normal avl right rotation
void SequoiaNode::rotateRight(){
    SequoiaNode* innerChild = right;
    SequoiaNode* grandparent = parent->parent;
    this->right = parent;
    this->right->parent = this;
    parent->left = innerChild;
    if (innerChild != nullptr)
        innerChild->parent = parent;
    if (grandparent != nullptr && parent->value < grandparent->value)
        grandparent->left = this;
    else if (grandparent != nullptr)
        grandparent->right = this;
    parent = grandparent;
}
//normal avl left rotation
void SequoiaNode::rotateLeft(){
    SequoiaNode* innerChild = left;
    SequoiaNode* grandparent = parent->parent;
    this->left = parent;
    this->left->parent = this;
    parent->right = innerChild;
    if (innerChild != nullptr)
        innerChild->parent = parent;
    if (grandparent != nullptr && parent->value < grandparent->value)
        grandparent->left = this;
    else if (grandparent != nullptr)
        grandparent->right = this;
    parent = grandparent;
}
//normal avl search
SequoiaNode* SequoiaNode::search(int x){
    if (x == value) return this;

    else if (x < value)
        if (left != nullptr) return left->search(x);
        else return nullptr;

    else if (right != nullptr) return right->search(x);
    else return nullptr;
}

//function to update height after making changes like rotations
void SequoiaNode::updateHeight(){
    //if no children then height is 1
    if (left == nullptr && right == nullptr){
        height = 1;
        return;
    }
    //if two children then height is height of greater child +1
    if(left!=nullptr && right!=nullptr){
        if(left->height > right->height) height = left->height +1;
        else height = right->height +1;
        return;
    }
    //if one child then height is height of that child +1
    if (left == nullptr) height = right->height+1;
    else height = left->height+1;

}
