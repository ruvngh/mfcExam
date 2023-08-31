﻿// CDlgImage.cpp: 구현 파일
//

#include "pch.h"
#include "gPrj.h"
#include "afxdialogex.h"
#include "CDlgImage.h"


// CDlgImage 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialogEx)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDlgImage, pParent),
	m_raidus(0)
{
	m_pParent = pParent;
}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::SetRadius(int size)
{
	m_raidus = size;
}

int CDlgImage::GetRadius()
{
	return m_raidus;
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_UP, &CDlgImage::OnBnClickedBtnUp)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDlgImage 메시지 처리기

#include "gPrjDlg.h"
void CDlgImage::OnBnClickedBtnUp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	static int n = 100;
	CgPrjDlg *pDlg = (CgPrjDlg*)m_pParent;
	pDlg->callFunc(n++);
}


BOOL CDlgImage::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	// AfxMessageBox(_T("ready?"));
	MoveWindow(0, 0, 640, 480);

	InitImage();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if (m_Image) {
		m_Image.Draw(dc, 0, 0);
	}

	drawData(&dc);
}


void CDlgImage::InitImage() 
{
	int nWidth = 640; //4096*8;
	int nHeight = 480; //4096*8;
	int nBpp = 8;

	m_Image.Create(nWidth, -nHeight, nBpp);
	if (nBpp == 8) {
		static RGBQUAD rgb[256];
		for (int i = 0; i < 256; i++)
			rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
		m_Image.SetColorTable(0, 256, rgb);
	}

	int nPitch = m_Image.GetPitch();
	unsigned char* fm = (unsigned char*)m_Image.GetBits();

	memset(fm, 0xff, nWidth * nHeight);
}


#define COLOR_RED	RGB(0xff, 0x00, 0x00)
#define COLOR_GREEN RGB(0x00, 0xff, 0x00)
#define COLOR_YELLOW RGB(0xff, 0xff, 0x00)
void CDlgImage::drawData(CDC* pDC)
{
	//CRect rect(0, 0, 640, 480);
	//pDC->Ellipse(rect);

	CRect rect;
	CPen pen;
	pen.CreatePen(PS_SOLID, 1, COLOR_YELLOW);
	CPen* pOldPen = pDC->SelectObject(&pen);

	CBrush brush;
	brush.CreateSolidBrush(RGB(0, 0, 0));
	CBrush* oldBrush = pDC->SelectObject(&brush);

	for (int i = 0; i < m_nDataCount; i++) { // m_nDataCount
		rect.SetRect(m_ptData[i], m_ptData[i]);
		rect.InflateRect(m_raidus, m_raidus);
		pDC->Ellipse(rect);

		rect.SetRect(m_ptData[i], m_ptData[i]);
		rect.InflateRect(1, m_raidus);
		pDC->Ellipse(rect);
		rect.SetRect(m_ptData[i], m_ptData[i]);
		rect.InflateRect(m_raidus, 1);
		pDC->Ellipse(rect);
	}
	pDC->SelectObject(pOldPen);
}