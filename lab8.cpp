#include <string>
#include <cstring>
#include <iostream>

using namespace std;

struct Matrix {
	// двумерный массив с данными.
	int** data_ = nullptr;
	// количество столбцов
	size_t n_ = 0u;
	// количество строк
	size_t m_ = 0u;

	void show() {
		for (int i = 0; i < m_; i++) {
			for (int j = 0; j < n_; j++) {
				cout << data_[i][j] << ' ';
			}
			cout << endl;
		}
	}
};



char* CopyString(const char* str) {
	char* res = new char[sizeof(str)];
	memcpy(res, str, sizeof(str));
	return res;
}

char* ConcatinateStrings(const char* a, const char* b) {
	char* res = new char[strlen(a) + strlen(b)];
	for (int i = 0; i < strlen(a); i++) {
		res[i] = a[i];
	}
	for (int i = strlen(a), j = 0; i < strlen(res); i++, j++) {
		res[i] = b[j];
	}
	return res;
}



void Construct(Matrix& out, size_t n, size_t m) {
	int** arr = new int* [m];
	for (int i = 0; i < m; i++) {
		arr[i] = new int[n];
	}
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			arr[i][j] = 0;
		}
	}
	out.n_ = n;
	out.m_ = m;
	out.data_ = arr;
}

void Destruct(Matrix& in) {
	delete(in.data_);
}

Matrix Copy(const Matrix& matrix) {
	Matrix res = { matrix.data_, matrix.n_, matrix.m_ };
	return res;
}

Matrix operator + (const Matrix& a, const Matrix& b) {
	if (a.m_ == b.m_ && a.n_ == b.n_) {
		Matrix res;
		Construct(res, a.n_, a.m_);
		for (int i = 0; i < a.m_; i++) {
			for (int j = 0; j < a.n_; j++) {
				res.data_[i][j] = a.data_[i][j] + b.data_[i][j];
			}
		}
		return res;
	}
	else
	{
		return { nullptr, 0, 0 };
	}
}

Matrix operator - (const Matrix& a, const Matrix& b) {
	if (a.m_ == b.m_ && a.n_ == b.n_) {
		Matrix res;
		Construct(res, a.n_, a.m_);
		for (int i = 0; i < a.m_; i++) {
			for (int j = 0; j < a.n_; j++) {
				res.data_[i][j] = a.data_[i][j] - b.data_[i][j];
			}
		}
		return res;
	}
	else
	{
		return { nullptr, 0, 0 };
	}
}

Matrix operator * (const Matrix& a, const Matrix& b) {
	if (a.n_ == b.m_) {
		Matrix res;
		Construct(res, b.n_, a.m_);
		for (int i = 0; i < a.m_; i++) {
			for (int j = 0; j < b.n_; j++) {
				int sum = 0;
				for (int t = 0; t < a.n_; t++) {
					sum += a.data_[i][t] * b.data_[t][j];
				}
				res.data_[i][j] = sum;
			}
		}
		return res;
	}
	else
	{
		return { nullptr, 0, 0 };
	}
}

void Transposition(Matrix& mat) {
	Matrix res;
	Construct(res, mat.m_, mat.n_);
	for (int i = 0; i < mat.m_; i++) {
		for (int j = 0; j < mat.n_; j++) {
			res.data_[j][i] = mat.data_[i][j];
		}
	}
	mat = res;
}

int main()
{
	Matrix mat;
	Construct(mat, 3, 4);
	for (int i = 0; i < mat.m_; i++) {
		for (int j = 0; j < mat.n_; j++) {
			mat.data_[i][j] = i + j;
		}
	}
	Matrix mat1;
	Construct(mat1, 6, 3);
	for (int i = 0; i < mat1.m_; i++) {
		for (int j = 0; j < mat1.n_; j++) {
			mat1.data_[i][j] = i + j * 2;
		}
	}
	mat.show();
	cout << endl;
	mat1.show();
	cout << endl;
	Matrix mat2 = mat * mat1;
	mat2.show();
	cout << endl;
	Transposition(mat2);
	mat2.show();
}