# CSS 样式入门

+ 布局属性： 影响网页上元素位置的属性(如边距、填充、对齐等)
+ 格式化属性： 影响网页中元素视觉显示的属性

## 布局属性

### display
描述元素相对于其他元素如何显示，可取值有：
1. block : 元素显示在下一行,作为一个段落
1. list-item : 元素显示在下一行,前面有列元素标记(项目符号)
1. inline : 元素显示在当前段落
1. none :　元素隐藏不显示

### 尺寸单位
1. in 英寸
1. cm 厘米
1. mm 毫米
1. px 像素
1. pt 点

## 格式化属性

### border 边框
- border-width : 边框的宽度
- border-color : 边框颜色
- border-style : 边框样式,可取值有:
 - solid : 实线
 - double : 双实线
 - dashed : 虚线
 - dotted : 点线
 - groove : 沟线
 - ridge : 脊线
 - inset : 内陷边框
 - outset : 外凸边框
 - none : 无边框
- border-left/right/top/bottom : 边框的左/右/上/下边
- border ： 边框的所有边

### color 文本颜色(前景色)
### background-color 背景色
### 字体与对齐
- text-align : 文本对齐方式
- text-indent : 文本缩进
- font-family : 字体集
- font-size : 字体大小
- font-style : 字体样式(普通normal/italic斜体)
- font-weight : 字体的粗细(细thin/medium中等/bold粗)

### line-height 文本高度
### text-decoration 可用于上传链接的下划线(属性设置为none)

## 外部样式 内部样式 和 内联样式
通过 `<link>` 标签设置属性 `type="text/css"` 以及 `href="css source"` 引用得到外部的样式文件,这称为外部样式

在某些情况下,需要指定只用于某一个网页的样式,可以将样式单放在标签`<style>`和`</style>`内,直接包含在 html 文档中,以这种方式使用的样式单必须出现在 html 文档的 head 中. --- 这种样式单称为 **`内部样式单`**

在某些情况下,可能需要将样式用于特定的元素,可以直接在元素属性中增加 `style` 属性设置其样式,这称为 **`内联样式`**

## 文本块和列表

### 在页面上对齐文本

### HTML 列表
1. 有序列表 `<ol><li></li></ol>`: 在每个列表项目前面有数字或字母的缩进列表
1. 无序列表 `<ul><li></li></ul>`: 在每个列表项目前面有一个项目符号或者其他符号的缩进列表
1. 定义列表 `<dl><dt></dt></dl>`: `<dt>`标签定义项目，`<dd>`标签描述项目

```
<dl>
  <dt>aa<dt>
  <dd>这是aa的描述</dd>
  <dt>bb<dt>
  <dd>这是bb的描述</dd>
</dl>
```


## 字体
一些字体格式标签：
1. `<b>` 粗体
1. `<i>` 斜体

一些CSS样式:
```
font-weight: 设置字体的粗细,可取值包括: 普通normal/粗体bold(bolder)/lighter
font-style: 设置字体样式,可取值包括: 普通normal/斜体italic(oblique)
```


```
<small> 小字体
<big> 大字体
<sup> 上标文本
<sub> 下标文本
<strike> 删除文本
<em>	把文本定义为强调的内容。
<strong>	把文本定义为语气更强的强调的内容。
<dfn>	定义一个定义项目。
<code>	定义计算机代码文本。
<samp>	定义样本文本。
<kbd>	定义键盘文本。它表示文本是从键盘上键入的。它经常用在与计算机相关的文档或手册中。
<var>	定义变量。
<cite>	定义引用。可使用该标签对参考文献的引用进行定义，比如书籍或杂志的标题。
```

### 常用转义字符

字符 | 数字代码 | 代码名称 | 说明
--|--
`"` | `&#34;` | `&quot;` | 引号
`&` | `&#38;` | `&amp;` | 符号与
`<` | `&#60;` | `&lt;`  | 小于
`>` | `&#62;` | `&gt;`  | 大于


## 表格`<table>`
- `<tr>` 标签创建表格的一行；
- `<td>` 标签创建表格的一个单元格
- `<th>` 标签，与`<td>`标签类似，创建一个单元格，但表示单元格是表头的一部分，大多数web浏览器将`<th>`单元格中的文本内容居中对齐并显示为粗体。

### 表格中的对齐与跨域
```
text-align: 设置文本水平对齐方式
vertical-align: 设置文本垂直对齐方式
colspan: 单元格列跨域
rowspan: 单元格行跨域
cellspacing: 表格单元格之间的间距，单位为像素
style:
  background-color:颜色 表格与没有背景颜色的单元格的背景颜色
  backgroundimage:url(图像url) 表格与没有背景图片的单元格的背景图案(如果指定了背景颜色，背景颜色将透过图像的透明区域显示出来)
```



## 使用外部和内部链接
1. 链接到锚的使用方法
1. 在自己的网站上的页面之间链接的方法
1. 链接到外部内容的方法
1. 链接到一个email地址的方法
1. 在新的浏览器窗口中查看链接的方法
1. 用css为链接添加样式的方法

#### 属性 href
指定所要链接的页面的地址

> 关于使用相对地址还是绝对地址，有一个通用规则，那就是在链接存储在一起的文件时，应用
相对地址，链接到其他地方---其他计算机、硬盘或internet的其他网站上的文件时，应用绝对地址

### 使用链接锚在页面中链接
`<a>`标签是负责web上超链接的标签，来源于`anchor(锚)`一词。
```
<a href="#top">Top</a>
```
`#`符号表示top指向当前文档中的命名锚接点，而不是单独的页面，当用户单击 Top 时，web浏览器
以显示以`id="top"`的标签开头的部分。

> 通过`<a>`标签的id属性指定的锚名称必须以数字或字母开头，所以如果想要为锚的ID编号，
一定要以文本开头，如img1，img2等，而不要只用数字，因为纯数字的ID在浏览器中能正常工作，
但是不能被验证为有效的 XHTML 代码。

### 在web内容间链接
### 链接到外部web内容
链接到外部网站时，必须包含内容的完整地址，完整的地址包括域名之前的 `http://`，然后是文件
的完整路径名，如一个html文件或图像等等。
```
<a href="http://www.google.com/">Google</a>
```

### 链接到一个 email 地址
```
<a href="mailto:username@domain.com">Send email</a>
```

```
<a href="mailto:author@domain.com?subject=My Question&body=where are you from?">Mail to author@domain.com</a>
```
点击后会创建一个以 `author@domain.com` 为收件人，`My Question`为主题，`where are you from?` 为信息正文的 E-mail。

### 在新浏览器窗口里打开链接
使用 `<a>` 标签的 `target` 属性完成。该属性指定在何处打开链接。

如果在一个 `<a>` 标签内包含一个 target 属性，浏览器将会载入和显示用这个标签的 href 属性
命名的、名称与这个目标吻合的框架或者窗口中的文档。如果这个指定名称或 id 的框架或者窗口不
存在，浏览器将打开一个新的窗口，给这个窗口一个指定的标记，然后将新的文档载入那个窗口。从
此以后，超链接文档就可以指向这个新的窗口。
```
<h3>Table of Contents</h3>
<ul>
  <li><a href="pref.html" target="view_window">Preface</a></li>
  <li><a href="chap1.html" target="view_window">Chapter 1</a></li>
  <li><a href="chap2.html" target="view_window">Chapter 2</a></li>
  <li><a href="chap3.html" target="view_window">Chapter 3</a></li>
</ul>
```
当用户第一次选择内容列表中的某个链接时，浏览器将打开一个新的窗口，将它标记为
"view_window"，然后在其中显示希望显示的文档内容。如果用户从这个内容列表中选择另一个链接，
且这个 "view_window" 仍处于打开状态，浏览器就会再次将选定的文档载入那个窗口，取代刚才的
那些文档。

在整个过程中，这个包含了内容列表的窗口是用户可以访问的。通过单击窗口中的一个连接，可使另
一个窗口的内容发生变化。

#### **在框架中打开窗口**
不用打开一个完整的浏览器窗口，使用 target 更通常的方法是在一个 `<frameset>` 显示中将超
链接内容定向到一个或者多个框架中。可以将这个内容列表放入一个带有两个框架的文档的其中一个
框架中，并用这个相邻的框架来显示选定的文档：
```
<frameset cols="100,*">
  <frame src="toc.html">
  <frame src="pref.html" name="view_frame">
</frameset>
```

#### **特殊的目标**
有 4 个保留的目标名称用作特殊的文档重定向操作：

- `_blank`:浏览器总在一个新打开、未命名的窗口中载入目标文档。
- `_self`: 这个目标的值对所有没有指定目标的 `<a>` 标签是默认目标，它使得目标文档载入并
显示在相同的框架或者窗口中作为源文档。这个目标是多余且不必要的，除非和文档标题 `<base>`
标签中的target 属性一起使用。
- `_parent`:这个目标使得文档载入父窗口或者包含来超链接引用的框架的框架集。如果这个引用
是在窗口或者在顶级框架中，那么它与目标 `_self` 等效。
- `_top`:这个目标使得文档载入包含这个超链接的窗口，用 `_top` 目标将会清除所有被包含的
框架并将文档载入整个浏览器窗口。
> 提示：这些 target 的所有 4 个值都以下划线开始。任何其他用一个下划线作为开头的窗口或者
目标都会被浏览器忽略，因此，不要将下划线作为文档中定义的任何框架 name 或 id 的第一个字符。

### 使用CSS设置超链接样式
`<a>`标签常用的伪类有：
1. `link`: 描述未被访问过的超链接的样式
1. `visited`: 描述访问过，并且存在于浏览器内存的超链接样式
1. `havor`: 描述用户的鼠标悬停下的超链接样式
1. `active`: 描述被点击但未被释放时的超链接的样式
> 伪类(pseudo class)：是一种描述应用到某些情况的元素样式的类，比如用户与该元素的交互状态


## 颜色
### 颜色在web上的工作方式


## 创建用于web上的图像
## 在web网页中使用图像
### `img`标签，
1. `src`属性: 指定图像文件源地址
1. `alt`属性: 指定关于图像的描述性文本,是在图像没有成功加载时的替代文字;另外seo对图片
意思的判断主要是依靠 alt 属性
1. `title`属性: 对图片的进一步说明,图片加载后,鼠标停放在图片上,会以小框(工具提示)方式显示
1. `width`属性: 指定图像宽度
1. `height`属性: 指定图像高度
> Flicker图像库服务,可以为每个图像提供一个URL

### **垂直对齐图像**

设置CSS:
1. `vertical-align:text-top`: 图像顶部和同一行中最高的图像或文本的顶部对齐
1. `vertical-align:text-bootom`: 图像底部与同一行中最低的图像或文本的底部对齐
1. `vertical-align:top`: 与同一行中的最高的图像的顶部对齐
1. `vertical-align:bottom`: 与同一行中最低的图像的底部对齐
1. `vertical-align:middle`: 图像的中心与同一行中其他内容的中心对齐
1. `vertical-align:baseline`: 图像的底部与文本的基线对齐

### 使用背景图像
创建背景的基本样式属性：
1. `background-color`: 指定元素的背景色彩
1. `background-image`: 指定元素的背景图片，值为 url
1. `background-repeat`: 指定图像的重复方式，可以是水平或垂直方向，默认情况下，背景将
在水平和垂直方向都重复。其他选项为：
 - `repeat(与默认值相同)`
 - `repeat-x(水平)`
 - `repeat-y(垂直)`
 - `no-repeat(不重复，图像仅出现一次)`
1. `background-position`: 指定图像开始相对于其容器的位置选项包括
 - `top-left`
 - `top-center`
 - `top-right`
 - `center-left`
 - `center-center`
 - `center-right`
 - `bottom-left`
 - `bottom-center`
 - `bottom-right`
 - 具体的像素和百分比位置

### 图像映射
p148
###### end
