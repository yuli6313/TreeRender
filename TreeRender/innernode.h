#ifndef INNERNODE_H
#define INNERNODE_H

#include <memory>
#include <QFontMetrics>
#include <algorithm>
#include "treenode.h"

class InnerNode : public TreeNode
{
public:
    InnerNode(QFontMetrics& fm, uint32_t dx, uint32_t dy, const QString& t = "", QString label = "") :
        TreeNode(fm, dx, dy, t), label(std::move(label)) {}

    void add_children(std::unique_ptr<TreeNode> child) {
        children.push_back(std::move(child));
    }

    //
    void place(QPoint p) override {
        int x = p.x();
        int y = p.y();
        height = 0;
        for (const auto& child : children) {
            child->place(QPoint(x, y + fm.height() * 2 + dy * 2));
            x += child->getWidth() + dx;
            width += child->getWidth() + dx;
            height = std::max(height, child->getHeight());
        }
        if (width < fm.width(txt)) {
            width = fm.width(txt);
        }
        height += 2*dy + 2*fm.height();
        pos.setX((p.x() + width) / 2 - fm.width(txt) / 2);
        pos.setY(y);
        l1 = QPoint(p.x(), p.y() + dy + fm.height() / 2);
        l2 = QPoint(p.x() + width - fm.width(label) - dx, p.y() + dy + fm.height() / 2);
        label_pos = QPoint(p.x() + width - fm.width(label), p.y() + dy + fm.height());
    }

    void render(QPainter& painter, int y_offset) override {
        for (auto const& child: children) {
            child->render(painter, y_offset);
        }
        painter.drawText(QRect(pos.x(), y_offset - pos.y(), fm.width(txt), fm.height()), txt);
        l1.setY(y_offset - l1.y());
        l2.setY(y_offset - l2.y());
        painter.drawLine(l1, l2);
        painter.drawText(QRect(label_pos.x(), y_offset - label_pos.y(), fm.width(label), fm.height()), label);
    }

private:
    std::vector<std::unique_ptr<TreeNode>> children;
    // label which is the rule number
    QString label;
    QPoint l1 = QPoint(0,0);
    QPoint l2 = QPoint(0,0);
    QPoint label_pos = QPoint(0,0);
};
#endif // INNERNODE_H
