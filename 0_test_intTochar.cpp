#include<iostream>
#include<vector>
#include<algorithm>
#include <cmath>
#define BITCAPACITY 1
#define PI 3.1415926535


void printFirstBlock_8_8(const std::vector<std::vector<double>> & matrix_total) {
    for (int i = 0; i < 8;i++){
        for (int j = 0; j < 8;j++){
            std::cout.width(8);
            std::cout << matrix_total[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

//dct变换：生成辅助矩阵A (参数：4或8，表示4*4 和 8*8)
std::vector<std::vector<double>>  createMatrixA(int num){
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
const std::vector<std::vector<double>> & dct_2_stage(std::vector<std::vector<double>> matrix_total){
    
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
            std::cout << "A:" << std::endl;
            printFirstBlock_8_8(matrix_a_8);
            std::cout << std::endl;

            std::vector<std::vector<double>> matrix_a_t_8 = createMatrixAT(matrix_a_8);
            std::cout << "AT:" << std::endl;
            printFirstBlock_8_8(matrix_a_t_8);
            std::cout << std::endl;

            std::vector<std::vector<double>> matrix_y_8 = matrixMulti(matrixMulti(matrix_a_8, matrix_x_8), matrix_a_t_8);
            std::cout << "一级分解8*8:" << std::endl;
            printFirstBlock_8_8(matrix_y_8);
            std::cout << std::endl;                    
                
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
                    matrix_y_8[k][l] = matrix_yy_4[k][l];

            //8*8分块写回总矩阵 matrix_y_8 -> matrix_sum
            for (int k = 0; k < 8;k++)
                for (int l = 0; l < 8;l++)
                    matrix_total[8 * i + k][8 * j + l] = matrix_y_8[k][l];

            counter++;

            if(counter % 100 == 0)
                std::cout << "block: " << counter << std::endl;
            if (counter == BITCAPACITY)
                return matrix_total;
        }
    return matrix_total;
}

const std::vector<std::vector<double>> & idct_2_stage(std::vector<std::vector<double>> & matrix_total){
    
    int counter = 0; //只需要做最多BITCAPACITY个分块（最多嵌入BITCAPACITYbit）

    for (int i = 0; 8 * i + 7 < matrix_total.size(); i++)
        for (int j = 0; 8 * j + 7 < matrix_total[0].size();j++){
            //matrix_sum[i][j]指的是某8*8的左上角
            //取 4 * 4 左上角 低频 matrix_y_8[i][j] 
            std::vector<std::vector<double>> matrix_xx_4(4, std::vector<double>(4, 0));//新建4*4初始矩阵
            //拷贝数据：4 * 4矩阵
            for (int k = 0; k < 4;k++)
                for (int l = 0; l < 4;l++)
                    matrix_xx_4[k][l] = matrix_total[k][l];

            //dct二级分解：4 * 4
            //二级分解完成的矩阵: matrix_yy_4
            std::vector<std::vector<double>> matrix_a_4 = createMatrixA(4);
            std::vector<std::vector<double>> matrix_a_t_4 = createMatrixAT(matrix_a_4);
            std::vector<std::vector<double>> matrix_yy_4 = matrixMulti(matrixMulti(matrix_a_t_4, matrix_xx_4), matrix_a_4);
            
            //4*4写入8*8左上角 matrix_xx_4 -> matrix_y_8
            for (int k = 0; k < 4;k++)
                for (int l = 0; l < 4;l++)
                    matrix_total[k][l] = matrix_yy_4[k][l];

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
            std::vector<std::vector<double>> matrix_y_8 = matrixMulti(matrixMulti(matrix_a_t_8, matrix_x_8), matrix_a_8);

            //8*8分块写回总矩阵 matrix_y_8 -> matrix_sum
            for (int k = 0; k < 8;k++)
                for (int l = 0; l < 8;l++)
                    matrix_total[8 * i + k][8 * j + l] = matrix_y_8[k][l];
                    
            counter++;

            if(counter % 100 == 0)
                //std::cout << "block: " << counter << std::endl;
            if (counter == BITCAPACITY)
                return matrix_total;
        }
    return matrix_total;
}



int main(){
    std::vector<std::vector<double>> v = {
        {59, 59, 59, 59, 59, 59, 59, 59},
        {59, 59, 68, 66, 69, 64, 65, 65},
        {59, 68, 69, 65, 71, 62, 71, 91},
        {59, 66, 65, 68, 71, 119, 193, 199},
        {59, 69, 71, 71, 148, 195, 196, 178},
        {59, 64, 62, 119, 195, 193, 158, 142},
        {59, 65, 71, 193, 196, 158, 146, 171},
        {59, 65, 91, 199, 178, 142, 171, 182}};

    std::vector<std::vector<double>> dct_v = dct_2_stage(v);
    std::cout << "dct_v:" << std::endl;
    printFirstBlock_8_8(dct_v);
    std::cout << std::endl;

    std::vector<std::vector<double>> idct_v = idct_2_stage(dct_v);
    std::cout << "idct_v:" << std::endl;
    printFirstBlock_8_8(idct_v);
    std::cout << std::endl;
}
