class Human6//方法参数为对象的引用
{
    String name;
}
public class canshuchuandi2 {
    void change2(Human6 h){
        h.name = "Bob";
        System.out.println("Human in change:"+h.name);
    }
    void change3(Human6 h){
        h = new Human6();
        h.name = "Bob";
        System.out.println("Human in change:"+h.name);}
    public static void main(String args[])
    {
        Human6 m = new Human6();
        m.name = "Bill";
        System.out.println("Human before change:"+m.name);
        canshuchuandi2 test=new canshuchuandi2();
        test.change2(m);
        System.out.println("Human after change:"+m.name);

        m.name = "Bill";
        System.out.println("Human before change:"+m.name);
        test.change3(m);
        System.out.println("Human after change:"+m.name);
    }


}


