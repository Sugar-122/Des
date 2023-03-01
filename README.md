# Des算法的C++实现
编译：g++ -o main main.cpp Block.cpp Block.h des.h

用法为：./main -选项 input.txt output.txt 密钥（8字节）
选项:可以是e(加密），d(解密）
input.txt为输入文件，output.txt为输出文件
对于数据最后不足8字节的情况，会出现问题
主要是考虑如果不足八位，势必要填充，如果填充，填充什么，填充之后我如何判断数据末尾是它本身的数据还是填充的数据，暂鸽......
