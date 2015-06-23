

#include <QApplication>

#include "appl.h"

int main(int argc, char *argv[])
{
    QApplication qappl{argc, argv};

    Appl appl{};

    return qappl.exec();
}
