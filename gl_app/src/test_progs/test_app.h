#pragma once

#include "camera.h"

//class Camera;
class Window;
class Layer;

class TestAppMgr
{
public:

	TestAppMgr(Window& window, Camera& camera, v2::Camera& camera2);
	Layer* GetLayer(uint32_t id);

	enum
	{
		COORD_SYS_CAM1,
		COORD_SYS_CAM2,

		LGL_TEXTURE_TEST,
		LGL_TEXTURES_COMBINED_TEST,

		LGL_BASIC_LIGHTING_COLOURS,
		LGL_BASIC_LIGHTING_DIFFUSE,
		LGL_BASIC_LIGHTING_SPECULAR,
		LGL_MATERIALS_TEST,
		LGL_LIGHT_MAP_DIFFUSE,
		LGL_LIGHT_MAP_SPECULAR,
		LGL_LIGHT_MAP_EMISSION,
		LGL_LIGHT_CASTER_DIRECTIONAL,
		LGL_LIGHT_CASTER_POINT,
		LGL_LIGHT_CASTER_SPOT,
		LGL_LIGHT_CASTER_SPOT_SOFT,
		LGL_MULTIPLE_LIGHTS,

		LGL_MODEL_LOADING_TEST,

		LGL_DEPTH_TESTING,
		LGL_DEPTH_TESTING_VIEW,
		LGL_STENCIL_TESTING,
		LGL_BLEND_DISCARD_TESTING,
		LGL_BLEND_SORT_TESTING,
		LGL_FACE_CULLING,
		LGL_FRAME_BUFFER_TEST,
		LGL_SKYBOX,
		LGL_ENV_MAPPING,
		LGL_ADVANCED_GLSL_UBO,
		LGL_GEOMETRY_SHADER_HOUSES,
		LGL_GEOMETRY_SHADER_EXPLODING,
		LGL_NORMAL_VISUALISATION,
		LGL_INSTANCING_QUADS,
		LGL_ASTEROIDS,
		LGL_ASTEROIDS_INSTANCED,
		LGL_ANTI_ALIASING_MSAA,
		LGL_ANTI_ALIASING_OFFSCREEN,

		LGL_ADVANCED_LIGHTING,
		LGL_GAMMA_CORRECTION,
		LGL_SHADOW_MAPPING_DEPTH,
		LGL_SHADOW_MAPPING_BASE,
		LGL_SHADOW_MAPPING,
		LGL_POINT_SHADOW,
		LGL_POINT_SHADOW_SOFT,
		LGL_NORMAL_MAPPING,
		LGL_PARALLAX_MAPPING,
		LGL_PARALLAX_MAPPING_MULTI_SAMPLE,
		LGL_PARALLAX_OCCLUSION_MAPPING,
		LGL_HDR,
		LGL_BLOOM,
		LGL_DEFERRED_SHADING,
		LGL_SCREEN_SPACE_AMBIENT_OCCLUSION,

		LGL_TEXT_RENDERING,

		LGL_SKELETAL_ANIMATION,
		LGL_CSM,
		LGL_SCENE_GRAPH,
		LGL_HEIGHT_MAP_CPU,
		LGL_HEIGHT_MAP_TESSELATION,
		
		SB7_POINT,
		SB7_TRIANGLE,
		SB7_MOVING_TRIANGLE,
		SB7_TESSELATED_TRIANGLE,
		SB7_GEOM_TRIANGLE,
		SB7_CH5_VERTEX_ARRAYS,

		MISC_ANIMATED_MODEL_BASIC,
		MISC_COMP_GEOM,
		MISC_DIR_SHADOW_VISUALISED,
		MISC_DIR_SHADOW_VISUALISED2,
		MISC_CSM_VISUALISED
	};

private:
	Camera& m_camera;
	v2::Camera& m_camera2;
	Window& m_window;
};
