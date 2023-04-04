#include<iostream>
#include<windows.h>
#include<string>
#include<time.h>
#include<stdlib.h>
//rand()是产生随机int型数,rand(A-B)+B,表示A-B之间的随机整数 包含在头文件#include<time.h> ，#include<stdlib.h>中，
//Sleep()函数的应用，让程序暂停一定时间后再运行，它包含在头文件#include<windows.h>中。 
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
  Time arrivaltime;//到达时间 
  int number;//编号 
  int business;	//办理业务 
};
struct window
{
	int withdrawals;//取款 
 	int deposit;//存款 
 	int reportloss;//挂失 
 	int borrowed;//还贷
	int anum[1000];//保存客户 
 };
class bankbusiness
{
 public:
 	bankbusiness();
 	void enqueue();//入队
	int getqueue();
	void personnel(ticket t2[],int n,int s);//手动生成业务函数，选择业务产生到达时间，打票信息 
	int ticket_produce(ticket t[],int n);//打票信息，到达时间，小票编号，业务种类 
	int personnel_diatribution(int n,int flag); //业务办理函数，等待队列元素分配到窗口（时间计算和窗口闲忙） 
	int business_statistic(window win[],int m);//统计函数，当天业务种类，数量 
	void diaplay_business(window w[],int m,int n,int coordinate);//按照窗口分别显示各个窗口办理的业务数量 
	void make_waittime(int n);//计算逗留时间 
	int menu();
    window win[4];
	ticket t[queuesize];
	ticket t2[queuesize];
 private:
 	string name;//业务名称 
 	int businesstime;//办理业务所需时间 
 	int alltime;//办理所有业务的总时间 
 	int waittime;//等待时间 
 	double averagetime;//平均等待时间
	long *a,*b,*v;
	int data[queuesize];
	ticket data2[queuesize];
	int front,rear;
};

bankbusiness::bankbusiness()
{
	front=rear=queuesize-1;
 } 
void  bankbusiness::enqueue()//手动业务生成编号
{
	int n,m;
	srand(time(0));//初始化随机数种子，time函数是为了减少重复而使用的。 
	while(front!=rear)
	{
		n=(rand()%(500-1)+1);
		rear=(rear+1)%queuesize;
		data2[rear].number==n;
		m=(rand()%(5-1)+1);
		data2[rear].business=m;//业务产生 
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
				name="取款";
				businesstime=1;
				break;
		case 2:
				name="存款";
				businesstime=2;
				break;
		case 3:
				name="挂失";
				businesstime=3;
				break;
		case 4:
				name="还贷";
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
		cout<<"*******银行业务系统*******"<<endl;
		cout<<"1.自动生成业务信息"<<endl;
		cout<<"2.显示客户逗留时间"<<endl;
		cout<<"3.显示各窗口业务统计时间"<<endl;
		cout<<"4.显示窗口1业务办理信息"<<endl; 
		cout<<"5.显示窗口2业务办理信息"<<endl; 
		cout<<"6.显示窗口3业务办理信息"<<endl; 
		cout<<"7.显示窗口4业务办理信息"<<endl; 
		cout<<"8.手动生成业务"<<endl;
		cout<<"0.退出系统"<<endl;
		cout<<"请输入你的选择："<<endl;
		while(cin>>m,!cin.eof())
		{
			if(!cin.good())
					{
						cin.clear();
						cin.ignore();
						cout<<"\t\t输入错误 ！请重新输入！"<<endl;
						Sleep(1000);
						return m;
					}
			else if(m<0||m>8)
			{
			cout<<"\t\t输入错误 ！请重新输入！"<<endl;
			Sleep(1000);//暂停1秒 
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
void bankbusiness::personnel(ticket t2[],int n,int s)//手动生成业务函数，选择业务产生到达时间，打票信息 
{
	int i=0,m=0;
	if(s)//如果s不为0继续 
	{
		srand(time(0));
		t2[i].arrivaltime.hour=(rand()%(16-8)+8);
		t2[i].arrivaltime.minute=rand()%60;
		t2[i].arrivaltime.second=rand()%60;
		n=(rand()%(200-1)+1);//n表示编号 
		t2[i].number=n;
		m=(rand()%(5-1))+1;
		t2[i].business=m;//业务生成 
		switch(m)
		{
			case 1:
				name="取款";
				businesstime=1;
				break;
			case 2:
				name="存款";
				businesstime=2;
				break;
			case 3:
				name="挂失";
				businesstime=3;
				break;
			case 4:
				name="还贷";
				businesstime=4;
				break;
		}
		system("cls");
		cout<<"****************************"<<endl;
		cout<<"*********中国银行***********"<<endl;
		cout<<"编号："<<t2[i].number<<endl;
		cout<<"业务："<<name<<endl;
		cout<<"到达时间：2019.1.11." <<"--"<<t2[i].arrivaltime.hour<<":"<<t2[i].arrivaltime.minute<<":"<<t2[i].arrivaltime.second<<endl;
		cout<<"前面还有："<<t2[i].number-1<<"人"<<endl; 
		cout<<"****************************"<<endl;
	}
}
int  bankbusiness::ticket_produce(ticket t[],int n)//打票信息，到达时间，小票编号，业务种类
{
	int temp,sign,i,j=0;
	a=new long[n];
	b=new long[n];
	v=new long[n];
	for(i=0;i<n;i++) //随机产生的时间无序，等待队列需按照有序等待，然后对时间进行排序并进入队列
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
		t[i].number=i;//编号产生 
		rear=(rear+1)%queuesize;//产生编号入队 
		data[rear]=t[i].number;
		sign=(rand()%(5-1)+1);
		t[i].business=sign; //业务产生
		switch(t[i].business) 
		{
			case 1:
				name="取款";
				businesstime=1;
				break;
			case 2:
				name="存款";
				businesstime=2;
				break;
			case 3:
				name="挂失";
				businesstime=3;
				break;
			case 4:
				name="还贷";
				businesstime=4;
				break;
		}
		b[i]=t[i].business*60; 
	}
	return n;
 } 
int  bankbusiness::personnel_diatribution(int n,int flag)//业务办理函数，等待队列元素分配到窗口（时间计算和窗口闲忙）
{
	int i,k=-1,j=0,m=0,g=0;
	int transh,transm,transs,transb;//小时，分钟，秒，业务 
	long first=0,end=0,next=0,nend=0;//开始时间，结束时间，下一个开始时间，下一个结束时间 
	long c[4]={-4,-3,-2,-1},temp;//c[4]4个窗口办理业务结束时间，c[4]进行初始化，找出数组中的最小元素，用队头元素修改数组c[4]中的最小值。  
	ticket_produce(t,n);//调用时间生产函数
	for(i=0;i<4;i++)
	{
		win[i].withdrawals=0;
		win[i].deposit=0;
		win[i].reportloss=0;
		win[i].borrowed=0;
	 } 
	c[0]=a[0]+b[0];//第一个窗口结束时间初值为队列中第一个客户办理业务 
	waittime=b[0];//第一个用户逗留时间
	transh=a[0]/3600;
	transm=(a[0]%3600)/60;
	transs=(a[0]%3600)%60;
	transb=b[0]/60;
	switch(transb)//窗口各种业务累计 
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
	d=new int[4]; //动态申请一维数组存放被修改结束时间窗口的序号,判断4个窗口的结束时间是否大于下一个客户办理业务的开始时间
	// 如果小于则数组的d[j]中保存该窗口的序号否则地址为-1，判断窗口序号保存数组d[j]中是否有被保存的窗口序号 
	flag=i;
	first=a[i];//开始时间 
	end=a[i]+b[i];//结束时间 
	nend=a[i+1]+b[i+1];//下一个结束时间 
	next=a[i+1]; //下一个开始时间 
	for(j=0;j<4;j++)//判断四个窗口中的结束时间是否大于下一个客户办理业务的开始时间 
	{
		if(c[j]<=next)
		{
			d[j]=j;//如果小于即保存该窗口序号 
		}
		else
		{
			d[j]=-1;//地址存为-1 
		 } 
	 } 
	 for(j=0;j<4;j++)//判断窗口序号保存中是否有被保存的窗口序号 
	 {
	 	if(d[j]>=0)
	 	{
	 		k=j;//若有则结束，记住该窗口序号 
	 		break;
		 }
		 else
		 {
		 	k=-1;
		 }
	 }
	 if(k>=0)
	 {
	 	c[k]=nend;//如果有窗口序号被更改，则继续修改当前结束时间为下一个用户的业务办理结束时间 
	 	transh=next/3600;
	    transm=(next%3600)/60;
	    transs=(next%3600)%60;
	    transb=b[i+1]/60;
	    waittime +=b[i+1];
	    v[i+1]=k;
	    switch(transb)//窗口各种业务累计 
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
	 else//如果当前窗口序号全未被修改，即当前所有窗口处于忙碌状态 
	 {
	 	temp=c[0];
	 	k=0;
	 	for(j=1;j<4;j++)//找出在办理业务中结束最早的窗口 
	 	{
	 		if(c[j]<temp)
	 		{
	 			temp=c[j];
	 			k=j;
			 }
		 }
		 if(temp<3600*17)
		 {
		 	c[k]=c[k]+b[i+1];//修改该窗口结束时间，下一个在等待客户到该窗口办理业务 
		 	transh=next/3600;
	        transm=(next%3600)/60;
	        transs=(next%3600)%60;
	        transb=b[i+1]/60;
	        waittime +=temp-next+b[i+1];
	        v[i+1]=k;
	    switch(transb)//各种业务累计 
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
  delete[]d;//每次循环结束时撤销窗口序号保存数组 
 }
 cout<<endl;
 return flag;
}
int bankbusiness::business_statistic(window win[],int m)//统计函数，当天业务种类，数量
{
	int i;
	int n=0;
	int allnum=0;
	for(int i=0;i<4;i++)
	{
		allnum=win[i].reportloss+win[i].borrowed+win[i].deposit+win[i].withdrawals;
		cout<<"           窗口"<<i+1;
		cout<<endl;
		cout<<"取款人数"<<"\t存款人数"<<"\t挂失人数"<<"\t还贷人数"<<"\t办理业务总数"<<endl;
	    cout<< win[i].withdrawals<<"\t\t"<<win[i].deposit<<"\t\t"<< win[i].reportloss<<"\t\t"<<win[i].borrowed<<"\t\t"<<allnum;
	    cout<<endl;
    }
    cout<<endl;
    return allnum;
} 
void bankbusiness::diaplay_business(window w[],int m,int n,int coordinate)//按照窗口分别显示各个窗口办理的业务数量
{
	int j;
	int flag=1;
	cout<<"\t\t\t\t窗口"<<coordinate+1<<"办理：";
	cout<<endl;
	for(j=0;j<n;j++)
	{
		if(v[j]==coordinate)
		{
			cout<<j+1<<"号客户"<<endl;
			flag=0;
		}
		
	 } 
	 if(flag==1)
		{
			cout<<"\t\t该窗口当天没有办理业务！"<<endl; 
		}
}
void bankbusiness::make_waittime(int n)//计算逗留时间 
{
//第一种情况，当天随机产生的客户都办理完了自己的业务。计算方法为 (每个客户开始办理业务的时间-到达银行的时间+办理业务所用时间)。
//第二种情况，当天随机产生的客户太多在下班时还有客户没有办理业务，且在银行停止营业时离开银行。 
//(已经办理完业务的每个客户开始办理业务时间—到达银行的时间+办理业务的时间)+( 未办理业务的每个客户的离开时间—到达银行时间 )。   
	int flag=0;
	long waittime2=0;
	double aver=0;
    flag=personnel_diatribution(n,flag);
    cout<<"总人数："<<n<<endl;
	cout<<"办理业务人数："<<flag+1<<endl;
	cout<<"未办理完业务人数："<<n-flag-1<<endl; 
	if((n-flag-1)!=0)
	cout<<"\t\t未办理完业务的编号："<<flag+2<<"->"<<n<<endl;
	aver=(waittime/(flag+1))/60.0;
	cout<<"已办理业务客户平均逗留时间："<<aver<<"分钟"<<endl; 
	for(int i=flag+2;i<n;i++)
	{
		waittime2 +=3600*17-a[i];
	 } 
	 averagetime=((waittime+waittime2)/n)/60.0;
	 cout<<"当日所有客户平均逗留时间："<<averagetime<<"分钟"<<endl;
}
int main()
{
	int i,n,m,flag=0;
	bankbusiness C;
	while(1)
	{
		cout<<"******************************"<<endl;
		cout<<"*******中国银行业务系统*******"<<endl;
		cout<<"营业时间：8点到16点"<<endl;
		cout<<"1.自动生成业务信息"<<endl;
		cout<<"2.显示客户逗留时间"<<endl;
		cout<<"3.显示各窗口业务统计时间"<<endl;
		cout<<"4.显示窗口1业务办理信息"<<endl; 
		cout<<"5.显示窗口2业务办理信息"<<endl; 
		cout<<"6.显示窗口3业务办理信息"<<endl; 
		cout<<"7.显示窗口4业务办理信息"<<endl; 
		cout<<"8.手动生成业务"<<endl;
		cout<<"0.退出系统"<<endl;
		cout<<"******************************"<<endl;
		cout<<"请输入你的选择："<<endl;
		while(cin>>m,!cin.eof())//流控制语句，判断变量输入是否为整型 //返回流结束位 
		{
			if(!cin.good())//如果不是整型则重新输入 
				{
					cin.clear();
					cin.ignore();
					cout<<"\t\t输入错误 ！请重新输入:"<<endl;
					Sleep(5000); 
					//return m;
				}
			else if(m<0||m>8)
			{
			cout<<"\t\t输入错误 ！请重新输入:"<<endl;
		;
			//Sleep(5000);//暂停1秒 
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
				C.ticket_produce(C.t,n);//打票信息，到达时间，小票编号，业务种类
				C.enqueue();
				C.getqueue();
				C.personnel_diatribution(n,0);//业务办理函数，等待队列元素分配到窗口（时间计算和窗口闲忙）
				flag=1;
				cout<<"业务信息生成成功！"<<endl;
				system("pause");
				break;
			case 2:
				system("cls");
				if(flag==0)
				{
					cout<<"\t\t无可查询信息"<<endl; 
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
					cout<<"\t\t无可查询信息"<<endl; 
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
					cout<<"\t\t无可查询信息"<<endl; 
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
					cout<<"\t\t无可查询信息"<<endl; 
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
					cout<<"\t\t无可查询信息"<<endl; 
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
					cout<<"\t\t无可查询信息"<<endl; 
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
					cout<<"*****是否打号？（1/0）*****"<<endl;
					cout<<"***************************"<<endl;
					cout<<"（是请输入1，不是请输入0）"<<endl;
					int tag=0; 
					while(cin>>m,!cin.eof()) 
					{
					if(!cin.good())
					{
						cin.clear();
						cin.ignore();
						cout<<"\t\t输入错误 ！请重新输入！"<<endl;
						Sleep(5000);
						system("cls");
						cout<<"***************************"<<endl;
					    cout<<"*****是否打号？（1/0）*****"<<endl;
					    cout<<"***************************"<<endl;
					    cout<<"（是请输入1，不是请输入0）"<<endl;
			    	}
					else if(m!=0&&m!=1)
					{
						cout<<"\t\t输入错误 ！请重新输入！"<<endl;
						Sleep(5000);
						system("cls");
						cout<<"***************************"<<endl;
				     	cout<<"*****是否打号？（1/0）*****"<<endl;
				    	cout<<"***************************"<<endl;
				    	cout<<"（是请输入1，不是请输入0）"<<endl;
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
