# Node学习


## npm link
一般情况下，我们安装某个包是全局还是本地，取决于：如果这个包作为工程的一部分时，
安装到本地，如果要在命令行下使用，则安装到全局。

但是有些使用很频繁的包，可能多个工程同时使用，那么每个都安装浪费空间、时间，
如果全局安装，那么是不是所有的工程都能正常的使用呢，可惜的是使用全局模式安装的包，
不能直接通过 `require` 使用，但是 `npm link` 命令可以打破这一限制，
如全局安装了 `express` 模块，然后在工程目录下运行命令：
```
$ npm link express
./node_modules/express -> /usr/local/lib/node_modules/express
```
我们可以在 `node_modules` 下发现一个指向全局的包的符号链接，通过这种方法，
可以将全局包当成本地包来使用了。

## Node.js 调试命令
命令 | 功能
---|---
run | 执行脚本，在第一行暂停
restart  | 重新执行脚本
cont, c  | 继续执行，直到遇到下一个断点
next, n  | 单步执行
step, s  | 单步执行并进入函数
out, o  | 从函数中步出
setBreakpoint(), sb()  | 在当前行设置断点
setBreakpoint(‘f()’), sb(...)  | 在函数f的第一行设置断点
setBreakpoint(‘script.js’, 20), sb(...)  | 在 script.js 的第20行设置断点
clearBreakpoint, cb(...)  | 清除所有断点
backtrace, bt  | 显示当前的调用栈
list(5)  | 显示当前执行到的前后5行代码
watch(expr)  | 把表达式 expr 加入监视列表
unwatch(expr)  | 把表达式 expr 从监视列表移除
watchers  | 显示监视列表中所有的表达式和值
repl  | 在当前上下文打开即时求值环境
kill  | 终止当前执行的脚本
scripts  | 显示当前已加载的所有脚本
version  | 显示 V8 的版本


## Node.js 远程调试
V8 提供的调试功能是基于 TCP 协议的，因此 Node.js 可以轻松地实现远程调试。在命
令行下使用以下两个语句之一可以打开调试服务器：
```
node --debug[=port] script.js
node --debug-brk[=port] script.js
```
`node --debug` 命令选项可以启动调试服务器，默认情况下调试端口是 5858，也可以
使用 `--debug=1234` 指定调试端口为 1234。使用 `--debug` 选项运行脚本时，
脚本会正常执行，但不会暂停，在执行过程中调试客户端可以连接到调试服务器。
如果要求脚本暂停执行等待客户端连接，则应该使用 `--debug-brk` 选项。
这时调试服务器在启动后会立刻暂停执行脚本，等待调试客户端连接。

当调试服务器启动以后，可以用命令行调试工具作为调试客户端连接，例如：
```
//在一个终端中
$ node --debug-brk debug.js
debugger listening on port 5858
//在另一个终端中
$ node debug 127.0.0.1:5858
connecting... ok
debug> n
break in /home/byvoid/debug.js:2
1 var a = 1;
2 var b = 'world';
3 var c = function (x) {
4 console.log('hello ' + x + a);
debug>
```

## node-inspector 调试 Node.js
大部分基于 Node.js 的应用都是运行在浏览器中的，例如强大的调试工具 `node-inspector`。
`node-inspector` 是一个完全基于 Node.js 的开源在线调试工具，提供了强大的调试功能和友好
的用户界面，它的使用方法十分简便。

首先，使用 `npm install -g node-inspector` 命令安装 `node-inspector`，然后在终
端中通过 `node --debug-brk=5858 debug.js` 命令连接你要除错的脚本的调试服务器，
启动 `node-inspector`：
```
$ node-inspector
```
在浏览器中打开 `http://127.0.0.1:8080/debug?port=5858`，即可显示出优雅的 Web 调试工
具。
