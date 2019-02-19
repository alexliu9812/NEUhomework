class TestInteger
{
	public static void main(String[] args)
	{
		int w = Integer.parseInt(args[0]);  //第一种方法
		int h = new  Integer(args[1]).intValue(); //第二种方法
		//int h = Integer.valueOf(args[1]).intValue(); //第三种方法
		for(int i=0;i<h;i++)
		{
		StringBuffer sb=new StringBuffer();
		for(int j=0 ;j<w;j++)
		{
			sb.append('*');
		}
		System.out.println(sb.toString());
		}
	}
}