#include "delay.h"
#include "chain.h"
#include "chainparams.h"
#include "pow.h"
#include "random.h"
#include "util.h"
#include "test/test_bitcoin.h"
#include "validation.h"

#include <boost/test/unit_test.hpp>

BOOST_FIXTURE_TEST_SUITE(blockdelay_tests, BasicTestingSetup)

BOOST_AUTO_TEST_CASE(GetBlock_delay) {
    CBlockIndex *block = new CBlockIndex();
    CBlockIndex *pblock = new CBlockIndex();

    CBlock newblock;
    CBlockIndex indexNew {newblock};
    CBlock prevblock;
    CBlockIndex indexPrev {prevblock};


    indexNew.nHeight = 100;
    indexPrev.nChainDelay = 0;
    int activeChainHeight = 100; 
    BOOST_CHECK(GetBlockDelay(indexNew, indexPrev, activeChainHeight, false) == 0);

    
    indexNew.nHeight = 5;
    indexPrev.nChainDelay = 0;
    activeChainHeight = 16;
    BOOST_CHECK(GetBlockDelay(indexNew, indexPrev, activeChainHeight, false) == 11);


    // some delay in the current chain
    indexNew.nHeight = 100 ;
    indexPrev.nChainDelay = 20 ;
    activeChainHeight = 500; 
    BOOST_CHECK(GetBlockDelay(indexNew, indexPrev, activeChainHeight, false) == 400);


    indexNew.nHeight = 6;
    indexPrev.nChainDelay = 11;
    activeChainHeight = 16;
    BOOST_CHECK(GetBlockDelay(indexNew, indexPrev, activeChainHeight, false) == 10);
}

BOOST_AUTO_TEST_SUITE_END()