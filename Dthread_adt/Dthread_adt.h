#pragma once

#include<semaphore>

namespace tsdt
{
	/**
	* @file threadsafe_datatypes.h
	* 
	* @brief library of commonly used list based data types with corresponding thread safe variants
	* 
	* 
	**/



	/**
	* @brief node type for each list storing 1 pointer for single linked lists and a T type data variable
	* 
	* the prev pointer is only used for sorted lists
	* 
	* 
	* */
	template<class T>class node_s
	{
	private:
		T data;

	public:
		node_s<T>* next;

		node_s(T d) : data(d), next(nullptr)
		{

		}

		~node_s()
		{

		}

		T get();
	};

	/**
	* @brief node type for each list storing 2 pointer for doubly linked lists and a T type data variable
	*
	* the prev pointer is only used for sorted lists
	*
	*
	* */
	template<class T>class node_d
	{
	private:
		T data;

	public:
		node_d<T>* next;

		node_d<T>* prev;

		node_d(T d): data(d), next(nullptr), prev(nullptr)
		{

		}

		~node_d()
		{

		}

		T get();
	};

	/**
	* @brief node type for each list storing 2 pointer for doubly linked lists and a T type data variable
	*
	* the prev pointer is only used for sorted lists
	*
	*
	* */
	template<class T>class node_t
	{
	private:
		T data;

	public:
		node_t<T>* parent;

		node_t<T>* lc;
		node_t<T>* rc;
		int lw;
		int rw;

		node_t(T d, node_t<T>* p) : data(d), parent(p), lc(nullptr), rc(nullptr), lw(0), rw(0)
		{

		}

		~node_t()
		{

		}

		T get();
	};

	/**
	* @brief list primitive as parent class of single linked based ADTs
	* 
	* 
	* 
	* 
	* */
	template<class T> class list_s
	{
	private:
		std::binary_semaphore sem{ 1 };
		node_s<T>* head;
		node_s<T>* tail;
		
	public:
		list_s() :head(nullptr), tail(nullptr)
		{

		}

		~list_s();

	
		bool contains(T);
		bool t_contains(T);
		

		void s_push(T);
		void q_push(T);
		T pop();

		void ts_push(T);
		void tq_push(T);
		T t_pop();
		

	};

	/**
	* @brief list primitive as parent class of doubly linked list ADT, requires type and comparison function to be supplied, <0 if first argument is bigger, >0 if right argument is bigger
	*
	*
	*
	*
	* */
	template<class T, typename F> class list_d
	{
	private:
		node_d<T>* head;
		node_d<T>* tail;
		node_t<T>* root;
		std::binary_semaphore sem{ 1 };
		bool inverse;
		bool unique;

		list_d(bool i=false, bool u=false) :head(nullptr), tail(nullptr), root(nullptr), inverse(i), unique(u)
		{

		}

		~list_d();

		node_t<T>* find_spot(T, node_t<T>*);

		void insert(node_d<T>*, node_d<T>*);
		T splice(node_d<T>*);

		bool insert_t(node_t<T>* , T , bool);

		void rotl();
		void rotr();
		void update_weight(node_t<T>*, bool);

	public:
		
		node_d<T>* contains(T);
		//bool t_contains(T);

		

		bool add(T);
		T rem(T);

		bool t_add(T);
		
		T t_rem(T);

	};


	//REMOVE
	
	

	/**
	* @brief
	*
	*
	*
	*
	* */
	template<class T> class s_var
	{
	private:
		T data;
		std::binary_semaphore sem{ 1 };
		s_var<T> assign(const s_var<T>&) const;

	public:
		s_var(T d) :data(d)
		{

		}

		~s_var()
		{

		}

		void set(T);//maybe use overloading?

		T get();

		s_var<T> operator=(const s_var<T>& other);

		
	};

	
}

