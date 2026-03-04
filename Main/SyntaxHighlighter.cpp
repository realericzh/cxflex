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

SyntaxHighlighter::~SyntaxHighlighter() = default;

void SyntaxHighlighter::highlightBlock(const QString &text)
{
    Q_UNUSED(text);
}

// class SyntaxHighlighterPrivate
