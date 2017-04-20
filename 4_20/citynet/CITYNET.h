#ifndef CITYNET_H_INCLUDED
#define CITYNET_H_INCLUDED

//邻接矩阵存储
class Citynet{
private:
        //关键内部成员
        int cn;//城市个数
        int ln;//通讯线数量
        int **p;//城市网络的二位数组
        int **p2;//关键线路矩阵
        int **unp;//冗余线路网络
        /////////////////////////////////////////////
        //深度优先遍历
        int *visited;
        ////////////////////////////////////////////
public:
//基本功能
        void creatline();//随机生成通讯线
        void print();//输出网络

        Citynet(int n,int m);//n个城市 m条通讯线路
        ~Citynet();//析构函数 用于删除二位动态数组
//辅助函数
        bool CheckLine(int a,int b);//检验ab是否联通
        void scanfnet();//遍历网络
        bool IsFull(int** );//判断联通图
//主功能函数
        ///////////////////////////////////////////
        void secure();//题目2，判断是否为可靠线路
        void create(int,int);
        bool DFSTraverseM();
        void DFSM(int);
        ///////////////////////////////////////////
        void deletecity();//重点城市
        //其他待完成
};

#endif // CITYNET_H_INCLUDED
