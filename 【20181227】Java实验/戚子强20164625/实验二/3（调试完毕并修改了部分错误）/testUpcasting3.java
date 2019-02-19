class A
{
	public void func1()
	{
		System.out.println("A func1 is calling");
		
	}
	public void func2()
	{
		func1();
	}
}
class B extends A
{
	public void func1()
	{
		System.out.println("B func1 is calling");
	}
}

class testUpcasting3
{
	public static void call(A a)
	{
		a.func1();
		a.func2();
	}
	public static void main(String args[])
	{
		B b=new B();
		A a=b;
		call(a);
		call(b);
		a = new A();
		call(a);
		
	}
}
