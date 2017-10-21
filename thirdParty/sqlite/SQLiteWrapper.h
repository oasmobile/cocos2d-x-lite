#ifndef __SQLiteWrapper_H__
#define __SQLiteWrapper_H__

#include "cocos2d.h"
#include "sqlite3/sqlite3.h"

#include <string>
#include <vector>

USING_NS_CC;

class SQLiteStatement : public Ref{
private:
    friend class SQLiteWrapper;
    SQLiteStatement(const std::string& statement, sqlite3* db);
    
public:
    SQLiteStatement();
	~SQLiteStatement();

    enum DataType {
        INT = SQLITE_INTEGER,
        FLT = SQLITE_FLOAT  ,
        TXT = SQLITE_TEXT   ,
        BLB = SQLITE_BLOB   ,
        NUL = SQLITE_NULL   ,
    };
    
    DataType dataType(int pos_zero_indexed);
	int dataCount();
    
	int valueCount();
	std::string valueName(int pos_zero_indexed);
    int valueInt (int pos_zero_indexed);
    std::string valueString(int pos_zero_indexed);
        
    bool bind(int pos_zero_indexed, const std::string& value);
    bool bind(int pos_zero_indexed, double value);
    bool bind(int pos_zero_indexed, int value);
    bool bindNull(int pos_zero_indexed);
    
    bool execute();    
    bool nextRow();    

	bool reset();
    
    bool restartSelect();
    
private:
    sqlite3_stmt* stmt_;
};

class SQLiteWrapper : public Ref{
public:
    SQLiteWrapper();
	virtual ~SQLiteWrapper();
	virtual bool init();

	static SQLiteWrapper* create();

	std::string getPath(const std::string& db_file, const std::string& db_dir);
	bool open(const std::string& db_file);
	SQLiteStatement* exec(const std::string& stmt);
	void close();

    bool directStatement(const std::string& stmt);    
    std::string lastError();
    
    bool begin();
    bool commit();
    bool rollback();

private:    
    static int selectCallback(void *p_data, int num_fields, char **p_fields, char **p_col_names);    
    sqlite3* db_;
};

#endif
