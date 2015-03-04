/* 
 * File:   Utils.h
 * Author: skrep
 *
 * Created on 2 de Março de 2015, 16:13
 */

#ifndef UTILS_H
#define	UTILS_H

class Utils {
public:
    Utils();
    Utils(const Utils& orig);
    virtual ~Utils();
    
    static long long int mod(long long int a, long long int b);
private:

};

#endif	/* UTILS_H */

