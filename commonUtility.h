//************************************************
//◇作者：yrc
//◇日期：2014年9月12日
//◇说明：使用工具大全
//*************************************************

#pragma  once
#ifndef _COMMON_UTILITY_H_
#define _COMMON_UTILITY_H_

#include <string>
#include <vector>

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int  uint32_t;

#ifdef __x86_64__
    typedef  unsigned  long uint64_t;
#else
    typedef  unsigned  long long  uint64_t;
#endif

namespace Utility
{
    using std::string;
    using std::vector;
    
	//获取系统当前时间，并按照特定格式输出
	//strDst:输出的时间字符串
	//strFormat:输入的时间格式控制
	int GetNowTime(string &strDst,string &strFormat);
	
	//将源字符串按照指定字符串样式分割到数组中
	//vecOut:输出的字符串数组
	//strSrc:源字符串
	//strPattern:字符串切割样式
	int SplitStr2Array(vector<string> &vecOut, string &strSrc, string &strPattern);
	
	//解码bas464字符串
	//strDest:输出的解码后的字符串
	//strBaseSrc:输入的base64编码的字符串
	int DecodeBase64(string &strDest ,string &strBaseSrc);
	
	//对字符串进行base64编码
	//strBaseDst:输出的base64字符串
	//strSrc:源字符串
	int EncodeBase64(string &strBaseDst, string &strSrc);
	
	//将字符串转换为整形
	
	//将整形转换为字符串
	
	//将点分十进制转换为网络字节序（大端）
	int String2NetAddr(const char * szSrc, uint64_t & ullDst);
	
	//网络字节序转换为点分十进制
	int NetAddr2String(uint64_t const ullSrc, char * szDst);
    
    //递归创建目录。
    //pPath(in)全路径
    int  RecursiveMkdir(const char * pPath);
    
    //获取给定目录下的所有子目录信息和文件信息(不支持递归搜索)
    int GetFileList(const char * pDir, vector<string> & vctSubDir, vector<string> & vctSubFile);
    
    //大小端转换
    int SmallToBigEndian(uint8_t *pData, uint32_t uDataLen);
	int BigToSmallEndian(uint8_t *pData, uint32_t uDataLen);	
    
    //去除字符串首尾的空白符
    int Str_trip(string & strsrc);
    
    //获得一定范围的随机值
    int GetRandomValue(int max);
    
    /*
	 * 在概率数组中随机抽取一个
	 * param  rates(in)概率集合,len(in),target(out)
	 * return 0-成功
    */
     int TurnLuckTable(vector<unsigned> & rates, int len, int & target);
	
    	/*
	 * 在两个值之间产生一个随机值
	 * param  min(in),max(in)
	 * return 随机值
	 */
	int GetRandomBetweenAB(int min, int max);	
	
		/*
	 * 设置指定位值为1
	 * param  current(in&out),pos(in)
	 * return 0-成功
	 */
	static int SetBitCurrent(unsigned & current, int pos);

	/*
	* 设置指定位值为1
	* param  current(in&out),pos(in)
	* return 0-成功
	*/
	static int SetBitCurrent(unsigned char & current, int pos);

	/*
	* 设置指定范围内位的值为0
	* param  current(in&out),first(in),last(in)，范围区间是[first, last]
	* return 0-成功
	*/
	static int SetZeroRange(unsigned char & current, int first, int last);

	/*
	* 设置指定位的值为0
	* param  current(in&out),pos(in)
	* return 0-成功
	*/
	static int SetZeroCurrent(unsigned char & current, int pos);

	/*
	 * 设置低位maxsize个全为1的值
	 * param  maxsize(in),target(out)
	 * return 0-成功
	 */
	static int GetTargetBitValue(int maxsize, unsigned &target);

	/*
	 * 判断某个值的指定pos位是否为0
	 * param  value(in),pos(in)-下标
	 * return true-是
	 */
	static bool CheckPosIsZero(unsigned value, unsigned pos);
	
		/*
	 * 获取两个时间点之间的整点次数
	 * param  value(in),pos(in)
	 * return 整点次数
	 */
	static int GetHourTimes(unsigned start, unsigned end);

	//获取整点时间
	static unsigned GetHourTime(unsigned times);

	//获取给定时间的小时值
	static unsigned GetHourByTime(unsigned time);

	//获取给定时间的年月日
	static int GetDate(unsigned time, int & year, int & month, int &day);
}

#endif //_COMMON_UTILITY_H_
