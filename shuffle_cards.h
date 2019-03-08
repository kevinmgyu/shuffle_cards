#ifndef __VP_ANAYLSE_H__
#define __VP_ANAYLSE_H__
#include <fc/crypto/elliptic.hpp>
#include <fc/exception/exception.hpp>
#include <fc/crypto/hex.hpp>

#include <fc/io/json.hpp>

//#include "transaction.hpp"
#include "ut_address.h"
#include "ut_log.h"
#include <iostream>
#include <fstream>
using namespace std;
void shuffle_cards(vector<int> &desk_cards,string &seed,int card_num);
#endif
