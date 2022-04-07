# 配置VS测试工程

## 正常建立CMake目录

![image-20220401151521215](https://s2.loli.net/2022/04/01/hmS4LATzOoPvBZD.png)

正常至少包含一个CMakeList.txt，一个程序入口的cpp文件，使用VS打开目录

## 生成CMakePresets.json与调试用的Launch.vs.json

1. CMakePresets.json

    ![image-20220401151800391](https://s2.loli.net/2022/04/01/yVLvaoiNCOedGks.png)

    右键CMakeList.txt点击Edit Cmake Presets for xxx，编辑预设的cmake项目属性，添加environment/projectDir为sourceDir。设置CMake变量：CMake_PREFIX_PATH为引擎库导出路径。![image-20220401152420084](https://s2.loli.net/2022/04/01/UzfFnK9iMQNbGXk.png)

2. launch.vs.json

    ![image-20220401152649187](https://s2.loli.net/2022/04/01/Z3rqtKe8UaYH2JC.png)![image-20220401152857608](https://s2.loli.net/2022/04/01/A53mbCexNwifrXI.png)

    点击Debug菜单，点击Debug And Launch Setting for xxx生成并打开launch.vs.json，往里面添加程序运行参数，目前-DataPath是必须的，表示引擎访问数据的根目录，projectDir是上面CMakePresets.json中定义的环境变量。