class A {
	int x;
	void func()	{
		System.out.println("func() in A");
	}		
	void foo() {
		System.out.println("foo() in A");
	}
}

class B extends A {
	void func()	{
		System.out.println("func() in B");
	}	
}

public class testinheritance3 {
	public static void main(String[] args) {
		A a = new A();
		B b = new B();
		a.func();
		b.func();
		a.foo();
		b.foo();
	}
}
