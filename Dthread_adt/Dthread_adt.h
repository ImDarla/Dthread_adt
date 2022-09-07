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

		node_s(T d) : data(d)
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

		node_d(T d): data(d)
		{

		}

		~node_d()
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
	protected:
		node_s<T>* head;
		node_s<T>* tail;

		list_s() :head(nullptr), tail(nullptr)
		{

		}

		~list_s();

	public:
		bool contains(T);
		

	};

	/**
	* @brief list primitive as parent class of doubly linked list ADT
	*
	*
	*
	*
	* */
	template<class T> class list_d
	{
	protected:
		node_d<T>* head;
		node_d<T>* tail;

		list_d() :head(nullptr), tail(nullptr)
		{

		}

		~list_d();

	public:
		bool contains(T);


	};

	/**
	* @brief stack data type, operators: void push(T), T pop()
	*
	*
	*
	*
	* */
	template<class T>class stack :public list_s<T>
	{

	private:
		//node<T>* head;
		//node<T>* tail;


	public:
		
		~stack();

		void push(T);

		T pop();
	};

	/**
	* @brief queue data type
	*
	*
	*
	*
	* */
	template<class T> class queue :public list_s<T>
	{
	private:
		//node<T>* head;
		//node<T>* tail;


	public:
		~queue();

		void push(T);

		T pop();
	};

	/**
	* @brief sorted list data type, constructor takes a std
	*
	*
	*
	*
	* */
	template<class T> class sorted :public list_d<T>
	{
	private:
		void insert(node_d<T>*, node_d<T>*);
		std::function<int(T, T)> func;// comparison function; returns negative if left is bigger, 0 when equal, positive when right is bigger
	public:

		sorted(std::function<int(T, T)>);
		~sorted();



		void add(T);

		int remove(T);//returns -1 on fail

		
	};

	/**
	* @brief
	*
	*
	*
	*
	* */
	template<class T> class s_stack :private stack<T>
	{
	private:
		std::binary_semaphore sem{ 1 };
	public:


		~s_stack();

		void s_push(T);

		T s_pop();

		bool contains(T);


	};

	/**
	* @brief
	*
	*
	*
	*
	* */
	template<class T> class s_queue : private queue<T>
	{
	private:
		std::binary_semaphore sem{ 1 };
	public:

		~s_queue();

		void s_push(T);

		T s_pop();

		bool contains(T);
	};

	/**
	* @brief
	*
	*
	*
	*
	* */
	template<class T> class s_sorted :public sorted<T>
	{
	private:
		std::binary_semaphore sem{ 1 };
		std::function<int(T, T)> func;// comparison function; returns negative if left is bigger, 0 when equal, positive when right is bigger
	public:
		s_sorted(std::function<int(T, T)>);

		~s_sorted();

		void s_add(T);

		int s_remove(T);

		bool contains(T);

	};

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
		

	public:
		s_var(T);

		~s_var();

		void set(T);//maybe use overloading?

		T get();

		bool cointains(T);
	};

	
}

