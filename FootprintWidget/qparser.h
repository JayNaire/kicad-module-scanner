#ifndef QPARSER_H
#define QPARSER_H
#include <QtGui>
#include <QtCore>
#include <QtCore/QSharedDataPointer>
#include <QtCore/QVarLengthArray>
//extern void * footprint_scan_string(const char *str); //where's the include for this static?
//struct YY_BUFFER_STATE;
//extern struct yy_buffer_state;
//yy_buffer_state* footprint_scan_string(const char *str);
int footprintget_lineno(void);
void footprintset_lineno(int);
char *footprintget_text(void);
template <typename _Parser, typename _Table, typename _Value = int>
class QParser: protected _Table
{
//public:
//	ModView *modView;
//	typedef class ModView m;
//	m *modView;
public:
    QParser();
    ~QParser();

    bool parse();
//    inline void setText(const QString text);
    const QString getErrorMessage()const {return QString(errorMessage);};
    inline _Value &sym(int index);
//    inline void setModView(ModView *mw){modView = mw;}; //we will add outlines and pads to this graphicsview as they're parsed
//    inline void setModView(m *mw){modView = mw;}; //we will add outlines and pads to this graphicsview as they're parsed

private:
    inline int nextToken()
    {
        return static_cast<_Parser*> (this)->nextToken();
    }

    inline void consumeRule(int rule)
    {
        static_cast<_Parser*> (this)->consumeRule(rule);
    }

    enum { DefaultStackSize = 128 };

    struct Data: public QSharedData
    {
        Data(): stackSize (DefaultStackSize), tos (0) {}

        QVarLengthArray<int, DefaultStackSize> stateStack;
        QVarLengthArray<_Value, DefaultStackSize> parseStack;
        int stackSize;
        int tos;

        void reallocateStack() {
            stackSize <<= 1;
            stateStack.resize(stackSize);
            parseStack.resize(stackSize);
        }
    };

    QSharedDataPointer<Data> d;
    QString errorMessage;
//	ModView *modView;
};

//template <typename _Parser, typename _Table, typename _Value>
//inline void QParser<_Parser, _Table, _Value>::setText(const QString text){
//	QByteArray ba = text.toLocal8Bit();
//	const char *cstr = ba.data();
//	footprint_scan_string(cstr);
//}

template <typename _Parser, typename _Table, typename _Value>
inline _Value &QParser<_Parser, _Table, _Value>::sym(int n)
{
    return d->parseStack [d->tos + n - 1];
}

template <typename _Parser, typename _Table, typename _Value>
QParser<_Parser, _Table, _Value>::QParser():
    d(new Data()), errorMessage("No error")
{
}

template <typename _Parser, typename _Table, typename _Value>
QParser<_Parser, _Table, _Value>::~QParser()
{
}

template <typename _Parser, typename _Table, typename _Value>
bool QParser<_Parser, _Table, _Value>::parse()
{
    const int INITIAL_STATE = 0;

    d->tos = 0;
    d->reallocateStack();
    int act = d->stateStack[++d->tos] = INITIAL_STATE;
    int token = -1;
    footprintset_lineno(1);
    forever {
        if (token == -1 && - _Table::TERMINAL_COUNT != _Table::action_index[act])
            token = nextToken();

        act = _Table::t_action(act, token);

        if (d->stateStack[d->tos] == _Table::ACCEPT_STATE)
            return true; //parse completed OK

        else if (act > 0) { //token is OK but rule not finished yet; shift
            if (++d->tos == d->stackSize)
                d->reallocateStack();

            d->parseStack[d->tos] = d->parseStack[d->tos - 1];
            d->stateStack[d->tos] = act;
            token = -1;
        }

        else if (act < 0) { //token is OK and rule is finished; reduce
            int r = - act - 1;
            d->tos -= _Table::rhs[r];
            act = d->stateStack[d->tos++];
            consumeRule(r);
            act = d->stateStack[d->tos] = _Table::nt_action(act, _Table::lhs[r] - _Table::TERMINAL_COUNT);
        }

        else{ //act is 0 for current token
        	errorMessage = QString("Line %1\nUnexpected input %2").arg(footprintget_lineno()).arg(footprintget_text());
        	qDebug() << errorMessage;
        	break; //parse failed
        }
    }

    return false;
}


#endif // QPARSER_H
