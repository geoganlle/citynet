#include<iostream>
#include"CITYNET.h"
#include<stdlib.h>
#include<stdio.h>
#include<queue>
#include <ctime>
#include<fstream>

using namespace std;

/*��һ��*/
extern bool Creat(int a,int b){//��·��Ŀ����
        if(b>(a*(a-1)/2)||b<=0)return false;
        else return true;
}

Citynet::Citynet(int n,int m){
        cn=n;
        ln=m;
        creatline();
        //cout<<"        �����ɹ�"<<endl;
}
Citynet::~Citynet(){
        for(int i=0;i<cn;i++){
                delete[] p[i];
        }
        delete[] p;
        //cout<<"���о���P1�����ɹ�"<<endl;
        for(int i=0;i<cn;i++){
                delete[] p2[i];
        }
        delete[] p2;
        //cout<<"�ؼ���·P2�����ɹ�"<<endl;
        for(int i=0;i<cn;i++){
                delete[] unp[i];
        }
        delete[] unp;
        //cout<<"������·UNP�����ɹ�"<<endl;

}
void Citynet::creatline(){//��������
        p=new int* [cn];//�����ʼ��
        for(int i=0;i<cn;i++){
                p[i]=new int[cn];
        }
        for(int row=0;row<cn;row++){
                for(int col=0;col<cn;col++){
                        p[row][col]=0;
                }
        }
        p2=new int* [cn];//�����ʼ��
        for(int i=0;i<cn;i++){
                p2[i]=new int[cn];
        }
        for(int row=0;row<cn;row++){
                for(int col=0;col<cn;col++){
                        p2[row][col]=0;
                }
        }

        unp=new int* [cn];//���������ʼ��
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

                for(int mn=0;mn<ln;mn++){//��������
                        int a=rand()%cn;
                        int b=rand()%cn;
                        if(a<b){
                                if(p[a][b]==0){
                                        if(CheckLine(a,b)==false)//����ͨ
                                        p[a][b]=p[b][a]=1;
                                        else{//��ͨ
                                        if(unp[a][b]==0)//δ��¼�������
                                        unp[a][b]=unp[b][a]=1;
                                        mn--;//�Ѵ��ڸ������
                                        }
                                }
                        }//��ֱ�������Ҳ���ͨ
                        else mn--;//a bֱ������
                }
        }

//        cout<<"-------------------------"<<endl;
//        cout<<"         ��һ��          "<<endl;
//        cout<<"-------------------------"<<endl;
//        cout<<"        �������"<<endl;
        //�б��б꣬���� n<10
        ofstream unfile("undata.txt",ios::trunc);
        //cout<<"  ";
        for(int col=0;col<cn;col++){
        //        cout<<col+1<<" ";
        }
        cout<<endl;
        for(int row=0;row<cn;row++){
                //cout<<row+1<<" ";//�б�
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
void Citynet::print(){//��ӡ����
        ofstream datafile("p1.txt",ios::trunc);
        //cout<<endl;
        //cout<<"         ����P1"<<endl;
//ע�Ͳ���Ϊ�б��б꣬��n<10
        //cout<<"  ";
        for(int col=0;col<cn;col++){
                //cout<<col+1<<" ";
        }
        //cout<<endl;
        for(int row=0;row<cn;row++){
                //cout<<row+1<<" ";//�б�
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
        cout<<"||||||||��������||||||||"<<endl;
        cout<<"         �ڽӱ�"<<endl;
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
        cout<<"      ������ȱ���"<<endl;
        //������ȱ���
        int *visited;//���ʱ��λ
        visited=new int[cn];
        for(int i=0;i<cn;i++)visited[i]=0;//���������ʼ��

        queue<int> q;
        q.push(0);
        visited[0]=1;//��� ���ʵ�
        while(!q.empty()){
                int row=q.front();//����һ��Ԫ��
                q.pop();
                cout<<row+1<<" ";
                for(int col=row+1;col<cn;col++){
                        if(p[row][col]==1&&visited[col]==0){
                        q.push(col);
                        visited[col]=1;//��� ���ʵ�
                        }
                }
        }
        cout<<endl;
        cout<<"||||||||||||||||||||||||"<<endl;
}

bool Citynet::CheckLine(int a,int b){//��������Ƿ���ͨ
        //������ȱ���
        int *visited;//���ʱ��λ
        visited=new int[cn];
        for(int i=0;i<cn;i++)visited[i]=0;//���������ʼ��

        queue<int> q;
        q.push(a);
        visited[a]=1;//��� ���ʵ�
        while(!q.empty()){
                int row=q.front();//����һ��Ԫ��
                q.pop();
                if(row==b)return true;
                for(int col=0;col<cn;col++){
                        if(p[row][col]==1&&visited[col]==0){
                        q.push(col);
                        visited[col]=1;//��� ���ʵ�
                        }
                }
        }
        return false;
}

///////////////////////////////////////////////////////////////////////////////////

/*�ڶ���*/
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
//        cout<<"         �ڶ���          "<<endl;
//        cout<<"-------------------------"<<endl;
//        cout<<"         ����P2"<<endl;
//        cout<<"  ";
        for(int col=0;col<cn;col++){
                //cout<<col+1<<" ";
        }
        //cout<<endl;
        for(int row=0;row<cn;row++){
                //cout<<row+1<<" ";//�б�
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
        //cout<<"���ɿ���·:"<<endl;
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
double random(double start, double end)      //��������ɺ���
{
    return start+(end-start)*rand()/(RAND_MAX + 1.0);
}


////////////////////////////*������ȱ���*////////////////////////////
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
    for(int j=0;j<cn;j++)           //��������vi�ڽӵ�
        if(p2[i][j]==1 && visited[j]==0)
            DFSM(j);
}

///////////////////////////////////////////////////////////////////////////////////
void Citynet::deletecity(){

        int **temp;//�������磬����ɾ����·�����

        temp=new int* [cn];//���������ʼ��
        for(int i=0;i<cn;i++){
                temp[i]=new int[cn];
        }
        for(int row=0;row<cn;row++){
                for(int col=0;col<cn;col++){
                        temp[row][col]=0;
                }
        }

        for(int n=0;n<cn;n++){//������������

                for(int row=0;row<cn;row++){
                        for(int col=0;col<cn;col++){
                                if(row==n||col==n){
                                        temp[row][col]=temp[col][row]=0;
                                }else temp[row][col]=p[row][col];
                        }
                }

                        int nn=0;
                        //������ȱ���
                        int *visited;//���ʱ��λ
                        visited=new int[cn];
                        for(int i=0;i<cn;i++)visited[i]=0;//���������ʼ��

                        queue<int> q;
                        if(n!=0){
                        q.push(0);
                        visited[0]=1;//��� ���ʵ�
                        }else{
                        q.push(1);
                        visited[1]=1;
                        }
                        while(!q.empty()){
                                int row=q.front();//����һ��Ԫ��
                                q.pop();

                                if(row!=n)
                                nn++;

                                for(int col=0;col<cn;col++){
                                        if(temp[row][col]==1&&visited[col]==0){
                                        q.push(col);
                                        visited[col]=1;//��� ���ʵ�
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
//        cout<<"          ������         "<<endl;
//        cout<<"-------------------------"<<endl;
//        cout<<"      �ص���о���P1"<<endl;

        for(int i=0;i<cn;i++){
                delete[] temp[i];
        }
        delete[] temp;


        temp=new int* [cn];//���������ʼ��
        for(int i=0;i<cn;i++){
                temp[i]=new int[cn];
        }
        for(int row=0;row<cn;row++){
                for(int col=0;col<cn;col++){
                        temp[row][col]=0;
                }
        }

        for(int n=0;n<cn;n++){//������������
                for(int row=0;row<cn;row++){
                        for(int col=0;col<cn;col++){
                                if(row==n||col==n){
                                        temp[row][col]=temp[col][row]=0;
                                }else temp[row][col]=p2[row][col];
                        }
                }

                        int nn=0;
                        //������ȱ���
                        int *visited;//���ʱ��λ
                        visited=new int[cn];
                        for(int i=0;i<cn;i++)visited[i]=0;//���������ʼ��

                        queue<int> q;
                        if(n!=0){
                        q.push(0);
                        visited[0]=1;//��� ���ʵ�
                        }else{
                        q.push(1);
                        visited[1]=1;
                        }
                        while(!q.empty()){
                                int row=q.front();//����һ��Ԫ��
                                q.pop();

                                if(row!=n)
                                nn++;

                                for(int col=0;col<cn;col++){
                                        if(temp[row][col]==1&&visited[col]==0){
                                        q.push(col);
                                        visited[col]=1;//��� ���ʵ�
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
//        cout<<"      �ص���о���P2"<<endl;
//        //ע�Ͳ���Ϊ�б��б꣬��n<10
//        cout<<"  ";
        for(int col=0;col<cn;col++){
                //cout<<col+1<<" ";
        }
        //cout<<endl;
        for(int row=0;row<cn;row++){
                //cout<<row+1<<" ";//�б�
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

        //�������ɾ��
        for(int i=0;i<cn;i++){
                delete[] temp[i];
        }
        delete[] temp;
        //cout<<"��ʱ����TEMP�����ɹ�"<<endl;

}
bool Citynet::IsFull(int** pp){
        int nn=0;
        //������ȱ���
        int *visited;//���ʱ��λ
        visited=new int[cn];
        for(int i=0;i<cn;i++)visited[i]=0;//���������ʼ��

        queue<int> q;

        q.push(0);
        visited[0]=1;//��� ���ʵ�

        while(!q.empty()){
                int row=q.front();//����һ��Ԫ��
                q.pop();
                nn++;
                for(int col=0;col<cn;col++){
                        if(pp[row][col]==1&&visited[col]==0){
                        q.push(col);
                        visited[col]=1;//��� ���ʵ�
                        }
                }
        }
        if(nn==cn)return true;
        else return false;
}
