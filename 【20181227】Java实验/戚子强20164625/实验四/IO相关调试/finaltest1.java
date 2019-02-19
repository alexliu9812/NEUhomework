import java.io.*;
public class finaltest1 {

	public static void main(String[] args) throws Exception
	{
		RandomAccessFile ra=new RandomAccessFile("e:\\3.txt","rw");
		String s="Hello! How r u?\nI am Fine.";
		ra.write(s.getBytes());
		ra.close();
		RandomAccessFile raf=new RandomAccessFile("e:\\3.txt","r");
		raf.seek(7);
		String str="";
		for (int i=0;i<s.length()-7;i++)
			str=str+(char)raf.readByte();
		System.out.println(str.toUpperCase());
		raf.close();
	}
}