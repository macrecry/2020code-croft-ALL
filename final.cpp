#include <cmath>
#include <queue>
#include <thread>
#include <time.h>
#include<cstring>
#include <vector>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <utility>
#include <fcntl.h>
#include <unistd.h>
#include<algorithm>
#include <string.h>
#include <iostream>
#include<stdexcept>
#include<functional>
#include <sys/mman.h>
#include <sys/time.h>
#include<unordered_map>
#include<unordered_set>
#include <bits/stdc++.h>
using namespace std;


uint32_t ALLDATASIZE;//图中顶点数
uint32_t MAXDATASIZE=1024000;//最大顶点数
uint32_t THX=12;//线程数
uint64_t MAXz=0;//判断最大路径长度
atomic<uint32_t> RW(1);//原子量分配任务

uint32_t DIL [7500000];//输入边
uint32_t DATA[5000000];//图前向星
uint32_t DLEN[1024000];//前向星长度

//uint32_t dis32x[12][1024000];//32位距离
double      ans[12][1024000];//答案
uint32_t      outys[1024000];//输出映射
unordered_map<uint32_t,uint32_t> in_ys;//输入映射
string testfile="/data/test_data.txt";//读入文件
string out_file="/projects/student/result.txt";//输出文件
typedef pair<uint64_t,uint32_t> P1;
typedef pair<uint32_t,uint32_t> P2;

typedef struct {
    bool     vis[1024000];//标记是否已访问
    uint8_t  lpe[1024000];//多条路径的前向星
    uint16_t pre[1024000];//到目标点路径数
    uint32_t sta[1024000];//更新答案用的栈
    double   tpp[1024000];//临时计算答案用
    uint32_t mpe[1024000][50];//多条路径的前一个节点
    
}THD;//线程所用变量
struct node32{
	uint32_t first;
	uint32_t second;
	node32(){first=0;second=0;};
	node32(const uint32_t& _first,const uint32_t& _second):first(_first),second(_second){}
	bool operator < (const node32 &r)const {return first>r.first;}//32位优先队列所用结构，默认最大堆，所用重载<为大于;
	node32 operator = (const node32 &r) {first=r.first;second=r.second; return *this;}//重载赋值
};//32位优先队列所用结构
class HEAP{//带更新的手写堆
    public:
        node32 node[1024000];
        uint32_t id[1024000];//用于更新队列里权值
        int size;
        bool empty(){return size==0?1:0;}//堆是否为空
        inline void swapn(node32 &x,node32 &y){auto p=x;x=y;y=p;}//交换
        
        void up(node32 x){  //堆的上浮
            node[id[x.second]].first=x.first;//更新队列中的权值
	        for(int i=id[x.second],j=i>>1;j;i=j,j>>=1){
		        if(node[i]<node[j]) {
		            swapn(node[i],node[j]);
		            swap(id[node[i].second],id[node[j].second]);
		        }
		        else break;
	        }
	        return;            
        }
        void push(node32 x){    //插入节点
            node[++size]=x;
            id[x.second]=size;
            up(x);
        }
        node32 top(){   //最大权重值
            return node[1];
        }

	    void pop() {    //删除最大权值
	        id[node[size].second]=1;
	        id[1]=0;	
	        swapn(node[1],node[size]);
	        size--;	      
	        int i=1;          
	        for(int j=2;j<=size;i=j,j<<=1)
	        {
	            if(j<size&&node[j+1]<node[j]) j++;
	            if(node[j]<node[i]) {
	                swapn(node[i],node[j]);
		            swap(id[node[i].second],id[node[j].second]);
	            }
	            else break;
            }
            
	    } 
};

//THD thdx[12];//实例化全局变量
//HEAP heapx[12]; 
void th_in_ys(int index,int lenend){//多线程映射

    for(int i=index;i<lenend;i+=3)
    {
        DIL[i]=in_ys.at(DIL[i]);
        DIL[i+1]=in_ys.at(DIL[i+1]);
    }
}

void getdata(){//读入数据，构建图

    int fd = open(testfile.c_str(),O_RDONLY);
    uint64_t len = lseek(fd,0,SEEK_END);
    char *buf = (char *) mmap(NULL,len,PROT_READ,MAP_PRIVATE,fd,0);//mmap读入文件为字符指针
    
    vector<uint32_t> paixu;//用于排序

    char *p=buf;
    uint32_t tmp1=0;
    uint32_t tmp2=0;
    uint32_t key =0; 
    uint32_t Y=0;   
    char *km=buf;
    km+=len;
    while(p<km){              
        while(*p!=','){
            tmp1=int(*p-'0')+tmp1*10;
            p++;
        }
        p++;
        while(*p!=','){
            tmp2=int(*p-'0')+tmp2*10;
            p++;
        }
        p++;
        while(*p!='\n'&&*p!='\r'){
            key=int(*p-'0')+key*10;
            p++;
        }
        if(*p=='\r') 
            p++;
        if(key!=0){
            paixu.push_back(tmp1);
            paixu.push_back(tmp2); 
            DIL[Y++]=tmp1;  
            DIL[Y++]=tmp2;  
            DIL[Y++]= key; 
            if(key>MAXz)MAXz=key;
        }        
        tmp1=0;
        tmp2=0;
        key=0;        
        p++;
    }     
    munmap(buf, len);
    close(fd); 
    sort(paixu.begin(),paixu.end());//点大小排序   
    ALLDATASIZE=unique(paixu.begin(),paixu.end())-paixu.begin();//去重，计算最大点数    
    for(int i=1;i<=ALLDATASIZE;i++){
        in_ys.insert({paixu[i-1],i});//输入映射
        outys[i]=paixu[i-1];//输出映射
    }
    int canshu[9]={0};
    for(int i=1;i<8;i++) 
        canshu[i]=(int)(Y/24)*3*i;
    canshu[8]=Y;
    vector<thread*>thr;
    for(int i=0;i<8;i++)
        thr.push_back(new thread(th_in_ys,canshu[i],canshu[i+1]));//多线程映射
    for(auto th:thr) th->join();
    
    vector<vector<P2>>data_g(ALLDATASIZE+1);//构建前向星
      
        for(int i=0;i<Y;i+=3)       
                data_g[DIL[i]].push_back(make_pair(DIL[i+1],DIL[i+2]));

        for(auto& line:data_g)
            sort(line.begin(),line.end());//排序获取更好的cache性能
        int num=0;
        DLEN[0]=0;
        for(int i=0;i<=ALLDATASIZE;i++){
            for(auto x:data_g[i]){                
                DATA[num++]=x.first;
                DATA[num++]=x.second;
            }
            DLEN[i+1]=num;//前向星位移数组        
        }
}

bool cmpsize(pair<double,uint32_t>&line1,pair<double,uint32_t>&line2)//输出排序
{
    if(abs(line1.first -line2.first)>0.0001) return line1.first>line2.first;
    return line1.second<line2.second;    
}
void out_data(){//输出
    for(int i=1;i<THX;i++){
        for(int j=1;j<=ALLDATASIZE;j++)
            ans[0][j]+=ans[i][j];//合并答案
    }        
    vector<pair<double,uint32_t>> out_data(ALLDATASIZE);
    for(int i=1;i<=ALLDATASIZE;i++)
        out_data[i-1]=pair<double,uint32_t>(ans[0][i],i);
    sort(out_data.begin(),out_data.end(),cmpsize);//排序
    int MINXX=ALLDATASIZE>100?100:ALLDATASIZE;
    FILE *fp=fopen(out_file.c_str(), "w");
    for(int i=0;i<MINXX;i++)               
        fprintf(fp,"%u,%.3f\n",outys[out_data[i].second],out_data[i].first);//输出
 
}


void dij1(uint32_t s,uint32_t index,THD &thdx,uint32_t* dis32,uint32_t&INF){//32位dij
    
    int nM=0;
    dis32[s]=0;
    thdx.pre[s]=1;
    priority_queue<node32> que; //优先队列 
    //heap.push(node32(0,s));
    que.push(node32(0,s));
    while(!que.empty())
    {   
        //node32 p=heap.node[1];
        //heap.pop();
        node32 p=que.top();
        que.pop();
        auto &v=p.second;  
        if(thdx.vis[v]){ continue;} 
        thdx.vis[v]=1;  
        thdx.sta[nM++]=v;//模拟栈用于更新答案
        for(uint32_t i=DLEN[v];i<DLEN[v+1];i+=2) //前向星    
        {            
            if(thdx.vis[DATA[i]]==0){//已访问的不再访问
                auto& w=DATA[i];
                auto KK=dis32[v]+DATA[i+1];               
                if(dis32[w]>KK){//更新距离
                    thdx.lpe[w]=0;                                            
                    dis32[w]=KK;                    
                    thdx.pre[w]=thdx.pre[v];
                    thdx.mpe[w][thdx.lpe[w]++]=v;
                    que.push(node32(KK,w));//插入队列
           
                }                
                 else if(dis32[w]==KK){    //多条最短路径            
                    thdx.mpe[w][thdx.lpe[w]++]=v;
                    thdx.pre[w]+=thdx.pre[v];
                } 
            }            
        }        
    }
    dis32[s]=INF;
    thdx.tpp[s]=0;    
    thdx.lpe[s]=0;
    thdx.vis[s]=0;
    while(nM){
        nM--;
        auto &w=thdx.sta[nM];
        
        for(auto i=0;i<thdx.lpe[w];i++){//根据栈中元素遍历不同路径
            auto &v=thdx.mpe[w][i];
            if(v!=s)
                thdx.tpp[v]+=(1.0+thdx.tpp[w])*thdx.pre[v]/thdx.pre[w];//公式计算
        }        
        
        ans[index][w]+=thdx.tpp[w];//更新答案
        dis32[w]=INF;//初始化
        thdx.tpp[w]=0;        
        thdx.vis[w]=0;
        thdx.lpe[w]=0;
        thdx.pre[w]=0;
    }  
    
}
void thrs1(uint32_t index){//多线程运算
    uint32_t INF32=pow(2,32);
    
        THD *thdx=new THD;
        THD&  thd=*thdx;
        uint32_t *dis32x=new uint32_t[1024000];
        for(int j=0;j<=ALLDATASIZE;j++){//初始化
            thd.vis[j]=0;
            thd.pre[j]=0;
            thd.lpe[j]=0;
            thd.tpp[j]=0;
            ans[index][j]=0;
            dis32x[j]=INF32;
        }         
        uint32_t i = RW.fetch_add(1);//原子量分配任务
        while(i<=ALLDATASIZE){
                dij1(i,index,thd,dis32x,INF32);              
            i=RW.fetch_add(1); 
            
        }                   
   
}

int main(){

    getdata();//获取数据
          
    vector<thread*> thr;
    
    for(int k=0;k<THX;k++) 
                
        thr.push_back(new thread(thrs1,k));//多线程运算
                
    for(auto &th:thr) 
    
        th->join();
    
    out_data();//输出
      
    exit(0); 
    
    return 0;    
     
}
