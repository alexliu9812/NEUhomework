class Outer
{
	int outer_i = 100;
  int member = 0;
  public class Inner{
        int member=10;
    		public void display()
        {			
         System.out.println(this.member);
         System.out.println(Outer.this.member);	
         
        }
  }
}

public class innertest4
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