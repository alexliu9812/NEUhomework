class Super {
   public Super (int i) { }
  Super (){}
}

class Derived extends Super {
   public Derived (){} //������ʽ���ö�û���޲ι��췽��

   
   public Derived (int i){
    super(i);	//��ȷ��ʽ���ô��ι��췽��
   }
}

public class testsuper2
{
	public static void main(String[] args) {
		new Derived();
	}
}
