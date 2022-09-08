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


template<class T>list_d<T>::~list_d()
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




template<class T> bool list_d<T>::contains(T d)
{
	node_d<T>* curr = head;
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



template<class T> void list_d<T>::add(T d)
{

}

template<class T> void list_d<T>::u_add(T d)
{

}

template<class T> T list_d<T>::rem(T d)
{

}

template<class T> void list_d<T>::t_add(T d)
{
	this->sem.acquire();
	this->add(d);
	this->sem.release();
}

template<class T> void list_d<T>::tu_add(T d)
{
	this->sem.aquire();
	this->u_add(d);
	this->sem.release();
}

template<class T> T list_d<T>::t_rem(T d)
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

