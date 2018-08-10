# SpaceGameEngineDocument
## Config File 配置文件

### Config File Value 配置文件值类型
&emsp;&emsp;配置文件值类型是用来储存配置文件中的值（非键部份）的。它支持`int,float,double,char,string,bool`这几种类型。在`SpaceGameEngine`中，使用`ConfigValue`来储存内容，通过`ConfigValueType`来标记类型。可以使用`void Set(...)`来设置**与实际类型相一致**的值，使用`XXX GetXXX()`来获取**与实际类型相一致**的值。

### Config Table 配置表
&emsp;&emsp;一个配置文件中可以有多个配置表。每个配置表在配置文件中以`[配置表名]`为起始，接下来的所有配置的内容（键值对）都被认定为在这个表中。可以使用`bool IfHaveConfigValue(const String& name)`来判断表中是否有某个键，使用`ConfigValue& GetConfigValue(const String& name)`来获取表中的某个键值对的值。

### Config File 配置文件
&emsp;&emsp;配置文件类(`class ConfigFile`)是用来从文件或是字符串中读取配置或是保存配置到文件中的。可以使用`void InitFromFile(const String& filename)`从文件中读取配置，使用`void Parse(const String& str)`从字符串中读取配置；使用`void SaveToFile(const String& filename)`将其中的配置保存到文件中；与`ConfigTable`类似的是，可以使用`bool IfHaveConfigTable(const String& name)`来判断配置文件中是否有某个配置表，也可以使用`ConfigTable& GetConfigTable(const String& name)`来获取某个配置表。

### 配置文件示例

以`;`开头的是注释

```
;config file example
[test] ;config table start
a=1 ;config value
b=2
[test2] ;another config table
c="test"
```