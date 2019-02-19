#ifndef READER_H
#define READER_H

#include "QString"

class Files
{
public:
    Files();
    QString read(QString filename);
    void write(QString filename, QString content);
    QString getHomeDir();
    void openFileManager(QString dir);
    QString getDirectory(QString filepath);
};

#endif // READER_H
