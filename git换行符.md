# GIT应用相关

## git使用中遇到的换行符问题总结

### 问题描述
项目组现在用git做版本控制，使用中遇到不同平台下换行符不同造成的问题，windows下的
换行符为crlf，linux和MAX OS 下换行符是 lf。linux和MAX OS就按说明设置为
`core.autocrlf input`（貌似是默认值），windows设置为`core.autocrlf true`。可是有
时候还是会遇到换行符的问题。review的时候就会发现有的commit的变化是所有行都被删除重建。

** git中设置core.autocrlf **

假如你正在Windows上写程序，又或者你正在和其他人合作，他们在Windows上编程，而你却在
其他系统上，在这些情况下，你可能会遇到行尾结束符问题。这是因为Windows使用回车和换行
两个字符来结束一行，而Mac和Linux只使用换行一个字符。虽然这是小问题，但它会极大地扰
乱跨平台协作。

Git可以在你提交时自动地把行结束符CRLF转换成LF，而在签出代码时把LF转换成CRLF。
用 `core.autocrlf` 来打开此项功能，如果是在Windows系统上，把它设置成`true`，
这样当签出代码时，LF会被转换成CRLF：
```
$ git config --global core.autocrlf true
```
Linux或Mac系统使用LF作为行结束符，因此你不想 Git 在签出文件时进行自动的转换；
当一个以CRLF为行结束符的文件不小心被引入时你肯定想进行修正，把 `core.autocrlf`
设置成input来告诉 Git 在提交时把CRLF转换成LF，签出时不转换：
```
$ git config --global core.autocrlf input
```
这样会在Windows系统上的签出文件中保留CRLF，会在Mac和Linux系统上，包括仓库中保留LF。

如果你是Windows程序员，且正在开发仅运行在Windows上的项目，可以设置`false`取消此功能，
把回车符记录在库中：
```
$ git config --global core.autocrlf false
```
