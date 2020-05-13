#include <iostream>
int main(){
    int stu_num, op_num;
    while (std::cin >>stu_num>>op_num){
        int stu_grade[stu_num];
        for (int i = 0; i < stu_num;i++){
            std::cin >> stu_grade[i];
        }
        while(op_num--){
            char op;
            int top_grade = 0;
            std::cin >> op;
            if(op == 'Q'){
                int a, b;
                int begin, end;
                std::cin >> a >> b;
                if(a<b){
                    begin = a;
                    end = b;
                }
                else{
                    begin = b;
                    end = a;
                }
                for (int i = begin - 1; i < end;i++){
                    if (stu_grade[i] > top_grade)
                        top_grade = stu_grade[i];
                }
                std::cout << top_grade << std::endl;
            }
            else if(op == 'U'){
                int stu_mod, grade_mod;
                std::cin >> stu_mod >> grade_mod;
                stu_grade[stu_mod - 1] = grade_mod;
            }
        }
    }
    return 0;
}