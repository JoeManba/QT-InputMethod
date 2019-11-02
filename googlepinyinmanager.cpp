#include "googlepinyinmanager.h"
#include <QDateTime>
#include <QSettings>
#include <QDebug>
#include "include/head/pinyinime.h"

using namespace ime_pinyin;

GooglePinyinManager::GooglePinyinManager()
{
    ChineseModel.clear();

            QSettings setter("./dict/pinyinEx.ini", QSettings::IniFormat);

        lstEN = setter.value("pyEn", lstEN).toStringList();
    if (lstEN.size() <= 1)
    {
        qDebug() << "Can't load pyEn!";
        return;
    }

    bool ret = im_open_decoder("./dict/dict_pinyin.dat", "./dict/user.dat");
    if (!ret)
    {
        qDebug() << "open dict faild";
        return;
    }
    im_init_user_dictionary("./dict/user.dat");
}

GooglePinyinManager::~GooglePinyinManager()
{
    lstEN.clear();
    ChineseModel.clear();
    im_close_decoder();
}

void GooglePinyinManager::SearchCN(const QString &gemfield)
{
    ChineseModel.clear();
    if (gemfield == "")
    {
        return;
    }

    im_reset_search();
    int num = im_search(gemfield.toLatin1().data(), gemfield.size());

    const uint16 *pos;
    int size = im_get_spl_start_pos(pos);

    QString py = gemfield;
    for (int i = size-1; i > 0; i--)
    {
        py.insert(pos[i], "'");
    }
    py.replace("''", "'");

    if (num > 100)
    {
        num = 100;
    }
    char16 buf[32]= {0};
    for (int i = 0; i < num; i++)
    {
        im_get_candidate(i, buf, 32);
        ChineseModel << QString::fromUtf16(buf);
    }
}

void GooglePinyinManager::BinarySearchEN(const QString &gemfield)
{
    int min = 0;
    int max = lstEN.size();
    int idx = max / 2;

    while (true)
    {
        if (lstEN[idx].startsWith(gemfield, Qt::CaseInsensitive))
            break;
        if (max == min + 1 || max <= min || max == idx + 1 || max == idx || min == idx + 1 || min == idx )
            break;
        if (lstEN[idx].toLower() > gemfield)
            max = idx;
        else
            min = idx;
        idx = (max + min) / 2;
    }
    do {
        if (--idx < 0)
            break;
    } while(lstEN[idx].startsWith(gemfield, Qt::CaseInsensitive));

    ++idx;
    int cnt = 0;
    while(++cnt < 100)
    {
        if (idx >= lstEN.size())
            break;
        if (lstEN[idx].startsWith(gemfield, Qt::CaseInsensitive))
            ChineseModel.append(lstEN[idx]);
        else
            break;
        idx++;
    }
}

void GooglePinyinManager::Matching(const QString &gemfield, bool isEn)
{
    ChineseModel.clear();
    if (isEn)
    {
        BinarySearchEN(gemfield);
    }
    else
    {
        SearchCN(gemfield);
    }
}
