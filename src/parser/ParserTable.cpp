#include "ParserTable.h"

static ParserTable* instance;
ParserTable::ParserTable()
{

}


ParserTable* ParserTable::getInstance()
{
    if(instance == NULL) {
        instance = new ParserTable();
    }
    return instance;
}
