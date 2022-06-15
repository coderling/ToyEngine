#pragma once

#include <DirectXMath.h>
#include <atlconv.h>
#include <d3dcompiler.h>
#include <wrl.h>
#include <GlobalEnvironment.hpp>
#include <IApp.hpp>
#include <IGraphicsCommandList.hpp>
#include <IPipelineFragmentHandler.hpp>
#include <iostream>
#include "EngineUtility.hpp"
#include "IUploadBuffer.hpp"
#include "Utility.hpp"
#include "d3dx12.h"

using namespace Microsoft::WRL;
using namespace Toy::Graphics;
using namespace DirectX;
struct Vertex
{
    XMFLOAT3 position;
    XMFLOAT4 color;
};

class RenderLogic : public Toy::Graphics::IPipelineFragmentHandler
{
   public:
    void Load() override
    {
        std::cout << "RenderLogic::Load" << std::endl;
        cmd_list = Toy::Graphics::IGraphicsCommandList::Create(0, COMMAND_LIST_TYPE::D3D12_COMMAND_LIST_TYPE_DIRECT);

        // rootsignature
        CD3DX12_ROOT_SIGNATURE_DESC root_signature_desc;
        root_signature_desc.Init(0, nullptr, 0, nullptr, D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT);
        ComPtr<ID3DBlob> signature;
        ComPtr<ID3DBlob> error;
        ASSERT_SUCCEEDED(D3D12SerializeRootSignature(&root_signature_desc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error));
        auto device = Toy::Engine::IApp::env->GetGraphics()->GetDevice();
        ASSERT_SUCCEEDED(
            device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), MY_IID_PPV_ARGS(&root_signature)));

        // shader
        ComPtr<ID3DBlob> vertex_shader;
        ComPtr<ID3DBlob> pixel_shader;

#if defined(_DEBUG)
        UINT compileflags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
        UINT compileflags = 0;
#endif
        const auto& app_args = Toy::Engine::IApp::env->GetApp()->GetArgs();
        const auto& data_path = app_args->data_path;
        std::string shader_path = data_path + "/shaders/shaders.hlsl";
        const auto wpath = Toy::s2ws(shader_path);
        ASSERT_SUCCEEDED(D3DCompileFromFile(wpath.c_str(), nullptr, nullptr, "VSMain", "vs_5_0", compileflags, 0, &vertex_shader, nullptr));
        ASSERT_SUCCEEDED(D3DCompileFromFile(wpath.c_str(), nullptr, nullptr, "PSMain", "ps_5_0", compileflags, 0, &pixel_shader, nullptr));

        // vertex input layout define
        D3D12_INPUT_ELEMENT_DESC input_element_descs[] = {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
            {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}};

        // describe and pipeline state object
        D3D12_GRAPHICS_PIPELINE_STATE_DESC pso_desc = {};
        pso_desc.InputLayout = {input_element_descs, _countof(input_element_descs)};
        pso_desc.pRootSignature = root_signature.Get();
        pso_desc.VS = CD3DX12_SHADER_BYTECODE(vertex_shader.Get());
        pso_desc.PS = CD3DX12_SHADER_BYTECODE(pixel_shader.Get());
        pso_desc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
        pso_desc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
        pso_desc.DepthStencilState.DepthEnable = FALSE;
        pso_desc.DepthStencilState.StencilEnable = FALSE;
        pso_desc.SampleMask = UINT_MAX;
        pso_desc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
        pso_desc.NumRenderTargets = 1;
        pso_desc.RTVFormats[0] = DXGI_FORMAT_R8G8B8A8_UNORM;
        pso_desc.SampleDesc.Count = 1;

        ASSERT_SUCCEEDED(device->CreateGraphicsPipelineState(&pso_desc, MY_IID_PPV_ARGS(&pipeline_state)));

        // triangle verties
        float aspect_ratio = static_cast<float>(app_args->screen_width) / static_cast<float>(app_args->screen_height);
        Vertex triangle_verties[] = {
            {{0.0f, 0.25f * aspect_ratio, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
            {{0.25f, -0.25f * aspect_ratio, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
            {{-0.25f, -0.25f * aspect_ratio, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
        };

        const UINT vertex_buffer_size = sizeof(triangle_verties);
        vertex_upbuffer = Toy::Graphics::IUploadBuffer::Create("VertexBuffer", vertex_buffer_size);
        UINT8* pbuffer = (UINT8*)vertex_upbuffer->Map();
        memcpy(pbuffer, triangle_verties, vertex_buffer_size);
        vertex_upbuffer->UnMap();

        // vertex buffer view
        vertex_buffer_view.BufferLocation = vertex_upbuffer->GetGpuVirtualAddress();
        vertex_buffer_view.StrideInBytes = sizeof(Vertex);
        vertex_buffer_view.SizeInBytes = vertex_buffer_size;

        // synchronization objects until have been uploaded to GPU
        Toy::Engine::IApp::env->GetGraphics()->WaitForGpu();

        view_port = CD3DX12_VIEWPORT(0.0f, 0.0f, static_cast<float>(app_args->screen_width), static_cast<float>(app_args->screen_height));
        scissor_rect = CD3DX12_RECT(0, 0, static_cast<LONG>(app_args->screen_width), static_cast<LONG>(app_args->screen_height));
    }

    void Render() override
    {
        std::cout << "RenderLogic::OnRender()" << std::endl;
        cmd_list->Reset();
        const auto raw_cmd_list = cmd_list->GetCmdList();
        raw_cmd_list->SetPipelineState(pipeline_state.Get());
        raw_cmd_list->SetGraphicsRootSignature(root_signature.Get());
        raw_cmd_list->RSSetViewports(1, &view_port);
        raw_cmd_list->RSSetScissorRects(1, &scissor_rect);

        // backbuffer set as rendertarget state
    }

    void Unload() override { std::cout << "RenderLogic::Unload()" << std::endl; }

   protected:
    void OnDestroy() override { std::cout << "RenderLogic::Destroy()" << std::endl; }

   private:
    std::unique_ptr<Toy::Graphics::IGraphicsCommandList> cmd_list;
    ComPtr<ID3D12RootSignature> root_signature;
    ComPtr<ID3D12DescriptorHeap> rtv_heap;
    ComPtr<ID3D12PipelineState> pipeline_state;
    CD3DX12_VIEWPORT view_port;
    CD3DX12_RECT scissor_rect;

    std::unique_ptr<IUploadBuffer> vertex_upbuffer;
    ComPtr<ID3D12Resource> vertex_buffer;
    D3D12_VERTEX_BUFFER_VIEW vertex_buffer_view;
};
