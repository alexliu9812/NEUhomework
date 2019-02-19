import java.util.*;  //下面用到的Vector类和Enumeration接口都在此包中
public class TestVector
{
	public static void main(String [] args)
	{
		int b=0;
		Vector v=new Vector();
		System.out.println("Please Enter Number:");
		while(true)
		{
			try
			{
				b= System.in.read();
			}
           	catch(Exception e)
			{
				System.out.println(e.getMessage());
			}
			
		//	if (b== ' ') continue;
			if(b=='\r' || b== '\n')
				break;
			else
			{   
			
				int num=b-'0';
				v.addElement(new Integer(num));
			}
		}
		int sum=0;
		Enumeration e=v.elements();    
		while(e.hasMoreElements())
		{
			Integer intObj=(Integer)e.nextElement();
			sum += intObj.intValue();
		}
		System.out.println(sum);
	}
}
