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
    
}

#endif //_COMMON_UTILITY_H_
