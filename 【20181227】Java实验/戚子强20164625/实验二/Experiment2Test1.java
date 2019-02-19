import java.util.Scanner;
public class Experiment2Test1{
    public static void main(String[] args){
        System.out.print("Please Input People Num:");
        Scanner input = new Scanner(System.in);
        int x = input.nextInt();
        System.out.println("Car Num:"+((x+1)/7+1));
        input.close();
    }
}