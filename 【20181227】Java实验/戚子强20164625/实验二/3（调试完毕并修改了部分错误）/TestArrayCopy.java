import java.util.*;
public class TestArrayCopy
{
	public static void main(String [] args)
	{
       int ia[]=new int[]{1,2,3,4,5};
       int ib[]=new int[]{9,8,7,6,5,4,3};
       
       System.arraycopy(ia,0,ib,0,3);
     // 复制源数组中从下标0开始的3个元素到目的数组，从下标0的位置开始存储。
       for(int i=0;i<ia.length;i++)
           System.out.print(ia[i]);
		   System.out.println();
       
       for(int j=0;j<ib.length;j++)
           System.out.print(ib[j]);
			System.out.println();
			
			Arrays.sort(ib);
			for(int j=0;j<ib.length;j++)
           System.out.print(ib[j]);
			System.out.println();
			
	}
}