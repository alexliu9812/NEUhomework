public class TestArrayLength
{
	public static void main(String [] args)
	{
       int ia[]=new int[]{1,2,3,4,5};
       int ib[]=new int[]{9,8,7,6,5,4,3};
       
       System.out.println("ia.length="+ia.length);
       for(int i=0;i<ia.length;i++)
           System.out.print(ia[i]);
		   System.out.println();
       
       for(int j=0;j<ib.length;j++)
           System.out.print(ib[j]);
			System.out.println();
	}
}