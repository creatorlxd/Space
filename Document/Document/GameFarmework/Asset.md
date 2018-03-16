# Space Game Engine Document
## Space Asset 资源
### Asset&AssetManager
#### Asset
&emsp;&emsp;`Asset`是所有资源类的基类，是用来管理所有的运行时游戏资源的。使用`Asset`来管理资源，而不是简单的直接读取的好处在与：对于一个可能需要多次的读取而不能被修改的静态资源来说，使用`Asset`来管理这类资源，可以避免多次的IO开销，因为这个资源会被储存起来，以便于下次的读取。

&emsp;&emsp;`Asset`主要有以下部分：

* 构造函数:**在子类的构造函数中必须将`m_TypeName`赋值为该子类所代表的资源的名称，也可以是该子类的名称**。

* `InitFormFile(const std::string& filename)`:该方法实现从文件中读取内容的功能。注意，这个方法必须要由子类去实现，而且**在该方法中必须把`m_FileName`赋值成`函数参数filename`**。

* `m_TypeName`:储存子类资源的类别名，可以通过这个成员变量来区分不同类型的资源。所以必须要在子类的构造函数中为它赋一个**有意义的值（见Asset的构造函数）**。

* `m_FileName`:储存子类资源文件的文件名。必须在子类的`InitFromFile(const std::string& filename)`中被赋值为`filename`。

#### AssetManager
&emsp;&emsp;`AssetManager`是用来管理`Asset`子类资源对象实例的，我们并不直接地使用它。我们只需要使用`AssetManager`之外的`GetAssetByFileName<T>(const std::string& filename)`方法就可以通过文件名来获取相对应的资源了。

#### `Component`中的`Asset`资源读取
&emsp;&emsp;在`Component`子类中，我们最好使用`ReadAssetFromFile<T>(const std::string& filename)`方法来读取资源。如果该`Component`子类只需要一种资源，那么使用`ReadAssetFromFile`的好处在于，使用这个方法来读取资源,`m_pAsset`成员就会被赋值去指向这个对象，从而你就可以在其他地方得知这个`Component`子类实例读取了哪个资源，并且可以获得这个资源的文件名(`m_FileName`)。当然，如果该`Component`子类需要读取多个文件资源(`Asset`子类)，那么使用`ReadAssetFromFile`就显得没有必要了。