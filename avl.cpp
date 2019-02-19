/*
 * avl.cpp
 */

#ifndef AVL_CPP
#define AVL_CPP



/* TODO
 * Goal: To find the balance factor of an AVL tree
 *       balance factor = height of right sub-tree - height of left sub-tree
 * Return: (int) balance factor
 */
template <typename T, typename K>
int AVL<T,K>::bfactor() const
{
    //write your codes here
	return this->is_empty() ? 0 : this->right_subtree()->height()-this->left_subtree()->height();
}


/* TODO
 * Goal: To rectify the height values of each node of of an AVL tree 
 */
template <typename T, typename K>
void AVL<T,K>::fix_height() const
{
    //write your codes here
	if (!this->is_empty())
	{
		int l_height = this->left_subtree()->height();
		int r_height = this->right_subtree()->height();
		this->root->bt_height = 1+max(l_height,r_height);
	}
}


/* TODO
 * Goal: To perform a single left (anti-clocwise) rotation of the root 
 */
template <typename T, typename K>
void AVL<T,K>::rotate_left() 
{
    //write your codes here
	bt_node* b = dynamic_cast<AVL*>(this->right_subtree())->root;
	this->right_subtree() = b->left;
	AVL<T,K>* temp_tree = new AVL();
	*temp_tree = *this;
	b->left = temp_tree;
	fix_height();
	this->root = b;
	fix_height();
}


/* TODO
 * Goal: To perform right (clockwise) rotation of the root 
 */
template <typename T, typename K>
void AVL<T,K>::rotate_right()
{
     //write your codes here
	bt_node* b = dynamic_cast<AVL*>(this->left_subtree())->root;
	this->left_subtree() = b->right;
	AVL<T,K>* temp_tree = new AVL();
	*temp_tree = *this;
	b->right = temp_tree;
	fix_height();
	this->root = b;
	fix_height();
}

/* TODO
 * Goal: To balance an AVL tree 
 */
template <typename T, typename K>
void AVL<T,K>::balance()
{
     //write your codes here
	if (this->is_empty())
		return;
	fix_height();
	int b_factor = bfactor();
	if (b_factor == 2)
	{
		if (dynamic_cast<AVL*>(this->right_subtree())->bfactor()<0)
			dynamic_cast<AVL*>(this->right_subtree())->rotate_right();
		return this->rotate_left();
	}
	else if (b_factor == -2)
	{
		if (dynamic_cast<AVL*>(this->left_subtree())->bfactor()>0)
			dynamic_cast<AVL*>(this->left_subtree())->rotate_left();
		return this->rotate_right();
	}
}


/* TODO
 * Goal: To insert an item x with key k to AVL tree
 */
template <typename T, typename K>
void AVL<T,K>::insert(const T& x, const K& k)
{
     //write your codes here
	if (this->is_empty())
	{
		this->root = new bt_node(x,k);
		this->right_subtree() = new AVL();
		this->left_subtree() = new AVL();
	}
	else if (k<this->root->key)
		this->left_subtree()->insert(x,k);
	else if (k>this->root->key)
		this->right_subtree()->insert(x,k);
	balance();
}



/* TODO
 * Goal: To remove an item with key k in AVL tree 
 */
template <typename T, typename K>
void AVL<T,K>::remove(const K& k)
{
     //write your codes here
	if (this->is_empty())
		return;
	if (k<this->root->key)
		dynamic_cast<AVL*>(this->left_subtree())->remove(k);
	else if (k>this->root->key)
		this->right_subtree()->remove(k);
	else
	{
		AVL* left_avl = dynamic_cast<AVL*>(this->left_subtree());
		AVL* right_avl = dynamic_cast<AVL*>(this->right_subtree());
		if (!left_avl->is_empty() && !right_avl->is_empty())
		{
			this->root->value = dynamic_cast<AVL*>(right_avl->find_min())->root->value;
			this->root->key = dynamic_cast<AVL*>(right_avl->find_min())->root->key;
			right_avl->remove(this->root->key);
		}
		else
		{
			bt_node* node_to_remove = this->root;
			*this = left_avl->is_empty() ? *right_avl : *left_avl;
			right_avl->root = left_avl->root = 0;
			delete node_to_remove;
		}
	}
	balance();
}



#endif /* AVL_CPP */
