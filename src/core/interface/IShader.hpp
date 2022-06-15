#pragma once
#include <stdint.h>
#include <CStringTool.hpp>
#include <IObject.hpp>
#include <string>

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
// shader modle struct etc:5.1
struct ShaderModel
{
    uint8_t major;
    uint8_t minor;
};

// shader macro
struct ShaderMacro
{
    const char* name = nullptr;
    const char* definition = nullptr;

    constexpr ShaderMacro() noexcept {}
    constexpr ShaderMacro(const char* _name, const char* _definition) noexcept : name(_name), definition(_definition) {}

    bool operator==(const ShaderMacro& rhs) const { return CStrEqual(this->name, rhs.name) && CStrEqual(this->definition, rhs.definition); }

    bool operator!=(const ShaderMacro& rhs) const { return !(*this == rhs); }
};

// shader desc
struct ShaderDesc
{
    const char* name = nullptr;
    SHADER_TYPE shader_type = SHADER_TYPE_UNKNOWN;

    constexpr ShaderDesc() noexcept {}
    constexpr ShaderDesc(const char* _name, const SHADER_TYPE& _shader_type) noexcept : name(_name), shader_type(_shader_type) {}

    bool operator==(const ShaderDesc& rhs) const { return this->shader_type == rhs.shader_type && CStrEqual(name, rhs.name); }

    bool operator!=(const ShaderDesc& rhs) const { return *this != rhs; }
};

struct ShaderCreateInfo
{
   private:
    // the source file path or the bytecode filepath, ignore when bytecode or source not null
    const char* file_path = nullptr;
    // load bytecode from file
    const bool load_bytecode = false;

    // shader source code, ignore when bytecode not null
    const char* source = nullptr;
    const void* bytecode = nullptr;
    union
    {
        std::size_t source_length = 0;
        std::size_t bytecode_length;
    };

    const char* entry = nullptr;

    const ShaderMacro* macro = nullptr;

    ShaderDesc desc;

   public:
    void InitASCompileFromeSourceFile(const char* file_path, const char* entry = "SDMain", const ShaderMacro* macro = nullptr)
    {
        this->file_path = file_path;
        this->entry = entry;
        this->macro = macro;
    }

    void InitASCompileFromSourceCode(const char* source_code, const std::size_t& len, const char* entry = "SDMain",
                                     const ShaderMacro* macro = nullptr)
    {
        this->source = source_code;
        this->source_length = len;

        this->entry = entry;
        this->macro = macro;
    }

    void InitASByteCode(const void* bytecode, const std::size_t& len)
    {
        this->bytecode = bytecode;
        this->bytecode_length = len;
    }
};

class IShader : public Engine::IObject, public Engine::NoCopy
{
   public:
    virtual const ShaderDesc& GetDesc() const = 0;
};
}  // namespace Toy::Graphics