class A {
	int x;
	void func() {
		System.out.println("func() in A");
	}
}

class B extends A {
  void foo(){
    System.out.println("foo() in B");
  }
}

public class testinheritance2 {
	public static void main(String[] args) {
		A a = new A();
		B b = new B();
		a.func();
		b.func();
		b.foo();
		// a.foo(); 

	}
}
