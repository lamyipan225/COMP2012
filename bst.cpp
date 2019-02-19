/*
 * bst.cpp
 *
 */

#ifndef BST_CPP
#define BST_CPP


/* TODO
 * Goal: To search for an item x with key k from the BST tree
 * Return: A pointer to the subtree whose root node contains the item if found,
 *         otherwise a NULL pointer.
 */
template <typename T, typename K>
BT<T,K>* BST<T,K>::search(const K& k)
{
    //write your codes here
	if (this->is_empty())
		return NULL;
	if (this->root->key==k)
		return this;
	else if (k<this->root->key)
		return this->left_subtree()->search(k);
	else return this->right_subtree()->search(k);
}


/* TODO
 * Goal: To find the minimum node stored in a BST tree.
 * Return: A pointer to the subtree whose root node contains the minimum key
 */
template <typename T, typename K>
BT<T,K>* BST<T,K>::find_min()
{
    //write your codes here
	BT<T,K>* left_BT = this->left_subtree();
	if (left_BT->is_empty())
		return this;
	return left_BT->find_min();
}


/* TODO
 * Goal: To insert an item x with key k to a BST tree 
 */
template <typename T, typename K>
void BST<T,K>::insert(const T& x, const K& k)
{
    //write your codes here
	if (this->is_empty())
	{
		this->root = new bt_node(x,k);
		this->right_subtree() = new BST();
		this->left_subtree() = new BST();
	}
	else if (k<this->root->key)
		this->left_subtree()->insert(x,k);
	else if (k>this->root->key)
		this->right_subtree()->insert(x,k);
}


/* TODO
 * Goal: To remove an item with key k in a BST tree 
 */
template <typename T, typename K>
void BST<T,K>::remove(const K& k)
{    
    //write your codes here
	if (this->is_empty())
		return;
	if (k<this->root->key)
		dynamic_cast<BST*>(this->left_subtree())->remove(k);
	else if (k>this->root->key)
		this->right_subtree()->remove(k);
	else
	{
		BST* left_bst = dynamic_cast<BST*>(this->left_subtree());
		BST* right_bst = dynamic_cast<BST*>(this->right_subtree());
		if (!left_bst->is_empty() && !right_bst->is_empty())
		{
			this->root->value = dynamic_cast<BST*>(right_bst->find_min())->root->value;
			this->root->key = dynamic_cast<BST*>(right_bst->find_min())->root->key;
			right_bst->remove(this->root->key);
		}
		else
		{
			bt_node* node_to_remove = this->root;
			*this = left_bst->is_empty() ? *right_bst : *left_bst;
			right_bst->root = left_bst->root = 0;
			delete node_to_remove;
		}
	}
}


/* TODO
 * Goal: Clear the node stack and set current pointer to the root 
 */
template<typename T, typename K>
void BST<T,K>::iterator_init()
{
    //write your codes here
	this->current = this->root;
	while (!this->istack.empty())
		this->istack.pop();
}


/* TODO
 * Goal: Check whether the next smallest node exists 
 */
template<typename T, typename K>
bool BST<T,K>::iterator_end()
{
    //write your codes here
	return !(this->current!=0||!this->istack.empty());
}


/* TODO
 * Goal: Return the value of next smallest node from the tree 
 */
template<typename T, typename K>
T& BST<T,K>::iterator_next()
{
    //write your codes here
	while (this->current!=0)
	{
		this->istack.push(this->current);
		this->current = dynamic_cast<BST*>(this->current->left)->root;
	}
	this->current = this->istack.top();
	this->istack.pop();
	bt_node* next = this->current;
	this->current = dynamic_cast<BST*>(this->current->right)->root;
	return next->value;
}


#endif /* BST_CPP */
