//用FileOutputStream类向文件中写入一串字符，并用FileInputStream读出
//FileStream.java

import java.io.*;

public class FileStream
{
	public static void main(String[] args)
	{
		File f=new File("hello.txt");
		try
		{
			FileOutputStream out=new FileOutputStream(f);
			byte buf[]="This is an example for FileI/O".getBytes();
			out.write(buf);
			out.close();

		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		
		try
		{
			FileInputStream in=new FileInputStream(f);
			byte[] buf=new byte[1024];
			int len=in.read(buf);
			System.out.println(new String(buf,0,len));
			in.close();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
}