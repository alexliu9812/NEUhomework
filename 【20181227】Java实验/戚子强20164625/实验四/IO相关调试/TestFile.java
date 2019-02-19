import java.io.*;
public class TestFile {

	public static void main(String[] args) {
		File f=new File("e:\\myinfo.txt");
		try
		{
			FileWriter fw=new FileWriter(f);
			fw.write("02222\nliuzheng\nfemale");
			fw.close();
		}catch(IOException e)
		{
			System.out.println(e.getMessage());
		}
		char ch[]=new char[1024];
		try{
			FileReader fr=new FileReader(f);
			int len=fr.read(ch);
			System.out.println(new String(ch,0,len));
			fr.close();
		}catch(IOException e)
		{
			System.out.println(e.getMessage());
		}
	}
}
