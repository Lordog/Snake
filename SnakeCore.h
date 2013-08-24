// SnakeCore.h: interface for the SnakeCore class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNAKECORE_H__6A455F74_A37A_4C64_830E_BBB6CEA71F8B__INCLUDED_)
#define AFX_SNAKECORE_H__6A455F74_A37A_4C64_830E_BBB6CEA71F8B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "afxtempl.h"

// ��������
const int UP = 1;
const int DOWN = 2;
const int LEFT = 3;
const int RIGHT = 4;

class CSnakeCore  
{
public:
        // ��Ϸ����
        int x, y;               // ���Ͻ�����
        int width, height;      // ��Ⱥ͸߶ȣ���λΪ����
        int pixel;              // ÿ�����������

        // �������ȼ�
        int score;
        int level;
        
        bool isPause;
        bool isOver;            // ��Ϸ�Ƿ����

        // ��ǰ�ƶ�����
        int currentDirection;
        bool hasChanged;        // ��һ���������ߵķ���ֻ�ܸı�һ��

        // ����
        CArray<CPoint, CPoint> snakeBody;
        // ʳ��
        CPoint food;

        // ��������Ч
        BOOL hasMusic;
        BOOL hasSound;

public:
	CSnakeCore();
	virtual ~CSnakeCore();

public:
        // ��ʼ��
        void initSnake();
        // ����ʳ��
        void createFood();
};

#endif // !defined(AFX_SNAKECORE_H__6A455F74_A37A_4C64_830E_BBB6CEA71F8B__INCLUDED_)
