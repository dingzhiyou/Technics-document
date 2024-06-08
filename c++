# cout
当cout输入了nullptr字段（0x0）,之后就无法在显示其他内容了char*是不行的，但是int*可以
char* str = nullptr;
cout<<"str:"<<str<<endl;
cout<<"str1111:"<<endl;
cout<<"str2222:"<<endl;
cout.flush();
后面的内容都不会输出


#菱形基础容易导致的二义性，数据冗余 可以通过虚继承的方式来解决
                                          A
                   B1(: virtual public A)   B2(: virtual public A)      
                                  C(public B1,public B2

#仿函数 当一个类重写了operator()方法后，他的函数对象可以称为仿函数，也就说你调用auto func = A(args)先调用其构造函数，使用func(参数)就可以调用其重载的operator方法

#labmda表达式  [需要捕获的外部变量 &表示引用方式，否则是值的方式](传入参数)可选 mutable -->返回值{}

#C++可变参数模版
// Args是一个模板参数包，args是一个函数形参参数包
// 声明一个参数包Args...args，这个参数包中可以包含0到任意个模板参数。
template <class ...Args>
void ShowList(Args... args)
{
  _ShowList(args...); //如何传参   
}


#include <iostream>
// 如何打印参数
// 递归终止条件：当没有参数时，停止递归，相当于一个模版特化.
void printArgs() {}

// 递归函数模板，用于遍历可变参数并打印它们的值
template<typename T, typename... Args>
void printArgs(T first, Args... args) {
    std::cout << first << std::endl;  // 打印第一个参数的值
    printArgs(args...);  // 递归调用，打印剩余参数的值
}

int main() {
    printArgs(1, "Hello", 3.14, 'a');  // 调用 printArgs 函数，传入多个参数
    return 0;
}

#父子类之间的智能指针转换函数 std::dynamic_pointer_cast<Derived>(basePtr);会进行检测，如果转换成功那么返回值可用
#重载bool，方便使用
operator bool() const {
        return isNonEmpty;
}

#operator重载到底要不要添加const ？



