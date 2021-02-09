#pragma once

#include <string>
#include "EditMatDlg.h"
#include <random>
#include <ctime>

#include "Matrix.h"

// Диалоговое окно MatrixDlg

class MatrixDlg : public CDialog
{
	DECLARE_DYNAMIC(MatrixDlg)

public:
	MatrixDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~MatrixDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MatrixDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBAddrowtab1();
	afx_msg void OnBnClickedBAddcoltab1();
private:
	CListCtrl m_matTab;

	Matrix m_mat1;
	Matrix m_mat2;
	Matrix m_matResult;

	void FillList(); // заполнение матрицу значениями в ClistCtrl 
	bool checkSizeMat(int pageNum); //проверка размерность матрицы
	void clearMatTab(); //очистка  ClistCtrl 
	std::mt19937 gen; // рандом для значений матрицы
	int m_currentPageNum; //страница , по ней ориентируемся какая матрица обрабатывается
public:
	afx_msg void OnBnClickedEditmat1(); // окно с редактированием матрицы , в виде текста
	afx_msg void OnBnClickedBNexttab(); // переход к следующей матрице
	afx_msg void OnBnClickedBPrevtab(); // переход к предыдущей матрице
};
