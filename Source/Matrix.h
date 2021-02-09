#pragma once
#include <vector>

class Matrix
{
public:
  Matrix();
  ~Matrix();
  void FillMat(const CListCtrl& matTab);
  void getMat(CListCtrl& matTab);

  Matrix operator*(const Matrix &matRight);
  Matrix& operator=(const Matrix& matRight);

  int getRow();
  int getCol();
private:
	std::vector<int> m_mat;
	int m_row;
	int m_col;
};

