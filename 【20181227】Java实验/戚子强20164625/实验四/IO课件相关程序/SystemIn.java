import java.util.*;
public class SystemIn{
	public static void main(String args[])
	{
		int c;
		byte []b = new byte[1024];
		try{
		
		  while ((c=System.in.read())!= -1){	
			System.out.print((char )c );
			//System.out.print(c);
			System.out.printf(" input is  %d", c);
		  }
		}
		catch(Exception e)
		{
		}
		
	}
}