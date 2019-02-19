public class TestException
{
	public static void main (String[] args)
	{
		try
		{
			String s = "10.1";
			int a = Integer.parseInt(s);
			System.out.println("a = " + a);
			int b = 10;
			System.out.println("b = " + b);
			int c = a / b;	
			System.out.println("a / b = " + c);
		}
//
		catch(NumberFormatException nfe)
		{
		  System.out.println("Error:" + nfe);
			System.out.println("Error Message: " + nfe.getMessage());
			nfe.printStackTrace();
		}
		catch(ArithmeticException ae)
		{
			System.out.println("ERROR: " + ae);
		}

		System.out.println ("program ends.");
		
	}
}
