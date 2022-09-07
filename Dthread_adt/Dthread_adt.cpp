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
	node_s<T>* curr = this->list_s<T>::head;
	node_s<T>* tmp = nullptr;
	while (curr != nullptr)
	{
		node_s<T>* tmp = curr; //retain pointer to current node so it can be deleted
		curr = curr->next;
		delete(tmp);
	}
	this->list_s<T>::head = nullptr;
	this->list_s<T>::tail = nullptr;
}

template<class T>void stack<T>::push(T d)//stack works by LIFO principle ->new elements are added at the head
{
	if (this->list_s<T>::head == nullptr)//case if list is empty
	{
		
		this->list_s<T>::head = new node_s<T>(d);
		this->list_s<T>::tail = this->list_s<T>::head;//set tail to head
	}
	else//case if list has elements in it
	{
		node_s<T>*curr = new node_s<T>(d);
		curr->next = this->list_s<T>::head;
		this->list_s<T>::head = curr;//tails does not get reset for the stack
	}
	
}

template<class T>T stack<T>::pop()//stacks works by LIFO principle ->pop always removes the head item
{
	T ret = this->list_s<T>::head->get();//retain value of current head
	node_s<T>* curr = this->list_s<T>::head->next;//retain current head
	delete (this->list_s<T>::head);
	this->list_s<T>::head = curr;
	return ret;
}



template<class T>queue<T>::~queue()
{
	node_s<T>* curr = this->head;
	node_s<T>* tmp = nullptr;
	while (curr != nullptr)
	{
		node_s<T>* tmp = curr;
		curr = curr->next;
		delete(tmp);
	}
	this->head = nullptr;
	this->tail = nullptr;
}

template<class T> void queue<T>::push(T d)
{
	if (this->list_s<T>::head == nullptr)
	{
		this->list_s<T>::head = new node_s<T>(d);
		this->list_s<T>::tail = this->list_s<T>::head;
	}
	else
	{
		this->list_s<T>::tail->next = new node_s<T>(d);
		this->list_s<T>::tail = this->list_s<T>::tail->next;
	}


}

template<class T> T queue<T>::pop()
{
	T ret = this->list_s<T>::head->get();
	node_s<T>* curr = this->list_s<T>::head->next;
	delete (this->list_s<T>::head);
	this->list_s<T>::head = curr;
	return ret;
}

template<class T> void sorted<T>::insert(node_d<T>* a, node_d<T>* b)//insert b after a
{
	
	b->next = a->next;
	b->prev = a;
	a->next = b;
	b->next->prev = b;

}

template<class T> sorted<T>::sorted(std::function<int(T, T)> j)
{
	this->list_d<T>::head = nullptr;
	this->func = j;
}

template<class T>sorted<T>::~sorted()
{
	node_d<T>* curr = this->list_d<T>::head;
	node_d<T>* tmp = nullptr;
	while (curr != nullptr)
	{
		node_d<T>* tmp = curr;
		curr = curr->next;
		delete(tmp);
	}
	this->list_d<T>::head = nullptr;
	this->list_d<T>::tail = nullptr;
}

template<class T> void sorted<T>::add(T d)
{
	if (this->list_d<T>::head == nullptr)
	{
		this->list_d<T>::head = new node_d<T>(d);
	}
	else
	{
		node_d<T>* curr = this->list_d<T>::head;
		node_d<T>* prev = nullptr;
		while (curr != nullptr && this->func(curr->get(), d) < 0)
		{
			prev = curr;
			curr = curr->next;
		}
		if (curr == nullptr)
		{
			prev->next = new node_d<T>(d);

		}
		else
		{
			if (curr->prev == nullptr)
			{
				node_d<T>* temp = new node_d<T>(d);
				temp->next = this->list_d<T>::head;
				this->list_d<T>::head->prev = temp;
				this->list_d<T>::head = temp;
			}
			else
			{
				node_d<T>* temp = new node_d<T>(d);
				this->insert(curr->prev, temp);
			}
		}
	}
}

template<class T> int sorted<T>::remove(T d)
{
	node_d<T>* curr = this->list_d<T>::head;
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
	node_s<T>* curr = this->head;
	node_s<T>* tmp = nullptr;
	while (curr != nullptr)
	{
		node_s<T>* tmp = curr;
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
	ret=list_s<T>::contains(d);
	this->sem.release();
	return ret;
}



template<class T>s_queue<T>::~s_queue()
{
	node_s<T>* curr = this->head;
	node_s<T>* tmp = nullptr;
	while (curr != nullptr)
	{
		node_s<T>* tmp = curr;
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
	ret = list_s<T>::contains(d);
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
	node_d<T>* curr = this->head;
	node_d<T>* tmp = nullptr;
	while (curr != nullptr)
	{
		node_d<T>* tmp = curr;
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
	ret = list_d<T>::contains(d);
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

