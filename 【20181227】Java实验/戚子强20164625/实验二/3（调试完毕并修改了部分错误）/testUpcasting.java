class A {
	void func() {
		System.out.println("func() in A");
	}   
}

class B extends A { }

public class testUpcasting {
	static void call(A a) 
  {
		  a.func();
	}


	public static void main(String[] args) 
  {
		B b=new B();
		A a=new A();
		call(a);		
		call(b); // Upcasting
	}
}
