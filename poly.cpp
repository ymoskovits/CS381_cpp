#include <iostream>
#include <sstream>
#include <fstream>
//3x^2 6x 9 x^5
//2x 4x^5 -3
using namespace std;


void add(double a[], double b[], double res[]){
	for(int i = 0; i < 100; ++i){
		res[i] = 0;
	}
	for(int i = 0; i < 100; ++i){
		res[i] = a[i] + b[i];
	}
}

void subtract(double a[], double b[], double res[]){
	for(int i = 0; i < 100; ++i){
		res[i] = 0;
	}
	for(int i = 0; i < 100; ++i){
		res[i] = a[i] - b[i];
	}
}

void multiply(double a[], double b[], double res[]){
	for(int i = 0; i < 100; ++i){
		res[i] = 0;
	}
	for(int i = 0; i < 100; ++i){
		for(int j = 0; j < 100; ++j){
			res[i + j] += a[i] * b[j];
		}
	}
}

void print(double p[]){
	cout << endl;
	bool first_term = true;
	for(int i = 99; i >= 0; --i){
		if(p[i] != 0){
			if(p[i] > 0 && !first_term){
				cout << "+";
			}
			if(p[i] != 1){
				cout << p[i];
			}
			if(i != 0){
				cout << "x";
				if(i != 1){
					cout << "^" << i;
				}
			}
			first_term = false;
		}
	}
	cout << endl;
}



int main(){
	double coef;
	int exp;
	string line;
	ifstream in("input.txt");
	ofstream out("output.txt");

	double polya[100] = {0}; // we will store the coeficients[4] = 12 for 12x^4
	double polyb[100] = {0};
	double ans[100] = {0};


	//Get every pair of lines/polynomials;
	while(getline(in, line)){
		stringstream stream(line);
		cout << line << endl;

		//Zero out for next set
		for(int i = 0; i < 100; ++i){
			polya[i] = 0;
			polyb[i] = 0;
		}

		while(stream >> coef){
			stream >> exp;
			polya[exp] = coef;
		}

		getline(in, line);
		stringstream streamb(line);
		cout << line << endl;

		while(streamb >> coef){
			streamb >> exp;
			polyb[exp] = coef;
		}

		print(polya); print(polyb);
		add(polya, polyb, ans);
		cout << "\nAdded: ";	print(ans);

		subtract(polya, polyb, ans);
		cout << "\nSubtracted: ";	print(ans);

		multiply(polya, polyb, ans);
		cout << "\nmultiplied: ";	print(ans); cout << endl;
		
	}

	return 0;
}
