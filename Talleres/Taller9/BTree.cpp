#ifndef _BTree_cpp_
#define _BTree_cpp_

#include "BTree.hpp"
#include <cmath>


template<typename dataType, typename pointerType>
BTree<dataType, pointerType>::pr::pr(node* L, std::size_t i) {
	this->L = L;
	this->i = i;
}

template <typename dataType, typename pointerType>
typename BTree<dataType, pointerType>::pr BTree<dataType, pointerType>::Find(dataType v) {
	if(deb) {
		std::cout<<"---------------------------"<<std::endl;
		std::cout << "Voy a buscar " << v << std::endl;
	}
	node * C = this->root;
	while (C->t == nullptr) {
		std::size_t i;
		for (i = 0; i < C->used; ++i) {
			if (v <= C->k[i])
				break;
		}
		if (i == C->used) {
			if (deb)
				std::cout << "Me voy a C->p[" << i << "]" << std::endl;
			C = C->p[i];
		}
		else if (v == C->k[i]) {
			if (deb)
				std::cout << "Me voy a C->p[" << i+1 << "]" << std::endl;
			C = C->p[i+1];
		}
		else {
			if (deb)
				std::cout << "Me voy a C->p[" << i << "]" << std::endl;
			C = C->p[i];
		}
	}
	if (deb)
		std::cout << "En este nodo hay " << C->used << " elementos" << std::endl;
	for (std::size_t i = 0; i < C->used; ++i) {
		if (deb)
			std::cout << "C->k[" << i << "] = " << C->k[i] << " y v " << " = " << v << std::endl;
		if (C->k[i] == v) {
			if (deb)
				std::cout << "encontre " << v << std::endl;
			return pr(C,i);
		}
	}
	if (deb)
		std::cout << "No pude encontrar " << v << std::endl;
	return pr(C,n+2);
}

template<typename dataType, typename pointerType>
void BTree<dataType, pointerType>::insert(dataType k, pointerType * p) {
	node * L;
	pr par = Find(k);
	if (par.i < n+2)
		return;
	if (deb) {
		std::cout << "Voy a insertar " << k << std::endl;
	}
	L = par.L;
	if (deb)
		std::cout << "Esta hoja tiene " << L->used << " elementos" << std::endl;
	if (L->used < n-1) {
		if (deb)
			std::cout << "Por lo que solo tengo que poner " << k << " en su lugar" << std::endl;
		insert_in_leaf(L, k, p);
	}
	else {
		if (deb)
			std::cout << "Por lo que no puedo poner "<<k<<" asi como asi"<<std::endl;
		node * L2 = new node;
		L2->k = new dataType[n-1];
		L2->t = new pointerType*[n-1];
		L2->p = nullptr;
		for (std::size_t j = 0; j < n-1; ++j)
			L2->t[j] = nullptr;
		node * T = new node;
		T->t = new pointerType*[n];
		T->k = new dataType[n];
		for (std::size_t i = 0; i < n-1; ++i) {
			T->t[i] = L->t[i];
			T->k[i] = L->k[i];
		}
		T->used = L->used;
		insert_in_leaf(T, k, p);
		L2->nl = L->nl;
		L->nl = L2;
		delete L->k;
		L->t = new pointerType*[n-1];
		L->k = new dataType[n-1];
		std::size_t tmp = ceil(n/2.0);
		if (deb){
			std::cout << "el techo de "<<n<<"/2 es " << tmp << std::endl;
			std::cout << "Voy a copiar los datos de T en L desde 0 hasta " << tmp-1 <<std::endl;
		}
		for (std::size_t i = 0; i < tmp; ++i) {
			L->t[i] = T->t[i];
			L->k[i] = T->k[i];
		}
		if (deb)
			std::cout<<"Ahora toca copiar de T de "<<tmp<<" hasta "<<n-1<<" en L2 de "<<0<<" hasta "<<n-1-tmp<<std::endl;
		for (std::size_t i = tmp; i < n; ++i) {
			L2->t[i-tmp] = T->t[i];
			L2->k[i-tmp] = T->k[i];
		}
		L2->used = n-tmp;
		L->used = tmp;
		if (deb) {
			std::cout << "L2 tiene " << L2->used << " elementos"<<std::endl;
			std::cout << "L tiene " << L->used << " elementos"<<std::endl;
		}
		dataType k2 = L2->k[0];
		if (deb)
			std::cout << "tengo que meter "<<k2<<" en el padre"<<std::endl;
		insert_in_parent(L, k2, L2);
	}
	if (deb) {
		std::cout << "Ya inserte " << k << std::endl;
		printTree();
		std::cout<<"---------------------------"<<std::endl;
	}
}

template<typename dataType, typename pointerType>
void BTree<dataType, pointerType>::insert_in_leaf(node * L, dataType k, pointerType * p) {
	std::size_t pos = 0;
	for (;pos < L->used; ++pos) {
		if (L->k[pos] > k) {
			break;
		}
	}
	if (deb)
		std::cout << "La posicion de k es "<<pos<<std::endl;
	for (std::size_t i = L->used; i > pos; --i) {
		L->k[i] = L->k[i-1];
		L->t[i] = L->t[i-1];
	}
	L->k[pos] = k;
	L->t[pos] = p;
	L->used++;
	if (deb)
		std::cout << "Ya puse " << k << " en su hoja y ahora hay " << L->used << " elementos" << std::endl;
}

template<typename dataType, typename pointerType>
void BTree<dataType, pointerType>::insert_in_parent(node * N, dataType k2, node * N2) {
	if (this->root == N) {
		if (deb)
			std::cout<<"No hay padre, soy la raiz"<<std::endl;
		node * R = new node;
		R->parent = nullptr;
		R->k = new dataType[n-1];
		R->k[0] = k2;
		R->t = nullptr;
		R->p = new node*[n];
		for (std::size_t i = 2; i < n; ++i) {
			R->p[i] = nullptr;
		}
		R->p[0] = N;
		R->p[1] = N2;
		R->used = 1;
		N->parent = R;
		N2->parent = R;
		R->nl = nullptr;
		this->root = R;
		if (deb)
			std::cout << "Ya meti " << k2 << " en la raiz"<<std::endl;
		return;
	}
	node * P = N->parent;
	if (P->used < n-1) {
		if (deb)
			std::cout << "Al padre le cabe "<<k2<<std::endl;
		std::size_t pos = 0;
		for (; pos <= P->used; ++pos) {
			if (P->p[pos] == N) {
				break;
			}
		}
		if (deb)
			std::cout <<"N esta en la posicion "<<pos<<std::endl;
		for (std::size_t j = P->used; j > pos; --j) {
			P->k[j] = P->k[j-1];
			P->p[j+1] = P->p[j];
		}
		P->k[pos] = k2;
		P->p[pos+1] = N2;
		P->used++;
		if (deb)
			std::cout <<"Ahora P tiene "<<P->used<<" elementos"<<std::endl;
		N2->parent = P;
	}
	else {
		if (deb)
			std::cout<<"Al padre no le cabe "<<k2<<std::endl;
		node * T = new node;
		T->k = new dataType[n];
		T->p = new node*[n+1];
		for (std::size_t j = 0; j < n-1; ++j) {
			T->k[j] = P->k[j];
			T->p[j] = P->p[j];
		}
		T->p[n-1] = P->p[n-1];
		std::size_t pos = 0;
		for (; pos < n; ++pos) {
			if (T->p[pos] == N) {
				break;
			}
		}
		if (deb)
			std::cout<<"N esta en la posicion "<<pos<<std::endl;
		for (std::size_t j = n-1; j > pos; --j) {
			T->k[j] = T->k[j-1];
			T->p[j+1] = T->p[j];
		}
		T->k[pos] = k2;
		T->p[pos+1] = N2;
		delete P->k;
		P->p = new node*[n];
		P->k = new dataType[n-1];
		node * P2 = new node;
		P2->k = new dataType[n-1];
		P2->p = new node*[n];
		P2->t = nullptr;
		P2->nl = P->nl;
		P->nl = P2;
		for (std::size_t j = 0; j < n; ++j) {
			P->p[j] = nullptr;
			P2->p[j] = nullptr;
		}
		std::size_t tmp = ceil(n/2.0);
		if (deb)
			std::cout<<"Voy a copiar T de 0 a "<<tmp-2<<" en P de 0 a "<<tmp-2<<std::endl;
		for (std::size_t j = 0; j < tmp-1; ++j) {
			P->p[j] = T->p[j];
			P->p[j]->parent = P;
			P->k[j] = T->k[j];
		}
		P->p[tmp-1] = T->p[tmp-1];
		P->p[tmp-1]->parent = P;
		P->used = tmp-1;
		if (deb) {
			std::cout<<"P tiene "<<P->used<<" elementos"<<std::endl;
			std::cout<<"Voy a copiar T de "<<tmp<<" a "<<n-1<<" en P2 de 0 a "<<n-1-tmp<<std::endl;
		}
		for (std::size_t j = tmp; j < n; ++j) {
			P2->p[j-tmp] = T->p[j];
			T->p[j]->parent = P2;
			P2->k[j-tmp] = T->k[j];
		}
		P2->p[n-tmp] = T->p[n];
		T->p[n]->parent = P2;
		P2->used = n-tmp;
		if (deb)
			std::cout<<"P2 tiene "<<P2->used<<" elementos"<<std::endl;
		dataType k3 = T->k[tmp-1];
		if (deb)
			std::cout<<"Ahora hay que meter "<<k3<<" en el padre de P"<<std::endl;
		insert_in_parent(P,k3,P2);
	}
}

template<typename dataType, typename pointerType>
pointerType * BTree<dataType, pointerType>::find(dataType k) {
	pr par = Find(k);
	if(par.i == n+2)
		return nullptr;
	return par.L->t[par.i];
}

template<typename dataType, typename pointerType>
void BTree<dataType, pointerType>::remove(dataType k) {
	pr par = Find(k);
	if (par.i == n+2) {
		return;
	}
	remove_entry(par.L, k);
	if (deb) {
		std::cout<<"Ya elimine "<<k<<std::endl;
		printTree();
		std::cout<<"---------------------------"<<std::endl;
	}
}

template<typename dataType, typename pointerType>
void BTree<dataType, pointerType>::remove_entry(node * N, dataType k) {
	if (deb) {
		std::cout<<"Voy a eliminar "<<k<<" de |";
		for (std::size_t j = 0; j < N->used; ++j) {
			std::cout<<" "<<N->k[j]<<" ";
		}
		std::cout<<"|"<<std::endl;
	}
	bool min = true;
	if (deb)
		std::cout<<"Este nodo tiene "<<N->used<<" elementos"<<std::endl;
	for (std::size_t pos = 0; pos< N->used; ++pos) {
		if  (N->k[pos] > k){
			N->k[pos-1] = N->k[pos];
			if (N->t == nullptr) {
				if (min) {
					delete N->p[pos];
					min = false;
				}
				N->p[pos] = N->p[pos+1];
			}
			else {
				if (min) {
					delete N->t[pos-1];
					min = false;
				}
				N->t[pos-1] = N->t[pos];
			}
		}
	}
	if (min) {
		if (N->t == nullptr) {
			delete N->p[N->used];
		}
		else {
			delete N->t[N->used-1];
		}
	}
	if (N->t == nullptr) {
		N->p[N->used] = nullptr;
	}
	else {
		N->t[N->used-1] = nullptr;
	}
	N->used--;
	if (deb)
		std::cout << "Ahora el nodo tiene "<<N->used<<" elementos"<<std::endl;
	if (N == this->root && N->t != nullptr) {
		if (deb)
			std::cout<<"La raiz era una hoja, entonces no hay que hacer mas"<<std::endl;
		return;
	}
	if (N == this->root && N->used == 0) {
		if (deb)
			std::cout<<"La raiz esta vacia, por lo que su hijo pasa a ser la raiz"<<std::endl;
		this->root = N->p[0];
		N->p[0] = nullptr;
		delete N;
		return;
	}
	if (N == this->root && N->t == nullptr) {
		if (deb)
			std::cout<<"El nodo es la raiz y tiene mas de un hijo, no hay que hacer mas"<<std::endl;
		return;
	}
	if (N->used < ceil(n/2.0)-1) {
		if (deb)
			std::cout<<"El nodo tiene menos de "<<ceil(n/2.0)-1<<" elementos"<<std::endl;
		node * P = N->parent;
		std::size_t pos = 0;
		for (; pos <= P->used; ++pos) {
			if (P->p[pos] == N)
				break;
		}
		if (deb)
			std::cout<<"N esta en la posicion "<<pos<<std::endl;
		node * N2;
		dataType k2;
		if (pos > 0) {
			N2 = P->p[pos-1];
			k2 = P->k[pos-1];
			if (deb)
				std::cout<<"Tengo hermano izquierdo y nos separa "<<k2<<std::endl;
		}
		else {
			N2 = P->p[pos+1];
			k2 = P->k[pos];
			if(deb)
				std::cout<<"No tengo hermano izquierdo y "<<k2<<" me separa de mi hermano derecho"<<std::endl;
		}
		if (N->t == nullptr && N->used + N2->used + 2 <= n) {
			if (deb)
				std::cout<<"No soy hoja y me puedo fusionar con mi hermano"<<std::endl;
			if (pos == 0) {
				node * tmp = N;
				N = N2;
				N2 = tmp;
			}
			N2->k[N2->used] = k2;
			for (std::size_t j = N2->used+1; j < N->used+N2->used+1; ++j) {
				N2->k[j] = N->k[j-N2->used-1];
				N2->p[j] = N->p[j-N2->used-1];
				N2->p[j]->parent = N2;
				N->p[j-N2->used-1] = nullptr;
			}
			N2->p[N->used+N2->used+1] = N->p[N->used];
			N2->p[N->used+N2->used+1]->parent = N2;
			N->p[N->used] = nullptr;
			N2->used = N->used+N2->used+1;
			if (deb) {
				std::cout<<"Quedo un nodo de "<<N2->used<<" elementos"<<std::endl;
				std::cout<<"Ahora hay que sacar "<<k2<<" de mi padre |";
				for (std::size_t j = 0; j < N->parent->used; ++j) {
					std::cout<<" "<<N->parent->k[j]<<" ";
				}
				std::cout<<"|"<<std::endl;
			}
			N2->nl = N->nl;
			remove_entry(P, k2);
		}
		else if (N->t != nullptr && N->used+N2->used < n) {
			if (deb)
				std::cout<<"Soy hoja y me puedo fusionar con mi hermano"<<std::endl;
			if (pos == 0) {
				node * tmp = N;
				N = N2;
				N2 = tmp;
			}
			for (std::size_t j = N2->used; j < N->used+N2->used; ++j) {
				N2->k[j] = N->k[j-N2->used];
				N2->t[j] = N->t[j-N2->used];
			}
			N2->nl = N->nl;
			N2->used += N->used;
			if (deb) {
				std::cout<<"Quedo un nodo de "<<N2->used<<" elementos"<<std::endl;
				std::cout<<"Ahora hay que sacar "<<k2<<" de mi padre |";
				for (std::size_t j = 0; j < P->used; ++j) {
					std::cout<<" "<<P->k[j]<<" ";
				}
				std::cout<<"|"<<std::endl;
			}
			remove_entry(P, k2);
		}
		else {
			if (deb)
				std::cout<<"No me puedo fusionar con mi hermano"<<std::endl;
			if (pos > 0) {
				if (deb)
					std::cout<<"Mi hermano me antecede"<<std::endl;
				if (N->t == nullptr) {
					if (deb)
						std::cout<<"No soy hoja"<<std::endl;
					std::size_t m = N2->used;
					dataType kr = N2->k[m-1];
					node * pr = N2->p[m];
					N2->p[m] = nullptr;
					N2->used--;
					for (std::size_t j = N->used+1; j > 1; --j) {
						N->p[j] = N->p[j-1];
						N->k[j-1] = N->k[j-2];
					}
					N->p[1] = N->p[0];
					N->p[0] = pr;
					pr->parent = N;
					N->k[0] = k2;
					N->used++;
					if (deb) {
						std::cout<<"Mi hermano me dio su ultimo puntero con el valor "<<k2<<" sacado de mi padre"<<std::endl;
						std::cout<<"Ahora yo tengo "<<N->used<<" elementos y mi hermano "<<N2->used<<std::endl;
					}
					P->k[pos-1] = kr;
					if (deb)
						std::cout<<"Ahora nos separa "<<kr<<std::endl;
				}
				else {
					if (deb)
						std::cout<<"Soy hoja"<<std::endl;
					std::size_t m  = N2->used-1;
					dataType kr = N2->k[m];
					pointerType * tr =  N2->t[m];
					N2->t[m] = nullptr;
					N2->used--;
					for (std::size_t j = N->used; j > 0; --j) {
						N->k[j] = N->k[j-1];
						N->t[j] = N->t[j-1];
					}
					N->k[0] = kr;
					N->t[0] = tr;
					N->used++;
					if (deb) {
						std::cout<<"Mi hermano me dio "<<kr<<" con su pointerType"<<std::endl;
						std::cout<<"Ahora yo tengo "<<N->used<<" elementos y el "<<N2->used<<std::endl;
					}
					P->k[pos-1] = kr;
					if (deb)
						std::cout<<"Ahora nos separa "<<kr<<std::endl;
				}
			}
			else {
				if (deb)
					std::cout<<"Mi hermano me procede"<<std::endl;
				if (N->t == nullptr) {
					std::cout<<"No soy hoja"<<std::endl;
					node * pr = N2->p[0];
					dataType kr = N2->k[0];
					for (std::size_t j = 1; j < N2->used; ++j) {
						N2->p[j-1] = N2->p[j];
						N2->k[j-1] = N2->k[j];
					}
					N2->p[N2->used-1] = N2->p[N2->used];
					N2->p[N2->used] = nullptr;
					N2->used--;
					N->k[N->used] = k2;
					N->p[N->used+1] = pr;
					pr->parent = N;
					N->used++;
					P->k[pos] = kr;
					if (deb) {
						std::cout<<"Mi hermano me dio su primer puntero con valor "<<k2<<" de mi padre"<<std::endl;
						std::cout<<"Ahora yo tengo "<<N->used<<" elementos y el "<<N2->used<<std::endl;
						std::cout<<"Ahora nos separa "<<kr<<std::endl;
					}
				}
				else {
					if (deb)
						std::cout<<"Soy hoja"<<std::endl;
					dataType kr = N2->k[0];
					pointerType * tr =  N2->t[0];
					for (std::size_t j = 1; j < N2->used; ++j) {
						N2->k[j-1] = N2->k[j];
						N2->t[j-1] = N2->t[j];
					}
					N2->t[N2->used-1] = nullptr;
					N2->used--;
					N->k[N->used] = kr;
					N->t[N->used] = tr;
					N->used++;
					P->k[pos] = kr;
					if (deb) {
						std::cout<<"Mi hermano me dio "<<kr<<" con su pointerType"<<std::endl;
						std::cout<<"Ahora yo tengo "<<N->used<<" elementos y el "<<N2->used<<std::endl;
						std::cout<<"Ahora nos separa "<<kr<<std::endl;
					}
				}
			}
		}
	}
}

template<typename dataType, typename pointerType>
BTree<dataType, pointerType>::BTree(std::size_t n) {
	if (n < 2) {
		n = 2;
	}
	this->n = n;
	this->root = new node;
	this->root->k = new dataType[n-1];
	this->root->p = nullptr;
	this->root->t = new pointerType*[n-1];
	for (std::size_t j = 0; j < n-1; ++j)
		this->root->t[j] = nullptr;
	this->root->used = 0;
	this->root->parent = nullptr;
	this->root->nl = nullptr;
}

template<typename dataType, typename pointerType>
void BTree<dataType, pointerType>::printTree() {
	node * C = this->root;
	while (C->t == nullptr) {
		node * C2 = C;
		while (C2 != nullptr) {
			std::cout<<"|";
			for (std::size_t j = 0; j < C2->used; ++j) {
				std::cout<<" "<<C2->k[j]<<" ";
			}
			std::cout<<"|";
			C2 = C2->nl;
		}
		std::cout<<std::endl;
		C = C->p[0];
	}
	while (C != nullptr) {
		std::cout<<"|";
		for (std::size_t j = 0; j < C->used; ++j) {
			std::cout<<" "<<C->k[j]<<" ";
		}
		std::cout<<"|";
		C = C->nl;
	}
	std::cout<<std::endl;
}
#endif //_BTree_cpp_
