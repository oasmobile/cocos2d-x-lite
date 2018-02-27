#include "SQLiteWrapper.h"

#define ENABLE_SQLITE_ENCRYPT	0
#define LE_SQLITE_KEY			"123456"

SQLiteStatement::SQLiteStatement(const std::string& statement, sqlite3* db) {
    if ( sqlite3_prepare(
                         db,
                         statement.c_str(),  // stmt
                         -1,                  // If than zero, then stmt is read up to the first nul terminator
                         &stmt_,
                         0                   // Pointer to unused portion of stmt
                         )
        != SQLITE_OK) {
        cocos2d::log("Fun SQLiteStatement::SQLiteStatement(const std::string& statement, sqlite3* db) ErrorCode %s" , sqlite3_errmsg(db));
        throw sqlite3_errmsg(db);
    }
    
    if (!stmt_) {
        cocos2d::log("Fun SQLiteStatement::SQLiteStatement(const std::string& statement, sqlite3* db) ErrorCode stmt_ is 0");
        throw "stmt_ is 0";
    }
    cocos2d::log("stmt_ is OK  ");
}

SQLiteStatement::~SQLiteStatement() {
	if (stmt_) {
		sqlite3_finalize(stmt_);
		stmt_ = 0;
	}
}

SQLiteStatement::SQLiteStatement() :
stmt_(0)
{
}

bool SQLiteStatement::bind(int pos_zero_indexed, const std::string& value) {
    if (sqlite3_bind_text (
                           stmt_,
                           pos_zero_indexed+1,  // Index of wildcard
                           value.c_str(),
                           value.length(),      // length of text
                           SQLITE_TRANSIENT     // SQLITE_TRANSIENT: SQLite makes its own copy
                           )
        != SQLITE_OK) {
        return false;
    }
    return true;
}

bool SQLiteStatement::bind(int pos_zero_indexed, double value) {
    if (sqlite3_bind_double(
                            stmt_,
                            pos_zero_indexed+1,  // Index of wildcard
                            value
                            )
        != SQLITE_OK) {
        return false;
    }
    return true;
}

bool SQLiteStatement::bind(int pos_zero_indexed, int value) {
    if (sqlite3_bind_int(
                         stmt_,
                         pos_zero_indexed+1,  // Index of wildcard
                         value
                         )
        != SQLITE_OK) {
        return false;
    }
    return true;
}

bool SQLiteStatement::bindNull(int pos_zero_indexed) {
    if (sqlite3_bind_null(
                          stmt_,
                          pos_zero_indexed+1  // Index of wildcard
                          )
        != SQLITE_OK) {
        return false;
    }
    return true;
}

bool SQLiteStatement::execute() {
    int rc = sqlite3_step(stmt_);
    if (rc == SQLITE_BUSY) {
        return false;
    }
    if (rc == SQLITE_ERROR) {
        return false;
    }
    if (rc == SQLITE_MISUSE) {
        return false;
    }
    if (rc != SQLITE_DONE) {
        //sqlite3_reset(stmt_);
        return false;
    }
    sqlite3_reset(stmt_);
    return true;
}

SQLiteStatement::DataType SQLiteStatement::dataType(int pos_zero_indexed) {
	return DataType(sqlite3_column_type(stmt_, pos_zero_indexed));
}

int SQLiteStatement::dataCount()
{
	return sqlite3_data_count(stmt_);
}

int SQLiteStatement::valueCount()
{
	return sqlite3_column_count(stmt_);
}

std::string SQLiteStatement::valueName(int pos_zero_indexed)
{
	if (sqlite3_column_name(stmt_, pos_zero_indexed) == NULL){
		return std::string("null");
	}

	return std::string(sqlite3_column_name(stmt_, pos_zero_indexed));
}
int SQLiteStatement::valueInt(int pos_zero_indexed) {
    return sqlite3_column_int(stmt_, pos_zero_indexed);
}

double SQLiteStatement::valueDouble(int pos_zero_indexed) {
    return sqlite3_column_double(stmt_, pos_zero_indexed);
}

std::string SQLiteStatement::valueString(int pos_zero_indexed) {
    
    if(sqlite3_column_text(stmt_, pos_zero_indexed) == NULL){
        return std::string("null");
    }
    
    return std::string(reinterpret_cast<const char*>(sqlite3_column_text(stmt_, pos_zero_indexed)));
}

bool SQLiteStatement::restartSelect() {
    sqlite3_reset(stmt_);
    return true;
}

bool SQLiteStatement::reset() {
    int rc = sqlite3_step(stmt_);
    
    sqlite3_reset(stmt_);
    
    if (rc == SQLITE_ROW) return true;
    return false;
}

bool SQLiteStatement::nextRow() {
    int rc = sqlite3_step(stmt_);
    
    if (rc == SQLITE_ROW   ) {
        return true;
    }
    if (rc == SQLITE_DONE  ) {
        sqlite3_reset(stmt_);
        return false;
    }
    else if (rc == SQLITE_MISUSE) {
        cocos2d::log("sqlite status: %s","SQLITE_MISUSE");
    }
    else if (rc == SQLITE_BUSY  ) {
        cocos2d::log("sqlite status: %s","SQLITE_BUSY");
    }
    else if (rc == SQLITE_ERROR ) {
        cocos2d::log("sqlite status: %s","SQLITE_ERROR");
    }
    return false;
}

SQLiteWrapper::SQLiteWrapper() : db_(0) {}
SQLiteWrapper::~SQLiteWrapper(){}

bool SQLiteWrapper::init()
{
	return true;
}

SQLiteWrapper * SQLiteWrapper::create()
{
	SQLiteWrapper * ret = new (std::nothrow) SQLiteWrapper();
	if (ret && ret->init())
	{
		ret->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(ret);
	}
	return ret;
}
std::string SQLiteWrapper::getPath(const std::string& db_file, const std::string& db_dir)
{
	std::string fullpath = "";
	fullpath = db_dir + "/" + db_file;
	fullpath = FileUtils::getInstance()->fullPathForFilename(fullpath.c_str());

	bool isExist = FileUtils::getInstance()->isFileExist(fullpath.c_str());
	CCASSERT(isExist,"db is not isExist");

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
	std::string copyPath  = FileUtils::getInstance()->getWritablePath();
	copyPath = copyPath + db_file;

	bool needCopy = true;

	isExist = FileUtils::getInstance()->isFileExist(copyPath.c_str());
	if (isExist)
	{

	}

	if (needCopy){
		FILE* file = fopen(copyPath.c_str(), "r");
		if (file != nullptr){
			FileUtils::getInstance()->removeFile(copyPath.c_str());
		}

		auto data = FileUtils::getInstance()->getDataFromFile(fullpath.c_str());
		FILE* dest = fopen(copyPath.c_str(), "wb");
		fwrite(data.getBytes(), 1, data.getSize(), dest);
		fclose(dest);
	}

	fullpath = copyPath;
#endif

	return fullpath;
}

bool SQLiteWrapper::open(const std::string& db_file) {
	if (sqlite3_open(db_file.c_str(), &db_) != SQLITE_OK) {
		return false;
	}

#if ENABLE_SQLITE_ENCRYPT
	if (sqlite3_key(db_, LE_SQLITE_KEY, strlen(LE_SQLITE_KEY)) != SQLITE_OK){
		return false;
	}
#endif

	return true;
}

SQLiteStatement* SQLiteWrapper::exec(const std::string& statement) {
	SQLiteStatement* stmt = 0;
	try {
		stmt = new (std::nothrow) SQLiteStatement(statement, db_);
		return stmt;
	}
	catch (const char* e) {
		return 0;
	}
}

void SQLiteWrapper::close(){
	sqlite3_close(db_);
}

bool SQLiteWrapper::directStatement(const std::string& stmt) {
    char *errmsg;
    int   ret;
    
    ret = sqlite3_exec(db_, stmt.c_str(), 0, 0, &errmsg);
    
    if(ret != SQLITE_OK) {
        return false;
    }
    return true;
}

std::string SQLiteWrapper::lastError() {
    return sqlite3_errmsg(db_);
}

bool SQLiteWrapper::begin() {
    return directStatement("begin");
}

bool SQLiteWrapper::commit() {
    return directStatement("commit");
}

bool SQLiteWrapper::rollback() {
    return directStatement("rollback");
}
