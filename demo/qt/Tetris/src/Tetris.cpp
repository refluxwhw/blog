#include "Tetris.h"
#include <QPainter>
#include <QPen>
#include <QTimer>

#include "LShape.h"
#include "LOppShape.h"
#include "SquareShpe.h"
#include "ZShape.h"
#include "ZOppShape.h"
#include "StripShape.h"
#include "TShape.h"
#include <QDateTime>

Tetris::Tetris(QWidget *parent) : QWidget(parent)
{
    m_height = 25;
    m_width = 12;
    m_size = 20;
    m_isSpeedup = false;
    m_level = 0;
    m_background = QColor(Qt::white);
    m_movingShape = NULL;

    m_blocks = new Block_t*[m_height];
    for (int i=0; i<m_height; i++)
    {
        m_blocks[i] = new Block_t[m_width];
        for (int j=0; j<m_width; j++)
        {
            m_blocks[i][j].setColor(m_background);
        }
    }

    onCreateMovingShape();
}

Tetris::~Tetris()
{
    for (int i=0; i<m_height; i++)
    {
        delete [] m_blocks[i];
    }
    delete [] m_blocks;
}

void Tetris::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    pen.setColor(m_background);
    pen.setWidth(1);
    painter.setPen(pen);
    for (int i=0; i<m_height; i++)
    {
        for (int j=0; j<m_width; j++)
        {
            Block_t block = m_blocks[i][j];
            painter.setBrush(QBrush(block.color()));
            painter.drawRect(j*m_size, i*m_size, m_size, m_size);
        }
    }

    if (m_movingShape)
    {
        QVector<PosBlock_t> blocks = m_movingShape->getBlocks();
        for (int i=0; i<blocks.size(); i++)
        {
            PosBlock_t& block = blocks[i];
            painter.setBrush(QBrush(block.color()));
            painter.drawRect(block.x*m_size, block.y*m_size, m_size, m_size);
        }
    }
}

void Tetris::onRestart()
{
    // stop

    // clear

    // singleShot
}

void Tetris::onPause()
{
    // set flag
}

void Tetris::onGoOn()
{
    // set flag

    // singleShot
}

void Tetris::onLeftClicked()
{
    if (m_movingShape)
    {
        m_movingShape->moveLeft(m_blocks);
    }
    update();
}

void Tetris::onRightClicked()
{
    if (m_movingShape)
    {
        m_movingShape->moveRight(m_blocks);
    }
    update();
}

void Tetris::onRotateLeft()
{
    if (m_movingShape)
    {
        m_movingShape->rotateLeft(m_blocks);
    }
    update();
}

void Tetris::onRotateRight()
{
    if (m_movingShape)
    {
        m_movingShape->rotateRight(m_blocks);
    }
    update();
}

void Tetris::onDownPresse()
{
    m_isSpeedup = true;
}

void Tetris::onDownRelease()
{
    m_isSpeedup = false;
}

void Tetris::onFall()
{
    if (m_movingShape)
    {
        if (m_movingShape->moveDown(m_blocks))
        {
            update();
            QTimer::singleShot(m_isSpeedup ? 100 : ((10-m_level) *100),
                               this, SLOT(onFall()));
        }
        else
        {
            // 将移动对象的方块数据加入到已经存在的方块数据中
            QVector<PosBlock_t> blocks = m_movingShape->getBlocks();
            QList<int> affectlines;
            for (int i=0; i<blocks.size(); i++)
            {
                PosBlock_t& b = blocks[i];
                m_blocks[b.y][b.x] = Block_t(b.color().red(), b.color().green(), b.color().blue(), true);

                if (!affectlines.contains(b.y))
                {
                    affectlines.append(b.y);
                }
            }
            delete m_movingShape;
            m_movingShape = NULL;

            // 检查是否存在需要消除的行
            m_eraserLines.clear();
            for (int i=0; i<affectlines.size(); i++)
            {
                int y = affectlines[i];
                bool ok = true;
                for (int x=0; x<m_width; x++)
                {
                    if (!m_blocks[y][x].isSolid())
                    {
                        ok = false;
                        break;
                    }
                }
                if (ok)
                {
                    m_eraserLines.append(y);
                }
            }

            if (m_eraserLines.size() == 0)
            {
                // 产生一个新的移动对象，并开始执行移动
                onCreateMovingShape();
            }
            else
            {
                m_stage = 0;
                onEraserLines();
            }
        }
    }

}

void Tetris::onEraserLines()
{
    switch (m_stage)
    {
        case 0: // 行变红
            for (int i=0; i<m_eraserLines.size(); i++)
            {
                int y = m_eraserLines[i];
                for (int x=0; x<m_width; x++)
                {
                    m_blocks[y][x].setColor(QColor(Qt::red));
                }
            }
            update();
            m_stage++;
            QTimer::singleShot(200, [this]{onEraserLines();});
            break;

        case 1: // 200ms 后，行变白
            for (int i=0; i<m_eraserLines.size(); i++)
            {
                int y = m_eraserLines[i];
                for (int x=0; x<m_width; x++)
                {
                    m_blocks[y][x].setColor(QColor(Qt::white));
                }
            }
            update();
            m_stage++;
            QTimer::singleShot(200, [this]{onEraserLines();});
            break;

        case 2: // 200ms 后，行变红
            for (int i=0; i<m_eraserLines.size(); i++)
            {
                int y = m_eraserLines[i];
                for (int x=0; x<m_width; x++)
                {
                    m_blocks[y][x].setColor(QColor(Qt::red));
                }
            }
            update();
            m_stage++;
            QTimer::singleShot(200, [this]{onEraserLines();});
            break;

        case 3: // 200ms 后，行变白
            for (int i=0; i<m_eraserLines.size(); i++)
            {
                int y = m_eraserLines[i];
                for (int x=0; x<m_width; x++)
                {
                    m_blocks[y][x].setColor(QColor(Qt::white));
                }
            }
            update();
            m_stage++;
            QTimer::singleShot(200, [this]{onEraserLines();});
            break;
        case 4:// 200ms 后，消除行，上面的行向下移动，并产生一个新的移动对象
            for (int i=0; i<m_eraserLines.size(); i++)
            {
                int y = m_eraserLines[i];
                delete [] m_blocks[y];
                for (; y>0; y--)
                {
                    m_blocks[y] = m_blocks[y-1];
                }

                m_blocks[0] = new Block_t[m_width];
                for (int j=0; j<m_width; j++)
                {
                    m_blocks[0][j].setColor(m_background);
                }
            }
            update();

            emit sigEraserLine(m_eraserLines.size()); // 外部计分

            onCreateMovingShape();
            break;
    }
}

void Tetris::onCreateMovingShape()
{
    if (m_movingShape)
    {
        delete m_movingShape;
        m_movingShape = NULL;
    }
    qint64 t = QDateTime::currentMSecsSinceEpoch();
    qint64 ms = t % 1000LL;
    int sid = (int)ms;
    srand(sid);
	int r = rand();
    int shape = r % 7;
	r = rand();
    unsigned char angel = r % 4;


    switch (shape)
    {
        case 0:
            m_movingShape = new LShape(m_width, m_height, 5, 0, angel);
            break;
        case 1:
            m_movingShape = new LOppShape(m_width, m_height, 5, 0, angel);
            break;
        case 2:
            m_movingShape = new SquareShpe(m_width, m_height, 5, 0);
            break;
        case 3:
            m_movingShape = new ZShape(m_width, m_height, 5, 0, angel);
            break;
        case 4:
            m_movingShape = new ZOppShape(m_width, m_height, 5, 0, angel);
            break;
        case 5:
            m_movingShape = new StripShape(m_width, m_height, 5, 0, angel);
            break;
        case 6:
            m_movingShape = new TShape(m_width, m_height, 5, 0, angel);
            break;

        default:
            break;
    }

    QTimer::singleShot(m_isSpeedup ? 100 : ((10-m_level) *100),
                       this, SLOT(onFall()));
}



