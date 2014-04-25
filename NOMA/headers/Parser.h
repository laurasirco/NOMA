 /* 
 * File:   Parser.h
 * Author: MAC
 *
 * Created on 6 de noviembre de 2013, 10:29
 */

#ifndef PARSER_H
#define	PARSER_H
#include "PGraph.h"
#include "World.h"
#include <list>
using namespace std;

class Parser {
public:
    Parser();
    Parser(const Parser& orig);
    virtual ~Parser();
    PGraph * ParseStage(std::string fileName);
    bool isInVector(vector<PNode *> nodes, PNode * e);
    bool isInList(std::vector< std::list<PEdge*> > List, PEdge* edge);
    void ParseWorld(std::string worldName, World * me);
    void ParseWorldMeshesData(std::string fileName, World * me);
private:
    bool get_file(std::string filename, wstring &description, wstring &data);
};

#endif	/* PARSER_H */

