
// gPrjDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "gPrj.h"
#include "gPrjDlg.h"
#include "afxdialogex.h"
#include "CDlgImage.h"

#include <iostream>
using namespace std;
#include "CProcess.h"
#include <chrono>
using namespace chrono;
#include <thread>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#pragma comment(linker, "/entry:WinMainCRTStartup /subsystem:console")

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CgPrjDlg 대화 상자



CgPrjDlg::CgPrjDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GPRJ_DIALOG, pParent)
	, circleNum(33)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgPrjDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, circleNum);
}

BEGIN_MESSAGE_MAP(CgPrjDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//ON_BN_CLICKED(IDC_BUTTON1, &CgPrjDlg::OnBnClickedButton1)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDOK, &CgPrjDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_Test, &CgPrjDlg::OnBnClickedTest)
	ON_BN_CLICKED(IDC_BTN_PROCESS, &CgPrjDlg::OnBnClickedBtnProcess)
	ON_BN_CLICKED(IDC_BTN_MAKE_PATTERN, &CgPrjDlg::OnBnClickedBtnMakePattern)
	ON_BN_CLICKED(IDC_BTN_GET_DATA, &CgPrjDlg::OnBnClickedBtnGetData)
	ON_BN_CLICKED(IDC_BTN_THREAD, &CgPrjDlg::OnBnClickedBtnThread)
END_MESSAGE_MAP()


// CgPrjDlg 메시지 처리기

BOOL CgPrjDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	MoveWindow(0, 0, 1280, 800);
	m_pDlgImage = new CDlgImage;
	m_pDlgImage->Create(IDD_CDlgImage, this);
	m_pDlgImage->ShowWindow(SW_SHOW);
	m_pDlgImage->MoveWindow(0, 0, 640, 480);

	m_pDlgImgResult = new CDlgImage;
	m_pDlgImgResult->Create(IDD_CDlgImage, this);
	m_pDlgImgResult->ShowWindow(SW_SHOW);
	m_pDlgImgResult->MoveWindow(640, 0, 0, 0);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CgPrjDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CgPrjDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CgPrjDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//void CgPrjDlg::OnBnClickedButton1()
//{
//	m_pDlgImage->ShowWindow(SW_SHOW);
	//CDlgImage dlg;
	//dlg.DoModal();
//}


void CgPrjDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	if(m_pDlgImage)		delete m_pDlgImage;
	if(m_pDlgImgResult)	delete m_pDlgImgResult;
}


void CgPrjDlg::callFunc(int n) 
{
	int nData = n;
	cout << n << endl;
}

void CgPrjDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}


void CgPrjDlg::OnBnClickedTest()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	//memset(fm, 0, 320*240);

	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();

	int nWidth = m_pDlgImage->m_Image.GetWidth();
	int nHeight = m_pDlgImage->m_Image.GetHeight();
	int nPitch = m_pDlgImage->m_Image.GetPitch();
	memset(fm, 0, nWidth * nHeight);


	unsigned char* fm2 = (unsigned char*)m_pDlgImgResult->m_Image.GetBits();
	memset(fm2, 0, 640 * 480);


	int nTest = GetDlgItemInt(IDC_EDIT1);
	m_pDlgImage->SetRadius(GetDlgItemInt(IDC_EDIT1));
	
	int x = rand() % nWidth;
	int y = rand() % nHeight;
	// fm[y * nPitch + x] = (rand()%250) +1;
	fm[y * nPitch + x] = 255;
	

	
	int nIndex = 0;
	int nTh = 100;
	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			if (fm[j * nPitch + i] > nTh) {
				if (m_pDlgImgResult->m_nDataCount < nTest)				// Max_POINT 대체
				{
					m_pDlgImgResult->m_ptData[nIndex].x = i;
					m_pDlgImgResult->m_ptData[nIndex].y = j;
					m_pDlgImgResult->m_nDataCount = ++nIndex;
				}
				//cout << nSum << "\t" << i << "," << j << endl;
				//nSum++;
			}
		}
	}

	nIndex = 0;
	m_pDlgImage->m_nDataCount = 0;
	
	for (int j = 0; j < nHeight; j++) {
		for (int i = 0; i < nWidth; i++) {
			if (fm[j * nPitch + i] > nTh) {
				if (m_pDlgImage->m_nDataCount == 0)				
				{
					cout  << "x :" << i << "\ty :" << j << endl;
					m_pDlgImage->m_ptData[nIndex].x = i;
					m_pDlgImage->m_ptData[nIndex].y = j;
					m_pDlgImage->m_nDataCount++;
				}
				//cout << nSum << "\t" << i << "," << j << endl;
				//nSum++;
			}
		}
	}

	// cout << nSum << endl;
	m_pDlgImage->Invalidate();
	m_pDlgImgResult->Invalidate(); // m_pDlgImgResult 데이터 만들었으면 이걸 선언해야 사용가능
}


void CgPrjDlg::OnBnClickedBtnProcess()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CProcess process;

	auto start = std::chrono::system_clock::now();
	int nRet = process.getStarInfo(&m_pDlgImage->m_Image, 10);//process.getStarInfo(&m_pDlgImage->m_Image, 100);
	auto end = std::chrono::system_clock::now();
	auto millisec = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

	cout << nRet <<"\t" << millisec.count() << "ms" << endl;
}


void CgPrjDlg::OnBnClickedBtnMakePattern()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();
	int nWidth = m_pDlgImage->m_Image.GetWidth();
	int nHeight = m_pDlgImage->m_Image.GetHeight();
	int nPitch = m_pDlgImage->m_Image.GetPitch();
	memset(fm, 0, nWidth * nHeight);

	CRect rect(100, 100, 200, 200);
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			fm[j * nPitch + i] = rand() % 0xff;
		}
	}
	m_pDlgImage->Invalidate(); // 이걸 해야 여기서 처리한 데이터가 영상에 반영
}


void CgPrjDlg::OnBnClickedBtnGetData()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	unsigned char* fm = (unsigned char*)m_pDlgImage->m_Image.GetBits();
	int nWidth = m_pDlgImage->m_Image.GetWidth();
	int nHeight = m_pDlgImage->m_Image.GetHeight();
	int nPitch = m_pDlgImage->m_Image.GetPitch();
	memset(fm, 0, nWidth * nHeight);

	int nTh = 0x01;
	CRect rect(0, 0, nWidth, nHeight);
	int nSumX = 0;
	int nSumY = 0;
	int nCount = 0;
	for (int j = rect.top; j < rect.bottom; j++) {
		for (int i = rect.left; i < rect.right; i++) {
			if (fm[j * nPitch + i] > nTh) {
				nSumX += i;
				nSumY += j;
				nCount++;
			}
		}
	}

	double dCenterX = (double)nSumX / nCount;
	double dCenterY = (double)nSumY / nCount;

	cout << dCenterX << "\t" << dCenterY << endl;

}

void threadProcess(CWnd* pParent, CRect rect, int* nRet) 
{
	CgPrjDlg* pWnd = (CgPrjDlg*)pParent;
	*nRet = pWnd->processImg(rect);
}

void CgPrjDlg::OnBnClickedBtnThread()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	auto start = system_clock::now();

	int nImgSize = 4096 * 4;
	CRect rect(0, 0, nImgSize, nImgSize);
	CRect rt[4] = {0,0,0,0};
	int nRet[4];
	//rt[0].SetRect(0,		0,			nImgSize,		nImgSize);
	//rt[1].SetRect(nImgSize, 0,			nImgSize * 2,	nImgSize);
	//rt[2].SetRect(0,		nImgSize,	nImgSize,		nImgSize * 2);
	//rt[3].SetRect(nImgSize, 0,			nImgSize * 2,	nImgSize);
	for (int k = 0; k < 4; k++) {
		rt[k] = rect;
		rt[k].OffsetRect(nImgSize * (k % 2), nImgSize * int(k / 2));
	}
	thread _thread0(threadProcess, this, rt[0], &nRet[0]);
	thread _thread1(threadProcess, this, rt[1], &nRet[1]);
	thread _thread2(threadProcess, this, rt[2], &nRet[2]);
	thread _thread3(threadProcess, this, rt[3], &nRet[3]);
	_thread0.detach(); // join은 세트로 묶은 작업들 기다림
	_thread1.detach();
	_thread2.detach();
	_thread3.detach();

	int nSum = 0;
	for (int i = 0; i < 4; i++) {
		nSum += nRet[i];
	}

	auto end = system_clock::now();
	auto millisec = duration_cast<milliseconds>(end - start);
	cout << "main:" << nSum << "\t" << millisec.count() * 0.001 << "sec" << endl;

}

int CgPrjDlg::processImg(CRect rect) 
{
	auto start = system_clock::now();
	CProcess process;

	int nRet = process.getStarInfo(&m_pDlgImage->m_Image, 0, rect);

	auto end = system_clock::now();
	auto millisec = duration_cast<milliseconds>(end - start);
	cout << "thread:" << nRet << "\t" << millisec.count() * 0.001 << "sec" << endl;

	return nRet;
}