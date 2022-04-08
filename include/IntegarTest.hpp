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
    int32_t _lo;
    int32_t _hi;
    std::mt19937 _randomEngine;
    int8_t _type;//1 = 有限个数字， 2 = int类型vector， 3 = int类型C风格数组
    int32_t _testIntegar;
    std::vector<int> _testVector;
    std::uniform_int_distribution<> _distib;
    std::vector<int> _randomIntegarSets;
    int* _testArray;
    int _randomIntegar(int lo, int high)
    {
         return _distib(_randomEngine);
    }
    void _initVector(size_t size, std::vector<int>& target)
    {
        target.clear();
        for(int i = 0; i < size; i++)
        {
            target.push_back(_randomIntegar(_lo, _hi));
        }
    }
    void _initArray(size_t size, int* target)
    {
        if(target)
            delete[] target;
        target = new int[size];
        for(int i = 0; i < size; i++)
        {
            target[i] = _randomIntegar(_lo, _hi);
        }

    }
    template<class FuncT, typename ...args>
    void _functorCall(FuncT Func, args ... arg)
    {
        Func(arg...);
    }         
public:
    IntegarTest()
    {
        _randomEngine.seed(time(nullptr));
        _testArray = nullptr;
        _lo = 1;
        _hi = 10000;
        _type = 1;
        std::uniform_int_distribution<>::param_type _params{_lo, _hi};
        _distib.param(_params);
    }

    IntegarTest(int lo, int high)
    {
        _randomEngine.seed(time(nullptr));
        _testArray = nullptr;
        _lo = lo;
        _hi = high;
        _type = 1;
        std::uniform_int_distribution<>::param_type _params{_lo, _hi};
        _distib.param(_params);
    }

    IntegarTest(int lo, int high, int type)
    {
        _randomEngine.seed(time(nullptr));
        _testArray = nullptr;
        _lo = lo;
        _hi = high;
        _type = type;
        std::uniform_int_distribution<>::param_type _params{_lo, _hi};
        _distib.param(_params);
    }
    ~IntegarTest()
    {
        if(_testArray)
            delete[] _testArray;
    }
    int getRandomIntegar(int lo, int high)
    {
        return _randomIntegar(lo, high);
    }
    template<class FunctorT>
    double singleTest(FunctorT& Func)
    {
        if(_type == 1)
        {
            _testIntegar = _randomIntegar(_lo, _hi);
            std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
            _functorCall(Func, _testIntegar);
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
        if(_type == 2)
        {
            _initVector(size, _testVector);
            return functest(Func, _testVector);
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
    double multiTest(FunctorT& Func, int frequency)
    {
        for(int i = 0; i < frequency; i++)
        {
            _randomIntegarSets.push_back(_randomIntegar(_lo, _hi));
        }
        std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
        for(int i = 0; i< frequency; i++)
        {
            _functorCall(Func, _randomIntegarSets[i]);
        }
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::chrono::duration<double, std::milli> time_span = std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(end - begin);
        _randomIntegarSets.clear();
        return time_span.count();
    }
    template<class FunctorT>
    void multiTest(FunctorT& Func, int minSize, int maxSize, int step)
    {
        if(_type == 2)
        {
            for(int i = minSize; i < maxSize; i = i + step)
            {
                _initVector(i, _testVector);
                std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
                _functorCall(Func, _testVector);
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
        _functorCall(Func, arg...);
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