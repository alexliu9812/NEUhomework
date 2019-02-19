class Human2{
   String name;
   int age;
   Human2(){
       System.out.println("A Human has been created¡­");
   }
   public Human2(String name){
           System.out.println("one parameter¡­");
           this.name=name;
   }
   
   public Human2(String name,int age){  
           
           this(name);
            System.out.println("two  parameters¡­");   
           this.age=age;
  }
  
  void print()
  {
    System.out.println("name="+name);
    System.out.println("age ="+age);
  }

   public static void main(String[] args){
       //Human2 h1=new Human2();
       Human2 h1 = new Human2("Bob", 33);
       h1.print();
  }
} 
