class Human{
  private int age;
  public int getAge(){
      return age;
   }
  public void setAge(int i){
       if(i<0||i>130)   return;
       age=i;
   }

}

public class Test{
public static void main(String[] args)
{
Human h1=new Human();
//h1.age=10;
h1.setAge(10);
//h1.age=-12
h1.setAge(-12);
System.out.println(h1.getAge());
}
}
  

