// CalculatorDlg.cpp: файл реализации
//

#include "pch.h"
#include "CalcAndMat.h"
#include "CalculatorDlg.h"
#include "afxdialogex.h"


// Диалоговое окно CalculatorDlg

IMPLEMENT_DYNAMIC(CalculatorDlg, CDialog)

CalculatorDlg::CalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CalculatorDlg, pParent)
{

}

CalculatorDlg::~CalculatorDlg()
{
}

void CalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//GetDlgItem(IDC_BUTTON3)->SetBkColor(RGB(0, 255, 0));
	//m_Button.SetFaceColor(RGB(255, 0, 0), true);
	//m_Button.SetTextColor(RGB(0, 0, 255));
	DDX_Control(pDX, IDC_BUTTON_MULT, m_multButton);
	DDX_Control(pDX, IDC_BUTTON_SPLIT, m_splitButton);
	DDX_Control(pDX, IDC_B_MINUS, m_minusButton);
	DDX_Control(pDX, IDC_B_PLUS, m_plusButton);
	DDX_Control(pDX, IDC_B_RESULT, m_resultButton);

	changeColorButtons();
	DDX_Control(pDX, IDC_LINE_VALUE, m_lineValue);
}


BEGIN_MESSAGE_MAP(CalculatorDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON3, &CalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_SPLIT, &CalculatorDlg::OnBnClickedButtonSplit)
	ON_BN_CLICKED(IDC_B_RESULT, &CalculatorDlg::OnBnClickedBResult)
	ON_BN_CLICKED(IDC_B_CLEAR, &CalculatorDlg::OnBnClickedBClear)
	ON_BN_CLICKED(IDC_B_SIF_USIG, &CalculatorDlg::OnBnClickedBSifUsig)
	ON_BN_CLICKED(IDC_BUTTON1, &CalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_MULT, &CalculatorDlg::OnBnClickedButtonMult)
	ON_BN_CLICKED(IDC_BUTTON4, &CalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_B_MINUS, &CalculatorDlg::OnBnClickedBMinus)
	ON_BN_CLICKED(IDC_BUTTON7, &CalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_B_PLUS, &CalculatorDlg::OnBnClickedBPlus)
	ON_BN_CLICKED(IDC_B_BUTTON0, &CalculatorDlg::OnBnClickedBButton0)
	ON_BN_CLICKED(IDC_B_DECIMAL, &CalculatorDlg::OnBnClickedBDecimal)
END_MESSAGE_MAP()


void CalculatorDlg::changeColorButtons() {

	// кнопка умножения
	m_multButton.EnableWindowsTheming(FALSE);
	m_multButton.SetFaceColor(RGB(0, 0, 255));
	m_multButton.SetTextColor(RGB(255, 255, 255));

	// кнопка деления
	m_splitButton.EnableWindowsTheming(FALSE);
	m_splitButton.SetFaceColor(RGB(100, 0, 0));
	m_splitButton.SetTextColor(RGB(255, 255, 255));


	// кнопка минус
	m_minusButton.EnableWindowsTheming(FALSE);
	m_minusButton.SetFaceColor(RGB(100, 220, 0));
	m_minusButton.SetTextColor(RGB(150, 255, 150));

	// кнопка плюс
	m_plusButton.EnableWindowsTheming(FALSE);
	m_plusButton.SetFaceColor(RGB(0, 200, 0));
	m_plusButton.SetTextColor(RGB(255, 255, 255));

	// кнопка равно
	m_resultButton.EnableWindowsTheming(FALSE);
	m_resultButton.SetFaceColor(RGB(255, 255, 255));
	m_resultButton.SetTextColor(RGB(0, 0, 0));

}

//функция смены знака 
//здесь получаем из строки число и умножаем на -1
void CalculatorDlg::changeSign() {
	
	int len = m_lineValue.LineLength(m_lineValue.LineIndex(0));

	CString line;
	m_lineValue.GetLine(0, line.GetBuffer(len), len);
	line.ReleaseBuffer(len);

	//если строка пустая,ничего делать не надо
	if (line == L"") {
		return void();
	}

	double value = wcstod(line,NULL);
	value *= (-1);

	line.Format(L"%g", value);
	m_lineValue.SetWindowText(_T(""));
	m_lineValue.ReplaceSel(line, TRUE);

}




void CalculatorDlg::addLine(CString valueStr) {

	int len = m_lineValue.LineLength(m_lineValue.LineIndex(0));

	if (len > 12) {
		MessageBox(L"Достигнут лимит.");
		return void();
	}
	  
	//проверка на порядок следования нулей
	if (len == 1 && valueStr != L".") {
		CString line;
		m_lineValue.GetLine(0, line.GetBuffer(len), len);
		line.ReleaseBuffer(len);

		if (line == L"0") {
		 m_lineValue.SetWindowText(_T(""));
		}
	}
	//контролирование десятичных значений
	if (valueStr == L".") {
		CString line;
		m_lineValue.GetLine(0, line.GetBuffer(len), len);
		line.ReleaseBuffer(len);

		//ищем в строке "."
		int pos = line.Find('.', 0); 

		// если нашли , то новую не добавляем
		if (pos != (-1)) {
			return void();
		}
	}

	m_lineValue.ReplaceSel(valueStr, TRUE); // добавляем значение в строку
}

double CalculatorDlg::convertLineToDouble() { //конвертация строки в число double
	
	int len = m_lineValue.LineLength(m_lineValue.LineIndex(0));
	CString line;
	m_lineValue.GetLine(0, line.GetBuffer(len), len);
	line.ReleaseBuffer(len);

	return wcstod(line, NULL);
}

// Обработчики сообщений CalculatorDlg

//кнопка =
void CalculatorDlg::OnBnClickedBResult()
{
	double value = convertLineToDouble();
	m_calc.addValue(value); // устанавливаем значение
		
	double result = m_calc.calculate(); //считаем

	m_lineValue.SetWindowText(_T(""));

	CString line;
	line.Format(L"%g", result);
	m_lineValue.ReplaceSel(line, TRUE);
}


void CalculatorDlg::OnBnClickedBClear()
{
	m_calc.clear();
	m_lineValue.SetWindowText(_T(""));
	
}

//кнопка смена знака числа +/-
void CalculatorDlg::OnBnClickedBSifUsig()
{
	changeSign();
}

//кнопка  разделить
void CalculatorDlg::OnBnClickedButtonSplit()
{
	double value = convertLineToDouble(); 
	m_calc.addValue(value); //добавляем значение
	m_calc.setOperator('/'); //указываем оператор

	m_lineValue.SetWindowText(_T("")); //очищаем строку
}

//кнопка минус
void CalculatorDlg::OnBnClickedBMinus()
{
	double value = convertLineToDouble();
	m_calc.addValue(value);
	m_calc.setOperator('-');

	m_lineValue.SetWindowText(_T(""));
}

//кнопка умножить
void CalculatorDlg::OnBnClickedButtonMult()
{
	double value = convertLineToDouble();
	m_calc.addValue(value);
	m_calc.setOperator('*');

	m_lineValue.SetWindowText(_T(""));
}

//кнопка плюс
void CalculatorDlg::OnBnClickedBPlus()
{
	double value = convertLineToDouble();
	m_calc.addValue(value);
	m_calc.setOperator('+');

	m_lineValue.SetWindowText(_T(""));
}


//Функции добавления в строку

void CalculatorDlg::OnBnClickedButton1()
{
	addLine(L"1");
}

void CalculatorDlg::OnBnClickedButton2()
{
	addLine(L"2");
}

void CalculatorDlg::OnBnClickedButton3()
{
	addLine(L"3");
}

void CalculatorDlg::OnBnClickedButton4()
{
	addLine(L"4");
}


void CalculatorDlg::OnBnClickedButton5()
{
	addLine(L"5");
}

void CalculatorDlg::OnBnClickedButton6()
{
	addLine(L"6");
}

void CalculatorDlg::OnBnClickedButton7()
{
	addLine(L"7");
}

void CalculatorDlg::OnBnClickedButton8()
{
	addLine(L"8");
}

void CalculatorDlg::OnBnClickedButton9()
{
	addLine(L"9");
}

void CalculatorDlg::OnBnClickedBButton0()
{
	addLine(L"0");
}

void CalculatorDlg::OnBnClickedBDecimal()
{
	addLine(L".");
}
