#ifndef SOFTKEYBOARD_H
#define SOFTKEYBOARD_H


#include <QWidget>
#include <qboxlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <googlepinyinmanager.h>

class SoftKeyboard : public QWidget
{
    Q_OBJECT
public:
    explicit SoftKeyboard(QLineEdit *lineEdit,QWidget *parent = nullptr);

    void initStyleSheet();//初始化可选样式表，用于不同的皮肤展示
    void initSecondArea();//初始化第二部分 输入显示区域
    void initThirdArea();//初始化第三部分 按键区域

    void initNumberLetterBtn();//初始化数字字母按键，分配空间，连接信号与槽
    void initSpecialBtn();//初始化特殊功能按键，诸如大小写切换，删除按键等
    void initKeyboardStyle(int num);//初始化键盘样式

    void setLetterLow();//设置小写字母显示
    void setLetterUpper();//设置大写字母显示
    void setSymbolsEN();//设置符号（英文状态）
    void setSymbolsCH();//设置符号（中文状态）

    void hideInputDiaplayArea();//隐藏输入显示区域

    void displayCandidateWord(int page);//显示指定页的候选词 page从1开始

    void matchChinese(QString pinyin);//根据输入的拼音匹配中文


private:
    GooglePinyinManager *googlePinyin = new GooglePinyinManager();
    //按键以及整个键盘的样式
    QStringList keyAndCandidateAreaStyle;//按键和候选词widget区域样式
    QStringList commonKeyStyle;//普通按键的样式
    QStringList specialKeyStyle;//特殊按键的样式

    int pageCount;//候选词当前页
    bool isENInput;//中英文输入模式
    bool isLetterInput;//数字字母或符号输入模式
    bool isLetterLower;//大小写模式
    int skinNum;//标记当前皮肤编号

    QTimer *delTimer;//实现长按删除键 删除定时
    QVBoxLayout *globalVLayout;
    QLineEdit *lineEdit;//编辑区

    QWidget *inputDisplayArea;//键盘的输入显示区域
    QLineEdit *candidateLetter;//中文输入时对应的字母显示
    QWidget *candidateWordArea;//候选词区域 在上面布局中有六个候选词和翻页按钮
    QPushButton *candidateWordBtn[6];//中文输入时的候选词
    QPushButton *prePageBtn;//前一页
    QPushButton *nextPageBtn;//后一页
    QWidget *keyBoardArea;//键盘的按键区域
    QPushButton *numberLetterBtn[36];//10个数字按键，26个字母按键,同时可以显示符号
    QPushButton *upperOrLowerBtn;//大小写转换按键
    QPushButton *deleteBtn;//删除按键
    QPushButton *skinBtn;//切换皮肤
    QPushButton *letterOrSymbolBtn;//数字字母与符号切换按键
    QPushButton *commaBtn;//逗号按键
    QPushButton *spaceBtn;//空格按键
    QPushButton *periodBtn;//句号按键
    QPushButton *chOrEnBtn;//中英文切换按键
    QPushButton *enterBtn;//回车按键
    QList<QString> tempChineseList;//待选择的汉字

signals:
    void sendText(QString text);//以信号的形式将输入文本发出去

public slots:

    void candidateLetterChangedSlot(QString text);//候选字母改变响应槽
    void candidateWordBtnSlot();//候选词被点击的响应槽
    void candidateWordPrePageSlot();//候选词向前翻页
    void candidateWordNextPageSlot();//候选词向后翻页
    void numberLetterBtnSlot();//数字字母(符号)按键被点击的响应槽
    void changeUpperLowerSlot();//大小写切换 也可以切换数字字母与字符界面
    void closeDelTimer();//关闭连续删除的定时器,并设置焦点
    void deleteTextSlot();//删除输入内容
    void changeSkinSlot();//换肤
    void changeLetterSymbolSlot();//切换符号界面 中英文输入下的部分符号不同
    void spaceSlot();//空格响应槽
    void changeChEnSlot();//中英文切换
    void enterSlot();// 回车
    void okBtnSlot();//软键盘退出，同时发出当前输入文本的信号
    void quitBtnSlot();//软键盘退出，不发出输入的文本信号
};

#endif // SOFTKEYBOARD_H
