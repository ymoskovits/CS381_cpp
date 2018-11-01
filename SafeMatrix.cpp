#include <iostream>
#include <algorithm>
#include <cstdlib> 
using namespace std;

template <class T>
class SafeMatrix{
public:
	int xfirst, xlast, yfirst, ylast, xlen, ylen;
	T **mp;

	/*
		Todo:
			Rule of 5
			operator<<
	*/


	SafeMatrix(){
		xfirst = 0;
		xlast = -1;
		yfirst = 0;
		ylast = -1;
		xlen = 0;
		ylen = 0;
		mp = nullptr;
	}


	SafeMatrix<T> operator*(const SafeMatrix<T>& other) const{
		if(xlen != other.ylen){
			throw new exception;
		}
		int val;
		SafeMatrix<T> res(0, ylen, 0, other.xlen);
		for(int i = 0; i <= res.ylen; ++i){
			for(int j = 0; j <= res.xlen; ++j){
				val = 0;
				for(int k = 0; k <= xlen; ++k){
					val += mp[i][k] * other.mp[k][j];
				}
				res[i][j] = val;

			}
		}

		return res;

	}

	// void swap(SafeMatrix& a, SafeMatrix& b){
	// 	std::swap(a.xfirst, b.xfirst);
	// 	std::swap(a.xlast, b.xlast);
	// 	std::swap(a.yfirst, b.yfirst);
	// 	std::swap(a.ylast, b.ylast);
	// 	std::swap(a.xlen, b.xlen);
	// 	std::swap(a.ylen, b.ylen);

	// 	T** temp = a.mp;
	// 	a.mp = b.mp;
	// 	b.mp = temp;
	// }

	//The bounds are inclusive.
	SafeMatrix(int xfirst, int xlast, int yfirst, int ylast){
		this->xfirst = xfirst;
		this->xlast = xlast;
		this->yfirst = yfirst;
		this->ylast = ylast;

		xlen = xlast - xfirst + 1;
		ylen = ylast - yfirst + 1;

		mp = new T*[ylen];
		for(int i = 0; i < ylen; ++i){
			mp[i] = new T[xlen];
		}
	}

	SafeMatrix(const SafeMatrix& other){
		xfirst = other.xfirst;
		xlast = other.xlast;
		yfirst = other.yfirst;
		ylast = other.ylast;
		xlen = xlast - xfirst + 1;
		ylen = ylast - yfirst + 1;

		mp = new T*[ylen];
		for(int i = 0; i < ylen; ++i){
			mp[i] = new T[xlen];
		}

		for(int i = 0; i < ylen; ++i){
			for(int j = 0; j < xlen; ++j){
				mp[i][j] = other.mp[i][j];
			}
		}
	}

	SafeMatrix(SafeMatrix&& other){
		// xfirst = other.xfirst;
		// xlast = other.xlast;
		// yfirst = other.yfirst;
		// ylast = other.ylast;
		// xlen = xlast - xfirst + 1;
		// ylen = ylast - yfirst + 1;

		mp = other.mp;
		other.mp = nullptr;
	}



	~SafeMatrix(){
		for(int i = 0; i < ylen; ++i){
			delete [] mp[i];
		}
		delete [] mp;
	}


	SafeMatrix& operator=(const SafeMatrix &other){

		// swap(mp, other);
		// return *this;


		if(this == &other){
			return *this;
		}

		for(int i = 0; i < ylen; ++i){
			delete [] mp[i];
		}
		delete [] mp;
		

		xfirst = other.xfirst;
		xlast = other.xlast;
		yfirst = other.yfirst;
		ylast = other.ylast;
		xlen = xlast - xfirst + 1;
		ylen = ylast - yfirst + 1;

		mp = new T*[ylen];
		for(int i = 0; i < ylen; ++i){
			mp[i] = new T[xlen];
		}

		for(int i = 0; i < ylen; ++i){
			for(int j = 0; j < xlen; ++j){
				mp[i][j] = other.mp[i][j];
			}
		}

		return *this;
	}




	class OpProxy{
		T* specific_array;
	public:

		OpProxy(){
			specific_array = nullptr;
		}

		OpProxy(T* arr){
			specific_array = arr;
		}

		T& operator[](int index){
			return specific_array[index];
		}

		~OpProxy(){

		}
	};

	OpProxy operator[](int index){
		if(index < xfirst || index > xlast){
			throw new exception;
		}
		OpProxy prox(mp[index - xfirst] - yfirst);
		return prox;
	}

	// friend ostream& operator<< <T>(ostream& os, const SafeMatrix<T>& sm);

};

template<class T>
ostream& operator<<(ostream& os, SafeMatrix<T>& sm){
	cout << sm.yfirst << " " << sm.ylast << endl;
	cout << sm.xfirst << " " << sm.xlast << endl;
	for(int i = sm.yfirst; i <= sm.ylast; ++i){
		for(int j = sm.xfirst; j <= sm.xlast; ++j){
			cout << sm.mp[i][j] << " ";
		}
		cout << endl;
	}
	return os;
};

int main(){
	SafeMatrix<int> m(0, 2, 0, 2);
	// SafeMatrix<int> b(3, 9, 3, 9);

	// int count = 100;

	for (int i = m.yfirst; i <= m.ylast; ++i){
		for(int j = m.xfirst; j <= m.xlast; ++j){
			m[i][j] = ++count;
		}
	}

	for (int i = b.yfirst; i <= b.ylast; ++i){
		for(int j = b.xfirst; j <= b.xlast; ++j){
			b[i][j] = i * j;
		}
	}
	cout << b << endl << m;

	// b = m;

	// cout << b ;//<< endl << m;


	return 0;
}







