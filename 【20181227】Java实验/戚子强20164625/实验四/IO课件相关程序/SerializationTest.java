import java.io.*;
class Student implements Serializable
{
	int id;
	String name;
	int age;
	String department;
	public Student(int id,String name,int age,String department)
	{
		this.id=id;
		this.name=name;
		this.age=age;
		this.department=department;
	}
}
public class SerializationTest
{
	public static void main(String[] args) throws IOException,ClassNotFoundException
	{
		Student stu=new Student(20,"mary",20,"computer");
		FileOutputStream out=new FileOutputStream("Serializationl.txt");
		ObjectOutputStream oout=new ObjectOutputStream(out);
		try
		{
			oout.writeObject(stu);
			oout.close();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		stu=null;
		FileInputStream in=new FileInputStream("Serializationl.txt");
		ObjectInputStream oin=new ObjectInputStream(in);
		try
		{
			stu=(Student)oin.readObject();
			oin.close();
		}
		catch(Exception e)
		{
			System.out.println(e.getMessage());
		}
		System.out.println("ID is "+stu.id);
		System.out.println("name is "+stu.name);
		System.out.println("age is "+stu.age);
		System.out.println("department is "+stu.department);
	}
}
		