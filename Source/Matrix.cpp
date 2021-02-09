#include "pch.h"
#include "Matrix.h"

Matrix::Matrix() {
    m_row = 0;
    m_col = 0;
}

Matrix::~Matrix() {
}

int Matrix::getRow() {
    return m_row;
}

int Matrix::getCol() {
    return m_col;
}

//заполняем матрицу данными из CListCtrl
void Matrix::FillMat(const CListCtrl& matTab) {

    //записываем размерность
    int row = matTab.GetItemCount();
    int col = matTab.GetHeaderCtrl()->GetItemCount();

    m_mat.resize(row * col); 

    m_row = row;
    m_col = col;

    //заполняем данными
    for (int rowIndex = 0; rowIndex < row; rowIndex++) {
        for (int colIndex = 0; colIndex < col; ++colIndex) {

         m_mat[m_col * rowIndex + colIndex] = (_ttoi)(matTab.GetItemText(rowIndex, colIndex));
        }
    }
}

//заполняем CListCtrl , значенииями из матрицы
void Matrix::getMat(CListCtrl &matTab) {

    for (int rowIndex = 0; rowIndex < m_row; rowIndex++) { 

        matTab.InsertItem(matTab.GetItemCount(), L"", -1);

        for (int colIndex = 0; colIndex < m_col; colIndex++) {
            CString valueStr;
            valueStr.Format(L"%d", m_mat[m_col * rowIndex + colIndex]);

            if (colIndex > matTab.GetHeaderCtrl()->GetItemCount() - 1) {

                CString posStr;
                posStr.Format(L"%d", colIndex);

                int nWidth = matTab.GetStringWidth(valueStr);
                matTab.InsertColumn(colIndex, posStr, LVCFMT_LEFT, nWidth + 30);
            }
                     
            matTab.SetItemText(rowIndex, colIndex, valueStr);
        }
    }
}

//умножение матрицы
Matrix Matrix::operator*(  const Matrix &matRight) {
    Matrix temp;
    temp.m_row = this->m_row;
    temp.m_col = matRight.m_col;
    temp.m_mat.resize(this->m_row * matRight.m_col);

    for (int i = 0; i < temp.m_row; i++) //цикл по строкам первого сомножителя 
    {
        for (int j = 0; j < temp.m_col; j++) // цикл по столбцам второго сомножителя
        {
            for (int k = 0; k < this->m_col; k++) // цикл по столбцам первого сомножителя
            {
             temp.m_mat[i * temp.m_col + j] += this->m_mat[i * this->m_col + k] * matRight.m_mat[k * matRight.m_col + j];
            }
        }
    }
    return temp;
    }

Matrix& Matrix::operator=(const Matrix& matRight) {
        //очищаем старую матрицу
         this->m_mat.clear();

        // устанавливаем новый размер
        this->m_row = matRight.m_row;
        this->m_col = matRight.m_col;
        this->m_mat.resize(m_row * m_col);

    // заполнить значениями
    for (int i = 0; i < matRight.m_row; i++)
        for (int j = 0; j < matRight.m_col; j++) 
            this->m_mat[matRight.m_col * i + j] = matRight.m_mat[matRight.m_col * i + j];

    return *this;
}

