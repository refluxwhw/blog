# QT4 安装问题
linux下安装QT4时，configure 遇到错误：
错误1：
> ```
> Basic XLib functionality test failed!
>  You might need to modify the include and library search paths by editing
>  QMAKE_INCDIR_X11 and QMAKE_LIBDIR_X11 in /home/whw/work/qt-everywhere-opensource-src-4.8.4/mkspecs/linux-g++-64.
> ```

原因：缺少库 libX11 的开发包

解决办法：
```
$ sudo apt-get install libX11-dev libXext-dev libXtst-dev
```

错误2：
> ```
> Project ERROR: Package gstreamer-app-0.10 not found
> ```

解决办法：
```
$ sudo apt-get install libgstreamer0.10-dev libgstreamer-plugins-base0.10-dev
```


错误3：
> ```
> g++: error: unrecognized command line option ‘-fuse-ld=gold’
>

这是一个
