#pragma once
#include <vector>
#include <iostream>

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

	matrix outputMatrix1;
	matrix outputMatrix2;

	vector<float> stuff;
	vector<float> coeffVector;
	vector<float> reducedVector;

	float x;

	//Generate augmented matrix
	for (size_t j = 0; j < mat2.mat.size(); j++) {
		for (size_t i = 0; i < 2 * mat2.mat.size(); i++) {
			if (i < mat2.mat.size()) {
				stuff.push_back(mat2.mat[j][i]);
			}
			else if (i == j+3) {
				stuff.push_back(1);
			}
			else {
				stuff.push_back(0);
			}
		}
		outputMatrix1.generateMatrix(stuff);
		stuff.clear();
	}

	outputMatrix1.printMatrix();

	cout << "matrix has " << outputMatrix1.mat.size() << " rows and " << outputMatrix1.mat[0].size() << " columns." << endl;

	//Pivot Process
	for (size_t i = 0; i < mat2.mat[0].size(); i++) {

		cout << "matrix has " << outputMatrix1.mat.size() << " rows and " << outputMatrix1.mat[0].size() << " columns." << endl;


		
		//Generate coefficient vector for specific column
		for (size_t j = 0; j < mat2.mat.size(); j++) {
				x = outputMatrix1.mat[j][i];
				coeffVector.push_back(x);
		}

		//Row operation to zero out ith column
		for (size_t j = 0; j < outputMatrix1.mat.size(); j++) {

			//reduce pivot to identity, 1st step
			if (j == i && outputMatrix1.mat[i][i] != 1) {
				for (size_t k = 0; k < outputMatrix1.mat[0].size(); k++) {
					if (k < i) {
						stuff.push_back(0);
					}
					else {
						stuff.push_back(outputMatrix1.mat[i][k] / outputMatrix1.mat[i][i]);
					}
				}
				outputMatrix2.generateMatrix(stuff);
				stuff.clear();
			}
			else if(j == i && outputMatrix1.mat[i][i] == 1) {
				for (size_t l = 0; l < outputMatrix1.mat[0].size(); l++) {
					stuff.push_back(outputMatrix1.mat[0][l]);
				}
				outputMatrix2.generateMatrix(stuff);
				stuff.clear();
			}

			//generate reduced vector
			if (outputMatrix1.mat[i][i] != 1) {
				for (size_t k = 0; k < outputMatrix1.mat[0].size(); k++) {
					if (k < i) {
						reducedVector.push_back(0);
					}
					else {
						reducedVector.push_back(outputMatrix1.mat[i][k] / outputMatrix1.mat[i][i]);
					}
				}
			}
			else if (outputMatrix1.mat[i][i] == 1) {
				for (size_t l = 0; l < outputMatrix1.mat[0].size(); l++) {
					reducedVector.push_back(outputMatrix1.mat[0][l]);
				}
			}


			if (j != i) {
				for (size_t k = 0; k < outputMatrix1.mat[0].size(); k++) {
					x = outputMatrix1.mat[j][k] - (reducedVector[k] * coeffVector[j]);
					stuff.push_back(x);
				}
				outputMatrix2.generateMatrix(stuff);
				stuff.clear();
			}
		}

		coeffVector.clear();
		reducedVector.clear();

		outputMatrix1.clearMatrix();

		//replace outputMatrix1 with outputMatrix2
		for (size_t j = 0; j < outputMatrix2.mat.size(); j++) {
			for (size_t k = 0; k < outputMatrix2.mat[0].size(); k++) {
				stuff.push_back(outputMatrix2.mat[j][k]);
			}
			outputMatrix1.generateMatrix(stuff);
			stuff.clear();
		}

		outputMatrix2.clearMatrix();

	}

	outputMatrix1.printMatrix();

	for (size_t j = 0; j < outputMatrix1.mat.size(); j++) {
		for (size_t k = outputMatrix1.mat[0].size()/2; k < outputMatrix1.mat[0].size(); k++) {
			stuff.push_back(outputMatrix1.mat[j][k]);
		}
		outputMatrix2.generateMatrix(stuff);
		stuff.clear();
	}

	return outputMatrix2;
	
}

float matrix::determinant(matrix mat2) {

	matrix outputMatrix;
	vector<float> stuff;
	vector<float> iVector;
	float outputX = 0;
	int sgnCheck = 1;

	for (size_t i = 0; i < mat2.mat.size(); i++) {

		//check for (+) position or (-) position
		for (size_t check = 0; check <= i; check++) {
			sgnCheck = sgnCheck * -1;
		}

		//check if 3x3 matrix or larger
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

			//subdivide the determinant process via recursion until a 2x2 is found, process repeats until the recursion is finished
			iVector.push_back(sgnCheck * determinant(outputMatrix));

			outputMatrix.clearMatrix();
		}
		
	}

	//handles the summing process of the recursion
	if (mat2.mat.size() >= 3) {
		for (size_t i2 = 0; i2 < mat2.mat.size() && iVector.size() > 0; i2++) {
			outputX = outputX + mat2.mat[0][i2] * iVector[i2];
		}
		return outputX;
	}

	//handles 2x2 matrices, this is where a recursive "branch" ends
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