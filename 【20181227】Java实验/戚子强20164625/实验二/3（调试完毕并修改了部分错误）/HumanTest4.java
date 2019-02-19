class HumanTest4
{
	int age=100;
	char sex;
	int money;
        static int test;

	void printAge()
	{
		System.out.println("My age is " + age);
	}

	void isManOrWoman()
	{
         

		if (sex == 'M' || sex == 'm')
			System.out.println("I am a man");
		else if (sex == 'F' || sex == 'f')
			System.out.println("I am a woman");
		else
			System.out.println("I am sorry ~~~");
	}

	int getMoney()
	{
		return money;
	}

	void addMoney(int m)
	{
		money += m;
		System.out.println("I got $" + money);
		return;
	}
	
	public static void main(String[] args)
  {
     HumanTest4 man1; 
     man1 = new HumanTest4();
    // man1 = null;
 
     System.out.println("Money is :" + man1.getMoney());


  }
}
