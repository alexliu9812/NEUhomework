//用FileWriter类向文件中写入一串字符，并用FileReader读出
//FileStream.java

import java.io.*;
public class ReaderTest
{
	public static void main(String[] args)
	{
		File f=new File("hello.txt");
		try
		{
			FileWriter out=new FileWriter(f);
			out.write("This is an example for FileI/O");
			out.close();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		
		try
		{
			FileReader in=new FileReader(f);
			char[] buf=new char[1024];
			int len=in.read(buf);
			System.out.println(new String(buf,0,len));
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
}