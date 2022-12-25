#ifndef HASH_H
#define HASH_H


#pragma once

#include <boost/crc.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <boost/uuid/detail/sha1.hpp>
#include <vector>

class IHash
{
public:
    IHash() = default;
    virtual ~IHash() = default;

    virtual std::vector<unsigned int> Hash(const char* buffer) = 0;

    // запрещаем под страхом смерти конструкторы копирования и операторы присваивания)))
    IHash(const IHash& other) = delete;
    IHash(IHash&& other) = delete;
    IHash& operator=(const IHash& other) = delete;
    IHash& operator=(IHash&& other) = delete;
};


class HashSHA1 : public IHash
{
public:
    HashSHA1() = default;

    std::vector<unsigned int> Hash(const char* buffer) override;
};

class HashCRC32 : public IHash
{
public:
    HashCRC32() = default;

    std::vector<unsigned int> Hash(const char* buffer) override;
};


class HashMD5 : public IHash
{
public:
    HashMD5() = default;

    std::vector<unsigned int> Hash(const char* buffer) override;
};

#endif // HASH_H
