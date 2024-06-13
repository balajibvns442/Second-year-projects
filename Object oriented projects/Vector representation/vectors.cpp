#include<iostream>
#include"vectors.hpp"
using namespace std ;

Vector::Vector(){
	this->co_ord = vector<int>(0,0);
	this->dim = 0 ;
}

Vector::Vector(vector<int> a){
	this->co_ord = a ;
	this->dim = a.size() ;
}

Vector& Vector::operator=(const Vector& a){
	if(this != &a){
		this->co_ord = a.co_ord ;
		this->dim = a.dim ;
	}
	return *this ;
}

Vector Vector::operator+(const Vector& a){
	Vector res(a.co_ord) ;
	if( this->dim == a.dim){
		for(int i=0 ; i<a.dim ; i++ ){
			res.co_ord[i] = this->co_ord[i] + a.co_ord[i] ;

		}
		res.dim = a.dim ;
		return res ;
	}
	else throw invalid_argument("The vectors are from different spaces ");
}

Vector Vector::operator-(const Vector& a){
	Vector res(a.co_ord) ;
	if( this->dim == a.dim){
		for(int i=0 ; i<a.dim ; i++ ){
			res.co_ord[i] = this->co_ord[i] - a.co_ord[i] ;
		}
		res.dim = a.dim ;
		return res ;
	}
	else throw invalid_argument("The vectors are from different spaces ");
}

int Vector::dot_product(const Vector& a){
	if( this->dim == a.dim ){
		int sum = 0 ;
		for(int i=0 ; i<a.dim ; i++){
			sum = sum + this->co_ord[i]*a.co_ord[i] ;
		}
		return sum ;
	}
	else throw invalid_argument("The vectors are from different spaces ");
}

Vector Vector::co_ord_mul(const Vector& a){
	Vector res(a.co_ord) ;
	if( this->dim == a.dim){
		for(int i=0 ; i<a.dim ; i++ ){
			res.co_ord[i] = this->co_ord[i] * a.co_ord[i] ;

		}
		res.dim = a.dim ;
		return res ;
	}
	else throw invalid_argument("The vectors are from different spaces ");
}
Vector Vector::operator*(int slr){
	Vector res(this->co_ord) ;
	for(int i=0 ; i<this->dim ; i++){
		res.co_ord[i] = this->co_ord[i] * slr ;
	}
	res.dim = this->dim ;
	return res ;
}

ostream& operator<<(ostream& out , const Vector& a){
	out<<"( " ;
	for(int i=0 ; i<a.dim ; i++ ){
		out<<a.co_ord[i]<<"," ;
	}
	out<<")" ;

	return out ;
}

Vector operator*(float a,const Vector& b) {
	Vector res(b.co_ord) ;
	for(int i=0 ; i<b.dim ; i++){
		res.co_ord[i] = b.co_ord[i] * a ;
	}
	return res ;
}



