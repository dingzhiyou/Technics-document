# cout
当cout输入了nullptr字段（0x0）,之后就无法在显示其他内容了char*是不行的，但是int*可以
char* str = nullptr;
cout<<"str:"<<str<<endl;
cout<<"str1111:"<<endl;
cout<<"str2222:"<<endl;
cout.flush();
后面的内容都不会输出
