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
    static const int s_size = 10;//这属于声明定义一起，为什么这里可以复制，也就是定义，因为这里是const才行（编译其就需要确定其值---常量），一般情况是不行的
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

#C++默认使用位常量，只要对象成员变量每一位都不发生变化，就符合const规则。由于static变量是在全局区，他在const修饰的函数中是可以改变的，逻辑常量要求函数指针所指向的内容也不能发送改变
所以当一个成员函数不是对象而是指针的时候，你返回的时候是可以返回的比如说这个函数char* text,这种方式是可以在外面修改text[position]的值的;
char& operator()(int position) const {
  return text[position];
}

#当你需要在一个const函数中，修改一些成员变量的值（非指针类型）,那么你就要将它从位常量中释放出来，可以在成员函数定义前加上mutable变量

#一个const对象只能调用const成员函数，当然静态函数是肯定可以的，但是记住，当我们要用一个版本调用另一个版本的时候，减少代码的冗余，那么我们可以使用非const版本调用const，那么
什么情况下也就是在什么内容下非const可以区分你里面调用的版本是const的呢，而不是非const版本的，这取决于你这个对象是不是const类型的，如果是对象const类型的，那么他就只能调用const类型
如果对象是非const类型的，那么就可以把对象转换为const类型，然后再去调用就是使用的const类型的成员函数。视频讲解放在下方了
#无论是const类型还是引用类型都必须在声明时初始好值
#如果一个类既有const函数，又有非const(并且二者是重载关系)，那么你的类是常量对象，则默认调用const函数，如果非常量对象则调用非const函数

```
https://www.bilibili.com/video/BV1QX4y1W7Ya?p=7&spm_id_from=pageDriver&vd_source=46bc0c757bab35efd01eb1756857f6b1
```


#初始化顺序
对于C部分（比如数组，int类型等等），编译器不一定对其进行初始化操作，而对于非C部分（STL容器等等），一般会对其进行初始化操作(注意不要混淆初始化和赋值操作，初始化操作一般发生在构造函数之前，调用其默认构造函数实现，而赋值操作一般全部在构造函数中进行)
注意这里区分使用初始化参数列表的方式和在构造函数赋值的方式，有较大区别，使用初始化参数列表方式意味着我们不会进行在构造函数之前的初始化，而是告诉编译器直接调用其拷贝构造函数（不是赋值函数）进行初始化
    A(const B& b):m_b(b) {
    }
    A(const B& b){
        m_b = b;
    }
  B m_b;
两者有区别，第一种是拷贝构造函数进行构造，不会进行构造函数前的初始化构造，第二种则是赋值构造函数，他会调用之前的初始化构造函数

#手动初始化内置类型的对象，因为C++不确保会初始化他们
#在构造函数中，优先使用成员初始化列表（以类中声明的顺序），而不是在构造函数中赋值，
#通过将非局部静态对象（其实也就是全局对象，普通全局对象的初始化顺序是不确定的，当一个全局对象使用到另一个全局对象时，不能确保他已经构造好了）替换为局部静态对象（一个函数中的静态成员变量，并将其返回这种方式取对象，一般也把这个函数写为一个类的静态成员函数），避免跨编译单元初始化的问题
```
https://www.bilibili.com/video/BV1QX4y1W7Ya?p=8&vd_source=46bc0c757bab35efd01eb1756857f6b1
```

#一个空类，编译器默认（需要用到时才会）会为你生成四个函数，默认构造函数，拷贝构造函数，析构函数，拷贝赋值运算符(如果成员变量出现了常量或者引用类型则无法生成会报错的)

#如果要实现不允许拷贝，最好的办法就是创建一个基类，将他的拷贝构造，赋值构造写成私有类型即可，或者直接将它 = delete也行

#如果是父类没有写成虚析构函数，那么父类指针指向子类对象进行delete时就只会析构父类，而不会析构子类。但是注意如果你本身delete的就是子类的指针，那么他是会全部析构的
写上虚析构函数之后，通过父类指针进行delete也会得到正确的结果，通过子类指针进行肯定也是完全没问题的
#operator重载到底要不要添加const ？



