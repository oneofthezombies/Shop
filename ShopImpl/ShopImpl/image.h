#pragma once

#include "commonMacroFunction.h"

class image
{
public:
	image();
	~image();
	//�� ��Ʈ�� �ʱ�ȭ
	HRESULT init(int width, int height);
	//�̹��� ���ҽ� �ʱ�ȭ
	HRESULT init(const DWORD resID, int width, int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
	//�̹��� ���� �ʱ�ȭ
	HRESULT init(const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));

    //������ �̹��� ���Ϸ� �ʱ�ȭ
    HRESULT init(const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));
    HRESULT init(const char* fileName, int x, int y, int width, int height, int frameX, int frameY, bool isTrans = false, COLORREF transColor = RGB(255, 0, 255));

	//����Ű����
	void setTransColor(bool isTrans, COLORREF transColor);
	//������
	void release();

	void render(HDC hdc);
	void render(HDC hdc, int destX, int destY);
    void render(HDC hdc, int destX, int destY, BYTE alpha);


    // ������ ����
    void frameRender(HDC hdc, int destX, int destY);
    void frameRender(HDC hdc, int destX, int destY, int currnetFrameX, int currentFrameY);
    void frameRender(HDC hdc, int destX, int destY, int currnetFrameX, int currentFrameY, BYTE alpha);

	//DC�� ���´�.
	inline HDC getMemDC() { return m_imageInfo->hMemDC;}
    
    //�̹��� ��ǥ X ���
    inline float getX() { return m_imageInfo->x; }
    inline void setX(float x) { m_imageInfo->x = x; }
    //�̹��� ��ǥ Y ���
    inline float getY() { return m_imageInfo->y; }
    inline void setY(float y) { m_imageInfo->y = y; }

    //�̹��� ���� ��ǥ ����
    inline void setCenter(float x, float y)
    {
        m_imageInfo->x = x - (m_imageInfo->width / 2);
        m_imageInfo->y = y - (m_imageInfo->height / 2);
    }

    //���� ���� ũ�� ���
    inline int getWidth() { return m_imageInfo->width; }
    inline int getHeight() { return m_imageInfo->height; }

    //�ٿ�� �ڽ�(�浹��)
    inline RECT getBoundingBox()
    {
        RECT rc = RectMakeCenter(m_imageInfo->x, m_imageInfo->y, m_imageInfo->width, m_imageInfo->height);
        return rc;
    }

    inline int getFrameX() { return m_imageInfo->currentFrameX; }
    inline void setFrameX(int frameX)
    {
        m_imageInfo->currentFrameX = frameX;
        if (frameX > m_imageInfo->maxFrameX)
        {
            m_imageInfo->currentFrameX = m_imageInfo->maxFrameX;
        }
    }

    inline int getFrameY() { return m_imageInfo->currentFrameY; }
    inline void setFrameY(int frameY)
    {
        m_imageInfo->currentFrameY = frameY;
        if (frameY > m_imageInfo->maxFrameY)
        {
            m_imageInfo->currentFrameY = m_imageInfo->maxFrameY;
        }
    }

    inline int getFrameWidth() { return m_imageInfo->frameWidth; }
    inline int getFrameHeight() { return m_imageInfo->frameHeight; }

    inline int getMaxFrameX() { return m_imageInfo->maxFrameX; }
    inline int getMaxFrameY() { return m_imageInfo->maxFrameY; }

	enum IMAGE_LOAD_KIND
	{
		LOAD_RESOURCE = 0,//���ҽ��ε�
		LOAD_FILE, //���� �ε�
		LOAD_EMPTY, // �� ��Ʈ�� ����
		LOAD_END
	};

	typedef struct tagImage
	{
		DWORD resID; //���ҽ� ID
		HDC hMemDC; //�޸� DC
		HBITMAP hBit; //��Ʈ��(���ο� ��Ʈ�� �ڵ�)
		HBITMAP hOBit; //�õ� ��Ʈ��(���� ��Ʈ�� �ڵ�)
        float x;    //�̹��� ��ǥ
        float y;
		int width; //�̹��� ����ũ��
		int height; //�̹��� ����ũ��
        int currentFrameX;  //���� ������ X
        int currentFrameY;
        int maxFrameX;  //�ִ� ������ ����
        int maxFrameY;
        int frameWidth; //1������ ���α���
        int frameHeight;
		BYTE loadType; // Ÿ��

		tagImage()
		{
			resID = 0;//�ʱ�ȭ
			hMemDC = nullptr;
			hBit = nullptr;
			hOBit = nullptr;
            x = 0;
            y = 0;
			width = 0;
			height = 0;
            currentFrameX = 0;
            currentFrameY = 0;
            maxFrameX = 0;
            maxFrameY = 0;
            frameWidth = 0;
            frameHeight = 0;
			loadType = LOAD_RESOURCE;
		}

	} IMAGE_INFO, *LPIMAGE_INFO;

    LPIMAGE_INFO m_imageInfo; //�̹�������

private:
	char* m_fileName; // �̹��� �̸�
	bool m_isTrans; //��� �����ų�?
	COLORREF m_transColor; //�������� rgb ����
};

