#pragma once

namespace Xixels
{

class Material
{
public:
	// The empty material.
	const static Material cNull;

public:
	Color	diffuse;
	Color	specular;
	Color	emissive;
	_float	roughness;
	_float	metallic;

public:
	inline Material( )
		: Material( Color::cWhite ) { }
	inline Material( const Color& d )
		: diffuse( d ), specular( Color::cBlack ), emissive( Color::cBlack ), roughness( 1.0f ), metallic( 0.0f ) { }
	inline Material( const Color& d, const Color& s, const Color& e, _float r, _float m )
		: diffuse( d ), specular( s ), emissive( e ), roughness( r ), metallic( m ) { }

	inline _bool operator == ( const Material& m ) const
		{ return diffuse == m.diffuse && specular == m.specular && emissive == m.emissive && roughness == m.roughness && metallic == m.metallic; }
	inline _bool operator != ( const Material& m ) const
		{ return diffuse != m.diffuse || specular != m.specular || emissive != m.emissive || roughness != m.roughness || metallic != m.metallic; }

	static Material Lerp( const Material& c1, const Material& c2, _float f );
};

};