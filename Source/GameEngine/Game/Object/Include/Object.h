#pragma once 
#include "stdafx.h"
#include "Game/Component/Include/ComponentManager.h"

class Object			//基本物体对象
{
public:
	Object();
	~Object();
	Component* GetComponent(const std::string& name);		//获取组件的指针
	bool AddComponent(Component* pc);						//添加组件，并不连接
	bool DeleteComponent(const std::string& name);			//删除组件，并去除连接

	void Start();											//开始时运行
	void InitFromFile(std::vector<std::pair<std::string, std::string> > filenames);	//从文件初始化
	void InitFromFile(const std::string& filename);										//通过资产文件列表来初始化
	void Run(float DeltaTime);								//每帧运行时的操作
	void Release();											//手动释放

	bool SetRootComponent(const std::string& name);			//设置根组件
	Component* GetRootComponent();							//获取根组件

	bool IfRun();						//是否每帧运行
	bool IfUse();						//是否使用
	void ChangeIfRun(bool b);			//更改每帧是否运行
	void ChangeIfUse(bool b);			//更改是否使用
protected:
	std::map<std::string, Component*> m_Components;			//组件们...
	Component* m_pRootComponent;							//根组件
	
	bool m_IfUse;											//是否使用
	bool m_IfRun;											//是否每帧运行
};

void RunComponentOnTree(Component* node,float DeltaTime);	//在树上运行组件(DFS)