/************�������************/
/****
     ������Ϊ���ײ�����ѯ
     ʹ������Ϊ��ʦ�ṩ��532ƪ�ĵ�
     ����ѯϵͳ��������һ��while(1)ѭ��,�û����밴ť���й���ѡ��
���幦�ܿ��˵����ߺ�������˵��

ע�����
     1.��ϵͳ��ʱû�п�����ô���������Ͽ��е��ַ�������˵�����
�������Ͽ��е��ַ����ǻ�ֱ���˳�
     2.��ϵͳ�ݲ�֧�������ѯ��ʽ���룬�밴�ձ�ϵͳ�������
****/

/************ͷ�ļ�����************/
#include<iostream>
#include<map>
#include<fstream>
#include<ctime>
#include<algorithm>
using namespace std;

/************�ṹ�嶨�岿��************/
struct intchain//int������
{
    int x;
    intchain *next;
};

struct paras//���ں�ȡ��ʽ����
{
    int df;
    int myi;
};

/************ȫ�ֱ������岿��************/
map<string,intchain*> dchain;
//map�����������ַ��������ҵ�
string fname[550];//�������ԭʼ���Ե�ַ
ofstream result;//��Ž��
intchain *cur;//����������������
intchain *res;//��������ͷָ��

/************������������************/
void menu( );//�˵�
void work( );//��ѯ����

void two_and( );//˫�ʵ�AND��ѯ
void two_or( );//˫�ʵ�OR��ѯ
void two_not( );//A AND NOT B��ѯ
void n_and( );//��ʵ�AND��ѯ
void n_or( );//��ʵ�OR��ѯ
void n_mix( );//��ʵ�AND��OR��NOT��ѯ
void para( );//��ʵĺ�ȡ��ʽ��ѯ

bool dfcmp(intchain* a,intchain* b);//df����������
bool i_dfcmp(intchain* a,intchain* b);//df����������
bool paracmp(paras a,paras b);//paras�ṹ�尴df����

/************������************/
int main( )
{
    /****���뵹��������****/
    ifstream file;
    file.open("C:\\Users\\Administrator\\Desktop\\data\\filelist.txt");
    for(int i=1;!file.eof( );i++)
    {
        getline(file,fname[i]);
    }
    file.close( );

    file.open("C:\\Users\\Administrator\\Desktop\\data\\index.txt");
    //file.open("D:\\my word\\�γ�\\���\\���С\\���޿�\\������Ϣ����\\����\\���������ء�IRʵ��\\IRʵ��\\���ű�\\result1.txt");

    string str;
    int num;
    int mem;

    //�������е��ű�
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

    //ϵͳ����
    work( );

    file.close( );

    return 0;
}

/************�˵���������************/
//�˵�����
void menu( )
{
    cout<<"***********��ӭʹ��hsxz��������ϵͳ*************"<<endl;
    cout<<"************************************************"<<endl;
    cout<<"*�������Ҫѡ����Ҫ�ķ���������Ӧ�����֣�*****"<<endl;
    cout<<"[1]******˫�ʵ�AND��ѯ**************************"<<endl;
    cout<<"[2]******˫�ʵ�OR��ѯ***************************"<<endl;
    cout<<"[3]******A AND NOT B��ѯ************************"<<endl;
    cout<<"[4]******��ʵ�AND��ѯ**************************"<<endl;
    cout<<"[5]******��ʵ�OR��ѯ***************************"<<endl;
    cout<<"[6]******��ʵ�AND��OR��NOT��ѯ*****************"<<endl;
    cout<<"[7]******��ʵĺ�ȡ��ʽ��ѯ*********************"<<endl;
    cout<<"[��������]�˳�ϵͳ******************************"<<endl;
    cout<<"************************************************"<<endl;
}

/************ϵͳ����************/
void work( )
{
    int n;
    while(1)//������Ӧ�Ĺ��ܣ����в�ͬ�Ĳ�ѯ
    {
        menu( );
        cin>>n;
        if(n==1)//������Կ�menu����
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
            cout<<"�˳�ϵͳ�ɹ�"<<endl<<endl;
            break;
        }
    }
}

/************��ѯ������************/

/****
1.˫�ʵ�AND��ѯ

��ѯ��ʽ��
     A AND B

�������ã�
     �̶���ѯ��������ʣ��ҵ����������ʵ������ĵ�

����˼·��
     �������������󽻼�
****/
void two_and( )
{
    res=new intchain;
    cur=res;
    res->next=NULL;

    result.open("D:\\my word\\�γ�\\���\\���С\\���޿�\\������Ϣ����\\����\\���������ء�IRʵ��\\IRʵ��\\���\\result.txt");
    cout<<"������ʹ�õ���˫��AND��ѯ"<<endl<<endl;

    intchain* last[2];

    cout<<"������������"<<endl;
    string sstr[2];
    cin>>sstr[0];
    cin>>sstr[1];

    clock_t startTime,endTime;
    startTime=clock();//��ʱ��ʼ

    //��ȡ����AND���Ӧ������
    last[0]=dchain[sstr[0]]->next;
    last[1]=dchain[sstr[1]]->next;

    //�������������󽻼�����
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

    endTime=clock();//��ʱ����
    cout<<"���β�ѯʱ�䣺"<<1000000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"us"<<endl;
    //������
    int res_num=0;
    for(cur=res->next;cur!=NULL;cur=cur->next)
    {
        result<<fname[cur->x]<<endl;
        res_num++;
    }
    cout<<"һ���ҵ�"<<res_num<<"ƪ�ĵ�"<<endl;

    //endTime=clock();//��ʱ����
    //cout<<"���β�ѯʱ�䣺"<<1000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"ms"<<endl;

    result.close( );

    delete res;

    return ;
}

/****
2.˫�ʵ�OR��ѯ

��ѯ��ʽ��
     A OR B

�������ã�
     �̶���ѯ��������ʣ��ҵ�����������������һ���ʵ������ĵ�

����˼·��
     �������������󲢼�
****/
void two_or( )
{
    res=new intchain;
    cur=res;
    res->next=NULL;

    result.open("D:\\my word\\�γ�\\���\\���С\\���޿�\\������Ϣ����\\����\\���������ء�IRʵ��\\IRʵ��\\���\\result.txt");
    cout<<"������ʹ�õ���˫��OR��ѯ"<<endl<<endl;

    intchain* last[2];

    cout<<"������������"<<endl;
    string sstr[2];
    cin>>sstr[0];
    cin>>sstr[1];

    clock_t startTime,endTime;
    startTime=clock();//��ʱ��ʼ

    //��ȡ����OR���Ӧ������
    last[0]=dchain[sstr[0]]->next;
    last[1]=dchain[sstr[1]]->next;

    //�������������󲢼�����
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

    endTime=clock();//��ʱ����
    cout<<"���β�ѯʱ�䣺"<<1000000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"us"<<endl;
    //������
    int res_num=0;
    for(cur=res->next;cur!=NULL;cur=cur->next)
    {
        result<<fname[cur->x]<<endl;
        res_num++;
    }
    cout<<"һ���ҵ�"<<res_num<<"ƪ�ĵ�"<<endl;

    //endTime=clock();//��ʱ����
    //cout<<"���β�ѯʱ�䣺"<<1000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"ms"<<endl;

    result.close( );

    delete res;

    return ;
}

/****
3.A AND NOT B��ѯ

��ѯ��ʽ��
     A AND (NOT B)

�������ã�
     �̶���ѯ��������ʣ��ҵ�����A���Ҳ�����B�������ĵ�

����˼·��
     ��������������Ĳ�
****/
void two_not( )
{
    res=new intchain;
    cur=res;
    res->next=NULL;

    result.open("D:\\my word\\�γ�\\���\\���С\\���޿�\\������Ϣ����\\����\\���������ء�IRʵ��\\IRʵ��\\���\\result.txt");
    cout<<"������ʹ�õ���A AND NOT B��ѯ"<<endl<<endl;

    intchain* last[2];

    cout<<"������A"<<endl;
    string sstr[2];
    cin>>sstr[0];

    cout<<"������B"<<endl;
    cin>>sstr[1];

    clock_t startTime,endTime;
    startTime=clock();//��ʱ��ʼ

    //��ȡ��������
    last[0]=dchain[sstr[0]]->next;
    last[1]=dchain[sstr[1]]->next;

    //������������Ĳ����
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

    endTime=clock();//��ʱ����
    cout<<"���β�ѯʱ�䣺"<<1000000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"us"<<endl;
    //������
    int res_num=0;
    for(cur=res->next;cur!=NULL;cur=cur->next)
    {
        result<<fname[cur->x]<<endl;
        res_num++;
    }
    cout<<"һ���ҵ�"<<res_num<<"ƪ�ĵ�"<<endl;

    //endTime=clock();//��ʱ����
    //cout<<"���β�ѯʱ�䣺"<<1000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"ms"<<endl;

    result.close( );

    delete res;

    return ;
}

/****
4.��ʵ�AND��ѯ

��ѯ��ʽ��
     A1 AND A2 AND A3...AN

�������ã�
     ��ѯN���ؼ��ʣ��ҵ��������йؼ��ʵ��ĵ�

����˼·��
     ������������Ľ���

�Ż�˼·��
     ��Ϊ�������������Ĺ����У���������Ԫ�ظ����ϸ񵥵��ݼ���
Ϊ���ܼ��ٱ��������������Ƚ���Щ����Ԫ��������dfֵ����������Ȼ
���������󽻼�
****/
void n_and( )
{
    res=new intchain;
    cur=res;
    res->next=NULL;

    result.open("D:\\my word\\�γ�\\���\\���С\\���޿�\\������Ϣ����\\����\\���������ء�IRʵ��\\IRʵ��\\���\\result.txt");
    cout<<"������ʹ�õ��Ƕ�ʵ�AND��ѯ"<<endl<<endl;
    cout<<"������AND�Ĵ���"<<endl;
    int and_num;
    cin>>and_num;

    if(and_num<1)//��֤������һ����������޷���ѯ
    {
        cout<<"�޷���ѯ"<<endl;
        result.close( );
        return ;
    }

    intchain **ress=new intchain*[and_num];//ress�������δ洢���ɵ�����
    for(int i=0;i<and_num;i++)
    {
        ress[i]=new intchain;
        ress[i]->next=NULL;
    }

    intchain** last=new intchain*[and_num];
    string *sstr=new string[and_num];

    cout<<"������������"<<and_num<<"����"<<endl;
    for(int i=0;i<and_num;i++)
    {
        cin>>sstr[i];
    }

    clock_t startTime,endTime;
    startTime=clock();//��ʱ��ʼ

    if(and_num==1)//һ���ؼ��ʣ�����Ҫ������ֱ���ҵ��������
    {
        delete res;
        res=dchain[sstr[0]];
    }
    else
    {
        cur=ress[0];
        for(int i=0;i<and_num;i++)//��ȡ���������
        {
            last[i]=dchain[sstr[i]];
        }
        sort(last,last+and_num,dfcmp);//��df��������

        //����һ��������Ϊ��ʼ��������
        for(last[0]=last[0]->next;last[0]!=NULL;last[0]=last[0]->next)
        {
            intchain *p=new intchain;
            p->x=last[0]->x;
            cur->next=p;
            cur=cur->next;
        }
        cur->next=NULL;

        int cnum=and_num;

        //�����󽻼�
        for(int i=1;i<and_num;i++)
        {
            cur=ress[i];
            intchain* llast=ress[i-1];
            if(ress[i-1]->next==NULL)//res�Ѿ�û��Ԫ����
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

    endTime=clock();//��ʱ����
    cout<<"���β�ѯʱ�䣺"<<1000000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"us"<<endl;
    //������
    int res_num=0;
    for(cur=res->next;cur!=NULL;cur=cur->next)
    {
        result<<fname[cur->x]<<endl;
        res_num++;
    }
    cout<<"һ���ҵ�"<<res_num<<"ƪ�ĵ�"<<endl;

    //endTime=clock();//��ʱ����
    //cout<<"���β�ѯʱ�䣺"<<1000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"ms"<<endl;

    result.close( );

    delete res;
    delete ress;
    delete last;
    delete sstr;

    return ;
}

/****
5.��ʵ�OR��ѯ

��ѯ��ʽ��
     A1 OR A2 OR A3...AN

�������ã�
     ��ѯN���ؼ��ʣ��ҵ��������йؼ��ʵ��ĵ�

����˼·��
     ������������Ĳ���
****/
void n_or( )
{
    res=new intchain;
    cur=res;
    res->next=NULL;

    result.open("D:\\my word\\�γ�\\���\\���С\\���޿�\\������Ϣ����\\����\\���������ء�IRʵ��\\IRʵ��\\���\\result.txt");
    cout<<"������ʹ�õ��Ƕ�ʵ�OR��ѯ"<<endl<<endl;
    cout<<"������OR�Ĵ���"<<endl;

    int or_num;
    cin>>or_num;

    if(or_num<1)//OR��С��1���޷���ѯ
    {
        cout<<"�޷���ѯ"<<endl;
        result.close( );
        return ;
    }

    intchain **ress=new intchain*[or_num];//���ÿ�����ɵĲ�������
    for(int i=0;i<or_num;i++)
    {
        ress[i]=new intchain;
        ress[i]->next=NULL;
    }

    intchain** last=new intchain*[or_num];
    string *sstr=new string[or_num];

    cout<<"������������"<<or_num<<"������"<<endl;
    for(int i=0;i<or_num;i++)
    {
        cin>>sstr[i];
    }

    clock_t startTime,endTime;
    startTime=clock();//��ʱ��ʼ

    if(or_num==1)//OR��Ϊ1���ҵ�����ֱ�����
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

        //��ó�ʼ��
        for(last[0]=last[0]->next;last[0]!=NULL;last[0]=last[0]->next)
        {
            intchain *p=new intchain;
            p->x=last[0]->x;
            cur->next=p;
            cur=cur->next;
        }
        cur->next=NULL;

        int cnum=or_num;

        //�����󲢼�
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

    endTime=clock();//��ʱ����
    cout<<"���β�ѯʱ�䣺"<<1000000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"us"<<endl;
    //������
    int res_num=0;
    for(cur=res->next;cur!=NULL;cur=cur->next)
    {
        result<<fname[cur->x]<<endl;
        res_num++;
    }
    cout<<"һ���ҵ�"<<res_num<<"ƪ�ĵ�"<<endl;

    //endTime=clock();//��ʱ����
    //cout<<"���β�ѯʱ�䣺"<<1000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"ms"<<endl;

    result.close( );

    delete res;
    delete ress;
    delete last;
    delete sstr;

    return ;
}

/****
6.��ʵ�AND��OR��NOT��ѯ

��ѯ��ʽ��
     ��A1 AND A2...AN�� AND (B1 OR B2...BM) AND NOT (C1 OR C2...CK)

�������ã�
     ��ѯN��AND�M��OR���K��NOT��ҵ���������AND����ٰ���һ��OR�
������NOT���ȫ�����

����˼·��
     �Ƚ��н�����OR������ȥ������������AND����н������㣬֮����ÿ��NOT
��������������

�Ż�˼·��
     ���������ʱ����dfֵ�������������������ʱ������dfֵ�������򣨲�
����Ҳ���ϸ񵥵��ݼ��ģ�
****/
void n_mix( )
{
    res=new intchain;
    cur=res;
    res->next=NULL;

    result.open("D:\\my word\\�γ�\\���\\���С\\���޿�\\������Ϣ����\\����\\���������ء�IRʵ��\\IRʵ��\\���\\result.txt");
    cout<<"������ʹ�õ��Ƕ�ʵ�AND��OR��NOT��ѯ"<<endl;
    cout<<"��ʽΪ����A1 AND A2...�� AND (B1 OR B2...) AND NOT (C1 OR C2...)"<<endl<<endl;

    int and_num,or_num,not_num;
    string *and_str,*or_str,*not_str;//������Ų����ַ���
    intchain **and_last;//�������ÿһ��and�������ָ��
    intchain **or_last;//�������ÿһ��or�������ָ��
    intchain **not_last;//�������ÿһ��not�������ָ��

    intchain **and_ress;//�������ÿһ��and���������ָ��
    intchain **or_ress;//�������ÿһ��or���������ָ��
    intchain **not_ress;//�������ÿһ��not���������ָ��
    intchain *llast;//����ָ����һ��

    //����and
    cout<<"������AND�������Ŀ:"<<endl;
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
        cout<<"������������"<<and_num<<"�����"<<endl;
        for(int i=0; i<and_num; i++)
        {
            cin>>and_str[i];
            and_last[i]=dchain[and_str[i]];
        }

        //AND������df��������
        sort(and_last,and_last+and_num,dfcmp);
    }

    //����or
    cout<<"������OR�������Ŀ:"<<endl;
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

        cout<<"������������"<<or_num<<"�����"<<endl;
        for(int i=0; i<or_num; i++)
        {
            cin>>or_str[i];
            or_last[i]=dchain[or_str[i]];
        }
    }


    //����not
    cout<<"������NOT�������Ŀ:"<<endl;
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

        cout<<"������������"<<not_num<<"�����"<<endl;
        for(int i=0; i<not_num; i++)
        {
            cin>>not_str[i];
            not_last[i]=dchain[not_str[i]];
        }
    }

    clock_t startTime,endTime;
    startTime=clock();//��ʱ��ʼ

    //NOT�df��������
    sort(not_last,not_last+not_num,i_dfcmp);

    //��Ϊ��������ѯ��ʽ�Ĵ��ڣ�����ֻ��Ҫ�����������
    //AND+OR
    //AND+NOT
    //OR+NOT
    //AND+OR+NOT
    if(and_num>0 and or_num>0 and not_num<1)//and+or
    {
        //����and��ʼ
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
            if(and_ress[i-1]->next==NULL)//res�Ѿ�û��Ԫ����
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
        //����and����

        if(cnum==and_num)//��Ȼ��Ԫ��
        {
            //����or��ʼ
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
            //����or������

            //�ϲ�
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
        //����and��ʼ
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
            if(and_ress[i-1]->next==NULL)//res�Ѿ�û��Ԫ����
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
        //����and����

        if(res->next!=NULL)//��Ȼ��Ԫ��
        {
            //����not��
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
            //not���������
        }
    }
    else if(and_num<1 and or_num>0 and not_num>0)//or+not
    {
        //����or��ʼ
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
        //����or������

        //����not��
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
        //not���������
    }
    else if(and_num>0 and or_num>0 and not_num>0)//and+or+not
    {
        //����and��ʼ
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
            if(and_ress[i-1]->next==NULL)//res�Ѿ�û��Ԫ����
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
        //����and����

        if(cnum==and_num)//��Ȼ��Ԫ��
        {
            //����or��ʼ
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
            //����or������

            //�ϲ�
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
            //�ϲ�����

            //����not��
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
            //not���������
        }
    }
    else
    {
        endTime=clock();//��ʱ����
        result.close( );
        cout<<"�޷���ѯ"<<endl;
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

    endTime=clock();//��ʱ����
    cout<<"���β�ѯʱ�䣺"<<1000000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"us"<<endl;
    //������
    int res_num=0;
    for(cur=res->next;cur!=NULL;cur=cur->next)
    {
        result<<fname[cur->x]<<endl;
        res_num++;
    }
    cout<<"һ���ҵ�"<<res_num<<"ƪ�ĵ�"<<endl;

    //endTime=clock();//��ʱ����
    //cout<<"���β�ѯʱ�䣺"<<1000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"ms"<<endl;

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
7.��ʵĺ�ȡ��ʽ��ѯ

��ѯ��ʽ��
     ��A1 OR A2...AN�� AND (B1 OR B2...BM) AND (C1 OR C2...CK)...

�������ã�
     �����ϣ����в�ѯ��ʽ���ն����Ի��ɺ�ȡ��ʽ����Ȼ����ʽû�п���NOT
����ڵ������

����˼·��
     �ȼ���ÿһ����ȡ��������ٽ��к�ȡ

�Ż�˼·��
     �ڽ����󽻼�ǰ�������ȶ�ÿһ���󲢼������Ԫ�ظ����������򣬵�Ϊ
�˲��˷ѱ�����������Ӽ�������ʱ�䣬������ÿ����ȡ���е���ȡ��dfֵ�ĺ�
��Ԥ�����ɲ�����Ԫ�����������Դ���Ϊ������������
****/
void para( )
{
    res=new intchain;
    cur=res;
    res->next=NULL;

    result.open("D:\\my word\\�γ�\\���\\���С\\���޿�\\������Ϣ����\\����\\���������ء�IRʵ��\\IRʵ��\\���\\result.txt");

    cout<<"������ʹ�ú�ȡ��ʽ��ѯ"<<endl;
    cout<<"��ʽΪ��A1 OR A2�� AND (B1 OR B2 OR B3) AND (C1 OR C2)..."<<endl;

    int and_num;
    int *or_num;
    paras *or_par;
    intchain ***or_last;

    //��Ž����
    intchain **res1;//ÿ����ȡ��newһ��
    intchain **res2;//���ÿ����ȡ�����Ľ��

    string *str;

    cout<<"�������ȡ�����Ŀ:"<<endl;
    cin>>and_num;
    while(and_num<1)//Ҫ��֤
    {
        cout<<"���Ϸ������������룺"<<endl;
        cin>>and_num;
    }

    or_num=new int[and_num];
    or_par=new paras[and_num];
    for(int i=0;i<and_num;i++)//���������ýṹ������
    {
        or_par[i].df=0;
        or_par[i].myi=i;
    }

    //��ȡ����
    or_last=new intchain**[and_num];
    res2=new intchain*[and_num+1];
    for(int i=0;i<and_num+1;i++)
    {
        res2[i]=new intchain;
        res2[i]->next=NULL;
    }

    for(int i=0;i<and_num;i++)
    {
        cout<<"�������"<<i+1<<"����ȡ������ȡ�����"<<endl;
        cin>>or_num[i];
        if(or_num[i]>0)
        {
            or_last[i]=new intchain*[or_num[i]];
        }

        cout<<"������������"<<or_num[i]<<"��"<<endl;
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
    startTime=clock();//��ʱ��ʼ

    //��df����������
    sort(or_par,or_par+and_num,paracmp);

    for(int i=0;i<and_num;i++)//��ÿһ����ȡ������
    {
        //���ɳ�ʼ��
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

        //���ɲ���
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

        //ת��
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

    //�ϲ�
    res1=new intchain*[and_num];
    for(int i=0;i<and_num;i++)
    {
        res1[i]=new intchain;
        res1[i]->next=NULL;
    }

    int cnum=and_num;

    //���ɳ�ʼ��
    cur=res1[0];
    intchain *llast=res2[or_par[0].myi]->next;//Ԥ������Сdf
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

    endTime=clock();//��ʱ����
    cout<<"���β�ѯʱ�䣺"<<1000000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"us"<<endl;
    //������
    int res_num=0;
    for(cur=res->next;cur!=NULL;cur=cur->next)
    {
        result<<fname[cur->x]<<endl;
        res_num++;
    }
    cout<<"һ���ҵ�"<<res_num<<"ƪ�ĵ�"<<endl;

    //endTime=clock();//��ʱ����
    //cout<<"���β�ѯʱ�䣺"<<1000*(double)(endTime-startTime)/CLOCKS_PER_SEC<<"ms"<<endl;

    result.close( );

    delete res;
    delete res1;
    delete res2;
    delete or_num;
    delete or_par;
    delete or_last;

    return ;
}

/************�����ñȽϺ�����************/
bool dfcmp(intchain* a,intchain* b)//df����������
{
    return a->x<b->x;
}

bool i_dfcmp(intchain* a,intchain* b)//df����������
{
    return a->x>b->x;
}

bool paracmp(paras a,paras b)//paras�ṹ�尴df����
{
    return a.df<b.df;
}

