/*************************************************************************
 > File Name: test.cpp
 > Author: aben
 > Mail: aben@taomee.com 
 > Created Time: Mon 02 Apr 2018 07:33:28 AM PDT                             
 ************************************************************************/
 
#include <iostream>
 
#include <odb/database.hxx>
#include <odb/transaction.hxx>
 
 
#include <odb/mysql/database.hxx>
 
#include "person-odb.hxx"
 
using namespace std;
using namespace odb::core;
 
int main (int argc, char* argv[])
{
    person aben, wenhao;
    aben.id = 1;aben.name = "aben";aben.sex = "man";aben.age = 23;
    wenhao.id = 2;wenhao.name = "wenhao";wenhao.sex = "man";wenhao.age = 22;
    
    typedef odb::query<person> query;
    typedef odb::result<person> result;
    try
    {
        shared_ptr<odb::mysql::database> db;
        db.reset(new odb::mysql::database ("root", "123456", "test"))
        transaction t (db->begin ());
        t.tracer (stderr_tracer);
        db->persist (aben);
        db->persist (wenhao);
        
        query q(query::id == 2);
 
        result r = db->query<person>(q)；
 
        for (auto i:r) 
        {
            cout << "{id:" << i.id << "  name:" << i.name << "   sex:" << i.sex << "   age:" << i.age << "}" << endl;
        }
        t.commit ();
    }
    catch (const odb::exception& e)
    {
        cerr << e.what () << endl;
    }
 
    return 0;
}

