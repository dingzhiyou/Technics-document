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


#通常C++要求为所有的任何东西提供定义，但类专用的静态整数类型（例如int，char，bool）常量是个例外，只要不获取他们的地址，就可以在不提供定义的情况下声明并使用他们
所以类常量的初始值是在声明时指定的，在定义时不允许对其进行赋值
class A  {
public:
private:
    static const int s_size = 10;//这属于声明定义一起
    int array[s_size];//此时已经需要拿到s_size的数值了,此时不要赋值
    static vector<int> s_v;//对于静态成员来说这属于声明
};
const int A::s_size;//定义------------总的来说类内声明类外实现是没问题的，但是如果你在类内就要使用到这个变量，你就需要在类内进行实现，比如像这里
vector<int> A::s_v;//这个属于定义，在s_v是静态成员的情况下


#const在*左边或者右边的情况
const char* p = "aaaaaa";//指的是不能通过p来修改“aaaaaa”的值，但是p是可以指向其他的地方的const char* p与 char const* p中是一致的
char* greet[]="hello";
char* const p = greet;//是指p不能指向别的值，但是可以通过p来修改"hello"的值,注意char* const p = "hello"0是错误的，不允许，原因是"hello"他就是const char*类型的;

const std::vector<int>::interator iter =vec.begin();
*iter = 10; //OK
iter++;//false

std::vector<int>::const_interator iter =vec.begin();
*iter = 10; //OFF
iter++;//OK

#既然进行了整个函数的const修饰，就意味着我们不打算修改值了，所以返回你也必须返回const，否则，会报错
const char& operator[](std::size_t position) const {
  return text[position];
}
 char& operator[](std::size_t position)  {
  return text[position];
}

#operator重载到底要不要添加const ？



