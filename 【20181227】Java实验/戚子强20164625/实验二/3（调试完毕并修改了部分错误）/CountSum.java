public class CountSum{
	int count(int a,int b){
		return a+b;
	}
	int count(int a ,int b, int c){
		return a+b+c;
	}
	int count(int a,int b,int c,int d){
		return a+b+c+d;
	}
	
	public static void main(String args[]){
		CountSum cs = new CountSum();
		int result = cs.count(348,578);
		System.out.println(result);
	}
}