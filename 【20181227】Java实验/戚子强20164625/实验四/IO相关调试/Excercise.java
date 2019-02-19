import java.io.*;
import java.util.*;
public class Excercise {

	public static void main(String[] args) throws Exception {
		
		File f=new File("d:\\D:\Java教程\\Java课件王波涛\\Java\\IO\\last.txt");
		
		BufferedInputStream br=new BufferedInputStream(new FileInputStream(f));
		
		Vector v=new Vector();
		
		byte[]str;
		
		while(str=br.read(byte[])!='\n')
		{

			v.add(str);
		}
		
		int size=v.size();
		System.out.println(size);
		Enumeration e=v.elements();
		
		String[] tmp=new String[size];
		
		int i=0;
		
		while(e.hasMoreElements())
		{
			tmp[i]=(String)e.nextElement();
			i++;
		}
		
		for (i=size;i>0;i--)
		{
			System.out.println(tmp[i-1]);
		}
		
		
	}
}