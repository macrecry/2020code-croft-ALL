#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <thread>


#include <fcntl.h>
#include <unistd.h>

#include <sys/mman.h>

using namespace std;
#include <sys/time.h>
struct timeval t1,t2;
float timeuse;

inline float sigmoidCalc(const float wxb)
{
    
    float expv = exp(-1 * wxb);
    float expvInv = 1 / (1 + expv);
    
    return expvInv;
}
/*
inline float sigmoidCalc(const float wxb)
{
    
    if(wxb<-2) return 0.01;
    if(wxb>2)  return 0.99;
    return sig_index[(int)(wxb*100)+200];
}
*/
class Data {
public:
    int _m,_n;
    float **_data;
    int *_label;
    float *_wight;
    float *_pyc;
    int bitch_size;
    Data(const  int m, const  int n){
        _m=m;
        _n=n;

    }
    /*
    ~Data(){
    if (!_data)for(int x=0;x<_m;x++) delete(_data[x]);
    if (!_label)delete(_wight);
    if (!_wight)delete(_label);
    if (!_pyc)delete(_pyc);

}*/

     void thread_js_pyc(int i,int size_n){
        
            for(int k=0;k<size_n;k++){
            float tmp=0;
            for(int j=0;j<this->_n;j++)
                tmp+=this->_data[i][j]*this->_wight[j];
            this->_pyc[i]=sigmoidCalc(tmp);
            i++;
            }
        

    }
    
    void get_pyc(){

        int i;
        
        int m=this->_m;
        int n=this->bitch_size ;

        vector<thread*> threads;
        for(i=0;i+n < m;i+=n)
            threads.push_back(new thread(&Data::thread_js_pyc,this,i,n));
        if(i<this->_m)
            threads.push_back(new thread(&Data::thread_js_pyc,this,i,m-i));
     
        for (auto& th : threads) th->join(); 
        for (auto& th : threads)  delete(th);



    }



     void thread_js_pyc2(int i,int size_n,float *lr){
            
            for(int k=0;k<size_n;k++){
            float tmp=0;//预测值
            for(int j=0;j<this->_n;j++)
            {
                tmp+=this->_data[i][j]*this->_wight[j];
            }
            tmp=sigmoidCalc(tmp);
            for(int j=0;j<this->_n;j++){
                 lr[j]+= (this->_data[i][j]*(this->_label[i]-tmp));
                          
            }
            
            i++;
            }


    }
    
    void get_pyc2(float stepSize,int i,float **tmp){

        vector<thread*> threads;
        int s=this->bitch_size/4;
       
        for(int k=0;k<4;k++){
            
            for(int j=0;j<this->_n;j++)
                tmp[k][j]=0;
            threads.push_back(new thread(&Data::thread_js_pyc2,this,i,s,tmp[k]));
            i+=s;
        }

        for (auto& th : threads) th->join(); 
        for (auto& th : threads)  delete(th);

        float tmpx=0;
         
        for (int j=0;j<this->_n;j++){
            for(int k=0;k<4;k++) tmpx+=tmp[k][j];
            this->_wight[j]+=stepSize *tmpx/this->_m;
            tmpx=0;
        }
 

    }







/*
void analyse1(char *buf,int index,int km)
{
    

    char *p=buf;
    int max_m=this->_m/4*(km+1);
    int x=this->_m/4*km;
    int y=0;
    p+=index;
    if(index!=0) while(*p!='\n') {p++;}
    
    for (;*p && x<max_m;p++){


         if(*p == '.')
         { 
            if(*(p-2)=='-')
                this->_data[x][y] =0-((int)(*(p-1) - '0')+ (int)(*(p+1) - '0')*0.1);
            else  this->_data[x][y] =((int)(*(p-1) - '0')+ (int)(*(p+1) - '0')*0.1);
             y++;
             if(y==this->_n){this->_label[x]=(int)(*(p+5)-'0');y=0;x++;p+=7;}
            else p+=5;
         }
    }
   
}

void loadTrainData1(string filename)
{

    
      int MAXS = 8*this->_m*this->_n;
    
    char *buf=new char[MAXS];
    vector<thread*> ths;
    int fd=open(filename.c_str(),O_RDONLY);   
    int len = read(fd,buf,MAXS);
    buf[len] = '\0';
    int index=0;
    for(int i=0;i<4;i++)
    { 
        ths.push_back(new thread(&Data::analyse1,this,buf,index,i));
        index+=len/4;
    }
    
    for (auto& th : ths) th->join(); 
    for (auto& th : ths)  delete(th);
    close(fd);
    delete(buf);
    gettimeofday(&t2,NULL);
    timeuse = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec)/1000000.0;
    printf("load train Use Time:%fs\n", timeuse); 
 
}

*/

void analyse1(char *buf)
{
    

    char *p=buf;
    int x=0;
    int y=0;
    
    for (;*p && x<this->_m;p++){

        
         if(*p == '.')
         { 
            if(p-2>buf&&*(p-2)=='-')
                this->_data[x][y] =0-((int)(*(p-1) - '0')+ (int)(*(p+1) - '0')*0.1);
            else  this->_data[x][y] =((int)(*(p-1) - '0')+ (int)(*(p+1) - '0')*0.1);
             y++;
             if(y==this->_n){this->_label[x]=(int)(*(p+5)-'0');y=0;x++;p+=7;}
            else p+=5;
         }
    }
   
}
void analyse11(char *buf)
{
    

    char *p=buf;
    int x=0;
    int y=0;
    while(x<this->_m/2) if(*p=='\n'){x++;p+=6000;}else{p++;}
    for (;*p && x<this->_m;p++){

        
         if(*p == '.')
         { 
            if(p-2>buf&&*(p-2)=='-')
                this->_data[x][y] =0-((int)(*(p-1) - '0')+ (int)(*(p+1) - '0')*0.1);
            else  this->_data[x][y] =((int)(*(p-1) - '0')+ (int)(*(p+1) - '0')*0.1);
             y++;
             if(y==this->_n){this->_label[x]=(int)(*(p+5)-'0');y=0;x++;p+=7;}
            else p+=5;
         }
    }
   
}
void loadTrainData1(string filename)
{

        /*
      int MAXS = 10*this->_m*this->_n;
    
    char *buf=new char[MAXS];
   
    int fd=open(filename.c_str(),O_RDONLY);   
    int len = read(fd,buf,MAXS);
    buf[len] = '\0';
    int index=0;
    */
    int fd = open(filename.c_str(),O_RDONLY);
    int len = lseek(fd,0,SEEK_END);
    char *buf = (char *) mmap(NULL,len,PROT_READ,MAP_PRIVATE,fd,0); 

 
    thread th(&Data::analyse11,this,buf);
    this->analyse1(buf);
    th.join();
    close(fd);

    gettimeofday(&t2,NULL);
    timeuse = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec)/1000000.0;
    printf("load train Use Time:%fs\n", timeuse); 
 
}

void analyse(char *buf,int index,int len,int i,string* strx)
{
    
    char *p=buf;
    p+=index;
    p+=2;
    float ycz=0;
    
    for (;*p && p-buf<len;){
        for(int k=0;k<this->_n;k++)
            {ycz+=this->_wight[k]*(float)(*p-'0');  p+=6;}

    *strx+=to_string(ycz<0?0:1)+'\n';ycz=0;
    
    }
       
}
void loadTrainData2(string filename,string outfile)
{


     int MAXS = 6*this->_m*this->_n;
    
    string outstr;

    int fd = open(filename.c_str(),O_RDONLY);
    int len = lseek(fd,0,SEEK_END);
    char *buf = (char *) mmap(NULL,len,PROT_READ,MAP_PRIVATE,fd,0); 
    vector<thread*> ths;
    int tmp=len/4;
    int index=0;
    string *str1=new string;
    string *str2=new string;
    string *str3=new string;
    string *str4=new string;
    
    ths.push_back(new thread(&Data::analyse,this,buf,0,tmp,index,str1));
    index+=len/(6*4);
    ths.push_back(new thread(&Data::analyse,this,buf,1*tmp,2*tmp,index,str2));
    index+=len/(6*4);
    ths.push_back(new thread(&Data::analyse,this,buf,2*tmp,3*tmp,index,str3));
    index+=len/(6*4);
    ths.push_back(new thread(&Data::analyse,this,buf,3*tmp,4*tmp,index,str4));
    
    for (auto& th : ths) th->join(); 
    for (auto& th : ths)  delete(th);
    close(fd);

    outstr=*str1+*str2+*str3+*str4;
    outstr.pop_back();
    ofstream fout(outfile.c_str());
    fout <<outstr<< endl;
    fout.close();

    gettimeofday(&t2,NULL);
    timeuse = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec)/1000000.0;
    printf("load test Use Time:%fs\n", timeuse);  
}




void storePredict(string filename)
{
    string line;
    int i;
    ofstream fout(filename.c_str());
    
    for (i = 0; i < this->_m-1; i++) 
        line+=to_string(this->_pyc[i]<0.5?0:1)+'\n';
        line+=to_string(this->_pyc[i]<0.5?0:1);
        fout <<line << endl;
    
    fout.close();

}
};



void load_m_n(string filename,int &index,int &tz)
{
  
    //char *buf=new char[MAXS];
    int fd = open(filename.c_str(),O_RDONLY);
    int len = lseek(fd,0,SEEK_END);
    char *buf = (char *) mmap(NULL,len,PROT_READ,MAP_PRIVATE,fd,0);
 
    tz=1000;
    
    char *p=buf;
    p+=5999;
    for (; p-buf<len;){
        index++;p+=6000;
          
    }

    close(fd);
}


void loadAnswerData(string awFile, vector<int> &awVec)
{
    ifstream infile(awFile.c_str());
    if (!infile) {
        cout << "打开答案文件失败" << endl;
        exit(0);
    }

    while (infile) {
        string line;
        int aw;
        getline(infile, line);
        if (line.size() > 0) {
            stringstream sin(line);
            sin >> aw;
            awVec.push_back(aw);
        }
    }

    infile.close();
    
}
int partition(float* array,int begin,int end){
        if(begin<end){
            float key=fabsf(array[begin]);
            while(begin<end){
                while(begin<end&&fabsf(array[end])>key){
                    end--;
                }
                if(begin<end){
                    array[begin]=fabsf(array[end]);
                    begin++;
                }
                while(begin<end&&fabsf(array[begin])<key){
                    begin++;
                }
                if(begin<end){
                    array[end]=fabsf(array[begin]);
                    end--;
                }
            }
            array[begin]=key;
        }
        return begin;       
    }

float findk(float* array,int begin,int end,int k){
        int i=partition(array,begin,end);
        //找出i+1大的数与k比较
        if(i+1>k){
            findk(array,begin,i-1,k);
        }else if(i+1<k){
            findk(array,i+1,end,k);
        }else{
           
            return array[i];
        }
    }
    //一趟快排

int main(int argc, char *argv[])
{
    gettimeofday(&t1,NULL);
    string trainFile = "data/train_data.txt";
    string testFile = "data/test_data.txt";
    string predictFile = "projects/student/result.txt";
    string answerFile = "projects/student/answer.txt";
    string cefile= "data/data2.txt";
    int index=0;
    int tz=0;
    int xl=1024;
    load_m_n(cefile,index,tz);
    
  

    Data train_data(xl,tz);
        train_data._wight=new float[tz];
        for(int i=0;i<tz;i++)
            train_data._wight[i]=1;
        train_data._data= new float*[xl];
        for(int i=0;i<xl;i++)
            train_data._data[i]=new float[tz];
        train_data._label=new int[xl];      
        
        train_data.bitch_size=256;

    Data test_data(index,tz);

    
    train_data.loadTrainData1(trainFile);

 
    float stepSize=4.5;
    int x_x_n=train_data.bitch_size;
    int y_y_n=train_data._m/x_x_n;
    
    float **tmp=new float*[4];
    for(int k=0;k<4;k++)
        tmp[k]=new float[train_data._n];
    for(int i=0;i<6;i++){
        for( int k=0;k<y_y_n;k++){
           
            train_data.get_pyc2(stepSize,k*x_x_n,tmp);   
        }
        //for(int j=0;j<1000;j++)if(fabsf(train_data._wight[j])<0.01) train_data._wight[j]=0;
        stepSize=stepSize*(1-1.0/(4)); 
    }
     gettimeofday(&t2,NULL);
    timeuse = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec)/1000000.0;
    printf(" Use Time:%fs\n", timeuse);  
    test_data._wight=train_data._wight;
    float txmp[1000];
    int y_xs[500];
    float maxs=0;
    for(int i=0;i<1000;i++){
        txmp[i]=train_data._wight[i];
        if(maxs<train_data._wight[i]) maxs=train_data._wight[i];
    }
    cout<<maxs<<endl;
    /*
    test_data._wight=new float[500];
    float txmp[1000];
    int y_xs[500];
    for(int i=0;i<1000;i++){
        txmp[i]=train_data._wight[i];
    }
    float kxiao=findk(txmp,0,999,500);
    int count=0;
    for(int i=0;i<1000;i++){
        if(fabsf(train_data._wight[i])>kxiao){
            test_data._wight[count]=train_data._wight[i];
            y_xs[count]=i;
            count++;
        }
    }   
    */ 
    
    test_data.loadTrainData2(cefile,predictFile); 

    vector<int> answerVec;
    vector<int> predictVec;
    int correctCount;
    loadAnswerData(answerFile, answerVec);
    loadAnswerData(predictFile, predictVec);
    correctCount = 0;
    for (int j = 0; j < predictVec.size(); j++) {
        if (j < answerVec.size()) {
            if (answerVec[j] == predictVec[j]) {
                correctCount++;
            }
        } 
    }
    double accurate = ((double)correctCount) / answerVec.size();
    cout << "the prediction accuracy is " << accurate << endl;
    
    //cout<<findk(a,0,4,5)<<endl; 
                     
    return 0;
}
