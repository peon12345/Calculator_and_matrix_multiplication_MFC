// MatrixDlg.cpp: файл реализации
//

#include "pch.h"
#include "CalcAndMat.h"
#include "MatrixDlg.h"
#include "afxdialogex.h"

// Диалоговое окно MatrixDlg

IMPLEMENT_DYNAMIC(MatrixDlg, CDialog)

MatrixDlg::MatrixDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MatrixDlg, pParent)
{
	gen.seed(time(0));
	m_currentPageNum = 1; 
}

MatrixDlg::~MatrixDlg()
{
}

void MatrixDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, ID_MAT1, m_matTab);
	GetDlgItem(IDC_B_PrevTab)->EnableWindow(FALSE);
}

BEGIN_MESSAGE_MAP(MatrixDlg, CDialog)
	ON_BN_CLICKED(IDC_B_AddRowTab1, &MatrixDlg::OnBnClickedBAddrowtab1)
	ON_BN_CLICKED(IDC_B_AddColTab1, &MatrixDlg::OnBnClickedBAddcoltab1)
	ON_BN_CLICKED(IDC_EditMat1, &MatrixDlg::OnBnClickedEditmat1)
	ON_BN_CLICKED(IDC_B_NextTab, &MatrixDlg::OnBnClickedBNexttab)
	ON_BN_CLICKED(IDC_B_PrevTab, &MatrixDlg::OnBnClickedBPrevtab)
END_MESSAGE_MAP()


bool MatrixDlg::checkSizeMat(int pageNum) {

	int cols = m_matTab.GetHeaderCtrl()->GetItemCount();
	int rows = m_matTab.GetItemCount();

	//проверка размерности
	if (cols >= 2 && rows >= 2) { // проверка на минимальную размерность

		switch (pageNum)
		{
		case 1:
			return true;
			break;
		case 2:
			int colsMat1 = m_mat1.getCol();

			if (colsMat1 == rows) { // если столбцы и строки двух совпадают , то ок
				return true;
			}
			break;
		}
	}

	return false;
}

void MatrixDlg::clearMatTab() {

	while (m_matTab.GetHeaderCtrl()->GetItemCount() != 0) {
		m_matTab.DeleteColumn(0);
	}
	m_matTab.DeleteAllItems();
}


void MatrixDlg::FillList() {
	std::uniform_int_distribution<int> randValue (0, 1000);

	int cols = m_matTab.GetHeaderCtrl()->GetItemCount();
	
	//заполняются пустые участки случайными значениями
	for (int i = 0; i < cols; i++) {

		for (int j = 0; j < m_matTab.GetItemCount(); ++j) {

			if (m_matTab.GetItemText(j, i) != "") {
				continue;
			}

			int value = randValue(gen);

			CString valueStr;
			valueStr.Format(L"%d", value);
			m_matTab.SetItemText(j, i, valueStr);
		}
	}
}

// Обработчики сообщений MatrixDlg

//добавление записи в CListCtrl
void MatrixDlg::OnBnClickedBAddrowtab1()
{
	int nItem = m_matTab.InsertItem(m_matTab.GetItemCount(), L"", -1);
	FillList();
}

//добавление столбца в CListCtrl
void MatrixDlg::OnBnClickedBAddcoltab1()
{
	int posCol = m_matTab.GetHeaderCtrl()->GetItemCount();

	CString posStr;
	posStr.Format(L"%d", posCol);
	m_matTab.InsertColumn(posCol, posStr,LVCFMT_LEFT,40);

	FillList();
}

void MatrixDlg::OnBnClickedEditmat1()
{
	EditMatDlg editMat(m_matTab); //вызов окна редактирования
	editMat.DoModal();
}

void MatrixDlg::OnBnClickedBNexttab()
{
	if (!checkSizeMat(m_currentPageNum)) {
		MessageBox(L"Неверное число строк или столбцов.");
		return void();
	}

	++m_currentPageNum;
	
	if (m_currentPageNum == 2) { // если переходим на вторую матрицу(страницу)
		m_mat1.FillMat(m_matTab); // сохраняем первую матрицу из CListCtrl в объект матрицы
		clearMatTab(); //очищаем ClistCtrl
		m_mat2.getMat(m_matTab);  //передаем данные из второй матрицы в ClistCtrl

		GetDlgItem(IDC_B_PrevTab)->EnableWindow(TRUE); //включаем кнопку НАЗАД
		GetDlgItem(IDC_CurrentTableLabel)->SetWindowTextW(L"Матрица №2"); 
		GetDlgItem(IDC_B_NextTab)->SetWindowTextW(L"Результат");
	}
	else {                                // Если переходим на страницу 3 ( Результат)
		m_mat2.FillMat(m_matTab); // сохраняем созданную матрицу
		clearMatTab();
		m_matResult = m_mat1 * m_mat2; //умножаем 

		m_matResult.getMat(m_matTab); // показываем результат


		GetDlgItem(IDC_CurrentTableLabel)->SetWindowTextW(L"Матрица №3");
		
        GetDlgItem(IDC_EditMat1)->EnableWindow(FALSE);  //отключаем кнопки
		GetDlgItem(IDC_B_AddColTab1)->EnableWindow(FALSE);
		GetDlgItem(IDC_B_AddRowTab1)->EnableWindow(FALSE);
		GetDlgItem(IDC_B_NextTab)->EnableWindow(FALSE);
	}
}

void MatrixDlg::OnBnClickedBPrevtab()
{
	--m_currentPageNum;

	GetDlgItem(IDC_EditMat1)->EnableWindow(TRUE);  
	GetDlgItem(IDC_B_AddColTab1)->EnableWindow(TRUE); //подключаем кнопки, могут быть отключены после страницы 
	GetDlgItem(IDC_B_AddRowTab1)->EnableWindow(TRUE);  //c результатом
	GetDlgItem(IDC_B_NextTab)->EnableWindow(TRUE);

	if (m_currentPageNum == 1) { 

		m_mat2.FillMat(m_matTab);
		clearMatTab();
		m_mat1.getMat(m_matTab);

		GetDlgItem(IDC_B_PrevTab)->EnableWindow(FALSE);
		GetDlgItem(IDC_B_NextTab)->EnableWindow(TRUE);
		GetDlgItem(IDC_B_NextTab)->SetWindowTextW(L"Далее");
		GetDlgItem(IDC_CurrentTableLabel)->SetWindowTextW(L"Матрица №1");
	}
	else {
		clearMatTab();
		m_mat2.getMat(m_matTab);

		GetDlgItem(IDC_B_NextTab)->SetWindowTextW(L"Результат");
		GetDlgItem(IDC_CurrentTableLabel)->SetWindowTextW(L"Матрица №2");
	}
	
}
