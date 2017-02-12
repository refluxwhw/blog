# C++ 知识点

## const
- 对于指针：
 - 如果const位于星号的左侧，则const就是用来修饰指针所指向的变量，即指针指向为常量；
 - 如果const位于星号的右侧，const就是修饰指针本身，即指针本身是常量
 -
- 对于函数：
 - 修饰参数，表示参数在函数中不可修改 `void Add(const double &a, const double& b);`
 - 修饰返回值，表示返回的对象有const属性，`const A& getA();`
 - 修饰类的成员函数，表示该函数不会对类的成员进行修改；`void fun() const;`


# END 
