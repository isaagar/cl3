import java.util.*;
public class BayesClass implements Runnable
{
	static String
	Work_Type[]={"Consultancy","Service","Research","Service","Consultancy","Research","Research","Service","Consultancy","Research"};
 	static int Age[]={30,21,26,28,40,35,27,32,45,36}; 
	static String
	Qualification[]={"Ph.D.","MTech.","MTech.","BTech.","MTech.","Ph.D.","BTech.","MTech.","BTech.","Ph.D."};
	static int Experience[]={9,1,2,10,14,10,6,9,17,7};
	static double prob[][]=new double[3][3];
	static double pp=3.0/10.0;
	static double npp=3.0/10.0;
	static double research=4.0/10.0;
	static int flag=0;
	static int flag1=0;
	static int flag2=0;
	static double play_N=1;
	static double notplay_N=1;
	static double researchp=1;
	static void cal_N(int a)
	{
		if(a==1)
		{
			for(int i=0;i<3;++i)
			play_N*=prob[i][0];
			play_N*=pp;
		}
		else if(a==2)
			{
				for(int i=0;i<3;++i)
				notplay_N*=prob[i][1];
				notplay_N*=npp;
			}
			else{
					for(int i=0;i<3;++i)
					researchp*=prob[i][2];
					researchp*=research;
				}
	}
	static double cal_play_prob(String ch)
	{
		double prob=0;
		double count=0;
		if(flag==0)
		{
			for(int i=0;i<10;++i)
			if(Age[i]==Integer.parseInt(ch) && Work_Type[i].equals("Consultancy"))
				++count;
			prob=count/3.0;
			flag=1;
		}
		else if(flag==1)
			{
				for(int i=0;i<10;++i)
				if(Qualification[i].equals(ch) && Work_Type[i].equals("Consultancy"))
					++count;
				prob=count/3.0;
				flag=2;
			}
			else if(flag==2)
				{
					for(int i=0;i<10;++i)
					if(Experience[i]==Integer.parseInt(ch) && Work_Type[i].equals("Consultancy"))
						++count;
					prob=count/3.0;
					flag=3;
				}
		return prob;
	}
	static double cal_noplay_prob(String ch)
	{
		double prob=0;
		double count=0;
		if(flag1==0)
		{
			for(int i=0;i<10;++i)
			if(Age[i]==Integer.parseInt(ch) && Work_Type[i].equals("Service"))
				++count;
			prob=count/3.0;
			flag1=1;
		}
		else if(flag1==1)
			{
				for(int i=0;i<10;++i)
				if(Qualification[i].equals(ch) && Work_Type[i].equals("Service"))
					++count;
				prob=count/3.0;
				flag1=2;
			}
		else if(flag1==2)
			{
				for(int i=0;i<10;++i)
				if(Experience[i]==Integer.parseInt(ch) && Work_Type[i].equals("Service"))
					++count;
				prob=count/3.0;
				flag1=3;
			}
		return prob;
	}	
	static double cal_nResearch_prob(String ch)
	{
		double prob=0;
		double count=0;
		if(flag2==0)
		{
			for(int i=0;i<10;++i)
			if(Age[i]==Integer.parseInt(ch) && Work_Type[i].equals("Research"))
				++count;
			prob=count/4.0;
			flag2=1;
		}
		else if(flag2==1)
			{
				for(int i=0;i<10;++i)
				if(Qualification[i].equals(ch) && Work_Type[i].equals("Research"))
					++count;
				prob=count/4.0;
				flag2=2;
			}
		else if(flag2==2)
		{
			for(int i=0;i<10;++i)
			if(Experience[i]==Integer.parseInt(ch) && Work_Type[i].equals("Research"))
				++count;
			prob=count/4.0;
			flag2=3;
		}
		return prob;
	}
	public BayesClass() 
	{
		Thread th=new Thread(this);///calling thread
		th.start();
	}
	public static void main(String args[])
	{
		BayesClass b=new BayesClass();
	}
	@Override
	public void run() 
	{
		Scanner scr=new Scanner(System.in);
		System.out.println("Table\n");
		System.out.println("Work Type\tAge\tQualification\tExperience");
		for(int i=0;i<10;++i)
		{	
			System.out.print(Work_Type[i]+"\t\t"+Age[i]+"\t\t"+Qualification[i]+"\t\t"+Experience[i]);
			System.out.println();
		}
		System.out.println("\nEnter your input:");
		String[] s = new String[20];
		for(int j=0;j<3;j++)
		{
			s[j]=scr.next();
		}
		String ch;
		int count=0;
		for(int i=0;i<3;i++)
		{
			ch=s[i];
			prob[count][0]=cal_play_prob(ch);
			prob[count][1]=cal_noplay_prob(ch);
			prob[count][2]=cal_nResearch_prob(ch);
			++count;
			System.out.print(s[i]+"\n");
		}	
		cal_N(1);
		cal_N(2);
		cal_N(3);
		double pt=play_N+notplay_N+researchp;
		double prob_of_play=0;	
		double prob_of_noplay=0;
		double prob_of_research=0;
		prob_of_play=play_N/pt;
		prob_of_noplay=notplay_N/pt;
		prob_of_research=research/pt;
		if(prob_of_play>prob_of_noplay && prob_of_play>prob_of_research)
			System.out.println("\nThe new tuple classified under \"Consultancy\"category.Hence there will be consultancy type!!!");
		else if(prob_of_noplay>prob_of_play && prob_of_noplay>prob_of_research)
			System.out.println("\nThe new tuple classified under \"Service\"category.Hence there will be service play.");
		else{
			System.out.println("\nThe new tuple classified under \"Research\"category.Hence there will be Research type.");
			}
	}
}

