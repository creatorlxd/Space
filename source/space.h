#pragma once
#include<d3d9.h>
#include<string>

enum thingskind //��Ʒ����
{
	
	oil = 1,	//ȼ��
	stone = 2	//����
};

struct thing	//��Ʒ
{
	wchar_t name[10];//����
	wchar_t describe[20];//����
};

enum paoskind	//�ڵ�����
{
	t1 = 1		//T-1ʵ����
};
class pao		//����
{
public:
	pao(std::string inname);
	int hpc(int &inint);//�ı�HPֵ,�����ϸı�ֵinint��
	int gjout();		//��ʱ���������������Ҫ�������Ϊʹ��gjmax��gjmin����������ɺ���������һ������gjmax��gjmin֮����������ֵ��

private:
	paoskind pk;	//�ڵ�����
	int hp;		//Ѫ��
	int gj;		//����ֵ�����ã�����Ӧʹ������������棡����
	std::string name;//�ڵ��ͺ�

};

enum pusherskind	//�ƽ�������
{
	p1=1,			//�ͺ�P-1
	p2=2			//�ͺ�P-2
};

class pusher		//�ƽ�����
{
public:
	pusher(std::string inname);
	~pusher();
	int hpc(int &inint);//�ı�HPֵ,�����ϸı�ֵinint��
	int nout();			//��ʱ���ǣ������ֵ
private:
	pusherskind prk;	//�ƽ������ͺ�
	int hp;				//Ѫ��
	int n;				//�ƽ�����ǣ����
	std::string name;	//�ƽ���������

};

