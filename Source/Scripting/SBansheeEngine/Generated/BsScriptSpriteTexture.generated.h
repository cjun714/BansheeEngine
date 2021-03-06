#pragma once

#include "BsScriptEnginePrerequisites.h"
#include "Wrappers/BsScriptResource.h"
#include "Math/BsVector2.h"
#include "../../../bsf/Source/Foundation/bsfCore/Image/BsSpriteTexture.h"
#include "../../../bsf/Source/Foundation/bsfCore/Image/BsSpriteTexture.h"

namespace bs
{
	class SpriteTexture;

	class BS_SCR_BE_EXPORT ScriptSpriteTexture : public TScriptResource<ScriptSpriteTexture, SpriteTexture>
	{
	public:
		SCRIPT_OBJ(ENGINE_ASSEMBLY, "BansheeEngine", "SpriteTexture")

		ScriptSpriteTexture(MonoObject* managedInstance, const ResourceHandle<SpriteTexture>& value);

		static MonoObject* createInstance();

	private:
		static MonoObject* Internal_getRef(ScriptSpriteTexture* thisPtr);

		static void Internal_setTexture(ScriptSpriteTexture* thisPtr, MonoObject* texture);
		static MonoObject* Internal_getTexture(ScriptSpriteTexture* thisPtr);
		static uint32_t Internal_getWidth(ScriptSpriteTexture* thisPtr);
		static uint32_t Internal_getHeight(ScriptSpriteTexture* thisPtr);
		static void Internal_setOffset(ScriptSpriteTexture* thisPtr, Vector2* offset);
		static void Internal_getOffset(ScriptSpriteTexture* thisPtr, Vector2* __output);
		static void Internal_setScale(ScriptSpriteTexture* thisPtr, Vector2* scale);
		static void Internal_getScale(ScriptSpriteTexture* thisPtr, Vector2* __output);
		static void Internal_setAnimation(ScriptSpriteTexture* thisPtr, SpriteSheetGridAnimation* anim);
		static void Internal_getAnimation(ScriptSpriteTexture* thisPtr, SpriteSheetGridAnimation* __output);
		static void Internal_setAnimationPlayback(ScriptSpriteTexture* thisPtr, SpriteAnimationPlayback playback);
		static SpriteAnimationPlayback Internal_getAnimationPlayback(ScriptSpriteTexture* thisPtr);
		static void Internal_create(MonoObject* managedInstance, MonoObject* texture);
		static void Internal_create0(MonoObject* managedInstance, Vector2* uvOffset, Vector2* uvScale, MonoObject* texture);
	};
}
