#pragma once
#include "CommonDefines.hpp"
#include "File.hpp"
#include "IDataBlob.hpp"
#include "IODefines.hpp"
#include "TObject.hpp"

namespace Toy::IO
{
class IFileInterface : public Toy::IObject
{
   public:
    static constexpr const IUUID CLS_UUID = {/* 71dc3d44-bd75-495d-be1f-adf39859edcd */
                                             0x71dc3d44,
                                             0xbd75,
                                             0x495d,
                                             {0xbe, 0x1f, 0xad, 0xf3, 0x98, 0x59, 0xed, 0xcd}};

    virtual bool IsExits() const = 0;

    virtual void Open(const char* path, const EFileAccess& mode) = 0;

    virtual void Close() = 0;

    virtual void ReadRaw(void* p_data, const std::size_t& r_size) = 0;

    virtual void ReadBlob(Engine::IDataBlob* blob) = 0;

    virtual std::size_t GetLength() const noexcept = 0;

    virtual std::size_t GetPosition() const noexcept = 0;

    virtual void WriteRaw(const void* buffer, const std::size_t& w_size) = 0;

    virtual void WriteBlob(const Engine::IDataBlob* blob, const std::size_t& w_size) = 0;

    virtual void WriteBlob(const Engine::IDataBlob* blob) = 0;

    virtual void WriteText(const char* text) = 0;

    virtual std::string ReadLine() const = 0;

    virtual std::string ReadToEnd() const = 0;

    virtual void Seek(const std::size_t& offset, const ESeekOrigin& orgin) = 0;
};

class TFile final : public Engine::TObject<IFileInterface>
{
    using TBase = Engine::TObject<IFileInterface>;

    File file;

    IMPLEMENT_CONSTRUCT_LOCALLY(TBase, TFile, const char* path, const EFileAccess& mode), file(path, mode) {}

    void OnDestroy() override { Close(); }

   public:
    IMPLEMENT_QUERYINTERFACE_LOCALLY(TFile, TBase)

    NODISCARD inline bool IsExits() const override { return file.IsExits(); }

    inline void Open(const char* path, const EFileAccess& mode) override { file.Open(path, mode); }

    inline void Close() override { file.Close(); }

    inline void ReadRaw(void* p_data, const std::size_t& r_size) override { file.ReadRaw(p_data, r_size); }

    inline void ReadBlob(Engine::IDataBlob* blob) override { file.ReadBlob(blob); }

    NODISCARD inline std::size_t GetLength() const noexcept override { return file.GetLength(); }

    NODISCARD inline std::size_t GetPosition() const noexcept override { return file.GetPosition(); }

    inline void WriteRaw(const void* buffer, const std::size_t& w_size) override { file.WriteRaw(buffer, w_size); }

    inline void WriteBlob(const Engine::IDataBlob* blob, const std::size_t& w_size) override { file.WriteBlob(blob, w_size); }

    inline void WriteBlob(const Engine::IDataBlob* blob) override { file.WriteBlob(blob); }

    inline void WriteText(const char* text) override { file.WriteText(text); }

    NODISCARD inline std::string ReadLine() const override { return file.ReadLine(); }

    NODISCARD inline std::string ReadToEnd() const override { return file.ReadToEnd(); }

    void Seek(const std::size_t& offset, const ESeekOrigin& orgin) override { file.Seek(offset, orgin); }
};
}  // namespace Toy::IO