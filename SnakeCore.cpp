// SnakeCore.cpp: implementation of the SnakeCore class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Snake.h"
#include "SnakeCore.h"

#include "MainFrm.h"
#include "SnakeDoc.h"
#include "SnakeView.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSnakeCore::CSnakeCore()
{
        initSnake();
         // ��ʼ���ȼ������ش�С
        level = 7; 
        pixel = 10;  
        
        // ��ʼ�����ֺ���Ч
        hasMusic = FALSE;
        hasSound = TRUE;
}

CSnakeCore::~CSnakeCore()
{

}
void CSnakeCore::initSnake() {
        // ��ʼ����Ϸ����
        x = 1;
        y = 1;
        width = 50;
        height = 40;


        // ��ʼ����Ϸ����
        score = 0;

        isPause = false;
        isOver = false;
        
        snakeBody.RemoveAll();
        snakeBody.Add(CPoint(6, 36));    // ��ͷ
        snakeBody.Add(CPoint(5, 36));
        snakeBody.Add(CPoint(4, 36));
        snakeBody.Add(CPoint(3, 36));    // ��β
        currentDirection = RIGHT;

        createFood();

        // ��ʼ�������������
        srand((unsigned) time(NULL));
}

void CSnakeCore::createFood() {
        CPoint t_food;
        bool isDup = false;

        for ( ; ; ) {
                // ����һ��ʳ��
                t_food.x = rand() % width;
                t_food.y = rand() % height;
                
                // �ж��Ƿ��������غ�
                for (int i = 0; i <= snakeBody.GetUpperBound(); i++) {
                        if (t_food == snakeBody.GetAt(i)) {
                                isDup = true;
                                break;
                        }
                }
                if (!isDup) {
                        break;
                }
        }
        food = t_food;
}

/*
void CSnakeCore::setDirection(int direction) {
        CPoint head = snakeBody.GetAt(0);       // ��ȡ��ͷ
        // ��������ͷλ��
        if (direction != currentDirection && !hasChanged) {
                switch (direction) {
                case UP:
                        if (currentDirection != DOWN) {
                                head.y--;
                                hasChanged = true;
                        }
                        break;
                case DOWN:
                        if (currentDirection != UP) {
                                head.y++;
                                hasChanged = true;
                        }
                        break;
                case LEFT:
                        if (currentDirection != RIGHT) {
                                head.x--;
                                hasChanged = true;
                        }
                        break;
                case RIGHT:
                        if (currentDirection != LEFT) {
                                head.x++;
                                hasChanged = true;
                        }
                        break;
                }
        }
        if (hasChanged) {
                currentDirection = direction;
        }

       // ����ǽ��
        if (!isOver && (head.x < 0 || head.x >= width || head.y < 0 || head.y >= height)) {
                isOver = true;
        }
        // ��������
        if (!isOver) {
                for (int i = 1; i <= snakeBody.GetUpperBound(); i++) {
                        if (head == snakeBody.GetAt(i)) {
                                isOver = true;
                                break;
                        }
                }
        }

        //CSnakeView *pView = (CSnakeView*) AfxGetMainWnd();
        //pView->GetActiveView();

        if (!isOver) {
                snakeBody.InsertAt(0, head);
                CSnakeView::ReDraw(head);
                if (head != food) {
                        // ɾ����β
                        CPoint tmpPoint = snakeBody.GetAt(snakeBody.GetUpperBound());
                        snakeBody.RemoveAt(snakeBody.GetUpperBound());
                        CSnakeView::ReDraw(tmpPoint);
                }
                else {
                        score++;
                }
        }
}
*/