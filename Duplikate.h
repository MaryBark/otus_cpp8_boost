#ifndef DUPLIKATE_H
#define DUPLIKATE_H

#pragma once
//#include <boost/filesystem.hpp>
//#include <boost/regex.hpp>
//#include <unordered_map>
//#include <unordered_set>

#include "Hash.h"
#include "HashFile.h"




class Duplikate
{
public:
    Duplikate(const strVec& include_dirs,
                    const strVec& exclude_dirs,
                    const strVec& filemasks,
                    size_t block_size,
                    size_t scan_depth,
                    uintmax_t min_file_size,
                    const std::string& hasher);

    duplicate Find();

    std::vector<BFilePath/*boost::filesystem::path*/> TrySetDirs(const strVec& dirs);

private:
    const std::vector<BFilePath> include_dirs_;
    const std::vector<BFilePath> exclude_dirs_;
    const std::vector<boost::regex> filemasks_;
    const size_t block_size_;
    const size_t scan_depth_;
    const unsigned int min_file_size_;
    std::shared_ptr<IHash> hasher_;
    std::vector<HashFile> files_;
    std::unordered_set<std::string> scanned_file_paths_;

    std::shared_ptr<IHash> TrySetHasher(const std::string& hasher);
    std::vector<boost::regex> SetFileMasks(const strVec& filemasks);

    void ScanPath(const BFilePath& path, size_t depth);

    void AddFile(const BFilePath& path);

    bool InExcludeDirs(const BFilePath& path);

    bool MasksSatisfied(const BFilePath& path);

    bool AlreadyInDuplicates(const BFilePath& path,
                             duplicate& duplicates);
};

#endif // DUPLIKATE_H
