#pragma once

namespace Xixels
{

template< typename Type > class QuadTree
{
public:
	class RootNode;
	class LeafNode;

	class QuadNode
	{
	public:
		Region		mRegion;
		RootNode*	mParent;

	public:
		inline QuadNode( const Region& r, RootNode* p ) : mRegion( r ), mParent( p )
			{ }

		virtual ~QuadNode( )
			{ }

		virtual QuadNode* FirstChild( ) const = 0;
		virtual _bool FindLeaf( const Vector2& p, Array< LeafNode* >& leafs ) = 0;
		virtual _bool FindLeaf( const Region& r, Array< LeafNode* >& leafs ) = 0;
		virtual _bool FindLeaf( const Array< ConvexPolygon >& polygons, Array< LeafNode* >& leafs ) = 0;
		virtual _bool FindLeaf( const SimplePolygon& sp, Array< LeafNode* >& leafs ) = 0;
		virtual _bool FindLeaf( const Vector2& p1, const Vector2& p2, Array< LeafNode* >& leafs ) = 0;
		virtual _void PickLeaf( Array< LeafNode* >& leafs ) = 0;
		virtual _bool IsLeaf( ) = 0;
		virtual _dword GetChildIndex( QuadNode* node ) = 0;
	};

	class RootNode : public QuadNode
	{
	public:
		QuadNode*	mChildNode[4];

	public:
		inline RootNode( const Region& r, RootNode* p ) : QuadNode( r, p )
		{
			mChildNode[0] = _null;
			mChildNode[1] = _null;
			mChildNode[2] = _null;
			mChildNode[3] = _null;
		}

		virtual ~RootNode( )
		{
			delete mChildNode[0];
			delete mChildNode[1];
			delete mChildNode[2];
			delete mChildNode[3];
		}

		virtual QuadNode* FirstChild( ) const
		{
			return mChildNode[0];
		}

		virtual _bool FindLeaf( const Vector2& p, Array< LeafNode* >& leafs )
		{
			// TODO, make it better.

			if ( ( p.x >= QuadNode::mRegion.l && p.x <= QuadNode::mRegion.r && p.y >= QuadNode::mRegion.t && p.y <= QuadNode::mRegion.b ) == _false )
				return _false;

			mChildNode[0]->FindLeaf( p, leafs );
			mChildNode[1]->FindLeaf( p, leafs );
			mChildNode[2]->FindLeaf( p, leafs );
			mChildNode[3]->FindLeaf( p, leafs );

			return _true;
		}

		virtual _bool FindLeaf( const Region& r, Array< LeafNode* >& leafs )
		{
			// TODO, make it better.

			if ( Region::Intersect( QuadNode::mRegion, r ) == Region::cNullRect )
				return _false;

			mChildNode[0]->FindLeaf( r, leafs );
			mChildNode[1]->FindLeaf( r, leafs );
			mChildNode[2]->FindLeaf( r, leafs );
			mChildNode[3]->FindLeaf( r, leafs );

			return _true;
		}

		virtual _bool FindLeaf( const Array< ConvexPolygon >& polygons, Array< LeafNode* >& leafs )
		{
			_bool intersect = _false, includeLT = _false, includeLB = _false, includeRT = _false, includeRB = _false;

			Vector2 lt = Vector2( QuadNode::mRegion.l, QuadNode::mRegion.t );
			Vector2 lb = Vector2( QuadNode::mRegion.l, QuadNode::mRegion.b );
			Vector2 rt = Vector2( QuadNode::mRegion.r, QuadNode::mRegion.t );
			Vector2 rb = Vector2( QuadNode::mRegion.r, QuadNode::mRegion.b );

			for ( _long i = 0; i < polygons.Length( ); i ++ )
			{
				if ( includeLT == _false && polygons[i].Inside( lt ) )
					includeLT = _true;
				if ( includeLB == _false && polygons[i].Inside( lb ) )
					includeLB = _true;
				if ( includeRT == _false && polygons[i].Inside( rt ) )
					includeRT = _true;
				if ( includeRB == _false && polygons[i].Inside( rb ) )
					includeRB = _true;
			}

			if ( includeLT && includeLB && includeRT && includeRB )
			{
				mChildNode[0]->PickLeaf( leafs );
				mChildNode[1]->PickLeaf( leafs );
				mChildNode[2]->PickLeaf( leafs );
				mChildNode[3]->PickLeaf( leafs );

				return _true;
			}

			intersect = includeLT || includeLB || includeRT || includeRB;

			if ( intersect == _false )
			{
				for ( _long i = 0; i < polygons.Length( ); i ++ )
				{
					for ( _dword j = 0; j < polygons[i].pn; j ++ )
					{
						if ( QuadNode::mRegion.Inside( polygons[i].ps[j] ) )
						{
							intersect = _true;
							break;
						}
					}
				}
			}

			if ( intersect == _false )
			{
				for ( _long i = 0; i < polygons.Length( ); i ++ )
				{
					Vector2 lt = Vector2( QuadNode::mRegion.l, QuadNode::mRegion.t );
					Vector2 lb = Vector2( QuadNode::mRegion.l, QuadNode::mRegion.b );
					Vector2 rt = Vector2( QuadNode::mRegion.r, QuadNode::mRegion.t );
					Vector2 rb = Vector2( QuadNode::mRegion.r, QuadNode::mRegion.b );

					if ( polygons[i].Intersect( lt, rt ) ||
						 polygons[i].Intersect( rt, rb ) ||
						 polygons[i].Intersect( rb, lb ) ||
						 polygons[i].Intersect( lb, lt ) )
					{
						intersect = _true;
						break;
					}
				}
			}

			if ( intersect == _false )
				return _false;

			mChildNode[0]->FindLeaf( polygons, leafs );
			mChildNode[1]->FindLeaf( polygons, leafs );
			mChildNode[2]->FindLeaf( polygons, leafs );
			mChildNode[3]->FindLeaf( polygons, leafs );

			return _true;
		}

		virtual _bool FindLeaf( const SimplePolygon& sp, Array< LeafNode* >& leafs )
		{
			if ( sp.Intersect( QuadNode::mRegion ) )
			{
				mChildNode[0]->FindLeaf( sp, leafs );
				mChildNode[1]->FindLeaf( sp, leafs );
				mChildNode[2]->FindLeaf( sp, leafs );
				mChildNode[3]->FindLeaf( sp, leafs );

				return _true;
			}

			return _false;
		}

		virtual _bool FindLeaf( const Vector2& p1, const Vector2& p2, Array< LeafNode* >& leafs )
		{
			_bool found = QuadNode::mRegion.Cross( p1, p2 );

			if ( found == _false && ( QuadNode::mRegion.Inside( p1 ) || QuadNode::mRegion.Inside( p2 ) || QuadNode::mRegion.OnEdge( p1 ) || QuadNode::mRegion.OnEdge( p2 ) ) )
				found = _true;

			if ( found == _false )
				return _false;

			mChildNode[0]->FindLeaf( p1, p2, leafs );
			mChildNode[1]->FindLeaf( p1, p2, leafs );
			mChildNode[2]->FindLeaf( p1, p2, leafs );
			mChildNode[3]->FindLeaf( p1, p2, leafs );

			return _true;
		}

		virtual _void PickLeaf( Array< LeafNode* >& leafs )
		{
			mChildNode[0]->PickLeaf( leafs );
			mChildNode[1]->PickLeaf( leafs );
			mChildNode[2]->PickLeaf( leafs );
			mChildNode[3]->PickLeaf( leafs );
		}

		virtual _bool IsLeaf( )
		{
			return _false;
		}

		virtual _dword GetChildIndex( QuadNode* node )
		{
			for ( _dword i = 0; i < 4; i ++ )
			{
				if ( mChildNode[i] == node )
					return i;
			}

			return -1;
		}

		RootNode* GetNext( ) const
		{
			if ( QuadNode::mParent == _null )
				return _null;

			if ( (RootNode*) QuadNode::mParent->mChildNode[0] == this )
				return (RootNode*) QuadNode::mParent->mChildNode[1];

			if ( (RootNode*) QuadNode::mParent->mChildNode[1] == this )
				return (RootNode*) QuadNode::mParent->mChildNode[2];

			if ( (RootNode*) QuadNode::mParent->mChildNode[2] == this )
				return (RootNode*) QuadNode::mParent->mChildNode[3];

			RootNode* pp = QuadNode::mParent->GetNext( );
			if ( pp == _null )
				return _null;

			return (RootNode*) pp->mChildNode[0];
		}
	};

	class LeafNode : public QuadNode
	{
	public:
		Type		mElement;

	public:
		inline LeafNode( const Region& r, RootNode* p ) : QuadNode( r, p )
			{ }

		virtual QuadNode* FirstChild( ) const
		{
			return _null;
		}

		virtual _bool FindLeaf( const Vector2& p, Array< LeafNode* >& leafs )
		{
			if ( ( p.x >= QuadNode::mRegion.l && p.x <= QuadNode::mRegion.r && p.y >= QuadNode::mRegion.t && p.y <= QuadNode::mRegion.b ) == _false )
				return _false;

			leafs.Add( this );
			return _true;
		}

		virtual _bool FindLeaf( const Region& r, Array< LeafNode* >& leafs )
		{
			if ( Region::Intersect( QuadNode::mRegion, r ) == Region::cNullRect )
				return _false;

			leafs.Add( this );
			return _true;
		}

		virtual _bool FindLeaf( const Array< ConvexPolygon >& polygons, Array< LeafNode* >& leafs )
		{
			for ( _long i = 0; i < polygons.Length( ); i ++ )
			{
				const ConvexPolygon& cp = polygons[i];

				Vector2 lt = Vector2( QuadNode::mRegion.l, QuadNode::mRegion.t );
				Vector2 lb = Vector2( QuadNode::mRegion.l, QuadNode::mRegion.b );
				Vector2 rt = Vector2( QuadNode::mRegion.r, QuadNode::mRegion.t );
				Vector2 rb = Vector2( QuadNode::mRegion.r, QuadNode::mRegion.b );

				if ( cp.Inside( lt ) || cp.Inside( lb ) || cp.Inside( rt ) || cp.Inside( rb ) )
				{
					leafs.Add( this );
					return _true;
				}
			}

			for ( _long i = 0; i < polygons.Length( ); i ++ )
			{
				const ConvexPolygon& cp = polygons[i];

				for ( _dword j = 0; j < cp.pn; j ++ )
				{
					if ( QuadNode::mRegion.Inside( cp.ps[j] ) )
					{
						leafs.Add( this );
						return _true;
					}
				}
			}

			for ( _long i = 0; i < polygons.Length( ); i ++ )
			{
				const ConvexPolygon& cp = polygons[i];

				Vector2 lt = Vector2( QuadNode::mRegion.l, QuadNode::mRegion.t );
				Vector2 lb = Vector2( QuadNode::mRegion.l, QuadNode::mRegion.b );
				Vector2 rt = Vector2( QuadNode::mRegion.r, QuadNode::mRegion.t );
				Vector2 rb = Vector2( QuadNode::mRegion.r, QuadNode::mRegion.b );

				if ( cp.Intersect( lt, rt ) || cp.Intersect( rt, rb ) || cp.Intersect( rb, lb ) || cp.Intersect( lb, lt ) )
				{
					leafs.Add( this );
					return _true;
				}
			}

			return _false;
		}

		virtual _bool FindLeaf( const SimplePolygon& sp, Array< LeafNode* >& leafs )
		{
			if ( sp.Intersect( QuadNode::mRegion ) )
			{
				leafs.Add( this );
				return _true;
			}

			return _false;
		}

		virtual _bool FindLeaf( const Vector2& p1, const Vector2& p2, Array< LeafNode* >& leafs )
		{
			if ( QuadNode::mRegion.Cross( p1, p2 ) )
			{
				leafs.Add( this );
				return _true;
			}

			if ( QuadNode::mRegion.Inside( p1 ) || QuadNode::mRegion.Inside( p2 ) || QuadNode::mRegion.OnEdge( p1 ) || QuadNode::mRegion.OnEdge( p2 ) )
			{
				leafs.Add( this );
				return _true;
			}

			return _false;
		}

		virtual _void PickLeaf( Array< LeafNode* >& leafs )
		{
			leafs.Add( this );
		}

		virtual _bool IsLeaf( )
		{
			return _true;
		}

		virtual _dword GetChildIndex( QuadNode* node )
		{
			return -1;
		}

		LeafNode* GetNext( ) const
		{
			if ( QuadNode::mParent == _null )
				return _null;

			if ( (LeafNode*) QuadNode::mParent->mChildNode[0] == this )
				return (LeafNode*) QuadNode::mParent->mChildNode[1];

			if ( (LeafNode*) QuadNode::mParent->mChildNode[1] == this )
				return (LeafNode*) QuadNode::mParent->mChildNode[2];

			if ( (LeafNode*) QuadNode::mParent->mChildNode[2] == this )
				return (LeafNode*) QuadNode::mParent->mChildNode[3];

			RootNode* pp = QuadNode::mParent->GetNext( );
			if ( pp == _null )
				return _null;

			return (LeafNode*) pp->mChildNode[0];
		}
	};

private:
	RootNode*	mRoot;
	_dword		mDepth;

public:
	inline QuadTree( ) : mRoot( _null )
		{ }
	inline QuadTree( const Region& region, _dword depth ) : mRoot( _null )
		{ mRoot = Create( region, depth ); }
	inline ~QuadTree( )
		{ delete mRoot; }

	RootNode* Create( const Region& region, _dword depth, RootNode* parent = _null )
	{
		RootNode* node = new RootNode( region, parent );

		if ( parent == _null )
		{
			delete mRoot;
			mRoot = node;
			mDepth = depth;
		}

		Region r1( region.l, region.t, ( region.l + region.r ) / 2, ( region.t + region.b ) / 2 );
		Region r2( ( region.l + region.r ) / 2, region.t, region.r, ( region.t + region.b ) / 2 );
		Region r3( region.l, ( region.t + region.b ) / 2, ( region.l + region.r ) / 2, region.b );
		Region r4( ( region.l + region.r ) / 2, ( region.t + region.b ) / 2, region.r, region.b );

		node->mChildNode[0] = new LeafNode( r1, node );
		node->mChildNode[1] = new LeafNode( r2, node );
		node->mChildNode[2] = new LeafNode( r3, node );
		node->mChildNode[3] = new LeafNode( r4, node );

		return node;
	}

	_void CreateAndPickLeafNodes( const Region& r, Array< LeafNode* >& picks )
	{
		if ( mRoot == _null )
			return;

		CreateAndPickSubtree( r, mRoot, mDepth, picks );
	}

	_void CreateAndPickLeafNodes( const AxisAlignedBox& box, Array< LeafNode* >& picks )
	{
		if ( mRoot == _null )
			return;

		CreateAndPickSubtree( Region( box.vmin.x, box.vmin.y, box.vmax.x, box.vmax.y ), mRoot, mDepth, picks );
	}

	_void CreateAndPickLeafNodes( const Vector2& p, Array< LeafNode* >& picks )
	{
		if ( mRoot == _null )
			return;

		CreateAndPickSubtree( Region( p.x, p.y, p.x, p.y ), mRoot, mDepth, picks );
	}

	_void CreateAndPickLeafNodes( const SimplePolygon& sp, Array< LeafNode* >& picks )
	{
		if ( mRoot == _null )
			return;

		CreateAndPickSubtree( sp, mRoot, mDepth, picks );
	}

	_void CreateAndPickSubtree( const Region& r, QuadNode* node, _long depth, Array< LeafNode* >& picks )
	{
		if ( Region::Intersect( node->mRegion, r ) != Region::cNullRect )
		{
			if ( node->IsLeaf( ) )
			{
				if ( depth >= 0 )
				{
					RootNode* parent = node->mParent;
					Region region = node->mRegion;
					_dword index = parent->GetChildIndex( node );
					if ( index == -1 )
					{
						XX_ERROR( L"[QT] Quad Tree Create error" )
						return;
					}

					RootNode* rootnode = CreateSubtree( region, r, depth, parent, picks );
					delete node;
					parent->mChildNode[index] = rootnode;
				}
				else
				{
					picks.Add( (LeafNode*) node );
				}
			}
			else
			{
				CreateAndPickSubtree( r, ( (RootNode*) node )->mChildNode[0], depth - 1, picks );
				CreateAndPickSubtree( r, ( (RootNode*) node )->mChildNode[1], depth - 1, picks );
				CreateAndPickSubtree( r, ( (RootNode*) node )->mChildNode[2], depth - 1, picks );
				CreateAndPickSubtree( r, ( (RootNode*) node )->mChildNode[3], depth - 1, picks );
			}
		}
	}

	RootNode* CreateSubtree( const Region& region, const Region& realregion, _long depth, RootNode* parent, Array< LeafNode* >& picks )
	{
		RootNode* node = new RootNode( region, parent );

		Region r1( region.l, region.t, ( region.l + region.r ) / 2, ( region.t + region.b ) / 2 );
		Region r2( ( region.l + region.r ) / 2, region.t, region.r, ( region.t + region.b ) / 2 );
		Region r3( region.l, ( region.t + region.b ) / 2, ( region.l + region.r ) / 2, region.b );
		Region r4( ( region.l + region.r ) / 2, ( region.t + region.b ) / 2, region.r, region.b );

		auto createchild = [node, depth, &realregion, &picks, this] ( _dword index, const Region& r )
		{
			if ( Region::Intersect( r, realregion ) != Region::cNullRect )
			{
				if ( depth > 0 )
				{
					node->mChildNode[index] = CreateSubtree( r, realregion, depth - 1, node, picks );
				}
				else
				{
					node->mChildNode[index] = new LeafNode( r, node );
					picks.Add( (LeafNode*) node->mChildNode[index] );
				}
			}
			else
			{
				node->mChildNode[index] = new LeafNode( r, node );
			}
		};

		createchild( 0, r1 );
		createchild( 1, r2 );
		createchild( 2, r3 );
		createchild( 3, r4 );

		return node;
	}

	_void CreateAndPickSubtree( const SimplePolygon& sp, QuadNode* node, _long depth, Array< LeafNode* >& picks )
	{
		if ( sp.Intersect( node->mRegion ) )
		{
			if ( node->IsLeaf( ) )
			{
				if ( depth >= 0 )
				{
					RootNode* parent = node->mParent;
					Region region = node->mRegion;
					_dword index = parent->GetChildIndex( node );
					if ( index == -1 )
					{
						XX_ERROR( L"[QT] Quad Tree Create error" )
						return;
					}

					RootNode* rootnode = CreateSubtree( region, sp, depth, parent, picks );
					delete node;
					parent->mChildNode[index] = rootnode;
				}
				else
				{
					picks.Add( (LeafNode*) node );
				}
			}
			else
			{
				CreateAndPickSubtree( sp, ( (RootNode*) node )->mChildNode[0], depth - 1, picks );
				CreateAndPickSubtree( sp, ( (RootNode*) node )->mChildNode[1], depth - 1, picks );
				CreateAndPickSubtree( sp, ( (RootNode*) node )->mChildNode[2], depth - 1, picks );
				CreateAndPickSubtree( sp, ( (RootNode*) node )->mChildNode[3], depth - 1, picks );
			}
		}
	}

	RootNode* CreateSubtree( const Region& region, const SimplePolygon& sp, _long depth, RootNode* parent, Array< LeafNode* >& picks )
	{
		RootNode* node = new RootNode( region, parent );

		Region r1( region.l, region.t, ( region.l + region.r ) / 2, ( region.t + region.b ) / 2 );
		Region r2( ( region.l + region.r ) / 2, region.t, region.r, ( region.t + region.b ) / 2 );
		Region r3( region.l, ( region.t + region.b ) / 2, ( region.l + region.r ) / 2, region.b );
		Region r4( ( region.l + region.r ) / 2, ( region.t + region.b ) / 2, region.r, region.b );

		auto createchild = [node, depth, &sp, &picks, this] ( _dword index, const Region& r )
		{
			if ( sp.Intersect( r ) )
			{
				if ( depth > 0 )
				{
					node->mChildNode[index] = CreateSubtree( r, sp, depth - 1, node, picks );
				}
				else
				{
					node->mChildNode[index] = new LeafNode( r, node );
					picks.Add( (LeafNode*) node->mChildNode[index] );
				}
			}
			else
			{
				node->mChildNode[index] = new LeafNode( r, node );
			}
		};

		createchild( 0, r1 );
		createchild( 1, r2 );
		createchild( 2, r3 );
		createchild( 3, r4 );

		return node;
	}

	inline _void Clear( )
		{ delete mRoot; mRoot = _null; }

	inline RootNode* GetRoot( ) const
		{ return mRoot; }
	inline const Region& GetRegion( ) const
		{ return mRoot->mRegion; }
	inline _dword GetDepth( ) const
		{ return mDepth; }

	LeafNode* GetFirstLeaf( ) const
	{
		if ( mRoot == _null )
			return _null;

		QuadNode* p = mRoot;
		QuadNode* c = p->FirstChild( );

		while ( c != _null )
		{
			p = c;
			c = p->FirstChild( );
		}

		return (LeafNode*) p;
	}

	_void Pick( const Vector2& p, Array< LeafNode* >& picks )
	{
		if ( mRoot == _null )
			return;

		mRoot->FindLeaf( p, picks );
	}

	_void Pick( const Vector3& p, Array< LeafNode* >& picks )
	{
		if ( mRoot == _null )
			return;

		mRoot->FindLeaf( Vector2( p.x, p.y ), picks );
	}

	_void Pick( const Region& r, Array< LeafNode* >& picks )
	{
		if ( mRoot == _null )
			return;

		mRoot->FindLeaf( r, picks );
	}

	_void Pick( const AxisAlignedBox& box, Array< LeafNode* >& picks )
	{
		if ( mRoot == _null )
			return;

		mRoot->FindLeaf( Region( box.vmin.x, box.vmin.y, box.vmax.x, box.vmax.y ), picks );
	}

	_void Pick( const Frustum& frustum, Array< LeafNode* >& picks )
	{
		if ( mRoot == _null )
			return;

		Vector2 p1[] = {
			Vector2( frustum.vs[0].x, frustum.vs[0].y ),
			Vector2( frustum.vs[1].x, frustum.vs[1].y ),
			Vector2( frustum.vs[2].x, frustum.vs[2].y ),
			Vector2( frustum.vs[3].x, frustum.vs[3].y ) };

		Vector2 p2[] = {
			Vector2( frustum.vs[4].x, frustum.vs[4].y ),
			Vector2( frustum.vs[5].x, frustum.vs[5].y ),
			Vector2( frustum.vs[6].x, frustum.vs[6].y ),
			Vector2( frustum.vs[7].x, frustum.vs[7].y ) };

		Vector2 p3[] = {
			Vector2( frustum.vs[0].x, frustum.vs[0].y ),
			Vector2( frustum.vs[1].x, frustum.vs[1].y ),
			Vector2( frustum.vs[5].x, frustum.vs[5].y ),
			Vector2( frustum.vs[4].x, frustum.vs[4].y ) };

		Vector2 p4[] = {
			Vector2( frustum.vs[1].x, frustum.vs[1].y ),
			Vector2( frustum.vs[2].x, frustum.vs[2].y ),
			Vector2( frustum.vs[6].x, frustum.vs[6].y ),
			Vector2( frustum.vs[5].x, frustum.vs[5].y ) };

		Vector2 p5[] = {
			Vector2( frustum.vs[0].x, frustum.vs[0].y ),
			Vector2( frustum.vs[3].x, frustum.vs[3].y ),
			Vector2( frustum.vs[7].x, frustum.vs[7].y ),
			Vector2( frustum.vs[4].x, frustum.vs[4].y ) };

		Vector2 p6[] = {
			Vector2( frustum.vs[2].x, frustum.vs[2].y ),
			Vector2( frustum.vs[3].x, frustum.vs[3].y ),
			Vector2( frustum.vs[7].x, frustum.vs[7].y ),
			Vector2( frustum.vs[6].x, frustum.vs[6].y ) };

		Array< ConvexPolygon > polygons;
		polygons.Add( ConvexPolygon( p1, 4, _true ) );
		polygons.Add( ConvexPolygon( p2, 4, _true ) );
		polygons.Add( ConvexPolygon( p3, 4, _true ) );
		polygons.Add( ConvexPolygon( p4, 4, _true ) );
		polygons.Add( ConvexPolygon( p5, 4, _true ) );
		polygons.Add( ConvexPolygon( p6, 4, _true ) );

		mRoot->FindLeaf( polygons, picks );
	}

	_void Pick( const Ray& ray, Array< LeafNode* >& picks, _float raylength = Math::cMaxFloat )
	{
		if ( mRoot == _null )
			return;

		Ray r = ray;
		r.orig.z = r.dir.z = 0;
		r.dir.Normalize( );

		Vector2 p1 = Vector2( r.orig.x, r.orig.y );

		// Find the farest dist between p1 and region.
		_float dist = ( Vector2( mRoot->mRegion.l, mRoot->mRegion.t ) - p1 ).Magnitude( );

		_float temp = ( Vector2( mRoot->mRegion.l, mRoot->mRegion.b ) - p1 ).Magnitude( );
		if ( dist < temp )
			dist = temp;

		temp = ( Vector2( mRoot->mRegion.r, mRoot->mRegion.b ) - p1 ).Magnitude( );
		if ( dist < temp )
			dist = temp;

		temp = ( Vector2( mRoot->mRegion.r, mRoot->mRegion.t ) - p1 ).Magnitude( );
		if ( dist < temp )
			dist = temp;

		// Use user raylength.
		if ( raylength < dist )
			dist = raylength;

		Vector3 p2 = r.VectorOnRay( dist );
		mRoot->FindLeaf( p1, Vector2( p2.x, p2.y ), picks );
	}

	_void Pick( const Ray& ray, _float maxdist, Array< LeafNode* >& picks )
	{
		if ( mRoot == _null )
			return;

		Vector3 temp = ray.VectorOnRay( maxdist );
		mRoot->FindLeaf( Vector2( ray.orig.x, ray.orig.y ), Vector2( temp.x, temp.y ), picks );
	}

	_void Pick( const Vector2& p1, const Vector2& p2, Array< LeafNode* >& picks )
	{
		if ( mRoot == _null )
			return;

		mRoot->FindLeaf( p1, p2, picks );
	}

	_void Pick( const ConvexPolygon& cp, Array< LeafNode* >& picks )
	{
		if ( mRoot == _null )
			return;

		Array< ConvexPolygon > polygons;
		polygons.Add( cp );
		mRoot->FindLeaf( polygons, picks );
	}

	_void Pick( const SimplePolygon& sp, Array< LeafNode* >& picks )
	{
		if ( mRoot == _null )
			return;

		mRoot->FindLeaf( sp, picks );
	}
};

};