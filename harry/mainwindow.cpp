#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "iostream"
#include "fstream"
#include "cstdio"
#include "QString"
#include "string"
#include"QTime"
#include "vector"
#include "QMessageBox"
#include<time.h>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

vector<SearchInfo> searchInfo;
const char *books[8] = {
    "J.K. Rowling - HP 4 - Harry Potter and the Goblet of Fire.txt",
    "J.K. Rowling - Quidditch Through the Ages.txt",
    "J.K. Rowling - HP 6 - Harry Potter and the Half-Blood Prince.txt",
    "J.K. Rowling - HP 3 - Harry Potter and the Prisoner of Azkaban.txt",
    "J.K. Rowling - HP 0 - Harry Potter Prequel.txt",
    "HP7--Harry_Potter_and_the_Deathly_Hallows_Book_7_.txt",
    "HP2--Harry_Potter_and_the_Chamber_of_Secrets_Book_2_.txt",
    "J.K. Rowling - The Tales of Beedle the Bard.txt"
};

// 点击查找按钮
void MainWindow::on_Button1_clicked()
{
    //显示时间
    QTime startTime1=QTime::currentTime();

    clock_t startTime,endTime;
    startTime = clock();
    ui->textBrowser->clear(); //清空textBrower
    searchInfo.clear(); //清空上一次查找的缓存
    ui->textBrowser->append("序号 人名/地名 页码 章节 书名");
    QString text = ui->name->text(); //获取输入文本
    int number = 0;
    /*/setlocale(LC_ALL, "zh-CN");              //设置好语言，系统默认是英文，而里面可能有中文
    ifstream in("BOOK\\" + book + ".txt");     //拼接路径，代码和txt放仪器
    string line, con;                        //存储按行读取到的内容
    */

    for(int i = 0; i < 8; i++)
    {
        fstream file;
        file.open(books[i], ios::in);
        if (!file.is_open()) {
            cerr << "文件打开失败" << endl;
        }
        char name[100];
        char sequence[1024] = {0};
        string chapterdaxie = "CHAPTER";
        string chapterxiaoxie = "Chapter";
        int now1chapter = 0;
        int now1page = 0;

        //cin<<name；输入查找的人名/地名
        strcpy(name, text.toStdString().c_str()); //转换用来查找的人名/地名
        while (file.getline(sequence, sizeof(sequence))) {
            if(sequence[0] == 0 && (sequence[1] == '\r' || sequence[1] == '\n')) continue;
            try {
                //是章节的情况是前七个字大写写是“CHAPTER”
                if (sequence[0] == chapterdaxie[0] && sequence[1] == chapterdaxie[1] && sequence[2] == chapterdaxie[2] &&
                    sequence[3] == chapterdaxie[3] && sequence[4] == chapterdaxie[4] && sequence[5] == chapterdaxie[5] && sequence[6] == chapterdaxie[6])
                {
                    now1chapter++;
                    continue;
                }
                //是章节的情况是前七个字大写写是“CHAPTER”
                else if (sequence[3] == chapterdaxie[0] && sequence[4] == chapterdaxie[1] && sequence[5] == chapterdaxie[2] &&
                           sequence[6] == chapterdaxie[3] && sequence[7] == chapterdaxie[4] && sequence[8] == chapterdaxie[5] && sequence[9] == chapterdaxie[6])
                {
                    now1chapter++;
                    //用于跳过开头utf-8标识
                    continue;
                //是章节的情况是前七个字母小写是“chapter”
                }
                else if(sequence[0] == chapterxiaoxie[0] && sequence[1] == chapterxiaoxie[1] && sequence[2] == chapterxiaoxie[2] &&
                           sequence[3] == chapterxiaoxie[3] && sequence[4] == chapterxiaoxie[4] && sequence[5] == chapterxiaoxie[5] && sequence[6] == chapterxiaoxie[6])
                {
                    now1chapter++;
                    continue;
                }
                //是章节的情况是前七个字母小写是“chapter”
                else if (sequence[3] == chapterxiaoxie[0] && sequence[4] == chapterxiaoxie[1] && sequence[5] == chapterxiaoxie[2] &&
                           sequence[6] == chapterxiaoxie[3] && sequence[7] == chapterxiaoxie[4] && sequence[8] == chapterxiaoxie[5] && sequence[9] == chapterxiaoxie[6])
                {
                    now1chapter++;
                    //用于跳过开头utf-8标识
                    continue;
                }
                else if (stoi(string(sequence)) && stoi(string(sequence)) == now1page + 1)
                { //判断是页码,且一整行都是数字
                    now1page++;
                    continue;
                }
            }  catch (...) {
                //do nothing
            }
            //开始在文字框输出序号，人名/地名，页码，章节，书名
            char *buf_point = sequence;
            while (*buf_point != 0) {
                if (*buf_point == *name) {
                    int POINT = 0;
                    int SIGNAL = 1;
                    while(*(name+POINT) != 0){
                        if(*(name+POINT) != *(buf_point+POINT)){
                            SIGNAL = 0;
                            break;
                        }
                        POINT++;
                    }
                    if (SIGNAL == 0) {
                        buf_point++;
                        continue;
                    } else {
                        /*cout << "  "
                             << i + 1 << "       "
                             << info << "         "
                             << s[i].page << "         "
                             << s[i].chapter << "         "
                             << s[i].bookName << "      " << endl;
                    */
                        searchInfo.push_back(SearchInfo(i, now1page, now1chapter, string(sequence)));
                        ui->textBrowser->append(QString::fromStdString("<a href='" + to_string(++number) + "'>" + to_string(number) + "</a>"+ "&nbsp;&nbsp;&nbsp;&nbsp;" + name + "&nbsp;&nbsp;&nbsp;&nbsp;" + to_string(now1page) + "&nbsp;&nbsp;&nbsp;&nbsp;" + to_string(now1chapter) + "&nbsp;&nbsp;&nbsp;&nbsp;"+ string(books[i])));
                    }
                }
                buf_point++;
            }
        }
        endTime = clock();
        //ui->textBrowser->append(QString::fromStdString("Totle Time"+((endTime- startTime) /                                                                           CLOCKS_PER_SEC+"s")));
        file.close();
    }
    //显示时间
    QTime stopTime1=QTime::currentTime();
    int qqqq1=startTime1.msecsTo(stopTime1);
    ui->textBrowser->append("\nTotle Time :"+QString::fromStdString(to_string(qqqq1))+"ms");
    ui->textBrowser->append("\nTotle Time :"+QString::fromStdString(to_string(qqqq1/1000))+"s");
}


SearchInfo::SearchInfo(int BOOKNAME, int PAGE, int CHAPTER, std::string LINE):BOOKNAME(BOOKNAME),PAGE(PAGE), CHAPTER(CHAPTER), LINE(LINE)
{

}

SearchInfo::~SearchInfo(){}

string SearchInfo::getLine()
{
    return this->LINE;
}

void MainWindow::on_Button_2_clicked()
{
    //在右框显示出操作2的操作时间
    QTime startTime2=QTime::currentTime();

    QString text1 = ui->serialnumber->text();//在右边的line框获取查询的text
    int number = 0;
    try {
        number = stoi(text1.toStdString());
    }  catch (...) {
        QMessageBox::warning(this,tr("warning"),tr("编号形式不正确"));
       return;
    }
    number-=1;
    if(number <0)
    {
        QMessageBox::warning(this,tr("warning"),tr("编号过小"));
        return;
    }
    if(number >= int(searchInfo.size()))
    {
        QMessageBox::warning(this,tr("warning"),tr("编号过大"));
        return;
    }
    //显示时间
    QTime stopTime2=QTime::currentTime();
    int qqqq2=startTime2.msecsTo(stopTime2);
    ui->textBrowser_2->clear();
    ui->textBrowser_2->append("\n所在段落："+QString::fromStdString(searchInfo[number].getLine()));
    ui->textBrowser_2->append("\nTotle Time :"+QString::fromStdString(to_string(qqqq2))+"ms");
    ui->textBrowser_2->append("\nTotle Time :"+QString::fromStdString(to_string(qqqq2/1000))+"s");
    ui->textBrowser_2->append("\n若要继续显示结果，请清空上框继续输入序号点击“Button2”或点击左框中的序号蓝色标注链接");
}


void MainWindow::on_textBrowser_anchorClicked(const QUrl &arg1)
{
     QTime startTime3=QTime::currentTime();
    ui->textBrowser->setOpenExternalLinks(false);
    ui->textBrowser->setOpenLinks(false);
    QString clickedText = arg1.toString();
    int number = stoi(clickedText.toStdString()) - 1;
    QTime stopTime3=QTime::currentTime();
    int qqqq3=startTime3.msecsTo(stopTime3);
    ui->textBrowser_2->clear();
    ui->textBrowser_2->append("\n所在段落："+QString::fromStdString(searchInfo[number].getLine()));
    ui->textBrowser_2->append("\nTotle Time :"+QString::fromStdString(to_string(qqqq3))+"ms");
    ui->textBrowser_2->append("\nTotle Time :"+QString::fromStdString(to_string(qqqq3/1000))+"s");
    ui->textBrowser_2->append("\n若要继续显示结果，请清空上框继续输入序号点击“Button2”或点击左框中的序号蓝色标注链接");
}

