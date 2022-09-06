// threads_datatypes.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "Dthread_adt.h"


using namespace tsdt;

template<class T>node<T>::node(T d)
{
	this->data = d;
	this->next = nullptr;
	this->prev = nullptr;
	
}

template<class T>node<T>::~node()
{

}

template<class T>T node<T>::get()
{
	return this->data;
}

template<class T>list<T>::list()
{
	this->head = nullptr;
	this->tail = nullptr;
}

template<class T>list<T>::~list()
{
	node<T>* curr = this->head;
	node<T>* tmp = nullptr;
	while (curr != nullptr)
	{
		node<T>* tmp = curr;
		curr = curr->next;
		delete(tmp);
	}
	this->head = nullptr;
	this->tail = nullptr;
}

template<class T> bool list<T>::contains(T d)
{
	node<T>* curr = head;
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



template<class T>stack<T>::~stack()
{
	node<T>* curr = this->list<T>::head;
	node<T>* tmp = nullptr;
	while (curr != nullptr)
	{
		node<T>* tmp = curr;
		curr = curr->next;
		delete(tmp);
	}
	this->list<T>::head = nullptr;
	this->list<T>::tail = nullptr;
}

template<class T>void stack<T>::push(T d)
{
	if (this->list<T>::head == nullptr)
	{
		
		this->list<T>::head = new node<T>(d);
		this->list<T>::tail = this->list<T>::head;
	}
	else
	{
		node<T>*curr = new node<T>(d);
		curr->next = this->list<T>::head;
		this->list<T>::head = curr;
	}
	
}

template<class T>T stack<T>::pop()
{
	T ret = this->list<T>::head->get();
	node<T>* curr = this->list<T>::head->next;
	delete (this->list<T>::head);
	this->list<T>::head = curr;
	return ret;
}



template<class T>queue<T>::~queue()
{
	node<T>* curr = this->head;
	node<T>* tmp = nullptr;
	while (curr != nullptr)
	{
		node<T>* tmp = curr;
		curr = curr->next;
		delete(tmp);
	}
	this->head = nullptr;
	this->tail = nullptr;
}

template<class T> void queue<T>::push(T d)
{
	if (this->list<T>::head == nullptr)
	{
		this->list<T>::head = new node<T>(d);
		this->list<T>::tail = this->list<T>::head;
	}
	else
	{
		this->list<T>::tail->next = new node<T>(d);
		this->list<T>::tail = this->list<T>::tail->next;
	}


}

template<class T> T queue<T>::pop()
{
	T ret = this->list<T>::head->get();
	node<T>* curr = this->list<T>::head->next;
	delete (this->list<T>::head);
	this->list<T>::head = curr;
	return ret;
}

template<class T> void sorted<T>::insert(node<T>* a, node<T>* b)//insert b after a
{
	
	b->next = a->next;
	b->prev = a;
	a->next = b;
	b->next->prev = b;

}

template<class T> sorted<T>::sorted(std::function<int(T, T)> j)
{
	this->list<T>::head = nullptr;
	this->func = j;
}

template<class T>sorted<T>::~sorted()
{
	node<T>* curr = this->list<T>::head;
	node<T>* tmp = nullptr;
	while (curr != nullptr)
	{
		node<T>* tmp = curr;
		curr = curr->next;
		delete(tmp);
	}
	this->list<T>::head = nullptr;
	this->list<T>::tail = nullptr;
}

template<class T> void sorted<T>::add(T d)
{
	if (this->list<T>::head == nullptr)
	{
		this->list<T>::head = new node<T>(d);
	}
	else
	{
		node<T>* curr = this->list<T>::head;
		node<T>* prev = nullptr;
		while (curr != nullptr && this->func(curr->get(), d) < 0)
		{
			prev = curr;
			curr = curr->next;
		}
		if (curr == nullptr)
		{
			prev->next = new node<T>(d);

		}
		else
		{
			if (curr->prev == nullptr)
			{
				node<T>* temp = new node<T>(d);
				temp->next = this->list<T>::head;
				this->list<T>::head->prev = temp;
				this->list<T>::head = temp;
			}
			else
			{
				node<T>* temp = new node<T>(d);
				this->insert(curr->prev, temp);
			}
		}
	}
}

template<class T> int sorted<T>::remove(T d)
{
	node<T>* curr = this->list<T>::head;
	while (curr->get() != d&&curr!=nullptr)
	{
		curr = curr->next;
	}
	if (curr == nullptr)
	{
		return -1;
	}
	
	else
	{
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		delete(curr);
		return 0;
	}
}




template<class T>s_stack<T>::~s_stack()
{
	node<T>* curr = this->head;
	node<T>* tmp = nullptr;
	while (curr != nullptr)
	{
		node<T>* tmp = curr;
		curr = curr->next;
		delete(tmp);
	}
	this->head = nullptr;
	this->tail = nullptr;
}

template<class T> void s_stack<T>::s_push(T d)
{
	this->sem.acquire();
	stack<T>::push(d);
	this->sem.release();
}

template<class T> T s_stack<T>::s_pop()
{
	T ret;
	this->sem.acquire();
	ret = stack<T>::pop();
	this->sem.release();
	return ret;
}

template<class T> bool s_stack<T>::contains(T d)
{
	bool ret;
	this->sem.acquire();
	ret=list<T>::contains(d);
	this->sem.release();
	return ret;
}



template<class T>s_queue<T>::~s_queue()
{
	node<T>* curr = this->head;
	node<T>* tmp = nullptr;
	while (curr != nullptr)
	{
		node<T>* tmp = curr;
		curr = curr->next;
		delete(tmp);
	}
	this->head = nullptr;
	this->tail = nullptr;
}

template<class T> void s_queue<T>::s_push(T d)
{
	this->sem.acquire();
	queue<T>::push(d);
	this->sem.release();
}

template<class T> T s_queue<T>::s_pop()
{
	T ret;
	this->sem.acquire();
	ret =queue<T>::pop();
	this->sem.release();
	return ret;
}

template<class T> bool s_queue<T>::contains(T d)
{
	bool ret;
	this->sem.acquire();
	ret = list<T>::contains(d);
	this->sem.release();
	return ret;
}

template<class T> s_sorted<T>::s_sorted(std::function<int(T, T)> j)
{
	this->list<T>::head = nullptr;
	this->func = j;
}

template<class T>s_sorted<T>::~s_sorted()
{
	node<T>* curr = this->head;
	node<T>* tmp = nullptr;
	while (curr != nullptr)
	{
		node<T>* tmp = curr;
		curr = curr->next;
		delete(tmp);
	}
	this->head = nullptr;
	this->tail = nullptr;
}

template<class T> void s_sorted<T>::s_add(T d)
{
	this->sem.acquire();
	sorted<T>::add(d);
	this->sem.acquire();

}

template<class T> int s_sorted<T>::s_remove(T d)
{
	int e = 0;
	this->sem.acquire();
	e = sorted<T>::remove(d);
	this->sem.release();
	return e;
}

template<class T> bool s_sorted<T>::contains(T d)
{
	bool ret;
	this->sem.acquire();
	ret = list<T>::contains(d);
	this->sem.release();
	return ret;
}

template<class T > s_var<T>::s_var(T d)
{
	this->data = d;
}

template<class T> s_var<T>::~s_var()
{

}

template<class T> void s_var<T>::set(T d)
{
	this->data = d;
}

template<class T> T s_var<T>::get()
{
	return this->data;
}

