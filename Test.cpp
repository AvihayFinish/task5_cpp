#include "doctest.h"
#include "sources/MagicalContainer.hpp"
#include <iostream>
using namespace ariel;
using namespace std;

TEST_CASE("Check the constructor of MagicalContainer") {
    MagicalContainer cont;
    CHECK(cont.size() == 0);
}

TEST_CASE("Check the functions of MagicalContainer") {
    MagicalContainer cont;
    cont.addElement(10);
    cont.addElement(6);
    cont.addElement(-4);
    cont.addElement(15);
    CHECK(cont.size() == 4);
    vector<int>& chk = cont.getCont();
    CHECK(chk[0] == -4);
    CHECK(chk[1] == 6);
    CHECK(chk[2] == 10);
    CHECK(chk[3] == 15);
    cont.removeElement(6);
    CHECK(chk[1] == 10);
    CHECK(cont.size() == 3);
    cont.removeElement(-4);
    CHECK(chk[0] == 10);
    CHECK(cont.size() == 2);
    cont.removeElement(25);
    CHECK(cont.size() == 2);
}

TEST_CASE("Check the AscendingIterator") {
    MagicalContainer cont1;
    cont1.addElement(10);
    cont1.addElement(6);
    cont1.addElement(-4);
    cont1.addElement(15);
    MagicalContainer cont2;
    cont2.addElement(100);
    cont2.addElement(60);
    cont2.addElement(-40);
    cont2.addElement(150);
    vector<int>& chk = cont1.getCont();
    MagicalContainer::AscendingIterator ascIt(cont1);
    MagicalContainer::AscendingIterator ascItOther(cont2);
    CHECK(*ascIt == chk[0]);
    ascIt++;
    CHECK(*ascIt == chk[1]);
    ++ascIt;
    CHECK(*ascIt == chk[2]);
    CHECK(ascIt != ascItOther);
    ascIt = ascIt.begin();
    CHECK(*ascIt == chk[0]);
    ascIt = ascIt.end();
    CHECK(*ascIt == chk[3]);
    MagicalContainer::AscendingIterator ascItSame(ascIt);
    CHECK(ascIt == ascItSame);
    ascItOther.begin();
    CHECK(ascIt > ascItOther);
    CHECK_FALSE(ascIt < ascItOther);
    cont1.removeElement(6);
    ascItOther++;
    CHECK(*ascItOther == 10);
}

TEST_CASE("Check the SideCrossIterator") {
    MagicalContainer cont1;
    cont1.addElement(10);
    cont1.addElement(6);
    cont1.addElement(-4);
    cont1.addElement(15);
    MagicalContainer cont2;
    cont2.addElement(100);
    cont2.addElement(60);
    cont2.addElement(-40);
    cont2.addElement(150);
    vector<int>& chk = cont1.getCont();
    MagicalContainer::SideCrossIterator sidIt(cont1);
    MagicalContainer::SideCrossIterator sidItOther(cont2);
    CHECK(*sidIt == chk[0]);
    sidIt++;
    CHECK(*sidIt == chk[3]);
    ++sidIt;
    CHECK(*sidIt == chk[1]);
    CHECK(sidIt != sidItOther);
    sidIt = sidIt.begin();
    CHECK(*sidIt == chk[0]);
    sidIt = sidIt.end();
    CHECK(*sidIt == chk[2]);
    MagicalContainer::SideCrossIterator sidItSame(sidIt);
    CHECK(sidIt == sidItSame);
    sidItOther.begin();
    CHECK(sidIt > sidItOther);
    CHECK_FALSE(sidIt < sidItOther);
    cont1.removeElement(15);
    sidItOther++;
    CHECK(*sidItOther == 10);
}

TEST_CASE("Check the PrimeIterator") {
    MagicalContainer cont1;
    cont1.addElement(10);
    cont1.addElement(6);
    cont1.addElement(-4);
    cont1.addElement(15);
    cont1.addElement(2);
    cont1.addElement(7);
    cont1.addElement(11);
    MagicalContainer cont2;
    cont2.addElement(100);
    cont2.addElement(60);
    cont2.addElement(-40);
    cont2.addElement(150);
    vector<int>& chk = cont1.getCont();
    MagicalContainer::PrimeIterator priIt(cont1);
    MagicalContainer::PrimeIterator priItOther(cont2);
    CHECK(*priIt == chk[0]);
    priIt++;
    CHECK(*priIt == chk[1]);
    ++priIt;
    CHECK(*priIt == chk[2]);
    CHECK(priIt != priItOther);
    priIt = priIt.begin();
    CHECK(*priIt == chk[0]);
    priIt = priIt.end();
    CHECK(*priIt == chk[2]);
    MagicalContainer::PrimeIterator priItSame(priIt);
    CHECK(priIt == priItSame);
    priItOther.begin();
    CHECK(priIt > priItOther);
    CHECK_FALSE(priIt < priItOther);
    cont1.removeElement(7);
    priItOther++;
    CHECK(*priItOther == 11);
}