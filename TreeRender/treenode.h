#ifndef TREENODE_H
#define TREENODE_H

#include <unistd.h>
#include <string>
#include <QPainter>
#include <QPoint>
#include <QFont>
#include <QFontMetrics>

class TreeNode
{
public:
    TreeNode(QFontMetrics& fm, uint32_t dx, uint32_t dy, QString t = "") :
        fm(fm), dx(dx), dy(dy), txt(std::move(t)) {}

    virtual ~TreeNode() = default;

    // get width
    uint32_t getWidth() const {
        return width;
    }

    // get height
    uint32_t getHeight() const {
        return height;
    }

    // place the node
    virtual void place(QPoint p) = 0;

    // render node in screen buffer
    virtual void render(QPainter &painter, int y_offset) = 0;

    size_t getSize() {
        return size;
    }

    void setSize(size_t s) {
        size = s;
    }

protected:
    QFontMetrics& fm;
    uint32_t dx;
    uint32_t dy;
    QString txt;      // text of tree node
    uint32_t width = 0;   // width of node (including sub-trees)
    uint32_t height = 0;  // height of node (including sub-trees)
    QPoint pos = QPoint(0,0); // position of the premise
    uint32_t size = 0;
};

#endif // TREENODE_H
