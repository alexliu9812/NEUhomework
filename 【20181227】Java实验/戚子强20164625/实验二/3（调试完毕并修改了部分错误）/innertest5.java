class Outer
{
	int outer_i = 100;
  int member = 0;
  void test()
  {
        class Inner{
           int member=10;
    		   public void display()
           {			
            System.out.println(this.member);  
           }
        }
        Inner inner = new Inner();
        inner.display();
  }
  
//  Inner inner2;
}

public class innertest5
{
	public static void main(String[] args)
	{

		Outer outRef;
	  outRef = new Outer();
	  outRef.test();
 	}
}