#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <list>
#include <stack>
#include <mcheck.h>
#include <algorithm>
using namespace std ;


template <typename T> class Trie ;

template <typename T>
struct Node
{
	friend class Trie<T>;
	T data ;
	Node* lptr ;
	Node* rptr ;
	bool isWord ;

	Node(T , Node<T>* , Node<T>* ) ;

} ;

template <typename T>
class Trie
{

private:
	Node<T>* root ;
	bool deleteString(T* str , Node<T>* parent , Node<T>* prev , Node<T>* pres) ;
	void displayTrie(Node<T>*, T*, int i, const int maxLength) ;
	void inorderTraversal(Node<T> *ptrNode) ;
	void destroy(Node<T>*) ;
	Node<T>* search(Node<T> *pres, const T *str);

public:
	Trie();
	~Trie() ;
	static const int MAX_WORD_LENGTH = 32;
	
	bool search(const T* str);

	void destroy1(Node<T>*);
	void display() ;
	bool insert(const T* ) ;
	void PrintTree(Node<T>* tp, int spaces ) ;
	
	
	bool deleteString(T* str) ;
	void clear();
	int size() ;	
	void inorderTraversal()
	{
		this->inorderTraversal(root) ;
		
	}
	
	template<typename U>
	class iterator
	{
		private:
			 Node<U> *root_;
			 list<Node<U>* > l_;
			 stack<Node<U>* > st;
			 void init (Node<U>* temp)
			{
				while(!(temp->isWord))
				{
					l_.push_back(temp);
					if ( temp->rptr )						
					{
						st.push(temp);
					}
					temp=temp->lptr;
				}
				l_.push_back(temp);
			}
			 
		public:

		template<typename V>
		friend ostream& operator<< (ostream& os, const list<Node<V>*>& );	 
			

		iterator(Node<U> *root):root_(root)
		{
			if ( root_ != NULL )
			{
				init(root_);
			}
		}
				
		bool operator==(const iterator<U>& rhs)
		{	 
			return root_==rhs.root_;
		}

		
		list<Node<U>* > operator*() const 
		{
			return this->l_;
		}

		bool operator!=(const iterator<U>& rhs)
		{
			return !(*this==rhs);
		}
/*another way of implementing operator* which returns string(string containing whole word)*/
/*
		U* operator*() const 
		{
			int l=l_.size();
			cout << l << endl;
			U *s=new U[l+1] ;
			auto begin_=l_.begin();
			auto end_=l_.end();
			int i=0;
			while(begin_!=end_)
			{
				//cout << (*begin_)->data << "\n" ;
				s[i++]=(*begin_)->data;
				++begin_;
			}
			s[i]='\0';
		 	return s;
		}
*/

		void operator++()
		{
			Node<U>* pop;
			Node<U>* last;

			if ( !st.empty() ) 
			{
				pop = st.top();
								
				last = l_.back();

				while (last!=pop)
				{
					l_.pop_back();
					last = l_.back();
				}
				l_.pop_back();
				st.pop();
				pop=pop->rptr;
				while(!(pop->isWord))
				{
					if ( pop->rptr )						
					{
						st.push(pop);
					}
					l_.push_back(pop);
					pop=pop->lptr;
				}
				l_.push_back(pop);
			}
			else
			{
				this->root_ = NULL;
			}
		}

	};

	iterator<T> begin()
	{
		if ( root->lptr )
		{
			return iterator<T>(root->lptr);
		}
	}

	iterator<T> end()
	{
		return 0;
	}

	const iterator<T> cbegin()
	{
		if ( root->lptr )
		{
			return iterator<T>(root->lptr);
		}
	}

	const iterator<T> cend()
	{
		return 0;
	}

};


template <typename T>
Node<T> :: Node(T c , Node<T>* pn , Node<T>* nn): data(c), lptr(pn) , rptr(nn) , isWord(false)
{}

template <typename T>
Trie<T> :: Trie()
{
	root = new Node<T>(0 , 0 , 0);
}

template <typename T>
void Trie<T>::clear()
{
	destroy1(root->lptr);
}

template <typename T>
void Trie<T>::destroy1(Node<T>* ptrNode)
{
	if ( ptrNode )
	{
		destroy1(ptrNode->lptr);
		destroy1(ptrNode->rptr);
		delete(ptrNode);
	}
}

template <typename T>
bool Trie<T> :: deleteString(T* str)
{
	return deleteString(str , root , 0 , root->lptr) ;
}

template <typename T>
bool Trie<T> :: deleteString(T* str , Node<T>* parent , Node<T>* prev , Node<T>* pres)
{
	if (*str) 
	{
		while (pres && pres->data != *str) 
		{
			prev = pres;
			pres = pres->rptr;
		}
		if (pres && deleteString(str + 1, pres, 0, pres->lptr)) 
		{
			if (!pres->lptr) 
			{
				if (prev) 
				{
					prev->rptr = pres->rptr;
				} 
				else 
				{
					parent->lptr = pres->rptr;
				}
				delete pres;
			}
			return true;
		}
	} 
	else if (parent->isWord) 
	{
		parent->isWord = false;
		return true;
	}

	return false;

}

template <typename T>
bool Trie<T>::search(const T* str)
{
	bool ret = false;
	Node<T> *temp = search(root->lptr, str);

	if(temp)
		ret=true;
	
	return ret;
}


template <typename T>
Node<T>* Trie<T>::search(Node<T> *pres, const T *str)
{
	Node<T> *prev = 0;
	while (*str) {
		while (pres && pres->data != *str) {
			prev = pres;
			pres = pres->rptr;
		}
		if (!pres && *str) {
			return 0;
		} else if (*str) {
			prev = pres;
			pres = pres->lptr;
		}
		++str;
	}

	return prev;
}


template <typename T>
void Trie<T>::displayTrie(Node<T> *ptrNode, T str[], int i, const int maxLength)
{
	if (ptrNode) {
		if (ptrNode->isWord && i <= maxLength) {
			std::cout << str << "\n";
		}
		if (ptrNode->lptr) {
			str[i] = ptrNode->lptr->data;
			str[i + 1] = '\0';
		}
		displayTrie(ptrNode->lptr, str, i + 1, maxLength);
		if (ptrNode->rptr) {
			str[i - 1] = ptrNode->rptr->data;
			str[i] = '\0';
			displayTrie(ptrNode->rptr, str, i, maxLength);
		}
	}
}


template <typename T>
void Trie<T>::display() 
{
	Node<T>* ptrNode = root;
	if (ptrNode->lptr) 
	{
		ptrNode = ptrNode->lptr;
		T cstr[Trie<T>::MAX_WORD_LENGTH + 1] = { ptrNode->data };
		displayTrie(ptrNode, cstr, 1, MAX_WORD_LENGTH);
	}
}

	
template <typename T>
bool Trie<T> :: insert(const T* str)
{
	Node<T> * prevNode = 0 ;
	Node<T> * presNode = root ;
	bool ret = false ;


	while(*str)
	{
		if(presNode -> lptr)
		{
			prevNode = presNode ;
			presNode = presNode -> lptr ;
			while(presNode && presNode->data < *str)
			{
				prevNode = presNode ;
				presNode = presNode -> rptr ;

			}

			if( !( presNode && presNode->data == *str))
			{
				if(presNode && (prevNode -> lptr == presNode))
				{
					prevNode -> lptr = new Node<T>(*str , 0 , presNode) ;
					presNode = prevNode -> lptr ;
				}
				else
				{
					prevNode -> rptr = new Node<T> (*str , 0 , presNode) ;
					presNode = prevNode -> rptr ;
				}
			}
			++str ;
		}
		else
		{
			while(*str)
			{
				presNode -> lptr = new Node<T>(*str , 0 , 0) ;
				presNode = presNode -> lptr ;
				++str ;
			}
		}
	}

	if(!presNode -> isWord)
	{
		presNode -> isWord = true ;
		ret = true ;
	}
	else
	{
		ret = false ;
	}
	return ret ;
}

template <typename T>
void Trie<T>::inorderTraversal(Node<T> *ptrNode)
{
	if (ptrNode)
	{
		inorderTraversal(ptrNode->lptr);
		std::cout << ptrNode->data << " ";
		inorderTraversal(ptrNode->rptr);
	}
}


template <typename T>
void Trie<T> :: PrintTree( Node<T>* tp, int spaces )
{
  int i;
 
  if( tp != NULL )
  {
    PrintTree( tp->rptr, spaces + 3 );
    for( i = 0; i < spaces; i++ )
      cout <<' ';
    cout << tp->data << endl;
    PrintTree( tp->lptr, spaces + 3 );
  }
}

template <typename T>
Trie<T> :: ~Trie()
{
		destroy1(root) ;		
		 //clear();		
}

template <typename T>
int Trie<T> :: size()
{
	int n = 0;
	auto begin_ = this->begin() ;
	auto end_ = this->end() ;
	while(begin_ != end_)
	{
		++begin_ ;
		++n ;
	}
	return n ;
}

template <typename T>
ostream& operator << (ostream& os, const list<Node<T>* > &l1)
{
	auto begin_ = l1.begin();

	while (begin_ != l1.end())
	{
		cout << (*begin_)->data;
		++begin_;
	}
	return os;
}
#endif
