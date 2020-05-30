#include <iostream>
#include <bits/stdc++.h>
#include <sstream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <thread>

#include<cstring>
#include <vector>
#include <string.h>
#include<unordered_map>
#include<unordered_set>
#include <queue>
#include <utility>

#include <fcntl.h>
#include <unistd.h>
#include<algorithm>
#include <sys/mman.h>
using namespace std;

int ALLDATASIZE;





void thr_out_data(int index,char* ans,char *px3[4],char *px4[4],char *px5[4],char *px6[4],char *px7[4],char *px8[4],unsigned int *len3,unsigned int *len4,unsigned int *len5,unsigned int *len6,unsigned int *len7,unsigned int *len8){
 
   
    char*p3[4]={px3[0],px3[1],px3[2],px3[3]};
    char*p4[4]={px4[0],px4[1],px4[2],px4[3]};
    char*p5[4]={px5[0],px5[1],px5[2],px5[3]};
    char*p6[4]={px6[0],px6[1],px6[2],px6[3]};
    char*p7[4]={px7[0],px7[1],px7[2],px7[3]};
    char*p8[4]={px8[0],px8[1],px8[2],px8[3]};
    for(int i=0;i<ALLDATASIZE;i++)
    {   if(len3[i]){
            int nt=i%4;
            if(nt==index){
                memcpy(ans, p3[nt],len3[i]);
                }
                ans+=len3[i]; 
                p3[nt]+=len3[i]; 
             
        }
    }
   
    for(int i=0;i<ALLDATASIZE;i++)
    {   if(len4[i]){
            int nt=i%4;
            if(nt==index){
                memcpy(ans, p4[nt],len4[i]);
                }
                ans+=len4[i]; 
                p4[nt]+=len4[i]; 
             
        }
    }

       for(int i=0;i<ALLDATASIZE;i++)
    {   if(len5[i]){
            int nt=i%4;
            if(nt==index){
                memcpy(ans, p5[nt],len5[i]);
                }
                ans+=len5[i]; 
                p5[nt]+=len5[i]; 
             
        }
    }
        for(int i=0;i<ALLDATASIZE;i++)
    {   if(len6[i]){
            int nt=i%4;
            if(nt==index){
                memcpy(ans, p6[nt],len6[i]);
                }
                ans+=len6[i]; 
                p6[nt]+=len6[i]; 
             
        }
    }  
  for(int i=0;i<ALLDATASIZE;i++)
    {   if(len7[i]){
            int nt=i%4;
            if(nt==index){
                memcpy(ans, p7[nt],len7[i]);
                }
                ans+=len7[i]; 
                p7[nt]+=len7[i]; 
             
        }
    }
  for(int i=0;i<ALLDATASIZE;i++)
    {   if(len8[i]){
            int nt=i%4;
            if(nt==index){
                memcpy(ans, p8[nt],len8[i]);
                }
                ans+=len8[i]; 
                p8[nt]+=len8[i]; 
             
        }
    }  
    
}
void getdata(string filename,unordered_map<unsigned int,unsigned int> &in_yingshe,vector<long long unsigned>& datalist){

    int fd = open(filename.c_str(),O_RDONLY);
    long long int len = lseek(fd,0,SEEK_END);
    char *buf = (char *) mmap(NULL,len,PROT_READ,MAP_PRIVATE,fd,0);
    

    vector<unsigned int> paixu;

    
    char *p=buf;
    unsigned int tmp1=0;
    unsigned int tmp2=0;
    long long unsigned int key=0;    
    char *km=buf;
    km+=len;
    int mx1=3;
    while(p<km){              
        while(*p!=','){tmp1=int(*p-'0')+tmp1*10;p++;}

        p++;
        while(*p!=','){tmp2=int(*p-'0')+tmp2*10;p++;}
        p++;
        while(*p!='\n'&&*p!='\r'){
             if(*p=='.'){p++;mx1=2;}
             if(mx1!=3){key=int(*p-'0')+key*10;p++;mx1--;}
             else{key=int(*p-'0')+key*10;p++;}
        }
        if(*p=='\r') p++;
        if(mx1==3) key*=100;
        if(mx1==1) key*=10;
        mx1=3;
        paixu.push_back(tmp1); 
        datalist.push_back(tmp1);  
        datalist.push_back(tmp2);
        datalist.push_back(key);
        tmp1=0;
        tmp2=0;
        key=0;
        p++;
    } 
    
     munmap(buf, len);
    close(fd); 

       sort(paixu.begin(),paixu.end());//haoshi
       
       ALLDATASIZE=unique(paixu.begin(),paixu.end())-paixu.begin();
       
 
    
       for(int i=0;i<ALLDATASIZE;i++){
            in_yingshe.insert({paixu[i],i});

       }
       
}



void get_data_g(vector<long long unsigned>& datalist,unordered_map<unsigned int,unsigned int> &in_yingshe,vector<vector<unsigned int>> &data_g){
    data_g=vector<vector<unsigned int>>(ALLDATASIZE);
    unsigned int tmp1=0;
    unsigned int tmp2=0;
    unsigned int key=0;        
        for(int i=0;i<datalist.size();i+=3){
            if(in_yingshe.count(datalist[i+1])){
                
                
                tmp1=in_yingshe.at(datalist[i]);
                tmp2=in_yingshe.at(datalist[i+1]);
                //key=datalist[i+2];
                data_g[tmp1].push_back(tmp2);
                
            }
            
        }
        for(auto &line:data_g)
         sort(line.begin(),line.end());
             
}
void get_key_g(vector<long long unsigned>& datalist,unordered_map<unsigned int,unsigned int> &in_yingshe,vector<vector<unsigned long long>> &key_g){
    key_g=vector<vector<unsigned long long>>(ALLDATASIZE);
    long long unsigned tmp1=0;
    long long unsigned tmp2=0;
    long long unsigned key=0; 
    vector<vector<pair<long long unsigned,long long unsigned>>>data_key_g(ALLDATASIZE);       
        for(int i=0;i<datalist.size();i+=3){
            if(in_yingshe.count(datalist[i+1])){
                
                
                tmp1=in_yingshe.at(datalist[i]);
                tmp2=in_yingshe.at(datalist[i+1]);
                key=datalist[i+2];
                data_key_g[tmp1].push_back(make_pair(tmp2,key));
                
            }
            
        }
        for(auto &line:data_key_g)
         sort(line.begin(),line.end());
         
         for(int i=0;i<ALLDATASIZE;i++)
         for(auto &n:data_key_g[i]){
            key_g[i].push_back(n.second);
            
         }
         
         
             
}
void get_last_t(vector<long long unsigned>& datalist,unordered_map<unsigned int,unsigned int> &in_yingshe,vector<vector<unsigned int>> &last_t){
    last_t=vector<vector<unsigned int>>(ALLDATASIZE);
    unsigned int tmp1=0;
    unsigned int tmp2=0;
    unsigned int key=0;        
        for(int i=0;i<datalist.size();i+=3){
            if(in_yingshe.count(datalist[i+1])){
                
                
                tmp1=in_yingshe.at(datalist[i]);
                tmp2=in_yingshe.at(datalist[i+1]);
                //key=datalist[i+2];
                last_t[tmp2].push_back(tmp1);
            }
            
        }
        
        for(auto &line:last_t)
         sort(line.begin(),line.end());
  
          
}
void get_yingshe(vector<long long unsigned>& datalist,unordered_map<unsigned int,unsigned int> &in_yingshe,vector<string>&yingshe){
     yingshe=vector<string>(ALLDATASIZE);      
     unsigned int tmp1=0;
        
        for(int i=0;i<datalist.size();i+=3){           
                tmp1=in_yingshe.at(datalist[i]);                
                if(!yingshe[tmp1].size())yingshe[tmp1]=to_string(datalist[i]);
            
            
        }


}




inline bool xjbx(unsigned int root,unsigned int x,unsigned int x2,vector<vector<unsigned int>>&data,vector<vector<unsigned long long>>& key){
    int x_k=0;
    int root_k=0;
    for(int i=0;i<data[x2].size();i++){
        if(data[x2][i]==x)
            {x_k=i;break;}
    
    }
    for(int i=0;i<data[x].size();i++){
        if(data[x][i]==root)
            {root_k=i;break;}   
    }
    if((key[x2][x_k]<=key[x][root_k]*5)&&(key[x2][x_k]*3>=key[x][root_k])) return 1;
    return 0;
    
    
}
void get_7(bool*l7,bool *l6,bool*l5,bool*l4,unsigned int root,vector<vector<unsigned int>>&data,vector<vector<unsigned long long>>& key,vector<vector<unsigned int>>& last,char* & data8,char* & data7,char*& data6,char*& data5,char*& data4,char*& data3,vector<string>& yingshe,int &jl_all){

    for(auto &x:last[root])
        if(x>root) {
            l7[x]=1;
            l6[x]=1;
            l5[x]=1; 
            l4[x]=1;
            for(auto &x2:last[x])
                if(x2>root&&xjbx(root,x,x2,data,key)){                   
                    l6[x2]=1;
                    l5[x2]=1; 
                    l4[x2]=1;                 
                    for(auto &x3:last[x2])
                        if(x3>root&&xjbx(x,x2,x3,data,key)){                            
                            l5[x3]=1; 
                            l4[x3]=1; 
                            for(auto &x4:last[x3])
                                if(x4>root&&xjbx(x2,x3,x4,data,key))
                                    l4[x4]=1;
           
                        }
                }
       }      
 
    int i1,i2,i3,i4,i5,i6,i7,i8;
    for(i1=0;i1<data[root].size();i1++){
        unsigned int &t1=data[root][i1];
        if(t1>root){ 
            for(i2=0;i2<data[t1].size();i2++){
                unsigned int &t2=data[t1][i2];
                if(t2>root&&(key[t1][i2]*5>=key[root][i1])&&(key[t1][i2]<=key[root][i1]*3)){
                    for(i3=0;i3<data[t2].size();i3++){
                        unsigned int &t3=data[t2][i3];
                        if(t3>root&&t3!=t1&&(key[t2][i3]*5>=key[t1][i2])&&(key[t2][i3]<=key[t1][i2]*3)){
                            for(i4=0;i4<data[t3].size();i4++){
                                unsigned int &t4=data[t3][i4];
                                if(l4[t4]&&t4!=t1&&t4!=t2&&(key[t3][i4]*5>=key[t2][i3])&&(key[t3][i4]<=key[t2][i3]*3)){
                                    for(i5=0;i5<data[t4].size();i5++){
                                        unsigned int &t5=data[t4][i5];
                                        if(l5[t5]&&t5!=t1&&t5!=t2&&t5!=t3&&(key[t4][i5]*5>=key[t3][i4])&&(key[t4][i5]<=key[t3][i4]*3)){
                                            for(i6=0;i6<data[t5].size();i6++){
                                                unsigned int &t6=data[t5][i6];
                                                if(l6[t6]&&t6!=t1&&t6!=t2&&t6!=t3&&t6!=t4&&(key[t5][i6]*5>=key[t4][i5])&&(key[t5][i6]<=key[t4][i5]*3)){
                                                    for(i7=0;i7<data[t6].size();i7++){
                                                        unsigned int &t7=data[t6][i7];
                                                        if(l7[t7]&&t7!=t1&&t7!=t2&&t7!=t3&&t7!=t4&&t7!=t5&&(key[t6][i7]*5>=key[t5][i6])&&(key[t6][i7]<=key[t5][i6]*3)){
                                                            for(i8=0;i8<data[t7].size();i8++){
                                                                unsigned int &t8=data[t7][i8];
                                                                if(t8==root&&(key[t7][i8]*5>=key[t6][i7])&&(key[t7][i8]<=key[t6][i7]*3)&&(key[root][i1]*5>=key[t7][i8])&&(key[root][i1]<=key[t7][i8]*3)){
                                                                     jl_all++;  
                                                                    memcpy(data8, yingshe[root].c_str(),yingshe[root].size());
                                                                    data8+=yingshe[root].size();*data8=',';data8++;
                                                                    memcpy(data8, yingshe[t1].c_str(),yingshe[t1].size());
                                                                    data8+=yingshe[t1].size();*data8=',';data8++;
                                                                    memcpy(data8, yingshe[t2].c_str(),yingshe[t2].size());
                                                                    data8+=yingshe[t2].size();*data8=',';data8++;
                                                                    memcpy(data8, yingshe[t3].c_str(),yingshe[t3].size());
                                                                    data8+=yingshe[t3].size();*data8=',';data8++;
                                                                    memcpy(data8, yingshe[t4].c_str(),yingshe[t4].size());
                                                                    data8+=yingshe[t4].size();*data8=',';data8++;
                                                                    memcpy(data8, yingshe[t5].c_str(),yingshe[t5].size());
                                                                    data8+=yingshe[t5].size();*data8=',';data8++;
                                                                    memcpy(data8, yingshe[t6].c_str(),yingshe[t6].size());
                                                                    data8+=yingshe[t6].size();*data8=',';data8++;   
                                                                    memcpy(data8, yingshe[t7].c_str(),yingshe[t7].size());
                                                                    data8+=yingshe[t7].size();*data8='\n';data8++;                                                                         
                                                                
                                                                }
                                                            
                                                            }
                                                        
                                                        
                                                        }
                                                        
                                                        else if(t7==root&&(key[t6][i7]*5>=key[t5][i6])&&(key[t6][i7]<=key[t5][i6]*3)&&(key[root][i1]*5>=key[t6][i7])&&(key[root][i1]<=key[t6][i7]*3)){
                                                            jl_all++;  
                                                            memcpy(data7, yingshe[root].c_str(),yingshe[root].size());
                                                            data7+=yingshe[root].size();*data7=',';data7++;
                                                            memcpy(data7, yingshe[t1].c_str(),yingshe[t1].size());
                                                            data7+=yingshe[t1].size();*data7=',';data7++;
                                                            memcpy(data7, yingshe[t2].c_str(),yingshe[t2].size());
                                                            data7+=yingshe[t2].size();*data7=',';data7++;
                                                            memcpy(data7, yingshe[t3].c_str(),yingshe[t3].size());
                                                            data7+=yingshe[t3].size();*data7=',';data7++;
                                                            memcpy(data7, yingshe[t4].c_str(),yingshe[t4].size());
                                                            data7+=yingshe[t4].size();*data7=',';data7++;
                                                            memcpy(data7, yingshe[t5].c_str(),yingshe[t5].size());
                                                            data7+=yingshe[t5].size();*data7=',';data7++;
                                                            memcpy(data7, yingshe[t6].c_str(),yingshe[t6].size());
                                                            data7+=yingshe[t6].size();*data7='\n';data7++;
                                                              
                                                        
                                                        
                                                        }
                                                    
                                                    }
                                                
                                                
                                                }
                                                
                                                
                                                else if(t6==root&&(key[t5][i6]*5>=key[t4][i5])&&(key[t5][i6]<=key[t4][i5]*3)&&(key[root][i1]*5>=key[t5][i6])&&(key[root][i1]<=key[t5][i6]*3)){
                                                    jl_all++;
                                                    memcpy(data6, yingshe[root].c_str(),yingshe[root].size());
                                                    data6+=yingshe[root].size();*data6=',';data6++;
                                                    memcpy(data6, yingshe[t1].c_str(),yingshe[t1].size());
                                                    data6+=yingshe[t1].size();*data6=',';data6++;
                                                    memcpy(data6, yingshe[t2].c_str(),yingshe[t2].size());
                                                    data6+=yingshe[t2].size();*data6=',';data6++;
                                                    memcpy(data6, yingshe[t3].c_str(),yingshe[t3].size());
                                                    data6+=yingshe[t3].size();*data6=',';data6++;
                                                    memcpy(data6, yingshe[t4].c_str(),yingshe[t4].size());
                                                    data6+=yingshe[t4].size();*data6=',';data6++;
                                                    memcpy(data6, yingshe[t5].c_str(),yingshe[t5].size());
                                                    data6+=yingshe[t5].size();*data6='\n';data6++;

                                                }
                                            
                                            
                                            }
                                        
                                        
                                        }
                                        else if(t5==root&&(key[t4][i5]*5>=key[t3][i4])&&(key[t4][i5]<=key[t3][i4]*3)&&(key[root][i1]*5>=key[t4][i5])&&(key[root][i1]<=key[t4][i5]*3)){
                                            jl_all++;
                                            memcpy(data5, yingshe[root].c_str(),yingshe[root].size());
                                            data5+=yingshe[root].size();*data5=',';data5++;
                                            memcpy(data5, yingshe[t1].c_str(),yingshe[t1].size());
                                            data5+=yingshe[t1].size();*data5=',';data5++;
                                            memcpy(data5, yingshe[t2].c_str(),yingshe[t2].size());
                                            data5+=yingshe[t2].size();*data5=',';data5++;
                                            memcpy(data5, yingshe[t3].c_str(),yingshe[t3].size());
                                            data5+=yingshe[t3].size();*data5=',';data5++;
                                            memcpy(data5, yingshe[t4].c_str(),yingshe[t4].size());
                                            data5+=yingshe[t4].size();*data5='\n';data5++;
                                                                                    
                        
                                        
                                        }
                                    
                                    }
                                
                                
                                }
                                else if(t4==root&&(key[t3][i4]*5>=key[t2][i3])&&(key[t3][i4]<=key[t2][i3]*3)&&(key[root][i1]*5>=key[t3][i4])&&(key[root][i1]<=key[t3][i4]*3)){
                                    jl_all++;
                                    memcpy(data4, yingshe[root].c_str(),yingshe[root].size());
                                    data4+=yingshe[root].size();*data4=',';data4++;
                                    memcpy(data4, yingshe[t1].c_str(),yingshe[t1].size());
                                    data4+=yingshe[t1].size();*data4=',';data4++;
                                    memcpy(data4, yingshe[t2].c_str(),yingshe[t2].size());
                                    data4+=yingshe[t2].size();*data4=',';data4++;
                                    memcpy(data4, yingshe[t3].c_str(),yingshe[t3].size());
                                    data4+=yingshe[t3].size();*data4='\n';data4++;
                                                            
                                }
                            
                            }
                        
                        
                        
                        }
                        else if(t3==root&&(key[t2][i3]*5>=key[t1][i2])&&(key[t2][i3]<=key[t1][i2]*3)&&(key[root][i1]*5>=key[t2][i3])&&(key[root][i1]<=key[t2][i3]*3)){
                        
                        
                            jl_all++;
                            memcpy(data3, yingshe[root].c_str(),yingshe[root].size());
                            data3+=yingshe[root].size();*data3=',';data3++;
                            memcpy(data3, yingshe[t1].c_str(),yingshe[t1].size());
                            data3+=yingshe[t1].size();*data3=',';data3++;
                            memcpy(data3, yingshe[t2].c_str(),yingshe[t2].size());
                            data3+=yingshe[t2].size();*data3='\n';data3++;
                                                   
                
                        }
                        
                    }
            
                }
            }
        }
    } 
 
    for(auto &x:last[root])
        if(x>root) {
            l7[x]=0;
            l6[x]=0;
            l5[x]=0; 
            l4[x]=0;
            for(auto &x2:last[x])
                if(x2>root){                   
                    l6[x2]=0;
                    l5[x2]=0; 
                    l4[x2]=0;                 
                    for(auto &x3:last[x2])
                        if(x3>root){                            
                            l5[x3]=0; 
                            l4[x3]=0; 
                            for(auto &x4:last[x3])
                                if(x4>root)
                                    l4[x4]=0;
                                
                            
                        }
                }
       }      
 

}




void thr(int index,vector<vector<unsigned int>>& data_g,vector<vector<unsigned long long>>& key_g,vector<vector<unsigned int>>& last_t,char *data8,char* data7,char* data6,char* data5,char* data4,char* data3,vector<string>& yingshe,int &jl_all,unsigned int* len3,unsigned int* len4,unsigned int* len5,unsigned int* len6,unsigned int* len7,unsigned int* len8){
    bool *l7=new bool[data_g.size()];
    bool *l6=new bool[data_g.size()];
    bool *l5=new bool[data_g.size()];
    bool *l4=new bool[data_g.size()];
    
    for(int k=0;k<ALLDATASIZE;k++) {l7[k]=0;l5[k]=0;l4[k]=0;l6[k]=0;}
    for(int i=0;i<ALLDATASIZE;i++){
        if(i%4==index){
                char *p3=data3;
                char *p4=data4;
                char *p5=data5;
                char *p6=data6;
                char *p7=data7;
                char *p8=data8;
                  get_7(l7,l6,l5,l4,i,data_g,key_g,last_t,data8,data7,data6,data5,data4,data3,yingshe,jl_all); 
                           
                len3[i]=data3-p3;
                len4[i]=data4-p4;
                len5[i]=data5-p5;
                len6[i]=data6-p6;
                len7[i]=data7-p7;
                len8[i]=data8-p8;
                
                
            }
        }
 

}



int main(){
    
   
    //string test_file="data/1004812/test_data.txt";
    //string out_file="data/my_out1.txt";
    
    string test_file="/data/test_data.txt";
    string out_file="/projects/student/result.txt";
    
    unordered_map<unsigned int,unsigned int> in_yingshe;
    vector<long long unsigned> datalist;
    getdata(test_file, in_yingshe, datalist);
    
    
    
    vector<vector<unsigned int>> data_g;
    vector<vector<unsigned long long>> key_g;
    vector<vector<unsigned int>> last_t;
             
    vector<string>yingshe;
    
    thread thx1(get_data_g,ref(datalist),ref(in_yingshe),ref(data_g));
    thread thx2(get_last_t,ref(datalist),ref(in_yingshe),ref(last_t));
    thread thx3(get_yingshe,ref(datalist),ref(in_yingshe),ref(yingshe));
    thread thx4(get_key_g,ref(datalist),ref(in_yingshe),ref(key_g));

    int TX=4;
     
    unsigned int QW=20000000; 
    char* strx3[TX];
    char* strx4[TX];
    char* strx5[TX];
    char* strx6[TX];
    char* strx7[TX];
    char* strx8[TX];
    for(int x=0;x<TX;x++){
        strx3[x]=new char [3*QW];
    
        strx4[x]=new char [4*QW];        
    
        strx5[x]=new char [5*2*QW];
    
        strx6[x]=new char [6*2*QW];        
    
        strx7[x]=new char [7*4*QW];        
    
        strx8[x]=new char [8*8*QW];    
    }           
 
     unsigned int *str_len3=new unsigned int[ALLDATASIZE];
    unsigned int *str_len4=new unsigned int[ALLDATASIZE];
    unsigned int *str_len5=new unsigned int[ALLDATASIZE];
    unsigned int *str_len6=new unsigned int[ALLDATASIZE];
    unsigned int *str_len7=new unsigned int[ALLDATASIZE];
    unsigned int *str_len8=new unsigned int[ALLDATASIZE];
  
  thx1.join();
  thx2.join();
  thx3.join();
  thx4.join();
   
  

      
    unsigned int datastr[TX*6]={0}; 
   
    vector<thread*> ths; 
    
    

    int jl_all[TX]={0};    
    for(int x=0;x<TX;x++)
    {
    
    ths.push_back(new thread(thr,x,ref(data_g),ref(key_g),ref(last_t),strx8[x],strx7[x],strx6[x],strx5[x],strx4[x],strx3[x],ref(yingshe),ref(jl_all[x]),ref(str_len3),ref(str_len4),ref(str_len5),ref(str_len6),ref(str_len7),ref(str_len8)));
    }
    for (auto& th : ths)  th->join();
    for (auto& th : ths)  delete(th);

 
    unsigned int strsize=0;   
    unsigned int strsize3=0; 
    unsigned int strsize4=0; 
    unsigned int strsize5=0; 
    unsigned int strsize6=0; 
    unsigned int strsize7=0; 
    unsigned int strsize8=0; 
    for(int x=0;x<ALLDATASIZE;x++)  {
                strsize3+=str_len3[x];      
                strsize4+=str_len4[x];
                strsize5+=str_len5[x];
                strsize6+=str_len6[x];
                strsize7+=str_len7[x];
                strsize8+=str_len8[x];
            }
              
    strsize=strsize3+strsize4+strsize5+strsize6+strsize7+strsize8;

       
    int datasize=0;    
for(int x=0;x<TX;x++)
    {
        datasize+=jl_all[x];
    }    
    string outstr=to_string(datasize)+'\n';
    cout<<outstr<<endl;
   
   
  
    //FILE *fp;
    //fp = fopen( out_file.c_str() , "w" );    
    //fclose(fp);
    int fd = open(out_file.c_str(), O_RDWR | O_CREAT, 00777);
    write(fd,"1",1);
    lseek(fd, strsize+outstr.size()-1, SEEK_SET);
    write(fd,"\n",1);
    char* buf = (char*)mmap(NULL,outstr.size()+strsize, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    close(fd);
    
    
    char *ans=buf;
    memcpy(ans, outstr.c_str(), outstr.size());
    ans+=outstr.size(); 
    
        char *p3[4]={strx3[0],strx3[1],strx3[2],strx3[3]};

        char *p4[4]={strx4[0],strx4[1],strx4[2],strx4[3]};
  
        char *p5[4]={strx5[0],strx5[1],strx5[2],strx5[3]};

        char *p6[4]={strx6[0],strx6[1],strx6[2],strx6[3]};

        char *p7[4]={strx7[0],strx7[1],strx7[2],strx7[3]};
        
        char *p8[4]={strx8[0],strx8[1],strx8[2],strx8[3]};
  vector<thread*> ths2;
     for(int x=0;x<TX;x++)
     ths2.push_back(new thread(thr_out_data,x,ans,p3,p4,p5,p6,p7,p8,str_len3,str_len4,str_len5,str_len6,str_len7,str_len8));
     
    for (auto& th : ths2)  th->join();
    for (auto& th : ths2)  delete(th);

    munmap(buf, strsize+outstr.size());
          
 
    exit(0); 
    return 0;    
     
}
