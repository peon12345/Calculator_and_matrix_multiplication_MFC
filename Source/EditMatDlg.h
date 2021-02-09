#pragma once


// Диалоговое окно EditMatDlg

class EditMatDlg : public CDialog
{
	DECLARE_DYNAMIC(EditMatDlg)

public:
	
	EditMatDlg(CListCtrl& matTab);
	virtual ~EditMatDlg();

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EditMatDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:

private:
	EditMatDlg(CWnd* pParent = nullptr);   // стандартный конструктор

	void FillEditControl();
	CListCtrl *editList;
public:
	CEdit m_Edit;
	afx_msg void OnBnClickedSave();
};
