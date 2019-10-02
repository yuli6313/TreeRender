#ifndef LEAFNODE_H
#define LEAFNODE_H

#include <QPainter>
#include <QString>
#include "treenode.h"

class LeafNode : public TreeNode {
public:
    LeafNode(QFontMetrics& fm, uint32_t dx, uint32_t dy, const QString& t = "") :
        TreeNode(fm, dx, dy, t) {}

    void place(QPoint p) override {
        pos = p;
        width = fm.width(txt);
        height = fm.height();
    }

    // render node in screen buffer
    void render(QPainter &painter, int y_offset) override {
        painter.drawText(QRect(pos.x(), y_offset - pos.y(), width, height), txt);
    }
};

#endif // LEAFNODE_H
