import java.io.*;
public class RandomFileTest {

	public static void main(String[] args) throws Exception
	{
		RandomAccessFile ra=new RandomAccessFile("e:\\3.txt","rw");
		String s="Hello!\nHow r u?";
		ra.write(s.getBytes());
		ra.close();
		RandomAccessFile raf=new RandomAccessFile("e:\\3.txt","r");
		raf.skipBytes(2);
		//raf.seek(2);
		String str="";
		for (int i=0;i<s.length()-2;i++)
			str=str+(char)raf.readByte();
		System.out.println(str);
		raf.close();
	}
}