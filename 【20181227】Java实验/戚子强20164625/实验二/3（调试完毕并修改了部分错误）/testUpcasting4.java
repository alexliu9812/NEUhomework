class A
{
	void func()
	{
		System.out.println("func() in A");
	}   
}
class B extends A
{
	void func()
	{
		System.out.println("func() in B");
	}
}
class C extends A
{
	void func()
	{
		System.out.println("func() in C");
	}
}
public class testUpcasting4
{
	static void call(A a)
	{
		a.func();
	}
	public static void main(String[] args)
	{
		A a = new A();
		B b = new B();
		C c = new C();

		call(a);
		call(b);
		call(c);
	}
}
