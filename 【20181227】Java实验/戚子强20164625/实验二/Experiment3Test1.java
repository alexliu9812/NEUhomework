public class Experiment3Test1{
    public static void main(String[] agrs){
        CountInt c = new CountInt();
        System.out.println(c.count(348,578));
    }
}

class CountInt{
    int count(int a, int b){
        return (a+b);
    }
    int count(int a, int b, int c){
        return (a+b+c);
    }
    int count(int a, int b, int c, int d){
        return (a+b+c+d);
    }
}