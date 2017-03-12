#include "Path.h"

#ifndef __unix__
#  define CHAR_DELIMITER ';'
#  define CHAR_SEPARATE  '\\'
#else
#  define CHAR_DELIMITER ':'
#  define CHAR_SEPARATE  '/'
#endif

typedef struct {
    string device;   // 卷标
    string dirname;  // 目录
    string basename; // 文件名
    string extname;  // 后缀名
} PathObj_t;

/**
 * @brief 将一个路径分割成四个部分，如果没有，就为空
 * win:
 * c:\\testdir\\dira\\my.txt
 * ┌──────┬─────────────────┬──────┬──────┐
 * │ root │ dir             │ name │ ext  │
 * ├──────┼─────────────────┼──────┼──────┤
 * │ c:\\ │ testdir\\dira\\ │ my   │ .txt │
 * └──────┴─────────────────┴──────┴──────┘
 * linux:
 * /root/testdir/dira/my.txt
 * ┌──────┬────────────────────┬──────┬──────┐
 * │ root │ dir                │ name │ ext  │
 * ├──────┼────────────────────┼──────┼──────┤
 * │ /    │ root/testdir/dira/ │ my   │ .txt │
 * └──────┴────────────────────┴──────┴──────┘
 * @param path[string] 要求编码格式为标准string
 */
PathObj_t splitPath(const string& path)
{
    PathObj_t obj;
    int pathLen = path.length();
    pathLen = pathLen > 3 ? pathLen + 1 : 4;
    char *buf = new char[pathLen];
    memset(buf, 0, pathLen);
    memcpy(buf, path.c_str(), path.size());

    // 将目录分割成两部分，[卷标,部分]
    // 卷标只能是 字母+冒号
    string device;
    string tail;
    if ( ((buf[0] >= 'a' && buf[0] <= 'z') || (buf[0] >='A' && buf[0] <='Z'))
         && buf[1] == ':' )
    {
        device = string(buf, 2);
        if (buf[2] == CHAR_SEPARATE)
        {
            device.append(CHAR_SEPARATE, 1);
        }
    }
    tail = string(buf + device.length());
    delete [] buf;
    buf = NULL;

    //
    // 从文件路径末尾开始，反向找文件名称，文件扩展名，剩下的为路径
    const char* p = tail.c_str();
    for (int i = tail.length() - 1; i >= 0; i--)
    {
        if (CHAR_SEPARATE == p[i])
        {
            obj.basename = string(tail.c_str() + i, tail.size() - i);
            p = obj.basename.c_str();
            for (int i = obj.basename.size() - 1; i >= 0; i--)
            {
                if (p[i] == '.')
                {
                    obj.extname = string(p + i, obj.basename.size() - i);
                    break;
                }
            }
            break;
        }
    }

    if (obj.basename.size() == 0)
    {
        obj.basename = tail;
        p = obj.basename.c_str();
        for (int i = obj.basename.size() - 1; i >= 0; i--)
        {
            if (p[i] == '.')
            {
                obj.extname = string(p + i, obj.basename.size() - i);
                break;
            }
        }
    }

    obj.dirname = string(tail.c_str(), tail.size() - obj.basename.size());

    return obj;
}

////////////////////////////////////////////////////////////////////////////////

namespace Util {

    char Path::delimiter()
    {
        return CHAR_DELIMITER;
    }

    char Path::sep()
    {
        return CHAR_SEPARATE;
    }

    string Path::basename(const string &path, string ext)
    {
        return "";
    }

    string Path::dirname(const string &path)
    {
        return "";
    }

    string Path::extname(const string &path)
    {
        return "";
    }

    bool Path::isAbsolute(const string &path)
    {
        return true;
    }

    string Path::join(const vector<string> &paths)
    {
        return "";
    }

    string Path::resolve(const std::vector<string> &paths)
    {
        return "";
    }

    string Path::normalize(const string &path)
    {
        return "";
    }

}

