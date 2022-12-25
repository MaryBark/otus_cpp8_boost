#ifndef HASHFILE_H
#define HASHFILE_H

#pragma once

#include "Hash.h"

#include <boost/filesystem.hpp>
#include <iostream>
#include <vector>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>
#include <unordered_map>
#include <unordered_set>


using BFilePath = boost::filesystem::path;
using duplicate = std::unordered_map<std::string, std::unordered_set<std::string>>;
using strVec = std::vector<std::string>;


struct HashNode
{
    std::vector<unsigned int> data;

    bool operator==(const HashNode& other) const;
    bool operator!=(const HashNode& other) const;
};


class HashFile
{
public:
    HashFile(BFilePath path, uintmax_t hash_blocksize, std::shared_ptr<IHash> hasher);

    bool Equal(HashFile& other);
    BFilePath GetFilePath() const;

private:
    const boost::filesystem::path filepath_;
    const uintmax_t filesize_;
    const size_t max_blocks_amount_;
    const uintmax_t blocksize_;
    std::shared_ptr<IHash> hasher_;
    std::vector<HashNode> hash_data_;
    std::unique_ptr<std::ifstream> file_handle_;


    void OpenHandle();
    void CloseHandle();
    std::unique_ptr<char[]> GetNextBlock();
    void CalcHashUntil(size_t block_index);
    HashNode GetHashNode(size_t block_index);
};

#endif // HASHFILE_H
