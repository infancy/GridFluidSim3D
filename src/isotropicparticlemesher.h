/*
Copyright (c) 2015 Ryan L. Guy

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
   claim that you wrote the original software. If you use this software
   in a product, an acknowledgement in the product documentation would be
   appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be
   misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/
#ifndef ISOTROPICPARTICLEMESHER_H
#define ISOTROPICPARTICLEMESHER_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <assert.h>

#include "fragmentedvector.h"
#include "markerparticle.h"
#include "fluidmaterialgrid.h"
#include "trianglemesh.h"
#include "implicitsurfacescalarfield.h"
#include "polygonizer3d.h"
#include "aabb.h"
#include "vmath.h"

class IsotropicParticleMesher {

public:
	IsotropicParticleMesher();
	IsotropicParticleMesher(int isize, int jsize, int ksize, double dx);
	~IsotropicParticleMesher();

	void setSubdivisionLevel(int n);
	void setNumPolygonizationSlices(int n);

	TriangleMesh meshParticles(FragmentedVector<MarkerParticle> &particles, 
		                       FluidMaterialGrid &materialGrid,
		                       double particleRadius);

private:

	TriangleMesh _polygonizeAll(FragmentedVector<MarkerParticle> &particles,
	                            FluidMaterialGrid &materialGrid);

	TriangleMesh _polygonizeSlices(FragmentedVector<MarkerParticle> &particles,
	                               FluidMaterialGrid &materialGrid);
	TriangleMesh _polygonizeSlice(int startidx, int endidx, 
		                          FragmentedVector<MarkerParticle> &particles, 
	                              FluidMaterialGrid &materialGrid);
	void _getSubdividedGridDimensions(int *i, int *j, int *k, double *dx);
	void _computeSliceScalarField(int startidx, int endidx, 
		                          FragmentedVector<MarkerParticle> &particles,
		                          FluidMaterialGrid &materialGrid,
		                          ImplicitSurfaceScalarField &field);
	vmath::vec3 _getSliceGridPositionOffset(int startidx, int endidx);
	void _getSliceParticles(int startidx, int endidx, 
		                    FragmentedVector<MarkerParticle> &markerParticles,
		                    FragmentedVector<vmath::vec3> &sliceParticles);
	void _getSliceMaterialGrid(int startidx, int endidx,
		                       FluidMaterialGrid &materialGrid,
		                       FluidMaterialGrid &sliceMaterialGrid);
	AABB _getSliceAABB(int startidx, int endidx);
	void _updateScalarFieldSeam(int startidx, int endidx, ImplicitSurfaceScalarField &field);
	void _applyScalarFieldSliceSeamData(ImplicitSurfaceScalarField &field);
	void _saveScalarFieldSliceSeamData(ImplicitSurfaceScalarField &field);
	void _getSliceMask(int startidx, int endidx, Array3d<bool> &mask);

	int _isize = 0;
	int _jsize = 0;
	int _ksize = 0;
	double _dx = 0.0;

	int _subdivisionLevel = 1;
	int _numPolygonizationSlices = 1;

	double _particleRadius = 0.0;

	Array3d<float> _scalarFieldSeamData;

};

#endif