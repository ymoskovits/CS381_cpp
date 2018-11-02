#include <iostream>
#include <algorithm>
#include <cstdlib> 
using namespace std;

template <class T>
class SafeMatrix{
public:
	int left_index, right_index, top_index, bottom_index, length, height;
	T **mp;

	/*
		Todo:
			Rule of 5
			operator<<
	*/


	SafeMatrix(){
		left_index = 0;
		right_index = -1;
		top_index = 0;
		bottom_index = -1;
		height = 0;
		length = 0;
		mp = nullptr;
	}


	//The bounds are inclusive.
	SafeMatrix(int left_index, int right_index, int top_index, int bottom_index){
		this->left_index = left_index;
		this->right_index = right_index;
		this->top_index = top_index;
		this->bottom_index = bottom_index;

		length = right_index - left_index + 1;
		height = bottom_index - top_index + 1;

		mp = new T*[height];
		for(int i = 0; i < height; ++i){
			mp[i] = new T[length];
		}
	}

	SafeMatrix(const SafeMatrix& other){
		left_index = other.left_index;
		right_index = other.right_index;
		top_index = other.top_index;
		bottom_index = other.bottom_index;
		length = right_index - left_index + 1;
		height = bottom_index - top_index + 1;

		mp = new T*[height];
		for(int i = 0; i < height; ++i){
			mp[i] = new T[length];
		}

		for(int i = 0; i < height; ++i){
			for(int j = 0; j < length; ++j){
				mp[i][j] = other.mp[i][j];
			}
		}
	}

	// SafeMatrix(SafeMatrix&& other){
	// 	// xfirst = other.xfirst;
	// 	// xlast = other.xlast;
	// 	// yfirst = other.yfirst;
	// 	// ylast = other.ylast;
	// 	// xlen = xlast - xfirst + 1;
	// 	// ylen = ylast - yfirst + 1;

	// 	mp = other.mp;
	// 	other.mp = nullptr;
	// }



	~SafeMatrix(){
		for(int i = 0; i < height; ++i){
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

		for(int i = 0; i < height; ++i){
			delete [] mp[i];
		}
		delete [] mp;
		

		left_index = other.left_index;
		right_index = other.right_index;
		top_index = other.top_index;
		bottom_index = other.bottom_index;
		length = right_index - left_index + 1;
		height = bottom_index - top_index + 1;

		mp = new T*[height];
		for(int i = 0; i < height; ++i){
			mp[i] = new T[length];
		}

		for(int i = 0; i < height; ++i){
			for(int j = 0; j < length; ++j){
				mp[i][j] = other.mp[i][j];
			}
		}

		return *this;
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

	SafeMatrix<T> operator*(const SafeMatrix<T>& other) const{
		if(length != other.height){
			throw new exception;
		}
		int val;
		SafeMatrix<T> res(0, height, 0, other.length);
		for(int i = 0; i < res.height; ++i){
			for(int j = 0; j < res.length; ++j){
				val = 0;
				for(int k = 0; k < length; ++k){
					val += mp[i][k] * other.mp[k][j];
				}
				res[i][j] = val;

			}
		}

		return res;

	}




	class OpProxy{
		T* specific_array;
		int l_index, r_index;
	public:

		OpProxy(){
			specific_array = nullptr;
		}

		OpProxy(T* arr, int l, int r){
			l_index = l;
			r_index = r;
			specific_array = arr;
		}

		T& operator[](int index){
			if(index < l_index || index > r_index){
				throw new exception;
			}
			return specific_array[index - l_index];
		}

		~OpProxy(){

		}
	};

	OpProxy operator[](int index){
		if(index < top_index || index > bottom_index){
			throw new exception;
		}
		OpProxy prox(mp[index - top_index], left_index, right_index);
		return prox;
	}

	// friend ostream& operator<< <T>(ostream& os, const SafeMatrix<T>& sm);

};


template<class T>
ostream& operator<<(ostream& os, SafeMatrix<T>& sm){
	// cout << sm.top_index << " " << sm.bottom_index << endl;
	// cout << sm.left_index << " " << sm.right_index << endl;
	cout << endl;
	for(int i = 0; i < sm.height; ++i){
		for(int j = 0; j < sm.length; ++j){
			cout << sm.mp[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	return os;
};

int main(){
	SafeMatrix<int> m(0, 2, 0, 2);
	SafeMatrix<int> b(3, 5, 12, 14);

	int count = 100;

	for (int i = m.top_index; i <= m.bottom_index; ++i){
		for(int j = m.left_index; j <= m.right_index; ++j){
			m[i][j] = ++count;
		}
	}

	for (int i = b.top_index; i <= b.bottom_index; ++i){
		for(int j = b.left_index; j <= b.right_index; ++j){
			b[i][j] = (i - b.top_index == j - b.left_index) ? 1 : 0;
		}
	}

	cout << m << b;




	SafeMatrix<int> mult = m * b;




	cout << mult;


	return 0;
}







