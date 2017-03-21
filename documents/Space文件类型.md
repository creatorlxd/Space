#Space Game Engine Helper
---
##Space文件类型
>注：所有文件的后缀名自拟

>注：该处的RGB颜色值均是形如 R G B 1 的四维向量

###1.模型文件
格式：

	顶点数
	索引数
	顶点信息(x,y,z,nx,ny,nz,uv)
	...
	索引信息
	...
用途：可以用来储存模型。用`Object::InitFromFile`或`Object::InitFromFileEx`来读取。

----------
###2.材质文件
格式：

	反射环境光的颜色值
	漫反射的颜色值
    镜面反射的颜色值
	自发光的颜色值
    镜面反射指数
>注：以上的数值需介于0.00f~1.00f之间

用途：用来储存材质。用`Object::InitFromFile`，`Object::InitFromFileEx`或`InitMaterialFromFile`来读取。

---
###3.光源文件
格式：

	光源的漫反射颜色值
    光源的镜面反射颜色值
    光源的环境光颜色值
    光源的位置（相对位置）
	光源的光照方向
	光源的光照范围
    光源的光亮强度的衰减系数0
	光源的光亮强度的衰减系数1
	光源的光亮强度的衰减系数2
	聚光灯光源的内光锥的外侧的光亮强度向外光锥的内侧衰减的方式，通常设为1.0f使光亮强度在两个光锥间平滑地过渡
	聚光灯光源的光锥的内核弧度
	聚光灯光源的光锥的外核弧度
>注：
>
>1.以上的数值需介于0.00f~1.00f之间
>
>2.如果不是聚光灯，后三个数据随便填

用途：用来储存光源。

* 用`Light::SetPointLightFromFile`来读取并设置点光源
* 用`Light::SetDirectionalLightFromFile`来读取并设置方向光源
* 用`Light::SetSpotLightFromFile`来读取并设置聚光灯

---
###4.光源引导文件
格式：

	光源文件名
	光源类型：
	{
		0:点光源
		1:方向光源
		3:聚光灯	
	}
	光源在物体中的相对位置(x,y,z)
>此文件需同光源文件一同使用

用途：用来供模型储存光源。用`Object::InitWithLightFromFile`读取。

---
###5.纹理引导文件
格式：

	需要过滤掉的RGB颜色

>此文件需同纹理图像一同使用

用途：用来储存需要过滤掉的纹理颜色值。使用`Object::InitFromFileEx`或直接使用`SetTextureFromFileEx`。