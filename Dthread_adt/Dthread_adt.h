#pragma once
#include "pch.h"
#include "framework.h"


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
	* @brief node type for each list storing 2 pointer for doubly linked lists and a T type data variable
	* 
	* the prev pointer is only used for sorted lists
	* 
	* 
	* */
	template<class T>class node
	{
	private:
		T data;

	public:
		node<T>* next;

		node<T>* prev;

		node(T);

		~node();

		T get();
	};

	/**
	* @brief list primitive as parent class of the other data types
	* 
	* 
	* 
	* 
	* */
	template<class T> class list
	{
	protected:
		node<T>* head;
		node<T>* tail;

		list();

		~list();

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
	template<class T>class stack :public list<T>
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
	template<class T> class queue :public list<T>
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
	template<class T> class sorted :public list<T>
	{
	private:
		void insert(node<T>*, node<T>*);
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
		std::binary_semaphore sem;
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
		std::binary_semaphore sem;
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
		std::binary_semaphore sem;
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
		std::binary_semaphore sem;
		

	public:
		s_var(T);

		~s_var();

		void set(T);//maybe use overloading?

		T get();

		bool cointains(T);
	};

	
}

