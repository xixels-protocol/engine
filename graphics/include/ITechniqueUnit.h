#pragma once

namespace Xixels
{

class ITechniqueUnit
{
public:
	virtual ITechniqueUnit&	Clone( ) = 0;

	virtual _void			EnableTechnique( ITechniqueUnit& oldtech, const Vector4* vcskin, _dword vcskincount, _bool instancing, _bool post ) const = 0;
	virtual _void			DisableTechnique( ) = 0;
	virtual _void			ClearTechnique( ) = 0;
};

};