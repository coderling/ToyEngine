#include "DataBlob.hpp"

namespace Toy::Engine
{
RefCountPtr<DataBlob> DataBlob::Create(const std::size_t& size, const void* p_data)
{
    return RefCountPtr<DataBlob>(MakeReferenceCounter<DataBlob>()(size, p_data));
}

IMPLEMENT_CONSTRUCT_DEFINE_HEAD(TBase, DataBlob, std::size_t size, const void* p_data), data_buffer(size)
{
    if (size > 0 && !data_buffer.empty() && p_data != nullptr)
        {
            std::memcpy(data_buffer.data(), p_data, size);
        }
}

DataBlob::~DataBlob() noexcept {}

IMPLEMENT_QUERYINTERFACE(DataBlob, TBase)

std::size_t DataBlob::GetDataSize() const { return data_buffer.size(); }

void* DataBlob::GetDataPointer()
{
    // 调用const 版本
    return const_cast<void*>((static_cast<const DataBlob*>(this))->GetDataPointer());
}

const void* DataBlob::GetDataPointer() const { return data_buffer.data(); }

void DataBlob::Resize(const std::size_t& size) { data_buffer.resize(size); }

void DataBlob::OnDestroy() {}

}  // namespace Toy::Engine