//
// Copyright 2019 Autodesk, Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef HD_VP2_MATERIAL
#define HD_VP2_MATERIAL

#include "pxr/pxr.h"
#include "pxr/imaging/hd/material.h"

#include <maya/MShaderManager.h>

#include <unordered_map>

PXR_NAMESPACE_OPEN_SCOPE

class HdSceneDelegate;
class HdVP2RenderDelegate;

/*! \brief  A deleter for MShaderInstance, for use with smart pointers.
*/
struct HdVP2ShaderDeleter
{
    void operator () (MHWRender::MShaderInstance*);
};

/*! \brief  A MShaderInstance owned by a std unique pointer.
*/
using HdVP2ShaderUniquePtr = std::unique_ptr<
    MHWRender::MShaderInstance,
    HdVP2ShaderDeleter
>;

/*! \brief  A deleter for MTexture, for use with smart pointers.
*/
struct HdVP2TextureDeleter
{
    void operator () (MHWRender::MTexture*);
};

/*! \brief  A MTexture owned by a std unique pointer.
*/
using HdVP2TextureUniquePtr = std::unique_ptr<
    MHWRender::MTexture,
    HdVP2TextureDeleter
>;

/*! \brief  A string-indexed texture map.
*/
using HdVP2TextureMap = std::unordered_map<
    std::string,
    HdVP2TextureUniquePtr
>;

/*! \brief  A VP2-specific implementation for a Hydra material prim.
    \class  HdVP2Material

    Provides a basic implementation of a Hydra material.
*/
class HdVP2Material final : public HdMaterial {
public:
    HdVP2Material(HdVP2RenderDelegate*, const SdfPath&);

    ~HdVP2Material() override;

    void Sync(HdSceneDelegate*, HdRenderParam*, HdDirtyBits*) override;

    HdDirtyBits GetInitialDirtyBitsMask() const override;
    void Reload() override;

    MHWRender::MShaderInstance* GetSurfaceShader() const;

    /*! \brief  Get primvar requirements required by this material.
    */
    const TfTokenVector& GetRequiredPrimvars() const {
        return _requiredPrimvars;
    }

private:
    MHWRender::MShaderInstance* _CreateShaderInstance(const HdMaterialNetwork& mat);
    void _UpdateShaderInstance(const HdMaterialNetwork& mat);

    HdVP2RenderDelegate* const _renderDelegate; //!< VP2 render delegate for which this material was created

    HdVP2ShaderUniquePtr  _surfaceShader;       //!< VP2 surface shader instance
    SdfPath               _surfaceShaderId;     //!< Path of the surface shader
    HdVP2TextureMap       _textureMap;          //!< Textures used by this material
    TfTokenVector         _requiredPrimvars;    //!< primvars required by this material
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
