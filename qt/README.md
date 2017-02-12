# QT编程

## QPainter
Qt的绘图系统允许使用相同的API在屏幕和打印设备上进行绘制。整个绘图系统基于`QPainter`，
`QPainterDevice`和`QPaintEngine`三个类。

`QPainter`用来执行绘制的操作；`QPaintDevice`是一个二维空间的抽象，这个二维空间可以由
`QPainter`在上面进行绘制；`QPaintEngine`提供了画笔`painter`在不同的设备上进行绘制的
统一的接口。`QPaintEngine`类用在`QPainter`和`QPaintDevice`之间，并且通常对开发人员
是透明的，除非你需要自定义一个设备，这时候你就必须重新定义`QPaintEngine`了。


## Event
事件(event)是由系统或者Qt本身在不同的时刻发出的。当用户按下鼠标，敲下键盘，或者是窗口
需要重新绘制的时候，都会发出一个相应的事件。一些事件是在对用户操作做出响应的时候发出，
如键盘事件等；另一些事件则是由系统自动发出，如计时器事件。

Qt的事件很容易和信号槽混淆。这里简单的说明一下，signal由具体对象发出，然后会马上交给
由connect函数连接的slot进行处理；而对于事件，Qt使用一个事件队列对所有发出的事件进行维
护，当新的事件产生时，会被追加到事件队列的尾部，前一个事件完成后，取出后面的事件进行处
理。但是，必要的时候，Qt的事件也是可以不进入事件队列，而是直接处理的。并且，事件还可以
使用“事件过滤器”进行过滤。总的来说，如果我们使用组件，我们关心的是信号槽；如果我们自定
义组件，我们关心的是事件。因为我们可以通过事件来改变组件的默认操作。比如，如果我们要自
定义一个QPushButton，那么我们就需要重写它的鼠标点击事件和键盘处理事件，并且在恰当的时
候发出clicked()信号。

```C++
class Q_WIDGETS_EXPORT QWidget : public QObject, public QPaintDevice
{
    // ...

protected:
    // Event handlers
    bool event(QEvent*) Q_DECL_OVERRIDE;
    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void mouseDoubleClickEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
#ifndef QT_NO_WHEELEVENT
    virtual void wheelEvent(QWheelEvent*);
#endif
    virtual void keyPressEvent(QKeyEvent*);
    virtual void keyReleaseEvent(QKeyEvent*);
    virtual void focusInEvent(QFocusEvent*);
    virtual void focusOutEvent(QFocusEvent*);
    virtual void enterEvent(QEvent*);
    virtual void leaveEvent(QEvent*);
    virtual void paintEvent(QPaintEvent*);
    virtual void moveEvent(QMoveEvent*);
    virtual void resizeEvent(QResizeEvent*);
    virtual void closeEvent(QCloseEvent*);
#ifndef QT_NO_CONTEXTMENU
    virtual void contextMenuEvent(QContextMenuEvent*);
#endif
#ifndef QT_NO_TABLETEVENT
    virtual void tabletEvent(QTabletEvent*);
#endif
#ifndef QT_NO_ACTION
    virtual void actionEvent(QActionEvent*);
#endif

#ifndef QT_NO_DRAGANDDROP
    virtual void dragEnterEvent(QDragEnterEvent*);
    virtual void dragMoveEvent(QDragMoveEvent*);
    virtual void dragLeaveEvent(QDragLeaveEvent*);
    virtual void dropEvent(QDropEvent*);
#endif

    virtual void showEvent(QShowEvent*);
    virtual void hideEvent(QHideEvent*);
    virtual bool nativeEvent(const QByteArray &eventType, void* message,
      long*result);

    // Misc. protected functions
    virtual void changeEvent(QEvent*);

    // ...
}
```

我们可以把Qt的事件传递看成链状：如果子类没有处理这个事件，就会继续向其他类传递。其实，
Qt的事件对象都有一个`accept()`函数和`ignore()`函数。正如它们的名字，前者用来告诉Qt，
事件处理函数“接收”了这个事件，不要再传递；后者则告诉Qt，事件处理函数“忽略”了这个事件，
需要继续传递，寻找另外的接受者。在事件处理函数中，可以使用`isAccepted()`来查询这个事
件是不是已经被接收了。

```C++
void MyLabel::mousePressEvent(QMouseEvent* event)
{
    if(event->button() == Qt::LeftButton) {
        // do something
    } else {
        QLabel::mousePressEvent(event);
    }
}
```

事实上，我们很少使用`accept()`和`ignore()`函数，而是想上面的示例一样，如果希望忽略事
件，只要调用父类的响应函数即可。记得我们曾经说过，Qt中的事件大部分是protected的，因此，
重写的函数必定存在着其父类中的响应函数，这个方法是可行的。为什么要这么做呢？因为我们无
法确认父类中的这个处理函数没有操作，如果我们在子类中直接忽略事件，Qt不会再去寻找其他的
接受者，那么父类的操作也就不能进行，这可能会有潜在的危险。另外我们查看一下QWidget的
`mousePressEvent()`函数的实现：

```C++
void QWidget::mousePressEvent(QMouseEvent* event)
{
    event->ignore();
    if ((windowType() == Qt::Popup)) {
        event->accept();
        QWidget* w;
        while ((w = qApp->activePopupWidget()) && w != this){
            w->close();
            if (qApp->activePopupWidget() == w) // widget does not want to dissappear
                w->hide(); // hide at least
        }
        if (!rect().contains(event->pos())){
            close();
        }
    }
}
```

请注意第一条语句，如果所有子类都没有覆盖`mousePressEvent`函数，这个事件会在这里被忽略
掉，这暗示着这个组件不关心这个事件，这个事件就可能被传递给其父组件。

不过，事情也不是绝对的。在一个情形下，我们必须使用accept()和ignore()函数，那就是在窗
口关闭的时候。如果你在窗口关闭时需要有个询问对话框，那么就需要这么去写：

```C++
void MainWindow::closeEvent(QCloseEvent* event)
{
    if(continueToClose()) {
        event->accept();
    } else {
        event->ignore();
    }
}
```
```C++
bool MainWindow::continueToClose()
{
    if (QMessageBox::question(this,
            tr("Quit"),
            tr("Are you sure to quit this application?"),
            QMessageBox::Yes | QMessageBox::No,
            QMessageBox::No)
        == QMessageBox::Yes) {
        return true;
    } else {
        return false;
    }
}
```

### **`event()`** 函数
事件对象创建完毕后，Qt将这个事件对象传递给QObject的event()函数。event()函数并不直接处
理事件，而是将这些事件对象按照它们不同的类型，分发给不同的事件处理器(event handler)。

event()函数主要用于事件的分发，所以，如果你希望在事件分发之前做一些操作，那么，就需要
注意这个event()函数了。为了达到这种目的，我们可以重写event()函数。例如，如果你希望在
窗口中的tab键按下时将焦点移动到下一组件，而不是让具有焦点的组件处理，那么你就可以继承
QWidget，并重写它的event()函数，已达到这个目的：
```C++
bool MyWidget::event(QEvent* event) {
	if (event->type() == QEvent::KeyPress) {
		QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
		if (keyEvent->key() == Qt::Key_Tab) {
			// 处理Tab鍵
			return true;
		}
	}

	return QWidget::event(event);
}
```

event()函数返回值是bool类型，如果传入的事件已被识别并且处理，返回true，否则返回false。
如果返回值是true，QApplication会认为这个事件已经处理完毕，会继续处理事件队列中的下一
事件；如果返回值是false，QApplication会尝试寻找这个事件的下一个处理函数。

event()函数的返回值和事件的accept()和ignore()函数不同。accept()和ignore()函数用于不
同的事件处理器之间的沟通，例如判断这一事件是否处理；event()函数的返回值主要是通知
QApplication的notify()函数是否处理下一事件。为了更加明晰这一点，我们来看看QWidget的
event()函数是如何定义的：
```C++
bool QWidget::event(QEvent* event) {
	switch (e->type()) {
		case QEvent::KeyPress:
			 keyPressEvent((QKeyEvent*)event);
			if (!((QKeyEvent*)event)->isAccepted())
				return false;
			break;

		case QEvent::KeyRelease:
			keyReleaseEvent((QKeyEvent*)event);
			if (!((QKeyEvent*)event)->isAccepted())
				return false;
			break;

			// more...
	}
	return true;
}
```
QWidget的event()函数使用一个巨大的switch来判断QEvent的type，并且分发给不同的事件处
理函数。在事件处理函数之后，使用这个事件的isAccepted()方法，获知这个事件是不是被接受，
如果没有被接受则event()函数立即返回false，否则返回true。

另外一个必须重写event()函数的情形是有自定义事件的时候。如果你的程序中有自定义事件，则
必须重写event()函数以便将自定义事件进行分发，否则你的自定义事件永远也不会被调用。

### 事件过滤器
有时候，你可能需要在调用event()函数之前做一些另外的操作，比如，对话框上某些组件可能并
不需要响应回车按下的事件，此时，你就需要重新定义组件的event()函数。如果组件很多，就需
要重写很多次event()函数，这显然没有效率。为此，你可以使用一个事件过滤器，来判断是否需
要调用event()函数。

QOjbect有一个`eventFilter()`函数，用于建立事件过滤器。这个函数的签名如下：
```
virtual bool QObject::eventFilter(QObject* watched, QEvent* event)
```

如果watched对象安装了事件过滤器，这个函数会被调用并进行事件过滤，然后才轮到组件进行事
件处理。在重写这个函数时，如果你需要过滤掉某个事件，例如停止对这个事件的响应，需要返
回true。

```C++
bool MainWindow::eventFilter(QObject* obj, QEvent* event)
{
	if (obj == textEdit) {
		if (event->type() == QEvent::KeyPress) {
			QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
			qDebug() << "Any key press" << keyEvent->key();
			return true;
		} else {
			return false;
		}
	} else {
		// pass the event on to the parent class
		return QMainWindow::eventFilter(obj, event);
	}
}
```
上面的例子中为MainWindow建立了一个事件过滤器。为了过滤某个组件上的事件，首先需要判断
这个对象是哪个组件，然后判断这个事件的类型。例如，我不想让textEdit组件处理键盘事件，
于是就首先找到这个组件，如果这个事件是键盘事件，则直接返回true，也就是过滤掉了这个事
件，其他事件还是要继续处理，所以返回false。对于其他组件，我们并不保证是不是还有过滤
器，于是最保险的办法是调用父类的函数。

在创建了过滤器之后，下面要做的是安装这个过滤器。安装过滤器需要调用
`installEventFilter()`函数。这个函数的签名如下：
```
void QObject::installEventFilter ( QObject * filterObj )
```

这个函数是QObject的一个函数，因此可以安装到任何QObject的子类，并不仅仅是UI组件。这个
函数接收一个QObject对象，调用了这个函数安装事件过滤器的组件会调用filterObj定义的
eventFilter()函数。例如，textField.installEventFilter(obj)，则如果有事件发送到
textField组件是，会先调用obj->eventFilter()函数，然后才会调用textField.event()。

如果一个组件安装了多个过滤器，则最后一个安装的会最先调用，类似于堆栈的行为。

事件过滤器和被安装的组件必须在同一线程，否则，过滤器不起作用。另外，如果在install之后，
这两个组件到了不同的线程，那么，只有等到二者重新回到同一线程的时候过滤器才会有效。

事件的调用最终都会调用`QCoreApplication`的`notify()`函数，因此，最大的控制权实际上是
重写`QCoreApplication`的`notify()`函数。由此可以看出，Qt的事件处理实际上是分层五个层
次，这几个层次的控制权是逐层增大的。
- 重定义事件处理函数
- 重定义`event()`函数
- 为单个组件安装事件过滤器
- 为`QApplication`安装事件过滤器
- 重定义`QCoreApplication`的`notify()`函数

### 自定义事件
Qt允许你创建自己的事件类型，这在多线程的程序中尤其有用，当然，也可以用在单线程的程序中，
作为一种对象间通讯的机制。那么，为什么我需要使用事件，而不是使用信号槽呢？主要原因是，
事件的分发既可以是同步的，又可以是异步的，而函数的调用或者说是槽的回调总是同步的。事件
的另外一个好处是，它可以使用过滤器。

Qt中的自定义事件很简单，同其他类似的库的使用很相似，都是要继承一个类进行扩展。在Qt中，
你需要继承的类是QEvent。注意，在Qt3中，你需要继承的类是QCustomEvent，不过这个类在Qt4
中已经被废除(这里的废除是不建议使用，并不是从类库中删除)。

继承QEvent类，你需要提供一个QEvent::Type类型的参数，作为自定义事件的类型值。这里的
QEvent::Type类型是QEvent里面定义的一个enum，因此，你是可以传递一个int的。重要的是，
你的事件类型不能和已经存在的type值重复，否则会有不可预料的错误发生！因为系统会将你的事
件当做系统事件进行派发和调用。在Qt中，系统将保留0 - 999的值，也就是说，你的事件type要
大于999. 具体来说，你的自定义事件的type要在QEvent::User和QEvent::MaxUser的范围之间。
其中，QEvent::User值是1000，QEvent::MaxUser的值是65535。从这里知道，你最多可以定义
64536个事件，相信这个数字已经足够大了！但是，即便如此，也只能保证用户自定义事件不能覆
盖系统事件，并不能保证自定义事件之间不会被覆盖。为了解决这个问题，Qt提供了一个函数
`registerEventType()`,用于自定义事件的注册。该函数签名如下：
```C++
static int QEvent::registerEventType ( int hint = -1 );
```

函数是static的，因此可以使用QEvent类直接调用。函数接受一个int值，其默认值为-1，返回值
是创建的这个Type类型的值。如果hint是合法的，不会发生任何覆盖，则会返回这个值；如果hint
不合法，系统会自动分配一个合法值并返回。因此，使用这个函数即可完成type值的指定。这个函
数是线程安全的，因此不必另外添加同步。

你可以在QEvent子类中添加自己的事件所需要的数据，然后进行事件的发送。Qt中提供了两种发送
方式：
1. `static bool QCoreApplication::sendEvent(QObjecy* receiver, QEvent* event)`：
事件被`QCoreApplication`的`notify()`函数直接发送给`receiver`对象，返回值是事件处理
函数的返回值。使用这个函数必须要在栈上创建对象，例如：
```C++
QMouseEvent event(QEvent::MouseButtonPress, pos, 0, 0, 0);
QApplication::sendEvent(mainWindow, &event);
```
1. `static bool QCoreApplication::postEvent(QObject* receiver, QEvent* event)`：
事件被`QCoreApplication`追加到事件列表的最后，并等待处理，该函数将事件追加后会立即返
回，并且注意，该函数是线程安全的。另外一点是，使用这个函数必须要在堆上创建对象，例如：
```c++
QApplication::postEvent(object, new MyEvent(QEvent::registerEventType(2048)));
```
这个对象不需要手动delete，Qt会自动delete掉！因此，如果在post事件之后调用delete，程序
可能会崩溃。另外，postEvent()函数还有一个重载的版本，增加一个优先级参数，具体请参见API。
通过调用sendPostedEvent()函数可以让已提交的事件立即得到处理。

如果要处理自定义事件，可以重写QObject的customEvent()函数，该函数接收一个QEvent对象作
为参数。注意，在Qt3中这个参数是QCustomEvent类型的。你可以像前面介绍的重写event()函数
的方法去重写这个函数：
```C++
void CustomWidget::customEvent(QEvent* event) {
    CustomEvent* customEvent = static_cast<CustomEvent*>(event);
    // ....
}
```

另外，你也可以通过重写event()函数来处理自定义事件：
```C++
bool CustomWidget::event(QEvent* event) {
    if (event->type() == MyCustomEventType) {
        CustomEvent* myEvent = static_cast<CustomEvent*>(event);
        // processing...
        return true;
    }

    return QWidget::event(event);
}
```


## --------
```
在最后一个窗口关闭后退出：
QApplication::setQuitOnLastWindowClosed(true);

退出event loop：
QCoreApplication::exit();
```

## Publish




# END
