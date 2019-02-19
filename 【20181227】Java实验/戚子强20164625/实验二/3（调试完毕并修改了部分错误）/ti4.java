class A {
  int x;
	static
	{
	  System.out.println("static part in A is executed." );
  }
  
  A()
  {
    System.out.println("The constructor of A is is called.");
  }

}

class B extends A {
  static
	{
	  System.out.println("static part in B is executed." );
  }
  B()
  {
    System.out.println("The constructor of B is is called.");
  }
}

public class ti4  {
	public static void main(String[] args) {
//		A a = new A();
		B b = new B();
 //   new A();
    new B();
	}
}
