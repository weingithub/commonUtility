//************************************************
//�����ߣ�yrc
//�����ڣ�2014��9��12��
//��˵����ʹ�ù��ߴ�ȫ
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
    
	//��ȡϵͳ��ǰʱ�䣬�������ض���ʽ���
	//strDst:�����ʱ���ַ���
	//strFormat:�����ʱ���ʽ����
	int GetNowTime(string &strDst,string &strFormat);
	
	//��Դ�ַ�������ָ���ַ�����ʽ�ָ������
	//vecOut:������ַ�������
	//strSrc:Դ�ַ���
	//strPattern:�ַ����и���ʽ
	int SplitStr2Array(vector<string> &vecOut, string &strSrc, string &strPattern);
	
	//����bas464�ַ���
	//strDest:����Ľ������ַ���
	//strBaseSrc:�����base64������ַ���
	int DecodeBase64(string &strDest ,string &strBaseSrc);
	
	//���ַ�������base64����
	//strBaseDst:�����base64�ַ���
	//strSrc:Դ�ַ���
	int EncodeBase64(string &strBaseDst, string &strSrc);
	
	//���ַ���ת��Ϊ����
	
	//������ת��Ϊ�ַ���
	
	//�����ʮ����ת��Ϊ�����ֽ��򣨴�ˣ�
	int String2NetAddr(const char * szSrc, uint64_t & ullDst);
	
	//�����ֽ���ת��Ϊ���ʮ����
	int NetAddr2String(uint64_t const ullSrc, char * szDst);
    
    //�ݹ鴴��Ŀ¼��
    //pPath(in)ȫ·��
    int  RecursiveMkdir(const char * pPath);
    
    //��ȡ����Ŀ¼�µ�������Ŀ¼��Ϣ���ļ���Ϣ(��֧�ֵݹ�����)
    int GetFileList(const char * pDir, vector<string> & vctSubDir, vector<string> & vctSubFile);
    
    //��С��ת��
    int SmallToBigEndian(uint8_t *pData, uint32_t uDataLen);
	int BigToSmallEndian(uint8_t *pData, uint32_t uDataLen);	
    
    //ȥ���ַ�����β�Ŀհ׷�
    int Str_trip(string & strsrc);
    
    //���һ����Χ�����ֵ
    int GetRandomValue(int max);
    
}

#endif //_COMMON_UTILITY_H_
