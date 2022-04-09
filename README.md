# C++函数效率测试 IntegarTest

## **开发中 STILL UNDERDEVELOPED**

## 介绍

一个测试C++函数运行时间的轮子，支持以下操作

- 测试任意函数的运行时间
- 生成指定范围的随机整数
- 生成指定长度范围的随机~~C风格int类型数组~~，随机int类型vector
- 测试接受整数/~~C风格int类型数组~~，int类型vector作为参数的函数在不同输入规模下的运行时间

## 快速使用教程

### 准备措施

要求编译器支持**C++17**标准，并在编译选项中添加 -std=c++17选项（不会添加？：[点我](https://github.com/Hdksg10/IntegarTest/blob/main/complietutorial.md)）

### 添加头文件

将./include/IntegerTest.hpp与代码文件放置在同一文件夹，在代码文件中添加

`#include "IntegerTest.hpp"`

### 正式使用(示例代码)

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
    cout<<It.functest(testFunction, 12, 2.67);//functest函数用于测试任意函数运行时间，返回单位为毫秒的运行时间
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

### includes

- <**random**>
- <**chrono**>
- <**iosteam**>
- <**vector**>

### classes

#### IntegarTest

Constructions

```C++
IntegarTest()//默认构造函数，设置随机数范围为[1, 10000)，默认随机测试类型为有限个整数
IntegarTest(int lo, int high)//构造函数，设置随机数范围为[lo, high)，默认随机测试类型为有限个整数
IntegarTest(int lo, int high, int type)//构造函数，设置随机数范围为[lo, high)，随机测试类型为type对应（见成员变量_type的介绍)
```

Desructions

```c++
 ~IntegarTest()//析构函数，主要处理数组内存的释放
```

Member Variables

```c++
std::vector<double> _timeCost//存放多次随机调用所测的时间
int32_t _lo//随机数生成器的最小值
Int32_t _hi//随机数生成器的最大值（不含)
Int8_t _type//内置随机测试函数的测试类型1 = 有限个整数， 2 = int类型vector， 3 = int类型C风格数组，functest函数不受限制
std::vector<int> _testVector//存储用于测试的vector
Int* _testArray//用于测试的C风格数组
Int32_t _testIntegar//用于测试的随机整数
std::uniform_int_distribution<> _distib//用于生成随机整数的标准均匀分布
std::mt19937 _randomEngine//用于生成随机数的随机数生成器
```

Member Functions

```c++
Private:
int _randomIntegar(int lo, int high)// 返回[lo, hi)范围内的随机整数
void _initVector(size_t size, std::vector<int>& target)// 对Target vector随机初始化，随机初始化后大小为size
void _initArray(size_t size, int* target)//对大小为size的C风格数组target随机初始化
template<class FuncT, typename ...args>void _functionCall(FuncT Func, args...arg)//用于调用任意函数，接受一个可调用对象作为第一个参数，以及可变个其他参数，可变个其他参数作为第一个参数可调用对象Func的参数
Public：
//随机数生成
int getRandomIntegar(int lo, int high)//返回[lo, high)范围内的随机整数
//随机测试
template<class FunctorT>double singleTest(FunctorT& Func)//对只接受一个整数作为参数的仿函数Func进行单次随机调用测试，返回运行消耗时间（单位：毫秒）
template<class FunctorT>double singleTest(FunctorT& Func, size_t size)//对只接受一个整数vector作为参数的仿函数Func进行单次随机调用测试，返回运行消耗时间（单位：毫秒）
template<class FunctorT>void multiTest(FunctorT& Func, int frequency)//对只接受一个整数作为参数的仿函数Func进行多次随机调用测试，frequency为测试次数， 返回累计消耗时间（单位：毫秒）
template<class FunctorT>void multiTest(FunctorT& Func, int minSize, int maxSize, int step)//对只接受一个整数vector作为参数的仿函数Func进行多次随机调用测试，数据规模从minSize增长到maxSize(不含)，每次增加step，每次调用消耗时间存储在_timeCost中
//时间测试
template<class FuncT, typename ...args>double functest(FuncT Func, args ... arg)//用于对任意函数进行单次运行时间测试，接受一个可调用对象作为第一个参数，以及可变个其他参数，接受的可变个其他参数作为第一个参数(即可调用对象Func)的参数，返回运行时间（单位：毫秒），不受_type指定类型的限制
```

Friend Function

```c++
friend std::ostream& operator<<(std::ostream& os , const IntegarTest &It)//重载的<<运算符，将IntegerTest中_timeCost中的元素全部输出到os这个标准输出流中
```
## 其他

大一学生C++作品，欢迎任何建议与批评

欢迎Issues/Pull Requests
