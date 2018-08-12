#pragma once

//�̱��� ->�߿���. �ݵ�� �˾ƾ� �Ұ�. �����ض�.��
/*
	�̵��� ������ ����ƽ ����� �ϳ��� �ν��Ͻ��� ������.
	���α׷� �ȿ��� ���������� ������ �Ǹ�, ���� Ŭ������ �ν��Ͻ��� �ϳ��� �����ϰ���
	�Ҷ� �����.

	���������� �̿��ص� �ϳ��� �ν��Ͻ��� �����Ҽ� ������ �̱��� ������ ����ϸ�
	Ŭ���� �ڽ��� �ڱ��� ������ �ν��Ͻ��� �����ϴ� ����� ĸ��ȭ �Ͽ� ���� �Ҽ� ����.
	���, ��ü ����, ��ü �Ҹ�, �ν��Ͻ��� ���� ������ Ȱ�뿡 ������.

	�� ���� ����� �ڱ� �����ΰ� �ڱ��� ������ �ν��Ͻ��� �����ϴ� ����� ��ü������ �����ϴ� �����.
	�� �̱��� ���̽��� �ٸ� �ν��Ͻ��� �������� �ʵ��� ó���Ҽ� �ְ� ���� ������� ������ �Ѽ� ����.

*/
template <typename T>
class singletonBase
{
protected:
	//�̱��� �ν��Ͻ� ����
	static T* singleton;

	singletonBase() {};
	~singletonBase() {};

public:
	//�̱��� ��ü ��������
	static T* getSingleton();
	void releaseSingleton();
};
//�̱��� �ν��Ͻ�����
template <typename T>
T* singletonBase<T>::singleton = nullptr;

//�̱��� ��ü ��������
template <typename T>
T* singletonBase<T>::getSingleton()
{//�̱��� ��ü�� ������ ���� ������
	if ( !singleton )singleton = new T;

	return singleton;
}
template <typename T>
void singletonBase<T>::releaseSingleton()
{
	//�̱��� ��ü�� �ִٸ� �޸𸮿��� ��������.
	if ( singleton )
	{
		delete singleton;
		singleton = nullptr;
	}
}
