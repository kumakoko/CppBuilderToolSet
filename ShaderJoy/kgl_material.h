﻿/*******************************************************************************
Copyright(C) 2014-2019 www.xionggf.com

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy,modify, merge, publish, distribute,sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER 、
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,ARISING FROM,OUT OF OR IN CONNECTION
WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*******************************************************************************/
/*!
* \file kgl_material.h
* \date 2017/12/31 13:45
*
* \author www.xionggf.com
* Contact: sun_of_lover@sina.com
*
* \brief
*
* TODO: 材质定义
*
* \note
*/
#ifndef kgl_material_h__
#define kgl_material_h__

#include "glad.h"
#include "glm/glm.hpp"

namespace kgl
{
    struct Material
    {
        glm::vec3 Ambient;
        glm::vec3 Diffuse;
        glm::vec3 Specular;
        float Shininess;
    };

    struct MaterialUniformLocation
    {
        GLint Ambient;
        GLint Diffuse;
        GLint Specular;
        GLint Shininess;
    };
} // namespace kgl
#endif // kgl_material_h__
