教程：如何在VSCode + Code Runner下修改编译选项

左上角File->Preference->Settings

在上分搜索栏中搜索 Executor Map

![image-20220408133423503](https://github.com/Hdksg10/IntegarTest/blob/main/image/image-20220408133423503.png)

点击Edit in settings.json

在打开的文件中找到code-runner.executorMap

在"cpp"中添加 -std=c++17(如下图)

![image-20220408133626121](https://github.com/Hdksg10/IntegarTest/blob/main/image/image-20220408133626121.png)