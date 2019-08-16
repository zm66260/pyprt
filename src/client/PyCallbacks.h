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

#include "IPyCallbacks.h"

#include "prt/Callbacks.h"

#include <pybind11/pybind11.h>

#include <string>
#include <vector>
#include <iostream>
#include <map>

struct Entry{
    uint32_t initialShapeIdx;
    int32_t id;
    FloatMap reportFloatData;
    StringMap reportStringData;
    BoolMap reportBoolData;
    std::vector<std::vector<double>> vertices;
    std::vector<std::vector<uint32_t>> faces;
};

using Entries = std::vector<Entry>;

class PyCallbacks : public IPyCallbacks {
private:
    Entries shapes;

    std::unordered_set<uint32_t> initialShapesIndices;
    std::map<uint32_t, FloatMap> CGAfloatReportsMap;
    std::map<uint32_t, StringMap> CGAstringReportsMap;
    std::map<uint32_t, BoolMap> CGAboolReportsMap;
    std::map<uint32_t, std::vector<std::vector<double>>> verticesMap;
    std::map<uint32_t, std::vector<std::vector<uint32_t>>> facesMap;

public:
    
	PyCallbacks() = default;

	virtual ~PyCallbacks() = default;

    void addEntry(
        const uint32_t initialShapeIndex,
        const int32_t shapeID,
        const FloatMap& CGAfloatreport,
        const StringMap& CGAstringreport,
        const BoolMap& CGAboolreport,
        const std::vector<std::vector<double>> verticesCoord,
        const std::vector<std::vector<uint32_t>> facesCoord
    ) override;

    void addGeometry(
        const uint32_t initialShapeIndex,
        const std::vector<std::vector<double>> verticesCoord,
        const std::vector<std::vector<uint32_t>> facesCoord
    ) override;

    void addReports(
        const uint32_t initialShapeIndex,
        const FloatMap& CGAfloatreport,
        const StringMap& CGAstringreport,
        const BoolMap& CGAboolreport
    ) override;

    std::unordered_set<uint32_t> PyCallbacks::getInitialShapesIndices() const;

    std::vector<std::tuple<uint32_t, int32_t, std::vector<std::vector<double>>>> getVertices() const;

    std::vector<std::tuple<uint32_t, int32_t, std::vector<std::vector<uint32_t>>>> getFaces() const;

    std::map<uint32_t, FloatMap> PyCallbacks::getFloatReportNEW() const;

    std::vector<std::tuple<uint32_t, int32_t, FloatMap>> getFloatReport() const;

    std::vector<std::tuple<uint32_t, int32_t, StringMap>> getStringReport() const;

    std::vector<std::tuple<uint32_t, int32_t, BoolMap>> getBoolReport() const;

	prt::Status generateError(size_t isIndex, prt::Status status, const wchar_t* message) {
		pybind11::print(L"GENERATE ERROR:", isIndex, status, message);
		return prt::STATUS_OK;
	}

	prt::Status assetError(size_t isIndex, prt::CGAErrorLevel level, const wchar_t* key, const wchar_t* uri, const wchar_t* message) {
		pybind11::print(L"ASSET ERROR:", isIndex, level, key, uri, message);
		return prt::STATUS_OK;
	}

	prt::Status cgaError(size_t isIndex, int32_t shapeID, prt::CGAErrorLevel level, int32_t methodId, int32_t pc, const wchar_t* message) {
		pybind11::print(L"CGA ERROR:", isIndex, shapeID, level, methodId, pc, message);
        return prt::STATUS_OK;
	}

	prt::Status cgaPrint(size_t isIndex, int32_t shapeID, const wchar_t* txt) {
		pybind11::print(L"CGA PRINT:", isIndex, shapeID, txt);
		return prt::STATUS_OK;
	}

	prt::Status cgaReportBool(size_t /*isIndex*/, int32_t /*shapeID*/, const wchar_t* /*key*/, bool /*value*/) {
		return prt::STATUS_OK;
	}

	prt::Status cgaReportFloat(size_t /*isIndex*/, int32_t /*shapeID*/, const wchar_t* /*key*/, double /*value*/) {
		return prt::STATUS_OK;
	}

	prt::Status cgaReportString(size_t /*isIndex*/, int32_t /*shapeID*/, const wchar_t* /*key*/, const wchar_t* /*value*/) {
		return prt::STATUS_OK;
	}

	prt::Status attrBool(size_t /*isIndex*/, int32_t /*shapeID*/, const wchar_t* /*key*/, bool /*value*/) {
		return prt::STATUS_OK;
	}

	prt::Status attrFloat(size_t /*isIndex*/, int32_t /*shapeID*/, const wchar_t* /*key*/, double /*value*/) {
		return prt::STATUS_OK;
	}

	prt::Status attrString(size_t /*isIndex*/, int32_t /*shapeID*/, const wchar_t* /*key*/, const wchar_t* /*value*/) {
		return prt::STATUS_OK;
	}
};
