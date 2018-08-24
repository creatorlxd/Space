# SpaceGameEngineReference
## Config File

### `enum class ConfigFileValueType` 配置文件值的类型:
* `Int`
* `Float`
* `Double`
* `Char`
* `String`
* `Bool`

### `struct ConfigFileValue` 配置文件中键值对的值:

* Public Member Function:
	* `int AsInt();`
	* `float AsFloat();`
	* `double AsDouble();`
	* `char AsChar();`
	* `String AsString();`
	* `bool AsBool();`
	* `void Set(int i);`
	* `void Set(float f);`
	* `void Set(double d);`
	* `void Set(char c);`
	* `void Set(const String& str);`
	* `void Set(bool b);`
* Public Member Variable:
	* `ConfigFileValueType m_Type;`
	* `String m_Content;`