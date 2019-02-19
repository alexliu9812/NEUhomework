public class Experiment1Test2{
    public static void main(String[] args){
        System.out.println("For:");
        for(int i = 1; i <= 100; System.out.println(i), i++);
        System.out.println("While:");
        int i = 1;
        while(i<=100){
            System.out.println(i);
            i++;
        }
        System.out.println("Do-While:");  
        i = 1;
        do{
            System.out.println(i);
            i++;
        }while(i<=100);    
    }
}