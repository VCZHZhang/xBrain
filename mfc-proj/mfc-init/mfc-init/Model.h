#pragma once


// Model 对话框

class Model : public CDialogEx
{
	DECLARE_DYNAMIC(Model)

public:
	Model(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Model();

// 对话框数据
	enum { IDD = IDD_DIALOGMODEL};

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
