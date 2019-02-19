abstract class A
{
	abstract public void func1();
}
public class innertest6
 {
	public static void main(String[] args) 
     {
		call(new A()
            {
			public void func1()
			{
				System.out.println("implement for func1");
			}
		    });
      }	
	public static void call(A a)
	{
		a.func1();
	}
}