# Space Game Engine[![Build State](https://ci.appveyor.com/api/projects/status/wgm69qg9437how6q?svg=true)](https://ci.appveyor.com/project/creatorlxd/space)

## Space 是一个3D的游戏引擎

其开发者目前主要是 creatorlxd

基于DirectX 11.0图形库

# 安装

1. git clone
2. 打开`Space.sln`文件
3. 选择解决方案配置为`BuildDebug`&`BuildRelease`（建议使用VS的解决方案批生成），生成x86&x64的静态库(Rlease)
4. 运行`build_lib.bat`脚本
5. 将生成的`build`文件夹中的所有内容复制到你的项目中。
6. 配置头文件包含和静态库链接(注意要把`ThirdParty`文件夹加入链接附加目录)
7. 将`SystemConfig.configfile`文件挪到你的项目（不是解决方案）的根目录中
8. 修改`SystemConfig.configfile`文件中的某些文件目录（根据你复制的头文件的位置） 

# 生成文档

使用`doxygen`来生成在`./Document/Reference/`下的参考文档。

# 注意

目前的引擎只做了整体的重构，已移动到[新的位置](https://github.com/SpaceGameEngine/SpaceGameEngine)