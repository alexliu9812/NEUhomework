class Student
{
	String name;
	int age;
	public boolean equals(Object obj)
	{
		Student st=null;
		if(obj instanceof Student)
		   st=(Student)obj;
		else
		   return false;
		if(st.name==this.name&&st.age==this.age)
		   return true;
		   else
		   return false;
	 }  
} 


class testObject2
{
  public static void main(String[] args)
  {
	   Student p=new Student();
	   Student q=new Student();
	   p.name="aaa";
	   q.name="aaa";
	   p.age=20;
	   q.age=20;
	   if (p.equals(q))
	      System.out.println("相等");
	   else   
	       System.out.println("不相等");
   }
}