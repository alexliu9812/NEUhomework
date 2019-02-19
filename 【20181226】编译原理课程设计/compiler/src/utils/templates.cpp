#include "templates.h"

Templates::Templates()
{

}

QString Templates::getAsmTemplate(){
    QString asmb = "section .text\n\tglobal _start:\n_start:\n\nsection .data\n";
    return asmb;
}

QString Templates::getCTemplate(){
    QString c = "#include <stdio.h>\n\nint main(int argc,char *argv[]){\n\t\n\n\treturn 0;\n}";
    return c;
}

QString Templates::getCPPTemplate(){
    QString cplusplus = "#include <iostream>\n\nusing namespace std;\n\nint main(){\n\t\n\n\treturn 0;\n}";
    return cplusplus;
}

QString Templates::getHtmlTemplate(){
    QString html = "<!DOCTYPE html>\n<head lang=\"en-US\">\n\t<meta charset=\"UTF-8\">\n\t<link rel=\"stylesheet\" href=\"\" />"
                   "\n\t<title></title>\n\n\t<script>\n\t\t\n\t</script>\n</head>\n"
                   "<body>\n\t<header>\n\t\t\n\t</header>\n\n</body>\n</html>";
    return html;
}

QString Templates::getJavaTemplate(){
    QString java = "public class name {\n\n\tpublic static void main(String args[]){\n\t\t\n\t}\n\n}";
    return java;
}

QString Templates::getCSSTemplate(){
    QString css = "* {\n\t\n}\n\nhtml {\n\t\n}\n\nbody {\n\tdisplay: block;\n\t\n}\n\nh1 {\n\t\n}\n\np {\n\t\n}\n\na {\n\t\n}\n\nimg {\n\t\n}";
    return css;
}
