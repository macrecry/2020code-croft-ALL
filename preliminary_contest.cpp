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

#include <fcntl.h>
#include <unistd.h>
#include<algorithm>
#include <sys/mman.h>
using namespace std;
#include <sys/time.h>

struct timeval t1,t2;
float timeuse;
int ALLDATASIZE=50000;

void getdata(char *buf,int len,vector<vector<unsigned int>>& last_t)
{
    char *p=buf;
    unsigned int tmp1=0;
    unsigned int tmp2=0;
    last_t=vector<vector<unsigned int>>(ALLDATASIZE);
  
    char *km=buf;
    km+=len;
    while(p<km){              
        while(*p!=','){tmp1=int(*p-'0')+tmp1*10;p++;}
        p++;
        while(*p!=','){tmp2=int(*p-'0')+tmp2*10;p++;}
        p+=2;
        while(*p!='\n'){p++;}
        if(tmp1<ALLDATASIZE&&tmp2<ALLDATASIZE)  
        last_t[tmp2].push_back(tmp1);
       
        tmp1=0;
        tmp2=0;
        p++;
    } 
    
        for(auto &line:last_t)
    if(line.size())sort(line.begin(),line.end());
    

}
void get_str_yingshe(vector<string>& yingshe){
    yingshe=vector<string>(ALLDATASIZE);
    
    char ch[10]={'0','1','2','3','4','5','6','7','8','9'};
    yingshe[0]='0';
    for(int i=1;i<ALLDATASIZE;i++){
        int tmp=i;
        
        string TMP;
        while(tmp>0){
            TMP+=ch[tmp%10];
            tmp=tmp/10;
        }
        for(int x=TMP.size()-1;x>=0;x--)
            yingshe[i]+=TMP[x];
    }
     
}
void getdataset(string filename,vector<vector<unsigned int>>& data_g,vector<string>& yingshe,vector<vector<unsigned int>>& last_t)
{
    

     
    int fd = open(filename.c_str(),O_RDONLY);
    int len = lseek(fd,0,SEEK_END);
    char *buf = (char *) mmap(NULL,len,PROT_READ,MAP_PRIVATE,fd,0);
    
    thread ths0(getdata,buf,len,ref(last_t));
    
    data_g=vector<vector<unsigned int>>(ALLDATASIZE);  
    
    
    char *p=buf;    
    unsigned int tmp1=0;
    unsigned int tmp2=0;
    unsigned int key=0;
    
    int num_bian=0;
    while(p-buf<len){             
        while(*p!=','){tmp1=int(*p-'0')+tmp1*10;p++;}
        p++;
        while(*p!=','){tmp2=int(*p-'0')+tmp2*10;p++;}
        while(*p!='\n'){p++;}
        if(tmp1<ALLDATASIZE&&tmp2<ALLDATASIZE)   
        data_g[tmp1].push_back(tmp2);
       
        tmp1=0;
        tmp2=0;
        p++;
    } 
    
        for(auto &line:data_g)
    if(line.size())sort(line.begin(),line.end());
 
    ths0.join();
    
    munmap(buf, len);
    close(fd);  

}



void get_7(bool*l7,bool*l5,bool*l4,unsigned int root,vector<vector<unsigned int>>&data,vector<vector<unsigned int>>& last,char* & data7,char*& data6,char*& data5,char*& data4,char*& data3,vector<string>& yingshe,int &jl_all){
    //vector<unsigned int> xx;
    if(last[root].size()<1||data[root].size()<1) return;
    else if(last[root][last[root].size()-1]<root||data[root][data[root].size()-1]<root) return;
       
    
    for(auto &x:last[root])
        if(x>root) {
            l7[x]=1;
            l5[x]=1; 
            l4[x]=1;
            //xx.push_back(x);
            for(auto &x2:last[x])
                if(x2>root){
                    l5[x2]=1;
                    l4[x2]=1;
                    //xx.push_back(x2);
                    for(auto &x3:last[x2])
                        if(x3>root){
                            l4[x3]=1;
                            //xx.push_back(x3);
                            }
                }
       }      
  
    
     for(auto &t1:data[root])        
        if(t1>root)
        for(auto &t2:data[t1]){
            if(t2>root){
            for(auto &t3:data[t2])
                    if(t3>root&&t3!=t1){
                        for(auto &t4:data[t3])
                                if(l4[t4]&&t2!=t4&&t1!=t4){
                                    for(auto &t5:data[t4])                                        
                                            if(l5[t5]&&t3!=t5&&t2!=t5&&t1!=t5){
                                                for(auto &t6:data[t5])
                                                        if(l7[t6]&&t4!=t6&&t3!=t6&&t2!=t6&&t1!=t6){jl_all++;
                                                        
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
                                                            
                                                        else if(root==t6) 
                                                            {jl_all++;
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
                                            else if(root==t5){jl_all++;
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
                            else if(root==t4){jl_all++;
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
                else if(root==t3){jl_all++;
                                    memcpy(data3, yingshe[root].c_str(),yingshe[root].size());
                                    data3+=yingshe[root].size();*data3=',';data3++;
                                    memcpy(data3, yingshe[t1].c_str(),yingshe[t1].size());
                                    data3+=yingshe[t1].size();*data3=',';data3++;
                                    memcpy(data3, yingshe[t2].c_str(),yingshe[t2].size());
                                    data3+=yingshe[t2].size();*data3='\n';data3++;
                                    
                                }   
                  
            } 
        }

    
       //for(auto &x:xx)
       //{l7[x]=0;l5[x]=0;l4[x]=0;} 
       
    for(auto &x:last[root])
        if(x>root) {
            l7[x]=0;
            l5[x]=0; 
            l4[x]=0;
            //xx.push_back(x);
            for(auto &x2:last[x])
                if(x2>root){
                    l5[x2]=0;
                    l4[x2]=0;
                    //xx.push_back(x2);
                    for(auto &x3:last[x2])
                        if(x3>root){
                            l4[x3]=0;
                            //xx.push_back(x3);
                            }
                }
       } 
       
     
}

inline bool isinset(unsigned int x, vector<vector<unsigned int>>& last_t){

    for(auto &nt:last_t[x])
        if(nt>x) return 1;
        
     return 0;//
}
inline bool isinnet(unsigned int x, vector<vector<unsigned int>>& data_g){

    for(auto &nt:data_g[x])
        if(nt>x) return 1;
        
      return 0;//
}



void thr(int index,vector<vector<unsigned int>>& data_g,vector<vector<unsigned int>>& last_t,char* data7,char* data6,char* data5,char* data4,char* data3,vector<string>& yingshe,int &jl_all,unsigned int* len3,unsigned int* len4,unsigned int* len5,unsigned int* len6,unsigned int* len7){
    bool *l7=new bool[data_g.size()];
    bool *l5=new bool[data_g.size()];
    bool *l4=new bool[data_g.size()];

    for(int i=0;i<ALLDATASIZE;i++){
        if(i%4==index){
                char *p3=data3;
                char *p4=data4;
                char *p5=data5;
                char *p6=data6;
                char *p7=data7;
                
                  get_7(l7,l5,l4,i,data_g,last_t,data7,data6,data5,data4,data3,yingshe,jl_all); 
                           
                len3[i]=data3-p3;
                len4[i]=data4-p4;
                len5[i]=data5-p5;
                len6[i]=data6-p6;
                len7[i]=data7-p7;
            }
        }
gettimeofday(&t2,NULL);
    timeuse = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec)/1000000.0;
    printf(" %d out  Use Time:%fs\n",index, timeuse);    
     

}

void thr_out_data(int index,char* ans,char *px3[4],char *px4[4],char *px5[4],char *px6[4],char *px7[4],unsigned int *len3,unsigned int *len4,unsigned int *len5,unsigned int *len6,unsigned int *len7){
 
   
    char*p3[4]={px3[0],px3[1],px3[2],px3[3]};
    char*p4[4]={px4[0],px4[1],px4[2],px4[3]};
    char*p5[4]={px5[0],px5[1],px5[2],px5[3]};
    char*p6[4]={px6[0],px6[1],px6[2],px6[3]};
    char*p7[4]={px7[0],px7[1],px7[2],px7[3]};
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
gettimeofday(&t2,NULL);
    timeuse = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec)/1000000.0;
    printf(" %d out  Use Time:%fs\n",index, timeuse);    
     

}

int main(){
    
    gettimeofday(&t1,NULL);
    string test_file="data/1004812/test_data.txt";
    string out_file="data/my_out1.txt";
    
    //string test_file="/data/test_data.txt";
    //string out_file="/projects/student/result.txt";
    vector<vector<unsigned int>> data_g;//data_g[x] ->lin jie biao
    vector<string>yingshe;//key->value
    
    
    vector<vector<unsigned int>> last_t;
    
    thread ths1(get_str_yingshe,ref(yingshe));
    
    thread ths12(getdataset,test_file,ref(data_g),ref(yingshe),ref(last_t));
 

    //get_last_t(data_g,last_t);


      
    int TX=4;
     
    unsigned int QW=2000000; 
    char* strx3[TX];
    char* strx4[TX];
    char* strx5[TX];
    char* strx6[TX];
    char* strx7[TX];
    
    for(int x=0;x<TX;x++){
        strx3[x]=new char [3*QW];
    
        strx4[x]=new char [4*QW];        
    
        strx5[x]=new char [5*2*QW];
    
        strx6[x]=new char [6*2*QW];        
    
        strx7[x]=new char [7*4*QW];        
    
    }           
 
     unsigned int *str_len3=new unsigned int[ALLDATASIZE];
    unsigned int *str_len4=new unsigned int[ALLDATASIZE];
    unsigned int *str_len5=new unsigned int[ALLDATASIZE];
    unsigned int *str_len6=new unsigned int[ALLDATASIZE];
    unsigned int *str_len7=new unsigned int[ALLDATASIZE];
    
    ths12.join();

    
    unsigned int datastr[TX*5]={0}; 
   
    
    ths1.join();
    vector<thread*> ths; 
    
    

    int jl_all[TX]={0};    
    for(int x=0;x<TX;x++)
    {
    
    ths.push_back(new thread(thr,x,ref(data_g),ref(last_t),strx7[x],strx6[x],strx5[x],strx4[x],strx3[x],ref(yingshe),ref(jl_all[x]),ref(str_len3),ref(str_len4),ref(str_len5),ref(str_len6),ref(str_len7)));
    }
    for (auto& th : ths)  th->join();
    for (auto& th : ths)  delete(th);

 
    unsigned int strsize=0;   
    unsigned int strsize3=0; 
    unsigned int strsize4=0; 
    unsigned int strsize5=0; 
    unsigned int strsize6=0; 
    unsigned int strsize7=0; 
    for(int x=0;x<ALLDATASIZE;x++)  {
                strsize3+=str_len3[x];      
                strsize4+=str_len4[x];
                strsize5+=str_len5[x];
                strsize6+=str_len6[x];
                strsize7+=str_len7[x];
            }
              
    strsize=strsize3+strsize4+strsize5+strsize6+strsize7;

       
    int datasize=0;    
for(int x=0;x<TX;x++)
    {
        datasize+=jl_all[x];
    }    
    string outstr=to_string(datasize)+'\n';
    //cout<<outstr<<endl;
   
   
    gettimeofday(&t2,NULL);
    timeuse = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec)/1000000.0;
    printf(" write begin  Use Time:%fs\n", timeuse);    
    
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
        
        
  vector<thread*> ths2;
     for(int x=0;x<TX;x++)
     ths2.push_back(new thread(thr_out_data,x,ans,p3,p4,p5,p6,p7,str_len3,str_len4,str_len5,str_len6,str_len7));
     
    for (auto& th : ths2)  th->join();
    for (auto& th : ths2)  delete(th);

    munmap(buf, strsize+outstr.size());
    
     gettimeofday(&t2,NULL);
    timeuse = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec)/1000000.0;
    printf(" end  Use Time:%fs\n", timeuse);    
          
 
    exit(0); 
    return 0;    
     
}
