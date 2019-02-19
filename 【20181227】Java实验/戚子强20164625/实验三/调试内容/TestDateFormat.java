import java.util.*;
import java.text.*;
public class TestDateFormat 
{
	public static void main(String[] args)
	{
		Date d1 = new Date();
		System.out.println(d1.toLocaleString());
		System.out.println(d1.toString());
		System.out.println(d1.toGMTString());
		
		SimpleDateFormat sdf1 =new SimpleDateFormat("yyyy-MM-dd:HH:mm:ss");
		SimpleDateFormat sdf2 =new SimpleDateFormat("yyyy年MM月dd日");
		SimpleDateFormat sdf3 =new SimpleDateFormat("yy年M月dd日");	
		SimpleDateFormat sdf4 = new SimpleDateFormat("yyyy.MM.dd G 'at' HH:mm:ss z");
		try
		{
			Date d=sdf1.parse("2003-10-15:12:34:45");
			System.out.println(sdf2.format(d));
			System.out.println(sdf3.format(d));
			System.out.println(sdf4.format(d));
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
}
