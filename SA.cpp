#include <iostream>
#include <cstdlib>
#include <vector>
#include <cassert>
#include <initializer_list>
#include <memory>


using namespace std;

class SA{
private:
 int low, high;
 //int* p;
unique_ptr<int[]> p;
public:

 // default constructor
 // allows for writing things like SA a;

 SA(){
 	low=0;
 	high=-1;
 	p=NULL;
 }


 // 2 parameter constructor lets us write
 // SA x(10,20);

 SA(int l, int h, const initializer_list<int>& il) : SA(l, h){
	//also check that it doesnt have too many or too few elements in il;
	initializer_list<int>::iterator lit = il.begin();
	for(int i = 0; i <= high - low; ++i, ++lit){
		p[i] = *lit;
	}
}

 SA(int l, int h) : p(new int[h - l + 1]){
	if((h-l+1)<=0){
	 	 cout<< "constructor error in bounds definition"<<endl;
		 exit(1);
	}
	low=l;
	high=h;
	// p=new int[h-l+1]; 
}

SA(const initializer_list<int>& il) : SA(0, il.size() - 1){
	initializer_list<int>::iterator lit = il.begin();
	for(int i = 0; i < il.size(); ++i, ++lit){
		p[i] = *lit;
	}
}

 // single parameter constructor lets us
 // create a SA almost like a "standard" one by writing
 // SA x(10); and getting an array x indexed from 0 to 9

 SA(int i) : p(new int[i]){
 	low=0;
 	high=i-1;
 	// p=new int[i];
 }
 // copy constructor for pass by value and
 // initialization

 SA(const SA & s) : p(new int[s.high - s.low + 1]){
	 int size=s.high-s.low+1;
	 // p=new int[size];
	 for(int i=0; i<size; i++){
	 	p[i]=s.p[i];
	 }
	 low=s.low;
	 high=s.high;
 }
 // destructor

 ~SA(){
 	// delete [] p;
 }
 //overloaded [] lets us write
 //SA x(10,20); x[15]= 100;

 int& operator[](int i){
	if(i<low || i>high){
 		cout<< "index "<<i<<" out of range"<<endl;
 		exit(1);
 	}
	return p[i-low];
 }
 

 // overloaded assignment lets us assign
 // one SA to another

 SA & operator=(const SA & s){
 	if(this==&s){
 		return *this;
 	}

 	
 	
	// delete [] p;
	this->low = s.low;
	this->high = s.high;
	int size=s.high-s.low+1;
 	// p=new int[size];
 	for(int i=0; i<size; i++){
 		p[i]=s.p[i];
 	}
	low=s.low;
	high=s.high;
	return *this;
 }

 // overloads << so we can directly print SAs

 friend ostream& operator<<(ostream& os, SA s);
};

ostream& operator<<(ostream& os, SA s){
	int size=s.high-s.low+1;
	for(int i=0; i<size; i++){
		cout<<s.p[i]<<endl;
	}
	return os;
}

int main(){

	SA z(3,6,{10, 20, 99, 5}); // should make an array of 2 vals (10 and 20)
	// cout << z;
	// SA x{1,2};
	// cout << x;
	// SA y(1,3,{1,34,0});
	// cout << y;
	// SA s3={1,2,3,4,5,6,7,8,9};
	// cout << s3;
	// SA a(z);
	// cout << a;

	SA s1(10);
    SA s2(1,6);
    
    for(int i=0;i<10;i++){
        s1[i]=10-i;
        cout<<s1[i]<<" ";
    }
    cout<<endl;
    
    for(int i=1;i<=6;i++){
        s2[i]=i;
        cout<<s2[i]<<" ";
    }
    cout<<endl;
    
    SA s3={1,2,3,4,5,6,7,8,9};
    for(int i=0;i<9;i++){
        cout<<s3[i]<<" ";
    }
    cout<<endl;
    

	
	return 0;
} 