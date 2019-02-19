class Base {
	void func() {
		System.out.println("func() in Base");
	}
}
class Sub extends Base {
	void func() {
		super.func();
		System.out.println("func() in Sub");
	}
}
public class testsuper {
	public static void main(String[] args) {
		new Sub().func();
	}
}
