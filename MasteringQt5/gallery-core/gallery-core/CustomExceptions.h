#ifndef CUSTOMEXCEPTIONS_H
#define CUSTOMEXCEPTIONS_H

#include <exception>

class SqlQueryException: public std::exception{
public:
    virtual const char* what() const noexcept {
        return "Sql Query exec() Failed";
    }
};

#endif // CUSTOMEXCEPTIONS_H
