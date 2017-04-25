#pragma once
#include "stdafx.h"
#include "Space.h"

class Component							//组件：用于继承的基类
{
public:
	Component();
	~Component();
	std::string GetTypeName();			//获取类型名
	virtual void InitFromFile(std::string filename, int mode=0);
	virtual void Start();			//在开始时执行
	virtual void Run(float DeltaTime);//每帧运行时的操作
	virtual void Attach(Component* pc);	//成为...组件的依附
	virtual void Release();				//释放
	bool IfRun();						//是否每帧运行
	bool IfUse();						//是否使用
	void ChangeIfRun(bool b);			//更改每帧是否运行
	void ChangeIfUse(bool b);			//更改是否使用
protected:
	std::string m_TypeName;				//组件的类型名
	bool m_IfRun;						//是否每帧运行
	bool m_IfUse;						//是否使用
	std::vector<Component*> m_pChilds;	//子组件
};