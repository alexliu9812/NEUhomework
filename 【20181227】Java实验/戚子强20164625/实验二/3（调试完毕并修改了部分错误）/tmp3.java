class Hello0 {
  static void func()	{
		int i = 0;
		System.out.println("Hello" + i);
	}		
	
	void func(int i){
  
  }
}

class Hello1 extends Hello0 {
	static  void func()	{
		int i = 1;
		System.out.println("Hello" + i);
  }
  	

//	int  func(int i) {
 int func (float i){
		System.out.println("arg of Hello1 = " + i);
	  return (int)i;
  }	
}


class tmp3 {
  public static void main(String []args)
  {
    Hello0 h0 = new Hello0();
    Hello1 h1 = new Hello1(); 

    
    h0.func();
    h1.func();
    h1.func(15);

    
  }
}