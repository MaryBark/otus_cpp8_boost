#include "HashFile.h"


bool HashNode::operator==(const HashNode &other) const
{
    return data == other.data;
}

bool HashNode::operator!=(const HashNode &other) const
{
    return data != other.data;
}

HashFile::HashFile(BFilePath path, uintmax_t hash_blocksize, std::shared_ptr<IHash> hasher):
    filepath_(path),
    filesize_(boost::filesystem::file_size(filepath_)),
    max_blocks_amount_((filesize_ + hash_blocksize - 1) / hash_blocksize),
    blocksize_(hash_blocksize),
    hasher_(hasher)
{}

bool HashFile::Equal(HashFile &other)
{
    if (filesize_ != other.filesize_)
    {
        return false;
    }
    for (size_t i = 0; i < max_blocks_amount_; i++)
    {
        if (GetHashNode(i) != other.GetHashNode(i))
        {
            CloseHandle();
            other.CloseHandle();
            return false;
        }
    }
    CloseHandle();
    other.CloseHandle();
    return true;
}

BFilePath HashFile::GetFilePath() const
{
    return filepath_;
}

void HashFile::OpenHandle()
{
    if (!file_handle_)
    {
        file_handle_ = std::make_unique<std::ifstream>(filepath_.string());
        file_handle_->seekg(hash_data_.size() * blocksize_);
    }
}

void HashFile::CloseHandle()
{
    if (file_handle_ != nullptr)
    {
        file_handle_->close();
        file_handle_.reset(nullptr);
    }
}

std::unique_ptr<char[]> HashFile::GetNextBlock()
{
    OpenHandle();
    auto buffer = std::make_unique<char[]>(blocksize_);
    file_handle_->read(buffer.get(), blocksize_);
    return buffer;
}

void HashFile::CalcHashUntil(size_t block_index)
{
    while (hash_data_.size() <= block_index)
    {
        auto data = GetNextBlock().get();
        std::cout << GetFilePath() << " : " << std::string(data).size() << " " << std::endl;
        hash_data_.emplace_back(HashNode { hasher_->Hash(data) });
    }
}

HashNode HashFile::GetHashNode(size_t block_index)
{
    if (block_index >= max_blocks_amount_)
    {
        throw std::logic_error("Invalid block index value!");
    }
    if (block_index < hash_data_.size())
    {
        return hash_data_[block_index];
    }
    CalcHashUntil(block_index);
    return hash_data_[block_index];
}

