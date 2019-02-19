abstract class A
{
	abstract public void func1();
}

public class InnerClass2 {
	public static void main(String[] args) {
		call(new A()
    {
      public  void func1(){
         System.out.println("fun1 is called");
       }
    }
    );
	}	
	public static void call(A a)
	{
		a.func1();
	}
}
