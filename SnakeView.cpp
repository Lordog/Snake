// SnakeView.cpp : implementation of the CSnakeView class
//

#include "stdafx.h"
#include "Snake.h"
#include "math.h"

#include "mmsystem.h"                   // ������Ч
#pragma comment(lib,"winmm.lib")        // ��������ͷ�ļ���

#include "MainFrm.h"
#include "SnakeDoc.h"
#include "SnakeCore.h"
#include "SnakeView.h"
#include "SnakeSetDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSnakeView

IMPLEMENT_DYNCREATE(CSnakeView, CView)

BEGIN_MESSAGE_MAP(CSnakeView, CView)
	//{{AFX_MSG_MAP(CSnakeView)
	ON_WM_KEYDOWN()
	ON_COMMAND(IDC_GAME_START, OnGameStart)
	ON_WM_TIMER()
	ON_COMMAND(IDC_GAME_SET, OnGameSet)
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// �����ߺ�����Ķ���
CSnakeCore aSnake;
// �������öԻ��������
CSnakeSetDlg aSetDlg;

/////////////////////////////////////////////////////////////////////////////
// CSnakeView construction/destruction

CSnakeView::CSnakeView()
{
	// TODO: add construction code here
}

CSnakeView::~CSnakeView()
{
}

BOOL CSnakeView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CSnakeView drawing

void CSnakeView::OnDraw(CDC* pDC)
{
	CSnakeDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	// TODO: add draw code for native data here   

        // ����Ϸ����
        CBrush* edge;
        edge = new CBrush;
        edge->CreateSolidBrush(RGB(0xFF, 0xFF, 0xFF));
        pDC->SelectObject(edge);
        pDC->Rectangle(aSnake.x, aSnake.y, 
                       aSnake.x + aSnake.width * aSnake.pixel, 
                       aSnake.y + aSnake.height * aSnake.pixel
                      );
        delete edge;

        /*
        // ��ʾ�ȼ�
        CString levelText;
        levelText.Format("�ȼ���%d", aSnake.level);
        pDC->TextOut(aSnake.x,
                     aSnake.y + aSnake.height * aSnake.pixel +15,
                     levelText);

        // ��ʾ�÷�
        CString scoreText;
        scoreText.Format("�÷֣�%06d", aSnake.score);
        pDC->TextOut(aSnake.x + 80,
                     aSnake.y + aSnake.height * aSnake.pixel +15,
                     scoreText);
        */

        CBrush* body;
        body = new CBrush;
        body->CreateSolidBrush(RGB(0xB2, 0x22, 0x22));          // ������ɫ
        // ��ʾ����
        for (int i = 0; i <= aSnake.snakeBody.GetUpperBound(); i++) {
                CPoint bPoint = aSnake.snakeBody.GetAt(i);
                pDC->FillRect(CRect(aSnake.x + bPoint.x * aSnake.pixel,
                                    aSnake.y + bPoint.y * aSnake.pixel, 
                                    aSnake.x + (bPoint.x + 1) * aSnake.pixel,
                                    aSnake.y + (bPoint.y + 1) * aSnake.pixel
                                   ), body
                             );
        }
        delete body;

        // ��ʾʳ��
        CBrush* food;
        food = new CBrush;
        food->CreateSolidBrush(RGB(0x2E, 0x88, 0x57));          // ʳ����ɫ
        pDC->FillRect(CRect(aSnake.x + aSnake.food.x * aSnake.pixel, 
                            aSnake.y + aSnake.food.y * aSnake.pixel, 
                            aSnake.x + (aSnake.food.x + 1) * aSnake.pixel, 
                            aSnake.y + (aSnake.food.y + 1) * aSnake.pixel
                           ), food);
        delete food;

}

/////////////////////////////////////////////////////////////////////////////
// CSnakeView diagnostics

#ifdef _DEBUG
void CSnakeView::AssertValid() const
{
	CView::AssertValid();
}

void CSnakeView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSnakeDoc* CSnakeView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSnakeDoc)));
	return (CSnakeDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSnakeView message handlers

void CSnakeView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
        
        switch (nChar) {
        case VK_UP:
                if (aSnake.currentDirection != DOWN && !aSnake.hasChanged) {
                        aSnake.currentDirection = UP;
                        aSnake.hasChanged = true;
                }
                break;
        case VK_DOWN:
                if (aSnake.currentDirection != UP && !aSnake.hasChanged) {
                        aSnake.currentDirection = DOWN;
                        aSnake.hasChanged = true;
                }
                break;
        case VK_LEFT:
                if (aSnake.currentDirection != RIGHT && !aSnake.hasChanged) {
                        aSnake.currentDirection = LEFT;
                        aSnake.hasChanged = true;
                }
                break;
        case VK_RIGHT:
                if (aSnake.currentDirection != LEFT && !aSnake.hasChanged) {
                        aSnake.currentDirection = RIGHT;
                        aSnake.hasChanged = true;
                }
                break;
        case VK_SPACE:
                if (aSnake.isPause) {
                        aSnake.isPause = false;
                }
                else {
                        aSnake.isPause = true;
                }
                break;
        default:
                break;
        }
        
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CSnakeView::ReDraw(CPoint point) {
        InvalidateRect(CRect(aSnake.x + point.x * aSnake.pixel, 
                             aSnake.y + point.y * aSnake.pixel, 
                             aSnake.x + (point.x + 1) * aSnake.pixel, 
                             aSnake.y + (point.y + 1) * aSnake.pixel
                            )
                      );
}

void CSnakeView::OnGameStart() 
{
	// TODO: Add your command handler code here
        aSnake.initSnake();
        int speed = int (1000 / pow(1.5, aSnake.level));
        SetTimer(1, speed, NULL);
        Invalidate();
        CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
        CStatusBar* pStatus = &pFrame->m_wndStatusBar;
        // ����״̬���ı����ٶȣ�
        CString lvl;
        lvl.Format("�ٶȣ�%d", aSnake.level);
        pStatus->SetPaneText(0, lvl);
        // ����״̬���ı���������
        CString scr;
        scr.Format("������%06d", aSnake.score);
        pStatus->SetPaneText(1, scr);

        
}

void CSnakeView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

        if (aSnake.isPause) {
                // ��ȡ״̬��ָ��
                CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
                CStatusBar* pStatus = &pFrame->m_wndStatusBar;
                pStatus->SetPaneText(2, "��Ϸ��ͣ");
                /*
                CDC *pDC = GetDC();
		pDC->TextOut(aSnake.x + 320, aSnake.y + aSnake.height * aSnake.pixel + 15,
                             "��Ϸ��ͣ");
		ReleaseDC(pDC);
                */
        }

        else if (aSnake.isOver){
                KillTimer(1);
                // ������Ϸ��������Ч
                if (aSnake.hasSound) {
                        if (aSnake.score > 1000) {
                                PlaySound((LPCTSTR)IDR_DEADXSND, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
                        }
                        else {
                                PlaySound((LPCTSTR)IDR_DEADSND, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC); 
                        }
                }
                // ��ȡ״̬��ָ��
                CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
                CStatusBar* pStatus = &pFrame->m_wndStatusBar;
                pStatus->SetPaneText(2, "��Ϸ����");
                /*
                CDC *pDC = GetDC();
		pDC->TextOut(aSnake.x + 320, aSnake.y + aSnake.height * aSnake.pixel + 15,
                             "��Ϸ����");
		ReleaseDC(pDC);
                */
        }

        else {
                // ��ȡ״̬��ָ��
                CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
                CStatusBar* pStatus = &pFrame->m_wndStatusBar;
                pStatus->SetPaneText(2, "        ");

                CPoint head = aSnake.snakeBody.GetAt(0);       // ��ȡ��ͷ

                switch (aSnake.currentDirection) {
                case UP:
                        if (aSnake.currentDirection != DOWN) {
                                head.y--;
                        }
                        break;
                case DOWN:
                        if (aSnake.currentDirection != UP) {
                                head.y++;
                        }
                        break;
                case LEFT:
                        if (aSnake.currentDirection != RIGHT) {
                                head.x--;
                        }
                        break;
                case RIGHT:
                        if (aSnake.currentDirection != LEFT) {
                                head.x++;
                        }
                        break;
                }

                // ����ǽ��
                if (head.x < 0 || head.x >= aSnake.width || head.y < 0 || head.y >= aSnake.height) {
                        aSnake.isOver = true;
                }
                // ��������
                if (!aSnake.isOver) {
                        for (int i = 1; i <= aSnake.snakeBody.GetUpperBound(); i++) {
                                if (head == aSnake.snakeBody.GetAt(i)) {
                                        aSnake.isOver = true;
                                        break;
                                }
                        }
                }

                if (!aSnake.isOver) {
                        aSnake.snakeBody.InsertAt(0, head);
                        ReDraw(head);
                
                        if (head != aSnake.food) {
                                // ɾ����β
                                CPoint tmpPoint = aSnake.snakeBody.GetAt(aSnake.snakeBody.GetUpperBound());
                                aSnake.snakeBody.RemoveAt(aSnake.snakeBody.GetUpperBound());
                                ReDraw(tmpPoint);
                        }
                        // �Ե�ʳ��
                        else {
                                // ���ųԵ�ʳ�����Ч
                                if (aSnake.hasSound) {
                                        PlaySound((LPCTSTR)IDR_EATSND, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC); 
                                }
                                // ˢ�·���
                                aSnake.score += aSnake.level;
                                // ��ȡ״̬��ָ��
                                CMainFrame* pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
                                CStatusBar* pStatus = &pFrame->m_wndStatusBar;
                                CString scr;
                                scr.Format("������%06d", aSnake.score);
                                pStatus->SetPaneText(1, scr);

                                /*
                                InvalidateRect(CRect(aSnake.x + 80, 
                                                     aSnake.y + aSnake.height * aSnake.pixel + 15, 
                                                     aSnake.x + aSnake.width * aSnake.pixel, 
                                                     aSnake.y + aSnake.height * aSnake.pixel + 35
                                                    )
                                               );
                                */
                                

                                // ˢ��ʳ��
                                aSnake.createFood();
                                ReDraw(aSnake.food);
                                
                        }
                }
                aSnake.hasChanged = false;
        }
	CView::OnTimer(nIDEvent);
}

void CSnakeView::OnGameSet() 
{
	// TODO: Add your command handler code here
        aSetDlg.m_nLevel = aSnake.level;
        aSetDlg.m_nMusic = aSnake.hasMusic;
        aSetDlg.m_nSound = aSnake.hasSound;
        if (aSetDlg.DoModal() == IDOK) {
                aSnake.level = aSetDlg.m_nLevel;
                //aSnake.pixel = aSetDlg.m_nPixel;
                aSnake.hasMusic = aSetDlg.m_nMusic;
                aSnake.hasSound = aSetDlg.m_nSound;
                KillTimer(1);
                OnGameStart();
        }
}

void CSnakeView::OnKillFocus(CWnd* pNewWnd) 
{
	CView::OnKillFocus(pNewWnd);
	
	// TODO: Add your message handler code here
        aSnake.isPause = 1;
}

void CSnakeView::OnSetFocus(CWnd* pOldWnd) 
{
	CView::OnSetFocus(pOldWnd);
	
	// TODO: Add your message handler code here
        aSnake.isPause = 0;
}
