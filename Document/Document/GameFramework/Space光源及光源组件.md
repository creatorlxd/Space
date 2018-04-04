# Space Game Engine Document
---
## Space光源及光源组件

### Space光源

#### Light
&emsp;&emsp;Space中的光源目前采用的是**Phong光照模型**。单个光源不论其类型都采用统一的`Light`结构体去储存其数据。这个`Light`结构体只储存光源的数据而不记录光源的状态等信息。

```
struct Light
{
	Light();

	XMFLOAT4 m_Ambient;			//环境光
	XMFLOAT4 m_Diffuse;			//漫反射光
	XMFLOAT4 m_Specular;		//镜面反射光

	XMFLOAT3 m_Position;
	float m_Range;

	XMFLOAT3 m_Direction;		//方向光和聚光灯所特有的光的方向
	float m_SpotLightOption;	//聚光灯的参数

	XMFLOAT3 m_LightOption;		//光源的基本的三个参数:a0,a1,a2-->a0+a1*d+a2*d^2
	LightType m_Type;			//光源的类型
};
```
> 注：镜面反射光的w值是镜面反射的参数

#### LightType
&emsp;&emsp;其中`LightType`的定义如下：
```
enum LightType :uint32_t
{
	UnkownLight = 0,
	DirectionLight = 1,
	PointLight = 2,
	SpotLight = 3
};
```

#### LightEx
&emsp;&emsp;而对于实际的使用中，我们用`LightEx`对`Light`进行了进一步的封装。使其可以表明一个光源的开关状态以及其在管理器中的模式（`LightMode` 分为`Normal`/`Dynamic`两种）。

```
struct LightEx			//基本的光源单位
{
	enum class LightMode
	{
		Normal=0,
		Dynamic=1		//often on/off or move
	};

	LightEx();
	LightMode m_Mode;
	bool m_IfOn;		//光源的开启状态
	Light m_Content;
};
```

#### LightManager
&emsp;&emsp;`LightManager`光源管理器是通过储存`LightEx`指针，来判断当前需要渲染哪些光源（因为是传统的ForwardRendering,所以不直接支持多光源，只能采取这种形式）。在每次渲染时，其的`GetLight`函数都会被调用，从而得到当前所需要的光源。在这些光源中，方向光优先，动态光源（即光源模式为`Dynamic`的）其次，最后是普通的光源（光源模式为`Normal
`）。再次过程中，一旦光源数超过最大光源数（目前为8），函数就会返回。

&emsp;&emsp;其中，`LightEx`的模式（`m_Mode`）分为`Normal`和`Dynamic`两种。

* `Normal`多是指那些静态或很少移动的光源。`LightManager`会把这些光源放在一个八叉树（`Octree`）中进行管理，所以移动它们是十分麻烦（慢）的。

*  `Dynamic`是指那些经常移动的光源。这类光源不会被插入八叉树中，而是会放入一个线性表中，所以过多的动态光源对效率是有影响的。

**注：如果使用Normal模式，需至少两个Normal光源。不然没法自动给八叉树建树**

### Space光源组件:`LightComponent`

&emsp;&emsp;光源组件是对`LightEx`的再封装，且能自动地将其所包含的`LightEx`插入其所在场景的`LightManager`中，同时还能在组件释放时将其从其所在场景中的`LightManager`删除。

&emsp;&emsp;其组件模式分为`StaticMode`和`DynamicMode`两种，对应着`LightEx`的`Normal`和`Dynamic`模式。
