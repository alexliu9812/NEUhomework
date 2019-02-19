abstract class A
{
	abstract public void func1();
}

public class InnerClass {
	public static void main(String[] args) {
		class Inner extends A
		{
			public void func1()
			{
				System.out.println("implement for func1");
			}
		}
		call(new Inner());
	}	
	public static void call(A a)
	{
		a.func1();
	}
}
