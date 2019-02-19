class Human 
{
	int age;
	char sex;
	int money;

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
	}

public static void main(String args[])
 {
   Human aMan;
   aMan = null;
//   aMan = new Human();
   aMan.sex = 'M';
   aMan.age = 24;
   aMan.printAge();
  
 }
}