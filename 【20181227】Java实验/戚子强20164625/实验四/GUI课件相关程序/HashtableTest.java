import java.util.*;
public class HashtableTest
{
	public static void main(String[] args)
	{
		Hashtable numbers=new Hashtable();
		numbers.put(new MyKey("zhangsan",18),new Integer(1));
		numbers.put(new MyKey("lisi",15),new Integer(2));
		numbers.put(new MyKey("wangwu",20),new Integer(3));
		Enumeration e=numbers.keys();
		while(e.hasMoreElements())
		{
			MyKey key=(MyKey)e.nextElement();
			System.out.print(key.toString()+"=");//没看到。。。。。。。
			System.out.println(numbers.get(key).toString());
		}
	}
}