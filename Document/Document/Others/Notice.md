# Space Game Engine Document

## 使用时的注意事项

1. 在运行时创建的`Component`/`Object`，在完成一系列的初始化的操作后，要手动调用`Start`方法。
2. 使用全局的常量时，如果是定义在头文件中请使用`GLOBALCONST`代替`const`。
3. 使用全局变量时，请使用`local static`加上`GlobalVariable<T>`来管理全局变量，以保证其构造和析构的顺序的正确。