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
	node_s<T>* curr = head;
	while (curr != nullptr)
	{
		if (curr->get == d)
		{
			return true;
		}
		curr = curr->next;
	}
	return false;
}

template<class T> bool list_s<T>::t_contains(T d)
{
	this->sem.acquire();
	bool ret = this->contains();
	this->sem.release();
	return ret;
}

template<class T> void list_s<T>::s_push(T d)
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

template<class T> void list_s<T>::q_push(T d)
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

template<class T> T list_s<T>::pop()
{
	T ret = this->head->get();
	node_s<T>* curr = this->head;
	this->head = this->head->next;
	delete curr;
	return ret;
}

template<class T> void list_s<T>::ts_push(T d)
{
	this->sem.acquire();
	this->s_push(d);
	this->sem.release();
}

template<class T> void list_s<T>::tq_push(T d)
{
	this->sem.aquire();
	this->q_push(d);
	this->sem.release();
}

template <class T> T list_s<T>::t_pop()
{
	this->sem.acquire();
	T ret = this->pop();
	this->sem.release();
	return ret;
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
		if ((p->lc == nullptr) && (p->rc == nullptr))
		{
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
			delete p;
		}
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


template<class T, typename F> node_d<T>* list_d<T, F>::contains(T d)
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




template<class T, typename F> bool list_d<T, F>::add(T d)
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
				return false;
				//FIX implement
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

template<class T, typename F> T list_d<T, F>::rem(T d)
{
	node_t<T>* curr = find_spot(d, this->head);
}

template<class T, typename F> bool list_d<T, F>::t_add(T d)
{
	this->sem.acquire();
	this->add(d);
	this->sem.release();
}



template<class T, typename F> T list_d<T, F>::t_rem(T d)
{
	this->sem.acquire();
	T ret = this->rem();
	this->sem.release();
	return ret;
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

