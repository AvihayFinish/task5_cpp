#include "MagicalContainer.hpp"
#include <iostream>
using namespace std;
using namespace ariel;

MagicalContainer::MagicalContainer () : sizeOfCont(0) {}

void MagicalContainer::addElement (int ind) {
    if (this->sizeOfCont == 0) {
        this->cont.push_back(ind);
    }
    else {
        for (std::vector<int>::size_type i = 0; i < this->sizeOfCont; i++) {
            if (this->cont[i] < ind) {
                if (i == (this->sizeOfCont - 1)) {
                    this->cont.push_back(ind);
                }
                continue;
            }
            auto it = this->cont.begin() + static_cast<std::vector<int>::difference_type>(i);
            this->cont.insert(it, ind);
            break;
        }
    }
    this->sizeOfCont++;
}

void MagicalContainer::removeElement (int ind) {
    bool exsit = false;
    for (std::vector<int>::size_type i = 0; i < this->cont.size(); i++) {
        if (this->cont[i] == ind) {
            this->cont.erase(this->cont.begin() + static_cast<std::vector<int>::difference_type>(i));
            this->sizeOfCont--;
            exsit = true;
        }
    }
    if (exsit == false) {
        cout << "this element dosent exist in the container" << endl;   
    }
}

vector<int>::size_type MagicalContainer::size () {
    return this->sizeOfCont;
}

vector<int>& MagicalContainer::getCont () {
    return this->cont;
}


// ******************* ascending ************************
MagicalContainer::AscendingIterator::AscendingIterator (MagicalContainer& container) : pointToCurr(&container.cont[0]), mag(&container) {}

MagicalContainer::AscendingIterator::AscendingIterator (AscendingIterator& other) : pointToCurr(other.pointToCurr), mag(other.mag) {}

MagicalContainer::AscendingIterator::~AscendingIterator() {}

MagicalContainer::AscendingIterator::AscendingIterator (AscendingIterator&& other) noexcept: mag(other.mag), pointToCurr(other.pointToCurr) {
    other.pointToCurr = nullptr;
    other.mag = nullptr;
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator= (AscendingIterator&& other) noexcept {
    return *this;
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator= (const AscendingIterator& other) {
    return *this;
}

bool MagicalContainer::AscendingIterator::operator== (const AscendingIterator& other) const {
    return this->pointToCurr == other.pointToCurr;
}

bool MagicalContainer::AscendingIterator::operator!= (const AscendingIterator& other) const {
    return this->pointToCurr != other.pointToCurr;
}

bool MagicalContainer::AscendingIterator::operator< (const AscendingIterator& other) const {
    return true;
}

bool MagicalContainer::AscendingIterator::operator> (const AscendingIterator& other) const {
    return true;
}

int MagicalContainer::AscendingIterator::operator* () const {
    return *this->pointToCurr;
}

MagicalContainer::AscendingIterator& MagicalContainer::AscendingIterator::operator++ () {
    this->pointToCurr++;
    return *this;
}

const MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::operator++ (int) {
    AscendingIterator asc(*this);
    this->pointToCurr++;
    return asc;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin () {
    AscendingIterator iter(*mag);
    iter.pointToCurr = &mag->cont[0];
    return iter;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end () {
    AscendingIterator iter(*mag);
    iter.pointToCurr = &mag->cont[mag->size()];
    return iter;
}

// ******************* sidecross ************************
MagicalContainer::SideCrossIterator::SideCrossIterator (MagicalContainer& container) : beginCurrPtr(&container.cont[0]), mag(&container), 
                                                                                        endCurrPtr(&container.cont[container.size() - 1]), _end(false) {}

MagicalContainer::SideCrossIterator::SideCrossIterator (SideCrossIterator& other) : beginCurrPtr(other.beginCurrPtr), mag(other.mag),
                                                                                    endCurrPtr(other.endCurrPtr), _end(other._end) {}

MagicalContainer::SideCrossIterator::~SideCrossIterator() {}

MagicalContainer::SideCrossIterator::SideCrossIterator(SideCrossIterator&& other) noexcept {}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator= (SideCrossIterator&& other) noexcept {
    return *this;
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator= (const SideCrossIterator& other) {
    return *this;
}

bool MagicalContainer::SideCrossIterator::operator== (const SideCrossIterator& other) const {
    if (this->_end) {
        return this->endCurrPtr == other.endCurrPtr;
    }
    return this->beginCurrPtr == other.beginCurrPtr;
}

bool MagicalContainer::SideCrossIterator::operator!= (const SideCrossIterator& other) const {
    if (this->_end) {
        return this->endCurrPtr != other.endCurrPtr;
    }
    return this->beginCurrPtr != other.beginCurrPtr;
}

bool MagicalContainer::SideCrossIterator::operator< (const SideCrossIterator& other) const {
    return true;
}

bool MagicalContainer::SideCrossIterator::operator> (const SideCrossIterator& other) const {
    return true;
}

int MagicalContainer::SideCrossIterator::operator* () const {
    if (this->_end) {
        return *this->endCurrPtr;
    }
    return *this->beginCurrPtr;
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++ () {
    if (this->_end) {
        this->endCurrPtr--;
        this->_end = false;
    }
    else {
        this->beginCurrPtr++;
        this->_end = true;
    }
    return *this;
} 

const MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::operator++ (int) {
    SideCrossIterator sid(*this->mag);
    sid.beginCurrPtr = this->beginCurrPtr;
    sid.endCurrPtr = this->endCurrPtr;
    if (this->_end) {
        this->endCurrPtr--;
        this->_end = false;
    }
    else {
        this->beginCurrPtr++;
        this->_end = true;
    }
    return sid;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin () {
    return SideCrossIterator(*mag);
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end () {
    SideCrossIterator iter(*mag);
    iter.beginCurrPtr = &mag->cont[mag->size()];
    iter.endCurrPtr = &mag->cont[mag->size()];
    return iter;
}


// ******************* prime ************************
MagicalContainer::PrimeIterator::PrimeIterator (MagicalContainer& container) : pointToCurr(&container.cont[0]), mag(&container) {}

MagicalContainer::PrimeIterator::PrimeIterator (PrimeIterator& other) : pointToCurr(other.pointToCurr), mag(other.mag) {}

MagicalContainer::PrimeIterator::~PrimeIterator() {}

MagicalContainer::PrimeIterator::PrimeIterator (PrimeIterator&& other) noexcept {}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator= (PrimeIterator&& other) noexcept {
    return *this;
}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator= (const PrimeIterator& other) {
    return *this;
}

bool MagicalContainer::PrimeIterator::operator== (const PrimeIterator& other) const {
    return this->pointToCurr == other.pointToCurr;
}

bool MagicalContainer::PrimeIterator::operator!= (const PrimeIterator& other) const {
    return this->pointToCurr != other.pointToCurr;
}

bool MagicalContainer::PrimeIterator::operator< (const PrimeIterator& other) const {
    return true;
}

bool MagicalContainer::PrimeIterator::operator> (const PrimeIterator& other) const {
    return true;
}

int MagicalContainer::PrimeIterator::operator* () const {
    return 3;
}

MagicalContainer::PrimeIterator& MagicalContainer::PrimeIterator::operator++ () {
    this->pointToCurr++;
    return *this;
}

const MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::operator++ (int) {
    PrimeIterator pri(*this->mag);
    pri.pointToCurr = this->pointToCurr;
    this->pointToCurr++;
    return pri;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin () {
    return PrimeIterator(*mag);
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end () {
    return PrimeIterator(*mag);
}
