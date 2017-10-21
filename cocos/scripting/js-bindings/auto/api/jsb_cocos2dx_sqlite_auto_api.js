/**
 * @module cocos2dx_sqlite
 */
var jsb = jsb || {};

/**
 * @class SQLiteStatement
 */
jsb.SQLiteStatement = {

/**
 * @method reset
 * @return {bool}
 */
reset : function (
)
{
    return false;
},

/**
 * @method execute
 * @return {bool}
 */
execute : function (
)
{
    return false;
},

/**
 * @method dataCount
 * @return {int}
 */
dataCount : function (
)
{
    return 0;
},

/**
 * @method dataType
 * @param {int} arg0
 * @return {SQLiteStatement::DataType}
 */
dataType : function (
int 
)
{
    return SQLiteStatement::DataType;
},

/**
 * @method bind
* @param {int|int|int} int
* @param {double|String|int} double
* @return {bool|bool|bool}
*/
bind : function(
int,
int 
)
{
    return false;
},

/**
 * @method nextRow
 * @return {bool}
 */
nextRow : function (
)
{
    return false;
},

/**
 * @method valueCount
 * @return {int}
 */
valueCount : function (
)
{
    return 0;
},

/**
 * @method restartSelect
 * @return {bool}
 */
restartSelect : function (
)
{
    return false;
},

/**
 * @method bindNull
 * @param {int} arg0
 * @return {bool}
 */
bindNull : function (
int 
)
{
    return false;
},

/**
 * @method valueName
 * @param {int} arg0
 * @return {String}
 */
valueName : function (
int 
)
{
    return ;
},

/**
 * @method valueInt
 * @param {int} arg0
 * @return {int}
 */
valueInt : function (
int 
)
{
    return 0;
},

/**
 * @method valueString
 * @param {int} arg0
 * @return {String}
 */
valueString : function (
int 
)
{
    return ;
},

/**
 * @method SQLiteStatement
 * @constructor
 */
SQLiteStatement : function (
)
{
},

};

/**
 * @class SQLiteWrapper
 */
jsb.SQLiteWrapper = {

/**
 * @method begin
 * @return {bool}
 */
begin : function (
)
{
    return false;
},

/**
 * @method rollback
 * @return {bool}
 */
rollback : function (
)
{
    return false;
},

/**
 * @method exec
 * @param {String} arg0
 * @return {SQLiteStatement}
 */
exec : function (
str 
)
{
    return SQLiteStatement;
},

/**
 * @method directStatement
 * @param {String} arg0
 * @return {bool}
 */
directStatement : function (
str 
)
{
    return false;
},

/**
 * @method commit
 * @return {bool}
 */
commit : function (
)
{
    return false;
},

/**
 * @method getPath
 * @param {String} arg0
 * @param {String} arg1
 * @return {String}
 */
getPath : function (
str, 
str 
)
{
    return ;
},

/**
 * @method init
 * @return {bool}
 */
init : function (
)
{
    return false;
},

/**
 * @method close
 */
close : function (
)
{
},

/**
 * @method lastError
 * @return {String}
 */
lastError : function (
)
{
    return ;
},

/**
 * @method open
 * @param {String} arg0
 * @return {bool}
 */
open : function (
str 
)
{
    return false;
},

/**
 * @method create
 * @return {SQLiteWrapper}
 */
create : function (
)
{
    return SQLiteWrapper;
},

/**
 * @method SQLiteWrapper
 * @constructor
 */
SQLiteWrapper : function (
)
{
},

};
