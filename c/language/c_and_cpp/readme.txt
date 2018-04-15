本例子用来测试混合C语音以及C++语言的程序
1. a.cpp调用了c.c里面的函数
2. b.cpp调用了c.c里面的函数
3. c.c调用了b.cpp里面的函数

编译命令：
gcc -c a.cpp && gcc -c c.c && g++ -c b.cpp && g++ -o a.out a.o b.o c.o
