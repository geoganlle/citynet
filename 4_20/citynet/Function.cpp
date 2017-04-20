#include<iostream>
#include"CITYNET.h"
#include<stdlib.h>
#include<stdio.h>
#include<queue>
#include <ctime>
#include<fstream>

using namespace std;

/*第一题*/
extern bool Creat(int a,int b){//线路数目检验
        if(b>(a*(a-1)/2)||b<=0)return false;
        else return true;
}

Citynet::Citynet(int n,int m){
        cn=n;
        ln=m;
        creatline();
        //cout<<"        构建成功"<<endl;
}
Citynet::~Citynet(){
        for(int i=0;i<cn;i++){
                delete[] p[i];
        }
        delete[] p;
        //cout<<"城市矩阵P1析构成功"<<endl;
        for(int i=0;i<cn;i++){
                delete[] p2[i];
        }
        delete[] p2;
        //cout<<"关键线路P2析构成功"<<endl;
        for(int i=0;i<cn;i++){
                delete[] unp[i];
        }
        delete[] unp;
        //cout<<"冗余线路UNP析构成功"<<endl;

}
void Citynet::creatline(){//创建矩阵
        p=new int* [cn];//网络初始化
        for(int i=0;i<cn;i++){
                p[i]=new int[cn];
        }
        for(int row=0;row<cn;row++){
                for(int col=0;col<cn;col++){
                        p[row][col]=0;
                }
        }
        p2=new int* [cn];//网络初始化
        for(int i=0;i<cn;i++){
                p2[i]=new int[cn];
        }
        for(int row=0;row<cn;row++){
                for(int col=0;col<cn;col++){
                        p2[row][col]=0;
                }
        }

        unp=new int* [cn];//冗余网络初始化
        for(int i=0;i<cn;i++){
                unp[i]=new int[cn];
        }
        for(int row=0;row<cn;row++){
                for(int col=0;col<cn;col++){
                        unp[row][col]=0;
                }
        }


        while(!IsFull(p)){

                for(int row=0;row<cn;row++){
                        for(int col=0;col<cn;col++){
                                p[row][col]=0;
                                unp[row][col]=0;
                        }
                }

                for(int mn=0;mn<ln;mn++){//创建网络
                        int a=rand()%cn;
                        int b=rand()%cn;
                        if(a<b){
                                if(p[a][b]==0){
                                        if(CheckLine(a,b)==false)//不联通
                                        p[a][b]=p[b][a]=1;
                                        else{//连通
                                        if(unp[a][b]==0)//未记录该冗余边
                                        unp[a][b]=unp[b][a]=1;
                                        mn--;//已存在该冗余边
                                        }
                                }
                        }//不直接相连且不连通
                        else mn--;//a b直接相连
                }
        }

//        cout<<"-------------------------"<<endl;
//        cout<<"         第一题          "<<endl;
//        cout<<"-------------------------"<<endl;
//        cout<<"        冗余矩阵"<<endl;
        //行标列标，建议 n<10
        ofstream unfile("undata.txt",ios::trunc);
        //cout<<"  ";
        for(int col=0;col<cn;col++){
        //        cout<<col+1<<" ";
        }
        cout<<endl;
        for(int row=0;row<cn;row++){
                //cout<<row+1<<" ";//行标
                for(int col=0;col<cn;col++){
                        //cout<<unp[row][col]<<" ";
                        unfile<<unp[row][col]<<" ";
                }
                //cout<<endl;
                unfile<<"\n";
        }
        //cout<<endl;
        unfile.close();

}
void Citynet::print(){//打印矩阵
        ofstream datafile("p1.txt",ios::trunc);
        //cout<<endl;
        //cout<<"         矩阵P1"<<endl;
//注释部分为行标列标，仅n<10
        //cout<<"  ";
        for(int col=0;col<cn;col++){
                //cout<<col+1<<" ";
        }
        //cout<<endl;
        for(int row=0;row<cn;row++){
                //cout<<row+1<<" ";//行标
                for(int col=0;col<cn;col++){
                        //cout<<p[row][col]<<" ";
                        datafile<<p[row][col]<<" ";
                }
                //cout<<endl;
                datafile<<"\n";
        }
        //cout<<endl;
        datafile.close();
}

void Citynet::scanfnet(){
        cout<<"||||||||遍历函数||||||||"<<endl;
        cout<<"         邻接表"<<endl;
        for(int row=0;row<cn;row++){
                cout<<row+1<<" ";
                for(int col=0;col<cn;col++){
                        //cout<<p[row][col]<<" ";
                        if(p[row][col]==1){
                                cout<<"->"<<col+1;
                        }
                }
                cout<<endl;
        }
        cout<<endl;
        cout<<"      广度优先遍历"<<endl;
        //广度优先遍历
        int *visited;//访问标记位
        visited=new int[cn];
        for(int i=0;i<cn;i++)visited[i]=0;//访问数组初始化

        queue<int> q;
        q.push(0);
        visited[0]=1;//入队 访问到
        while(!q.empty()){
                int row=q.front();//出队一个元素
                q.pop();
                cout<<row+1<<" ";
                for(int col=row+1;col<cn;col++){
                        if(p[row][col]==1&&visited[col]==0){
                        q.push(col);
                        visited[col]=1;//入队 访问到
                        }
                }
        }
        cout<<endl;
        cout<<"||||||||||||||||||||||||"<<endl;
}

bool Citynet::CheckLine(int a,int b){//检查两边是否连通
        //广度优先遍历
        int *visited;//访问标记位
        visited=new int[cn];
        for(int i=0;i<cn;i++)visited[i]=0;//访问数组初始化

        queue<int> q;
        q.push(a);
        visited[a]=1;//入队 访问到
        while(!q.empty()){
                int row=q.front();//出队一个元素
                q.pop();
                if(row==b)return true;
                for(int col=0;col<cn;col++){
                        if(p[row][col]==1&&visited[col]==0){
                        q.push(col);
                        visited[col]=1;//入队 访问到
                        }
                }
        }
        return false;
}

///////////////////////////////////////////////////////////////////////////////////

/*第二题*/
int vn=0;
int r=0;
int *vx;
void Citynet::create(int m,int n){
        for(int i=0;i<cn;i++){
                for(int j=0;j<cn;j++){
                        p2[i][j]=p[i][j];
                        if(unp[i][j]==1&&p[i][j]==0){
                                p2[i][j]=1;
                        }
                }
        }

//        cout<<"-------------------------"<<endl;
//        cout<<"         第二题          "<<endl;
//        cout<<"-------------------------"<<endl;
//        cout<<"         矩阵P2"<<endl;
//        cout<<"  ";
        for(int col=0;col<cn;col++){
                //cout<<col+1<<" ";
        }
        //cout<<endl;
        for(int row=0;row<cn;row++){
                //cout<<row+1<<" ";//行标
                for(int col=0;col<cn;col++){
                        //cout<<p2[row][col]<<" ";
                }
                //cout<<endl;
        }
        //cout<<endl;
        ofstream out("p2.txt");
        for (int i=0;i<cn;i++){
                for(int j=0;j<cn;j++){
                        out<<p2[i][j]<<" ";
                }
                out<<endl;
        }
        out.close();
}

void Citynet::secure(){

        int a[cn][cn];
        for(int i=0;i<cn;i++){
                for(int j=0;j<cn;j++){
                        a[i][j]=0;
                }
        }
        //cout<<"不可靠线路:"<<endl;
        bool t;
        for(int i=0;i<cn;i++){
                for(int j=i;j<cn;j++){
                        if(p2[i][j]==1){

                                p2[i][j]=p2[j][i]=0;
                                t=DFSTraverseM();
                                        if(t==true){a[i][j]=a[j][i]=1;
                                                //cout<<i+1<<"-"<<j+1<<endl;vn=0;
                                        }
                                p2[i][j]=p2[j][i]=1;
                        }
                }
        }
        //cout<<endl;
        ofstream out("secure.txt");
        for(int i=0;i<cn;i++){
                //cout<<"  ";
                for(int j=0;j<cn;j++){
                        //cout<<a[i][j]<<" ";
                        out<<a[i][j]<<" ";
                }
                //cout<<endl;
                out<<endl;
        }
        out.close();

}
double random(double start, double end)      //随机数生成函数
{
    return start+(end-start)*rand()/(RAND_MAX + 1.0);
}


////////////////////////////*深度优先遍历*////////////////////////////
bool Citynet::DFSTraverseM(){
        vx=new int[cn];
        vn=0;
        for(int m=0;m<cn;m++){vx[m]=-1;}
        visited=new int[cn];
        for(int i=0;i<cn;i++){
                visited[i]=0;
        }

        visited[0]=1;
        DFSM(0);
        if(vx[cn-1]==-1){return true;}
        else{return false;}

}

void Citynet::DFSM(int i)
{
   // cout<<i;
    for(int m=0;m<vn;m++){
        if(vx[m]!=i){r++;}
    }
    if(r==vn){
        vx[vn]=i;
        vn++;
    }
    r=0;
    visited[i]=1;
    for(int j=0;j<cn;j++)           //依次搜索vi邻接点
        if(p2[i][j]==1 && visited[j]==0)
            DFSM(j);
}

///////////////////////////////////////////////////////////////////////////////////
void Citynet::deletecity(){

        int **temp;//辅助网络，用于删除线路或城市

        temp=new int* [cn];//辅助网络初始化
        for(int i=0;i<cn;i++){
                temp[i]=new int[cn];
        }
        for(int row=0;row<cn;row++){
                for(int col=0;col<cn;col++){
                        temp[row][col]=0;
                }
        }

        for(int n=0;n<cn;n++){//遍历各个城市

                for(int row=0;row<cn;row++){
                        for(int col=0;col<cn;col++){
                                if(row==n||col==n){
                                        temp[row][col]=temp[col][row]=0;
                                }else temp[row][col]=p[row][col];
                        }
                }

                        int nn=0;
                        //广度优先遍历
                        int *visited;//访问标记位
                        visited=new int[cn];
                        for(int i=0;i<cn;i++)visited[i]=0;//访问数组初始化

                        queue<int> q;
                        if(n!=0){
                        q.push(0);
                        visited[0]=1;//入队 访问到
                        }else{
                        q.push(1);
                        visited[1]=1;
                        }
                        while(!q.empty()){
                                int row=q.front();//出队一个元素
                                q.pop();

                                if(row!=n)
                                nn++;

                                for(int col=0;col<cn;col++){
                                        if(temp[row][col]==1&&visited[col]==0){
                                        q.push(col);
                                        visited[col]=1;//入队 访问到
                                        }
                                }
                        }
                        //cout<<"(nn:"<<nn<<")";
                        if(nn<cn-1){
                               // cout<<n+1<<" ";
                                p[n][n]=1;
                        }
        }
//        cout<<endl;
//        cout<<"-------------------------"<<endl;
//        cout<<"          第三题         "<<endl;
//        cout<<"-------------------------"<<endl;
//        cout<<"      重点城市矩阵P1"<<endl;

        for(int i=0;i<cn;i++){
                delete[] temp[i];
        }
        delete[] temp;


        temp=new int* [cn];//辅助网络初始化
        for(int i=0;i<cn;i++){
                temp[i]=new int[cn];
        }
        for(int row=0;row<cn;row++){
                for(int col=0;col<cn;col++){
                        temp[row][col]=0;
                }
        }

        for(int n=0;n<cn;n++){//遍历各个城市
                for(int row=0;row<cn;row++){
                        for(int col=0;col<cn;col++){
                                if(row==n||col==n){
                                        temp[row][col]=temp[col][row]=0;
                                }else temp[row][col]=p2[row][col];
                        }
                }

                        int nn=0;
                        //广度优先遍历
                        int *visited;//访问标记位
                        visited=new int[cn];
                        for(int i=0;i<cn;i++)visited[i]=0;//访问数组初始化

                        queue<int> q;
                        if(n!=0){
                        q.push(0);
                        visited[0]=1;//入队 访问到
                        }else{
                        q.push(1);
                        visited[1]=1;
                        }
                        while(!q.empty()){
                                int row=q.front();//出队一个元素
                                q.pop();

                                if(row!=n)
                                nn++;

                                for(int col=0;col<cn;col++){
                                        if(temp[row][col]==1&&visited[col]==0){
                                        q.push(col);
                                        visited[col]=1;//入队 访问到
                                        }
                                }
                        }
                        //cout<<"(nn:"<<nn<<")";
                        if(nn<cn-1){
                               // cout<<n+1<<" ";
                                p2[n][n]=1;
                        }
        }
//        cout<<endl;
//        cout<<"      重点城市矩阵P2"<<endl;
//        //注释部分为行标列标，仅n<10
//        cout<<"  ";
        for(int col=0;col<cn;col++){
                //cout<<col+1<<" ";
        }
        //cout<<endl;
        for(int row=0;row<cn;row++){
                //cout<<row+1<<" ";//行标
                for(int col=0;col<cn;col++){
                        //cout<<p2[row][col]<<" ";
                        //datafile<<p[row][col]<<" ";
                }
                //cout<<endl;
                //datafile<<"\n";
        }
        //cout<<"-------------------------"<<endl;

        ofstream p1file("p1fh.txt",ios::trunc);
        for(int i=0;i<cn;i++){
                for(int j=0;j<cn;j++){
                        p1file<<p[i][j]<<" ";
                }
                p1file<<endl;
        }
        p1file.close();

        ofstream p2file("p2fh.txt",ios::trunc);
        for(int i=0;i<cn;i++){
                for(int j=0;j<cn;j++){
                        p2file<<p2[i][j]<<" ";
                }
                p2file<<endl;
        }
        p2file.close();

        //冗余矩阵删除
        for(int i=0;i<cn;i++){
                delete[] temp[i];
        }
        delete[] temp;
        //cout<<"临时矩阵TEMP析构成功"<<endl;

}
bool Citynet::IsFull(int** pp){
        int nn=0;
        //广度优先遍历
        int *visited;//访问标记位
        visited=new int[cn];
        for(int i=0;i<cn;i++)visited[i]=0;//访问数组初始化

        queue<int> q;

        q.push(0);
        visited[0]=1;//入队 访问到

        while(!q.empty()){
                int row=q.front();//出队一个元素
                q.pop();
                nn++;
                for(int col=0;col<cn;col++){
                        if(pp[row][col]==1&&visited[col]==0){
                        q.push(col);
                        visited[col]=1;//入队 访问到
                        }
                }
        }
        if(nn==cn)return true;
        else return false;
}
