// Model.cpp : 实现文件
//

#include "stdafx.h"
#include "mfc-init.h"
#include "Model.h"
#include "afxdialogex.h"


// Model 对话框

IMPLEMENT_DYNAMIC(Model, CDialogEx)

Model::Model(CWnd* pParent /*=NULL*/)
	: CDialogEx(Model::IDD, pParent)
{

}

Model::~Model()
{
}

void Model::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(Model, CDialogEx)
END_MESSAGE_MAP()


// Model 消息处理程序
