
// mfcCimageDlg.h: 헤더 파일
//

#pragma once


// CmfcCimageDlg 대화 상자
class CmfcCimageDlg : public CDialogEx
{
private:
	CImage m_image;
	BOOL validImagePos(int x, int y);
// 생성입니다.
public:
	CmfcCimageDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCIMAGE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnImage();
	afx_msg void OnBnClickedBntSave();
	afx_msg void OnBnClickedBntLoad();
	void UpdateDisplay();
	void moveRect();
	void drawCircle(unsigned char* fm, int i, int j, int nRadius, int nGray);
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);

	void drawRandomwCircle(unsigned char* fm, int i, int j, int nRadius, int nGray);

	afx_msg void OnBnClickedBtnAction();
	afx_msg void OnBnClickedBtnRandom();
};
