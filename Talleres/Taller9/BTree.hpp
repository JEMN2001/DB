#ifndef _BTree_hpp_
#define _BTree_hpp_

#ifndef DEBUG
bool deb = false;
#endif //DEBUG

#ifdef DEBUG
bool deb = true;
#endif //DEBUG


template<typename dataType, typename pointerType>
class BTree {
	private:
		std::size_t n;
		struct node {
			dataType * k;
			node* * p;
			pointerType* * t;
			node * nl;
			std::size_t used;
			node * parent;
		};

		node * root;

		void insert_in_leaf(node * L, dataType k, pointerType * p);
		void insert_in_parent(node * N, dataType k, node * L);

		void remove_entry(node * N, dataType k);

		struct pr {
			node* L;
			std::size_t i;
			pr(node* L, std::size_t i);
		};
		pr Find(dataType V);

		void printTree();

	public:
		BTree(std::size_t n = 2);
		void insert(dataType k, pointerType * p);
		void remove(dataType k);
		pointerType * find(dataType val);

};

#include "BTree.cpp"
#endif //_BTree_hpp_