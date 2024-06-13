#include<iostream>
#include"vectors.hpp"
using namespace std ;

int main(){
	vector<int> b = {1,2,3,4,5,6};
	vector<int> a(6,0);

	Vector B(b) ;
	Vector A(a) ;
	Vector C,D ;

	cout<<" before '=' operator overloading "<<endl ;
	cout<<"a = " <<A<<endl ;
	cout<<"b = " <<B<<endl ;
	cout<<"c = " <<C<<endl ;

	printf("going to add the vectors  \n");
	C = A = B ;

	cout<<" '=' operator overloading "<<endl ;
	cout<<"a = " <<A<<endl ;
	cout<<"b = " <<B<<endl ;
	cout<<"c = " <<C<<endl ;	

	C = A + B ;
	cout<<" '+' operator overloading i.e addition of "<<A<<"and"<<B<<endl ;
	cout<<"c = "<<C<<endl ;

	// C = A - B ;
	cout<<" '-' operator overloading i.e addition of "<<A<<"and"<<B<<endl ;
	cout<<"c = "<<C<<endl ;

	int dot = A.dot_product(B);
	cout<<"dot product of "<<A<<" and "<<B<<" is " <<dot<<endl ;

	D = dot*C;
     cout<<"The scalar product "<<dot<<"*("<<C<<") is: "<<D<<endl;
     D = C*dot;
     cout<<"The scalar product ("<<C<<")*"<<dot<<" is :"<<D<<endl;

	D = C.co_ord_mul(A);
	cout<<D<<endl ;

	 return 0 ;	
}