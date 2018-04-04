# Space Game Engine Document
---
## Space基本组件Component类

>注意：在使用Component及其子类之前，确保你已经定义了一个Game对象和Scene对象。
### 1.概述
`Component`组件类是Space游戏引擎中执行动作的基本类。  
目前已有的大部分功能（比如：网格，材质，纹理，坐标...）都是由通过继承`Component`类来实现的。

[Component类](../../../Source/GameEngine/Game/Component/Include/Component.h "Component类")

### 2.如何使用
我们只需使用每个`Component`子类的`NewComponent`方法即可获得一个`Component*`指针。当然，你不需要去释放它。

例如：

	TransformComponent* transform=TransformComponent::NewComponent();
	//use transform to do something...

然后我们可以通过调用其的`GetTypeName()`来获取其的组件类型  

或是使用`IfUSe()`和`IfRun()`来得知这个组件是否会被引擎调用或是在每帧是运行。  
当然我们也可以使用`ChangeIfRun(bool b)`和`ChangeIfUse(bool b)`来设置这些属性。

>注意：在实际运用中，我们并不是单独的使用Component，而是将其绑定到Object对象中来由引擎调用。所以就不介绍它的初始化和运行了。

### 3.如何编写自己的组件
>这个才是本文档的重点，要注意的地方很多。

你先需要写一个类去继承Component类，然后你就可以在你的类中写代码了。

然而你需要注意的是以下这些需要被重载的函数及其作用。

* `构造函数`:  
重新初始化m_TypeName为你的组件类的名称，必须重写!!!
	
* `void InitFromFile(const String& filename,int mode)`:  
用来从文件中初始化组件，如果你不需要也可以不写。
	
* `void Start()`:  
由其实例在其所在场景***开始***时所执行的操作，如果你不需要也可以不写。
	
* `void Run(float DeltaTime)`:  
由其实例在其所在场景***每帧***时所执行的操作，如果你不需要也可以不写。

* `void EveryFrameCleanUp()`:  
每帧该组件要做的清理工作。如果你不需要也可以不写。

* `void CleanUp()`:  
清理组件与外部关系的操作，不释放组件，在`Object::DeleteComponent`时被调用。如果你不需要也可以不写。但是如果你写了的话，最好在你的`Clear`函数的末尾调用`Component::Clear()`。

* `void Copy(Component* pc)`:  
负责该组件类的复制。最好做安全检查。不要忘记将`m_Mode&m_pAsset`一并复制

除此之外，你还要在你的组件类中**加入**以下成员变量。

* 公有的`static const int`类型的各种`mode`:  
用来判断组件的内部具体模式（比如网格组件中分为model文件和XMesh文件两种mode）。对应`InitFromFile(const string& filename,int mode)`的`mode`形参。

**最后，你还要在public声明中加入一行`REGISTER_COMPONENT(你的component的类名)`以构造这个子类的工厂方法(`NewComponent()`)，和一个用于动态创建的包含类名的仿函数(`GetComponentFactory()`)。**

这样你就可以构建自己的组件类了。

### 4.实例：（MeshComponent）

[MeshComponent](../../../Source/GameEngine/Graphics/Mesh/Include/Mesh.h "MeshComponent")