// EditMatDlg.cpp: файл реализации
//

#include "pch.h"
#include "CalcAndMat.h"
#include "EditMatDlg.h"
#include "afxdialogex.h"

#include "iostream"


// Диалоговое окно EditMatDlg

IMPLEMENT_DYNAMIC(EditMatDlg, CDialog)

EditMatDlg::EditMatDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_EditMatDlg, pParent)
{
	
}

EditMatDlg::EditMatDlg(CListCtrl& matTab) : EditMatDlg()
{
	editList = &matTab;
}

EditMatDlg::~EditMatDlg()
{
}

void EditMatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_Edit);

	//заполняем элемент текстом из CtrilList
    FillEditControl();
}

void EditMatDlg::FillEditControl() {

	int cols = editList->GetHeaderCtrl()->GetItemCount();

	for (int i = 0; i < editList->GetItemCount(); i++) {
		for (int j = 0; j < cols; ++j) {

			CString valueStr;
			valueStr = editList->GetItemText(i, j);
			m_Edit.ReplaceSel(valueStr, TRUE);

			//если не последний элемент, то разделяем пробелом
			if (j != cols - 1) {
				m_Edit.ReplaceSel(L" ", TRUE);
			}
		}

		m_Edit.ReplaceSel(L"\r\n", TRUE);
	}
}


BEGIN_MESSAGE_MAP(EditMatDlg, CDialog)
	ON_BN_CLICKED(ID_Save, &EditMatDlg::OnBnClickedSave)
END_MESSAGE_MAP()


// Обработчики сообщений EditMatDlg

void EditMatDlg::OnBnClickedSave()
{
	//удаляем столбцы
	while (editList->GetHeaderCtrl()->GetItemCount() != 0) {
		editList->DeleteColumn(0);
	}

	editList->DeleteAllItems();

	int nLineCount = m_Edit.GetLineCount();

	for(int lineIndex = 0; lineIndex < nLineCount; lineIndex++)
	{
		int len = m_Edit.LineLength(m_Edit.LineIndex(lineIndex)); // получаем длину строки ( в окне редактирования)

		CString line;
		m_Edit.GetLine(lineIndex, line.GetBuffer(len), len);
		line.ReleaseBuffer(len); // получили значения первой строки 

		CString temp = line;
		temp.Remove(' ');
		if (temp == ""){ // || temp.SpanIncluding(L"0123456789") != temp) {
			continue;
		}

		editList->InsertItem(editList->GetItemCount(), L"", -1);

		CString sToken = _T("");
		int numCount = 0;

		int colIndex = 0;
		while (AfxExtractSubString(sToken, line, numCount, ' ')) {

			//если ввели не число 
			if (sToken.SpanIncluding(L"0123456789") != sToken ||  sToken == L"") {
				numCount++;
				continue;
			}

			//добавляем новый столбец , если не хватает
			if (colIndex > editList->GetHeaderCtrl()->GetItemCount()-1 && sToken != L"")
			{
				int posCol = editList->GetHeaderCtrl()->GetItemCount(); 
				CString posStr;
				posStr.Format(L"%d", posCol);
				int nWidth = editList->GetStringWidth(sToken);
				editList->InsertColumn(posCol, posStr, LVCFMT_LEFT, nWidth + 30);
			}

			editList->SetItemText(lineIndex, colIndex, sToken); 

			colIndex++;
			numCount++;
		}
	}
	this->EndDialog(1);
}
