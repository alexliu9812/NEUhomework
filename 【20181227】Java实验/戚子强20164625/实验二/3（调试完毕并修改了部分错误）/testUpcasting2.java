class A
{
	int i = 1;
	void func()
	{
		System.out.println("func() in A");
	}   
}
class B extends A
{
	int i =2 ;
	void func()
	{
		System.out.println("func() in B");
	}
}

public class testUpcasting2
{
	public static void main(String[] args)
	{
		A a = new A();
		B b = new B();

		a.func();
		b.func();
		
		System.out.println("b.i = " + b.i);
		System.out.println("a.i = " + a.i);

		// Notice the following code.
		A x = new B();

		x.func();
		System.out.println("x.i = " + x.i);
	}
}
