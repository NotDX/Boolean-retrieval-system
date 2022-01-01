#include<iostream>
#include<fstream>
using namespace std;

const int stop_limit=400;

class tdocID
{
    string x;
    int y;
    int df;
    tdocID *next;
public:
    tdocID()
    {
        df=0;
        next=NULL;
    }
    tdocID(string xx,int yy)
    {
        x=xx;
        y=yy;
        df=0;
        next=NULL;
    }

    void setxy(string xx,int yy)//���ýڵ�����
    {
        x=xx;
        y=yy;
    }

    void adddf( )//df+1
    {
        df+=1;
    }

    bool stop_word( )
    {
        if(df>stop_limit)
        {
            return 1;
        }
        return 0;
    }

    void thenext(tdocID *ahead)//����������
    {
        next=ahead;
    }

    tdocID* getnext( )//����������
    {
        return next;
    }

    string getname( )
    {
        return x;
    }

    int gety( )
    {
        return y;
    }

    int getdf( )
    {
        return df;
    }

    void nclear( )//�������
    {
        next=NULL;
    }
};


bool check(string x)//�ж��ַ����Ƿ�Ϊ���ִ�
{
    if(x.length( )>2)//�ų������ַ��͵���
    {
        if(x[0]&0x80 and x[1]&0x80)//��һ�����Ǻ�������
        {
            return 1;
        }
    }
    return 0;
}

int main( )
{
    tdocID *head=new tdocID;
    head->setxy(" ",1);

    tdocID *cur;
    tdocID *llast;

    char ifstr[200];
    char ofstr[200];
    string cstr;

    ifstream ifs;
    ifstream ofs;

    ifstream is;
    ofstream os;

    string x;

    //�����ļ�
    ifs.open("C:\\Users\\Administrator\\Desktop\\data\\filelist.txt");
    ofs.open("C:\\Users\\Administrator\\Desktop\\data\\file_list.txt");

    for(int i=1; !ifs.eof(); i++)
    {
        //cout<<i<<endl;

        //��ȡ�����ļ���������ļ���
        getline(ifs,cstr);
        int ccount;
        for(ccount=0;cstr[ccount]!=0;ccount++)
        {
            ifstr[ccount]=cstr[ccount];
        }
        ifstr[ccount]=0;

        getline(ofs,cstr);
        for(ccount=0;cstr[ccount]!=0;ccount++)
        {
            ofstr[ccount]=cstr[ccount];
        }
        ofstr[ccount]=0;

        //cout<<ifstr<<endl;
        //cout<<ofstr<<endl;

        is.open(ifstr);

        //ÿ�δ����������
        head->nclear( );
        for(; !is.eof();)
        {
            is>>x;

            if(check(x))
            {
                int judge=0;
                for(cur=head; cur!=NULL; cur=cur->getnext( ))
                {
                    if(cur->getname()==x)
                    {
                        cur->adddf( );
                        judge=1;
                        break;
                    }
                    if(cur->getnext()==NULL)
                    {
                        llast=cur;
                    }
                }
                if(!judge)
                {
                    cur=new tdocID(x,i);
                    cur->adddf( );
                    llast->thenext(cur);
                }
            }
        }

        is.close( );

        //������ļ�
        os.open(ofstr);
        for(cur=head->getnext( ); cur->getnext( )!=NULL; cur=cur->getnext( ))
        {
            os<<cur->getname( )<<" "<<cur->getdf( )<<" "<<cur->gety( )<<endl;
        }
        os<<cur->getname( )<<" "<<cur->getdf( )<<" "<<cur->gety( );
        os.close( );
    }

    ifs.close( );
    ofs.close( );

    return 0;
}

