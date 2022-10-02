#pragma once

#include <cmath>


namespace geometry
{
	template<typename T>
	struct AVL_node
	{
		unsigned depth = 1;
		T root;
		AVL_node* left = nullptr;
		AVL_node* right = nullptr;

		AVL_node() = default;
		explicit AVL_node(const T& val,
						  AVL_node* left_node = nullptr,
						  AVL_node* right_node = nullptr);
		~AVL_node() = default;

		void update_depth();
	};

	template<typename T>
	AVL_node<T>::AVL_node(const T& val,
						  AVL_node* left_node,
						  AVL_node* right_node):
			root(T(val)),
			left(left_node),
			right(right_node)
	{
		update_depth();
	}

	template<typename T>
	void AVL_node<T>::update_depth()
	{
		unsigned left_depth = (left == nullptr) ? 0 : left->depth;
		unsigned right_depth = (right == nullptr) ? 0 : right->depth;

		depth = 1 + std::max(left_depth, right_depth);
	}

	template<typename T>
	class AVL_tree
	{
	public:
		typedef AVL_node<T> Node;

	protected:
		Node* root = nullptr;

	public:
		AVL_tree() = default;
		~AVL_tree();

		virtual bool compare(const T& left,
							 const T& right) const = 0;
		virtual bool are_equal(const T& left,
							   const T& right) const = 0;

		bool is_empty() const;
		unsigned depth() const;
		unsigned size() const;

		Node* find(const T& val) const;
		Node* find_left_neighbour(const T& val) const;
		Node* find_right_neighbour(const T& val) const;

		void insert(const T& val);
		void remove(const T& val);
		void remove(const T& val, bool& found);
		T extract_min();
		T extract_max();

		unsigned nb_miss_depth();

	protected:
		unsigned aux_size(Node* node) const;
		Node* aux_find(const T& val, Node* node) const;
		Node* aux_find_left_neighbour(const T& val,
									  Node* node,
									  Node* candidate) const;
		Node* aux_find_right_neighbour(const T& val,
									   Node* node,
									   Node* candidate) const;

		void aux_insert(const T& val,
						Node*& node);
		void aux_remove(const T& val,
						Node*& node,
						bool& found);

		unsigned depth(Node* node);
		void update_depth(Node*& node);
		void delete_node(Node* node);

		void right_rotation(Node*& node);
		void left_rotation(Node*& node);
		void balance(Node*& node);

		T extract_min(Node*& node);
		T extract_max(Node*& node);
		void remove_node(Node*& node);

		unsigned aux_nb_miss_depth(Node* node);
	};


	// +-----------------------------------------------------------------------+
	// |                         TEMPLATE DEFINITIONS                          |
	// +-----------------------------------------------------------------------+

	template<typename T>
	AVL_tree<T>::~AVL_tree()
	{ delete_node(root); }

	template<typename T>
	bool AVL_tree<T>::is_empty() const
	{ return root == nullptr; }

	template<typename T>
	unsigned AVL_tree<T>::depth() const
	{
		if (root == nullptr)
		{ return 0; }

		return root->depth;
	}

	template<typename T>
	unsigned AVL_tree<T>::aux_size(AVL_node<T>* node) const
	{
		if (node == nullptr)
		{ return 0; }

		return 1 + aux_size(node->left) + aux_size(node->right);
	}

	template<typename T>
	unsigned AVL_tree<T>::size() const
	{ return aux_size(root); }

	template<typename T>
	typename AVL_tree<T>::Node* AVL_tree<T>::aux_find(const T& val,
													  AVL_node<T>* node) const
	{
		if (node == nullptr || are_equal(node->root, val))
		{ return node; }

		if (compare(val, node->root))
		{ return aux_find(val, node->left); }

		return aux_find(val, node->right);
	}

	template<typename T>
	typename AVL_tree<T>::Node* AVL_tree<T>::find(const T& val) const
	{ return aux_find(val, root); }

	template<typename T>
	typename AVL_tree<T>::Node*
	AVL_tree<T>::aux_find_left_neighbour(const T& val,
										 AVL_node<T>* node,
										 AVL_node<T>* candidate) const
	{
		if (node == nullptr)
		{ return candidate; }

		if (compare(val, node->root))
		{ return aux_find_left_neighbour(val, node->left, candidate); }

		return aux_find_left_neighbour(val, node->right, node);
	}

	template<typename T>
	typename AVL_tree<T>::Node*
	AVL_tree<T>::find_left_neighbour(const T& val) const
	{ return aux_find_left_neighbour(val, root, nullptr); }

	template<typename T>
	typename AVL_tree<T>::Node*
	AVL_tree<T>::aux_find_right_neighbour(const T& val,
										  AVL_node<T>* node,
										  AVL_node<T>* candidate) const
	{
		if (node == nullptr)
		{ return candidate; }

		if (compare(node->root, val))
		{ return aux_find_right_neighbour(val, node->right, candidate); }

		return aux_find_right_neighbour(val, node->left, node);
	}

	template<typename T>
	typename AVL_tree<T>::Node*
	AVL_tree<T>::find_right_neighbour(const T& val) const
	{ return aux_find_right_neighbour(val, root, nullptr); }

	template<typename T>
	void AVL_tree<T>::aux_insert(const T& val,
								 Node*& node)
	{
		if (node == nullptr)
		{
			node = new Node(val);
			return;
		}

		if (compare(val, node->root))
		{
			aux_insert(val, node->left);
			node->update_depth();
			balance(node);
			return;
		}

		aux_insert(val, node->right);
		node->update_depth();
		balance(node);
	}

	template<typename T>
	void AVL_tree<T>::insert(const T& val)
	{
		aux_insert(val, root);
		update_depth(root);
	}

	template<typename T>
	void AVL_tree<T>::aux_remove(const T& val,
								 Node*& node,
								 bool& found)
	{
		if (node == nullptr)
		{
			found = false;
			return;
		}

		if (val == node->root)
		{
			found = true;
			remove_node(node);
			return;
		}

		if (compare(val, node->root))
		{
			aux_remove(val, node->left, found);
			balance(node);
			return;
		}

		aux_remove(val, node->right, found);
		balance(node);
	}

	template<typename T>
	void AVL_tree<T>::remove(const T& val)
	{
		bool dummy;
		aux_remove(val, root, dummy);
		update_depth(root);
	}

	template<typename T>
	void AVL_tree<T>::remove(const T& val,
							 bool& found)
	{
		aux_remove(val, root, found);
		update_depth(root);
	}

	template<typename T>
	T AVL_tree<T>::extract_min()
	{ return extract_min(root); }

	template<typename T>
	T AVL_tree<T>::extract_max()
	{ return extract_max(root); }

	template<typename T>
	unsigned AVL_tree<T>::nb_miss_depth()
	{ return aux_nb_miss_depth(root); }

	template<typename T>
	unsigned AVL_tree<T>::aux_nb_miss_depth(AVL_tree::Node* node)
	{
		if (node == nullptr)
		{ return 0; }

		unsigned left_depth = depth(node->left);
		unsigned right_depth = depth(node->right);
		if (node->depth == 1 + std::max(left_depth, right_depth))
		{
			return aux_nb_miss_depth(node->left) +
				   aux_nb_miss_depth(node->right);
		}
		return 1 + aux_nb_miss_depth(node->left) +
			   aux_nb_miss_depth(node->right);
	}

	template<typename T>
	unsigned AVL_tree<T>::depth(AVL_tree::Node* node)
	{
		if (node == nullptr)
		{ return 0; }

		return node->depth;
	}

	template<typename T>
	void AVL_tree<T>::update_depth(Node*& node)
	{
		if (node == nullptr)
		{ return; }

		node->update_depth();
	}

	template<typename T>
	void AVL_tree<T>::delete_node(AVL_tree::Node* node)
	{
		if (node == nullptr)
		{ return; }

		delete_node(node->left);
		delete_node(node->right);
		delete node;
	}

	template<typename T>
	void AVL_tree<T>::right_rotation(AVL_tree::Node*& node)
	{
		T p = node->left->root;
		T q = node->root;

		Node* U = node->left->left;
		Node* V = node->left->right;
		Node* W = node->right;

		delete node->left;
		delete node;

		node = new Node(p, U, new Node(q, V, W));
	}

	template<typename T>
	void AVL_tree<T>::left_rotation(AVL_tree::Node*& node)
	{
		T p = node->root;
		T q = node->right->root;

		Node* U = node->left;
		Node* V = node->right->left;
		Node* W = node->right->right;

		delete node->right;
		delete node;

		node = new Node(q, new Node(p, U, V), W);
	}

	template<typename T>
	void AVL_tree<T>::balance(Node*& node)
	{
		if (node == nullptr)
		{ return; }

		int diff = depth(node->left) - depth(node->right);

		if (diff == 2)
		{
			if (node->left != nullptr &&
				depth(node->left->left) < depth(node->left->right))
			{
				left_rotation(node->left);
				node->update_depth();
				right_rotation(node);
				return;
			}

			right_rotation(node);
			return;
		}

		if (diff == -2)
		{
			if (node->right != nullptr &&
				depth(node->right->right) < depth(node->right->left))
			{
				right_rotation(node->right);
				node->update_depth();
				left_rotation(node);
				return;
			}

			left_rotation(node);
			return;
		}
	}

	template<typename T>
	T AVL_tree<T>::extract_min(AVL_tree::Node*& node)
	{
		if (node->left == nullptr)
		{
			T min = node->root;
			Node* right = node->right;
			delete node;

			node = right;
			return min;
		}

		T min = extract_min(node->left);
		node->update_depth();
		balance(node);
		return min;
	}

	template<typename T>
	T AVL_tree<T>::extract_max(AVL_tree::Node*& node)
	{
		if (node->right == nullptr)
		{
			T max = node->root;
			Node* left = node->left;
			delete node;

			node = left;
			return max;
		}

		T max = extract_max(node->right);
		node->update_depth();
		balance(node);
		return max;
	}

	template<typename T>
	void AVL_tree<T>::remove_node(AVL_tree::Node*& node)
	{
		if (node->right != nullptr)
		{
			node->root = extract_min(node->right);
			node->update_depth();
			balance(node);
			return;
		}

		Node* left = node->left;
		delete node;

		node = left;
	}
}