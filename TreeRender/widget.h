#ifndef WIDGET_H
#define WIDGET_H

#include <memory>
#include <QWidget>
#include <QPainter>
#include <QPaintDevice>
#include <QDebug>
#include <QFont>
#include <QString>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include "treenode.h"
#include "ui_widget.h"
#include "innernode.h"
#include "leafnode.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(char* jsonFile, int font_size = 11, uint32_t dx = 5, uint32_t dy = 5, QWidget *parent = nullptr) :
        ui(new Ui::Widget),
        QWidget(parent),
        fm(QFontMetrics(QFont())),
        font_size(font_size),
        dx(dx), dy(dy) {
        ui->setupUi(this);
        this->resize(1000,800);
        QString jsonString;
        QFile file;
        file.setFileName(jsonFile);
        file.open(QIODevice::ReadOnly | QIODevice::Text);
        jsonString = file.readAll();
        this->jsonDoc = QJsonDocument::fromJson(jsonString.toUtf8());
        QJsonObject proof = jsonDoc.object()["proof"].toObject();
        tree = std::move(buildTree(proof));
        tree->place(QPoint(0,0));
    }
    ~Widget() {
        delete ui;
    }
    // paint the proof tree
    void paintEvent(QPaintEvent* event) {

        QPainter painter(this);
        QFont f;
        f.setPointSize(font_size);
        fm = QFontMetrics(f);
        painter.setFont(f);
        // place the nodes

        // render the nodes
        tree->render(painter, tree->getHeight());
    }

private:
    Ui::Widget *ui;
    QJsonDocument jsonDoc;
    QFontMetrics fm;
    std::unique_ptr<TreeNode> tree;
    int font_size;
    uint32_t dx;
    uint32_t dy;
    // recursively build the tree with the given JSON object
    std::unique_ptr<TreeNode> buildTree(const QJsonObject& node) {
        if (node.contains("children")) {
            std::unique_ptr<InnerNode> n(new InnerNode(fm, dx, dy, node["premises"].toString(), node["rule-number"].toString()));
            auto array = node["children"].toArray();
            for (auto c : array) {
                n->add_children(std::move(buildTree(c.toObject())));
            }
            std::unique_ptr<TreeNode> ret(std::move(n));
            return ret;
        } else {
            std::unique_ptr<TreeNode> n(new LeafNode(fm, dx, dy, node["axiom"].toString()));
            return n;
        }
    }

};

#endif // WIDGET_H
