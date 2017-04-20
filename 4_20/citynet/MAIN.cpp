
#include<iostream>
#include"CITYNET.h"
#include<cstdlib>
#include <fstream>
//屏蔽控制台
using namespace std;
extern bool Creat(int a,int b);

//#pragma comment( linker, "/subsystem:\"windows\" /entry:\"mainCRTStartup\"" ) // 设置入口地址

//////////////////////////////////////////////////////////////////////////////////////////////////
void System(){
//        while(true){
//                system("cls");
//                int n,m;
//                cout<<"请输入城市数目:(m>=2)                   (PS:m<2退出系统)"<<endl;
//                cin>>n;
//                if(n<2)break;
//                do{
//                cout<<"请输入线路数目："<<"1<=m<="<<n*(n-1)/2<<endl;
//                cin>>m;
//                }while(!Creat(n,m));
//                //创建对象
//                Citynet* ll=new Citynet(n,m);
//                //输出(屏幕和文件)
//                ll->print();//第一题
//                //ll->scanfnet();
//                ll->create(m,n);
//                ll->secure();//第二题
//                ll->deletecity();//第三题
//                system("pause");
//                ll->~Citynet();
//                system("pause");
//        }
        int m,n;
        fstream citycin,linecity;
        citycin.open("citycin.txt",ios::in);
        linecity.open("linecin.txt",ios::in);
        citycin>>n;
        linecity>>m;
        Citynet* ll=new Citynet(n,m);
        ll->print();//第一题
        //ll->scanfnet();
        ll->create(m,n);
        ll->secure();//第二题
        ll->deletecity();//第三题
        ll->~Citynet();
        citycin.close();
        linecity.close();
        //system("pause");
}
//////////////////////////////////////////////////////////////////////////////////////////////////
int main(){
        System();
        return 0;
}
