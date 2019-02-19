class A {
   int x;
	void func() {
		System.out.println("func() in A");
	}
}

class B extends A {
}

public class testinheritance1 {
	public static void main(String[] args) {
		B b = new B();
		b.x = 4; 
		System.out.println("b.x = " + b.x);
		b.func();
	}
}
