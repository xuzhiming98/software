#include<iostream>
#include<windows.h>
#include<string>
#include<time.h>
#include<stdlib.h>
//rand()�ǲ������int����,rand(A-B)+B,��ʾA-B֮���������� ������ͷ�ļ�#include<time.h> ��#include<stdlib.h>�У�
//Sleep()������Ӧ�ã��ó�����ͣһ��ʱ��������У���������ͷ�ļ�#include<windows.h>�С� 
using namespace std;
const int queuesize=1000;
struct Time
{
  int hour;
  int minute;
  int second;
};
struct ticket
{
  Time arrivaltime;//����ʱ�� 
  int number;//��� 
  int business;	//����ҵ�� 
};
struct window
{
	int withdrawals;//ȡ�� 
 	int deposit;//��� 
 	int reportloss;//��ʧ 
 	int borrowed;//����
	int anum[1000];//����ͻ� 
 };
class bankbusiness
{
 public:
 	bankbusiness();
 	void enqueue();//���
	int getqueue();
	void personnel(ticket t2[],int n,int s);//�ֶ�����ҵ������ѡ��ҵ���������ʱ�䣬��Ʊ��Ϣ 
	int ticket_produce(ticket t[],int n);//��Ʊ��Ϣ������ʱ�䣬СƱ��ţ�ҵ������ 
	int personnel_diatribution(int n,int flag); //ҵ����������ȴ�����Ԫ�ط��䵽���ڣ�ʱ�����ʹ�����æ�� 
	int business_statistic(window win[],int m);//ͳ�ƺ���������ҵ�����࣬���� 
	void diaplay_business(window w[],int m,int n,int coordinate);//���մ��ڷֱ���ʾ�������ڰ����ҵ������ 
	void make_waittime(int n);//���㶺��ʱ�� 
	int menu();
    window win[4];
	ticket t[queuesize];
	ticket t2[queuesize];
 private:
 	string name;//ҵ������ 
 	int businesstime;//����ҵ������ʱ�� 
 	int alltime;//��������ҵ�����ʱ�� 
 	int waittime;//�ȴ�ʱ�� 
 	double averagetime;//ƽ���ȴ�ʱ��
	long *a,*b,*v;
	int data[queuesize];
	ticket data2[queuesize];
	int front,rear;
};

bankbusiness::bankbusiness()
{
	front=rear=queuesize-1;
 } 
void  bankbusiness::enqueue()//�ֶ�ҵ�����ɱ��
{
	int n,m;
	srand(time(0));//��ʼ����������ӣ�time������Ϊ�˼����ظ���ʹ�õġ� 
	while(front!=rear)
	{
		n=(rand()%(500-1)+1);
		rear=(rear+1)%queuesize;
		data2[rear].number==n;
		m=(rand()%(5-1)+1);
		data2[rear].business=m;//ҵ����� 
	 } 
 } 
int bankbusiness::getqueue()
{
  int n=0;
  while(front!=rear)
  {
  	front=(front+1)%queuesize;
  	switch(t[front].business)
  	{
  		case 1:
				name="ȡ��";
				businesstime=1;
				break;
		case 2:
				name="���";
				businesstime=2;
				break;
		case 3:
				name="��ʧ";
				businesstime=3;
				break;
		case 4:
				name="����";
				businesstime=4;
				break;
  			
	  }
	} 
   return data[front];
}
int bankbusiness::menu()
{
	int m;
	while(m<0||m>8)
	{
		system("cls");
		cout<<"**************************"<<endl;
		cout<<"*******����ҵ��ϵͳ*******"<<endl;
		cout<<"1.�Զ�����ҵ����Ϣ"<<endl;
		cout<<"2.��ʾ�ͻ�����ʱ��"<<endl;
		cout<<"3.��ʾ������ҵ��ͳ��ʱ��"<<endl;
		cout<<"4.��ʾ����1ҵ�������Ϣ"<<endl; 
		cout<<"5.��ʾ����2ҵ�������Ϣ"<<endl; 
		cout<<"6.��ʾ����3ҵ�������Ϣ"<<endl; 
		cout<<"7.��ʾ����4ҵ�������Ϣ"<<endl; 
		cout<<"8.�ֶ�����ҵ��"<<endl;
		cout<<"0.�˳�ϵͳ"<<endl;
		cout<<"���������ѡ��"<<endl;
		while(cin>>m,!cin.eof())
		{
			if(!cin.good())
					{
						cin.clear();
						cin.ignore();
						cout<<"\t\t������� �����������룡"<<endl;
						Sleep(1000);
						return m;
					}
			else if(m<0||m>8)
			{
			cout<<"\t\t������� �����������룡"<<endl;
			Sleep(1000);//��ͣ1�� 
			return m;
			}
			else if(cin.good()&&(m>=0&&m<=8))
			{
				break;
			}
		}
	}
    return m;
}
void bankbusiness::personnel(ticket t2[],int n,int s)//�ֶ�����ҵ������ѡ��ҵ���������ʱ�䣬��Ʊ��Ϣ 
{
	int i=0,m=0;
	if(s)//���s��Ϊ0���� 
	{
		srand(time(0));
		t2[i].arrivaltime.hour=(rand()%(16-8)+8);
		t2[i].arrivaltime.minute=rand()%60;
		t2[i].arrivaltime.second=rand()%60;
		n=(rand()%(200-1)+1);//n��ʾ��� 
		t2[i].number=n;
		m=(rand()%(5-1))+1;
		t2[i].business=m;//ҵ������ 
		switch(m)
		{
			case 1:
				name="ȡ��";
				businesstime=1;
				break;
			case 2:
				name="���";
				businesstime=2;
				break;
			case 3:
				name="��ʧ";
				businesstime=3;
				break;
			case 4:
				name="����";
				businesstime=4;
				break;
		}
		system("cls");
		cout<<"****************************"<<endl;
		cout<<"*********�й�����***********"<<endl;
		cout<<"��ţ�"<<t2[i].number<<endl;
		cout<<"ҵ��"<<name<<endl;
		cout<<"����ʱ�䣺2019.1.11." <<"--"<<t2[i].arrivaltime.hour<<":"<<t2[i].arrivaltime.minute<<":"<<t2[i].arrivaltime.second<<endl;
		cout<<"ǰ�滹�У�"<<t2[i].number-1<<"��"<<endl; 
		cout<<"****************************"<<endl;
	}
}
int  bankbusiness::ticket_produce(ticket t[],int n)//��Ʊ��Ϣ������ʱ�䣬СƱ��ţ�ҵ������
{
	int temp,sign,i,j=0;
	a=new long[n];
	b=new long[n];
	v=new long[n];
	for(i=0;i<n;i++) //���������ʱ�����򣬵ȴ������谴������ȴ���Ȼ���ʱ��������򲢽������
	{
		for(j=i+1;j<n;j++)
		{
			if(t[i].arrivaltime.hour>t[j].arrivaltime.hour)
			{
				temp=t[i].arrivaltime.hour;
				t[i].arrivaltime.hour=t[j].arrivaltime.hour;
				t[j].arrivaltime.hour=temp;
				temp=t[i].arrivaltime.minute;
				t[i].arrivaltime.minute=t[j].arrivaltime.minute;
				t[j].arrivaltime.minute=temp;
				temp=t[i].arrivaltime.second;
				t[i].arrivaltime.second=t[j].arrivaltime.second;
				t[j].arrivaltime.second=temp;
			}
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(t[i].arrivaltime.hour=t[j].arrivaltime.hour&&t[i].arrivaltime.minute>t[j].arrivaltime.minute)
			{
				temp=t[i].arrivaltime.minute;
				t[i].arrivaltime.minute=t[j].arrivaltime.minute;
				t[j].arrivaltime.minute=temp;
				temp=t[i].arrivaltime.second;
				t[i].arrivaltime.second=t[j].arrivaltime.second;
				t[j].arrivaltime.second=temp;
			}
			else continue;
		}
	}
	for(i=0;i<n;i++)
	{
		for(j=i+1;j<n;j++)
		{
			if(t[i].arrivaltime.hour==t[j].arrivaltime.hour&&t[i].arrivaltime.minute==t[j].arrivaltime.minute&&t[i].arrivaltime.second>t[j].arrivaltime.second)
			{
				temp=t[i].arrivaltime.second;
				t[i].arrivaltime.second=t[j].arrivaltime.second;
				t[j].arrivaltime.second=temp;
			}
			else continue;
		}
	}
	for(i=0;i<n;i++)
	{
		a[i]=v[i]=t[i].arrivaltime.hour*3600+t[i].arrivaltime.minute*60+t[i].arrivaltime.second;
	}
	srand(time(0));
	for(i=0;i<n;i++)
	{
		int sign;
		t[i].number=i;//��Ų��� 
		rear=(rear+1)%queuesize;//���������� 
		data[rear]=t[i].number;
		sign=(rand()%(5-1)+1);
		t[i].business=sign; //ҵ�����
		switch(t[i].business) 
		{
			case 1:
				name="ȡ��";
				businesstime=1;
				break;
			case 2:
				name="���";
				businesstime=2;
				break;
			case 3:
				name="��ʧ";
				businesstime=3;
				break;
			case 4:
				name="����";
				businesstime=4;
				break;
		}
		b[i]=t[i].business*60; 
	}
	return n;
 } 
int  bankbusiness::personnel_diatribution(int n,int flag)//ҵ����������ȴ�����Ԫ�ط��䵽���ڣ�ʱ�����ʹ�����æ��
{
	int i,k=-1,j=0,m=0,g=0;
	int transh,transm,transs,transb;//Сʱ�����ӣ��룬ҵ�� 
	long first=0,end=0,next=0,nend=0;//��ʼʱ�䣬����ʱ�䣬��һ����ʼʱ�䣬��һ������ʱ�� 
	long c[4]={-4,-3,-2,-1},temp;//c[4]4�����ڰ���ҵ�����ʱ�䣬c[4]���г�ʼ�����ҳ������е���СԪ�أ��ö�ͷԪ���޸�����c[4]�е���Сֵ��  
	ticket_produce(t,n);//����ʱ����������
	for(i=0;i<4;i++)
	{
		win[i].withdrawals=0;
		win[i].deposit=0;
		win[i].reportloss=0;
		win[i].borrowed=0;
	 } 
	c[0]=a[0]+b[0];//��һ�����ڽ���ʱ���ֵΪ�����е�һ���ͻ�����ҵ�� 
	waittime=b[0];//��һ���û�����ʱ��
	transh=a[0]/3600;
	transm=(a[0]%3600)/60;
	transs=(a[0]%3600)%60;
	transb=b[0]/60;
	switch(transb)//���ڸ���ҵ���ۼ� 
	{
		case 1:
		win[0].withdrawals++;
		businesstime=1;
		break; 
		case 2:
		win[0].deposit++;
		businesstime=2;
		break; 
		case 3:
		win[0].reportloss++;
		businesstime=3;
		break; 
		case 4:
		win[0].borrowed++;
		businesstime=4;
		break; 
	} 
	v[0]=0;
	for(i=0;i<n;i++)
	{
	int *d;
	d=new int[4]; //��̬����һά�����ű��޸Ľ���ʱ�䴰�ڵ����,�ж�4�����ڵĽ���ʱ���Ƿ������һ���ͻ�����ҵ��Ŀ�ʼʱ��
	// ���С���������d[j]�б���ô��ڵ���ŷ����ַΪ-1���жϴ�����ű�������d[j]���Ƿ��б�����Ĵ������ 
	flag=i;
	first=a[i];//��ʼʱ�� 
	end=a[i]+b[i];//����ʱ�� 
	nend=a[i+1]+b[i+1];//��һ������ʱ�� 
	next=a[i+1]; //��һ����ʼʱ�� 
	for(j=0;j<4;j++)//�ж��ĸ������еĽ���ʱ���Ƿ������һ���ͻ�����ҵ��Ŀ�ʼʱ�� 
	{
		if(c[j]<=next)
		{
			d[j]=j;//���С�ڼ�����ô������ 
		}
		else
		{
			d[j]=-1;//��ַ��Ϊ-1 
		 } 
	 } 
	 for(j=0;j<4;j++)//�жϴ�����ű������Ƿ��б�����Ĵ������ 
	 {
	 	if(d[j]>=0)
	 	{
	 		k=j;//�������������ס�ô������ 
	 		break;
		 }
		 else
		 {
		 	k=-1;
		 }
	 }
	 if(k>=0)
	 {
	 	c[k]=nend;//����д�����ű����ģ�������޸ĵ�ǰ����ʱ��Ϊ��һ���û���ҵ��������ʱ�� 
	 	transh=next/3600;
	    transm=(next%3600)/60;
	    transs=(next%3600)%60;
	    transb=b[i+1]/60;
	    waittime +=b[i+1];
	    v[i+1]=k;
	    switch(transb)//���ڸ���ҵ���ۼ� 
	{
		case 1:
		win[k].withdrawals++;
		businesstime=1;
		break; 
		case 2:
		win[k].deposit++;
		businesstime=2;
		break; 
		case 3:
		win[k].reportloss++;
		businesstime=3;
		break; 
		case 4:
		win[k].borrowed++;
		businesstime=4;
		break; 
	} 
	 }
	 else//�����ǰ�������ȫδ���޸ģ�����ǰ���д��ڴ���æµ״̬ 
	 {
	 	temp=c[0];
	 	k=0;
	 	for(j=1;j<4;j++)//�ҳ��ڰ���ҵ���н�������Ĵ��� 
	 	{
	 		if(c[j]<temp)
	 		{
	 			temp=c[j];
	 			k=j;
			 }
		 }
		 if(temp<3600*17)
		 {
		 	c[k]=c[k]+b[i+1];//�޸ĸô��ڽ���ʱ�䣬��һ���ڵȴ��ͻ����ô��ڰ���ҵ�� 
		 	transh=next/3600;
	        transm=(next%3600)/60;
	        transs=(next%3600)%60;
	        transb=b[i+1]/60;
	        waittime +=temp-next+b[i+1];
	        v[i+1]=k;
	    switch(transb)//����ҵ���ۼ� 
	   {
	    case 1:
		    win[k].withdrawals++;
		    businesstime=1;
		    break; 
		case 2:
		    win[k].deposit++;
		    businesstime=2;
		    break; 
		case 3:
		    win[k].reportloss++;
		    businesstime=3;
		    break; 
		case 4:
		    win[k].borrowed++;
		    businesstime=4;
		    break; 
		 }
	 }
	 else break;
  }
  delete[]d;//ÿ��ѭ������ʱ����������ű������� 
 }
 cout<<endl;
 return flag;
}
int bankbusiness::business_statistic(window win[],int m)//ͳ�ƺ���������ҵ�����࣬����
{
	int i;
	int n=0;
	int allnum=0;
	for(int i=0;i<4;i++)
	{
		allnum=win[i].reportloss+win[i].borrowed+win[i].deposit+win[i].withdrawals;
		cout<<"           ����"<<i+1;
		cout<<endl;
		cout<<"ȡ������"<<"\t�������"<<"\t��ʧ����"<<"\t��������"<<"\t����ҵ������"<<endl;
	    cout<< win[i].withdrawals<<"\t\t"<<win[i].deposit<<"\t\t"<< win[i].reportloss<<"\t\t"<<win[i].borrowed<<"\t\t"<<allnum;
	    cout<<endl;
    }
    cout<<endl;
    return allnum;
} 
void bankbusiness::diaplay_business(window w[],int m,int n,int coordinate)//���մ��ڷֱ���ʾ�������ڰ����ҵ������
{
	int j;
	int flag=1;
	cout<<"\t\t\t\t����"<<coordinate+1<<"����";
	cout<<endl;
	for(j=0;j<n;j++)
	{
		if(v[j]==coordinate)
		{
			cout<<j+1<<"�ſͻ�"<<endl;
			flag=0;
		}
		
	 } 
	 if(flag==1)
		{
			cout<<"\t\t�ô��ڵ���û�а���ҵ��"<<endl; 
		}
}
void bankbusiness::make_waittime(int n)//���㶺��ʱ�� 
{
//��һ�������������������Ŀͻ������������Լ���ҵ�񡣼��㷽��Ϊ (ÿ���ͻ���ʼ����ҵ���ʱ��-�������е�ʱ��+����ҵ������ʱ��)��
//�ڶ��������������������Ŀͻ�̫�����°�ʱ���пͻ�û�а���ҵ����������ֹͣӪҵʱ�뿪���С� 
//(�Ѿ�������ҵ���ÿ���ͻ���ʼ����ҵ��ʱ�䡪�������е�ʱ��+����ҵ���ʱ��)+( δ����ҵ���ÿ���ͻ����뿪ʱ�䡪��������ʱ�� )��   
	int flag=0;
	long waittime2=0;
	double aver=0;
    flag=personnel_diatribution(n,flag);
    cout<<"��������"<<n<<endl;
	cout<<"����ҵ��������"<<flag+1<<endl;
	cout<<"δ������ҵ��������"<<n-flag-1<<endl; 
	if((n-flag-1)!=0)
	cout<<"\t\tδ������ҵ��ı�ţ�"<<flag+2<<"->"<<n<<endl;
	aver=(waittime/(flag+1))/60.0;
	cout<<"�Ѱ���ҵ��ͻ�ƽ������ʱ�䣺"<<aver<<"����"<<endl; 
	for(int i=flag+2;i<n;i++)
	{
		waittime2 +=3600*17-a[i];
	 } 
	 averagetime=((waittime+waittime2)/n)/60.0;
	 cout<<"�������пͻ�ƽ������ʱ�䣺"<<averagetime<<"����"<<endl;
}
int main()
{
	int i,n,m,flag=0;
	bankbusiness C;
	while(1)
	{
		cout<<"******************************"<<endl;
		cout<<"*******�й�����ҵ��ϵͳ*******"<<endl;
		cout<<"Ӫҵʱ�䣺8�㵽16��"<<endl;
		cout<<"1.�Զ�����ҵ����Ϣ"<<endl;
		cout<<"2.��ʾ�ͻ�����ʱ��"<<endl;
		cout<<"3.��ʾ������ҵ��ͳ��ʱ��"<<endl;
		cout<<"4.��ʾ����1ҵ�������Ϣ"<<endl; 
		cout<<"5.��ʾ����2ҵ�������Ϣ"<<endl; 
		cout<<"6.��ʾ����3ҵ�������Ϣ"<<endl; 
		cout<<"7.��ʾ����4ҵ�������Ϣ"<<endl; 
		cout<<"8.�ֶ�����ҵ��"<<endl;
		cout<<"0.�˳�ϵͳ"<<endl;
		cout<<"******************************"<<endl;
		cout<<"���������ѡ��"<<endl;
		while(cin>>m,!cin.eof())//��������䣬�жϱ��������Ƿ�Ϊ���� //����������λ 
		{
			if(!cin.good())//��������������������� 
				{
					cin.clear();
					cin.ignore();
					cout<<"\t\t������� ������������:"<<endl;
					Sleep(5000); 
					//return m;
				}
			else if(m<0||m>8)
			{
			cout<<"\t\t������� ������������:"<<endl;
		;
			//Sleep(5000);//��ͣ1�� 
		//	return m;
			}
			else if(cin.good()&&(m>=0&&m<=8))
			{
				break;
			}
		}
			switch(m)
		{
			case 1:
				system("cls");
				srand(time(0));
				n=(rand()%(500-1)+1);
				for(i=0;i<n;i++)
				{
					C.t[i].arrivaltime.hour=(rand()%(16-8)+8);
		            C.t[i].arrivaltime.minute=rand()%60;
	              	C.t[i].arrivaltime.second=rand()%60;
				}
				C.ticket_produce(C.t,n);//��Ʊ��Ϣ������ʱ�䣬СƱ��ţ�ҵ������
				C.enqueue();
				C.getqueue();
				C.personnel_diatribution(n,0);//ҵ����������ȴ�����Ԫ�ط��䵽���ڣ�ʱ�����ʹ�����æ��
				flag=1;
				cout<<"ҵ����Ϣ���ɳɹ���"<<endl;
				system("pause");
				break;
			case 2:
				system("cls");
				if(flag==0)
				{
					cout<<"\t\t�޿ɲ�ѯ��Ϣ"<<endl; 
				 } 
				 else
				 {
				 	C.make_waittime(n);
				 }
				 system("pause");
				 break;
			case 3:
				system("cls");
				if(flag==0)
				{
					cout<<"\t\t�޿ɲ�ѯ��Ϣ"<<endl; 
				 } 
				 else
				 {
				 	C.business_statistic(C.win,4);
			 }
				 system("pause");
				 break;
			case 4:
				system("cls");
				if(flag==0)
				{
					cout<<"\t\t�޿ɲ�ѯ��Ϣ"<<endl; 
				 } 
				 else
				 {
				 	C.diaplay_business(C.win,4,n,0);
				 }
				 system("pause");
				 break;
			case 5:
				system("cls");
				if(flag==0)
				{
					cout<<"\t\t�޿ɲ�ѯ��Ϣ"<<endl; 
				 } 
				 else
				 {
				 C.diaplay_business(C.win,4,n,1);
				 }
				 system("pause");
				 break;
			case 6:
				system("cls");
				if(flag==0)
				{
					cout<<"\t\t�޿ɲ�ѯ��Ϣ"<<endl; 
				 } 
				 else
				 {
				 	C.diaplay_business(C.win,4,n,2);
				 }
				 system("pause");
				 break;
		    case 7:
		    	system("cls");
				if(flag==0)
				{
					cout<<"\t\t�޿ɲ�ѯ��Ϣ"<<endl; 
				 } 
				 else
				 {
				 	C.diaplay_business(C.win,4,n,3);
				 }
				 system("pause");
				 break;
			case 8:
				system("cls");
				for(i=0;i<queuesize;i++)
				{
					cout<<"***************************"<<endl;
					cout<<"*****�Ƿ��ţ���1/0��*****"<<endl;
					cout<<"***************************"<<endl;
					cout<<"����������1������������0��"<<endl;
					int tag=0; 
					while(cin>>m,!cin.eof()) 
					{
					if(!cin.good())
					{
						cin.clear();
						cin.ignore();
						cout<<"\t\t������� �����������룡"<<endl;
						Sleep(5000);
						system("cls");
						cout<<"***************************"<<endl;
					    cout<<"*****�Ƿ��ţ���1/0��*****"<<endl;
					    cout<<"***************************"<<endl;
					    cout<<"����������1������������0��"<<endl;
			    	}
					else if(m!=0&&m!=1)
					{
						cout<<"\t\t������� �����������룡"<<endl;
						Sleep(5000);
						system("cls");
						cout<<"***************************"<<endl;
				     	cout<<"*****�Ƿ��ţ���1/0��*****"<<endl;
				    	cout<<"***************************"<<endl;
				    	cout<<"����������1������������0��"<<endl;
					}
					else if(cin.good()&&(m==0||m==1))
					{
							if(m==0)
							{
								tag=1;	
							}
							break;
					}
					}
					  if(tag==1) break;
					  C.personnel(C.t2,0,m);
				}
					system("pause");
					  break;
			case 0:
				exit(0);
         }
     }
	return 0;
} 
