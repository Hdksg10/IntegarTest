#ifndef IntegerTest_HPP
#define IntegerTest_HPP
#include <random>
#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>


namespace Integar
{
class IntegarTest
{
    friend std::ostream& operator<<(std::ostream& os , const IntegarTest &It);
private:
    std::vector<double> _timeCost;
    int32_t __lo;
    int32_t __hi;
    std::mt19937 _randomEngine;
    int8_t __type;//1 = 有限个数字， 2 = int类型vector， 3 = int类型C风格数组
    int32_t __testIntegar;
    std::vector<int> __testVector;
    std::uniform_int_distribution<> __distib;
    std::vector<int> __randomIntegarSets;
    int* __testArray;
    int __randomIntegar(int lo, int high)
    {
         return __distib(_randomEngine);
    }
    void __initVector(size_t size, std::vector<int>& target)
    {
        target.clear();
        for(int i = 0; i < size; i++)
        {
            target.push_back(__randomIntegar(__lo, __hi));
        }
    }
    void __initArray(size_t size, int* target)
    {
        if(target)
            delete[] target;
        target = new int[size];
        for(int i = 0; i < size; i++)
        {
            target[i] = __randomIntegar(__lo, __hi);
        }

    }
    template<class FuncT, typename ...args>
    void __functorCall(FuncT Func, args ... arg)
    {
        Func(arg...);
    }         
public:
    IntegarTest()
    {
        _randomEngine.seed(time(nullptr));
        __testArray = nullptr;
        __lo = 1;
        __hi = 10000;
        __type = 1;
        std::uniform_int_distribution<>::param_type _params{__lo, __hi};
        __distib.param(_params);
    }

    IntegarTest(int lo, int high)
    {
        _randomEngine.seed(time(nullptr));
        __testArray = nullptr;
        __lo = lo;
        __hi = high;
        __type = 1;
        std::uniform_int_distribution<>::param_type _params{__lo, __hi};
        __distib.param(_params);
    }

    IntegarTest(int lo, int high, int type)
    {
        _randomEngine.seed(time(nullptr));
        __testArray = nullptr;
        __lo = lo;
        __hi = high;
        __type = type;
        std::uniform_int_distribution<>::param_type _params{__lo, __hi};
        __distib.param(_params);
    }
    ~IntegarTest()
    {
        if(__testArray)
            delete[] __testArray;
    }
    int getRandomIntegar(int lo, int high)
    {
        return __randomIntegar(lo, high);
    }
    template<class FunctorT>
    double singleTest(FunctorT& Func)
    {
        if(__type == 1)
        {
            __testIntegar = __randomIntegar(__lo, __hi);
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            __functorCall(Func, __testIntegar);
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            std::chrono::duration<double, std::milli> time_span = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - begin);
            return time_span.count();
        }
        else
        {
            return 0;
        }
    }
    template<class FunctorT>
    double singleTest(FunctorT& Func, size_t size)
    {
        if(__type == 2)
        {
            __initVector(size, __testVector);
            return functest(Func, __testVector);
        }
        // else if(__type == 3)
        // {
        //     __initArray(size, __testArray);
        //     return functest(Func, __testArray);
        // }
        else
        {
            return 0;
        }
    }
    template<class FunctorT>
    void multiTest(FunctorT& Func, int frequency)
    {
        for(int i = 0; i < frequency; i++)
        {
            __randomIntegarSets.push_back(__randomIntegar(__lo, __hi));
        }
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        for(int i = 0; i< frequency; i++)
        {
            __functorCall(Func, __randomIntegarSets[i]);
        }
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> time_span = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - begin);
        __randomIntegarSets.clear();
    }
    template<class FunctorT>
    void multiTest(FunctorT& Func, int minSize, int maxSize, int step)
    {
        if(__type == 2)
        {
            for(int i = minSize; i < maxSize; i = i + step)
            {
                __initVector(i, __testVector);
                std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                __functorCall(Func, __testVector);
                std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
                std::chrono::duration<double, std::milli> time_span = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - begin);
                _timeCost.push_back(time_span.count());
            }
        }
        else
        {
            return ;
        }
    }



    template<class FuncT, typename ...args>
    double functest(FuncT Func, args ... arg)
    {
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        __functorCall(Func, arg...);
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> time_span = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - begin);
        return time_span.count();
    }

};

std::ostream& operator<<(std::ostream& os , const IntegarTest &It)
    {
        for(auto time : It._timeCost)
        {
            os << time<<std::endl;
        }
        return os;
    }
}

    
#endif