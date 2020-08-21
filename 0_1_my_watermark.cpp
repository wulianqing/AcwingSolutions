#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<iomanip>
#include<math.h> 

#pragma pack(2)
typedef unsigned long       DWORD;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
//位图文件头 
typedef struct BITMAPFILEHEADER{
WORD bfType;
DWORD bfSize;
WORD bfReserved1;
WORD bfReserved2;
DWORD bfOffBits;
}BITMAPFILEHEADER;
typedef struct BITMAPINFOHEADER{
DWORD biSize;
DWORD biWidth;
DWORD biHeight;
WORD  biPlanes;
WORD  biBitCount;
DWORD biCompression;
DWORD biSizeImage;
DWORD biXPelsPerMeter;
DWORD biYPelsPerMeter;
DWORD biClrUsed;
DWORD biClrImportant;
}BITMAPINFODEADER;        
typedef struct RGBQUAD{
BYTE  rgbBLUE;
BYTE  rgbGREEN;
BYTE  rbgRED;
BYTE  rgbReserved;
}RGBQUAD;    

//---------------------------------------------------------------------------------------
//以下该模块是完成BMP图像(彩色图像是24bit RGB各8bit)的像素获取，并存在文件名为xiang_su_zhi.txt中
unsigned char *pBmpBuf;//读入图像数据的指针 
int bmpWidth;//图像的宽
int bmpHeight;//图像的高
RGBQUAD *pColorTable;//颜色表指针 
int biBitCount;//图像类型，每像素位数
 
//-------------------------------------------------------------------------------------------
//读图像的位图数据、宽、高、颜色表及每像素位数等数据进内存，存放在相应的全局变量中
bool readBmp(char *bmpName) 
{
    FILE *fp=fopen(bmpName,"rb");//二进制读方式打开指定的图像文件 
    if(fp==0){
    	printf("Input error!! Can't find this picture!\n");
    	return 0;
	} 
		
 
    //跳过位图文件头结构BITMAPFILEHEADER 
    fseek(fp, sizeof(BITMAPFILEHEADER),0);
 
    //定义位图信息头结构变量，读取位图信息头进内存，存放在变量head中
    BITMAPINFOHEADER head;   
    fread(&head, sizeof(BITMAPINFOHEADER), 1,fp); //获取图像宽、高、每像素所占位数等信息 
    bmpWidth = head.biWidth; 
    bmpHeight = head.biHeight; 
    biBitCount = head.biBitCount;//定义变量，计算图像每行像素所占的字节数（必须是4的倍数） 
    int lineByte=(bmpWidth * biBitCount/8+3)/4*4;
 
    if(biBitCount==8)
	{ 	//灰度图像有颜色表，且颜色表表项为256,申请颜色表所需要的空间，读颜色表进内存 
        pColorTable=new RGBQUAD[256]; 
        fread(pColorTable,sizeof(RGBQUAD),256,fp); 
	}
 
    //申请位图数据所需要的空间，读位图数据进内存 
    pBmpBuf=new unsigned char[lineByte * bmpHeight]; 
    fread(pBmpBuf,1,lineByte * bmpHeight,fp); 
    
    fclose(fp);//关闭文件 
    return 1;//读取文件成功
}
 
//-----------------------------------------------------------------------------------------
//给定一个图像位图数据、宽、高、颜色表指针及每像素所占的位数等信息,将其写到指定文件中
bool saveBmp(char *bmpName, unsigned char *imgBuf, int width, int height, int biBitCount, RGBQUAD *pColorTable)
{ 
    //如果位图数据指针为0，则没有数据传入，函数返回 
    if(!imgBuf){
    	printf("Write error!! No data incoming! \n");
    	return 0;
	}
        
    //颜色表大小，以字节为单位，灰度图像颜色表为1024字节，彩色图像颜色表大小为0 
    int colorTablesize=0; 
    if(biBitCount==8)
        colorTablesize=1024;
 
    //待存储图像数据每行字节数为4的倍数 
    int lineByte=(width * biBitCount/8+3)/4*4;
 
    //以二进制写的方式打开文件 
    FILE *fp=fopen(bmpName,"wb");
    if(fp==0){
    	printf("Create erroe!! Failed to create new picture!\n");
    	return 0;
	}	
 
    //申请位图文件头结构变量，填写文件头信息 
    BITMAPFILEHEADER fileHead;
    fileHead.bfType = 0x4D42;//bmp类型 
    //bfSize是图像文件4个组成部分之和
    fileHead.bfSize= sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + colorTablesize + lineByte*height; 
    fileHead.bfReserved1 = 0; 
    fileHead.bfReserved2 = 0;
    //bfOffBits是图像文件前3个部分所需空间之和 
    fileHead.bfOffBits=54+colorTablesize; 
    //写文件头进文件 
    fwrite(&fileHead, sizeof(BITMAPFILEHEADER),1, fp);
 
    //申请位图信息头结构变量，填写信息头信息 
    BITMAPINFOHEADER head; 
    head.biBitCount=biBitCount; 
    head.biClrImportant=0; 
    head.biClrUsed=0;     head.biCompression=0;
    head.biHeight=height; 
    head.biPlanes=1;
    head.biSize=40; 
    head.biSizeImage=lineByte*height; 
    head.biWidth=width; 
    head.biXPelsPerMeter=0; 
    head.biYPelsPerMeter=0;
    //写位图信息头进内存
    fwrite(&head, sizeof(BITMAPINFOHEADER),1, fp);
 
    //如果灰度图像，有颜色表，写入文件 
    if(biBitCount==8)
        fwrite(pColorTable, sizeof(RGBQUAD),256, fp);
 
    //写位图数据进文件 
    fwrite(imgBuf, height*lineByte, 1, fp);
 
    //关闭文件 
    fclose(fp); 
    return 1; 
}
//冒泡排序 
void bubble_sort(int arr[], int len) {
    int i, j, temp;
    for (i = 0; i < len - 1; i++){
    	for (j = 0; j < len - 1 - i; j++){
        	if (arr[j] > arr[j + 1]) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
		}
	} 
	/*printf("len=%d\n",len);
	for(i=0;i<len;i++){
		printf("%d ",arr[i]);
	}  
	printf("\n");   
	*/     
}

//删除数组中的0元素 
void Del(int a[],int m){
	int j=0;
    for(int i=0;i<m;i++){
        if(a[i]!=0){
            a[j]=a[i];
            j++;
        }
    }	
}
void doIt()
{      
    char readPath[]="/Users/wubaobao/GoogleCloud-aaedu/Dropbox/ProjectCodeFolder/VSCode/AcwingSolutions/image/t.bmp";//读入指定BMP文件进内存 
    char writePath[]="/Users/wubaobao/GoogleCloud-aaedu/Dropbox/ProjectCodeFolder/VSCode/AcwingSolutions/image/test.bmp";
    int word=111;//中文文本
	//int word=222;//英文文本 
    readBmp(readPath);     
    printf("width=%d  height=%d biBitCount=%d\n",bmpWidth,bmpHeight,biBitCount);//输出图像的信息  
    int lineByte=(bmpWidth*biBitCount/8+3)/4*4;//每行字节数 
    int  **b=new int *[bmpHeight];//动态创建像素矩阵 
    for(int i=0;i<bmpHeight;i++){
  	 	b[i]=new int[lineByte];
    }
    if(biBitCount==8){ //对于灰度图像	              
	    for(int i=0;i<bmpHeight;i++){        
            for(int j=0;j<bmpWidth;j++){
            	b[i][j]=*(pBmpBuf+i*lineByte+j);
			}             
        }        
	} 
	if(biBitCount==24){//彩色图像
		for(int i=0;i<bmpHeight;i++){   
			int j1=0;
			for(int j=0;j<bmpWidth;j++){				
                b[i][j]=*(pBmpBuf+i*lineByte+j1);
				j1=j1+3;									
            }
        }
	}


   
    //将图像数据存盘    
    
     if (biBitCount == 8){
        for(int i=0;i<bmpHeight;i++){   
            for(int j=0;j<bmpWidth;j++){
            	pBmpBuf[i*lineByte + j]=b[i][j];
            }
        }
	}
 	if (biBitCount == 24){
        for(int i=0;i<bmpHeight;i++){   
		    int j=0;
            for(int j1=0;j1<lineByte;j1=j1+3){
            	pBmpBuf[i*lineByte + j1]=b[i][j];
				pBmpBuf[i*lineByte + j1 + 1] = b[i][j];
                pBmpBuf[i*lineByte + j1 + 2] =b[i][j];
                j=j+1;
            }
        }
	}
    saveBmp(writePath, pBmpBuf, bmpWidth, bmpHeight, biBitCount, pColorTable);
 	printf("write success!!\n");
    //清除缓冲区，pBmpBuf和pColorTable是全局变量，在文件读入时申请的空间 
    delete []pBmpBuf; 
    if(biBitCount==8){
    	delete [] pColorTable;
	}        
   printf("clean 1 success!!\n");      
    for(int i=0;i<bmpHeight;i++){   
	    delete [] b[i]; 
		//printf("%d:clean success!!\n",i);       
	}
    delete [] b;  
	printf("clean success!!\n");   
}
 
int main()
{
    doIt();
}