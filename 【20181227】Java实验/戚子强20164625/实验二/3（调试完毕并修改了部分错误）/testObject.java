
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
}

public class testObject{
public static void main(String args[])
 {
	String s1 = new String("Hello");
  String s2 = new String("Hello");
  String s3 = s1;
  
  System.out.println("s1==s2 is "+ (s1==s2));
  System.out.println("s1==s3 is "+ (s1==s3));
  
  Human h1 = new Human();
  Human h2 = new Human();	
  Human h3 = h1;
  
  System.out.println("h1.equals(h2) is "+ h1.equals(h2));
  System.out.println("h1.equals(h3) is "+ h1.equals(h3));
  
  System.out.println("s1.equals(s2) is "+ s1.equals(s2));
  System.out.println("s1.equals(s3) is "+ s1.equals(s3));
 
 
 }
}