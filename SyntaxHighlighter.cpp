#include "SyntaxHighlighter.h"
#include "SyntaxHighlighter_p.h"

#include <QFile>

// class SyntaxHighlighter

SyntaxHighlighter::SyntaxHighlighter(QObject *parent)
    : QSyntaxHighlighter{parent}
    , d_ptr{new SyntaxHighlighterPrivate{}}
{
    d_ptr->q_ptr = this;
}

SyntaxHighlighter::~SyntaxHighlighter()
{
}

void SyntaxHighlighter::highlightBlock(const QString &text)
{
    Q_UNUSED(text);
}

QString SyntaxHighlighter::loadCode(const QString &fileName) const
{
    QFile file{QStringLiteral(":/qt/qml/Flexbox/") % fileName};
    if (file.open(QFile::ReadOnly)) {
        return QString::fromUtf8(file.readAll());
    }

    return {};
}

// class SyntaxHighlighterPrivate
