#pragma once


// Model �Ի���

class Model : public CDialogEx
{
	DECLARE_DYNAMIC(Model)

public:
	Model(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~Model();

// �Ի�������
	enum { IDD = IDD_DIALOGMODEL};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
