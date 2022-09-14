// threads_datatypes.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "Dthread_adt.h"


using namespace tsdt;



template<class T>T node_s<T>::get()
{
	return this->data;
}

template<class T>T node_d<T>::get()
{
	return this->data;
}

template<class T>T  node_t<T>::get()
{
	return this->data;
}




template<class T> bool list_s<T>::i_contains(T d)
{
	node_s<T>* curr = head;
	while (curr != nullptr)
	{
		if (curr->get() == d)
		{
			return true;
		}
		curr = curr->next;
	}
	return false;
}

template<class T> bool list_s<T>::ti_contains(T d)
{
	this->sem.acquire();
	bool ret = this->contains(d);
	this->sem.release();
	return ret;
}

template<class T> void list_s<T>::i_print()
{
	node_s<T>* curr = this->head;
	while (curr != nullptr)
	{
		std::cout << curr->get() << std::endl;
		curr = curr->next;
	}
}

template<class T> void list_s<T>::ti_print()
{
	this->sem.acquire();
	this->i_print();
	this->sem.release();
}

template<class T> void list_s<T>::si_push(T d)
{
	if (this->head == nullptr)
	{
		this->head = new node_s<T>(d);
		this->tail = head;
	}
	else
	{
		node_s<T>* curr = new node_s<T>(d);
		curr->next = this->head;
		this->head = curr;
	}
}

template<class T> void list_s<T>::qi_push(T d)
{
	if (this->head == nullptr)
	{
		this->head = new node_s<T>(d);
		this->tail = head;
	}
	else
	{
		this->tail->next = new node_s<T>(d);
		this->tail = this->tail->next;
	}
	
}

template<class T> T list_s<T>::i_pop()
{
	T ret = this->head->get();
	node_s<T>* curr = this->head;
	this->head = this->head->next;
	delete curr;
	return ret;
}

template<class T> void list_s<T>::tsi_push(T d)
{
	this->sem.acquire();
	this->s_push(d);
	this->sem.release();
}

template<class T> void list_s<T>::tqi_push(T d)
{
	this->sem.acquire();
	this->q_push(d);
	this->sem.release();
}

template <class T> T list_s<T>::ti_pop()
{
	this->sem.acquire();
	T ret = this->pop();
	this->sem.release();
	return ret;
}

template<class T>list_s<T>::~list_s()
{
	node_s<T>* curr = this->head;
	node_s<T>* tmp = nullptr;
	while (curr != nullptr)
	{
		node_s<T>* tmp = curr;//retain pointer to current node so it can be deleted
		curr = curr->next;
		delete(tmp);
	}
	this->head = nullptr;
	this->tail = nullptr;
}

template<class T> bool list_s<T>::contains(T d)
{
	if (this->thread == false)
	{
		return this->i_contains(d);
	}
	else
	{
		return this->ti_contains(d);

	}
}

template<class T> void list_s<T>::print()
{
	if (this->thread == false)
	{
		this->i_print();
	}
	else
	{
		this->ti_print();
	}
}

template<class T> void list_s<T>::s_push(T d)
{
	if (this->thread == false)
	{
		this->si_push(d);
	}
	else
	{
		this->tsi_push(d);
	}
}

template<class T> void list_s<T>::q_push(T d)
{
	if (this->thread == false)
	{
		this->qi_push(d);
	}
	else
	{
		this->tqi_push(d);
	}
}

template<class T> T list_s<T>::pop()
{
	if (this->thread == false)
	{
		return this->i_pop();
	}
	else
	{
		return this->ti_pop();
	}
}

template<class T, typename F> void list_d<T, F>::fell_tree(node_t<T>* p, bool left)
{
	if (p->parent == nullptr)
	{
		if ((p->lc == nullptr) && (p->rc == nullptr))
		{
			delete p;
			this->head = nullptr;
		}
		else
		{
			if (p->lc != nullptr)
			{
				this->fell_tree(p->lc, true);
			}
			if (p->rc != nullptr)
			{
				this->fell_tree(p->rc, false);

			}
			delete p;
			this->head = nullptr;
		}
	}
	else
	{
		if (p->lc != nullptr)
		{
			this->fell_tree(p->lc, true);
		}
		if (p->rc != nullptr)
		{
			this->fell_tree(p->rc, false);

		}
		if (left)
		{
			p->parent->lc = nullptr;
			delete p;
		}
		else
		{
			p->parent->rc = nullptr;
			delete p;
		}
	}
}

template<class T, typename F> void list_d<T, F>::print_tree(node_t<T>* p)
{
	if (p->lc != nullptr) 
	{
		print_tree(p->lc);
	}
	std::cout << p->get() << std::endl;
	if (p->rc != nullptr)
	{
		print_tree(p->rc);
	}

}

template<class T,typename F>list_d<T,F>::~list_d()
{
	if (this->unique == false)
	{
		node_d<T>* curr = this->head;
		node_d<T>* tmp = nullptr;
		while (curr != nullptr)
		{
			node_d<T>* tmp = curr;//retain pointer to current node so it can be deleted
			curr = curr->next;
			delete(tmp);
		}
		this->head = nullptr;
		this->tail = nullptr;
	}
	else
	{
		fell_tree(this->head, false);
	}
	
}

template<class T, typename F> node_t<T>* list_d<T, F>::find_spot(T d, node_t<T>* p)//returns the parent for the new node
{

	//FIX add inverse
	if (F(p->get(), d)== 0)
	{
		return nullptr;
	}
	if (F(p->get(), d) < 0)
	{
		if (p->lc == nullptr)
		{
			return p;
		}
		else
		{
			return this->find_spot(d, p->lc);
		}
	}
	else
	{
		if (p->rc == nullptr)
		{
			return p;
		}
		else
		{
			return this->find_spot(d, p->rc);
		}
	}

}

template<class T, typename F> node_t<T>* list_d<T, F>::i_find_node(T d, node_t<T>* p)//returns the node holding d
{
	//FIX add inverse
	if (F(p->get(), d) == 0)
	{
		return p;
	}
	if (F(p->get(), d) < 0)
	{
		if (p->lc == nullptr)
		{
			return nullptr;
		}
		else
		{
			return this->find_spot(d, p->lc);
		}
	}
	else
	{
		if (p->rc == nullptr)
		{
			return nullptr;
		}
		else
		{
			return this->find_spot(d, p->rc);
		}
	}

}


template<class T, typename F> node_d<T>* list_d<T, F>::i_contains(T d)
{
	
	node_d<T>* curr = head;
	while (curr != nullptr)
	{
		if (curr->get() == d)
		{
			return curr;
		}
		curr = curr->next;
	}
	return curr;
	
	
}

template<class T, typename F> node_t<T>* list_d<T, F>::ti_find_node(T d, node_t<T>* p)
{
	bool ret;
	this->sem.acquire();
	ret=this->i_find_node(d, p);
	this->sem.release();
	return ret;
}

template<class T, typename F> node_d<T>* list_d<T, F>::ti_contains(T d)
{
	bool ret;
	this->sem.acquire();
	ret = this->i_contains(d);
	this->sem.release();
	return ret;
}

template<class T, typename F> void list_d<T, F>::insert(node_d<T>* a, node_d<T>* b)
{
	b->next = a->next;
	b->prev = a;
	a->next = b;
	if (a!=this->tail)
	{
		b->next->prev = b;
	}
	else
	{
		tail = b;
	}

}

template<class T, typename F> bool list_d<T, F>::insert_t(node_t<T>* p, T d, bool left)//FIX different addition?
{
	if (p == nullptr)
	{
		return false;
	}
	else
	{
		if (left)
		{
			p->lc=new node_t<T>(d);
		}
		else
		{
			p->rc=new node_t<T>(d);
		}
	}
	
}




template<class T, typename F> bool list_d<T, F>::i_add(T d)
{
	if (this->unique == false)
	{
		if (this->head == nullptr)
		{
			this->head = new node_d<T>(d);
			this->tail = head;
			return true;
		}
		else
		{
			node_d<T>* p = contains(d);
			if (p != nullptr)
			{
				node_d<T>* curr = new node_d<T>(d);
				insert(p, curr);
				return true;
			}
			else
			{
				p = this->head;
				while (p != nullptr)
				{
					if (F(p->next->get(), d) < 0)
					{
						break;
					}
					p = p->next;
				}
				node_d<T>* curr = new node_d<T>(d);
				insert(p, curr);
				return true;
			}
		}
	}
	else
	{
		if (this->root == nullptr)
		{
			this->root = new node_t<T>(d);
			return true;
		}
		else
		{
			node_t<T>* p = find_spot(d, this->root);
			return insert_t(this->root,d);
		}
		

	}
}

template<class T, typename F> T list_d<T, F>::i_rem(T d)
{
	if (this->unique == false)
	{
		node_d<T>* curr = nullptr;
		if (this->head->get() == d)
		{
			curr = head;
			T ret = curr->get();
			head = head->next;
			delete curr;
			return ret;
		}
		if (this->tail->get() == d)
		{
			curr = tail;
			T ret = curr->get();
			tail = tail->prev;
			delete curr;
			return ret;
		}
		node_d<T>* curr = contains(d);
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		T ret = curr->get();
		delete curr;
		return ret;
	}
	else
	{
		node_t<T>* curr = find_node(d, this->root);
		if (curr != nullptr)
		{
			T ret = curr->get();
			if ((curr->lc == nullptr) && (curr->rc == nullptr))
			{
				
				delete curr;
				return ret;
			}
			else
			{
				if (curr->lc == nullptr)
				{
					node_t<T>* o = curr->rc;
					delete curr;
					node_t<T>* n = find_spot(o->get(), this->root);
					if (F(n->get(), o->get()) < 0)
					{
						n->lc = o;
						o->parent = n;
					}
					else
					{
						n->rc = o;
						o->parent = n;
					}
					return ret;
					
				}
				if (curr->rc == nullptr)
				{
					node_t<T>* o = curr->lc;
					delete curr;
					node_t<T>* n = find_spot(o->get(), this->root);
					if (F(n->get(), o->get()) < 0)
					{
						n->lc = o;
						o->parent = n;
					}
					else
					{
						n->rc = o;
						o->parent = n;
					}
					return ret;
				}

				node_t<T>* o = curr->lc;
				node_t<T>* tmp = find_spot(o->get(), curr->rc);
				if (F(tmp->get(), o->get()) < 0)
				{
					tmp->lc = o;
					o->parent = tmp;
				}
				else
				{
					tmp->rc = o;
					o->parent = tmp;
				}
				node_t<T>* n = curr->rc;
				delete curr;
				node_t<T>* n = find_spot(o->get(), this->root);
				if (F(n->get(), o->get()) < 0)
				{
					n->lc = o;
					o->parent = n;
				}
				else
				{
					n->rc = o;
					o->parent = n;
				}
				return ret;

			}
		}
		
	}
	
}

template<class T, typename F> void list_d<T, F>::i_print()
{
	if (this->unique == false)
	{
		node_d<T>* curr = head;
		while (curr != nullptr)
		{
			std::cout << curr->get() << std::endl;
			curr = curr->next;
		}
	}
	else
	{
		this->print_tree(this->root);
	}
}

template<class T, typename F> bool list_d<T, F>::contains(T d)
{
	if (this->unique == false)
	{
		if (this->thread == false)
		{
			return this->contains(d);
		}
		else
		{
			return this->ti_contains(d);
		}
	}
	else
	{
		if (this->thread == false)
		{
			return this->i_find_node(d, this->root);
		}
		else
		{
			return this->ti_find_node(d, this->root);
		}
	}
}

template<class T, typename F> void list_d<T, F>::print()
{
	if (this->thread)
	{
		this->sem.acquire();
		this->i_print();
		this->sem.release();
	}
	else
	{
		this->i_print();
	}
}

template<class T, typename F> bool list_d<T, F>::add(T d)
{
	if (this->thread)
	{
		bool ret;
		this->sem.aquire();
		ret = this->i_add(d);
		this->sem.release();
		return ret;
	}
	else
	{
		return this->i_add(d);
	}
}



template<class T, typename F> T list_d<T, F>::rem(T d)
{
	if (this->thread)
	{
		T ret;
		this->sem.acquire();
		ret = this->i_rem();
		this->sem.release();
		return ret;
	}
	else
	{
		return this->i_rem();
	}
}
//REMOVE








template<class T> s_var<T> s_var<T>::assign(const s_var<T>& other) const
{
	return s_var<T>(other.get());
}

template<class T> void s_var<T>::set(T d)
{
	this->sem.acquire;
	this->data = d;
	this->sem.release;
}

template<class T> T s_var<T>::get()
{
	this->sem.acquire();
	T ret= this->data;
	this->sem.release();
	return ret;
}

template<class T> s_var<T> s_var<T>::operator=(const s_var<T>& other)
{
	return this->assign(other);
}

