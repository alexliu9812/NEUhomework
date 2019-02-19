class Person 
{
      public String name;
      public int age;
	  public Person(String name,int age)
	 {
		this.name=name;
		this.age=age;
	  }
	 
  //  public Person() {}
      public void getInfo() 
      {
       	System.out.println(name);    
      	System.out.println(age);    
      }
}
class Student extends Person
{
      public void study()
      {
      	    System.out.println("Studying");
      }
      
      public static void main(String[] args)
      {
      	Person p=new Person();
      	p.name="person";
      	p.age=30;
      	p.getInfo();
      	
      	Student s=new Student();
        s.name="student";
        s.age=16;
        s.getInfo();
        s.study();
      }
}