class MyKey
{
	private String name;
	private int age;
	public MyKey(String name,int age)
	{
		this.name = name;
		this.age = age;
	}
	public String toString()
	{
		return new String(name + "," + age);
	}
	public boolean equals(Object obj)
	{
		if(obj instanceof MyKey)
		{
			MyKey objTemp = (MyKey)obj;
			if(name.equals(objTemp.name) && age==objTemp.age)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		//假如obj不是MyKey类的实例对象，它就不可能与当前对象相等了
		else 
		{
			return false;
		}
	}
	public int hashCode()
	{
		return name.hashCode() + age;
	}
}