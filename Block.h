#include "des.h"
#include <fstream>
class Block{
    public:

        Data_64 block;//64位数据
        Data_32 left; //左边32位数据
        Data_32 right;//右边32位数据

        Data_64 initial_key;//初始64密码


        //64位数据初始置换并分组
        int Block_ip_divide(const Data_64 & block , Data_32 & left , Data_32 & right);
        
        //1轮加密，不交换 1.扩展置换 --> 2.与子密钥异或 --> 3.S盒替换 --> 4.P盒替换 --> 与左边部分异或
        int Des_turn(Data_32 & left , Data_32 & right , const Code_48 & subkey);

        //每一轮加密之后左右需要进行交换，除最后一轮
        int Exchange(Data_32 & left , Data_32 & right) ;

        //最后置换
        int Block_ip_final(const Data_32 & left , const Data_32 & right , Data_64 & block);

        //获取第n轮的子密钥
        Code_48 Getkey(const unsigned int n , const Data_64 & initial_key) ;

        void Des(Block &b, Method method);

};
