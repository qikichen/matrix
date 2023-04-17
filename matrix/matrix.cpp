// Matrix class that ustilises most matrix operations
//Qi Nohr Chen 10499501 24/03/2023


#include <iostream>
#include <cstdlib> // for C-style exit
#include <ostream> // for ostream
#include <vector>
#include <cmath>

class Matrix {
  // Friends
  friend std::ostream& operator<<(std::ostream &os, const Matrix &mat);
  friend std::istream& operator>>(std::istream& is, Matrix& mat);
private: //Private Data 
  int rows{0};
  int columns{0};
  double *matrix_data{nullptr}; // Dynamic Array
public:
  // Default constructor
  Matrix() = default;

  // Parametrized Constructor 
  Matrix(int rows, int columns) : rows(rows), columns(columns), matrix_data{new double[rows * columns]} {
    for(size_t i{0}; i< (rows*columns); i++) matrix_data[i]=0;
  }

  // Copy constructor
  Matrix(const Matrix &mat) : rows(mat.rows), columns(mat.columns), matrix_data(new double[mat.rows * mat.columns])
  {
      for(int i = 0; i < rows * columns; i++){
          matrix_data[i] = mat.matrix_data[i];
      }
  }

  // Move constructor 
  Matrix(Matrix &&mat) : rows(mat.rows), columns(mat.columns), matrix_data(mat.matrix_data)
  { 
      rows = mat.rows;
      columns = mat.columns;
      matrix_data = mat.matrix_data;
      mat.rows = 0;
      mat.columns = 0;
      mat.matrix_data = nullptr;
  }

  //Deep Copy Assignment

  Matrix& operator=(Matrix &mat)
  {
    if(&mat == this) return *this; // no self assignment
    delete[] matrix_data; matrix_data=nullptr;
    // Now copy size and declare new array
    rows = mat.rows;
    columns = mat.columns;
    if(rows*columns>0)
      {
        matrix_data=new double[rows*columns];
        for(int i{};i<rows*columns;i++) matrix_data[i] = mat.matrix_data[i];
      }
    return *this; // Special pointer!!!
  }

  // Destructor
  ~Matrix() {
    delete[] matrix_data;
  }

  // Access functions
  int get_rows() const { return rows; } // Return number of rows
  int get_cols() const { return columns; } // Return number of columns

  int index(int m, int n) const { // Return position in array of element (m,n)
    if(m>0 && m<=rows && n>0 && n<=columns) {
      return (n-1)+(m-1)*columns;} 
      else {
      std::cout<<"Error: out of range"<<std::endl;
      exit(1);
    }
  }

  //MOVE ASSIGNMENT OPERATOR 
  Matrix& operator=(Matrix&& mat) noexcept 
  {
  std::cout <<"move assignment\n";
  std::swap(columns,mat.columns);
  std::swap(rows,mat.rows);
  std::swap(matrix_data,mat.matrix_data);
  return *this; // Special pointer!!!
  }

  double& operator()(int m, int n) const { return matrix_data[index(m,n)]; }

//Overloading Operators

// Overloading + operator

 Matrix operator+(const Matrix &mat) const 
 {
  if (mat.rows != rows || mat.columns != columns) {
    std::cout << "Error: rows or columns don't match for addition" << std::endl;
    exit(1);
  } else {
    Matrix new_matrix(rows, columns);
    for (int i = 1; i <= rows; i++) {
      for (int j = 1; j <= columns; j++) {
        new_matrix(i, j) = (*this)(i, j) + mat(i, j);
      }
    }
    return new_matrix;
  }
}

// Overloading - operaotr

Matrix operator-(const Matrix &mat) const 
{
  if (mat.rows != rows || mat.columns != columns) {
    std::cout << "Error: rows or columns don't match for subtraction" << std::endl;
    exit(1);
  } else {
    Matrix new_matrix(rows, columns);
    for (int i = 1; i <= rows; i++) {
      for (int j = 1; j <= columns; j++) {
        new_matrix(i, j) = (*this)(i, j) - mat(i, j);
      }
    }
    return new_matrix;
  }
}

// Overloading * operator
Matrix operator*(const Matrix &mat) const
{
    if(columns != mat.rows || rows != mat.columns){
      std::cout << "Error: rows or columns don't match for multiplication" << std::endl;
      exit(1);
    }
    else{
      Matrix multiplied_m{columns, mat.rows};
      for(int i = 1; i <= rows; i++){
        for(int j = 1; j <= columns; j++){
          double sum{0};
          for(int k = 1; k <= rows; k++){
            sum += (*this)(i,k) * mat(k,j);
          }
          multiplied_m(i,j) = sum;
        }
      }
      return multiplied_m;
    }
}

Matrix get_minor(int r_row, int r_column) const
//Minor function finding the minor of a matrix
{
  Matrix minor{rows-1, columns-1};
  std::vector<double> tmp{};
  for(int i=1; i <= rows; i++){
    for(int j=1; j <=columns; j++){
      if(i != r_row && j != r_column){
        tmp.push_back((*this)(i,j));
      }
    }
  }
  int index{0};
  for(int k=1; k <= rows-1; k++){
    for(int l=1; l <= columns-1; l++){
      minor(k,l) = tmp[index];
      index++;
    }
  }
  return minor;
}

double determinant() const
//Determinant functio that recursively calculates teh determinant
{
  if(rows != columns){
    std::cout << "Rows and Columns do not match" << std::endl;
    exit(1);
  }
  double determinant{};
  for(int j{1}; j <= columns; j++){
    Matrix minor{(*this).get_minor(1,j)};
    if(minor.rows == 1 && minor.columns == 1){
      determinant += pow(-1,1+j) * (*this)(1,j) * minor(1,1);
    }
    else{
      determinant += pow(-1,1+j) * (*this)(1,j) * (minor).determinant();
    }
  }
  
  return determinant;
}

};

std::ostream & operator<<(std::ostream &os, const Matrix &mat) 
{
  for (int i = 1; i <= mat.rows; i++) {
    for (int j = 1; j <= mat.columns; j++) {
      os << mat(i,j) << " ";
    }
    os << std::endl;
  }
  return os;
};

/*std::istream& operator>>(std::istream& is, Matrix& mat) 
{ 
  

  return is;
};*/

// Main program

int main()
{

  //
  // First part of assignment: constructing and deep copying matrices
  //

  // Demonstrate default constructor
  Matrix a1;
  std::cout<<a1;

  // Parameterized constructor
  const int m{2};
  const int n{2};
  Matrix a2{m,n};
  // Set values for a2 here
  a2(1,1) = 1;
  a2(1,2) = 2;
  a2(2,1) = 3;
  a2(2,2) = 4;
  // Print matrix a2
  std::cout<<a2;


  // Deep copy by assignment: define new matrix a3 then copy from a2 to a3
  std::cout << "Deep Copy Assignment TEST" << std::endl;
  Matrix a3{m,n};
  std::cout<<a3;
  a3=a2;
  std::cout<<a3;
  // Modify contents of original matrix and show assigned matrix is unchanged here

  std::cout << "Unchanged assigned matrix"<< std::endl;
 
  a2(1,1) = 0; //NEW VALUES
  a2(1,2) = 0;
  a2(2,1) = 0;
  a2(2,2) = 0;
  std::cout<<a2;
  std::cout<<a3;
 

  // Deep copy using copy constructor 
  std::cout << "Deep Copy Constructor TEST" << std::endl;
  Matrix a4{a2};
  std::cout<<a4;

  // Modify contents of original matrix and show copied matrix is unchanged here

  std::cout << "Unchanged assigned matrix"<< std::endl;
  a2(1,1) = 1; //NEW VALUES
  a2(1,2) = 2;
  a2(2,1) = 3;
  a2(2,2) = 4;
  std::cout<<a2;
  std::cout<<a4;

  // Move copy construction demonstration

  Matrix m1{2,2};
  m1(1,1) = 1; //NEW VALUES
  m1(1,2) = 99;
  m1(2,1) = 0;
  m1(2,2) = 1;

  
  std::cout << "Move Copy Constructor TEST" << std::endl;
  Matrix a5{std::move(m1)};
  std::cout << m1;
  std::cout << a5;

  // Move assignment demonstration
  
  Matrix m2{2,2};
  m2(1,1) = 1; //NEW VALUES
  m2(1,2) = 1;
  m2(2,1) = 0;
  m2(2,2) = 0;

  std::cout << "Move Copy Assignment TEST" << std::endl;
  Matrix a6 = std::move(m2);
  std::cout << m2;
  std::cout << a6;

  //
  // Second part of assignment: matrix operations
  //

  Matrix test1{3,3};
  Matrix test2{3,3};
  Matrix test3{2,3};

  test1(1,1) = 1;
  test1(1,2) = 2;
  test1(1,3) = 3;
  test1(2,1) = 9;
  test1(2,2) = 8;
  test1(2,3) = 7;
  test1(3,1) = 4;
  test1(3,2) = 2;
  test1(3,3) = 6;

  test2(1,1) = 5;
  test2(1,2) = 5;
  test2(1,3) = 4;
  test2(2,1) = 1;
  test2(2,2) = 2;
  test2(2,3) = 3;
  test2(3,1) = 6;
  test2(3,2) = 9;
  test2(3,3) = 7;

  test3(1,1) = 3;
  test3(1,2) = 4;
  test3(1,3) = 1;
  test3(2,1) = 2;
  test3(2,2) = 5;
  test3(2,3) = 6;

  std::cout << "Test Matrix 1" << std::endl;
  std::cout << test1;

  std::cout << "Test Matrix 2" << std::endl;
  std::cout << test2;

  std::cout << "Test Matrix 3" << std::endl;
  std::cout << test3;
  


  // Addition of 2 matrices
  std::cout << "Addition TEST" << std::endl;
  Matrix add{test1+test2};
  std::cout << add;
  // Subtraction of 2 matrices
  std::cout << "Subtraction TEST" << std::endl;
  Matrix sub{test1-test2};
  std::cout << sub;
  // Multiplication of 2 matrices
  std::cout << "Multiplication TEST" << std::endl;
  Matrix mult{test1*test2};
  std::cout << mult;
  // Minor of test matrix 1
  std::cout << "Minor TEST" << std::endl;
  Matrix min{test1.get_minor(1,1)};
  std::cout << min;
  // Determinant
  std::cout << "Determinant TEST" << std::endl;
  std::cout << test1.determinant() << std::endl;

  // IMPOSSIBLE TO MULTIPLY C AND B

  std::cout << "Multiplication FAIL TEST" << std::endl;
  Matrix failure{test2*test3};
  std::cout << failure;
  
  return 0;
}