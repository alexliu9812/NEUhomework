import java.io.*;
public class TestFile2 {

	public static void main(String[] args) {
		File f=new File("e:\\myinfo.txt");
		try
		{
			FileWriter fw=new FileWriter(f);
		//	fw.write("02222|liuzheng|female");
				fw.write("02222\nliuzheng\nfemale");
			fw.close();
		}catch(IOException e)
		{
			System.out.println(e.getMessage());
		}
		char ch[]=new char[1024];
		int c;
		try{
			FileReader fr=new FileReader(f);
		/*	
			while((c=fr.read())!=-1)
			{
				if(c=='|') System.out.println();
				else System.out.print((char)c);
			}
			System.out.println();
			*/
			/////
			c=fr.read(ch);
			System.out.println(new String(ch,0,c));
			fr.close();
		}catch(IOException e)
		{
			System.out.println(e.getMessage());
		}
	}
}