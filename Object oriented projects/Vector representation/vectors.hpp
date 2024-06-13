#include<iostream>
#include<vector>

using namespace std ;

class Vector{
	private: 
		int dim ;
	 	vector<int> co_ord ;

	public:
		Vector(vector<int> a) ;
		Vector();
		Vector& operator=(const Vector& a) ;
		Vector operator+(const Vector& a) ; // check for space equality
		Vector operator-(const Vector& a) ; // check for space equality 
		Vector operator*(int x) ;
		int dot_product(const Vector& a) ; // check for space equality

		Vector co_ord_mul(const Vector& a);

	friend Vector operator*(float a,const Vector& b) ;
	friend ostream& operator<<(ostream& out ,const Vector& a);

};
