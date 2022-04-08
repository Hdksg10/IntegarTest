# C++函数效率测试 IntegarTest

## **开发中 STILL UNDERDEVELOPED**

## 介绍

一个测试C++函数运行时间的轮子，支持以下操作

- 测试任意函数的运行时间
- 生成指定范围的随机整数
- 生成指定长度范围的随机C风格Int类型数组，随机Int类型vector
- 测试接受整数/C风格Int类型数组，Int类型vector作为参数的函数在不同输入规模下的运行时间

## 快速使用教程

### 准备措施

要求编译器支持C++17标准，并在编译选项中添加 -std=c++17选项（不会添加？：[点我](.\complietutorial.md)）

### 添加头文件

将IntegerTest.hpp与代码文件放置在同一文件夹，在代码文件中添加

`#include "IntegerTest.hpp"`

### 正式使用

```c++
#include "IntegarTest.hpp"
#include "iostream"
using namespace std;
using namespace Integar;//所有内容包装在Integer命名空间内
void testFunction(int r, double s)//测试函数
{
    for(int i = 0; i < r; i++)
    {
        cout<<"test"<<s<<" ";
    }
    cout<<endl;
}

int main()
{
    IntegarTest It;
    cout<<It.functest(testFunction, 12, 2.67);//functest函数用于测试任意函数运行时间
}
```

functest函数为可变参数函数，第一个参数接受可调用对象(函数名、函数指针等)，之后可变个参数为第一个参数的参数，如示例中testFunction函数需要一个int类型和一个double类型参数，则在调用functest时，需在testFunction后提供一个int类型和一个double类型参数。

函数原型：

```c++ 
template<class FuncT, typename ...args> double functest(FuncT Func, args ... arg)
```

输出结果

```
test2.67 test2.67 test2.67 test2.67 test2.67 test2.67 test2.67 test2.67 test2.67 test2.67 test2.67 test2.67 
2.1965
```

## 详细介绍（施工中）
