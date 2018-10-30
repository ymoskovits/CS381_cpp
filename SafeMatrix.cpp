#include <iostream>
#include <algorithm>
using namespace std;

template <typename T>
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

	void swap(SafeMatrix& a, SafeMatrix& b){
		std::swap(a.xfirst, b.xfirst);
		std::swap(a.xlast, b.xlast);
		std::swap(a.yfirst, b.yfirst);
		std::swap(a.ylast, b.ylast);
		std::swap(a.xlen, b.xlen);
		std::swap(a.ylen, b.ylen);

		T** temp = a.mp;
		a.mp = b.mp;
		b.mp = temp;
	}

	//The bounds are inclusive.
	SafeMatrix(int xfirst, int xlast, int yfirst, int ylast){
		this->xfirst = xfirst;
		this->xlast = xlast;
		this->yfirst = yfirst;
		this->ylast = ylast;

		xlen = xlast - xfirst + 1;
		ylen = ylast - yfirst + 1;

		mp = new T*[xlen];
		for(int i = 0; i < xlen; ++i){
			mp[i] = new T[ylen];
		}
	}

	SafeMatrix(const SafeMatrix& other){
		xfirst = other.xfirst;
		xlast = other.xlast;
		yfirst = other.yfirst;
		ylast = other.ylast;
		xlen = xlast - xfirst + 1;
		ylen = ylast - yfirst + 1;

		mp = new T*[xlen];
		for(int i = 0; i < xlen; ++i){
			mp[i] = new T[ylen];
		}

		for(int i = 0; i < xlen; ++i){
			for(int j = 0; j < ylen; ++j){
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
		for(int i = 0; i < xlen; ++i){
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

		for(int i = 0; i < xlen; ++i){
			delete [] mp[i];
		}
		delete [] mp;
		

		xfirst = other.xfirst;
		xlast = other.xlast;
		yfirst = other.yfirst;
		ylast = other.ylast;
		xlen = xlast - xfirst + 1;
		ylen = ylast - yfirst + 1;

		mp = new T*[xlen];
		for(int i = 0; i < xlen; ++i){
			mp[i] = new T[ylen];
		}

		for(int i = 0; i < xlen; ++i){
			for(int j = 0; j < ylen; ++j){
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


};




int main(){
	SafeMatrix<int> m(0, 2, 0, 2);
	SafeMatrix<int> b(3, 9, 3, 9);

	int count = 100;

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


	for (int i = m.yfirst; i <= m.ylast; ++i){
		for(int j = m.xfirst; j <= m.xlast; ++j){
			cout << m[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = b.yfirst; i <= b.ylast; ++i){
		for(int j = b.xfirst; j <= b.xlast; ++j){
			cout << b[i][j] << " ";
		}
		cout << endl;
	}

	b = m;

	for (int i = m.yfirst; i <= m.ylast; ++i){
		for(int j = m.xfirst; j <= m.xlast; ++j){
			cout << m[i][j] << " ";
		}
		cout << endl;
	}

	for (int i = b.yfirst; i <= b.ylast; ++i){
		for(int j = b.xfirst; j <= b.xlast; ++j){
			cout << b[i][j] << " ";
		}
		cout << endl;
	}


	return 0;
}