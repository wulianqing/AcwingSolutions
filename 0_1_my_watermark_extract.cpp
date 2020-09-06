#include "0_0_bmpstruct.h"
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

#define PI 3.1415926535
#define BITCAPACITY 4000
#define SIZEPERGROUP 2


//dct变换：生成辅助矩阵A (参数：4或8，表示4*4 和 8*8)
std::vector<std::vector<double>> createMatrixA(int num){
    if(!(num == 4 || num == 8))
        throw "dct变换：生成辅助矩阵A (参数：4或8，表示4*4 和 8*8)";

    std::vector<std::vector<double>> matrix_a(num, std::vector<double>(num, 0));
    for (int i = 0; i < num;i++)
        for (int j = 0; j < num;j++){
            double a = 0;
            if (i == 0)
                a = sqrt((double)1 / num);
            else
                a = sqrt((double)2 / num);
            matrix_a[i][j] = a * cos(((double)j + (double)1 / 2) * i * PI / num);
        }

    return matrix_a;
}

//dct变换：通过辅助矩阵A生成A‘
std::vector<std::vector<double>> createMatrixAT(std::vector<std::vector<double>> matrix_a){
    for (int i = 0; i < matrix_a.size();i++)
        for (int j = 0; j < i;j++){
            std::swap(matrix_a[i][j], matrix_a[j][i]);
        }
    return matrix_a;
}

//dct变换：矩阵相乘
std::vector<std::vector<double>> matrixMulti(std::vector<std::vector<double>> matrix_a,std::vector<std::vector<double>> matrix_b){
    int matrix_a_height = matrix_a.size();
    int matrix_a_width = matrix_a[0].size();
    int matrix_b_height = matrix_b.size();
    int matrix_b_width = matrix_b[0].size();

    //ret matrix
    std::vector<std::vector<double>> matrix_c(matrix_a_height, std::vector<double>(matrix_b_width,0));
    for (int i = 0; i < matrix_c.size();i++)
        for (int j = 0; j < matrix_c[0].size();j++){
            double sum = 0;
            for (int k = 0; k < matrix_a_width;k++)
                sum += matrix_a[i][k] * matrix_b[k][j];
            matrix_c[i][j] = sum;
        }
    return matrix_c;
}

//遍历蓝色分量矩阵 将8*8分块做dct变换(注意输入的矩阵的元素为char，即8位信息)
std::vector<std::vector<double>> & dct_2_stage(std::vector<std::vector<double>> matrix_total){
    
    int counter = 0; //只需要做最多BITCAPACITY个分块（最多嵌入BITCAPACITYbit）

    for (int i = 0; 8 * i + 7 < matrix_total.size(); i++)
        for (int j = 0; 8 * j + 7 < matrix_total[0].size();j++){
            //matrix_sum[i][j]指的是某8*8的左上角
            
            //8*8dct变换中 内嵌4*4
            std::vector<std::vector<double>> matrix_x_8(8, std::vector<double>(8, 0));//新建8*8初始矩阵
            //拷贝数据：8 * 8矩阵
            for (int k = 0; k < 8;k++)
                for (int l = 0; l < 8;l++)
                    matrix_x_8[k][l] = matrix_total[8 * i + k][8 * j + l];

            //dct一级分解：8 * 8
            //一级分解完成的矩阵:matrix_y_8
            std::vector<std::vector<double>> matrix_a_8 = createMatrixA(8);
            std::vector<std::vector<double>> matrix_a_t_8 = createMatrixAT(matrix_a_8);
            std::vector<std::vector<double>> matrix_y_8 = matrixMulti(matrixMulti(matrix_a_8, matrix_x_8), matrix_a_t_8);
                    
                
            //取 4 * 4 左上角 低频 matrix_y_8[i][j] 
            std::vector<std::vector<double>> matrix_xx_4(4, std::vector<double>(4, 0));//新建4*4初始矩阵
            //拷贝数据：4 * 4矩阵
            for (int k = 0; k < 4;k++)
                for (int l = 0; l < 4;l++)
                    matrix_xx_4[k][l] = matrix_y_8[k][l];
            
            //dct二级分解：4 * 4
            //二级分解完成的矩阵: matrix_yy_4
            std::vector<std::vector<double>> matrix_a_4 = createMatrixA(4);
            std::vector<std::vector<double>> matrix_a_t_4 = createMatrixAT(matrix_a_4);
            std::vector<std::vector<double>> matrix_yy_4 = matrixMulti(matrixMulti(matrix_a_4, matrix_xx_4), matrix_a_t_4);
            
            //4*4写入8*8左上角 matrix_xx_4 -> matrix_y_8
            for (int k = 0; k < 4;k++)
                for (int l = 0; l < 4;l++)
                    matrix_y_8[k][l] = matrix_xx_4[k][l];

            //8*8分块写回总矩阵 matrix_y_8 -> matrix_sum
            for (int k = 0; k < 8;k++)
                for (int l = 0; l < 8;l++)
                    matrix_total[8 * i + k][8 * j + l] = matrix_x_8[k][l];

            counter++;

            if(counter % 100 == 0)
                std::cout << "block: " << counter << std::endl;
            if (counter == BITCAPACITY)
                return matrix_total;
        }
    return matrix_total;
}

//提取信息
//拿前BITCAPACITY个8*8分块
//取8*8分块的左上角的4*4中的b2,b3,b4的2*2分块,计算Eb2,Eb3,Eb4
//排序Eb_big,Eb_small,Eb_middle
//根据Eb_middle的值算出嵌入的是0/1
//存入vector<bool>
std::vector<bool> extractBitMessage(std::vector<std::vector<double>> matrix_total){
    int counter = 0;
    std::vector<bool> bit_msg;
    for (int i = 0; i * 8 + 7 < matrix_total.size(); i++)
    {
        if(counter == BITCAPACITY)
                break;
        for (int j = 0; j * 8 + 7 < matrix_total[0].size();j++){
            //只嵌入前BITCAPACITY个分块
            if(counter == BITCAPACITY)
                break;

            //初始矩阵
            std::vector<std::vector<double>> b2(2, std::vector<double>(2, 0));
            std::vector<std::vector<double>> b3(2, std::vector<double>(2, 0));
            std::vector<std::vector<double>> b4(2, std::vector<double>(2, 0));

            //2*2分块均值：Eb2~Eb4
            double Eb2 = 0, Eb3 = 0, Eb4 = 0;
            
            //拷贝至3个2*2矩阵 -> 计算Eb2 ～ Eb4
            for (int k = 0; k < 2;k++)
                for (int l = 0; l < 2;l++){
                    b2[k][l] = matrix_total[8 * i + k][8 * j + 2 + l];
                    b3[k][l] = matrix_total[8 * i + 2 + k][8 * j + l];
                    b4[k][l] = matrix_total[8 * i + 2 + k][8 * j + 2 + l];
                    Eb2 += b2[k][l];
                    Eb3 += b3[k][l];
                    Eb4 += b4[k][l];
                }
            Eb2 /= 4;
            Eb3 /= 4;
            Eb4 /= 4;

            //排序
            double Eb_max = std::max(std::max(Eb2, Eb3), Eb4);
            double Eb_min = std::min(std::min(Eb2, Eb3), Eb4);
            double Eb_middle = Eb2 + Eb3 + Eb4 - Eb_max - Eb_min;

            //计算嵌入的是0/1
            double region = (Eb_max - Eb_min) / (2 * SIZEPERGROUP - 1);
            if(Eb_middle<  Eb_min + region / 2)
                bit_msg.push_back(0);
            else{
                int pos = (Eb_middle - Eb_min - region / 2) / region;
                //嵌入1
                if(pos % 2 == 0)
                    bit_msg.push_back(1);
                //嵌入0
                else
                    bit_msg.push_back(0);
            }
            counter++;
        }
    }
    return bit_msg;
}

//vector<bool> -> string
std::string vectorboolToString(std::vector<bool> bit_msg){
    std::string str_msg = "";
    //每8位合成一个char
    for (int i = 0; i * 8 + 7 < bit_msg.size();i++){
        char cur_c = 0;
        for (int j = 0; j < 8;j++){
            cur_c <<= 1;
            if(bit_msg[8 * i + j] == 1)
                cur_c |= 1;    
        }
        str_msg = str_msg + cur_c;
    }
    return str_msg;
}




//执行函数
void doIt(char* img_path){
    //取得bitmap数据__data
    bmp::bitbmp my_img;
    my_img.read(img_path);
    //输出image信息
    std::cout << "image height: " << my_img.height << std::endl
              << "image width: " << my_img.width << std::endl
              << "image bits: " << my_img.info.biBitCount << std::endl;

    //计算最大嵌入容量
    //int max_embeded_capacity = my_img.height / 8 * my_img.width / 8;

    //将__data的蓝色分量转入matrix
    std::vector<std::vector<double>> blue_matrix(my_img.height, std::vector<double>(my_img.width, 0));
    for (int i = 0; i < my_img.height;i++){
        for (int j = 0; j < my_img.width;j++){
            blue_matrix[i][j] = (double)my_img.__data[i * j].Blue;
            //std::cout << blue_matrix[i][j] << " ";
        }
        //std::cout << std::endl;
    }

    //dct: vector<vector<char>>  ->  vector<vector<double>>
    std::vector<std::vector<double>> dct_matrix_blue = dct_2_stage(blue_matrix);

    //提取过程
    std::vector<bool> bit_msg = extractBitMessage(dct_matrix_blue);
    std::string str_msg = vectorboolToString(bit_msg);

    std::cout << str_msg << std::endl;
    //测试用例:“To me...” 对应ascII:
    //T:84(01010100) o:111(01101111) m:109 e:101
}

int main(){
    //读图像
    char *img_path = "/Users/wubaobao/GoogleCloud-aaedu/Dropbox/ProjectCodeFolder/VSCode/AcwingSolutions/image/test.bmp";
    doIt(img_path);
}