public class canshuchuandi {//参数传递
    void change1(int i){
        i = 100;
        System.out.println("i in change is:"+ i); //打印出??
    }

    public static void main(String[] args)
    {
        int i = 10;
        System.out.println("i before change is:" + i);//打印出??
        canshuchuandi test=new canshuchuandi();
        test.change1(i);
        System.out.println("i after change is:" + i);//打印出??

    }

}
