#include"Block.h"
//初始置换表
const static unsigned char Initial_table[64] = {
	58 , 50 , 42 , 34 , 26 , 18 , 10 , 2 , 60 , 52 , 44 , 36 , 28 , 20 , 12 , 4 ,
	62 , 54 , 46 , 38 , 30 , 22 , 14 , 6 , 64 , 56 , 48 , 40 , 32 , 24 , 16 , 8 ,
	57 , 49 , 41 , 33 , 25 , 17 , 9 , 1 , 59 , 51 , 43 , 35 , 27 , 19 , 11 , 3 ,
	61 , 53 , 45 , 37 , 29 , 21 , 13 , 5 , 63 , 55 , 47 , 39 , 31 , 23 , 15 , 7
} ;

//扩展置换，将数据从32位扩展为48位
static const unsigned char Expa_perm[48] = {
	32 , 1 , 2 , 3 , 4 , 5 , 4 , 5 , 6 , 7 , 8 , 9 , 8 , 9 , 10 , 11 ,
	12 , 13 , 12 , 13 , 14 , 15 , 16 , 17 , 16 , 17 , 18 , 19 , 20 , 21 , 20 , 21 ,
	22 , 23 , 24 , 25 , 24 , 25 , 26 , 27 , 28 , 29 , 28 , 29 , 30 , 31 , 32 , 1
} ;

//S盒子代替
const static unsigned char sbox[8][64]={
    {//S1盒子
	    14 , 4 , 13 , 1 , 2 , 15 , 11 , 8 , 3 , 10 , 6 , 12 , 5 , 9 , 0 , 7 ,
       	0 , 15 , 7 , 4 , 14 , 2 , 13 , 1 , 10 , 6 , 12 , 11 , 9 , 5 , 3 , 8 ,
       	4 , 1 , 14 , 8 , 13 , 6 , 2 , 11 , 15 , 12 , 9 , 7 , 3 , 10 , 5 , 0 ,
       	15 , 12 , 8 , 2 , 4 , 9 , 1 , 7 , 5 , 11 , 3 , 14 , 10 , 0 , 6 , 13
} ,
	{//S2盒子
       	15 , 1 , 8 , 14 , 6 , 11 , 3 , 4 , 9 , 7 , 2 , 13 , 12 , 0 , 5 , 10 ,
       	3 , 13 , 4 , 7 , 15 , 2 , 8 , 14 , 12 , 0 , 1 , 10 , 6 , 9 , 11 , 5 ,
       	0 , 14 , 7 , 11 , 10 , 4 , 13 , 1 , 5 , 8 , 12 , 6 , 9 , 3 , 2 , 15 ,
       	13 , 8 , 10 , 1 , 3 , 15 , 4 , 2 , 11 , 6 , 7 , 12 , 0 , 5 , 14 , 9
} ,
	{//S3盒子
       	10 , 0 , 9 , 14 , 6 , 3 , 15 , 5 , 1 , 13 , 12 , 7 , 11 , 4 , 2 , 8 ,
       	13 , 7 , 0 , 9 , 3 , 4 , 6 , 10 , 2 , 8 , 5 , 14 , 12 , 11 , 15 , 1 ,
       	13 , 6 , 4 , 9 , 8 , 15 , 3 , 0 , 11 , 1 , 2 , 12 , 5 , 10 , 14 , 7 ,
       	1 , 10 , 13 , 0 , 6 , 9 , 8 , 7 , 4 , 15 , 14 , 3 , 11 , 5 , 2 , 12
} ,
	{//S4盒子
       	7 , 13 , 14 , 3 , 0 , 6 , 9 , 10 , 1 , 2 , 8 , 5 , 11 , 12 , 4 , 15 ,
       	13 , 8 , 11 , 5 , 6 , 15 , 0 , 3 , 4 , 7 , 2 , 12 , 1 , 10 , 14 , 9 ,
       	10 , 6 , 9 , 0 , 12 , 11 , 7 , 13 , 15 , 1 , 3 , 14 , 5 , 2 , 8 , 4 ,
       	3 , 15 , 0 , 6 , 10 , 1 , 13 , 8 , 9 , 4 , 5 , 11 , 12 , 7 , 2 , 14
} ,
    {//S5盒子
	    2 , 12 , 4 , 1 , 7 , 10 , 11 , 6 , 8 , 5 , 3 , 15 , 13 , 0 , 14 , 9 ,
       	14 , 11 , 2 , 12 , 4 , 7 , 13 , 1 , 5 , 0 , 15 , 10 , 3 , 9 , 8 , 6 ,
       	4 , 2 , 1 , 11 , 10 , 13 , 7 , 8 , 15 , 9 , 12 , 5 , 6 , 3 , 0 , 14 ,
       	11 , 8 , 12 , 7 , 1 , 14 , 2 , 13 , 6 , 15 , 0 , 9 , 10 , 4 , 5 , 3
} ,
    {//S6盒子
	    12 , 1 , 10 , 15 , 9 , 2 , 6 , 8 , 0 , 13 , 3 , 4 , 14 , 7 , 5 , 11 ,
       	10 , 15 , 4 , 2 , 7 , 12 , 9 , 5 , 6 , 1 , 13 , 14 , 0 , 11 , 3 , 8 ,
       	9 , 14 , 15 , 5 , 2 , 8 , 12 , 3 , 7 , 0 , 4 , 10 , 1 , 13 , 11 , 6 ,
       	4 , 3 , 2 , 12 , 9 , 5 , 15 , 10 , 11 , 14 , 1 , 7 , 6 , 0 , 8 , 13
} ,
	{//S7盒子
       	4 , 11 , 2 , 14 , 15 , 0 , 8 , 13 , 3 , 12 , 9 , 7 , 5 , 10 , 6 , 1 ,
       	13 , 0 , 11 , 7 , 4 , 9 , 1 , 10 , 14 , 3 , 5 , 12 , 2 , 15 , 8 , 6 ,
       	1 , 4 , 11 , 13 , 12 , 3 , 7 , 14 , 10 , 15 , 6 , 8 , 0 , 5 , 9 , 2 ,
       	6 , 11 , 13 , 8 , 1 , 4 , 10 , 7 , 9 , 5 , 0 , 15 , 14 , 2 , 3 , 12
} ,
	{//S8盒子
       	13 , 2 , 8 , 4 , 6 , 15 , 11 , 1 , 10 , 9 , 3 , 14 , 5 , 0 , 12 , 7 ,
       	1 , 15 , 13 , 8 , 10 , 3 , 7 , 4 , 12 , 5 , 6 , 11 , 0 , 14 , 9 , 2 ,
       	7 , 11 , 4 , 1 , 9 , 12 , 14 , 2 , 0 , 6 , 10 , 13 , 15 , 3 , 5 , 8 ,
       	2 , 1 , 14 , 7 , 4 , 10 , 8 , 13 , 15 , 12 , 9 , 0 , 3 , 5 , 6 , 11
}
} ;

//P盒置换
const static unsigned char pbox[32] = {
	16 , 7 , 20 , 21 , 29 , 12 , 28 , 17 , 1 , 15 , 23 , 26 , 5 , 18 , 31 , 10 ,
	2 , 8 , 24 , 14 , 32 , 27 , 3 , 9 , 19 , 13 , 30 , 6 , 22 , 11 , 4 , 25
} ;

//最后置换
const static unsigned char final_table[64] = {
	40 , 8 , 48 , 16 , 56 , 24 , 64 , 32 , 39 , 7 , 47 , 15 , 55 , 23 , 63 , 31 ,
	38 , 6 , 46 , 14 , 54 , 22 , 62 , 30 , 37 , 5 , 45 , 13 , 53 , 21 , 61 , 29 ,
	36 , 4 , 44 , 12 , 52 , 20 , 60 , 28 , 35 , 3 , 43 , 11 , 51 , 19 , 59 , 27 ,
	34 , 2 , 42 , 10 , 50 , 18 , 58 , 26 , 33 , 1 , 41 , 9 , 49 , 17 , 57 , 25
} ;

//密钥置换表，将64位密钥置换压缩置换为56位
const static unsigned char Key_ip_table[56] = {
	57 , 49 , 41 , 33 , 25 , 17 , 9 , 1 ,
	58 , 50 , 42 , 34 , 26 , 18 , 10 , 2 ,
	59 , 51 , 43 , 35 , 27 , 19 , 11 , 3 ,
	60 , 52 , 44 , 36 , 63 , 55 , 47 , 39 ,
	31 , 23 , 15 , 7 , 62 , 54 , 46 , 38 ,
	30 , 22 , 14 , 6 , 61 , 53 , 45 , 37 ,
	29 , 21 , 13 , 5 , 28 , 20 , 12 , 4
} ;

//压缩置换表，56位密钥压缩位48位密钥
const static unsigned char Comp_perm[48] = {
	14 , 17 , 11 , 24 , 1 , 5 , 3 , 28 ,
	15 , 6 , 21 , 10 , 23 , 19 , 12 , 4 ,
	26 , 8 , 16 , 7 , 27 , 20 , 13 , 2 ,
	41 , 52 , 31 , 37 , 47 , 55 , 30 , 40 ,
	51 , 45 , 33 , 48 , 44 , 49 , 39 , 56 ,
	34 , 53 , 46 , 42 , 50 , 36 , 29 , 32
} ;

//每轮移动的位数
const static unsigned char Bit_shift[16] = {
	1 , 1 , 2 , 2 , 2 , 2 , 2 , 2 , 1 , 2 , 2 , 2 , 2 , 2 , 2 , 1
} ;


//64位数据初始置换并分组    历史遗留问题？？？？？
int Block::Block_ip_divide(const Data_64 & block , Data_32 & left , Data_32 & right){

	//获取置换后的左半部分
	for(size_t i = 0 ; i < left.size() ; ++i)
		left[i] = block[Initial_table[i+left.size()] - 1] ;
	//获取置换后的右半部分
	for(size_t i = 0 ; i < right.size() ; ++i)
		right[i] = block[Initial_table[i]- 1] ;  
	return 0 ;
};

int Block::Des_turn(Data_32 & left , Data_32 & right , const Code_48 & subkey){
    Code_48 code ;//48位数据块
	Data_32 pcode ;//32位数据块
	
    //将右半部分扩展为48位
	for(size_t i = 0 ; i < code.size() ; ++i)
		code[i] = right[Expa_perm[i] - 1] ;//扩展置换

	code ^= subkey ;//与子密钥异或

	//S盒代替
	std::bitset<4> col ;//S盒的列
	std::bitset<2> row ;//S盒的行
	for(size_t i = 0 ; i < 8 ; ++i)
	{//8个盒子

        //获取行号
		row[0] = code[6 * i] ;
		row[1] = code[6 * i + 5] ;

        //获取列号
		col[0] = code[6 * i + 1] ;
		col[1] = code[6 * i + 2] ;
		col[2] = code[6 * i + 3] ;
		col[4] = code[6 * i + 4] ;

        //s盒替换
		std::bitset<4> temp(sbox[i][row.to_ulong() * 16 + col.to_ulong()]) ;
		
        //临时保存
        for(size_t j = 0 ; j < temp.size() ; ++j)
			code[4 * i + j] = temp[j] ;
	}

    //P盒置换
	for(size_t i = 0 ; i < pcode.size() ; ++i)
		pcode[i] = code[pbox[i] - 1] ;
	
    //与左半部分异或
    left ^= pcode ;

	return 0 ;
};

//左右两边交换
int Block::Exchange(Data_32 & left , Data_32 & right) {
    Data_32 temp ;
	for(size_t i = 0 ; i < temp.size() ; ++i)
		temp[i] = left[i] ;
	for(size_t i = 0 ; i < left.size() ; ++i)
		left[i] = right[i] ;
	for(size_t i = 0 ; i < right.size() ; ++i)
		right[i] = temp[i] ;
	return 0 ;
};

//将左右两部分数据进行末置换形成一个数据块
int Block::Block_ip_final(const Data_32 & left , const Data_32 & right , Data_64 & block)
{
	for(size_t i = 0 ; i < block.size() ; ++i)
	{
		if(final_table[i] <= 32)
			block[i] = right[final_table[i] - 1] ;//从right部分获取数据
		else
			block[i] = left[final_table[i] - 32 - 1] ;//从left部分获取数据
	}
	return 0 ;
};

//获取第n轮的子密钥
//64位初始密钥-->密钥转换（56位）-->分成两组28位-->左旋n位-->重新合并-->置换选择
Code_48 Block::Getkey(const unsigned int n , const Data_64 & initial_key){
    
    //n在区间[0,15]之间取值，initial_key为64位初始密钥
    Key_56 key ;                        //56位密钥
	Code_48 subkey;                      //返回值,48位子密钥

	unsigned int klen = key.size();     //56位
    unsigned int slen = subkey.size();  //48位
	
    ////密钥置换,获取56位密钥
	for(size_t i = 0 ; i < key.size() ; ++i)
		key[i] = initial_key[Key_ip_table[i] - 1] ;

    //分成两组,循环移位
	for(size_t i = 0 ; i <= n ; ++i)
	{
        
        //做一个备份
		for(size_t j = 0 ; j < Bit_shift[i] ; ++j)
		{
			//将密钥循环位暂存在subkey中
			subkey[slen - Bit_shift[i] + j] = key[klen - Bit_shift[i] + j] ;
			subkey[slen / 2 - Bit_shift[i] + j] = key[klen / 2 - Bit_shift[i] + j] ;
        }

        //移位，因为计算机不是循环移位的，所以需要记录
		key <<= Bit_shift[i] ;

        //写回key中
		for(size_t j = 0 ; j < Bit_shift[i] ; ++j)
		{		
			key[klen / 2 + j] = subkey[slen - Bit_shift[i] + j] ;
			key[j] = subkey[slen / 2 - Bit_shift[i] + j] ;
		}
	}

	//压缩置换
	for(size_t i = 0 ; i < subkey.size() ; ++i)
		subkey[i] = key[Comp_perm[i] - 1] ;
	return subkey ;
};
void Block::Des(Block &b,Method method){
	b.Block_ip_divide(b.block , b.left , b.right) ;//初始置换
	switch(method)
	{
		case e://加密
			for(char i = 0 ; i < 16 ; ++i)	
			{	
				Code_48 key = b.Getkey(i,b.initial_key);
				b.Des_turn(b.left , b.right , key);
				if(i != 15) 
                    b.Exchange(b.left, b.right);
			}
			break ;
		case d://解密
			for(char i = 15 ; i >= 0 ; --i)
			{
				Code_48 key = b.Getkey(i,b.initial_key) ;
				b.Des_turn(b.left , b.right , key) ;
				if(i != 0) 
                    b.Exchange(b.left, b.right);
			}
			break ;
		default:
			break ;
	}
	b.Block_ip_final(b.left , b.right , b.block) ;//末置换

};
