#ifndef GETANDSINDRESPONSEMIDDLEWARE_H
#define GETANDSINDRESPONSEMIDDLEWARE_H

#include <QObject>
class GetAndSindResponseMiddleWare : public QObject
{
Q_OBJECT
public:
    GetAndSindResponseMiddleWare();

public slots:
    void getResponseFromBoardSquare(QString respone[]);

signals:
    void sendRespnoseToGameBoard(QString respone[]);
};

#endif // GETANDSINDRESPONSEMIDDLEWARE_H
