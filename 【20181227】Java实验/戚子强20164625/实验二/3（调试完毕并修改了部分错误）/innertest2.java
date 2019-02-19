class Outer
{
	static int outer_i = 100;
	int z;
	void test()
	{
		Inner in = new Inner();
		in.display();
	}
	
	static class Inner
	{
    static int y=10;	 
	 static void display()
		{
	
		System.out.println("display: outer_i = " + outer_i);
		}
	}
	
	void showY()
	{
	  //System.out.println(y);
  }
}


class innertest2
{
	public static void main(String[] args)
	{
		Outer.Inner InRef;
		InRef = new Outer.Inner();
		InRef.display();
	  Outer.Inner.display();
	 System.out.println(Outer.Inner.y);
	}
}