# socket.io

## WebSocket 工作机制
**工作流程**：浏览器通过 JavaScript 向服务器发出建立 WebSocket 的连接请求，
连接建立后，客户端和服务端就可以通过 TCP 通信。

为了建立一个 WebSocket 连接，客户端浏览器首先要向服务器发起一个 HTTP 请求，
这个请求和通常的 HTTP 请求不同，包含了一些附加头信息，其中附加头信息
"Upgrade: WebSocket"表明这是一个申请协议升级的 HTTP 请求，服务器端解析这些附加的头信息然后产生应答信息返回给客户端，客户端和服务器端的 WebSocket 连接就建立起来了，双方就可以通过这个连接通道自由的传递信息，并且这个连接会持续存在直到客户端或者服务器端的某一方主动的关闭连接。

协议规范：一个典型的websocket发起请求到响应请求的例子如下
```
客户端到服务端：
GET / HTTP/1.1
Connection:Upgrade
Host:127.0.0.1:8088
Origin:null
Sec-WebSocket-Extensions:x-webkit-deflate-frame
Sec-WebSocket-Key:puVOuWb7rel6z2AVZBKnfw==
Sec-WebSocket-Version:13
Upgrade:websocket

服务端到客户端：
HTTP/1.1 101 Switching Protocols
Connection:Upgrade
Server:beetle websocket server
Upgrade:WebSocket
Date:Mon, 26 Nov 2013 23:42:44 GMT
Access-Control-Allow-Credentials:true
Access-Control-Allow-Headers:content-type
Sec-WebSocket-Accept:FCKgUr8c7OsDsLFeJTWrJw6WO8Q=
```


### END
