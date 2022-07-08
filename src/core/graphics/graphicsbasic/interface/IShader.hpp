#pragma once
#include <stdint.h>
#include <CStringTool.hpp>
#include <string>
#include "DeviceObject.hpp"
#include "IDataBlob.hpp"
#include "InterfaceUUID.hpp"
#include "RefCountPtr.hpp"

namespace Toy::Graphics
{
enum SHADER_TYPE
{
    SHADER_TYPE_UNKNOWN = 0,
    SHADER_TYPE_VERTEX = 1 << 0,
    SHADER_TYPE_PIXEL = 1 << 1,
    SHADER_TYPE_GEOMETRY = 1 << 2,
    SHADER_TYPE_HULL = 1 << 3,
    SHADER_TYPE_DOMAIN = 1 << 4,
    SHADER_TYPE_COMPUTE = 1 << 5,
    SHADER_TYPE_MESH = 1 << 6,
};
// shader modle struct etc:6.1
struct ShaderModel
{
    uint8_t major;
    uint8_t minor;
};

// shader macro
struct ShaderMacro
{
    const char* macro = nullptr;

    constexpr ShaderMacro() noexcept {}
    constexpr ShaderMacro(const char* _macro) noexcept
        : macro(_macro)
    {
    }

    bool operator==(const ShaderMacro& rhs) const { return CStrEqual(this->macro, rhs.macro); }

    bool operator!=(const ShaderMacro& rhs) const { return !(*this == rhs); }
};

// shader desc
struct ShaderDesc
{
    const char* name = nullptr;
    SHADER_TYPE shader_type = SHADER_TYPE_UNKNOWN;

    constexpr ShaderDesc() noexcept {}
    constexpr ShaderDesc(const char* _name, const SHADER_TYPE& _shader_type) noexcept
        : name(_name),
          shader_type(_shader_type)
    {
    }

    bool operator==(const ShaderDesc& rhs) const { return this->shader_type == rhs.shader_type && CStrEqual(name, rhs.name); }

    bool operator!=(const ShaderDesc& rhs) const { return *this != rhs; }
};

struct ShaderCreateInfo
{
    // the source file path or the bytecode filepath, ignore when bytecode or source not null
    const char* file_path = nullptr;
    // load bytecode from file
    const bool load_bytecode = false;

    // shader source code, ignore when bytecode not null
    const char* source = nullptr;
    std::size_t source_length = 0;
    Engine::RefCountPtr<Engine::IDataBlob> p_shader_bytecode;

    const char* entry = nullptr;

    const ShaderMacro* macro = nullptr;

    ShaderDesc desc;

    ShaderModel shader_model;

   public:
    void InitASCompileFromeSourceFile(const char* file_path, const char* entry = "SDMain", const ShaderMacro* macro = nullptr)
    {
        this->file_path = file_path;
        this->entry = entry;
        this->macro = macro;
    }

    void InitASCompileFromSourceCode(const char* source_code,
                                     const std::size_t& len,
                                     const char* entry = "SDMain",
                                     const ShaderMacro* macro = nullptr)
    {
        this->source = source_code;
        this->source_length = len;

        this->entry = entry;
        this->macro = macro;
    }

    void InitASByteCode(const Engine::RefCountPtr<Engine::IDataBlob>& bytecode) { p_shader_bytecode = std::move(bytecode); }

    NODISCARD std::string GetShaderModelString() const noexcept
    {
        std::string sm = "";
        switch (desc.shader_type)
            {
                case SHADER_TYPE_VERTEX:
                    sm += "vs";
                    break;
                case SHADER_TYPE_PIXEL:
                    sm += "ps";
                    break;
                case SHADER_TYPE_GEOMETRY:
                case SHADER_TYPE_HULL:
                case SHADER_TYPE_DOMAIN:
                case SHADER_TYPE_COMPUTE:
                case SHADER_TYPE_MESH:
                case SHADER_TYPE_UNKNOWN:
                    LOG_ERROR("not support this shader type: ", desc.shader_type);
                    break;
            }

        if (!sm.empty())
            {
                if (shader_model.major == 6)
                    {
                        sm += "_6_" + std::to_string(shader_model.minor);
                    }
                else
                    {
                        LOG_ERROR("only support shader model greater 6!!!");
                    }
            }

        return sm;
    }
};

class IShader : public Toy::Graphics::IDeviceObject
{
   public:
    INTERFACEUUID(IShader) = {/* 83006833-6598-4387-a374-d76dccefe15d */
                              0x83006833,
                              0x6598,
                              0x4387,
                              {0xa3, 0x74, 0xd7, 0x6d, 0xcc, 0xef, 0xe1, 0x5d}};

    virtual const ShaderDesc& GetDesc() const = 0;
};
}  // namespace Toy::Graphics