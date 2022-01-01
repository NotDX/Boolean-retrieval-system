/************程序介绍************/
/****
     本程序为简易布尔查询
     使用语料为老师提供的532篇文档
     本查询系统的主体是一个while(1)循环,用户输入按钮进行功能选择，
具体功能看菜单或者函数功能说明

注意事项：
     1.本系统暂时没有考虑怎么处理不在语料库中的字符串，因此当输入
不在语料库中的字符串是会直接退出
     2.本系统暂不支持任意查询公式输入，请按照本系统规则进行
****/

/************头文件部分************/
#include<iostream>
#include<map>
#include<fstream>
#include<ctime>
#include<algorithm>
using namespace std;

/************结构体定义部分************/
struct intchain//int型链表
{
    int x;
    intchain *next;
};

struct paras//用于合取范式排序
{
    int df;
    int myi;
};

/************全局变量定义部分************/
map<string,intchain*> dchain;
//map，用来根据字符串快速找到
string fname[550];//存放数据原始绝对地址
ofstream result;//存放结果
intchain *cur;//用来生成最终链表
intchain *res;//最终链表头指针

/************函数声明部分************/
void menu( );//菜单
void work( );//查询任务

void two_and( );//双词的AND查询
void two_or( );//双词的OR查询
void two_not( );//A AND NOT B查询
void n_and( );//多词的AND查询
void n_or( );//多词的OR查询
void n_mix( );//多词的AND、OR、NOT查询
void para( );//多词的合取范式查询

bool dfcmp(intchain* a,intchain* b);//df正向排序用
bool i_dfcmp(intchain* a,intchain* b);//df逆向排序用
bool paracmp(paras a,paras b);//paras结构体按df升序

/************主函数************/
int main( )
{
    /****读入倒排索引表****/
    ifstream file;
    file.open("C:\\Users\\Administrator\\Desktop\\data\\filelist.txt");
    for(int i=1;!file.eof( );i++)
    {
        getline(file,fname[i]);
    }
    file.close( );

    file.open("C:\\Users\\Administrator\\Desktop\\data\\index.txt");
    //file.open("D:\\my word\\课程\\大二\\大二小\\主修课\\智能信息检索\\资料\\【批量下载】IR实验\\IR实验\\倒排表\\result1.txt");

    string str;
    int num;
    int mem;

    //读入所有倒排表
    for(int i=0;!file.eof( );i++)
    {
        file>>str;
        //file>>num;
        file>>num;

        intchain *head=new intchain;
        head->x=num;
        cur=head;
        for(int j=0;j<num;j++)
        {
            intchain *p=new intchain;
            file>>mem;
            p->x=mem;
            cur->next=p;
            cur=cur->next;
        }
        cur->next=NULL;

        dchain[str]=head;
    }

    //系统运行
    work( );

    file.close( );

    return 0;
}

/************菜单函数部分************/
//菜单函数
void menu( )
{
    cout<<"***********欢迎使用hsxz简易搜索系统*************"<<endl;
    cout<<"************************************************"<<endl;
    cout<<"*请根据需要选择想要的服务（输入相应的数字）*****"<<endl;
    cout<<"[1]******双词的AND查询**************************"<<endl;
    cout<<"[2]******双词的OR查询***************************"<<endl;
    cout<<"[3]******A AND NOT B查询************************"<<endl;
    cout<<"[4]******多词的AND查询**************************"<<endl;
    cout<<"[5]******多词的OR查询***************************"<<endl;
    cout<<"[6]******多词的AND、OR、NOT查询*****************"<<endl;
    cout<<"[7]******多词的合取范式查询*********************"<<endl;
    cout<<"[其他数字]退出系统******************************"<<endl;
    cout<<"************************************************"<<endl;
}

/************系统运行************/
void work( )
{
    int n;
    while(1)//输入相应的功能，进行不同的查询
    {
        menu( );
        cin>>n;
        if(n==1)//具体可以看menu函数
        {
            two_and( );
        }
        else if(n==2)
        {
            two_or( );
        }
        else if(n==3)
        {
            two_not( );
        }
        else if(n==4)
        {
            n_and( );
        }
        else if(n==5)
        {
            n_or( );
        }
        else if(n==6)
        {
            n_mix( );
        }
        else if(n==7)
        {
            para( );
        }
        else
        {
            cout<<"退出系统成功"<<endl<<endl;
            break;
        }
    }
}

/************查询函数集************/

/****
1.双词的AND查询

查询形式：
     A AND B

函数作用：
     固定查询两个输入词，找到包含两个词的所有文档

基本思路：
     两个有序链表求交集
****/
void two_and( )
{
    res=new intchain;
    cur=res;
    res->next=NULL;

    result.open("D:\\my word\\课程\\大二\\大二小\\主修课\\智能信息检索\\资料\\【批量下载】IR实验\\IR实验\\结果\\result.txt");
    cout<<"您正在使用的是双词AND查询"<<endl<<endl;

    intchain* last[2];

    cout<<"请输入两个词"<<endl;
    string sstr[2];
    cin>>sstr[0];
    cin>>sstr[1];

    clock_t startTime,endTime;
    startTime=clock();//计时开始

    //获取两个AND项对应的链表
    last[0]=dchain[sstr[0]]->next;
    last[1]=dchain[sstr[1]]->next;

    //进行有序链表求交集操作
    for(;last[0]!=NULL and last[1]!=NULL;)
    {
        if(last[0]->x==last[1]->x)
        {
            intchain *p=new intchain;
            p->x=last[0]->x;
            cur->next=p;
            cur=cur->next;

            last[0]=last[0]->next;
            last[1]=last[1]->next;
        }
        else if(last[0]->x>last[1]->x)
        {
            last[1]=last[1]->next;
        }
        else
        {
            last[0]=last[0]->next;
        }
    }
    cur->next=NULL;

    endTime=clock();//计时结束
    cout<<"本次查询时间："<<1000000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"us"<<endl;
    //输出结果
    int res_num=0;
    for(cur=res->next;cur!=NULL;cur=cur->next)
    {
        result<<fname[cur->x]<<endl;
        res_num++;
    }
    cout<<"一共找到"<<res_num<<"篇文档"<<endl;

    //endTime=clock();//计时结束
    //cout<<"本次查询时间："<<1000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"ms"<<endl;

    result.close( );

    delete res;

    return ;
}

/****
2.双词的OR查询

查询形式：
     A OR B

函数作用：
     固定查询两个输入词，找到包含两个词中任意一个词的所有文档

基本思路：
     两个有序链表求并集
****/
void two_or( )
{
    res=new intchain;
    cur=res;
    res->next=NULL;

    result.open("D:\\my word\\课程\\大二\\大二小\\主修课\\智能信息检索\\资料\\【批量下载】IR实验\\IR实验\\结果\\result.txt");
    cout<<"您正在使用的是双词OR查询"<<endl<<endl;

    intchain* last[2];

    cout<<"请输入两个词"<<endl;
    string sstr[2];
    cin>>sstr[0];
    cin>>sstr[1];

    clock_t startTime,endTime;
    startTime=clock();//计时开始

    //获取两个OR项对应的链表
    last[0]=dchain[sstr[0]]->next;
    last[1]=dchain[sstr[1]]->next;

    //进行有序链表求并集操作
    for(;last[0]!=NULL and last[1]!=NULL;)
    {
        if(last[0]->x==last[1]->x)
        {
            intchain *p=new intchain;
            p->x=last[0]->x;
            cur->next=p;
            cur=cur->next;

            last[0]=last[0]->next;
            last[1]=last[1]->next;
        }
        else if(last[0]->x>last[1]->x)
        {
            intchain *p=new intchain;
            p->x=last[1]->x;
            cur->next=p;
            cur=cur->next;

            last[1]=last[1]->next;
        }
        else
        {
            intchain *p=new intchain;
            p->x=last[0]->x;
            cur->next=p;
            cur=cur->next;

            last[0]=last[0]->next;
        }
    }

    if(last[0]==NULL and last[1]==NULL){}
    else if(last[0]==NULL)
    {
        for(;last[1]!=NULL;)
        {
            intchain *p=new intchain;
            p->x=last[1]->x;
            cur->next=p;
            cur=cur->next;

            last[1]=last[1]->next;
        }
    }
    else
    {
        for(;last[0]!=NULL;)
        {
            intchain *p=new intchain;
            p->x=last[0]->x;
            cur->next=p;
            cur=cur->next;

            last[0]=last[0]->next;
        }
    }

    cur->next=NULL;

    endTime=clock();//计时结束
    cout<<"本次查询时间："<<1000000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"us"<<endl;
    //输出结果
    int res_num=0;
    for(cur=res->next;cur!=NULL;cur=cur->next)
    {
        result<<fname[cur->x]<<endl;
        res_num++;
    }
    cout<<"一共找到"<<res_num<<"篇文档"<<endl;

    //endTime=clock();//计时结束
    //cout<<"本次查询时间："<<1000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"ms"<<endl;

    result.close( );

    delete res;

    return ;
}

/****
3.A AND NOT B查询

查询形式：
     A AND (NOT B)

函数作用：
     固定查询两个输入词，找到包含A并且不包含B的所有文档

基本思路：
     求两个有序链表的差
****/
void two_not( )
{
    res=new intchain;
    cur=res;
    res->next=NULL;

    result.open("D:\\my word\\课程\\大二\\大二小\\主修课\\智能信息检索\\资料\\【批量下载】IR实验\\IR实验\\结果\\result.txt");
    cout<<"您正在使用的是A AND NOT B查询"<<endl<<endl;

    intchain* last[2];

    cout<<"请输入A"<<endl;
    string sstr[2];
    cin>>sstr[0];

    cout<<"请输入B"<<endl;
    cin>>sstr[1];

    clock_t startTime,endTime;
    startTime=clock();//计时开始

    //获取两项链表
    last[0]=dchain[sstr[0]]->next;
    last[1]=dchain[sstr[1]]->next;

    //进行有序链表的差操作
    for(;last[0]!=NULL and last[1]!=NULL;)
    {
        if(last[0]->x==last[1]->x)
        {
            last[0]=last[0]->next;
            last[1]=last[1]->next;
        }
        else if(last[0]->x>last[1]->x)
        {
            last[1]=last[1]->next;
        }
        else
        {
            intchain *p=new intchain;
            p->x=last[0]->x;
            cur->next=p;
            cur=cur->next;

            last[0]=last[0]->next;
        }
    }

    if(last[0]==NULL and last[1]==NULL){}
    else if(last[1]==NULL)
    {
        for(;last[0]!=NULL;)
        {
            intchain *p=new intchain;
            p->x=last[0]->x;
            cur->next=p;
            cur=cur->next;

            last[0]=last[0]->next;
        }
    }

    cur->next=NULL;

    endTime=clock();//计时结束
    cout<<"本次查询时间："<<1000000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"us"<<endl;
    //输出结果
    int res_num=0;
    for(cur=res->next;cur!=NULL;cur=cur->next)
    {
        result<<fname[cur->x]<<endl;
        res_num++;
    }
    cout<<"一共找到"<<res_num<<"篇文档"<<endl;

    //endTime=clock();//计时结束
    //cout<<"本次查询时间："<<1000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"ms"<<endl;

    result.close( );

    delete res;

    return ;
}

/****
4.多词的AND查询

查询形式：
     A1 AND A2 AND A3...AN

函数作用：
     查询N个关键词，找到包含所有关键词的文档

基本思路：
     求多个有序链表的交集

优化思路：
     因为求有序链表交集的过程中，结果链表的元素个数严格单调递减的
为了能减少遍历次数，可以先将这些链表按元素数（即df值）升序排序，然
后再依次求交集
****/
void n_and( )
{
    res=new intchain;
    cur=res;
    res->next=NULL;

    result.open("D:\\my word\\课程\\大二\\大二小\\主修课\\智能信息检索\\资料\\【批量下载】IR实验\\IR实验\\结果\\result.txt");
    cout<<"您正在使用的是多词的AND查询"<<endl<<endl;
    cout<<"请输入AND的词数"<<endl;
    int and_num;
    cin>>and_num;

    if(and_num<1)//保证至少有一个与项，否则无法查询
    {
        cout<<"无法查询"<<endl;
        result.close( );
        return ;
    }

    intchain **ress=new intchain*[and_num];//ress数组依次存储生成的链表
    for(int i=0;i<and_num;i++)
    {
        ress[i]=new intchain;
        ress[i]->next=NULL;
    }

    intchain** last=new intchain*[and_num];
    string *sstr=new string[and_num];

    cout<<"请依次输入这"<<and_num<<"个项"<<endl;
    for(int i=0;i<and_num;i++)
    {
        cin>>sstr[i];
    }

    clock_t startTime,endTime;
    startTime=clock();//计时开始

    if(and_num==1)//一个关键词，不需要操作，直接找到链表输出
    {
        delete res;
        res=dchain[sstr[0]];
    }
    else
    {
        cur=ress[0];
        for(int i=0;i<and_num;i++)//获取各项的链表
        {
            last[i]=dchain[sstr[i]];
        }
        sort(last,last+and_num,dfcmp);//按df升序排列

        //将第一串链表作为初始串并复制
        for(last[0]=last[0]->next;last[0]!=NULL;last[0]=last[0]->next)
        {
            intchain *p=new intchain;
            p->x=last[0]->x;
            cur->next=p;
            cur=cur->next;
        }
        cur->next=NULL;

        int cnum=and_num;

        //依次求交集
        for(int i=1;i<and_num;i++)
        {
            cur=ress[i];
            intchain* llast=ress[i-1];
            if(ress[i-1]->next==NULL)//res已经没有元素了
            {
                cnum=i;
                break;
            }
            last[i]=last[i]->next;
            for(llast=llast->next;llast!=NULL and last[i]!=NULL;)
            {
                if(llast->x==last[i]->x)
                {
                    intchain *p=new intchain;
                    p->x=last[i]->x;
                    cur->next=p;
                    cur=cur->next;

                    llast=llast->next;
                    last[i]=last[i]->next;
                }
                else if(llast->x>last[i]->x)
                {
                    last[i]=last[i]->next;
                }
                else
                {
                    llast=llast->next;
                }
            }
            cur->next=NULL;
        }
        delete res;
        res=ress[cnum-1];
    }

    endTime=clock();//计时结束
    cout<<"本次查询时间："<<1000000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"us"<<endl;
    //输出结果
    int res_num=0;
    for(cur=res->next;cur!=NULL;cur=cur->next)
    {
        result<<fname[cur->x]<<endl;
        res_num++;
    }
    cout<<"一共找到"<<res_num<<"篇文档"<<endl;

    //endTime=clock();//计时结束
    //cout<<"本次查询时间："<<1000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"ms"<<endl;

    result.close( );

    delete res;
    delete ress;
    delete last;
    delete sstr;

    return ;
}

/****
5.多词的OR查询

查询形式：
     A1 OR A2 OR A3...AN

函数作用：
     查询N个关键词，找到包含所有关键词的文档

基本思路：
     求多个有序链表的并集
****/
void n_or( )
{
    res=new intchain;
    cur=res;
    res->next=NULL;

    result.open("D:\\my word\\课程\\大二\\大二小\\主修课\\智能信息检索\\资料\\【批量下载】IR实验\\IR实验\\结果\\result.txt");
    cout<<"您正在使用的是多词的OR查询"<<endl<<endl;
    cout<<"请输入OR的词数"<<endl;

    int or_num;
    cin>>or_num;

    if(or_num<1)//OR项小于1，无法查询
    {
        cout<<"无法查询"<<endl;
        result.close( );
        return ;
    }

    intchain **ress=new intchain*[or_num];//存放每次生成的并集链表
    for(int i=0;i<or_num;i++)
    {
        ress[i]=new intchain;
        ress[i]->next=NULL;
    }

    intchain** last=new intchain*[or_num];
    string *sstr=new string[or_num];

    cout<<"请依次输入这"<<or_num<<"个数字"<<endl;
    for(int i=0;i<or_num;i++)
    {
        cin>>sstr[i];
    }

    clock_t startTime,endTime;
    startTime=clock();//计时开始

    if(or_num==1)//OR项为1，找到链表直接输出
    {
        delete res;
        res=dchain[sstr[0]];
    }
    else
    {
        cur=ress[0];
        for(int i=0;i<or_num;i++)
        {
            last[i]=dchain[sstr[i]];
        }

        //获得初始串
        for(last[0]=last[0]->next;last[0]!=NULL;last[0]=last[0]->next)
        {
            intchain *p=new intchain;
            p->x=last[0]->x;
            cur->next=p;
            cur=cur->next;
        }
        cur->next=NULL;

        int cnum=or_num;

        //依次求并集
        for(int i=1;i<or_num;i++)
        {
            cur=ress[i];
            intchain* llast=ress[i-1];

            last[i]=last[i]->next;
            for(llast=llast->next;llast!=NULL and last[i]!=NULL;)
            {
                if(llast->x==last[i]->x)
                {
                    intchain *p=new intchain;
                    p->x=last[i]->x;
                    cur->next=p;
                    cur=cur->next;

                    llast=llast->next;
                    last[i]=last[i]->next;
                }
                else if(llast->x>last[i]->x)
                {
                    intchain *p=new intchain;
                    p->x=last[i]->x;
                    cur->next=p;
                    cur=cur->next;

                    last[i]=last[i]->next;
                }
                else
                {
                    intchain *p=new intchain;
                    p->x=llast->x;
                    cur->next=p;
                    cur=cur->next;

                    llast=llast->next;
                }
            }
            if(llast==NULL and last[i]==NULL){}
            else if(llast==NULL)
            {
                for(;last[i]!=NULL;)
                {
                    intchain *p=new intchain;
                    p->x=last[i]->x;
                    cur->next=p;
                    cur=cur->next;

                    last[i]=last[i]->next;
                }
            }
            else
            {
                for(;llast!=NULL;)
                {
                    intchain *p=new intchain;
                    p->x=llast->x;
                    cur->next=p;
                    cur=cur->next;

                    llast=llast->next;
                }
            }

            cur->next=NULL;
        }

        delete res;
        res=ress[cnum-1];
    }

    endTime=clock();//计时结束
    cout<<"本次查询时间："<<1000000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"us"<<endl;
    //输出结果
    int res_num=0;
    for(cur=res->next;cur!=NULL;cur=cur->next)
    {
        result<<fname[cur->x]<<endl;
        res_num++;
    }
    cout<<"一共找到"<<res_num<<"篇文档"<<endl;

    //endTime=clock();//计时结束
    //cout<<"本次查询时间："<<1000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"ms"<<endl;

    result.close( );

    delete res;
    delete ress;
    delete last;
    delete sstr;

    return ;
}

/****
6.多词的AND、OR、NOT查询

查询形式：
     （A1 AND A2...AN） AND (B1 OR B2...BM) AND NOT (C1 OR C2...CK)

函数作用：
     查询N个AND项，M个OR项和K个NOT项，找到包含所有AND项，至少包含一个OR项，
不包含NOT项的全部结果

基本思路：
     先进行将所有OR项链表去并集，与所有AND项进行交集运算，之后与每个NOT
项依次做差运算

优化思路：
     在做与操作时，按df值进行升序排序，做差操作时，按照df值降序排序（差
操作也是严格单调递减的）
****/
void n_mix( )
{
    res=new intchain;
    cur=res;
    res->next=NULL;

    result.open("D:\\my word\\课程\\大二\\大二小\\主修课\\智能信息检索\\资料\\【批量下载】IR实验\\IR实验\\结果\\result.txt");
    cout<<"您正在使用的是多词的AND、OR、NOT查询"<<endl;
    cout<<"形式为：（A1 AND A2...） AND (B1 OR B2...) AND NOT (C1 OR C2...)"<<endl<<endl;

    int and_num,or_num,not_num;
    string *and_str,*or_str,*not_str;//用来存放查找字符串
    intchain **and_last;//用来存放每一个and项的链表指针
    intchain **or_last;//用来存放每一个or项的链表指针
    intchain **not_last;//用来存放每一个not项的链表指针

    intchain **and_ress;//用来存放每一个and项的新链表指针
    intchain **or_ress;//用来存放每一个or项的新链表指针
    intchain **not_ress;//用来存放每一个not项的新链表指针
    intchain *llast;//用来指向上一串

    //输入and
    cout<<"请输入AND词项的数目:"<<endl;
    cin>>and_num;
    if(and_num>0)
    {
        and_str=new string[and_num];
        and_last=new intchain*[and_num];

        and_ress=new intchain*[and_num];
        for(int i=0; i<and_num; i++)
        {
            and_ress[i]=new intchain;
            and_ress[i]->next=NULL;
        }
        cout<<"请依次输入这"<<and_num<<"个词项："<<endl;
        for(int i=0; i<and_num; i++)
        {
            cin>>and_str[i];
            and_last[i]=dchain[and_str[i]];
        }

        //AND项链表按df升序排序
        sort(and_last,and_last+and_num,dfcmp);
    }

    //输入or
    cout<<"请输入OR词项的数目:"<<endl;
    cin>>or_num;

    if(or_num>0)
    {
        or_str=new string[or_num];
        or_last=new intchain*[or_num];

        or_ress=new intchain*[or_num+1];
        for(int i=0; i<=or_num; i++)
        {
            or_ress[i]=new intchain;
            or_ress[i]->next=NULL;
        }

        cout<<"请依次输入这"<<or_num<<"个词项："<<endl;
        for(int i=0; i<or_num; i++)
        {
            cin>>or_str[i];
            or_last[i]=dchain[or_str[i]];
        }
    }


    //输入not
    cout<<"请输入NOT词项的数目:"<<endl;
    cin>>not_num;
    if(not_num>0)
    {
        not_str=new string[not_num];
        not_last=new intchain*[not_num];

        not_ress=new intchain*[not_num+1];
        for(int i=0; i<not_num+1; i++)
        {
            not_ress[i]=new intchain;
            not_ress[i]->next=NULL;
        }

        cout<<"请依次输入这"<<not_num<<"个词项："<<endl;
        for(int i=0; i<not_num; i++)
        {
            cin>>not_str[i];
            not_last[i]=dchain[not_str[i]];
        }
    }

    clock_t startTime,endTime;
    startTime=clock();//计时开始

    //NOT项按df降序排序
    sort(not_last,not_last+not_num,i_dfcmp);

    //因为有其他查询形式的存在，这里只需要考虑四种情况
    //AND+OR
    //AND+NOT
    //OR+NOT
    //AND+OR+NOT
    if(and_num>0 and or_num>0 and not_num<1)//and+or
    {
        //处理and开始
        cur=and_ress[0];
        for(and_last[0]=and_last[0]->next; and_last[0]!=NULL; and_last[0]=and_last[0]->next)
        {
            intchain *p=new intchain;
            p->x=and_last[0]->x;
            cur->next=p;
            cur=cur->next;
        }
        cur->next=NULL;

        int cnum=and_num;

        for(int i=1; i<and_num; i++)
        {
            cur=and_ress[i];
            llast=and_ress[i-1];
            if(and_ress[i-1]->next==NULL)//res已经没有元素了
            {
                cnum=i;
                break;
            }

            and_last[i]=and_last[i]->next;
            for(llast=llast->next; llast!=NULL and and_last[i]!=NULL;)
            {
                if(llast->x==and_last[i]->x)
                {
                    intchain *p=new intchain;
                    p->x=and_last[i]->x;
                    cur->next=p;
                    cur=cur->next;

                    llast=llast->next;
                    and_last[i]=and_last[i]->next;
                }
                else if(llast->x>and_last[i]->x)
                {
                    and_last[i]=and_last[i]->next;
                }
                else
                {
                    llast=llast->next;
                }
            }
            cur->next=NULL;
        }

        delete res;
        res=and_ress[cnum-1];
        //处理and结束

        if(cnum==and_num)//仍然有元素
        {
            //处理or开始
            cur=or_ress[0];
            for(or_last[0]=or_last[0]->next; or_last[0]!=NULL; or_last[0]=or_last[0]->next)
            {
                intchain *p=new intchain;
                p->x=or_last[0]->x;
                cur->next=p;
                cur=cur->next;
            }
            cur->next=NULL;

            for(int i=1; i<or_num; i++)
            {
                cur=or_ress[i];
                llast=or_ress[i-1];

                or_last[i]=or_last[i]->next;
                for(llast=llast->next; llast!=NULL and or_last[i]!=NULL;)
                {
                    if(llast->x==or_last[i]->x)
                    {
                        intchain *p=new intchain;
                        p->x=or_last[i]->x;
                        cur->next=p;
                        cur=cur->next;

                        llast=llast->next;
                        or_last[i]=or_last[i]->next;
                    }
                    else if(llast->x>or_last[i]->x)
                    {
                        intchain *p=new intchain;
                        p->x=or_last[i]->x;
                        cur->next=p;
                        cur=cur->next;

                        or_last[i]=or_last[i]->next;
                    }
                    else
                    {
                        intchain *p=new intchain;
                        p->x=llast->x;
                        cur->next=p;
                        cur=cur->next;

                        llast=llast->next;
                    }
                }
                cur->next=NULL;
            }
            //处理or串结束

            //合并
            cur=or_ress[or_num];
            llast=and_ress[cnum-1]->next;
            for(or_ress[or_num-1]=or_ress[or_num-1]->next; llast!=NULL and or_ress[or_num-1]!=NULL;)
            {
                if(or_ress[or_num-1]->x==llast->x)
                {
                    intchain *p=new intchain;
                    p->x=llast->x;
                    cur->next=p;
                    cur=cur->next;

                    llast=llast->next;
                    or_ress[or_num-1]=or_ress[or_num-1]->next;
                }
                else if(or_ress[or_num-1]->x>llast->x)
                {
                    llast=llast->next;
                }
                else
                {
                    or_ress[or_num-1]=or_ress[or_num-1]->next;
                }
            }
            cur->next=NULL;

            res=or_ress[or_num];
        }
    }
    else if(and_num>0 and or_num<1 and not_num>0)//and+not
    {
        //处理and开始
        cur=and_ress[0];
        for(and_last[0]=and_last[0]->next; and_last[0]!=NULL; and_last[0]=and_last[0]->next)
        {
            intchain *p=new intchain;
            p->x=and_last[0]->x;
            cur->next=p;
            cur=cur->next;
        }
        cur->next=NULL;

        int cnum=and_num;

        for(int i=1; i<and_num; i++)
        {
            cur=and_ress[i];
            llast=and_ress[i-1];
            if(and_ress[i-1]->next==NULL)//res已经没有元素了
            {
                cnum=i;
                break;
            }

            and_last[i]=and_last[i]->next;
            for(llast=llast->next; llast!=NULL and and_last[i]!=NULL;)
            {
                if(llast->x==and_last[i]->x)
                {
                    intchain *p=new intchain;
                    p->x=and_last[i]->x;
                    cur->next=p;
                    cur=cur->next;

                    llast=llast->next;
                    and_last[i]=and_last[i]->next;
                }
                else if(llast->x>and_last[i]->x)
                {
                    and_last[i]=and_last[i]->next;
                }
                else
                {
                    llast=llast->next;
                }
            }
            cur->next=NULL;
        }

        delete res;
        res=and_ress[cnum-1];
        //处理and结束

        if(res->next!=NULL)//仍然有元素
        {
            //处理not串
            for(int i=0; i<not_num; i++)
            {
                cur=res;
                for(; cur->next!=NULL and not_last[i]->next!=NULL;)
                {
                    if(not_last[i]->next->x==cur->next->x)
                    {
                        llast=cur->next;
                        cur->next=cur->next->next;
                        llast->next=NULL;
                        delete llast;
                    }
                    else if(not_last[i]->next->x>cur->next->x)
                    {
                        cur=cur->next;
                    }
                    else
                    {
                        not_last[i]=not_last[i]->next;
                    }
                }
            }
            //not串处理结束
        }
    }
    else if(and_num<1 and or_num>0 and not_num>0)//or+not
    {
        //处理or开始
        cur=or_ress[0];
        for(or_last[0]=or_last[0]->next; or_last[0]!=NULL; or_last[0]=or_last[0]->next)
        {
            intchain *p=new intchain;
            p->x=or_last[0]->x;
            cur->next=p;
            cur=cur->next;
        }
        cur->next=NULL;

        for(int i=1; i<or_num; i++)
        {
            cur=or_ress[i];
            llast=or_ress[i-1];

            or_last[i]=or_last[i]->next;
            for(llast=llast->next; llast!=NULL and or_last[i]!=NULL;)
            {
                if(llast->x==or_last[i]->x)
                {
                    intchain *p=new intchain;
                    p->x=or_last[i]->x;
                    cur->next=p;
                    cur=cur->next;

                    llast=llast->next;
                    or_last[i]=or_last[i]->next;
                }
                else if(llast->x>or_last[i]->x)
                {
                    intchain *p=new intchain;
                    p->x=or_last[i]->x;
                    cur->next=p;
                    cur=cur->next;

                    or_last[i]=or_last[i]->next;
                }
                else
                {
                    intchain *p=new intchain;
                    p->x=llast->x;
                    cur->next=p;
                    cur=cur->next;

                    llast=llast->next;
                }
            }
            cur->next=NULL;
        }

        delete res;
        res=or_ress[or_num-1];
        //处理or串结束

        //处理not串
        for(int i=0; i<not_num; i++)
        {
            cur=res;
            for(; cur->next!=NULL and not_last[i]->next!=NULL;)
            {
                if(not_last[i]->next->x==cur->next->x)
                {
                    llast=cur->next;
                    cur->next=cur->next->next;
                    llast->next=NULL;
                    delete llast;
                }
                else if(not_last[i]->next->x>cur->next->x)
                {
                    cur=cur->next;
                }
                else
                {
                    not_last[i]=not_last[i]->next;
                }
            }
        }
        //not串处理结束
    }
    else if(and_num>0 and or_num>0 and not_num>0)//and+or+not
    {
        //处理and开始
        cur=and_ress[0];
        for(and_last[0]=and_last[0]->next; and_last[0]!=NULL; and_last[0]=and_last[0]->next)
        {
            intchain *p=new intchain;
            p->x=and_last[0]->x;
            cur->next=p;
            cur=cur->next;
        }
        cur->next=NULL;

        int cnum=and_num;

        for(int i=1; i<and_num; i++)
        {
            cur=and_ress[i];
            llast=and_ress[i-1];
            if(and_ress[i-1]->next==NULL)//res已经没有元素了
            {
                cnum=i;
                break;
            }

            and_last[i]=and_last[i]->next;
            for(llast=llast->next; llast!=NULL and and_last[i]!=NULL;)
            {
                if(llast->x==and_last[i]->x)
                {
                    intchain *p=new intchain;
                    p->x=and_last[i]->x;
                    cur->next=p;
                    cur=cur->next;

                    llast=llast->next;
                    and_last[i]=and_last[i]->next;
                }
                else if(llast->x>and_last[i]->x)
                {
                    and_last[i]=and_last[i]->next;
                }
                else
                {
                    llast=llast->next;
                }
            }
            cur->next=NULL;
        }

        delete res;
        res=and_ress[cnum-1];
        //处理and结束

        if(cnum==and_num)//仍然有元素
        {
            //处理or开始
            cur=or_ress[0];
            for(or_last[0]=or_last[0]->next; or_last[0]!=NULL; or_last[0]=or_last[0]->next)
            {
                intchain *p=new intchain;
                p->x=or_last[0]->x;
                cur->next=p;
                cur=cur->next;
            }
            cur->next=NULL;

            for(int i=1; i<or_num; i++)
            {
                cur=or_ress[i];
                llast=or_ress[i-1];

                or_last[i]=or_last[i]->next;
                for(llast=llast->next; llast!=NULL and or_last[i]!=NULL;)
                {
                    if(llast->x==or_last[i]->x)
                    {
                        intchain *p=new intchain;
                        p->x=or_last[i]->x;
                        cur->next=p;
                        cur=cur->next;

                        llast=llast->next;
                        or_last[i]=or_last[i]->next;
                    }
                    else if(llast->x>or_last[i]->x)
                    {
                        intchain *p=new intchain;
                        p->x=or_last[i]->x;
                        cur->next=p;
                        cur=cur->next;

                        or_last[i]=or_last[i]->next;
                    }
                    else
                    {
                        intchain *p=new intchain;
                        p->x=llast->x;
                        cur->next=p;
                        cur=cur->next;

                        llast=llast->next;
                    }
                }
                cur->next=NULL;
            }
            //处理or串结束

            //合并
            cur=or_ress[or_num];
            llast=and_ress[cnum-1]->next;
            for(or_ress[or_num-1]=or_ress[or_num-1]->next; llast!=NULL and or_ress[or_num-1]!=NULL;)
            {
                if(or_ress[or_num-1]->x==llast->x)
                {
                    intchain *p=new intchain;
                    p->x=llast->x;
                    cur->next=p;
                    cur=cur->next;

                    llast=llast->next;
                    or_ress[or_num-1]=or_ress[or_num-1]->next;
                }
                else if(or_ress[or_num-1]->x>llast->x)
                {
                    llast=llast->next;
                }
                else
                {
                    or_ress[or_num-1]=or_ress[or_num-1]->next;
                }
            }
            cur->next=NULL;

            res=or_ress[or_num];
            //合并结束

            //处理not串
            for(int i=0; i<not_num; i++)
            {
                cur=res;
                for(; cur->next!=NULL and not_last[i]->next!=NULL;)
                {
                    if(not_last[i]->next->x==cur->next->x)
                    {
                        llast=cur->next;
                        cur->next=cur->next->next;
                        llast->next=NULL;
                        delete llast;
                    }
                    else if(not_last[i]->next->x>cur->next->x)
                    {
                        cur=cur->next;
                    }
                    else
                    {
                        not_last[i]=not_last[i]->next;
                    }
                }
            }
            //not串处理结束
        }
    }
    else
    {
        endTime=clock();//计时结束
        result.close( );
        cout<<"无法查询"<<endl;
        delete res;
        if(and_num>0)
        {
            delete and_str;
            delete and_last;
        }
        if(or_num>0)
        {
            delete or_str;
            delete or_last;
        }
        if(not_num>0)
        {
            delete not_str;
            delete not_last;
        }

        return ;
    }

    endTime=clock();//计时结束
    cout<<"本次查询时间："<<1000000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"us"<<endl;
    //输出结果
    int res_num=0;
    for(cur=res->next;cur!=NULL;cur=cur->next)
    {
        result<<fname[cur->x]<<endl;
        res_num++;
    }
    cout<<"一共找到"<<res_num<<"篇文档"<<endl;

    //endTime=clock();//计时结束
    //cout<<"本次查询时间："<<1000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"ms"<<endl;

    result.close( );

    delete res;
    if(and_num>0)
    {
        delete and_str;
        delete and_last;
    }
    if(or_num>0)
    {
        delete or_str;
        delete or_last;
    }
    if(not_num>0)
    {
        delete not_str;
        delete not_last;
    }

    return ;
}

/****
7.多词的合取范式查询

查询形式：
     （A1 OR A2...AN） AND (B1 OR B2...BM) AND (C1 OR C2...CK)...

函数作用：
     理论上，所有查询公式最终都可以化成合取范式（虽然此形式没有考虑NOT
项存在的情况）

基本思路：
     先计算每一个合取项的链表，再进行合取

优化思路：
     在进行求交集前，可以先对每一个求并集结果按元素个数进行排序，但为
了不浪费遍历链表和增加计数器的时间，可以用每个合取项中的析取项df值的和
来预估生成并集的元素数量，并以此作为依据升序排序
****/
void para( )
{
    res=new intchain;
    cur=res;
    res->next=NULL;

    result.open("D:\\my word\\课程\\大二\\大二小\\主修课\\智能信息检索\\资料\\【批量下载】IR实验\\IR实验\\结果\\result.txt");

    cout<<"您正在使用合取范式查询"<<endl;
    cout<<"格式为（A1 OR A2） AND (B1 OR B2 OR B3) AND (C1 OR C2)..."<<endl;

    int and_num;
    int *or_num;
    paras *or_par;
    intchain ***or_last;

    //存放结果用
    intchain **res1;//每个合取项new一次
    intchain **res2;//存放每个合取项最后的结果

    string *str;

    cout<<"请输入合取项的数目:"<<endl;
    cin>>and_num;
    while(and_num<1)//要保证
    {
        cout<<"不合法，请重新输入："<<endl;
        cin>>and_num;
    }

    or_num=new int[and_num];
    or_par=new paras[and_num];
    for(int i=0;i<and_num;i++)//生成排序用结构体数组
    {
        or_par[i].df=0;
        or_par[i].myi=i;
    }

    //获取链表
    or_last=new intchain**[and_num];
    res2=new intchain*[and_num+1];
    for(int i=0;i<and_num+1;i++)
    {
        res2[i]=new intchain;
        res2[i]->next=NULL;
    }

    for(int i=0;i<and_num;i++)
    {
        cout<<"请输入第"<<i+1<<"个合取项中析取项个数"<<endl;
        cin>>or_num[i];
        if(or_num[i]>0)
        {
            or_last[i]=new intchain*[or_num[i]];
        }

        cout<<"请依次输入这"<<or_num[i]<<"项"<<endl;
        str=new string[or_num[i]];

        for(int j=0;j<or_num[i];j++)
        {
            cin>>str[j];
            or_last[i][j]=dchain[str[j]];
            or_par[i].df+=dchain[str[j]]->x;
        }
        delete str;
    }

    clock_t startTime,endTime;
    startTime=clock();//计时开始

    //按df和升序排列
    sort(or_par,or_par+and_num,paracmp);

    for(int i=0;i<and_num;i++)//求每一个合取项链表
    {
        //生成初始串
        res1=new intchain*[or_num[i]];
        for(int j=0;j<or_num[i];j++)
        {
            res1[j]=new intchain;
            res1[j]->next=NULL;
        }

        cur=res1[0];
        for(or_last[i][0]=or_last[i][0]->next;or_last[i][0]!=NULL;or_last[i][0]=or_last[i][0]->next)
        {
            intchain* p=new intchain;
            p->x=or_last[i][0]->x;
            cur->next=p;
            cur=cur->next;
        }
        cur->next=NULL;

        //生成并集
        for(int j=1;j<or_num[i];j++)
        {
            cur=res1[j];
            intchain *llast=res1[j-1]->next;

            for(or_last[i][j]=or_last[i][j]->next;llast!=NULL and or_last[i][j]!=NULL;)
            {
                if(or_last[i][j]->x==llast->x)
                {
                    intchain *p=new intchain;
                    p->x=llast->x;
                    cur->next=p;
                    cur=cur->next;

                    llast=llast->next;
                    or_last[i][j]=or_last[i][j]->next;
                }
                else if(or_last[i][j]->x>llast->x)
                {
                    intchain *p=new intchain;
                    p->x=llast->x;
                    cur->next=p;
                    cur=cur->next;

                    llast=llast->next;
                }
                else
                {
                    intchain *p=new intchain;
                    p->x=or_last[i][j]->x;
                    cur->next=p;
                    cur=cur->next;

                    or_last[i][j]=or_last[i][j]->next;
                }
            }

            if(llast==NULL and or_last[i][j]==NULL)
            {

            }
            else if(llast==NULL)
            {
                for(;or_last[i][j]!=NULL;)
                {
                    intchain *p=new intchain;
                    p->x=or_last[i][j]->x;
                    cur->next=p;
                    cur=cur->next;

                    or_last[i][j]=or_last[i][j]->next;
                }
            }
            else
            {
                for(;llast!=NULL;)
                {
                    intchain *p=new intchain;
                    p->x=llast->x;
                    cur->next=p;
                    cur=cur->next;

                    llast=llast->next;
                }
            }
            cur->next=NULL;
        }

        //转移
        cur=res2[i];
        intchain *llast=res1[or_num[i]-1]->next;
        for(;llast!=NULL;llast=llast->next)
        {
            intchain *p=new intchain;
            p->x=llast->x;
            //cout<<p->x<<" ";
            cur->next=p;
            cur=cur->next;
        }
        cur->next=NULL;
        delete res1;
    }

    //合并
    res1=new intchain*[and_num];
    for(int i=0;i<and_num;i++)
    {
        res1[i]=new intchain;
        res1[i]->next=NULL;
    }

    int cnum=and_num;

    //生成初始串
    cur=res1[0];
    intchain *llast=res2[or_par[0].myi]->next;//预估的最小df
    for(;llast!=NULL;llast=llast->next)
    {
        intchain *p=new intchain;
        p->x=llast->x;
        cur->next=p;
        cur=cur->next;
    }
    cur->next=NULL;

    for(int i=1;i<and_num;i++)
    {
        if(res1[i-1]->next==NULL)
        {
            cnum=i;
            break;
        }
        cur=res1[i];
        llast=res2[or_par[i].myi]->next;
        for(res1[i-1]=res1[i-1]->next;llast!=NULL and res1[i-1]!=NULL;)
        {
            if(res1[i-1]->x==llast->x)
            {
                intchain *p=new intchain;
                p->x=llast->x;
                cur->next=p;
                cur=cur->next;

                llast=llast->next;
                res1[i-1]=res1[i-1]->next;
            }
            else if(res1[i-1]->x>llast->x)
            {
                llast=llast->next;
            }
            else
            {
                res1[i-1]=res1[i-1]->next;
            }
        }
        cur->next=NULL;
    }

    res=res1[cnum-1];

    endTime=clock();//计时结束
    cout<<"本次查询时间："<<1000000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"us"<<endl;
    //输出结果
    int res_num=0;
    for(cur=res->next;cur!=NULL;cur=cur->next)
    {
        result<<fname[cur->x]<<endl;
        res_num++;
    }
    cout<<"一共找到"<<res_num<<"篇文档"<<endl;

    //endTime=clock();//计时结束
    //cout<<"本次查询时间："<<1000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"ms"<<endl;

    result.close( );

    delete res;
    delete res1;
    delete res2;
    delete or_num;
    delete or_par;
    delete or_last;

    return ;
}

/************排序用比较函数集************/
bool dfcmp(intchain* a,intchain* b)//df正向排序用
{
    return a->x<b->x;
}

bool i_dfcmp(intchain* a,intchain* b)//df逆向排序用
{
    return a->x>b->x;
}

bool paracmp(paras a,paras b)//paras结构体按df升序
{
    return a.df<b.df;
}

