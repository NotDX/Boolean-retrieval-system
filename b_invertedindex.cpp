#include<iostream>
#include<fstream>
using namespace std;

const int stop_limit=250;//ͣ�ô���

struct intchain//int������
{
    int x;
    intchain *next;
};

class dchain//���ÿһ����������������
{
    string x;
    int df;
    intchain *head;
    dchain *next;
public:
    dchain( )
    {
        head=new intchain;
        head->next=NULL;
    }
    dchain(string xx,int fre)
    {
        head=new intchain;
        df=1;
        x=xx;
        intchain *p=new intchain;
        p->x=fre;
        p->next=NULL;
        head->next=p;
    }
    ~dchain( )
    {
        delete head;
    }

    void addone(int f);//��������������

    dchain* getnext( ){return next;}
    string getx( ){return x;}

    void setnext(dchain* nn){next=nn;}//������������
    bool olimit( )//ͣ�ô��ж�
    {
        if(df>stop_limit)
        {
            return 1;
        }
        return 0;
    }

    int getdf( ){return df;}
    void printchain(ofstream& os);//�����������������
};

void dchain::addone(int f)
{
    df++;
    intchain *cur=head;
    for(; cur->next!=NULL; cur=cur->next);
    intchain *p=new intchain;
    p->x=f;
    p->next=NULL;
    cur->next=p;
}

void dchain::printchain(ofstream& os)
{
    int endnum=0;
    intchain* cur=head->next;
    for(;cur->next!=NULL;cur=cur->next)
    {
        endnum++;
        os<<cur->x;
        if(endnum%50==0)
        {
            os<<endl;
        }
        else
        {
            os<<" ";
        }
    }
    os<<cur->x;
}

int main( )
{
    dchain *head=new dchain("\0",0);

    ifstream ifs;
    ifs.open("C:\\Users\\Administrator\\Desktop\\data\\file_list.txt");

    ifstream is;
    string str;
    char cstr[200];

    for(int i=1; !ifs.eof( ); i++)
    //for(int i=1; i<5; i++)
    {
        cout<<"���ڴ����"<<i<<"���ĵ�"<<endl;
        getline(ifs,str);
        //cout<<"���ڴ����"<<i<<"���ĵ�"<<endl;
        //�򿪵�iƪ�ĵ�
        int ccount;
        //cout<<"���ڴ����"<<i<<"���ĵ�"<<endl;
        for(ccount=0; str[ccount]!=0; ccount++)
        {
            cstr[ccount]=str[ccount];
            //cout<<"���ڴ����"<<i<<"���ĵ�"<<endl;
        }
        cstr[ccount]=0;
        //cout<<"���ڴ����"<<i<<"���ĵ�"<<endl;
        is.open(cstr);
        //cout<<"���ڴ����"<<i<<"���ĵ�"<<endl;
        string x;
        int a;
        dchain *cur;
        cout<<"���ڴ����"<<i<<"���ĵ�"<<endl;
        //������������
        for(;!is.eof( );)
        {
            is>>x;
            is>>a;
            is>>a;
            cout<<"���ڴ����"<<i<<"���ĵ�"<<endl;
            int judge=1;
            for(cur=head;cur->getnext( )!=NULL;cur=cur->getnext( ))
            {
                cout<<"���ڴ����"<<i<<"���ĵ�"<<endl;
                if(x==(cur->getnext( ))->getx( ))
                {
                    cout<<"���ڴ����"<<i<<"���ĵ�"<<endl;
                    (cur->getnext( ))->addone(i);
                    judge=0;
                    //cout<<"���ڴ����"<<i<<"���ĵ�"<<endl;
                    break;
                }
                if(x<(cur->getnext( ))->getx( ))
                {
                    dchain *p=new dchain(x,i);
                    p->setnext(cur->getnext( ));
                    cur->setnext(p);
                    judge=0;
                    break;
                }
            }
            if(judge)
            {
                dchain *p=new dchain(x,i);
                p->setnext(NULL);
                cur->setnext(p);
            }
        }

        is.close( );
        //cout<<"���ڴ����"<<i<<"���ĵ�"<<endl;
    }
    ifs.close( );

    //ɾ��ͣ�ô�
    /*for(dchain* cur=head;cur->getnext( )!=NULL;cur=cur->getnext( ))
    {
        if((cur->getnext( ))->olimit( ))
        {
            cur->setnext((cur->getnext( ))->getnext( ));
        }
    }*/

    //���
    ofstream os;
    os.open("C:\\Users\\Administrator\\Desktop\\data\\dddchain.txt");
    dchain* cur;
    for(cur=head->getnext( );cur!=NULL;cur=cur->getnext( ))
    {
        os<<cur->getx( )<<" "<<cur->getdf( )<<" ";
        cur->printchain(os);
        os<<endl;
    }
    os<<cur->getx( )<<" "<<cur->getdf( )<<" ";
    cur->printchain(os);
    os.close( );

    delete head;

    return 0;
}

