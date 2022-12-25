#include "Hash.h"
#include <iostream>

std::vector<unsigned int> HashSHA1::Hash(const char *buffer)
{
    boost::crc_32_type result;
    result.process_bytes(buffer, strlen(buffer));
    auto checksum = result.checksum();
    return { checksum };
}


std::vector<unsigned int> HashCRC32::Hash(const char *buffer)
{
    boost::uuids::detail::md5 hash;
    boost::uuids::detail::md5::digest_type digest;
    hash.process_bytes(buffer, strlen(buffer));
    hash.get_digest(digest);
    return { std::begin(digest), std::end(digest) };
}


std::vector<unsigned int> HashMD5::Hash(const char *buffer)
{
    boost::uuids::detail::sha1 hash;
    boost::uuids::detail::sha1::digest_type digest;
    hash.process_bytes(buffer, strlen(buffer));
    hash.get_digest(digest);
    return { std::begin(digest), std::end(digest) };
}
