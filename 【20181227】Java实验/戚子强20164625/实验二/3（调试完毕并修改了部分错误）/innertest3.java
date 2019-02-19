class Outer
{
	int outer_i = 100;
  public class Inner
	{
	 int outer_i = 10;
	 void display()
		{
		System.out.println("display: outer_i = " + Outer.this.outer_i);
		System.out.println("display: outer_i = " + Inner.this.outer_i);
		System.out.println("display: outer_i = " + this.outer_i);
		}
	}	
}

public class innertest3
{
	public static void main(String[] args)
	{
		Outer.Inner InRef;
		Outer outRef;
	  outRef = new Outer();
	//	InRef = new Outer().new Inner();
  	InRef = outRef.new Inner();
		InRef.display();

	}
}