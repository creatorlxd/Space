# Space Game Engine Document
---
## Space文件类型
>注：所有文件的后缀名自拟

>注：该处的RGB颜色值均是形如 R G B 1 的四维向量

### 1.模型文件
格式：

	顶点数
	索引数
	顶点信息(x,y,z,nx,ny,nz,uv)
	...
	索引信息
	...
用途：可以用来储存模型。用`MeshComponent::InitFromFile(filename,ModelFileMode)`来读取。

----------
### 2.材质文件
格式：

	反射环境光的颜色值
	漫反射的颜色值
    镜面反射的颜色值(w是镜面反射的系数)
    自发光的颜色值

>注：以上的数值需介于0.00f~1.00f之间

用途：用来储存材质。用`MaterialComponent::InitFromFile(filename,SingleMode)`来读取。

---
### 3.光源文件
格式：

	光源的环境光颜色值
	光源的漫反射颜色值
    光源的镜面反射颜色值
    光源的位置（实际上没有用，因为由`TransfromComponent`决定）
	光源的光照范围
	光源的光照方向（实际上没有用，因为由`TransfromComponent`决定）
	聚光灯的参数（参见Phong光照模型）
    光源的光亮强度的衰减系数0
	光源的光亮强度的衰减系数1
	光源的光亮强度的衰减系数2
	光源类型（1：方向光；2：点光源；3：聚光灯）
>注：  
>1.以上的数值需介于0.00f~1.00f之间  
>2.如果不是聚光灯，后三个数据随便填  
>3.镜面反射的w是镜面反射的系数（参见Phong光照模型）

用途：用来储存光源。

* 用`LightComponent::InitFromFile(filename,mode)`来读取光源
>mode是StaticMode/DynamicMode中的一个，参见光源相关文档。
