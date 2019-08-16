/**
 * Esri CityEngine SDK Callbacks for Geometry Encoder for Python
 *
 * This example demonstrates the usage of the PRTX interface
 * to write custom encoders.
 *
 * See README.md in http://github.com/ArcGIS/esri-cityengine-sdk for build instructions.
 *
 * Written by Camille Lechot
 * Esri R&D Center Zurich, Switzerland
 *
 * Copyright 2012-2017 (c) Esri R&D Center Zurich
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include "prt/Callbacks.h"

#include <string>
#include <vector>
#include <map>

using FloatMap = std::map<std::string, double>;
using StringMap = std::map<std::string, std::string>;
using BoolMap = std::map<std::string, bool>;

class IPyCallbacks : public prt::Callbacks {
public:

    virtual ~IPyCallbacks() override = default;

    virtual void addEntry(
        const uint32_t initialShapeIndex,
        const int32_t shapeID,
        const FloatMap& CGAfloatreport,
        const StringMap& CGAstringreport,
        const BoolMap& CGAboolreport,
        const std::vector<std::vector<double>> verticesCoord,
        const std::vector<std::vector<uint32_t>> facesCoord
    ) = 0;

    virtual void addGeometry(
        const uint32_t initialShapeIndex,
        const std::vector<std::vector<double>> verticesCoord,
        const std::vector<std::vector<uint32_t>> facesCoord
    ) = 0;

    virtual void addReports(
        const uint32_t initialShapeIndex,
        const FloatMap& CGAfloatreport,
        const StringMap& CGAstringreport,
        const BoolMap& CGAboolreport
    ) = 0;

};
