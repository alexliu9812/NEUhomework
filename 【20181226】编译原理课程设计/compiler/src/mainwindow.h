#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <highlighter.h>
#include <QShortcut>
#include "QSettings"
#include <QPlainTextEdit>

#include "files.h"
#include "search.h"
#include "utils/conversion.h"
#include "utils/templates.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void openWith(QString);

private slots:
    void save();

    void open(QString file);

    void newTab();

    void selectText(int pos,int len);

    void highlightCurrentLine();

    void updateHighlighterTheme();

    void setTabWidth(int width);

    void updateLineNums(int newBlockCount);

    void scrollOverview(int scrollValue);

    void setMainWindowStyle(QString backgroundColor, QString lineColor);

    void setTabWidgetStyle(QString foregroundColor, QString backgroundColor);

    void setLineNumStyle(QString lineColor, QString foregroundColor);

    void setOverViewStyle(QString lineColor, QString foregroundColor);

    QString getFileType(QString file);

    void on_actionOpen_triggered();

    void on_actionNew_triggered();

    void on_actionSave_triggered();

    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_actionExit_triggered();

    void on_actionSave_as_triggered();

    void on_actionFind_triggered();

    void on_actionHex_triggered();

    void on_actionAscii_triggered();

    void on_actionStrings_triggered();

    void on_findLineEdit_returnPressed();

    void on_actionAbout_triggered();

    void on_tabWidget_tabCloseRequested(int index);

    void on_tabWidget_currentChanged(int index);

    void onBlockCountChanged(int newBlockCount);

    void onTextChanged();

    void on_actionFullScreen_triggered();

    void on_actionGoTo_triggered();

    void on_actionAsm_triggered();

    void on_actionC_triggered();

    void on_actionCpluspluss_triggered();

    void on_actionHtml_triggered();

    void on_actionJava_triggered();

    bool confirmApplyTemplate();

    void on_actionCss_triggered();

    void on_findButton_clicked();

    void on_findPrevButton_clicked();

    void on_actionFind_Next_triggered();

    void findNext();

    void findPrev();

    void on_actionFind_Previous_triggered();

    void on_actionReplace_triggered();

    void on_replaceButton_clicked();

    void on_actionDelete_line_triggered();

    void on_actionRemove_word_triggered();

    void on_replaceAllButton_clicked();

    void on_replaceLineEdit_returnPressed();

    void on_findLineEdit_textChanged(const QString &arg1);

    void on_actionToggle_comment_triggered();

    void on_actionOverview_triggered();

    void on_actionDark_triggered();

    void on_actionSolarized_Dark_triggered();

    void on_actionJoin_Lines_triggered();

    void on_actionMove_Line_Up_triggered();

    void on_actionSwap_line_down_triggered();

    void on_actionMenubar_triggered();

    void on_actionSolarized_triggered();

    void on_action8_triggered();

    void on_action4_triggered();

    void on_action2_triggered();

    void on_actionClose_All_triggered();

    void on_actionTommorrow_triggered();

    void on_actionTommorrow_Night_triggered();

    void on_actionRunIn16Bit_triggered();

    void on_actionRunIn64Bit_triggered();

    void on_actionToken_Table_triggered();

    void on_actionSymbol_Table_triggered();

    void on_actionQuaternary_File_triggered();

    void on_actionASM_File_triggered();

private:
    Ui::MainWindow *ui;
    Highlighter *highlighter;
    QShortcut *shortcut;
    QSettings settings;

    Conversion conversion;
    Files files;
    Search searcher;
    Templates templates;

    int numBlocks;
    int newNumBlocks;
    int outputMode;
    int foundPosElement;
    int searchTermLen;
    int *outputModeP;

    QString filename;
    QString theme;
    QString currentDirectory;
    QString currentSearchTerm;  // Current Value Of Search Term
    QStringList foundPositions; // Positions Of Substrings Matching Search Term
    QColor lineColor;

};

#endif // MAINWINDOW_H
