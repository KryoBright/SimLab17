#include <iostream>
#include <cmath>
#include <ctime>
#include <chrono>

using namespace std;

double rand_exp(double in)
{
	double r=rand()*1.0/RAND_MAX;
	return -log(r)/in;
}

double getTime()
{
	unsigned __int64 now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    return now;
}

int main()
{
	cout.flush();
	double *ints=new double[3];
	double *event_times=new double[3];
	int *event_number=new int[4];
	double event_last[2];
	
	int combined_probs[2];
	int sum_probs[2];
	combined_probs[0]=1;
	combined_probs[1]=1;
	sum_probs[0]=1;
	sum_probs[1]=1;
	event_last[0]=getTime()/1000;
	event_last[1]=getTime()/1000;
	
	cout<<"Enter intensivity of first process:"<<endl;
	cin>>ints[0];
	cout<<"Enter intensivity of second process:"<<endl;
	cin>>ints[1];
	ints[2]=ints[0]+ints[1];
		
	event_times[0]=rand_exp(ints[0])+getTime()/1000;
	event_number[0]=0;
	event_times[1]=rand_exp(ints[1])+getTime()/1000;
	event_number[1]=0;
	event_times[2]=rand_exp(ints[2])+getTime()/1000;
	event_number[2]=0;
	double st_time=getTime()/1000;
	
	while (true)
	{
		int i=0;
		while (i<3)
		{
			if (event_times[i]<getTime()/1000)
			{
				event_number[i]++;
				event_times[i]=rand_exp(ints[i])+getTime()/1000;
				if (i<2)
				{
					int interval=0;
					if ((getTime()/1000-event_last[0])>ints[2])
					{
						interval=1;
					}
					event_last[0]=getTime()/1000;
					combined_probs[interval]++;
				}
				else
				{
					int interval=0;
					if ((getTime()/1000-event_last[1])>ints[2])
					{
						interval=1;
					}
					event_last[1]=getTime()/1000;
					sum_probs[interval]++;
				}
				
			}
			i++;
		}
		double exp_time=getTime()/1000-st_time;
		event_number[3]=event_number[0]+event_number[1];
		system("cls");
		cout<<"First event happend "<<event_number[0]<<" times. This is "<<event_number[0]/exp_time<<" times per second on average"<<endl;
		cout<<"Second event happend "<<event_number[1]<<" times. This is "<<event_number[1]/exp_time<<" times per second on average"<<endl;
		cout<<"First OR Second event happend "<<event_number[3]<<" times. This is "<<event_number[3]/exp_time<<" times per second on average"<<endl;
		cout<<"Event with combined intensivity happend "<<event_number[2]<<" times. This is "<<event_number[2]/exp_time<<" times per second on average"<<endl;
		cout<<endl;
		cout<<"For 'OR' event thread"<<endl;
		double av=combined_probs[1]*1.0/(combined_probs[0]+combined_probs[1]);
		cout<<"Average: "<<av<<endl;
		cout<<"Dispersion: "<<av*(1-av)<<endl;
		cout<<endl;
		cout<<"For Sum event thread"<<endl;
		av=sum_probs[1]*1.0/(sum_probs[0]+sum_probs[1]);
		cout<<"Average: "<<av<<endl;
		cout<<"Dispersion: "<<av*(1-av)<<endl;
	}
	
	
}
