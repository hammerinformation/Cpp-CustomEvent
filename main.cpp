#include <vector>
#include <tuple>
#include <iostream>

template <class Class, class ReturnType, typename ...Args>
class HIEvent
{
private:
    std::vector<ReturnType(Class::*)(Args ...)> functionList;
    Class* myClass;
    std::tuple<Args...> types;
public:
    explicit HIEvent(Class* T): myClass(T)
    {
    }

    void add(ReturnType (Class::*f)(Args ...))
    {
        functionList.emplace_back(f);
    }

    void invoke(Args ... args)
    {
        for (int i = 0; i < functionList.size(); ++i)
        {
            (myClass->*functionList[i])((args)...);
        }
    }

    void clear()
    {
        functionList.clear();
    }
};

class Math
{
public:
    void addition(int x, int y)
    {
        std::cout << "result:" << x + y << "\n";
    }

    void multiplication(int x, int y)
    {
        std::cout << "result:" << x * y << "\n";
    }
};

int main()
{
    Math* math = new Math;
    HIEvent<Math, void, int, int> myEvent(math);
    myEvent.add(&Math::addition);
    myEvent.add(&Math::multiplication);
    myEvent.invoke(4, 5);

    return 0;
}
