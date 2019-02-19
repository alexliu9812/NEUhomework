#include "files.h"
#include "QFile"
#include "QDir"
#include "QTextStream"

using namespace std;

Files::Files()
{
}

// Read file contents
QString Files::read(QString filename){
    QString content = "";
    QFile file(filename);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in(&file);

        while (!in.atEnd()) {
            QString line = in.readLine() + "\n";
            content += line;
        }
    }

    return content;
}

// Write String Content To File
void Files::write(QString filename, QString content){
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream out(&file);
        out << content;
    }
}

// Return Users Home Directory
QString Files::getHomeDir(){
    QString homeDir = QDir::homePath();
    return homeDir;
}

QString Files::getDirectory(QString filepath){
    int lastIndex = filepath.lastIndexOf("/");
    filepath.chop(filepath.length() - lastIndex);

    return filepath;
}
