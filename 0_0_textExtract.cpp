close all;  clc;  clear all;
I5 = imread('ps/2020-09-22_100828.jpg');
word=111;
[m, n] = size(I5);

%%%%%%**********************************************************行列识别部分
%行识别
col_left=zeros(m,1);%每行每个左边界白点列值
col_right=zeros(1,m);%每行右边界白点列值
row_per=zeros(1,m);%每行黑点数比值
up=zeros(1,round(m/20));%文本行上边界数组
down=zeros(1,round(m/20));%文本行下边界数组
rownum1=0;rownum2=0;
black=230;
for i=1:m
    num=0;%黑点数计数值
    col=1;%col_left数组计数值
    for j=1:n %获得每行黑点数及左右边界
        if I5(i,j)<black  %240及以上认为是白点,240以下是黑点
            num=num+1;
        end
        if (j>1)&&(j<n)
            if (I5(i,j)<black)&&(I5(i,j-1)>=black)%左边界
                if col==1                                      
                    col_left(i,col)=j;
                    col=col+1;
                end
            end
            if(I5(i,j)>=black)&&(I5(i,j-1)<black)%右边界
                col_right(1,i)=j-1;
            end            
        end          
    end
    %获取黑点数比值，作为划分行边界依据
    col_width=col_right(1,i)-col_left(i,1)+1; %像素行实际宽度
    if col_width<=10 %限制最低有效行宽，去除噪点影响
        col_width=0;
    end
    if(num==0)||(col_width==0)%黑点数比值en
        row_per(1,i)=0;
    else 
        row_per(1,i)=num/col_width;
    end
    %划分行边界
    if (i>1)&&(i<m)
        if row_per(1,i)>0 && row_per(1,i-1)==0
            rownum1=rownum1+1;           
            up(1,rownum1)=i;
        end
        if row_per(1,i)==0 && row_per(1,i-1)>0
            rownum2=rownum2+1;
            down(1,rownum2)=i-1;
        end
    end
end
%矫正行列边界，删去多余噪点导致的上下行边界（置0）
row_h=NaN(1,rownum1);%文本行宽数组
for i=1:rownum1
    row_h(1,i)=down(1,i)-up(1,i)+1;
end
row_h1=sort(row_h);%平均文本行宽
row_havg=row_h1(1,round(rownum1/2));
num=0;
for i=1:rownum1
    if row_h(1,i)< row_havg/2 %若文本行宽不足平均行宽一半，则置0
        up(1,i)=0;down(1,i)=0;  
        num=num+1;
    end
end
up(up==0)=[];down(down==0)=[];%删去上下边界数组的0元素
rownum1=rownum1-num;%更新文本行数
% for i=1:rownum1%行边界划线
%     for j=i:n
%         if up(1,i)~=0 &&down(1,i)~=0
%             I5(up(1,i),j)=0;
%             I5(down(1,i),j)=0;
%         end
%     end
% end
% figure(8), imshow(I5); 
% imwrite(I5,'re2.bmp');

%%%%列识别
colnum=NaN(rownum1,n);%每文本行每列黑点数统计，作为划分列边界依据
for k=1:rownum1
    for j=1:n
        num=0;        
        for i=up(1,k) :down(1,k)
            if I5(i,j)<black
                num=num+1;
            end
        end
        colnum(k,j)=num;      
    end
end
left=zeros(rownum1,round(n/20));%每文本字左边界列数组
right=zeros(rownum1,round(n/20));%每文本字右边界列数组
count=zeros(1,k);
num=0;
for k=1:rownum1 %获取左右列边界数组
    col1=0;col2=0;
     for j=1:n 
        if j==0 &&colnum(k,j)>num &&colnum(k,j+1)>num
            col1=col1+1;
            left(k,col1)=j;
        end
        if j==n && colnum(k,j-1)>num && colnum(k,j)>num
            col2=col2+1;
            right(k,col2)=j;
        end
        if j>1 && j<n
            if colnum(k,j)>num && colnum(k,j-1)<=num
                col1=col1+1;
                left(k,col1)=j;
            end
            if colnum(k,j)<=num && colnum(k,j-1)>num
                col2=col2+1;
                right(k,col2)=j-1;
            end
        end
    end
    count(1,k)=col1;%数组值计数
end
% %%若左右边界数组值相等则删除
for k=1:rownum1   %获取划分出的每组字宽
    for i=1:count(1,k)
        if (right(k,i)-left(k,i)+1)<=1
            left(k,i)=0;right(k,i)=0;
        end
        
    end 
end
for k=1:rownum1 %删去左右边界的0元素
    left1=left(k,:);right1=right(k,:);
    left1(left1==0)=[];right1(right1==0)=[];
    [i,num]=size(left1);
    for i= 1:num       
       left(k,i)=left1(1,i);
       right(k,i)=right1(1,i);
    end
    for i=num+1:count(1,k)
        left(k,i)=0;
        right(k,i)=0;
    end
    count(1,k)=num;
end  
colmax=max(count)+10;% 左边界数组最大列值

%%%%%%%%%%%%%%%%%%%%%%%英文文本单词识别%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
col_dis=NaN(rownum1,colmax);
if word==222
     for k=1:rownum1   %获取字间距
        for i=2:count(1,k)
            col_dis(k,i-1)=left(k,i)-right(k,i-1)-1;
        end         
     end
     sort_cd=sort(col_dis,2);     
     for k=1:rownum1
        cd_avg(1,k)=sort_cd(k,round((count(1,k)-1)/2));%平均字间距矩阵
     end
     cdavg1=sort(cd_avg);
     cdavg2=cdavg1(1,round(rownum1/2));%总平均字间距
     for k=1:rownum1
         if cd_avg(1,k)>cdavg2
             cdavg=cd_avg(1,k);
         else
            cdavg=cdavg2;
         end         
         for i=1:count(1,k)
            if col_dis(k,i)<2*cdavg-1
                left(k,i+1)=0;
                right(k,i)=0;
            end
        end  
     end
     for k=1:rownum1 %删去左右边界的0元素
        left1=left(k,:);right1=right(k,:);
        left1(left1==0)=[];right1(right1==0)=[];
        [i,num]=size(left1);
        for i= 1:num       
           left(k,i)=left1(1,i);
           right(k,i)=right1(1,i);
        end
        for i=num+1:count(1,k)
            left(k,i)=0;
            right(k,i)=0;
        end
        count(1,k)=num;
     end
end  
      
%  % % %列边界划线
% for k=1:rownum1
%     for s=1:count(1,k)
%         for i=up(1,k):down(1,k)
%             if up(1,k)~=0 && down(1,k)~=0
%                 for j=1:n
%                     if left(k,s)~=0 && right(k,s)~=0
%                         I5(i,left(k,s))=0;
%                         I5(i,right(k,s))=0;
%                     end
%                 end
%             end
%         end
%     end
% end    
% figure(8), imshow(I5); 
% imwrite(I5,'re.bmp');
%%%%%%%%%%%%%%%%%%%%%中文文本字识别%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if word==111
    %获取划分出的每组字宽
    col_w=NaN(k,colmax);
    col_wavg=NaN(1,rownum1);
    for k=1:rownum1   
        for i=1:count(1,k)
            col_w(k,i)=right(k,i)-left(k,i)+1;
        end 
    end
    col_wsort=sort(col_w,2); %按行对字宽数组排序，找到每行中间数作为每行平均字宽
     for k=1:rownum1
         col_wavg(1,k)=col_wsort(k,round(count(1,k)/2));
     end
    col_wavg1=sort(col_wavg);%对每行平均字宽排序找到中间值作为整体平均字宽
    colavg1=col_wavg1(1,round(k/2));
    %%%%%%获取字间距
    for k=1:rownum1
        for i=2:count(1,k)
            col_dis(k,i-1)=left(k,i)-right(k,i-1)-1;
        end
    end
    %%%%删除英文字母,若连续5个字宽小于阈值且左右字间距均小于阈值，则认定为英文字母，边界置0删除
    for k=1:rownum1
        if col_wavg(1,k)>=colavg1
            colavg=col_wavg(1,k);
        else
            colavg=colavg1;
        end
        div=round(colavg/2)+2;   %2*colavg/3
        %%%%%fprintf('k=%d\n',k);
        for i=3:count(1,k)-3    
%             flag=0;
            if col_w(k,i-2)<=div && col_w(k,i-1)<=div &&col_w(k,i)<=div &&col_w(k,i+1)<=div && col_w(k,i+2)<=div  && col_w(k,i+3)<=div
                left(k,i-2)=0;left(k,i-1)=0;left(k,i)=0;left(k,i+1)=0;left(k,i+2)=0;left(k,i+3)=0;
                right(k,i-2)=0;right(k,i-1)=0;right(k,i)=0;right(k,i+1)=0;right(k,i+2)=0;right(k,i+3)=0;
            end
        end
        num=0;
        for i=1:count(1,k)
            if left(k,i)==0
                num=num+1;
            end
        end
        count(1,k)=count(1,k)-num;
    end
    for k=1:rownum1 %删去左右边界的0元素
        left1=left(k,:);right1=right(k,:);
        left1(left1==0)=[];right1(right1==0)=[];
        for i= 1:count(1,k)        
           left(k,i)=left1(1,i);
           right(k,i)=right1(1,i);
        end
        for i=count(1,k)+1:colmax
            left(k,i)=0;
            right(k,i)=0;
        end
    end  
    for k=1:rownum1   %更新字宽数组
        for i=1:count(1,k)
            col_w(k,i)=right(k,i)-left(k,i)+1;
        end 
        for i=count(1,k)+1:colmax
            col_w(k,i)=NaN;
        end
    end
    col_wsort=sort(col_w,2); %按行对字宽数组排序，找到每行中间数作为每行平均字宽
    for k=1:rownum1
        col_wavg(1,k)=col_wsort(k,round(count(1,k)/2));
    end
    col_wavg1=sort(col_wavg);%对每行平均字宽排序找到中间值作为整体平均字宽
    colavg1=col_wavg1(1,round(k/2));
    % % % % % % % %     矫正左右边界数组一，若字宽大于平均字宽的二倍，则从中间寻找最小值分开两个字
    for k=1:rownum1
        if col_wavg(1,k)>=colavg1
            colavg=col_wavg(1,k);
        else
            colavg=colavg1;
        end 
        for i=1:count(1,k)  
            col_w(k,i)=right(k,i)-left(k,i)+1;
            if (col_w(k,i)/colavg)>=1.5 %若字宽是平均字宽的2倍
               %fprintf('k=%f,i=%f,left=%f ,right=%f\n ',k,i,left(k,i),right(k,i));
               lefti=left(k,i)+5;
               righti=right(k,i)-5;
               temp1=colnum(k,lefti:righti);
               mid=fix((righti+lefti)/2);
               bound=min(temp1);               
               %fprintf('bound=%f\n ',bound);
               %%%若两字中间距离小于colavg/10，则被认为是一个字，此时两字中间存在像素值为0的点，且数目不定
               if colnum(k,mid)==bound  || colnum(k,mid-1)==bound ||colnum(k,mid+1)==bound 
                   if colnum(k,mid-1)==bound 
                       mid=mid-1;
                   end
                   if colnum(k,mid+1)==bound 
                       mid=mid+1;
                   end
                   for s1=1:(mid-lefti+1)
                       s=mid-s1;
                       if colnum(k,s)~=bound
                           rightj=s;
                           break;
                       end                      
                   end
                   for s1=1:(righti-mid+1)
                       s=mid+s1;
                       if colnum(k,s)~=bound
                           leftj=s;   
                           break;
                       end                     
                   end
               end
               if colnum(k,mid)~=bound
                   leftj=mid+1;
                   rightj=mid-1;
               end
                
               temp2=left(k,i+1:count(1,k));
               left(k,i+1)=leftj;
               %fprintf('leftj=%f\n ',leftj);
               temp3=right(k,i:count(1,k));
               right(k,i)=rightj;  
               %fprintf('rightj=%f\n ',rightj);
               count(1,k)=count(1,k)+1;
               left(k,i+2:count(1,k))=temp2;
               right(k,i+1:count(1,k))=temp3;  
            end          
        end
        for i=1:colmax
            if left(k,i)==0
                count(1,k)=i-1;
                break;
            end
        end
     end
    for k=1:rownum1   %更新字宽数组
        for i=1:count(1,k)
            col_w(k,i)=right(k,i)-left(k,i)+1;
            
        end 
        for i=count(1,k)+1:colmax
            col_w(k,i)=NaN;
        end
    end
    
     %%%%%%%%%%%更新字宽数组 , 若字宽小于3，则左右边界置0 
    for k=1:rownum1   %获取划分出的每组字宽
        for i=1:count(1,k)
             if col_w(k,i)<=2
                left(k,i)=0;right(k,i)=0;
             end   
        end 
    end
    for k=1:rownum1 %删去左右边界的0元素
        left1=left(k,:);right1=right(k,:);
        left1(left1==0)=[];right1(right1==0)=[];
        [i,num]=size(left1);
        for i= 1:num       
           left(k,i)=left1(1,i);
           right(k,i)=right1(1,i);
        end
        for i=num+1:count(1,k)
            left(k,i)=0;
            right(k,i)=0;
        end
        count(1,k)=num;
    end  
    for k=1:rownum1   %更新字宽数组
        for i=1:count(1,k)
            col_w(k,i)=right(k,i)-left(k,i)+1;
        end 
        for i=count(1,k)+1:colmax
            col_w(k,i)=NaN;
        end
    end
    col_wsort=sort(col_w,2); %按行对字宽数组排序，找到每行中间数作为每行平均字宽
    for k=1:rownum1
        col_wavg(1,k)=col_wsort(k,round(count(1,k)/2));
    end
    col_wavg1=sort(col_wavg);%对每行平均字宽排序找到中间值作为整体平均字宽
    colavg1=col_wavg1(1,round(k/2));
    

%%%% %矫正左右边界数组二,优化左右结构字的判断，相应值置0之后删除    
    for k=1:rownum1 %判断i与i+1的大小是否构成左右结构字，若是且字间距小于等于5则合并，中间的边界置0
        if col_wavg(1,k)>=colavg1-1
            colavg=col_wavg(1,k);
        else
            colavg=colavg1;
        end  
        Threshold=colavg/2+5;
        Threshold2=colavg-3;
        num=0;
        for i= 1:count(1,k)-1          
            if (col_w(k,i)<= Threshold && col_w(k,i+1)<=Threshold2)||(col_w(k,i)<=Threshold2 && col_w(k,i+1)<=Threshold)
                dis=left(k,i+1)-right(k,i)-1;
%%%                 fprintf('fix=%d\n ',round(colavg/10)));
                if dis<(colavg/10)+1
                    left(k,i+1)=0;
                    right(k,i)=0;
                    num=num+1;
                end
            end
        end
        count(1,k)=count(1,k)-num;%更新左右边界数组大小
    end
    for k=1:rownum1 %删去左右边界的0元素
        left1=left(k,:);right1=right(k,:);
        left1(left1==0)=[];right1(right1==0)=[];
        for i= 1:count(1,k)        
           left(k,i)=left1(1,i);
           right(k,i)=right1(1,i);
        end
        for i=count(1,k)+1:colmax
            left(k,i)=0;
            right(k,i)=0;
        end
    end  
    for k=1:rownum1   %更新字宽数组
        for i=1:count(1,k)
            col_w(k,i)=right(k,i)-left(k,i)+1;
        end 
        for i=count(1,k)+1:colmax
            col_w(k,i)=NaN;
        end
    end
    col_wsort=sort(col_w,2); %按行对字宽数组排序，找到每行中间数作为每行平均字宽
    for k=1:rownum1
        col_wavg(1,k)=col_wsort(k,round(count(1,k)/2));
    end
    col_wavg1=sort(col_wavg);%对每行平均字宽排序找到中间值作为整体平均字宽
    colavg1=col_wavg1(1,round(k/2));
% % % % % %     矫正左右边界数组三，若字宽大于平均字宽的二倍，则从中间寻找最小值分开两个字
    for k=1:rownum1
        if col_wavg(1,k)>=colavg1
            colavg=col_wavg(1,k);
        else
            colavg=colavg1;
        end      
        %fprintf('count(1,k)=%d\n ',count(1,k));
        for i=1:count(1,k)   
            col_w(k,i)=right(k,i)-left(k,i)+1;
            if col_w(k,i)/colavg>=1.5 %若字宽是平均字宽的2倍
                %fprintf('k=%f,i=%f,left=%f ,right=%f\n ',k,i,left(k,i),right(k,i));
               lefti=left(k,i)+5;
               righti=right(k,i)-5;
               temp1=colnum(k,lefti:righti);
               mid=fix((righti+lefti)/2);
               bound=min(temp1);
               %fprintf('bound=%f\n ',bound);
               %若两字中间距离小于colavg/10，则被认为是一个字，此时两字中间存在像素值为0的点，且数目不定
               if (colnum(k,mid)==bound)  || (colnum(k,mid-1)==bound) || (colnum(k,mid+1)==bound) 
                   if colnum(k,mid-1)==bound 
                       mid=mid-1;
                   end
                   if colnum(k,mid+1)==bound 
                       mid=mid+1;
                   end
                   for s1=1:(mid-lefti+1)
                       s=mid-s1;
                       if colnum(k,s)~=bound
                           rightj=s;
                           break;
                       end                      
                   end
                   for s1=1:(righti-mid+1)
                       s=mid+s1;
                       if colnum(k,s)~=bound
                           leftj=s;   
                           break;
                       end                     
                   end
               end
               if colnum(k,mid)~=bound
                   for s1=1:(mid-lefti+1)
                       s=mid-s1;
                       if  colnum(k,s)==bound
                           leftj=s+1;
                           rightj=s-1;
                           break;
                       end
                   end 
                   if (rightj-left(k,i)+1)<= (colavg/2+2)
                       for s1=1:(righti-mid+1)
                           s=mid+s1;
                           if colnum(k,s)==bound
                               leftj=s+1;
                               rightj=s-1;   
                               break;
                           end 
                       end
                   end 
               end
               temp2=left(k,i+1:count(1,k));
               left(k,i+1)=leftj;
               %fprintf('leftj=%f\n ',leftj);
               temp3=right(k,i:count(1,k));
               right(k,i)=rightj;  
               %fprintf('rightj=%f\n ',rightj);
               count(1,k)=count(1,k)+1;
               left(k,i+2:count(1,k))=temp2;
               right(k,i+1:count(1,k))=temp3;
               
            end
        end
        for i=1:colmax
            if left(k,i)==0 
                count(1,k)=i-1;
                break;
            end
        end
    end
    
 %%%%%%%%%%%求平均字间距，限制水印提取位置
    for k=1:rownum1
        for i=2:count(1,k)
            col_dis(k,i-1)=left(k,i)-right(k,i-1)-1;
        end
        for i=count(1,k)+1:colmax
            col_dis(k,i-1)=NaN;
        end
    end
    col_disort=sort(col_dis,2);
    for k=1:rownum1
        col_disavg(1,k)=col_disort(k,round((count(1,k)-1)/2));
    end
    col_disavg1=sort(col_disavg);
    coldis1=col_disavg1(1,round(rownum1/2));
    
 %%%%%%%%%%%更新字宽数组 , 若字宽小于3，则左右边界置0 
    for k=1:rownum1   %获取划分出的每组字宽
        for i=1:count(1,k)
            if (right(k,i)-left(k,i)+1)<=3
                left(k,i)=0;right(k,i)=0;
            end
        end 
    end
    for k=1:rownum1 %删去左右边界的0元素
        left1=left(k,:);right1=right(k,:);
        left1(left1==0)=[];right1(right1==0)=[];
        [i,num]=size(left1);
        for i= 1:num       
           left(k,i)=left1(1,i);
           right(k,i)=right1(1,i);
        end
        for i=num+1:count(1,k)
            left(k,i)=0;
            right(k,i)=0;
        end
        count(1,k)=num;
    end  
     %%%%%%%%%%%更新字宽数组 , 若字宽小于平均字宽，则左右边界置0 
    for k=1:rownum1   
        for i=1:count(1,k)
            col_w(k,i)=right(k,i)-left(k,i)+1;
        end 
        for i=count(1,k)+1:colmax
            col_w(k,i)=NaN;
        end
    end
    col_wsort=sort(col_w,2); %按行对字宽数组排序，找到每行中间数作为每行平均字宽
    for k=1:rownum1
        col_wavg(1,k)=col_wsort(k,round(count(1,k)/2));
    end
    col_wavg1=sort(col_wavg);%对每行平均字宽排序找到中间值作为整体平均字宽
    colavg1=col_wavg1(1,round(k/2));    
    for k=1:rownum1  
        if col_wavg(1,k)>=colavg1
            colavg=col_wavg(1,k);
        else
            colavg=colavg1;
        end 
        for i= 1:count(1,k)        
            if col_w(k,i)<= (colavg/2+4)          
                left(k,i)=0;right(k,i)=0; 
            end
        end
    end
end
% % %列边界划线
for k=1:rownum1
    for s=1:count(1,k)
        for i=up(1,k):down(1,k)
            if up(1,k)~=0 && down(1,k)~=0
                for j=1:n
                    if left(k,s)~=0 && right(k,s)~=0
                        I5(i,left(k,s))=0;
                        I5(i,right(k,s))=0;
                    end
                end
            end
        end
    end
end
% figure(8), imshow(I5); 
% imwrite(I5,'re.bmp');

%%%%%%%%%%******************************************************行移水印提取     
%统计文本行间距
row_dis=zeros(rownum1,3);
 for k=2:rownum1
     fk=rownum1-k+1;
     row_dis(k,2)=fk+1;
     row_dis(k,3)=fk;
     row_dis(k,1)=up(1,fk+1)-down(1,fk)-1;
 end
%提取行移水印
row=NaN(1,30);
r1=1;
for k= 2:rownum1-1
    % fk=rownum1-k+1;
    if row_dis(k,1)>= row_dis(k+1,1) %优化段落之间间距大情况
        div=row_dis(k,1)/row_dis(k+1,1);
    else
        div=row_dis(k+1,1)/row_dis(k,1);
    end
%     fprintf('div=%f\n ',div);
    if rem(k,2)==0 && div<=2  
        if row_dis(k,1)>=row_dis(k+1,1)
            row(1,r1)=1;
        else
            row(1,r1)=0;
        end
        r1=r1+1;     
    end        
end
water_len=0;
num1=5;
for i=1:6
    water_len=water_len+row(1,i)*2^(num1);
    num1=num1-1;
end
% %%%%%%%%%%******************************************************字移水印提取      
r=1;
w=zeros(rownum1,colmax);
for i=1:rownum1
    for j=1:colmax
        w(i,j)=2;
    end
end
dis1=NaN(rownum1,colmax);
dis2=NaN(rownum1,colmax);

 for k=1:rownum1
    if col_disavg(1,k)>=coldis1
        coldis=col_disavg(1,k);
    else
        coldis=coldis1;
    end     
    coldis=coldis*4-2;
% %     fprintf('k=%d  coldis=%d\n',k,coldis);
    for s=2:count(1,k)-1
        if  rem(s-1,2)~=0 && right(k,s-1)~=0 %左侧右边界可识别
            if rem(s,2)==0 && left(k,s)~=0 && right(k,s)~=0 && left(k,s+1)~=0 %自己可识别，右侧左边界可识别
                dis1(k,s)=left(k,s)-right(k,s-1)-1;
                dis2(k,s)=left(k,s+1)-right(k,s)-1;
                if (dis1(k,s)<coldis && dis2(k,s)<coldis)|| word==222                        
                    if dis1(k,s)<=dis2(k,s)
                        w(k,s)=0;
                        r=r+1;
                    else
                        w(k,s)=1;
                        r=r+1;
                    end
                end
            end
        end
    end
end
% figure(8), imshow(I5); 
% imwrite(I5,'re.bmp');
fprintf('r=%d\n',r);  
water1=NaN(1200,3);
num=1;
for k=1:rownum1
    fk=rownum1-k+1;
    for s=1:colmax
        if w(fk,s)==0 
            water1(num,1)=fk;
            water1(num,2)=s;
            water1(num,3)=0;
            num=num+1;
        end
        if w(fk,s)==1 
            water1(num,1)=fk;
            water1(num,2)=s;
            water1(num,3)=1;
            num=num+1;
        end
    end
end
water_len=35;
div=round(r/water_len);%四舍五入取整
dif=rem(r,water_len);
if dif~=0
    div=div+1;
end
if div>11   
   div=11; 
end
water2=NaN(div,water_len);
num=1;
for i=1:div
    for j=1:water_len
        water2(i,j)=water1(num,3);
        num=num+1;
    end
end
water=mode(water2);   

wm=1;
for i=1:7:water_len
    num=0;
    num1=6;
    for j=i:i+6
        num=num+water(1,j)*2^(num1);
        num1=num1-1;
    end
    watermark(1,wm)=char(num);   
    wm=wm+1;
end
fprintf('%c',watermark);
fprintf('\n');