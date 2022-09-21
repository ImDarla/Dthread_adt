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

		T& get();
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

		T& get();
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
			if (this->parent != nullptr)
			{
				if (this->parent->lc == this)
				{
					this->parent->lc = nullptr;
				}
				else
				{
					this->parent->rc = nullptr;
				}
			}
			
			
		}

		T& get();
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

		bool thread;
		
		
		bool i_contains(T);
		bool ti_contains(T);

		void i_print();
		void ti_print();


		void si_push(T);
		void qi_push(T);
		T i_pop();

		void tsi_push(T);
		void tqi_push(T);
		T ti_pop();

	public:
		list_s(bool t=false) :head(nullptr), tail(nullptr), thread(t)
		{

		}

		~list_s();

		bool contains(T);

		void print();

		void s_push(T);
		void q_push(T);
		T pop();
		
		class iterator : public std::iterator<std::input_iterator_tag, node_s<T>, node_s<T>, const node_s<T>*, node_s<T>>
		{
		private: node_s<T>* start;
		public:
			explicit iterator(node_s<T>* _start = 0) : start(_start)
			{

			}
			iterator& operator++()
			{
				start = start->next;
				return *this;
			}
			iterator operator++()
			{
				iterator ret = *this;
				++(*this);
				return ret;
			}
			bool operator==(iterator other) const
			{
				return this->start == other.start;
			}
			bool operator!=(iterator other) const
			{
				return !(*this == other);
			}
			reference operator*()
			{
				return start;
			}
				
		};

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
		bool thread;

		template<class T> struct bundle
		{
			node_t<T>* parent;
			bool left;
		};

		void fell_tree(node_t<T>*, bool);

		void print_tree(node_t<T>*);
		
		node_d<T>* i_contains(T);
		bundle<T> find_spot(T, node_t<T>*);
		node_t<T>* i_find_node(T, node_t<T>*);

		node_d<T>* ti_contains(T);
		node_t<T>* ti_find_node(T, node_t<T>*);

		void insert(node_d<T>*, node_d<T>*);
		

		bool insert_t(list_d<T, F>::bundle<T>&, T);

		void i_print();
		
		bool i_add(T);
		T i_rem(T);

	public:
		
		
		

		list_d(bool i = false, bool u = false, bool t=false) :head(nullptr), tail(nullptr), root(nullptr), inverse(i), unique(u), thread(t)
		{

		}

		~list_d();

		bool contains(T);

		void print();

		bool add(T);
		
		T rem(T);

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
		s_var<T> assign(const s_var<T>&);

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

