#include "Game/Draw.h"
#include <nn/math/math_Matrix34.h>
#include <nn/math/math_Matrix44.h>
#include <nn/math/math_Vector3.h>
#include <nn/ulcd/CTR/ulcd_StereoCamera.h>
#include "png.h"

//Global cliprect
RECT split(grcFull) = { 0, 0, SURFACE_WIDTH, SURFACE_HEIGHT };

void PutBitmap3(const RECT *rcView, int x, int y, const RECT *rect, int surf_no, int a6){
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, 0, 0);
    png_create_info_struct(png);
}

//Setup the stereo camera for 3D drawing
extern "C" void InitStereoCamera(nn::ulcd::CTR::StereoCamera *camera)
{
	nn::math::MTX34 base_camera;
	nn::math::MTX34 *pBase = &base_camera;
	nn::math::MTX44 proj_l, proj_r;
	nn::math::MTX34 view_l, view_r;

	nn::math::ARMv6::MTX34CopyAsm(pBase, &nn::math::MTX34::Identity());
	camera->SetBaseCamera(&base_camera);
	camera->SetBaseFrustum(-0.04f, 0.04f, -(0.04f / 5.0f * 3.0f), 0.04f / 5.0f * 3.0f, 0.1f, 1000.0f);

	camera->CalculateMatrices(&proj_l, &view_l, &proj_r, &view_r, 10.0f, 0.3f, nn::math::PIVOT_UPSIDE_TO_TOP);
}