import java.io.*;
public class ClassName {

	public static void main(String[] args) throws Exception{
		
		Classmate c1=new Classmate("dgg",11);
		Classmate c2=new Classmate("dgfhhghhj",12);
		Classmate c3=new Classmate("asdfghjk",13);
		
		RandomAccessFile rf=new RandomAccessFile("e:\\myclass.txt","rw");
		rf.writeInt(c1.no);
		rf.write(c1.name.getBytes());
		rf.writeInt(c2.no);
		rf.write(c2.name.getBytes());
		rf.writeInt(c3.no);
		rf.write(c3.name.getBytes());
		
		rf.close();
		RandomAccessFile rf2=new RandomAccessFile("e:\\myclass.txt","r");
		rf2.skipBytes(12);//学号占4个字节，姓名占8个字节
		System.out.print("第二个学生：");
		System.out.print(rf2.readInt()+" ");
		String str="";
		int len=8;
		for(int i=0;i<len;i++)
		{
			str=str+(char)rf2.readByte();
		}
		System.out.println(str);
		//System.out.println(rf2.readInt());
		rf2.close();
	}
}
class Classmate
{
	String name;
	int no;
	final static int NAMELEN=8;
	public Classmate(String name,int no)
	{
		if(name.length()>NAMELEN)
		{
			name=name.substring(0,8);
		}
		else
		{
			while(name.length()<NAMELEN)
			{
				name=name+" ";
			}
		}
		this.name=name;
		this.no=no;
	}
}