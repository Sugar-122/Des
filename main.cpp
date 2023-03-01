#include <cstring>
#include <string>
#include <cstdlib>
#include "Block.h"
using namespace std;
const int num = 88 ;

// data_64-->string
void StrFromData_64(char * str , const Data_64 & data_64)
{
    //将8个字节全部置0
	memset(str , 0 , 8); 
	for(size_t i = 0 ; i < data_64.size() ; ++i)
	{
        //第i位为1
		if(true == data_64[i])
			*((unsigned char *)(str) + i / 8) |= (1 << (7 - i % 8)) ;
	}
}

// string-->data_64
void Data_64FromStr(Data_64 & data_64 , const char * str)
{
	for(size_t i = 0 ; i < data_64.size() ; ++i)
	{
		if(0 != (*((unsigned char *)(str) + i / 8) & (1 << (7 - i % 8))))
			data_64[i] = true ;
		else 	data_64[i] = false ;
	}	
}

int main(int argc , char * argv[]){
    
    //输入示例：./main -e inputfile outputfile initial_key 加密
    //         ./main -d inputfile outputfile initial_key 解密
    if(argc < 2 || argv[1][0] != '-')
        std::cout<<"Command Args Error"<<std::endl;
    
    //密钥不足8位
    if(argc < 5 || strlen(argv[4]) < 8)
		std::cout<<"Command Args Error"<<std::endl;

    Method method;//加密还是解密
    switch(argv[1][1])
	{
		case 'e'://加密
			method = e ;
			break ;
		case 'd'://加密
			method = d ;
			break ;
		default:
			std::cout<<"Command Args Error"<<std::endl;
			break ;
	}
    ifstream inputFile(argv[2]) ;//输入文件
	ofstream outputFile(argv[3]) ;//输出文件

    if(!inputFile || !outputFile) 
        std::cout<<"File Open Error"<<std::endl;//文件打开失败


    
	// char keyword[8];
	// StrFromData_64(keyword,b.initial_key);
	// cout<<keyword<<endl;
    char buffer[8] ;
    while(1)
	{
		Block b;
		Data_64FromStr(b.initial_key , argv[4]) ;//获取密钥
		memset(buffer , 0 , 8) ;//将8个字节置0
		inputFile.read(buffer , 8) ;//从源中读取数据
		
        if(inputFile.eof()) 
            break ;
		Data_64FromStr(b.block , buffer) ;//构建数据块
		// std::cout<<b.block<<std::endl;
		// StrFromData_64(buffer , b.block);
		// std::cout<<buffer[0]<<buffer[1]<<endl;

		b.Des(b,method); 

		StrFromData_64(buffer , b.block) ;//获取运算后的数据
		outputFile.write(buffer , 8) ;//写入目标文件

	}
    inputFile.close() ;
	outputFile.close() ;

	return 0 ;

}