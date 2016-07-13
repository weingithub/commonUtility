#include "commonUtility.h"
#include <time.h>
#include <cstdio>
#include <cstring>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <glob.h>
#include <ctime>
#include <cstdlib>

using namespace std;

int Utility::GetNowTime(string &strDst,string &strFormat)
{
	time_t now = time(0);
	char szTemp[64];
	memset(szTemp,0,64);
	strftime(szTemp,sizeof(szTemp),strFormat.c_str(),localtime(&now));
	strDst = szTemp	;
    
    return 0;
}

int Utility::SplitStr2Array(vector<string> &vecOut,string &strSrc,string &strPattern)
{
	if (!strSrc.empty())
	{
		int nLen = strSrc.size();
		string::size_type pos , last_search_pos = 0;  
		while( (pos = strSrc.find(strPattern,last_search_pos)) != string::npos )  
		{ 
		    if(pos != last_search_pos)
			{
		      //substr����ָ���±괦��ʼ������ָ��n���ֽ�
		      vecOut.push_back(strSrc.substr(last_search_pos,pos-last_search_pos));
		    }          
		    last_search_pos = pos+1;  
	    }
		
	   //�ж�last_search_pos�Ƿ����ַ���ĩβ
	   if(last_search_pos < nLen)
	   {
		 	vecOut.push_back(strSrc.substr(last_search_pos,nLen-last_search_pos));
	   }
    }    
    
    return 0;
}

int Utility::DecodeBase64(string &strDest ,string &strBaseSrc)
{
	const int BAD = -1;
	const int MAXLENG = 1000;
	char base64_decode_map[] = {
     BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD,
     BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD,
     BAD,BAD,BAD,BAD, BAD,BAD,BAD,BAD, BAD,BAD,BAD, 62, BAD,BAD,BAD, 63,
      52, 53, 54, 55, 56, 57, 58, 59, 60, 61,BAD,BAD, BAD,BAD,BAD,BAD,
     BAD, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14,
      15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25,BAD, BAD,BAD,BAD,BAD,
     BAD, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
      41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51,BAD, BAD,BAD,BAD,BAD
    };
     
	char dst[MAXLENG] , src[MAXLENG];
    memset(dst,0, MAXLENG);
    memset(src,0, MAXLENG);
    
    strncpy(src, strBaseSrc.c_str(), sizeof(src));
    
    int i = 0, j = 0 ,src_len;
    src_len = strBaseSrc.size(); 
    
    for (; i < src_len; i += 4) 
    {
        dst[j++] = base64_decode_map[src[i]]<<2 | base64_decode_map[src[i + 1]] >> 4;
        dst[j++] = base64_decode_map[src[i + 1]]<<4 | base64_decode_map[src[i + 2]] >> 2; //��base64_decode_map[src[i + 2]]ֵΪ-1ʱ���������ƣ��ұ߲�1�����һֱ���ƵĻ������;ͱ��0xFFFFFFFF ��-1���������ƵĻ����ұ߲�0��һֱ���ƵĻ���������0����-2<<2 Ϊ-4 �� -2<<31Ϊ0
        dst[j++] = base64_decode_map[src[i + 2]]<<6 | base64_decode_map[src[i + 3]];
    }
    
	//�����Ŀո�����,base�����У�һ��=��Ӧ���������е�һ���ո�Ҫȥ���ո�
	if((int)dst[j-2] == -1)
	{
		dst[j-2] = '\0';
	}
	else if((int)dst[j-1] == -1)
	{
		dst[j-1] = '\0';
	}
	else
	{
		dst[j] = '\0';
	}
    
	strDest = dst;
    
    return 0;
}

int Utility::EncodeBase64(string &strBaseDst ,string &strSrc)
{
	const int MAXLENG = 1000;
	char base64_encode_map[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
	int i = 0, j = 0, src_len;
	char dst[MAXLENG] , src[MAXLENG];
    memset(dst, 0, MAXLENG);
    memset(src, 0, MAXLENG);
    
    strncpy(src, strSrc.c_str(), sizeof(src));

    src_len = strSrc.size(); 
    
    for (; i < src_len - src_len % 3; i += 3)
	{
        dst[j++] = base64_encode_map[(src[i] >> 2) & 0x3f];
        dst[j++] = base64_encode_map[((src[i]<< 4) | (src[i + 1] >> 4)) & 0x3f];
        dst[j++] = base64_encode_map[((src[i + 1] << 2) | (src[i + 2] >> 6 )) & 0x3f];
        dst[j++] = base64_encode_map[src[i + 2] & 0x3f];
	}
	
    if (src_len % 3 == 1)
	{
		dst[j++] = base64_encode_map[(src[i]>> 2) & 0x3f];
        dst[j++] = base64_encode_map[(src[i] <<4) & 0x3f];
        dst[j++] = '=';
		dst[j++] = '=';
    }
    else if (src_len % 3 == 2) 
	{
        dst[j++] = base64_encode_map[(src[i]>> 2) & 0x3f];
        dst[j++] = base64_encode_map[((src[i] << 4) | (src[i + 1] >> 4)) & 0x3f];
        dst[j++] = base64_encode_map[(src[i + 1] << 2) & 0x3f];
        dst[j++] = '=';
    }
    
    dst[j] = '\0';
	strBaseDst = dst;
    
    return 0;
}

int Utility::String2NetAddr(const char *szSrc, uint64_t &ullDst)
{
	unsigned int val = 0;
	unsigned int tmp = 0;
	char c;
	int base = 10;
	int shift = 32;
	char *szval = new char [strlen(szSrc)+1];
	char *pTemp = szval;
	strcpy(szval,szSrc);
	c = *szval;
    
	for (;;) 
	{
		//���Ը���һ�����ⳤ�ȵ��ַ�����
		tmp = 0;
		for (;;) 
		{//���'.'�ָ��ÿһ���ַ�������ֵ��
			if (isdigit(c))
			{
				tmp = (tmp * base) + (c - '0');
				c = *++szval;
			} else break;
		}

		shift -= 8;
		tmp <<= shift;
		val += tmp;  //�����ֽ����ֵ
		
		if (c == '.')
		{
			c = *++szval;
		} 
		else
		{
			break;
		}
	
	}
	
	delete[] pTemp;
	/*
	 * Check for trailing characters.
	 */
	if (c != '\0' && (!isspace(c)))
	{
		return -1;
	}
	
	ullDst = htonl (val);  //�õ������ֽ���
    
	return 0;
}

int  Utility::NetAddr2String(uint64_t const ullSrc,char * szDst)
{
	unsigned int utmp = ntohl(ullSrc);  //�������ֽ���ת��Ϊ�����ֽ���
	unsigned char *bytes = (unsigned char *) &utmp;
	snprintf (szDst,32, "%d.%d.%d.%d",bytes[3], bytes[2], bytes[1], bytes[0]);//�����ֽ����Ǵ�˱�ʾ����һ����byte[3]��
    
	return 0;
}

int Utility::RecursiveMkdir(const char * pPath)
{
    if (NULL == pPath)
    {
       // WRITELOG(LOG_ERROR, "RecursiveMkdir param invalid");
        return -1;
    }

    if (0 == access(pPath, F_OK))   
    {
       return 0;
    }

    int nRet = mkdir(pPath, S_IRWXU|S_IRGRP|S_IXGRP|S_IROTH|S_IXOTH|S_IWGRP|S_IWOTH);   //��Ҫͷ�ļ�<sys/stat.h>��֧��

    if (0 == nRet)
    {
        return 0;
    }
    else  //����Ŀ¼ʧ�ܣ��༶Ŀ¼���ݹ鴴��
    {
        char szLocalPath[100] = {0};
        char * pstr = strrchr((char *)pPath, '/');   //��Ҫͷ�ļ�<string.h>֧��
        int len = pstr - pPath;

        if (len >= sizeof(szLocalPath))
        {
            len = sizeof(szLocalPath) -1;  //��1��λ�����յ�\0�����ַ�
        }

        strncpy(szLocalPath, pPath, len);  // ��Ҫͷ�ļ�<string.h>֧��

        szLocalPath[len+1] = '\0';

        //cout<<"�ݹ鴴����·����"<<szLocalPath<<endl;
        RecursiveMkdir(szLocalPath);
        return RecursiveMkdir(pPath);
    }
}

int Utility::GetFileList(const char * pDir, vector<string> & vctSubDir, vector<string> & vctSubFile)
{
    if (NULL == pDir)
    {
        return -1;
    }
    
    glob_t globObj;
	char szPath[512] = {0};
	
	sprintf(szPath, "%s/*", pDir);
	
	glob(szPath, GLOB_TILDE, 0, &globObj);
    struct stat buf;	
    
    char szName[1000] = {0};
    
    for(unsigned int uNum = 0; uNum < globObj.gl_pathc; uNum++)
	{
        //gl_pathv·���Ǿ���·��
		memset(szName, 0, sizeof(szName));
		strcpy(szName, globObj.gl_pathv[uNum]);
        
        if (stat(szName, &buf) < 0)
		{
			//cerr<<"��ȡ�ļ���Ϣʧ�ܡ�file:"<<szName<<"errmsg:"<<strerror(errno);
			continue;
		}
        
        if (S_ISREG(buf.st_mode)) //��ͨ�ļ�
		{
            vctSubFile.push_back(szName);
		}
        else if(S_ISDIR(buf.st_mode))  //Ŀ¼
        {
            //��Ŀ¼��д�뼯����
            vctSubDir.push_back(szName);
        }
    }
    
    if ( 0 == vctSubDir.size() || 0 == vctSubFile.size())
    {
        return -1;
    }
    
    return 0;
}
 
int Utility::SmallToBigEndian(uint8_t *pData, uint32_t uDataLen)
{
    unsigned char *pStart = pData;
    unsigned char *pEnd   = pData + uDataLen - 1;
    unsigned char cTmp;
     
    while(pEnd > pStart)  //�ֽ�λ������β����
    {
        cTmp    = *pStart;
        *pStart = *pEnd;
        *pEnd   = cTmp;
 
        ++pStart;
        --pEnd;
    }
     
    return 0;
}
 
int Utility::BigToSmallEndian(uint8_t *pData, uint32_t uDataLen)
{
    return SmallToBigEndian(pData, uDataLen);
}	

int Utility::Str_trip(string & strsrc)
{
    if (strsrc.empty())
    {
        return 0;
    }
    
    int start = 0, end = 0;  //��ʼλ�úͽ���λ��
      
    int pos = 0;
   
    while ( strsrc[pos] && strchr(" \t\n\r", strsrc[pos]) )
    {
        ++pos;
    }
        
    start = pos;
        
    pos = strsrc.size() - 1;  //����
    while(pos >= start && strsrc[pos] == ' ')
    {
        --pos;
    }
        
    end = pos;
        
    strsrc = strsrc.substr(start, end - start + 1);
        
    return 0;
}

int Utility::GetRandomValue(int max)
{
    if (0 == max)
    {
        return 0;
    }
    
    //���������������
    srand((unsigned)time(0));
    
    int random = rand()% max;
    
    return random;
}
