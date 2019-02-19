public class change2{

   static  class Human{
    String name;
  }
  
  static void change2(Human h){
//    h = new Human();
    h.name = "Bob";
    System.out.println("Human in change:"+h.name); 
}

  
  public static void main(String args[]){
    Human m = new Human();
    m.name = "Bill";
    
    System.out.println("Human before change:"+m.name);  
    change2(m);
    System.out.println("Human after change:"+m.name); 
  }

}