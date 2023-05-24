#include "getandsindresponsemiddleware.h"

GetAndSindResponseMiddleWare::GetAndSindResponseMiddleWare()
{

}

void GetAndSindResponseMiddleWare::getResponseFromBoardSquare(QString respone[])
{
    emit sendRespnoseToGameBoard(respone);
}
