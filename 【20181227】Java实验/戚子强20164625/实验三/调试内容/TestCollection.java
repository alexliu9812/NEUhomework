import java.util.*;  //ArrayList类和Iterator接口都在此包中
public class TestCollection
{
	public static void main(String [] args)
	{
        int b=0;
		ArrayList al=new ArrayList();
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
			if(b=='\r' | b== '\n')
				break;
			else
			{
				int num=b-'0';
				al.add(new Integer(num));
			}
		}
		int sum=0;
		Iterator itr=al.iterator();
		while(itr.hasNext())
		{
			Integer intObj=(Integer)itr.next();
			sum += intObj.intValue();
		}
		System.out.println(sum);
	}
}