public class change3{
  static class Human{
    String name;
  } 
  
  static void change3(Human h){
  //  h = new Human();
    h.name = "Bob";
    System.out.println("Human in change:"+h.name);
  }
  
  public static void main(String args[]){
    Human m = new Human();
    m.name = "Bill";
    
    System.out.println("Human before change:"+m.name);
    change3(m);
    System.out.println("Human after change:"+m.name);

  }
}