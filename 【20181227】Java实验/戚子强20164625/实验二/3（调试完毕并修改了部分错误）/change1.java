//test1.java
public class change1{

 public  void change1(int i){
      i = 100;
      System.out.println("i in change is:"+i); //打印出??
    }

public static void main(String args[]){
	  
	   change1 c1= new change1();
	   int i;
	   i=10;
	   System.out.println("i is:"+i);
	   c1.change1(i);
     System.out.println("i after change is:" + i); //打印出??
     
    
}   
}
