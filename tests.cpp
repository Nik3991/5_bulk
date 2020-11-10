#define BOOST_TEST_MODULE helloworld_test_module
#include <boost/test/included/unit_test.hpp>

#include <sstream>
#include <string>

using namespace std;

struct cout_mock
{
    string s;
    cout_mock& operator<<(const string& _s)
    {
        s.append(_s);
        return *this;
    }
};

namespace {
    cout_mock cmock;
}

//--------------------------
#define cout cmock
#define endl " "

#include "Bulk.h"

#undef cout
#undef endl
//--------------------------

BOOST_AUTO_TEST_SUITE(bulk_test_suite)
BOOST_AUTO_TEST_CASE(bulk_test)
{
    istringstream stream("c1 c2 { c3 c4 } { c5 c6 { c7 c8 } c9 } { c10 c11");
    cin.rdbuf(stream.rdbuf());

    Block b(3);
    b.exec();

    BOOST_CHECK(cmock.s == "bulk: c1, c2 bulk: c3, c4 bulk: c5, c6, c7, c8, c9 ");
}

BOOST_AUTO_TEST_SUITE_END()
