
//#include "stdafx.h"

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
#include<iomanip>
#include<math.h> 



#ifndef _WINDOWS


#pragma pack(2)
typedef unsigned long       DWORD;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
//位图文件头 
typedef struct BITMAPFILEHEADER {
	WORD bfType;
	DWORD bfSize;
	WORD bfReserved1;
	WORD bfReserved2;
	DWORD bfOffBits;
}BITMAPFILEHEADER;
typedef struct BITMAPINFOHEADER {
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
typedef struct RGBQUAD {
	BYTE  rgbBLUE;
	BYTE  rgbGREEN;
	BYTE  rbgRED;
	BYTE  rgbReserved;
}RGBQUAD;
#endif

//冒泡排序 
void bubble_sort(int arr[], int len) {
	int i, j, temp;
	for (i = 0; i < len - 1; i++) {
		for (j = 0; j < len - 1 - i; j++) {
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
void Del(int a[], int m) {
	int j = 0;
	for (int i = 0; i<m; i++) {
		if (a[i] != 0) {
			a[j] = a[i];
			j++;
		}
	}
}
void EmbedBlindWatermark(unsigned char *pBmpBuf, int bmpWidth, int bmpHeight, int biBitCount, char *wm)
{

	//char writePath[] = "b.bmp";  //写入图像名，与上层程序合并时注释掉 
	int word = 111;//中文文本
				   //int word=222;//英文文本 
				   //readBmp(readPath);     
				   //printf("width=%d  height=%d biBitCount=%d\n",bmpWidth,bmpHeight,biBitCount);//输出图像的信息  
	int lineByte = (bmpWidth*biBitCount / 8 + 3) / 4 * 4;//每行字节数 
	int  **b = new int *[bmpHeight];//动态创建像素矩阵 
	for (int i = 0; i<bmpHeight; i++) {
		b[i] = new int[lineByte];
	}
	if (biBitCount == 8) { //对于灰度图像	              
		for (int i = 0; i<bmpHeight; i++) {
			for (int j = 0; j<bmpWidth; j++) {
				b[i][j] = *(pBmpBuf + i*lineByte + j);
			}
		}
	}
	if (biBitCount == 24) {//彩色图像
		for (int i = 0; i<bmpHeight; i++) {
			int j1 = 0;
			for (int j = 0; j<bmpWidth; j++) {
				b[i][j] = (*(pBmpBuf + i*lineByte + j1) + *(pBmpBuf + i*lineByte + j1 + 1) + *(pBmpBuf + i*lineByte + j1 + 2)) / 3;
				j1 = j1 + 3;
			}
		}
	}


	int *col_left = new int[bmpHeight];
	int *col_right = new int[bmpHeight];//每像素行 右边界一维数组  
	double *row_per = new double[bmpHeight];//每像素行黑点数所占百分比矩阵 

	int *up = new int[bmpHeight]; //上边界行号 
	int *down = new int[bmpHeight];//下边界行号 
	int rownum1 = 0, rownum2 = 0;
	int black = 255;
	for (int i = 0; i<bmpHeight; i++) {
		int j1 = 0, j = 0;
		int num = 0;
		int colnum = 0;
		//printf("第%d行：",i);
		for (j = 0; j<bmpWidth; j++) {
			if (b[i][j]<black) {
				num = num + 1;
			}
			if (j>0) {
				if ((b[i][j]<black) && (b[i][j - 1] >= black)) {
					if (colnum == 0) {
						col_left[i] = j;
						//printf("left[%d][%d]:%d ",i,colnum,col_left[i][colnum]);		    		        
						colnum++;
					}
				}
				if ((b[i][j] >= black) && (b[i][j - 1]<black)) {
					col_right[i] = j - 1;
				}
			}
		}
		//printf("\n");
		//printf("num=%d\n",num);
		//printf("left:%d ,right:%d",col_left[i][0],col_right[i]);
		int col_width = col_right[i] - col_left[i] + 1;  //文本行实际宽度，分母为每行像素点最左边界与最右边界 
														 //if((col_width>bmpWidth)||(col_width<=10)){ col_width=0;} //限制最低有效行宽	 
		if (col_width>bmpWidth) { col_width = 0; } //限制最低有效行宽	 
												   //printf("文本行实际宽度：%d\n",col_width);
		if ((num == 0) || (col_width == 0)) { row_per[i] = 0; }
		else { row_per[i] = (double)num / col_width; }//每行黑点数占百分比，
													  //printf("平均黑点数：%f\n",row_per[i]);
													  //标记边界 
		if (i>0) {
			if ((row_per[i] == 0) && (row_per[i - 1] != 0)) { //标记i-1为上边界 
															  //for(int j=0;j<bmpWidth;j++){b[i-1][j]=0;}//划线操作 
				up[rownum1] = i - 1;
				//fprintf(fp1,"%d:第%d是上边界\n",rownum1,up[rownum1]);
				rownum1 = rownum1 + 1;
			}
			else if ((row_per[i] != 0) && (row_per[i - 1] == 0)) { //标记i为下边界
																   //for(int j=0;j<bmpWidth;j++){b[i][j]=0;}//划线操作 
				down[rownum2] = i;
				//fprintf(fp1,"%d:第%d是下边界\n",rownum2,down[rownum2]);
				rownum2 = rownum2 + 1;
			}
		}
	}
	delete[] col_left;
	delete[] col_right;
	delete[] row_per;
	//统计每组中每列的黑点数，获得数组col_num[k][j] 
	int  **col_num = new int *[rownum1];//动态创建像素矩阵 
	for (int i = 0; i<rownum1; i++) {
		col_num[i] = new int[bmpWidth];
	}
	for (int k = 0; k<rownum1; k++) {
		for (int j = 0; j<bmpWidth; j++) {
			int num = 0;
			for (int i = down[k]; i <= up[k]; i++) {
				if (b[i][j] <black) {
					num = num + 1;
				}
			}
			col_num[k][j] = num;
			//fprintf(fp1, "%d %d %d ",k,j,col_num[k][j]);
		}
		//fprintf(fp1,"\n");   	 
	}

	/***************************************列识别*********************************/
	//识别每文本字左右边界 
	int *count = new int[rownum1];  //每文本行内每个字的左边界计数数组  
	int count1, count2;//计数 

	int  **left = new int *[rownum1];//动态创建像素矩阵 
	int  **right = new int *[rownum1];
	for (int i = 0; i<rownum1; i++) {
		left[i] = new int[bmpWidth];
		right[i] = new int[bmpWidth];
	}
	//int left[rownum1][bmpWidth];//每文本行左边界数组 
	//int right[rownum1][bmpWidth];//每文本行右边界数组 
	int num = 0;
	for (int k = 0; k<rownum1; k++) {
		count1 = 0; count2 = 0;
		for (int j = 0; j<bmpWidth; j++) {
			if ((j == 0) && (col_num[k][j]>num) && (col_num[k][j + 1]>num)) {
				left[k][count1] = j;
				//printf("left[%d][%d] =%d \n",k,count1,left[k][count1]);
				//for(int i=down[k];i<=up[k];i++){  b[i][j]=0;}//划线操作 
				count1++;
			}
			else if ((j == bmpWidth - 1) && (col_num[k][j]>num) && (col_num[k][j - 1]>num)) {
				right[k][count2] = j;
				//printf("right[%d][%d] =%d  \n",k,count2,right[k][count2]);		
				//for(int i=down[k];i<=up[k];i++){  b[i][j]=0;}//划线操作 
				count2++;
			}
			else if ((j>0) && (j<bmpWidth - 1)) {
				if ((col_num[k][j]>num) && (col_num[k][j - 1] <= num)) { //left:j
					left[k][count1] = j;
					//printf("left[%d][%d] =%d \n",k,count1,left[k][count1]);
					//for(int i=down[k];i<=up[k];i++){  b[i][j]=0;}//划线操作 
					count1++;
				}
				if ((col_num[k][j] <= num) && (col_num[k][j - 1]>num)) {//right：j-1 
					right[k][count2] = j - 1;
					//printf("right[%d][%d] =%d  \n",k,count2,right[k][count2]);		
					//for(int i=down[k];i<=up[k];i++){  b[i][j-1]=0;}//划线操作 
					count2++;
				}
			}
		}
		//fprintf(fp1,"count1=%d ,count2=%d\n",count1,count2);
		count[k] = count1;
	}
	//若左右数组值相等则置0
	int *data = new int[rownum1];
	int *sort_data = new int[rownum1];
	//int data[rownum1],sort_data[rownum1];
	for (int k = 0; k<rownum1; k++) {
		num = 0;
		for (int j = 0; j<count[k]; j++) {
			if (left[k][j] == right[k][j]) {
				left[k][j] = 0;
				right[k][j] = 0;
				num = num + 1;
			}
		}
		data[k] = count[k] - num;
		sort_data[k] = data[k];
	}
	bubble_sort(sort_data, rownum1);//对左边界计数数组排序，取最大值 
	int count_max = sort_data[rownum1 - 1] + 10;//左边界计数最大值，防止计算列边距数据不全 
	printf("count_max=%d \n", count_max);
	if (count_max <= 0) {
		return;
	}
	for (int k = 0; k<rownum1; k++) {  //删除数组内的0 
		int *temp1 = new int[count[k]];
		int *temp2 = new int[count[k]];
		//int temp1[count[k]],temp2[count[k]];
		for (int j = 0; j<count[k]; j++) {
			temp1[j] = left[k][j];
			temp2[j] = right[k][j];
		}
		Del(temp1, count[k]);
		Del(temp2, count[k]);
		for (int j = 0; j<data[k]; j++) {
			left[k][j] = temp1[j];
			right[k][j] = temp2[j];
		}
		delete[] temp1;
		delete[] temp2;
	}

	int  **col_dis = new int *[rownum1];//动态创建像素矩阵 
	for (int i = 0; i<rownum1; i++) {
		col_dis[i] = new int[count_max];
	}

	int *sort_cd = new int[count_max];
	int *cd_avg = new int[rownum1];
	int cdavg1 = 0, cdavg = 0;
	/*******************英文文本优化字识别************************/
	if (word == 222) { //获得文本字间距 		
		for (int k = 0; k<rownum1; k++) {
			int i;
			for (i = 1; i<data[k]; i++) {
				//printf("left:%d ,right:%d\n",left[k][i],right[k][i]);
				col_dis[k][i - 1] = left[k][i] - right[k][i - 1] - 1;
				sort_cd[i - 1] = col_dis[k][i - 1];
				//printf("%d \n",col_dis[k][i-1]); 
			}
			//printf("\n");
			bubble_sort(sort_cd, i - 1);
			cd_avg[k] = sort_cd[(i - 1) / 2];
			printf("cd_avg[%d]=%d \n", k, cd_avg[k]);
		}
		bubble_sort(cd_avg, rownum1 - 1);
		cdavg1 = cd_avg[(rownum1 - 1) / 2];
		printf("cdavg=%d \n", cdavg1);
		for (int k = 0; k<rownum1; k++) {
			//printf("第%d行：",k);	
			if (cd_avg[k]>cdavg) {
				cdavg = cd_avg[k];
			}
			else {
				cdavg = cdavg1;
			}
			int num = 0;
			for (int i = 0; i<data[k] - 1; i++) {
				if (col_dis[k][i] < (2 * cdavg - 1)) {
					left[k][i + 1] = 0;
					right[k][i] = 0;
					num = num + 1;
				}
				//printf("left:%d ,right:%d\n",left[k][i],right[k][i]);			
			}
			//printf("\n");
			count[k] = data[k] - num;
		}
		for (int k = 0; k<rownum1; k++) {  //删除数组内的0 
										   //printf("第%d行：",k);
			int *temp1 = new int[data[k]];
			int *temp2 = new int[data[k]];
			//int temp1[data[k]],temp2[data[k]];
			for (int j = 0; j<data[k]; j++) {
				temp1[j] = left[k][j];
				temp2[j] = right[k][j];
			}
			Del(temp1, data[k]);
			Del(temp2, data[k]);
			for (int j = 0; j<count[k]; j++) {
				//printf("第%d个字：",j);
				left[k][j] = temp1[j];
				//printf("left:%d ",left[k][j]);
				right[k][j] = temp2[j];
				//printf("right:%d ",right[k][j]);			
			}
			//printf("\n"); 
			delete[] temp1;
			delete[] temp2;
		}
	}

	/*****************************中文文本字识别**********************************/
	if (word == 111) {
		//获得文本平均字宽 
		int **col_w = new int *[rownum1];
		for (int i = 0; i<rownum1; i++) {
			col_w[i] = new int[count_max];
		}

		int *sort_colw = new int[count_max];//字宽数组 
		int *col_avg = new int[rownum1];
		int *sort_colavg = new int[rownum1];//每文本行平均字宽数组 
		for (int k = 0; k<rownum1; k++) {
			int i;
			for (i = 0; i<data[k]; i++) {
				col_w[k][i] = right[k][i] - left[k][i] + 1;
				sort_colw[i] = col_w[k][i];
			}
			bubble_sort(sort_colw, i);
			col_avg[k] = sort_colw[i / 2];
			sort_colavg[k] = sort_colw[i / 2];
			//printf("平均字宽：%d \n",col_avg[k]);	
		}
		bubble_sort(sort_colavg, rownum1);
		int colavg1 = sort_colavg[rownum1 / 2];
		printf("总平均字宽：%d \n", colavg1);
		int colavg = 0;

		//删除英文字母:连续六个字宽小于阈值，则认为其是英文字母，去除中间左右边界 
		for (int k = 0; k<rownum1; k++) {
			if (col_avg[k] >= colavg1) {
				colavg = col_avg[k];
			}
			else {
				colavg = colavg1;
			}
			double div = (double)colavg / 2 + 2;
			//printf("%d:div=%f \n",k,div);			
			for (int i = 2; i<data[k] - 3; i++) {
				if (col_w[k][i - 2] <= div&&col_w[k][i - 1] <= div &&col_w[k][i] <= div&&col_w[k][i + 1] <= div&&col_w[k][i + 2] <= div && col_w[k][i + 3] <= div) {
					for (int j = i - 2; j<i + 2; j++) {
						//printf("%d %d left=%d,right=%d \n",k,j,left[k][j],right[k][j]);
						int dis = left[k][j + 1] - right[k][j] - 1;
						//printf("%d:dis=%f \n",j,dis);
						if (dis <= 3) {
							int dis1 = 1;
							for (int p = down[k]; p <= up[k]; p++) {
								for (int s = right[k][j] - dis1; s <= left[k][j + 1] + dis1; s++) {
									if (biBitCount == 8) {
										pBmpBuf[p*lineByte + s] = 255;
									}
									if (biBitCount == 24) {
										pBmpBuf[p*lineByte + s * 3] = 255;
										pBmpBuf[p*lineByte + s * 3 + 1] = 255;
										pBmpBuf[p*lineByte + s * 3 + 2] = 255;
									}
								}
							}
						}
					}
				}
			}
			for (int i = 2; i<data[k] - 2; i++) {
				if (col_w[k][i - 2] <= div&&col_w[k][i - 1] <= div &&col_w[k][i] <= div&&col_w[k][i + 1] <= div&&col_w[k][i + 2] <= div && col_w[k][i + 3] <= div) {
					left[k][i - 2] = 0; left[k][i - 1] = 0; left[k][i] = 0; left[k][i + 1] = 0; left[k][i + 2] = 0; left[k][i + 3] = 0;
					right[k][i - 2] = 0; right[k][i - 1] = 0; right[k][i] = 0; right[k][i + 1] = 0; right[k][i + 2] = 0; right[k][i + 3] = 0;
				}
			}
			num = 0;
			for (int i = 0; i<data[k]; i++) {
				if (left[k][i] == 0) {
					num = num + 1;
				}
			}
			count[k] = data[k] - num;
			//printf("k=%d ,count=%d\n",k,count[k]);
		}
		for (int k = 0; k<rownum1; k++) {  //删除数组内的0 
										   //printf("第%d行：",k);
			int *temp1 = new int[data[k]];
			int *temp2 = new int[data[k]];
			for (int j = 0; j<data[k]; j++) {
				temp1[j] = left[k][j];
				temp2[j] = right[k][j];
			}
			Del(temp1, data[k]);
			Del(temp2, data[k]);
			for (int j = 0; j<count[k]; j++) {
				//printf("第%d个字：",j);
				left[k][j] = temp1[j];
				//printf("left:%d ",left[k][j]);
				right[k][j] = temp2[j];
				//printf("right:%d ",right[k][j]);
			}
			for (int j = count[k]; j<data[k]; j++) {
				left[k][j] = 0;
				right[k][j] = 0;
			}
			data[k] = count[k];
			//printf("k=%d ,data=%d\n",k,data[k]);
			delete[] temp1;
			delete[] temp2;
		}
		for (int k = 0; k<rownum1; k++) {
			int i;
			for (i = 0; i<data[k]; i++) {
				col_w[k][i] = right[k][i] - left[k][i] + 1;
				sort_colw[i] = col_w[k][i];
			}
			bubble_sort(sort_colw, i);
			col_avg[k] = sort_colw[i / 2];
			sort_colavg[k] = sort_colw[i / 2];
			//printf("平均字宽：%d \n",col_avg[k]);	
		}
		bubble_sort(sort_colavg, rownum1);
		colavg1 = sort_colavg[rownum1 / 2];


		//矫正边界数组一,先分开误判为一个字的两个字 		
		for (int k = 0; k<rownum1; k++) {
			if (col_avg[k] >= colavg1) {
				colavg = col_avg[k];
			}
			else {
				colavg = colavg1;
			}
			int num1 = 0;
			for (int i = 0; i<data[k]; i++) {
				//printf("left=%d  right=%d\n",left[k][i],right[k][i]);
				col_w[k][i] = right[k][i] - left[k][i] + 1;
				double dif = (double)col_w[k][i] / colavg;
				if (dif >= 1.5) { //若判断为是两字合并，则寻找中间值与列黑点数最小值
					num1 = num1 + 1;
					int lefti = left[k][i] + 5;
					int righti = right[k][i] - 5;
					int leftj = 0, rightj = 0;
					int *temp1 = new int[righti - lefti + 1];
					num = 0;
					for (int j = lefti; j<righti; j++) {
						temp1[num] = col_num[k][j];
						num = num + 1;
					}
					int bound = temp1[0]; //两字中间列黑点数最小值 
					for (int j = 0; j<num; j++) {
						if (bound >= temp1[j]) {
							bound = temp1[j];
						}
					}
					delete[] temp1;
					//printf("min=%d \n",bound); 
					int mid = (righti + lefti) / 2; //两字列中间值 
					if (col_num[k][mid] == bound) { //若两字列中间值为黑点数最小值，则向左向右寻找不是最小值的值作为新增的左右边界 
						for (int j = 0; j<(mid - lefti + 1); j++) {
							int s = mid - j;
							if (col_num[k][s] != bound) {
								rightj = s;
								break;
							}
						}
						for (int j = 0; j<(righti - mid + 1); j++) {
							int s = mid + j;
							if (col_num[k][s] != bound) {
								leftj = s;
								break;
							}
						}
					}
					else { //若两字中间值不是黑点数最小值，则查找最小值位置，将其左右作为新增左右边界 
						for (int j = lefti; j <= righti; j++) {
							if (col_num[k][j] == bound) {
								leftj = j + 1;
								rightj = j - 1;
								break;
							}
						}
					}
					for (int j = data[k]; j>i + 1; j--) { // 插入新增左边界 
						left[k][j] = left[k][j - 1];
					}
					left[k][i + 1] = leftj;
					for (int j = data[k]; j>i; j--) { //插入新增右边界 
						right[k][j] = right[k][j - 1];
					}
					right[k][i] = rightj;
				}
			}
			data[k] = data[k] + num1;
		}
		for (int k = 0; k<rownum1; k++) {
			int i;
			for (i = 0; i<data[k]; i++) {
				col_w[k][i] = right[k][i] - left[k][i] + 1;
				sort_colw[i] = col_w[k][i];
			}
			bubble_sort(sort_colw, i);
			col_avg[k] = sort_colw[i / 2];
			sort_colavg[k] = sort_colw[i / 2];
		}
		bubble_sort(sort_colavg, rownum1);
		colavg1 = sort_colavg[rownum1 / 2];
		printf("总平均字宽：%d \n", colavg1);
		//矫正左右边界数组二，合并左右结构字 		
		for (int k = 0; k<rownum1; k++) {
			if (col_avg[k] >= colavg1) {
				colavg = col_avg[k];
			}
			else {
				colavg = colavg1;
			}
			int th1 = colavg / 2 + 5;
			int th2 = colavg - 3;
			printf("th1=%d  ,th2=%d\n", th1, th2);
			for (int j = 0; j<data[k] - 1; j++) { //判断i与i+1的大小是否构成左右结构字，若是且字间距小于等于5则合并，中间的边界置0
				if (((col_w[k][j] <= th1) && (col_w[k][j + 1] <= th2)) || ((col_w[k][j] <= th2) && (col_w[k][j + 1] <= th1))) {
					int dis = left[k][j + 1] - right[k][j] - 1;
					double dis2 = (double)colavg / 10 + 1; //对dis四舍五入取整 
					int dis3 = dis2;
					if (dis2 - dis3 >= 0.5) {
						dis3 = dis3 + 1;
					}
					//printf("j=%d,dis=%d ,dis3=%d\n",j,dis,dis3);
					if (dis < dis3) { //若两字合，则将中间边界置0 
						left[k][j + 1] = 0;
						right[k][j] = 0;
						//col_w[k][j+1]= col_w[k][j]+col_w[k][j+1]+dis;
					}
					if (dis <= (dis3 + 3) && dis >= (dis3)) {//若相差范围在dis3-dis3+3，则扩大中间范围，更新左右边界数组 
						for (int p = down[k]; p <= up[k]; p++) {
							for (int s = right[k][j] - 1; s <= left[k][j + 1] + 1; s++) {
								if (biBitCount == 8) {
									pBmpBuf[p*lineByte + s] = 255;
								}
								if (biBitCount == 24) {
									pBmpBuf[p*lineByte + s * 3] = 255;
									pBmpBuf[p*lineByte + s * 3 + 1] = 255;
									pBmpBuf[p*lineByte + s * 3 + 2] = 255;
								}
							}
						}
						right[k][j] = right[k][j] - 2;
						left[k][j + 1] = left[k][j + 1] + 2;
					}
				}
			}
			num = 0;
			for (int i = 0; i<data[k]; i++) {
				if (left[k][i] == 0) {
					num = num + 1;
				}
			}
			count[k] = data[k] - num;
			//printf("k=%d ,count=%d\n",k,count[k]);
		}
		for (int k = 0; k<rownum1; k++) {  //删除数组内的0 
										   //printf("第%d行：",k);
			int *temp1 = new int[data[k]];
			int *temp2 = new int[data[k]];
			for (int j = 0; j<data[k]; j++) {
				temp1[j] = left[k][j];
				temp2[j] = right[k][j];
			}
			Del(temp1, data[k]);
			Del(temp2, data[k]);
			for (int j = 0; j<count[k]; j++) {
				//printf("第%d个字：",j);
				left[k][j] = temp1[j];
				//printf("left:%d ",left[k][j]);
				right[k][j] = temp2[j];
				//printf("right:%d ",right[k][j]);
			}
			for (int j = count[k]; j<data[k]; j++) {
				left[k][j] = 0;
				right[k][j] = 0;
			}
			delete[] temp1;
			delete[] temp2;
		}
		for (int k = 0; k<rownum1; k++) { //更新字宽数组，获取平均字宽 
			int i;
			for (i = 0; i<count[k]; i++) {
				col_w[k][i] = right[k][i] - left[k][i] + 1;
				sort_colw[i] = col_w[k][i];
			}
			bubble_sort(sort_colw, i);
			col_avg[k] = sort_colw[i / 2];
			sort_colavg[k] = sort_colw[i / 2];
		}
		bubble_sort(sort_colavg, rownum1);
		colavg1 = sort_colavg[rownum1 / 2];
		printf("总平均字宽：%d \n", colavg1);

		delete[] data;
		delete[] sort_data;

		//矫正边界数组三,矫正被误判为一个字的两个字 
		for (int k = 0; k<rownum1; k++) {
			//printf("%d:data[k]=%d ",k,count[k]);
			//printf("col_avg=%d ",col_avg[k]);
			if (col_avg[k] >= colavg1) {
				colavg = col_avg[k];
			}
			else {
				colavg = colavg1;
			}
			//printf("colavg=%d \n",colavg);
			for (int i = 0; i<count[k]; i++) {
				col_w[k][i] = right[k][i] - left[k][i] + 1;
				double dif = (double)col_w[k][i] / colavg;
				if (dif >= 1.5) { //若判断为是两字合并，则寻找中间值与列黑点数最小值 
								  //printf("col_w=%d ",col_w[k][i]);		
					int lefti = left[k][i] + 5;
					int righti = right[k][i] - 5;
					//printf("lefti=%d  righti=%d",lefti,righti);
					int leftj = 0, rightj = 0;
					int *temp1 = new int[righti - lefti + 1];
					num = 0;
					for (int j = lefti; j<righti; j++) {
						temp1[num] = col_num[k][j];
						num = num + 1;
					}
					int bound = temp1[0]; //两字中间列黑点数最小值 
					for (int j = 0; j<num; j++) {
						if (bound >= temp1[j]) {
							bound = temp1[j];
						}
					}
					delete[] temp1;
					//printf("bound=%d \n",bound); 
					int mid = (righti + lefti) / 2; //两字列中间值 
													//printf("mid=%d\n",mid);
					if (col_num[k][mid] == bound) { //若两字列中间值为黑点数最小值，则向左向右寻找不是最小值的值作为新增的左右边界 
													//printf("mid==bound\n");
						for (int j = mid; j >= lefti; j--) {
							if (rightj == 0 && col_num[k][j] != bound) {
								rightj = j;
								break;
							}
						}
						for (int j = mid; j <= righti; j++) {
							if (leftj == 0 && col_num[k][j] != bound) {
								leftj = j;
								break;
							}
						}
					}
					else { //若两字中间值不是黑点数最小值，则查找最小值位置，将其左右作为新增左右边界 
						   //printf("mid!=bound\n");
						for (int j = mid; j >= lefti; j--) {
							if (leftj == 0 && col_num[k][j] == bound) {
								leftj = j + 1;
								break;
							}
						}
						for (int j = leftj - 1; j >= lefti; j--) {
							if (rightj == 0 && col_num[k][j] != bound) {
								rightj = j;
								break;
							}
						}
						//printf("leftj=%d ,rightj=%d\n",leftj,rightj);
						if ((rightj - left[k][i] + 1)<(colavg / 2 + 2)) {
							//printf("向右找：\n");
							rightj = 0; leftj = 0;
							for (int j = mid; j <= righti; j++) {
								if (rightj == 0 && col_num[k][j] == bound) {
									rightj = j - 1;
									break;
								}
							}
							for (int j = rightj + 1; j <= righti; j++) {
								if (leftj == 0 && col_num[k][j] != bound) {
									leftj = j;
									break;
								}
							}

						}
					}
					//printf("leftj=%d ,right=%d\n",leftj,rightj);
					for (int j = count[k]; j>i + 1; j--) { // 插入新增左边界 
						left[k][j] = left[k][j - 1];
					}
					left[k][i + 1] = leftj;
					for (int j = count[k]; j>i; j--) { //插入新增右边界 
						right[k][j] = right[k][j - 1];
					}
					right[k][i] = rightj;
					count[k] = count[k] + 1;

					//printf("count[k]=%d\n",count[k]);									
				}
			}
		}
		for (int i = 0; i<rownum1; i++) {
			delete[] col_num[i];
			//printf("%d:clean success!!\n",i);       
		}
		delete[] col_num;
		//求字间距的平均值，限制水印嵌入位置
		//int sort_cdavg[rownum1];//const array size
		int *sort_cdavg = new int[rownum1];
		for (int k = 0; k<rownum1; k++) {
			int i;
			for (i = 1; i<count[k]; i++) {
				col_dis[k][i - 1] = left[k][i] - right[k][i - 1] - 1;
				sort_cd[i - 1] = col_dis[k][i - 1];
				//printf("%d ",col_dis[k][i-1]); 
			}
			//printf("\n");
			bubble_sort(sort_cd, i - 1);
			cd_avg[k] = sort_cd[(i - 1) / 2];
			sort_cdavg[k] = cd_avg[k];
			printf("cd_avg[%d]=%d \n", k, cd_avg[k]);
		}
		bubble_sort(sort_cdavg, rownum1 - 1);
		cdavg1 = sort_cdavg[(rownum1 - 1) / 2];
		delete[]sort_cdavg;
		printf("cdavg1=%d \n", cdavg1);

		for (int i = 0; i<rownum1; i++) {
			delete[] col_dis[i];
		}
		delete[] col_dis;
		delete[] sort_cd;
		/*
		for(int k=0;k<rownum1;k++){
		num=0;
		printf("第%d行：\n",k);
		for(int i=0;i<count[k];i++){
		num=num+1;
		printf("NUM=%d ,left=%d ,right=%d\n",num,left[k][i],right[k][i]);
		}
		printf("NUM=%d \n",num);
		printf("\n");
		}
		*/
		//更新字宽数组，若字宽小于阈值，则左右边界置0 
		for (int k = 0; k<rownum1; k++) {
			int i;//printf("data[k]=%d ",data[k]);
			for (i = 0; i<count[k]; i++) {
				col_w[k][i] = right[k][i] - left[k][i] + 1;
				int dis = left[k][i + 1] - right[k][i] - 1;
				//printf("col_w=%d  dis=%d",col_w[k][i],dis);	
				sort_colw[i] = col_w[k][i];
			}
			bubble_sort(sort_colw, i);
			col_avg[k] = sort_colw[i / 2];
			sort_colavg[k] = sort_colw[i / 2];
		}
		bubble_sort(sort_colavg, rownum1);
		colavg1 = sort_colavg[rownum1 / 2];
		printf("总平均字宽：%d \n", colavg1);

		delete[] sort_colw;
		delete[] sort_colavg;

		for (int k = 0; k<rownum1; k++) {
			if (col_avg[k] >= colavg1) {
				colavg = col_avg[k];
			}
			else {
				colavg = colavg1;
			}
			for (int i = 1; i<count[k]; i++) {
				int dis1 = left[k][i] - right[k][i - 1] - 1;
				if (dis1 <= 2) {
					for (int p = down[k]; p <= up[k]; p++) {
						for (int q = right[k][i - 1] - 1; q <= left[k][i] + 1; q++) {
							if (biBitCount == 8) {
								pBmpBuf[p*lineByte + q] = 255;
							}
							if (biBitCount == 24) {
								pBmpBuf[p*lineByte + q * 3] = 255;
								pBmpBuf[p*lineByte + q * 3 + 1] = 255;
								pBmpBuf[p*lineByte + q * 3 + 2] = 255;
							}
						}
					}
				}
			}
			for (int i = 0; i<count[k]; i++) {
				col_w[k][i] = right[k][i] - left[k][i] + 1;
				if (col_w[k][i]<(colavg / 2 + 2)) {
					left[k][i] = 0;
					right[k][i] = 0;
				}
			}
		}
		for (int i = 0; i<rownum1; i++) {
			delete[] col_w[i];
		}
		delete[]col_w;
		delete[] col_avg;
	}


	/*
	//新列边界划线操作
	for(int k=0;k<rownum1;k++){
	for(int s=0;s<count[k];s=s+1){
	int s1=left[k][s];
	int s2=right[k][s];
	//if(s1!=0 && s2!=0 ){
	for(int  i=down[k];i<=up[k];i++){
	for( int j=0;j<bmpWidth;j++){
	if (biBitCount == 8){
	pBmpBuf[i*lineByte + s1]=0;
	pBmpBuf[i*lineByte + s2]=0;
	}
	if (biBitCount == 24){
	pBmpBuf[i*lineByte + s1*3]=0;
	pBmpBuf[i*lineByte + s1*3 + 1] = 0;
	pBmpBuf[i*lineByte + s1*3 + 2] =0;
	pBmpBuf[i*lineByte + s2*3]=0;
	pBmpBuf[i*lineByte + s2*3 + 1] = 0;
	pBmpBuf[i*lineByte + s2*3 + 2] =0;
	}

	}
	}
	//}
	}
	}
	*/

	//**************************************字移编码部分************************* 
	for (int i = 0; wm[i]; i++) {
		printf("%d=%d \n", i, wm[i]);
	}
	int a[1000];
	num = 0;
	for (int i = 0; wm[i]; i++) {
		int waternum = wm[i];
		int a1[10], temp[10];//保存十进制waternum转为的二进制序列 ,从后往前读 
		int water_len = 0;
		int r = 0;
		while (waternum)
		{
			a1[water_len] = waternum % 2;
			waternum /= 2;
			water_len++;
		}
		for (int i = 0; i<water_len; i++) {
			temp[water_len - i - 1] = a1[i];
		}
		for (int i = 0; i<water_len; i++) {
			a[num] = temp[i];
			num++;
		}
	}

	for (int i = 0; i<num; i++) {
		printf("%d", a[i]);
	}
	printf("\n");
	int water_len = num;
	printf("water_len=%d\n", water_len);
	int r = 0;
	for (int k = 0; k<rownum1; k++) {
		printf("*****************第%d行：********************\n", k);
		int oppo = 0;
		cdavg = 0;
		printf("cd_avg[k]=%d \n", cd_avg[k]);
		if (cd_avg[k] >= cdavg1) {
			cdavg = cd_avg[k];
		}
		else {
			cdavg = cdavg1;
		}
		printf("cdavg=%d\n", cdavg);
		cdavg = cdavg * 5;//若字间距小于平均字间距的8倍，则可嵌入 
		printf("cdavg=%d\n", cdavg);
		for (int s = 0; s<count[k] - 1; s++) {
			printf("第%d个字：左边界是：%d ，右边界是：%d \n", s, left[k][s], right[k][s]);
			if (((s - 1) % 2 == 0) && (right[k][s - 1] != 0)) { //前一个右边界可识别 
				if ((s % 2 != 0) && (left[k][s] != 0) && (right[k][s] != 0) && (left[k][s + 1] != 0)) {  //当前字左右边界均可识别，后一个字左边界可识别 
					int dis1 = left[k][s] - right[k][s - 1] - 1;
					int dis2 = left[k][s + 1] - right[k][s] - 1;
					printf("r=%d  ,dis1=%d ,dis2=%d\n", r, dis1, dis2);
					//double div=0;
					int flag = 0;
					if (word = 111) {
						if (dis1<cdavg && dis2<cdavg) {
							flag = 1;
						}
					}
					//printf("div=%f\n", div);
					if ((flag == 1) || word == 222) {
						oppo = oppo + 1;
						printf("第%d个字: ", s);
						if (a[r%water_len] == 0) { //嵌入0：左<右 
							printf("嵌入0\n");
							int dif = 0;//若不合下面两个条件，则不动 
							if (dis1 <= dis2 && dis2 - dis1 <= 2) {//若左比右小1或左右相等，则左移 
								dif = dis2 - (dis1 + dis2) / 2 + 1;
							}
							else if (dis1>dis2) {//若左大于右，则左移 
								dif = dis1 - (dis1 + dis2) / 2 + 1;
							}
							if (dif <= 1) {
								dif = 2;
							}
							for (int i = down[k]; i <= up[k]; i++) { //左移 dif 
								for (int j = (left[k][s] - dif); j <= (right[k][s] - dif); j++) {
									if (biBitCount == 8) {
										pBmpBuf[i*lineByte + j] = pBmpBuf[i*lineByte + j + dif];
									}
									if (biBitCount == 24) {
										pBmpBuf[i*lineByte + j * 3] = pBmpBuf[i*lineByte + (j + dif) * 3];
										pBmpBuf[i*lineByte + j * 3 + 1] = pBmpBuf[i*lineByte + (j + dif) * 3 + 1];
										pBmpBuf[i*lineByte + j * 3 + 2] = pBmpBuf[i*lineByte + (j + dif) * 3 + 2];
									}
									//b[i][j]=b[i][j+dif];
								}
								for (int j = (right[k][s] - dif + 1); j <= (right[k][s]); j++) {

									//b[i][j]=255;
									if (biBitCount == 8) {
										pBmpBuf[i*lineByte + j] = 255;
									}
									if (biBitCount == 24) {
										pBmpBuf[i*lineByte + j * 3] = 255;
										pBmpBuf[i*lineByte + j * 3 + 1] = 255;
										pBmpBuf[i*lineByte + j * 3 + 2] = 255;
									}
								}
							}
							printf("左边界：%d ，右边界:%d\n ", (left[k][s] - dif), (right[k][s] - dif));
							printf("左移成功：dif=%d\n", dif);
						}
						if (a[r%water_len] == 1) {//嵌入1：左>右
							printf("嵌入1\n");
							int dif = 0;//若不合下面两个条件，则不动 
							if (dis1 >= dis2 && dis1 - dis2 <= 2) {//若左比右大1或左右相等，则右移 
								dif = dis1 - (dis1 + dis2) / 2 + 1;

							}
							else if (dis1<dis2) {//若左小于右，则右移 
								dif = dis2 - (dis1 + dis2) / 2 + 1;

							}
							if (dif <= 1) {
								dif = 2;
							}
							if (biBitCount == 8) {
								int cm = up[k] - down[k] + 1; //中间矩阵高 
								int cn = right[k][s] - left[k][s] + 1;//中间矩阵宽 
								int **c = new int *[cm]; //中间矩阵 
								for (int i = 0; i<cm; i++) {
									c[i] = new int[cn];
								}
								int cm1 = 0, cn1;
								for (int i = down[k]; i <= up[k]; i++) {  //矩阵整体后移需要中间数组协助 
									cn1 = 0;
									for (int j = left[k][s]; j <= right[k][s]; j++) {
										c[cm1][cn1] = b[i][j];
										cn1++;
									}
									cn1 = 0;
									for (int j = (left[k][s] + dif); j <= (right[k][s] + dif); j++) {
										//b[i][j]=c[cm1][cn1];											
										pBmpBuf[i*lineByte + j] = c[cm1][cn1];
										cn1++;
									}
									for (int j = (left[k][s]); j<(left[k][s] + dif); j++) {
										pBmpBuf[i*lineByte + j] = 255;
									}
									cm1++;
								}
								for (int i = 0; i<cm; i++) {
									delete[] c[i];
								}
								delete[] c;
								printf("左边界：%d ，右边界:%d\n ", (left[k][s] + dif), (right[k][s] + dif));
								printf("右移成功,dif=%d\n", dif);
							}
							if (biBitCount == 24) {
								int cm = (up[k] - down[k] + 1) * 3; //中间矩阵高 
								int cn = (right[k][s] - left[k][s] + 1) * 3;//中间矩阵宽 
								int **c1 = new int *[cm]; //中间矩阵 
								int **c2 = new int *[cm]; //中间矩阵
								int **c3 = new int *[cm]; //中间矩阵
								for (int i = 0; i<cm; i++) {
									c1[i] = new int[cn];
									c2[i] = new int[cn];
									c3[i] = new int[cn];
								}
								int cm1 = 0, cn1;
								for (int i = down[k]; i <= up[k]; i++) {  //矩阵整体后移需要中间数组协助 
									cn1 = 0;
									for (int j = left[k][s]; j <= right[k][s]; j++) {
										c1[cm1][cn1] = pBmpBuf[i*lineByte + j * 3];
										c2[cm1][cn1] = pBmpBuf[i*lineByte + j * 3 + 1];
										c3[cm1][cn1] = pBmpBuf[i*lineByte + j * 3 + 2];
										cn1++;
									}
									cn1 = 0;
									for (int j = (left[k][s] + dif); j <= (right[k][s] + dif); j++) {
										//b[i][j]=c[cm1][cn1];
										pBmpBuf[i*lineByte + j * 3] = c1[cm1][cn1];
										pBmpBuf[i*lineByte + j * 3 + 1] = c2[cm1][cn1];
										pBmpBuf[i*lineByte + j * 3 + 2] = c3[cm1][cn1];
										cn1++;
									}
									for (int j = (left[k][s]); j<(left[k][s] + dif); j++) {
										pBmpBuf[i*lineByte + j * 3] = 255;
										pBmpBuf[i*lineByte + j * 3 + 1] = 255;
										pBmpBuf[i*lineByte + j * 3 + 2] = 255;
									}
									cm1++;
								}
								for (int i = 0; i<cm; i++) {
									delete[] c1[i];
									delete[] c2[i];
									delete[] c3[i];
								}
								delete[] c1;
								delete[] c2;
								delete[] c3;
								printf("左边界：%d ，右边界:%d\n ", (left[k][s] + dif), (right[k][s] + dif));
								printf("右移成功,dif=%d\n", dif);
							}
						}
						r = r + 1;
					}
				}
			}
		}
		printf("oppo=%d\n", oppo);
	}
	printf("r=%d\n", r);
	printf("cdavg=%d\n", cdavg);

	delete[]count;
	for (int i = 0; i<rownum1; i++) {
		delete[] left[i];
		delete[] right[i];
	}
	delete[] left;
	delete[] right;
	delete[] cd_avg;
	//************************行移编码部分************************************

	//统计文本行间距，寻找标准行距 
	int *row_dis = new int[rownum1]; //int copy_rowdis[rownum1];//行间距数组
	for (int i = 0; i<rownum1; i++) {
		if (i == 0) {
			row_dis[i] = down[i];
		}
		if (i>0) {
			row_dis[i] = down[i] - up[i - 1] - 1;//down、up所存行号均有黑点，计算行距应减一 
		}
	}
	//获取行移嵌入内容 
	int disavg = water_len;
	int row[5], row2[5];
	int row1 = 0;
	while (disavg)
	{
		row[row1] = disavg % 2;
		disavg /= 2;
		row1++;
	}
	printf("row1=%d\n", row1);
	if (row1<4) {
		int dif = 4 - row1;
		for (int i = 0; i<dif; i++) {
			row[row1] = 0;
			row1++;
		}
	}
	for (int i = 0; i<row1; i++) {
		printf("%d", row[i]);
	}
	printf("\n");
	num = 0;
	for (int i = row1 - 1; i >= 0; i--) {
		row2[num] = row[i];
		num = num + 1;
	}
	for (int i = 0; i<num; i++) {
		printf("%d", row2[i]);
	}
	printf("\n");
	//printf("row1=%d ,num=%d\n",row1,num);
	// 嵌入水印
	int **o1 = new int *[100];//每文本行像素矩阵 副本 
	int **o2 = new int *[100];
	int **o3 = new int *[100];
	for (int i = 0; i<100; i++) {
		o1[i] = new int[bmpWidth];
		o2[i] = new int[bmpWidth];
		o3[i] = new int[bmpWidth];
	}

	int r1 = 0;
	for (int k = 0; k<rownum1 - 1; k++) {
		double div = 0;
		if (row_dis[k] >= row_dis[k + 1]) {
			div = (double)row_dis[k] / row_dis[k + 1];
		}
		else {
			div = (double)row_dis[k + 1] / row_dis[k];
		}
		if ((k >= 1) && (k % 2 != 0) && (k<(rownum1 - 1)) && (div <= 2)) {
			if (row2[r1%row1] == 0) {//嵌入0：下<上 
				printf("嵌入0\n");
				int dis = 0;
				if (row_dis[k] <= row_dis[k + 1] && row_dis[k + 1] - row_dis[k]<2) {//若下比上小2以下，则下移 
					dis = row_dis[k + 1] - (row_dis[k] + row_dis[k + 1]) / 2 + 2;
				}
				else if (row_dis[k]>row_dis[k + 1]) {//若下大于上，则下移 
					dis = row_dis[k] - (row_dis[k] + row_dis[k + 1]) / 2 + 2;
				}
				for (int i = down[k]; i <= up[k]; i++) {
					for (int j = 0; j<bmpWidth; j++) {
						//b[i-dis][j]=b[i][j];
						if (biBitCount == 8) {
							pBmpBuf[(i - dis)*lineByte + j] = pBmpBuf[i*lineByte + j];
						}
						if (biBitCount == 24) {
							pBmpBuf[(i - dis)*lineByte + j * 3] = pBmpBuf[i*lineByte + j * 3];
							pBmpBuf[(i - dis)*lineByte + j * 3 + 1] = pBmpBuf[i*lineByte + j * 3 + 1];
							pBmpBuf[(i - dis)*lineByte + j * 3 + 2] = pBmpBuf[i*lineByte + j * 3 + 2];
						}
					}
				}
				for (int i = (up[k] - dis + 1); i <= up[k]; i++) {
					for (int j = 0; j<bmpWidth; j++) {
						//b[i][j]=255;
						if (biBitCount == 8) {
							pBmpBuf[i*lineByte + j] = 255;
						}
						if (biBitCount == 24) {
							pBmpBuf[i*lineByte + j * 3] = 255;
							pBmpBuf[i*lineByte + j * 3 + 1] = 255;
							pBmpBuf[i*lineByte + j * 3 + 2] = 255;
						}
					}
				}
			}
			if (row2[r1%row1] == 1) {//嵌入1：下>上 
				printf("嵌入1\n");
				int dis = 0;

				if (row_dis[k] >= row_dis[k + 1] && row_dis[k] - row_dis[k + 1]<2) {//若下比上大2以下，则上移 
					dis = row_dis[k] - (row_dis[k] + row_dis[k + 1]) / 2 + 2;
				}
				else if (row_dis[k]<row_dis[k + 1]) {//若下小于上，则上移 
					dis = row_dis[k + 1] - (row_dis[k] + row_dis[k + 1]) / 2 + 2;
				}
				printf("%d  %d  %d\n", row_dis[k], row_dis[k + 1], dis);
				int om = 0, on;
				if (biBitCount == 8) {
					for (int i = down[k]; i <= up[k]; i++) {
						on = 0;
						for (int j = 0; j<bmpWidth; j++) {
							o1[om][on] = pBmpBuf[i*lineByte + j];
							on++;
						}
						om++;
					}
					om = 0;
					for (int i = (down[k] + dis); i <= (up[k] + dis); i++) {
						on = 0;
						for (int j = 0; j<bmpWidth; j++) {
							pBmpBuf[i*lineByte + j] = o1[om][on];
							on++;
						}
						om++;
					}
					for (int i = down[k]; i<(down[k] + dis); i++) {
						for (int j = 0; j<bmpWidth; j++) {
							pBmpBuf[i*lineByte + j] = 255;
						}
					}
				}
				if (biBitCount == 24) {
					for (int i = down[k]; i <= up[k]; i++) {
						on = 0;
						for (int j = 0; j<bmpWidth; j++) {
							o1[om][on] = pBmpBuf[i*lineByte + j * 3];
							o2[om][on] = pBmpBuf[i*lineByte + j * 3 + 1];
							o3[om][on] = pBmpBuf[i*lineByte + j * 3 + 2];
							on++;
						}
						om++;
					}
					om = 0;
					for (int i = (down[k] + dis); i <= (up[k] + dis); i++) {
						on = 0;
						for (int j = 0; j<bmpWidth; j++) {
							pBmpBuf[i*lineByte + j * 3] = o1[om][on];
							pBmpBuf[i*lineByte + j * 3 + 1] = o2[om][on];
							pBmpBuf[i*lineByte + j * 3 + 2] = o3[om][on];
							on++;
						}
						om++;
					}
					for (int i = down[k]; i<(down[k] + dis); i++) {
						for (int j = 0; j<bmpWidth; j++) {
							pBmpBuf[i*lineByte + j * 3] = 255;
							pBmpBuf[i*lineByte + j * 3 + 1] = 255;
							pBmpBuf[i*lineByte + j * 3 + 2] = 255;
						}
					}
				}
			}
			r1 = r1 + 1;
		}
	}
	printf("r1=%d\n", r1);
	for (int i = 0; i<100; i++) {
		delete[] o1[i];
		delete[] o2[i];
		delete[] o3[i];
	}
	delete[] o1;
	delete[] o2;
	delete[] o3;
	delete[] row_dis;

	//fclose(fp1);
	printf("read success!!\n");

	//将图像数据存盘    
	/*
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
	*/
	
	printf("write success!!\n");
	//delete[]pBmpBuf;

	printf("clean 1 success!!\n");



	//清除数组  
	for (int i = 0; i<bmpHeight; i++) {
		delete[] b[i];
		//printf("%d:clean success!!\n",i);       
	}
	delete[] b;
	delete[] up;
	delete[] down;
	printf("clean success!!\n");

}
