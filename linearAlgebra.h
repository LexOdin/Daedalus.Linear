#pragma once
#include <vector>

using namespace std;

class matrix {
	int col;
	int row;

	vector< vector<float> > mat;
	
public:

	matrix transpose(matrix mat2); // input a matrix, output its transpose
	matrix add(matrix addMat1, matrix addMat2); // input two matrices of equal dimensions and it will add them together
	matrix inverse(matrix mat2); // input a matrix, output its inverse
	float determinant(matrix mat2); // input a matrix, output its determinant
	bool isSquare(); // check if matrix is square
	void generateMatrix(vector<float> vec); // input vectors and it will form the matrix
	void clearMatrix(); //input a matrix and it will empty it
	void printMatrix(); // output the matrix

};

matrix matrix::transpose(matrix mat2) {
	// input a matrix, output its transpose
	matrix outputMatrix;
	vector<float> stuff;

	for (size_t i = 0; i < mat2.mat[0].size(); i++) {
		for (size_t j = 0; j < mat2.mat.size(); j++) {
			float x = mat2.mat[j][i];
			stuff.push_back(x);
		}
		outputMatrix.generateMatrix(stuff);
		stuff.clear();
	}

	return outputMatrix;
}

matrix matrix::add(matrix addMat1, matrix addMat2) {
	// input two matrices of equal dimensions and it will add them together

	if (addMat1.mat.size() > 0 && addMat2.mat.size() > 0 && addMat1.mat.size() == addMat2.mat.size()) {
		for (size_t i = 0; i < addMat1.mat.size(); i++) {
			for (size_t j = 0; j < addMat1.mat[i].size(); j++) {
				float x = addMat1.mat[i][j];
				float y = addMat2.mat[i][j];
				addMat1.mat[i][j] = x + y;
			}
		}

		return addMat1;

	}
}

matrix matrix::inverse(matrix mat2) {
	
	return mat2;

}

float matrix::determinant(matrix mat2) {

	matrix outputMatrix;
	vector<float> stuff;
	vector<float> iVector;
	float outputX = 0;
	int sgnCheck = 1;

	for (size_t i = 0; i < mat2.mat.size(); i++) {

		for (int check = 0; check <= i; check++) {
			sgnCheck = sgnCheck * -1;
		}

		if (mat2.mat.size() >= 3) {
			for (size_t j = 0; j < mat2.mat.size(); j++) {
				for (size_t k = 0; k < mat2.mat.size(); k++) {
					if (j != 0 && k != i) {
						float x = mat2.mat[j][k];
						stuff.push_back(x);
					}
				}
				cout << endl;
				if (stuff.size() > 0) {
					outputMatrix.generateMatrix(stuff);
					stuff.clear();
				}
			}

			if (i % 2 == 0) sgnCheck = 1;
			else sgnCheck = -1;

			cout << sgnCheck << " * " << determinant(outputMatrix);
			iVector.push_back(sgnCheck * determinant(outputMatrix));

			outputMatrix.clearMatrix();
			outputMatrix.printMatrix();
		}
		
	}

	if (mat2.mat.size() >= 3) {
		for (size_t i2 = 0; i2 < mat2.mat.size() && iVector.size() > 0; i2++) {
			outputX = outputX + mat2.mat[0][i2] * iVector[i2];
		}
		return outputX;
	}

	if (mat2.mat.size() == 2) {
		return ((mat2.mat[0][0] * mat2.mat[1][1]) - (mat2.mat[1][0] * mat2.mat[0][1]));
	}

}

void matrix::generateMatrix(vector<float> vec) {
	// feed the function vectors and it will hold them in mat
	mat.push_back(vec);
}

void matrix::clearMatrix() {
	mat.clear();
}

bool matrix::isSquare() {
	if (mat.size() == mat[0].size()){
		cout << mat[0].size() << " = " << mat.size() << endl;
		return true;
	}
	else {
		return false;
	}
}

void matrix::printMatrix() {

	for (size_t i = 0; i < mat.size(); i++) {
		for (size_t j = 0; j < mat[i].size(); j++) {
			cout << " " << mat[i][j];
		}
		cout << endl;
	}

}