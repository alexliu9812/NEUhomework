#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QInputDialog>
#include <QScrollBar>
#include <QTabWidget>
#include <QDesktopServices>

#include "QDebug"

#include "widgets/geisttextedit.h"

GeistTextEdit *currentEditorWidget = NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    numBlocks = 1;
    newNumBlocks = 0;
    outputMode = 0;
    foundPosElement = 0;
    searchTermLen = 0;

    outputModeP = &outputMode;  //  0 = ascii, 1 = hex, 2 = strings

    filename = "";              // Name Of File In Current Tab
    lineColor = QColor(7, 54, 66);

    // UI Setup
    ui->setupUi(this);

    // Style Sheet
    this->setWindowTitle("Cmini");
    ui->menuBar->setStyleSheet("color:white; background-color:#262626; QMenuBar::item {background:black;}");
    ui->centralWidget->layout()->setContentsMargins(0,0,0,0);

    // Disbale manual scrolling for line numbers
    ui->listWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->listWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Hide Search Bar By Default
    ui->findReplaceBar->hide();
    ui->replaceLineEdit->hide();
    ui->replaceButton->hide();
    ui->replaceAllButton->hide();
    ui->replaceLabel->hide();

    // Set Theme From Settings
    theme = settings.value("theme", "monokai").toString();
    if (theme == "monokai"){
        on_actionDark_triggered();
    } else if (theme == "solarized"){
        on_actionSolarized_triggered();
    } else if (theme == "solarizedDark"){
        on_actionSolarized_Dark_triggered();
    } else if (theme == "tomorrow"){
        on_actionTommorrow_triggered();
    } else if (theme == "tomorrowNight"){
        on_actionTommorrow_Night_triggered();
    }

    // Create And Setup Initial Tab
    newTab();
    connect(currentEditorWidget, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    currentEditorWidget->setFocus();
    highlightCurrentLine();

    ui->listWidget->addItem("1");
    QListWidgetItem *item = ui->listWidget->item(numBlocks-1);
    item->setSizeHint(QSize(item->sizeHint().height(), 14));

    // Setup Window Based On User's Settings

    // Set Window Size
    int windowWidth = settings.value("windowWidth", 1000).toInt();
    int windowHeight = settings.value("windowHeight", 600).toInt();
    MainWindow::resize(windowWidth, windowHeight);

    // Show/Hide Overview
    if (!settings.value("showOverview", true).toBool()){
        ui->fileOverview->hide();
    }

    currentDirectory = files.getHomeDir();

    // Open Files From List Saved In Settings
    QStringList openFiles;
    openFiles = settings.value("openFilesList").toStringList();

    if (!openFiles.isEmpty()){
        for (int i = 0; i < openFiles.length(); i++){
            open(openFiles.at(i));
        }
    }

}

MainWindow::~MainWindow()
{
    QRect windowRect = MainWindow::normalGeometry();
    settings.setValue("windowWidth", windowRect.width());
    settings.setValue("windowHeight", windowRect.height());


    // Save List Of Files Open In Editor
    QStringList fileList;
    int numOpenFiles = ui->tabWidget->count();

    for (int i = 0; i < numOpenFiles; i++){
        ui->tabWidget->setCurrentIndex(i);
        fileList.append(currentEditorWidget->getFilepath());
    }
    settings.setValue("openFilesList", fileList);

    delete ui;
}

/*
 *****************************
 *         Tabs              *
 *****************************
*/

// Switch Tab
void MainWindow::on_tabWidget_currentChanged(int index)
{
    if (currentEditorWidget != 0){
        disconnect(currentEditorWidget, SIGNAL(blockCountChanged(int)), this, SLOT(onBlockCountChanged(int)));
        disconnect(currentEditorWidget, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
    }

    currentEditorWidget = qobject_cast<GeistTextEdit *>(ui->tabWidget->widget(index));
    newNumBlocks = currentEditorWidget->document()->blockCount();

    QObject::connect(currentEditorWidget->verticalScrollBar(), SIGNAL(valueChanged(int)), ui->listWidget->verticalScrollBar(), SLOT(setValue(int)));
    QObject::connect(currentEditorWidget->verticalScrollBar(), SIGNAL(valueChanged(int)), this, SLOT(scrollOverview(int)));
    connect(currentEditorWidget, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
    updateLineNums(newNumBlocks);
    connect(currentEditorWidget, SIGNAL(blockCountChanged(int)), this, SLOT(onBlockCountChanged(int)));
    connect(currentEditorWidget, SIGNAL(textChanged()), this, SLOT(onTextChanged()));
    ui->fileOverview->setPlainText(currentEditorWidget->toPlainText());

    filename = currentEditorWidget->getFilepath();

    ui->labelFileType->setText(currentEditorWidget->getFileType().toUpper());
    foundPositions.clear();

    foundPosElement = 0;

    highlightCurrentLine();

}

// Close Tab
void MainWindow::on_tabWidget_tabCloseRequested(int index)
{
    if (ui->tabWidget->count() < 2){
        newTab();
    }

    // delete highlighter
    ui->tabWidget->setCurrentIndex(index);
    currentEditorWidget->setHighlighter(NULL);

        // Set the new current tab
        if (index > 0){
            ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(index - 1));
        } else {
            ui->tabWidget->setCurrentWidget(ui->tabWidget->widget(index + 1));
        }


        // Delete the tab
        delete ui->tabWidget->widget(index);

        // Update filename to correspond to new current tab
        filename = currentEditorWidget->getFilepath();

}

// Create New Tab
void MainWindow::newTab(){
    if (ui->tabWidget->count() < 50){
        ui->tabWidget->addTab(new GeistTextEdit, "New File");
        ui->tabWidget->setCurrentIndex(ui->tabWidget->count() - 1);
        ui->tabWidget->setTabToolTip(ui->tabWidget->currentIndex(), "");
        filename = "";

        setTabWidth(settings.value("tabWidth", 4).toInt());
        currentEditorWidget->setWordWrapMode(QTextOption::NoWrap);
    }
}

void MainWindow::on_actionNew_triggered()
{
    MainWindow::newTab();
}

/*
 *****************************
 *         Files             *
 *****************************
*/

QString MainWindow::getFileType(QString file){
    QStringList dotSplit = file.split(".");
    if (dotSplit.length() > 1)
        return dotSplit.last();
    else
        return "";
}

/*
 *  Open file
 *  Opens in new tab unless current tab is empty
 *  If file does not exist it will be created on save
*/
void MainWindow::open(QString file){

    if (file != ""){

        if (filename != "" || currentEditorWidget->toPlainText() != ""){
            newTab();
        }

        filename = file;
        QString filetype = getFileType(file);
        currentEditorWidget->setPlainText(files.read(filename));

        currentEditorWidget->setFilePath(filename);
        currentEditorWidget->setFileType(filetype);
        currentEditorWidget->setHighlighter(new Highlighter(filetype, theme, currentEditorWidget->document() ));

        if (filename.length() >= 21){
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), filename.right(21));
        } else {
            ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), filename);
        }

        ui->tabWidget->setTabToolTip(ui->tabWidget->currentIndex(), filename);
        ui->labelFileType->setText(filetype.toUpper());

        ui->textBrowser->setText("");
        *outputModeP = 0;
        currentDirectory = files.getDirectory(filename);
    }
}

void MainWindow::on_actionOpen_triggered()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Open File"), currentDirectory, tr("All (*)"));
    open(file);
}

// Save File
void MainWindow::save(){
    if (filename == "" || *outputModeP != 0){
        on_actionSave_as_triggered();
    } else {
        files.write(filename, currentEditorWidget->toPlainText());
        ui->textBrowser->setText("Saved");
    }
}

void MainWindow::on_actionSave_triggered()
{
    MainWindow::save();
}

void MainWindow::on_actionSave_as_triggered()
{
    filename = QFileDialog::getSaveFileName(this, tr("Save As"), currentDirectory, tr("All (*)"));
    QString filetype = getFileType(filename);

    if (filename != ""){
        files.write(filename, currentEditorWidget->toPlainText());

        currentEditorWidget->setFilePath(filename);
        currentEditorWidget->setFileType(filetype);
        currentEditorWidget->setHighlighter(new Highlighter(filetype, theme, currentEditorWidget->document() ));

        ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), filename.right(21));
        ui->tabWidget->setTabToolTip(ui->tabWidget->currentIndex(), filename);
        ui->labelFileType->setText(filetype.toUpper());

        ui->textBrowser->setText("Saved");
       }
}

/*
 *****************************
 *         Searching         *
 *****************************
*/

// Toggle Find Bar
void MainWindow::on_actionFind_triggered()
{
    if (ui->findReplaceBar->isHidden()){
        ui->findReplaceBar->show();
        ui->findLineEdit->setFocus();
    } else {
        if (ui->replaceLineEdit->isHidden()){
            ui->findReplaceBar->hide();
            currentEditorWidget->setFocus();
        } else {
            ui->replaceLineEdit->hide();
            ui->replaceButton->hide();
            ui->replaceAllButton->hide();
            ui->replaceLabel->hide();
        }

    }
}

// Find All Instances Of Search Term And Cycles Through Them
void MainWindow::on_findLineEdit_returnPressed()
{
    if (ui->findLineEdit->text() == currentSearchTerm){
            findNext();

    } else {
        QString searchTerm = ui->findLineEdit->text();
        currentSearchTerm = searchTerm;
        searchTermLen = searchTerm.length();

        if (searchTermLen > 0){
            QString found = QString::fromStdString(searcher.findAll(searchTerm.toStdString(), currentEditorWidget->toPlainText().toStdString()));
            foundPositions = found.split(" ");
            foundPosElement = 0;
            selectText(foundPositions[foundPosElement].toInt(), searchTermLen);
        }
    }
}
void MainWindow::on_findLineEdit_textChanged(const QString &arg1)
{
    on_findLineEdit_returnPressed();
}

// Selects Text Given the Position Of the First Char And It's Length
void MainWindow::selectText(int pos, int len){
    if (foundPositions.length() > 1){
        QTextCursor cur = currentEditorWidget->textCursor();
        cur.setPosition(pos , QTextCursor::MoveAnchor);
        cur.setPosition(pos + len, QTextCursor::KeepAnchor);
        currentEditorWidget->setTextCursor(cur);
        ui->listWidget->verticalScrollBar()->setValue(currentEditorWidget->verticalScrollBar()->value());
    }
}

//  Find Next Instance Of Search Term
void MainWindow::findNext(){
    if (ui->findLineEdit->text() == currentSearchTerm){

        if (foundPositions.length() > 1){

            if (foundPosElement < foundPositions.length() - 2){
                foundPosElement++;
            } else {
                foundPosElement = 0;
            }

            selectText(foundPositions[foundPosElement].toInt(), searchTermLen);
        }

    } else {
        on_findLineEdit_returnPressed();
    }
}

// Find Previous Instance Of Search Term
void MainWindow::findPrev(){

    if (foundPositions.length() > 1){

        if (foundPosElement > 0){
            foundPosElement--;
        } else {
            foundPosElement = foundPositions.length() - 2;
        }

        selectText(foundPositions[foundPosElement].toInt(), searchTermLen);
    }
}

void MainWindow::on_findButton_clicked()
{
    findNext();
    currentEditorWidget->setFocus();
}

void MainWindow::on_actionFind_Next_triggered()
{
    findNext();
}

void MainWindow::on_findPrevButton_clicked()
{
    findPrev();
    currentEditorWidget->setFocus();
}

void MainWindow::on_actionFind_Previous_triggered()
{
    findPrev();
}

//  Toggle Replace Bar
void MainWindow::on_actionReplace_triggered()
{
    if (ui->findReplaceBar->isHidden()){
        ui->findReplaceBar->show();
        ui->findLineEdit->setFocus();
        if (ui->replaceLineEdit->isHidden()){
            ui->replaceLineEdit->show();
            ui->replaceButton->show();
            ui->replaceAllButton->show();
            ui->replaceLabel->show();
        }
    } else {

        if (ui->replaceLineEdit->isHidden()){
            ui->replaceLineEdit->show();
            ui->replaceButton->show();
            ui->replaceAllButton->show();
            ui->replaceLabel->show();
        } else {
            ui->replaceLineEdit->hide();
            ui->replaceButton->hide();
            ui->replaceAllButton->hide();
            ui->findReplaceBar->hide();
            ui->replaceLabel->hide();
            currentEditorWidget->setFocus();
        }

    }
}

// Replace Currently Selected Found Instance Of Text To Be Replaced
void MainWindow::on_replaceButton_clicked()
{
    QTextCursor cur = currentEditorWidget->textCursor();

    if (cur.selectedText() != ""){
        cur.removeSelectedText();
        cur.insertText(ui->replaceLineEdit->text());
    }

    currentEditorWidget->setTextCursor(cur);
    QString searchTerm = ui->findLineEdit->text();
    currentSearchTerm = searchTerm;
    searchTermLen = searchTerm.length();

    if (searchTermLen > 0){
        QString found = QString::fromStdString(searcher.findAll(searchTerm.toStdString(), currentEditorWidget->toPlainText().toStdString()));
        foundPositions = found.split(" ");
        foundPosElement = 0;
        selectText(foundPositions[foundPosElement].toInt(), searchTermLen);
    }
}
void MainWindow::on_replaceLineEdit_returnPressed()
{
    MainWindow::on_replaceButton_clicked();
}

//  Replace All Found Instances Of Text To Be Replaced
void MainWindow::on_replaceAllButton_clicked()
{
    QString searchTerm = ui->findLineEdit->text();
    currentSearchTerm = searchTerm;
    do {
        searchTermLen = searchTerm.length();

        if (searchTermLen > 0){
            QString found = QString::fromStdString(searcher.findAll(searchTerm.toStdString(), currentEditorWidget->toPlainText().toStdString()));
            foundPositions = found.split(" ");
            foundPosElement = 0;
            selectText(foundPositions[foundPosElement].toInt(), searchTermLen);
        }

        QTextCursor cur = currentEditorWidget->textCursor();

        if (cur.selectedText() != ""){
            cur.removeSelectedText();
            cur.insertText(ui->replaceLineEdit->text());
        }

        currentEditorWidget->setTextCursor(cur);

    } while (foundPositions.length() > 1);
}

// Go To Line Number
void MainWindow::on_actionGoTo_triggered()
{
    bool ok = 0;

    if (int line = QInputDialog::getText(this, tr("Enter"),tr("Go to:"), QLineEdit::Normal,"", &ok).toInt()){
        QTextCursor cur = currentEditorWidget->textCursor();
        cur.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);
        cur.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, line-1);
        currentEditorWidget->setTextCursor(cur);
        ui->listWidget->verticalScrollBar()->setValue(currentEditorWidget->verticalScrollBar()->value());
    }
}

/*
 *****************************
 *         Editing           *
 *****************************
*/

//  Undo/Redo
void MainWindow::on_actionUndo_triggered()
{
    currentEditorWidget->undo();
}
void MainWindow::on_actionRedo_triggered()
{
    currentEditorWidget->redo();
}

//  Delete Line Where Cusor Currently Resides
void MainWindow::on_actionDelete_line_triggered()
{
    currentEditorWidget->deleteLine();
}

//  Delete Word Where Cusor Currently Resides
void MainWindow::on_actionRemove_word_triggered()
{
    currentEditorWidget->deleteWord();
}

/*
 *  Toggles currently selected line(s) between commented out and uncommented
 *  If no text is selected then it selects the current line
*/
void MainWindow::on_actionToggle_comment_triggered()
{
    currentEditorWidget->toggleComment();
}

// Join Lines
void MainWindow::on_actionJoin_Lines_triggered()
{
    currentEditorWidget->joinLines();
}

// Swap Line Up
void MainWindow::on_actionMove_Line_Up_triggered()
{
    currentEditorWidget->swapLineUp();
}

// Swap Line Down
void MainWindow::on_actionSwap_line_down_triggered()
{
    currentEditorWidget->swapLineDown();
}

/*
 *****************************
 *         Tools             *
 *****************************
*/

// Strips All Nonprintable ascii Characters From Contents Of Current Tab
void MainWindow::on_actionStrings_triggered()
{
    if (*outputModeP != 1){
        *outputModeP = 2;
        currentEditorWidget->setPlainText( QString::fromStdString(conversion.getStrings(currentEditorWidget->toPlainText().toStdString())) );
    }
}

//  Converts ascii Values Of Content Of Current Tab Into Hexidecimal
void MainWindow::on_actionHex_triggered()
{
    if (*outputModeP == 0 || *outputModeP == 2){
        *outputModeP = 1;
        currentEditorWidget->setPlainText( QString::fromStdString( conversion.hex(currentEditorWidget->toPlainText().toStdString() ) ) );
    }
}

//  Converts Hexidecimal Values Of Content Of Current Tab Into ascii
void MainWindow::on_actionAscii_triggered()
{
    if (*outputModeP == 1){
        *outputModeP = 0;
        currentEditorWidget->setPlainText( QString::fromStdString( conversion.ascii(currentEditorWidget->toPlainText().toStdString() ) ) );
    }
}



/*
 *****************************
 *           Run             *
 *****************************
*/
void MainWindow::on_actionRunIn16Bit_triggered(){

    QString batName = "doit.bat";
    QString batContent;
    QString pathNow = QDir::currentPath();
    QString filenameplus = filename + ".asm";
    QString toPath = pathNow + "/Masm/out.asm";
    QString copyCommand;

    QFile topathfileasm(toPath);
    QString objfile = pathNow +"/Masm/out.obj";
    QFile topathfileobj(objfile);
    QString exefile = pathNow +"/Masm/out.exe";

    //清理之前文件
    QFile topathfileexe(exefile);
    if(topathfileasm.exists())
    {
        topathfileasm.remove();
    }
    if(topathfileobj.exists())
    {
        topathfileobj.remove();
    }
    if(topathfileexe.exists())
    {
        topathfileexe.remove();
    }
    QFile fileplus(filenameplus);
    if(fileplus.exists())
    {
        fileplus.remove();
    }
    QFile filebat(batName);
    if(filebat.exists())
    {
        filebat.remove();
    }

    batContent = "";

    //进入真正的批处理过程
    if(filename.contains("11ScopeNesting",Qt::CaseSensitive))
    {

        QString repla = "Compiler.exe " + filename + "\n\r";
        QString real = repla;
        repla.replace("11ScopeNesting","llScopeNesting");
        //Compile
        batContent = real;
        //batContent = repla;
        //Copy
        repla = filenameplus;
        repla.replace("11ScopeNesting","llScopeNesting");
        copyCommand = "copy " + repla + " " + toPath;
        copyCommand.replace("/","\\\\");
        batContent += copyCommand + "\r\n";

        //masm,link and run
        //batContent += "DOSBox.exe -noconsole -c \"mount c ./Masm\" -c \"c:\" -c \"masm out.asm;\" -c \"link out.obj;\" -c \"out.exe\"";
        QString run1 = "DOSBox.exe -noconsole -c ";
        QString run2 = "\"";
        QString run3 = "mount c ./Masm";
        QString run4 = " -c ";
        QString run5 = "c:";
        QString run6 = "masm out.asm;";
        QString run7 = "link out.obj;";
        QString run8 = "out.exe";
        QString runit = run1 + run2 + run3 + run2 + run4 + run2 + run5 + run2 + run4 + run2 + run6 + run2 + run4 + run2 + run7 + run2 +run4+run2+run8+run2;
        batContent += runit;
    }
    else {
        //Compile
        batContent = "Compiler.exe " + filename + "\n\r";
        //Copy
        copyCommand = "copy " + filenameplus + " " + toPath;
        copyCommand.replace("/","\\\\");
        batContent += copyCommand + "\r\n";

        //masm,link and run
        //batContent += "DOSBox.exe -noconsole -c \"mount c ./Masm\" -c \"c:\" -c \"masm out.asm;\" -c \"link out.obj;\" -c \"out.exe\"";
        QString run1 = "DOSBox.exe -noconsole -c ";
        QString run2 = "\"";
        QString run3 = "mount c ./Masm";
        QString run4 = " -c ";
        QString run5 = "c:";
        QString run6 = "masm out.asm;";
        QString run7 = "link out.obj;";
        QString run8 = "out.exe";
        QString runit = run1 + run2 + run3 + run2 + run4 + run2 + run5 + run2 + run4 + run2 + run6 + run2 + run4 + run2 + run7 + run2 +run4+run2+run8+run2;
        batContent += runit;
    }
    //QMessageBox::information(this,"DOSBox",batContent,QMessageBox::Close);
    QFile file(batName);
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    //写入内容,这里需要转码，否则报错。
    QByteArray str = batContent.toUtf8();
    //写入QByteArray格式字符串
    file.write(str);
    file.close();

    if (file.exists())
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(batName));
    }
/*
    //QProcess process(this);
    //process.startDetached("cmd.exe");
    //process.write ("ipconfig\n\r");
    //QProcess process(this);
    //process.start("cmd.exe");
    //process.write ("ipconfig\n\r");
    //process.write ("exit\n\r");
    //process.waitForFinished();
    //process.close();
    //process.waitForFinished();
    /*
    QProcess process(this);
    process.execute("cmd.exe");
    process.write("Compiler.exe");
    char* compileCommandLine;
    QByteArray ccl = filename.toLatin1();
    compileCommandLine = ccl.data();
    process.write(compileCommandLine);
    //QProcess::startDetached("cmd.exe");
    //QProcess::write("Compiler.exe");
    //QProcess::write("Compiler.exe");

    QString pathNow = QDir::currentPath();
    QString program0 = "cmd";
    QStringList arguments0;
    arguments0<<"";
    QProcess *myProcess0 = new QProcess(this);
    myProcess0->start(program0,arguments0);
    myProcess0->waitForStarted();
    myProcess0->waitForFinished();

    //Compile
    QString program1 = "Compiler.exe";
    QStringList arguments1;
    arguments1<<filename;
    QProcess *myProcess1 = new QProcess(this);
    myProcess1->start(program1,arguments1);
    myProcess1->waitForStarted();
    myProcess1->waitForFinished();


    //cp
    QString filenameplus = filename + ".asm";
    QString toPath = pathNow + "/Masm/out.asm";
    QFile toFile(toPath);
    if(toFile.exists()){
        toFile.remove();
    }
    if(QFile::copy(filenameplus,toPath)){
        qDebug()<<QStringLiteral("Copy Successful!");
    }

    //masm,link and run
    QString program2 = "DOSBox.exe";
    QStringList arguments2;
    arguments2<<"-noconsole"<<"-c"<<"mount c ./Masm"<<"-c"<<"c:"<<"-c"<<"masm out.asm;"<<"-c"<<"link out.obj;"<<"-c"<<"out.exe";
    QProcess *myProcess2 = new QProcess(this);
    myProcess2->start(program2,arguments2);
    myProcess2->waitForStarted();
    myProcess2->waitForFinished();
    //QString dosboxCommand = "DOSBox -noconsole -c 'mount c ./Masm' -c 'c:' -c 'masm out.asm;' -c 'link out.obj;' -c 'out.exe'";
    */
}


void MainWindow::on_actionRunIn64Bit_triggered(){
    QString notes = "The compiler that generates 64-bit assembly language is on the way, very soon!";
    QMessageBox::information(this, tr("x64 assembly"), notes,QMessageBox::Close);
}



/*
 *****************************
 *     Look Other File       *
 *****************************
*/

void MainWindow::on_actionQuaternary_File_triggered(){
    QFile file("quat.dat");
    if (file.exists())
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile("quat.dat"));
    }
}

void MainWindow::on_actionASM_File_triggered(){
    QString asmFileName = filename + ".asm";
    QFile file(asmFileName);
    if (file.exists())
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(asmFileName));
    }

}

void MainWindow::on_actionSymbol_Table_triggered(){
    QString symFile = "synbl.csv";
    QFile file(symFile);
    if (file.exists())
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(symFile));
    }
}


void MainWindow::on_actionToken_Table_triggered(){
    QString tokenFile = "Token.csv";
    QFile file(tokenFile);
    if (file.exists())
    {
        QDesktopServices::openUrl(QUrl::fromLocalFile(tokenFile));
    }
}





/*
 *****************************
 *         Templates         *
 *****************************
*/

bool MainWindow::confirmApplyTemplate(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Template", "Are you sure you want to apply a template?\nAll unsaved work will be lost.", QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes){
        return true;
    } else {
        return false;
    }
}

// If current tab contents are not empty, prompt user for confirmation to apply template

void MainWindow::on_actionAsm_triggered(){
    if (currentEditorWidget->toPlainText() == ""){
        currentEditorWidget->setPlainText(templates.getAsmTemplate());
    } else {
        if (confirmApplyTemplate()){
            currentEditorWidget->setPlainText(templates.getAsmTemplate());
        }
    }
}

void MainWindow::on_actionC_triggered(){
    if (currentEditorWidget->toPlainText() == ""){
        currentEditorWidget->setPlainText(templates.getCTemplate());
    } else {
        if (confirmApplyTemplate()){
            currentEditorWidget->setPlainText(templates.getCTemplate());
        }
    }
}

void MainWindow::on_actionCpluspluss_triggered(){
    if (currentEditorWidget->toPlainText() == ""){
        currentEditorWidget->setPlainText(templates.getCPPTemplate());
    } else {
        if (confirmApplyTemplate()){
            currentEditorWidget->setPlainText(templates.getCPPTemplate());
        }
    }
}

void MainWindow::on_actionHtml_triggered(){
    if (currentEditorWidget->toPlainText() == ""){
        currentEditorWidget->setPlainText(templates.getHtmlTemplate());
    } else {
        if (confirmApplyTemplate()){
            currentEditorWidget->setPlainText(templates.getHtmlTemplate());
        }
    }
}

void MainWindow::on_actionJava_triggered(){
    if (currentEditorWidget->toPlainText() == ""){
        currentEditorWidget->setPlainText(templates.getJavaTemplate());
    } else {
        if (confirmApplyTemplate()){
            currentEditorWidget->setPlainText(templates.getJavaTemplate());
        }
    }
}

void MainWindow::on_actionCss_triggered(){
    if (currentEditorWidget->toPlainText() == ""){
        currentEditorWidget->setPlainText(templates.getCSSTemplate());
    } else {
        if (confirmApplyTemplate()){
            currentEditorWidget->setPlainText(templates.getCSSTemplate());
        }
    }
}

/*
 *****************************
 *         View              *
 *****************************
*/

// Toggle FullScreen
void MainWindow::on_actionFullScreen_triggered()
{
    if (MainWindow::isFullScreen())
    {
        MainWindow::showNormal();
    } else {
        MainWindow::showFullScreen();
    }
}

// Toggle File Overview
void MainWindow::on_actionOverview_triggered()
{
    if (ui->fileOverview->isHidden()){
        ui->fileOverview->show();
        settings.setValue("showOverview", true);
    } else {
        ui->fileOverview->hide();
        settings.setValue("showOverview", false);
    }
}

// Toggle Menubar
void MainWindow::on_actionMenubar_triggered()
{
    if (ui->menuBar->height() > 0){
        ui->menuBar->setMaximumHeight(0);
    } else {
        ui->menuBar->setMaximumHeight(100);
    }
}

/*
 *****************************
 *         Themes            *
 *****************************
*/

void MainWindow::setMainWindowStyle(QString backgroundColor, QString lineColor){
    QString stylesheet = "QMenu {"
                "background-color: rgb(48, 47, 54);"
                "color:white;"
                "selection-background-color: #404f4f;"
                "border: 1px solid #404f4f;"
                "border-radius: 3px 3px 3px 3px;"
             "}"
             "QMenuBar::item {"
                "background:#262626;"
             "}"
             "QMenuBar::item:selected {"
                "background: #232629;"
             "}"
             "QMessageBox {"
                "color:white;"
             "}"
             "QLineEdit {"
                "border: 1px solid #676767;"
                "border-radius: 5px 5px 5px 5px;"
             "}"
             "QScrollBar::sub-page:vertical {"
                "background: " +  backgroundColor + ";"
             "}"
             "QScrollBar::add-page:vertical {"
                "background: " +  backgroundColor + ";"
             "}"
             "QScrollBar::sub-page:horizonal {"
                "background: " +  backgroundColor +";"
             "}"
             "QScrollBar::add-page:horizontal {"
                "background: " +  backgroundColor +";"
             "}"
             "QScrollBar:vertical{"
                "background: white;"
                "width:12px;margin: 0px 0px 0px 0px;"
             "}"
             "QScrollBar::handle:vertical {"
                "background:" + lineColor  +";"
                "border: 2px solid " +  backgroundColor  +";"
                "border-radius: 5px 5px 5px 5px;"
                "min-height: 30px;"
             "}"
             "QScrollBar:horizontal{"
                "background: white;"
                "height:12px;"
                "margin: 0px 0px 0px 0px;"
             "}"
             "QScrollBar::handle:horizontal {"
                "background:" + lineColor  +";"
             "border: 2px solid " +  backgroundColor  +";"
             "border-radius: 5px 5px 5px 5px;"
             "min-height: 30px;"
             "}";

    MainWindow::setStyleSheet(stylesheet);

}

void MainWindow::setTabWidgetStyle(QString foregroundColor, QString backgroundColor){
    QString stylesheet = "QPlainTextEdit {"
                "background-color: " +  backgroundColor  +";"
                "color:" + foregroundColor  +";"
                "border: 0px;"
                "padding-left: 1px;"
                "selection-background-color: #404f4f;"
                "font-family: \"Anonymous Pro\";"
                "font-size:11pt;"
             "}"
             "QScrollBar:vertical{"
                "background: " +  backgroundColor  +";"
             "}"
             "QScrollBar:horizontal{"
                "background: " +  backgroundColor  +";"
             "}"
             "QTabBar::tab:selected{"
                "color: white;"
                "border-bottom: 3px solid #2F4F4F;"
             "}"
             "QTabBar::tab {"
                "height: 22px; width: 160px;"
                "color: #676767;"
                "font-size:9pt;"
                "margin: 0 -2px;"
                "padding: 1px 5px;"
                "background-color: #262626;"
                "border-bottom: 3px solid #212121;"
             "}";
   ui->tabWidget->setStyleSheet(stylesheet);

}

void MainWindow::setLineNumStyle(QString lineColor, QString foregroundColor){
    QString stylesheet = "background-color: " + lineColor  +";"
            "margin-top: 30px;"
            "padding-left: 5px;"
            "padding-right: 1px;"
            "color: " + foregroundColor  +";"
            "border: none;"
            "font: 11pt \"Anonymous Pro\";";
    ui->listWidget->setStyleSheet(stylesheet);
}

void MainWindow::setOverViewStyle(QString lineColor, QString foregroundColor){
    QString stylesheet = "font-family: \"Anonymous Pro\";"
            "font-size: 1pt;"
            "color:" + foregroundColor  +";"
            "margin-top: 28px;"
            "background-color:" + lineColor  +";"
            "border: 0px;";
    ui->fileOverview->setStyleSheet(stylesheet);
}

void MainWindow::updateHighlighterTheme(){
    int current = ui->tabWidget->currentIndex();
    int numOpenTabs = ui->tabWidget->count();
    for(int i = 0; i < numOpenTabs; i++){
        ui->tabWidget->setCurrentIndex(i);
        currentEditorWidget->setHighlighterTheme(theme);
    }
    ui->tabWidget->setCurrentIndex(current);
}

void MainWindow::on_actionDark_triggered()
{
    theme = "monokai";
    settings.setValue("theme", "monokai");
    QString fgc = "#e0e0e0";
    QString bgc = "#272822";
    QString lc = "#32332c";

    setMainWindowStyle(bgc, lc);
    setTabWidgetStyle(fgc, bgc);
    setLineNumStyle(lc, fgc);
    setOverViewStyle(lc, fgc);

    updateHighlighterTheme();

    lineColor = QColor(50, 51, 44);
    highlightCurrentLine();

}

void MainWindow::on_actionSolarized_triggered()
{
    theme = "solarized";
    settings.setValue("theme", "solarized");

    QString fgc = "#839496";
    QString bgc = "#fdf6e3";
    QString lc = "#eee7d5";

    setMainWindowStyle(bgc, lc);
    setTabWidgetStyle(fgc, bgc);
    setLineNumStyle(lc, fgc);
    setOverViewStyle(lc, fgc);

    updateHighlighterTheme();

    lineColor = QColor(238, 232, 213);
    highlightCurrentLine();
}

void MainWindow::on_actionSolarized_Dark_triggered()
{
    theme = "solarizedDark";
    settings.setValue("theme", "solarizedDark");
    QString fgc = "#839496";
    QString bgc = "#002b36";
    QString lc = "#073642";

    setMainWindowStyle(bgc, lc);
    setTabWidgetStyle(fgc, bgc);
    setLineNumStyle(lc, fgc);
    setOverViewStyle(lc, fgc);

    updateHighlighterTheme();

    lineColor = QColor(7, 54, 66);
    highlightCurrentLine();
}

void MainWindow::on_actionTommorrow_triggered()
{
    theme = "tomorrow";
    settings.setValue("theme", "tomorrow");
    QString fgc = "#4d4d4c";
    QString bgc = "#ffffff";
    QString lc = "#efefef";

    setMainWindowStyle(bgc, lc);
    setTabWidgetStyle(fgc, bgc);
    setLineNumStyle(lc, fgc);
    setOverViewStyle(lc, fgc);

    updateHighlighterTheme();

    lineColor = QColor(237, 237, 237);
    highlightCurrentLine();
}

void MainWindow::on_actionTommorrow_Night_triggered()
{
    theme = "tomorrowNight";
    settings.setValue("theme", "tomorrowNight");
    QString fgc = "#c5c8c6";
    QString bgc = "#1d1f21";
    QString lc = "#282a2e";

    setMainWindowStyle(bgc, lc);
    setTabWidgetStyle(fgc, bgc);
    setLineNumStyle(lc, fgc);
    setOverViewStyle(lc, fgc);

    updateHighlighterTheme();

    lineColor = QColor(40, 42, 46);
    highlightCurrentLine();
}

/*
 *****************************
 *         Window            *
 *****************************
*/

//  Highlight Current Line
void MainWindow::highlightCurrentLine(){
   if (currentEditorWidget != NULL){
       QList<QTextEdit::ExtraSelection> extraSelections;

       QTextEdit::ExtraSelection selections;
       selections.format.setBackground(lineColor);
       selections.format.setProperty(QTextFormat::FullWidthSelection, true);
       selections.cursor = currentEditorWidget->textCursor();
       selections.cursor.clearSelection();
       extraSelections.append(selections);

       currentEditorWidget->setExtraSelections(extraSelections);
       ui->listWidget->verticalScrollBar()->setValue(currentEditorWidget->verticalScrollBar()->value());
   }
}

//  Update Line Numbers
void MainWindow::updateLineNums(int newBlockCount){

    if (newBlockCount > numBlocks){
        //  Add Line Numbers
        while (numBlocks < newBlockCount){
            numBlocks++;
            QString lineNum = QString::number(numBlocks);
            ui->listWidget->addItem(lineNum);
            QListWidgetItem *item = ui->listWidget->item(numBlocks-1);
            item->setSizeHint(QSize(item->sizeHint().height(), 14));
        }

    } else {
        //  Remove Line Numbers
        while (numBlocks > newBlockCount){
            ui->listWidget->takeItem(numBlocks - 1);
            numBlocks--;
        }
    }

    QString numLinesText = QString::number(newBlockCount) + " Lines";
    ui->statusMsgLabel->setText(numLinesText);
}
void MainWindow::onBlockCountChanged(int newBlockCount)
{
    /*  Auto-Indent New Lines   */

    //  If Block Count Only Increased By One
    if (newBlockCount == numBlocks + 1){

        QString data = currentEditorWidget->toPlainText();
        int cursorPosition = currentEditorWidget->textCursor().position();

        // If Beginning Cursor At Beginning Of New Line
        if (data.mid(cursorPosition-1, 1) == "\n"){
            int pos;

            // Get Position Of Start Of New Line
            for (pos=cursorPosition-2; pos>=0; pos--){

                if (data.mid(pos, 1) == "\n") {
                    break;
                    }
                }

                //  For Each Tab Char At Beggining Of Previous Line: Add Tab To New Line
                while (data.mid(pos + 1, 1) == "\t"){
                    currentEditorWidget->textCursor().insertText("\t");
                    pos++;
                }
         }
    }

    // Update Line Numbers
    MainWindow::updateLineNums(newBlockCount);
}

//  Text Changed
void MainWindow::onTextChanged(){

    ui->textBrowser->setText("");
    ui->fileOverview->setPlainText(currentEditorWidget->toPlainText());
    currentSearchTerm = "";
}

// Sync Overview Scrolling With Editor Scrolling
void MainWindow::scrollOverview(int scrollValue){
    ui->fileOverview->verticalScrollBar()->setValue(scrollValue * 2.5);
}

//  Close Program
void MainWindow::on_actionExit_triggered()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Test", "Quit?", QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
      QApplication::quit();
    } else {

    }
}

// Close All Tabs
void MainWindow::on_actionClose_All_triggered()
{
    while (ui->tabWidget->count() > 1){
        on_tabWidget_tabCloseRequested(0);
    }
    on_tabWidget_tabCloseRequested(0);
}

//  Display About Info
void MainWindow::on_actionAbout_triggered()
{
    QString licence = "About Cmini Compiler\n"
                      "A compiler for a subset of C\n"
                      "@Author:刘学渊/戚子强/王润哲\n"
                      "@BuildTime: 12/23/2018\n"
                      "@Version: 0.24Beta\n";
    QMessageBox::information(this, tr("About Cmini"), licence,QMessageBox::Close);
}

// Set Tab Stop Width
void MainWindow::setTabWidth(int width){
    QFont font;
    font.setFamily("Anonymous Pro");
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);
    font.setPointSize(10);
    QFontMetrics metrics(font);

    int current = ui->tabWidget->currentIndex();

    for(int i = 0; i < ui->tabWidget->count(); i++){
        ui->tabWidget->setCurrentIndex(i);
        currentEditorWidget->setTabStopWidth(width * metrics.width(' ') );
    }

    ui->tabWidget->setCurrentIndex(current);

}

void MainWindow::on_action8_triggered()
{
    settings.setValue("tabWidth", 8);
    setTabWidth(8);
}

void MainWindow::on_action4_triggered()
{
    settings.setValue("tabWidth", 4);
    setTabWidth(4);
}

void MainWindow::on_action2_triggered()
{
    settings.setValue("tabWidth", 2);
    setTabWidth(2);
}

void MainWindow::openWith(QString file){
    open(file);
}
