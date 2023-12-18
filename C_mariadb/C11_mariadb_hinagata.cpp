#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
//g++ -std=c++20 test_db.cpp -o test_db -lmysqlcppconn
//segmentaion faultした　-> smart-pointerによる明示的開放が為されていない可能性があるので、原因が分かるまでは使用しないこと
int main(){
    std::unique_ptr<sql::mysql::MySQL_Driver> driver;
    std::unique_ptr<sql::Connection> con;

    try{
        driver = std::unique_ptr<sql::mysql::MySQL_Driver>(sql::mysql::get_mysql_driver_instance());
        con = std::unique_ptr<sql::Connection>(driver->connect("localhost:3306", "your-username", "your-password"));

        //dbとの接続
        con->setSchema("test_database");

        //tableからdataを取得するquery
        std::unique_ptr<sql::Statement> stmt(con->createStatement());
        std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM test_table"));

        //result_output
        while(res -> next()){
            std::cout << "Column 1: " << res->getInt(1) << " ,Column 2: " << res->getString(2) << " ,Column3: " << res->getString(3) << "\n";
        }

    }catch (sql::SQLException &e) {
        std::cout << "# ERR: SQLException in " << __FILE__;
        std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << "\n";

        std::cout << "#ERR: " << e.what();
        std::cout << " (MySQL error code: " << e.getErrorCode();
        std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
    return 0;
}