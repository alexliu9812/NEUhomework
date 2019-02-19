import java.util.Scanner;
public class Experiment2Test2{
    public static void main(String[] agrs){
        Scanner input = new Scanner(System.in);
        int num = input.nextInt();
        double max = Math.sqrt(num) + 1;
        boolean flag = true;
        for(int i = 2; i <= max; i++)
        {
            if((num%i == 0 && i != num)||num == 1)
                flag = false;
        }
        System.out.println(num + " is" + ((flag)?"":" not") + " a prime number.");
        input.close();
    }
}