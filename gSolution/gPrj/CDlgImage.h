﻿#pragma once
#include "afxdialogex.h"

#define MAX_POINT 1000000

// CDlgImage 대화 상자

class CDlgImage : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgImage();

	CImage m_Image;
	CWnd* m_pParent;
	int m_nDataCount = 0;
	CPoint m_ptData[MAX_POINT];

	void SetRadius(int size);
	int GetRadius();

private:
	int circleR;

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlgImage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

private:
	void drawData(CDC* pDC);
	void InitImage();
public:
	afx_msg void OnBnClickedBtnUp();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

	// void InitImage();
};
