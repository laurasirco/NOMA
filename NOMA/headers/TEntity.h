/* 
 * File:   TEntity.h
 * Author: laurasirventcollado
 *
 * Created on 10 de febrero de 2014, 11:37
 */

#ifndef TENTITY_H
#define	TENTITY_H

class TEntity {
public:
    TEntity();
    TEntity(const TEntity& orig);
    virtual ~TEntity();
    
    virtual void beginDraw() = 0;
    virtual void endDraw() = 0;
private:
};

#endif	/* TENTITY_H */

