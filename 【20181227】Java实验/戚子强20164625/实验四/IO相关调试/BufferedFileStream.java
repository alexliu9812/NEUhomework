//用FileOutputStream类向文件中写入一串字符，并用FileInputStream读出
//FileStream.java

import java.io.*;
public class BufferedFileStream
{
	public static void main(String[] args)
	{
		File f=new File("D:\\hellos.txt");
		try
		{
			//FileOutputStream out=new FileOutputStream(f);
			BufferedOutputStream bout=new BufferedOutputStream(new FileOutputStream(f));
			byte buf1[]="11".getBytes();
			byte buf2[]="22".getBytes();
			byte buf3[]="33".getBytes();
			bout.write(buf1);
			bout.write(buf2);
			bout.write(buf3);
			bout.close();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		
		try
		{
			//FileInputStream in=new FileInputStream(f);
			BufferedInputStream bin=new BufferedInputStream(new FileInputStream(f));
			
		    
			byte[] buf1=new byte[2];
			byte[] buf2=new byte[2];
			byte[] buf3=new byte[2];
		
		    bin.mark(2);
			int len=bin.read(buf1);
           // bin.reset();
			int len2=bin.read(buf2);
			int len3=bin.read(buf3);
			System.out.println(new String(buf1,0,len));
		    System.out.println(new String(buf2,0,len2));
		    System.out.println(new String(buf3,0,len3));
			bin.close();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
	}
}