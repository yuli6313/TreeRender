#include "widget.h"
#include <QApplication>

#include <iostream>

int main(int argc, char *argv[])
{
    // json file is passed as argument
    if (argc != 2) {
        std::cerr << "Expected JSON file as input" << std::endl;
        return -1;
    }
    QApplication a(argc, argv);
    Widget w(argv[1]);
    w.show();

    return a.exec();
}
