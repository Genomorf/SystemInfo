#include "darkpalette.h"

QPalette darkPalette::setDarkPalette()
{
    Palette.setColor(QPalette::Window, QColor(33, 33, 33));
    Palette.setColor(QPalette::WindowText, Qt::white);
    Palette.setColor(QPalette::Base, QColor(23, 23, 23));
    Palette.setColor(QPalette::AlternateBase, QColor(23, 23, 23));
    Palette.setColor(QPalette::ToolTipBase, Qt::white);
    Palette.setColor(QPalette::ToolTipText, Qt::white);
//    Palette.setColor(QPalette::Text, Qt::white);
    Palette.setColor(QPalette::Button, QColor(53, 53, 53));
    Palette.setColor(QPalette::ButtonText, Qt::white);
    Palette.setColor(QPalette::BrightText, Qt::red);
    Palette.setColor(QPalette::Link, QColor(42, 130, 218));
    Palette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    Palette.setColor(QPalette::HighlightedText, Qt::black);

    return this->Palette;
}
