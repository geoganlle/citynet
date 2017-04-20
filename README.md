# citynet
using c++ and matlab (view) to build M lines  among N cities .

please open the file "Citynet4_7.mlapp" with matlab(2016a+)
you can use the fallow command

open("Citynet4_7.mlapp");

the C++ code was wroten by codeblocks, you can use CB open the ".cbp" or other way to build a project with (CITYNET.h,Function.cpp,MAIN.cpp)

thank you .
welcom communication with my e-mail:

geoganlle@163.com

geoganllegoo@gmail.com

Problem description (by Chinese):

构建连通n个城市的通讯网络。

(1) 输入：城市个数n（城市编号为1到n），城市间通讯线路条数m，随机生成m个不同的城市对（a，b），表示城市间的通讯线路。
依次对这m条通讯线路判断其对于构建连通的通讯网络是否为冗余的，即加入通讯线路（p，q）时，如果城市p与城市q已经连通，则这条通讯线路就是冗余的，将其剔除，否则将其加入通讯网。
输出：图形展示连通的通讯网络的构建结果及冗余线路信息，并用文件将这些信息存储起来。

(2) 为提高通讯网络的可靠性，需要保证如果任何一段通讯线路出现故障，不影响整个通讯网络的连通性。针对（1）中输入，判断该网络是否为可靠网络，并将网络图形展示并文件保存。

(3) 建立城市间的通讯网络，每个城市都有通讯交换机，直接或间接与其它城市连接。交换机有可能会发生故障，需要配备备用交换机。但备用交换机数量有限，不能全部配备，只能给部分重要城市配置。于是规定：如果某个城市由于交换机损坏，不仅本城市通讯中断，还造成其它城市间通讯中断，则为其配备备用交换机。分别针对前面(1)和(2)两种情形建立的通讯网络，标记出需配备备用交换机的城市。
