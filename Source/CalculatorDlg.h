#pragma once


// Диалоговое окно CalculatorDlg
#include "Calculator.h"

class CalculatorDlg : public CDialog
{
	DECLARE_DYNAMIC(CalculatorDlg)

public:
	CalculatorDlg(CWnd* pParent = nullptr);   // стандартный конструктор
	virtual ~CalculatorDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CalculatorDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButtonSplit();
	afx_msg void OnBnClickedBResult();
	
private:
	Calculator m_calc;
	void changeSign();
	void addLine(CString valueStr);
	void changeColorButtons();
	double convertLineToDouble();
public:
	CMFCButton m_multButton;
	CMFCButton m_splitButton;
	CMFCButton m_minusButton;
	CMFCButton m_plusButton;
	CMFCButton m_resultButton;
	afx_msg void OnBnClickedBClear();
	afx_msg void OnBnClickedBSifUsig();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtonMult();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedBMinus();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedBPlus();
	afx_msg void OnBnClickedBButton0();
	afx_msg void OnBnClickedBDecimal();
	CEdit m_lineValue;
};
