class Hello0 {
	void func()	{
		int i = 0;
		System.out.println("Hello" + i);
	}		
}

class Hello1 extends Hello0 {
	void func()	{
		int i = 1;
		System.out.println("Hello" + i);
	}	

	void func(int i) {
		System.out.println("arg of Hello1 = " + i);
	}	
}

class Hello2 extends Hello1 {
	void func()	{
		int i = 2;
		System.out.println("Hello" + i);
	}	
}

class Hello3 extends Hello2 {
	void func(boolean b) {
		System.out.println("arg of Hello3 = " + b);
	}	
}

class testoverride {
  public static void main(String []args)
  {
    Hello0 h0 = new Hello0();
    Hello1 h1 = new Hello1(); 
    Hello2 h2 = new Hello2(); 
    Hello3 h3 = new Hello3();
    
    h0.func();
    h1.func();
    h1.func(15);
    h2.func();
    h2.func(10);
    h3.func();
    h3.func(true);
    h3.func(100);
    
  }
}