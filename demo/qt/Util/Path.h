#ifndef PATH_H
#define PATH_H

#include <iostream>
#include <vector>
using namespace std;

namespace Util {
    namespace Path {
        /**
         * @brief delimiter 定界符号
         * @return
         */
        static char delimiter();
        /**
         * @brief sep 分隔符
         * @return
         */
        static char sep();

        /**
         * @brief basename
         * @param path
         * @param ext
         * @return
         */
        static string basename(const string& path, string ext= "");
        static string dirname(const string& path);
        static string extname(const string& path);
        static bool isAbsolute(const string& path);
        static string join(const vector<string>& paths);
        static string resolve(const std::vector<string>& paths);
        static string normalize(const string& path);
    }
}



#endif // PATH_H
