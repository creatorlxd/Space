#pragma once
#include<d3d9.h>
#include<string>

enum thingskind //物品种类
{
	
	oil = 1,	//燃料
	stone = 2	//矿物
};

struct thing	//物品
{
	wchar_t name[10];//名字
	wchar_t describe[20];//描述
};

enum paoskind	//炮的类型
{
	t1 = 1		//T-1实验型
};
class pao		//炮塔
{
public:
	pao(std::string inname);
	int hpc(int &inint);//改变HP值,即加上改变值inint。
	int gjout();		//暂时输出攻击力，后期要将其改造为使用gjmax和gjmin的随机数生成函数来生成一个介于gjmax与gjmin之间的随机攻击值。

private:
	paoskind pk;	//炮的类型
	int hp;		//血量
	int gj;		//攻击值（暂用），后应使用随机数来代替！！！
	std::string name;//炮的型号

};

enum pusherskind	//推进器类型
{
	p1=1,			//型号P-1
	p2=2			//型号P-2
};

class pusher		//推进器类
{
public:
	pusher(std::string inname);
	~pusher();
	int hpc(int &inint);//改变HP值,即加上改变值inint。
	int nout();			//暂时输出牵引力的值
private:
	pusherskind prk;	//推进器的型号
	int hp;				//血量
	int n;				//推进器的牵引力
	std::string name;	//推进器的名字

};

