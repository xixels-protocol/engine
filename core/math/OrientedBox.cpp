#include "Frustum.h"
#include "OrientedBox.h"

using namespace Xixels;

OrientedBox& OrientedBox::Build( const Vector3& vmin, const Vector3& vmax )
{
	vs[0] = Vector3( vmin.x, vmin.y, vmin.z );
	vs[1] = Vector3( vmax.x, vmin.y, vmin.z );
	vs[2] = Vector3( vmin.x, vmax.y, vmin.z );
	vs[3] = Vector3( vmax.x, vmax.y, vmin.z );
	vs[4] = Vector3( vmin.x, vmin.y, vmax.z );
	vs[5] = Vector3( vmax.x, vmin.y, vmax.z );
	vs[6] = Vector3( vmin.x, vmax.y, vmax.z );
	vs[7] = Vector3( vmax.x, vmax.y, vmax.z );

	return *this;
}

OrientedBox& OrientedBox::Build( const Matrix4& projinv, _float begin, _float end )
{
	HomogenousFrustum hfrustum( projinv );

	Vector3 righttop( hfrustum.mRightSlope, hfrustum.mTopSlope, 1.0f );
	Vector3 leftbottom( hfrustum.mLeftSlope, hfrustum.mBottomSlope, 1.0f );
	Vector3 nearv( begin, begin, begin );
	Vector3 farv( end, end, end );

	Vector3 righttopnear = righttop * nearv;
	Vector3 righttopfar = righttop * farv;
	Vector3 leftbottomnear = leftbottom * nearv;
	Vector3 leftbottomfar = leftbottom * farv;

	vs[0] = righttopnear;
	vs[1] = righttopnear; vs[1].x = leftbottomnear.x;
	vs[2] = leftbottomnear;
	vs[3] = righttopnear; vs[3].y = leftbottomnear.y;

	vs[4] = righttopfar;
	vs[5] = righttopfar; vs[5].x = leftbottomfar.x;
	vs[6] = leftbottomfar;
	vs[7] = righttopfar; vs[7].y = leftbottomfar.y;

	return *this;
}

_void OrientedBox::ComputeMinMax( Vector3& frustummin, Vector3& frustummax )
{
	frustummin = Vector3( Math::cMaxFloat, Math::cMaxFloat, Math::cMaxFloat );
	frustummax = Vector3( Math::cMinFloat, Math::cMinFloat, Math::cMinFloat );

	// Transform the frustum from camera view space to world space.
	for ( _dword j = 0; j < 8; j ++ )
	{
		Vector3 temp = vs[j];

		frustummin = Vector3::Min( temp, frustummin );
		frustummax = Vector3::Max( temp, frustummax );
	}
}