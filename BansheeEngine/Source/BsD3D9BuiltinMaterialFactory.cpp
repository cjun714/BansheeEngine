#include "BsD3D9BuiltinMaterialFactory.h"
#include "CmHighLevelGpuProgram.h"
#include "CmShader.h"
#include "CmTechnique.h"
#include "CmPass.h"
#include "CmMaterial.h"
#include "CmBlendState.h"
#include "CmRendererManager.h"

using namespace CamelotFramework;

namespace BansheeEngine
{
	void D3D9BuiltinMaterialFactory::startUp()
	{
		initSpriteTextShader();
		initSpriteImageShader();
	}

	void D3D9BuiltinMaterialFactory::shutDown()
	{
		mSpriteTextShader = nullptr;
		mSpriteImageShader = nullptr;
	}

	const CM::String& D3D9BuiltinMaterialFactory::getSupportedRenderSystem() const
	{
		static String renderSystem = "CamelotD3D9RenderSystem";

		return renderSystem;
	}

	HMaterial D3D9BuiltinMaterialFactory::createSpriteTextMaterial() const
	{
		return Material::create(mSpriteTextShader);
	}

	HMaterial D3D9BuiltinMaterialFactory::createSpriteImageMaterial() const
	{
		return Material::create(mSpriteImageShader);
	}


	void D3D9BuiltinMaterialFactory::initSpriteTextShader()
	{
		String vsCode = "										\
			float halfViewportWidth;							\
			float halfViewportHeight;							\
			float4x4 worldTransform;							\
																\
			void vs_main(										\
			in float3 inPos : POSITION,							\
			in float2 uv : TEXCOORD0,							\
			out float4 oPosition : POSITION,					\
			out float2 oUv : TEXCOORD0)							\
			{													\
				float4 tfrmdPos = mul(worldTransform, float4(inPos.xy, 0, 1));	\
																\
				float tfrmdX = ((tfrmdPos.x - 0.5f) / halfViewportWidth) - 1.0f;			\
				float tfrmdY = ((tfrmdPos.y + 0.5f) / halfViewportHeight) + 1.0f;		\
																\
				oPosition = float4(tfrmdX, tfrmdY, 0, 1);		\
				oUv = uv;										\
			}													\
			";

		String psCode = "																\
			sampler2D mainTexture;														\
																						\
			float4 ps_main(float2 uv : TEXCOORD0) : COLOR0								\
			{																			\
				float4 color = float4(1.0f, 1.0f, 1.0f, tex2D(mainTexture, uv).r);		\
				return color;															\
			}";

		HHighLevelGpuProgram vsProgram = HighLevelGpuProgram::create(vsCode, "vs_main", "hlsl", GPT_VERTEX_PROGRAM, GPP_VS_3_0);
		HHighLevelGpuProgram psProgram = HighLevelGpuProgram::create(psCode, "ps_main", "hlsl", GPT_FRAGMENT_PROGRAM, GPP_PS_3_0);

		vsProgram.waitUntilLoaded();
		psProgram.waitUntilLoaded();

		mSpriteTextShader = Shader::create("TextSpriteShader");

		mSpriteTextShader->addParameter("worldTransform", "worldTransform", GPDT_MATRIX_4X4);
		mSpriteTextShader->addParameter("halfViewportWidth", "halfViewportWidth", GPDT_FLOAT1);
		mSpriteTextShader->addParameter("halfViewportHeight", "halfViewportHeight", GPDT_FLOAT1);
		mSpriteTextShader->addParameter("mainTexSamp", "mainTexture", GPOT_SAMPLER2D);
		mSpriteTextShader->addParameter("mainTexture", "mainTexture", GPOT_TEXTURE2D);

		TechniquePtr newTechnique = mSpriteTextShader->addTechnique("D3D9RenderSystem", RendererManager::getCoreRendererName()); 
		PassPtr newPass = newTechnique->addPass();
		newPass->setVertexProgram(vsProgram);
		newPass->setFragmentProgram(psProgram);

		BLEND_STATE_DESC desc;
		desc.renderTargetDesc[0].blendEnable = true;
		desc.renderTargetDesc[0].srcBlend = BF_SOURCE_ALPHA;
		desc.renderTargetDesc[0].dstBlend = BF_INV_SOURCE_ALPHA;
		desc.renderTargetDesc[0].blendOp = BO_ADD;

		HBlendState blendState = BlendState::create(desc);
		newPass->setBlendState(blendState);
	}

	void D3D9BuiltinMaterialFactory::initSpriteImageShader()
	{
		String vsCode = "										\
						float halfViewportWidth;							\
						float halfViewportHeight;							\
						float4x4 worldTransform;							\
						\
						void vs_main(										\
						in float3 inPos : POSITION,							\
						in float2 uv : TEXCOORD0,							\
						out float4 oPosition : POSITION,					\
						out float2 oUv : TEXCOORD0)							\
						{													\
						float4 tfrmdPos = mul(worldTransform, float4(inPos.xy, 0, 1));	\
						\
						float tfrmdX = ((tfrmdPos.x - 0.5f) / halfViewportWidth) - 1.0f;			\
						float tfrmdY = ((tfrmdPos.y + 0.5f) / halfViewportHeight) + 1.0f;		\
						\
						oPosition = float4(tfrmdX, tfrmdY, 0, 1);		\
						oUv = uv;										\
						}													\
						";

		String psCode = "												\
						sampler2D mainTexture;							\
						\
						float4 ps_main(float2 uv : TEXCOORD0) : COLOR0	\
						{												\
						float4 color = tex2D(mainTexture, uv);			\
						return color;									\
						}";

		HHighLevelGpuProgram vsProgram = HighLevelGpuProgram::create(vsCode, "vs_main", "hlsl", GPT_VERTEX_PROGRAM, GPP_VS_2_0);
		HHighLevelGpuProgram psProgram = HighLevelGpuProgram::create(psCode, "ps_main", "hlsl", GPT_FRAGMENT_PROGRAM, GPP_PS_2_0);

		vsProgram.waitUntilLoaded();
		psProgram.waitUntilLoaded();

		mSpriteImageShader = Shader::create("ImageSpriteShader");

		mSpriteImageShader->addParameter("worldTransform", "worldTransform", GPDT_MATRIX_4X4);
		mSpriteImageShader->addParameter("halfViewportWidth", "halfViewportWidth", GPDT_FLOAT1);
		mSpriteImageShader->addParameter("halfViewportHeight", "halfViewportHeight", GPDT_FLOAT1);
		mSpriteImageShader->addParameter("mainTexSamp", "mainTexture", GPOT_SAMPLER2D);
		mSpriteImageShader->addParameter("mainTexture", "mainTexture", GPOT_TEXTURE2D);

		TechniquePtr newTechnique = mSpriteImageShader->addTechnique("D3D9RenderSystem", RendererManager::getCoreRendererName()); 
		PassPtr newPass = newTechnique->addPass();
		newPass->setVertexProgram(vsProgram);
		newPass->setFragmentProgram(psProgram);

		BLEND_STATE_DESC desc;
		desc.renderTargetDesc[0].blendEnable = true;
		desc.renderTargetDesc[0].srcBlend = BF_SOURCE_ALPHA;
		desc.renderTargetDesc[0].dstBlend = BF_INV_SOURCE_ALPHA;
		desc.renderTargetDesc[0].blendOp = BO_ADD;

		HBlendState blendState = BlendState::create(desc);
		newPass->setBlendState(blendState);
	}
}