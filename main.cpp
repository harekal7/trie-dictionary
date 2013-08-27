#include<iostream>
#include "trie.h"

using namespace std ;

template <typename ptr_t>
void print1(ptr_t begin, ptr_t end)
{
	while ( begin != end )
	{
		cout << (*begin) << endl;
		++begin;
	}
}

int main()
{
	
	char str1[] = "ability" ;
    char str2[] = "atitude" ;
	char str3[] = "apple" ;
	char str4[] = "abacus" ;
	char str5[] = "zebra" ;
	char str6[] = "search" ;

	
	Trie<char> t ;
	t.insert(str1) ;
	t.insert(str2) ;
	t.insert(str3) ;
	t.insert(str4) ;
	t.insert(str5) ;
	t.insert(str6) ;
	cout<<"Displaying entire trie\n";
	t.display();	
	cout << "\n\n\n";
	cout<<"inorderTraversal of Trie is \n\n";
	t.inorderTraversal() ;
    cout<<"\n\n";
	cout << endl;

	if ( t.deleteString(str6))
	{
		cout << str6 << "   deleted" << endl;
	}
	else
	{
		cout <<str6<< "not found \n";
	}
	
	cout<<"\n";
	if ( t.deleteString("computer"))
	{
		cout << "computer  " << "   deleted" << endl;
	}
	else
	{
		cout <<"computer  "<< "not found \n";
	}
   
	cout<<"\n";

	if ( t.search(str4))
	{
		cout << str4<< "   found" << endl;
	}
	else
	{
		cout<<str4 << "  not found \n";
	}
	if ( t.search(str6))
	{
		cout << str6<< "   found" << endl;
	}
	else
	{
		cout<<str6 << "  not found \n";
	}

	
	cout<<"\n";
	if ( t.search("rohith"))
	{
		cout << "rohith" << "   found" << endl;
	}
	else
	{
		cout <<"rohith"<< "  not found \n";
	}

    
	cout<<"\n";
    cout<<"displaying words using iterators\n"; 
	print1(t.begin(), t.end()) ;
    
	cout<<"\n";
	cout << "size of the container is.. " << t.size() << endl ;
}
