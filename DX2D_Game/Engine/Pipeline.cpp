#include <d3d11.h>
#include <assert.h>

#include "Pipeline.h"

#if not defined _DEBUG
#define MUST(Expression) (((Expression)))
#else
#define MUST(Expression) (assert(SUCCEEDED(Expression)))
#endif

namespace Pipeline
{
	namespace
	{
		ID3D11Device        * Device;
		ID3D11DeviceContext * DeviceContext;
		IDXGISwapChain      * SwapChain;

		namespace Buffer
		{
			ID3D11Buffer* Vertex;
			ID3D11Buffer* Constant[2];

			template<typename Data>
			void Update(ID3D11Buffer * buffer, Data const & data)
			{
				D3D11_MAPPED_SUBRESOURCE subResource = D3D11_MAPPED_SUBRESOURCE();

				MUST(DeviceContext->Map(buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &subResource));
				{ memcpy_s(subResource.pData, subResource.RowPitch, data, sizeof(data)); }
				DeviceContext->Unmap(buffer, 0);
			}
		}

		ID3D11RenderTargetView * RenderTargetView;
	}

	namespace String
	{
		void Render(HFONT const hFont, LPCSTR const string, COLORREF const color, SIZE const size, POINT const center)
		{
			IDXGISurface1 * surface = nullptr;

			MUST(SwapChain->GetBuffer(0, IID_PPV_ARGS(&surface)));
			{
				HDC hDC = HDC();

				MUST(surface->GetDC(false, &hDC));
				{

				}
				MUST(surface->ReleaseDC(nullptr));
			}
			surface->Release();
			DeviceContext->OMSetRenderTargets(1, &RenderTargetView, nullptr);
		}
	}

	namespace Texture
	{
		struct Handle final
		{ ID3D11ShaderResourceView * ShaderResourceView = nullptr; };

		void Create(Handle *& handle, SIZE const size, BYTE const * const data)
		{
			D3D11_TEXTURE2D_DESC const descriptor
			{
				static_cast<UINT>(size.cx),
				static_cast<UINT>(size.cy),
				1,
				1,
				DXGI_FORMAT_B8G8R8A8_UNORM,
				1,
				0,
				D3D11_USAGE_IMMUTABLE,
				D3D11_BIND_SHADER_RESOURCE
			};

			UINT constexpr bPP = 32;

			D3D11_SUBRESOURCE_DATA const subResource
			{
				data,
				size.cx * bPP / 8
			};

			ID3D11Texture2D * texture2D = nullptr;

			MUST(Device->CreateTexture2D(&descriptor, &subResource, &texture2D));
			{ MUST(Device->CreateShaderResourceView(texture2D, nullptr, &(handle = new Handle())->ShaderResourceView)); }
			texture2D->Release();
		}

		void Render(Handle const * const & handle, RECT const area)
		{
			{
				DeviceContext->PSSetShaderResources(0, 1, &handle->ShaderResourceView);

				float const Coordinatas[4][2]
				{
					{ static_cast<float>(area.left) , static_cast<float>(area.top)    },
					{ static_cast<float>(area.right), static_cast<float>(area.top)    },
					{ static_cast<float>(area.left) , static_cast<float>(area.bottom) },
					{ static_cast<float>(area.right), static_cast<float>(area.bottom) }
				};
				Buffer::Update(Buffer::Vertex, Coordinatas);
			}
			DeviceContext->Draw(4, 0);
		}

		void Delete(Handle const * const & handle)
		{
			handle->ShaderResourceView->Release();
			delete handle;
		}
	}

	namespace Transform
	{
		template<Type type>
		void Update(matrix const& matrix)
		{ Buffer::Update(Buffer::Constant[static_cast<UINT>(type)], matrix); }

		template void Update<Type::Formar>(matrix const & matrix);
		template void Update<Type::Latter>(matrix const & matrix);
	}

	void Procedure(HWND const hWindow, UINT const uMessage, WPARAM const wParam, LPARAM const lParam)
	{
		switch (uMessage)
		{
			case WM_APP:
			{
				MUST(SwapChain->Present(0, 0));

				float const color[4]{ 0.0f, 0.0f, 0.0f, 1.0f };

				DeviceContext->ClearRenderTargetView(RenderTargetView, color);

				return;
			}
			case WM_SIZE:
			{
				{
					D3D11_VIEWPORT viewport = D3D11_VIEWPORT();
					viewport.Width  = LOWORD(lParam);
					viewport.Height = HIWORD(lParam);

					DeviceContext->RSSetViewports(1, &viewport);
				}
				{
					if (RenderTargetView != nullptr)
					{
						RenderTargetView->Release();
						MUST(SwapChain->ResizeBuffers
						(
							1,
							LOWORD(lParam),
							HIWORD(lParam),
							DXGI_FORMAT_B8G8R8A8_UNORM,
							DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE
						));
					}
				}
				{
					ID3D11Texture2D * texture2D = nullptr;

					MUST(SwapChain->GetBuffer(0, IID_PPV_ARGS(&texture2D)));
					{
						IDXGISurface1 * surface = nullptr;
						MUST(texture2D->QueryInterface(IID_PPV_ARGS(&surface)));
						{
							HDC hDC = HDC();
							MUST(surface->GetDC(false, &hDC));
							{ SetBkMode(hDC, TRANSPARENT); }
							MUST(surface->ReleaseDC(nullptr));
						}
						surface->Release();
							
						MUST(Device->CreateRenderTargetView(texture2D, nullptr, &RenderTargetView));

						DeviceContext->OMSetRenderTargets(1, &RenderTargetView, nullptr);
					}
					texture2D->Release();
				}
				return;
			}
			case WM_CREATE:
			{
				{
					DXGI_SWAP_CHAIN_DESC descriptor = DXGI_SWAP_CHAIN_DESC();

					descriptor.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
					descriptor.SampleDesc.Count  = 1;
					descriptor.BufferUsage       = DXGI_USAGE_RENDER_TARGET_OUTPUT;
					descriptor.BufferCount       = 1;
					descriptor.OutputWindow      = hWindow;
					descriptor.Windowed          = true;
					descriptor.Flags             = DXGI_SWAP_CHAIN_FLAG_GDI_COMPATIBLE;

					MUST(D3D11CreateDeviceAndSwapChain
					(
						nullptr,
						D3D_DRIVER_TYPE_HARDWARE,
						nullptr,
						0,
						nullptr,
						0,
						D3D11_SDK_VERSION,
						&descriptor,
						&SwapChain,
						&Device,
						nullptr,
						&DeviceContext
					));
				}
				{
#include "Shader/Bytecode/Vertex.h"
					{
						D3D11_INPUT_ELEMENT_DESC const descriptor[2]
						{
							{ "POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0 },
							{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 1 }
						};

						ID3D11InputLayout * inputLayout = nullptr;

						MUST(Device->CreateInputLayout(descriptor, 2, Bytecode, sizeof(Bytecode), &inputLayout));

						DeviceContext->IASetInputLayout(inputLayout);

						inputLayout->Release();
					}
					{
						ID3D11VertexShader * vertexShader = nullptr;

						MUST(Device->CreateVertexShader(Bytecode, sizeof(Bytecode), nullptr, &vertexShader));

						DeviceContext->VSSetShader(vertexShader, nullptr, 0);

						vertexShader->Release();
					}
				}
				{
#include "Shader/Bytecode/Pixel.h"
					{
						ID3D11PixelShader * pixelShader = nullptr;

						MUST(Device->CreatePixelShader(Bytecode, sizeof(Bytecode), nullptr, &pixelShader));

						DeviceContext->PSSetShader(pixelShader, nullptr, 0);

						pixelShader->Release();
					}
				}
				{
					D3D11_BLEND_DESC descriptor = D3D11_BLEND_DESC();

					descriptor.RenderTarget->BlendEnable           = true;
					descriptor.RenderTarget->SrcBlend              = D3D11_BLEND_SRC_ALPHA;
					descriptor.RenderTarget->DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;
					descriptor.RenderTarget->BlendOp               = D3D11_BLEND_OP_ADD;
					descriptor.RenderTarget->SrcBlendAlpha         = D3D11_BLEND_ZERO;
					descriptor.RenderTarget->DestBlendAlpha        = D3D11_BLEND_ONE;
					descriptor.RenderTarget->BlendOpAlpha          = D3D11_BLEND_OP_ADD;
					descriptor.RenderTarget->RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

					ID3D11BlendState * blendState = nullptr;
					MUST(Device->CreateBlendState(&descriptor, &blendState));

					DeviceContext->OMSetBlendState(blendState, nullptr, D3D11_DEFAULT_SAMPLE_MASK);
				}
				{
					
					float const coordinates[4][2]
					{
						{ -0.5f , +0.5f }, 
						{ +0.5f , +0.5f }, 
						{ -0.5f , -0.5f }, 
						{ +0.5f , -0.5f }	
					};

					D3D11_BUFFER_DESC const Descriptor
					{
						sizeof(coordinates),
						D3D11_USAGE_IMMUTABLE,
						D3D11_BIND_VERTEX_BUFFER
					};

					D3D11_SUBRESOURCE_DATA const subResourece{ coordinates };

					ID3D11Buffer * buffer = nullptr;

					MUST(Device->CreateBuffer(&Descriptor, &subResourece, &buffer));

					UINT const stride = sizeof(*coordinates);
					UINT const offset = 0;

					DeviceContext->IASetVertexBuffers(0, 1, &buffer, &stride, &offset);

					buffer->Release();
				}
				{
					D3D11_BUFFER_DESC const Descriptor
					{
						sizeof(float[4][2]),
						D3D11_USAGE_DYNAMIC,
						D3D11_BIND_VERTEX_BUFFER,
						D3D11_CPU_ACCESS_WRITE
					};

					MUST(Device->CreateBuffer(&Descriptor, nullptr, &Buffer::Vertex));

					UINT const stride = sizeof(float[2]);
					UINT const offset = 0;

					DeviceContext->IASetVertexBuffers(1, 1, &Buffer::Vertex, &stride, &offset);
				}
				{
					DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
				}
				{
					D3D11_BUFFER_DESC Descriptor
					{
						sizeof(float[4][4]),
						D3D11_USAGE_DYNAMIC,
						D3D11_BIND_CONSTANT_BUFFER,
						D3D11_CPU_ACCESS_WRITE
					};

					for (UINT i = 0; i < 2; ++i)
						MUST(Device->CreateBuffer(&Descriptor, nullptr, &Buffer::Constant[i]));

					DeviceContext->VSSetConstantBuffers(0, 2, Buffer::Constant);
				}
				return;
			}
			case WM_DESTROY:
			{
				RenderTargetView->Release();

				SwapChain->Release();
				DeviceContext->Release();
				Device->Release();
				return;
			}
		}
	}
}