#include <iostream>
#include <bitset>

typedef std::bitset<64> Data_64 ;//原始64位明文数据
typedef std::bitset<32> Data_32;//原始32位明文数据

typedef std::bitset<56> Key_56;//原始56位密钥
typedef std::bitset<28> Key_28;//初始密钥的一半28

typedef std::bitset<48> Code_48 ;//可以用来存子密钥(48位),也可以存48位扩展之后的分组数据
typedef std::bitset<24> Code_24;

typedef enum { e , d } Method;//e为加密，d为解密

