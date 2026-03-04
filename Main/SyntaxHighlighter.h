#ifndef SYNTAXHIGHLIGHTER_H
#define SYNTAXHIGHLIGHTER_H

#include <QSyntaxHighlighter>
#include <QtQmlIntegration>

class SyntaxHighlighterPrivate;
class SyntaxHighlighter : public QSyntaxHighlighter
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(SyntaxHighlighter)

    QML_ELEMENT

public:
    explicit SyntaxHighlighter(QObject *parent = nullptr);
    ~SyntaxHighlighter() override;
protected:
    QScopedPointer<SyntaxHighlighterPrivate> d_ptr;

public:
    void highlightBlock(const QString &text) final;
};

#endif // SYNTAXHIGHLIGHTER_H
