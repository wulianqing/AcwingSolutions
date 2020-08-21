#include<iostream>
#include<fstream>


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

struct bmpOperator{
    unsigned char *pBmpBuf;//读入图像数据的指针
    int bmpWidth;//图像的宽
    int bmpHeight;//图像的高
    int biBitCount;//图像类型，每像素位数
    RGBQUAD *pColorTable;//颜色表指针
};


//全局变量
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
 
//-----------------------------------------------------------------------€------------------
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






//————————start——————————————————————————————————————————————————




//--------------------------------------------------------

void doIt(){
	char readPath[] = "/Users/wubaobao/GoogleCloud-aaedu/Dropbox/ProjectCodeFolder/VSCode/AcwingSolutions/image/wulianqing_60_60.bmp";
	char writePath[] = "/Users/wubaobao/GoogleCloud-aaedu/Dropbox/ProjectCodeFolder/VSCode/AcwingSolutions/image/b.bmp";
	bmpOperator bmp_opt;
	readBmp(readPath);
	//图像信息：长，宽，每像素的位数
	std::cout << "width: " << bmp_opt.bmpWidth<<std::endl
			  << "height: " <<  bmp_opt.bmpHeight<<std::endl
			  << "bit counter: " << bmp_opt.biBitCount<<std::endl;
	int lineByte=(bmp_opt.bmpWidth * bmp_opt.biBitCount/8+3)/4*4;//每行字节数 
    int  **b=new int *[bmp_opt.bmpHeight];//动态创建像素矩阵 
    for(int i=0;i<bmp_opt.bmpHeight;i++){
  	 	b[i]=new int[lineByte];
    }
    if(bmp_opt.biBitCount==8){ //对于灰度图像	              
	    for(int i=0;i<bmp_opt.bmpHeight;i++){        
            for(int j=0;j<bmp_opt.bmpWidth;j++){
            	b[i][j]=*(bmp_opt.pBmpBuf+i*lineByte+j);
			}             
        }        
	} 
	if(bmp_opt.biBitCount==24){//彩色图像
		for(int i=0;i<bmp_opt.bmpHeight;i++){   
			int j1=0;
			for(int j=0;j<bmp_opt.bmpWidth;j++){				
                b[i][j]=*(bmp_opt.pBmpBuf+i*lineByte+j1);
				j1=j1+3;									
            }
        }
	}
    int col_left[bmp_opt.bmpHeight][1],col_right[bmp_opt.bmpHeight];//每像素行 右边界一维数组 
    double row_per[bmp_opt.bmpHeight];//每像素行黑点数所占百分比矩阵 
  
    int up[bmp_opt.bmpHeight]; //上边界行号 
    int down[bmp_opt.bmpHeight];//下边界行号 
    int rownum1=0,rownum2=0; 


	//将图像数据存盘    
    
     if (bmp_opt.biBitCount == 8){
        for(int i=0;i<bmp_opt.bmpHeight;i++){   
            for(int j=0;j<bmp_opt.bmpWidth;j++){
            	bmp_opt.pBmpBuf[i*lineByte + j]=b[i][j];
            }
        }
	}
 	if (bmp_opt.biBitCount == 24){
        for(int i=0;i<bmp_opt.bmpHeight;i++){   
		    int j=0;
            for(int j1=0;j1<lineByte;j1=j1+3){
            	bmp_opt.pBmpBuf[i*lineByte + j1]=b[i][j];
				bmp_opt.pBmpBuf[i*lineByte + j1 + 1] = b[i][j];
                bmp_opt.pBmpBuf[i*lineByte + j1 + 2] =b[i][j];
                j=j+1;
            }
        }
	}
    saveBmp(writePath, bmp_opt.pBmpBuf, bmp_opt.bmpWidth, bmp_opt.bmpHeight, bmp_opt.biBitCount, bmp_opt.pColorTable);
 	printf("write success!!\n");
	
}

int main(){
	doIt();
	return 0;
}


