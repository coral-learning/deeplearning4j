/*******************************************************************************
 * Copyright (c) 2015-2018 Skymind, Inc.
 *
 * This program and the accompanying materials are made available under the
 * terms of the Apache License, Version 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 ******************************************************************************/


#include <vector>
#include <pointercast.h>
#include "../NativeOpExcutioner.h"
#include <types/types.h>


////////////////////////////////////////////////////////////////////////
/**
*
* @param opNum
* @param x
* @param xShapeInfo
* @param extraParams
* @param result
* @param resultShapeInfo
*/
Nd4jLong NativeOpExcutioner::execIndexReduceScalar(int opNum, void *x, Nd4jLong *xShapeInfo, void *extraParams) {
    auto xType = nd4j::ArrayOptions::dataType(xShapeInfo);

    BUILD_SINGLE_SELECTOR(xType,return functions::indexreduce::IndexReduce, ::execScalar(opNum, x,xShapeInfo,extraParams), LIBND4J_TYPES);
}

////////////////////////////////////////////////////////////////////////
/**
 *
 * @param opNum
 * @param x
 * @param xShapeInfo
 * @param extraParams
 * @param result
 * @param resultShapeInfoBuffer
 * @param dimension
 * @param dimensionLength
 */

void NativeOpExcutioner::execIndexReduce(int opNum,
        void *x,
        Nd4jLong *xShapeInfo,
        void *extraParams,
        Nd4jLong *result,
        Nd4jLong *resultShapeInfoBuffer,
        int *dimension,
        int dimensionLength,
        Nd4jLong *tadShapeInfo,
        Nd4jLong *tadOffsets) {

    auto xType = nd4j::ArrayOptions::dataType(xShapeInfo);

    BUILD_SINGLE_SELECTOR(xType, functions::indexreduce::IndexReduce, ::exec(opNum, x, xShapeInfo, extraParams, result, resultShapeInfoBuffer, dimension, dimensionLength, tadShapeInfo, tadOffsets);, LIBND4J_TYPES);
}

////////////////////////////////////////////////////////////////////////
/**
 *
 * @param opNum
 * @param x
 * @param xShapeInfo
 * @param y
 * @param yShapeInfo
 * @param result
 * @param resultShapeInfo
 * @param dimension
 * @param dimensionLength
 */

void NativeOpExcutioner::execBroadcast(int opNum, void *x, Nd4jLong *xShapeInfo, void *y, Nd4jLong *yShapeInfo, void *result, Nd4jLong *resultShapeInfo, int *dimension, int dimensionLength, Nd4jLong *tadOnlyShapeInfo, Nd4jLong *tadOffsets, Nd4jLong *tadOnlyShapeInfoZ, Nd4jLong *tadOffsetsZ) {
    auto xType = nd4j::ArrayOptions::dataType(xShapeInfo);
    auto yType = nd4j::ArrayOptions::dataType(yShapeInfo);

    BUILD_DOUBLE_SELECTOR(xType, yType, functions::broadcast::Broadcast, ::exec(opNum, x, xShapeInfo, y, yShapeInfo, result, resultShapeInfo, dimension, dimensionLength, tadOnlyShapeInfo, tadOffsets, tadOnlyShapeInfoZ, tadOffsetsZ);, LIBND4J_TYPES, LIBND4J_TYPES);
}


////////////////////////////////////////////////////////////////////////
/**
*
* @param opNum
* @param dx
* @param xStride
* @param y
* @param yStride
* @param result
* @param resultStride
* @param extraParams
* @param n
*/
void NativeOpExcutioner::execPairwiseTransform(int opNum, void *dx, Nd4jLong *xShapeInfo, void *y, Nd4jLong *yShapeInfo, void *result, Nd4jLong *resultShapeInfo, void *extraParams) {
    auto xType = nd4j::ArrayOptions::dataType(xShapeInfo);
    auto yType = nd4j::ArrayOptions::dataType(yShapeInfo);

    BUILD_DOUBLE_SELECTOR(xType, yType, functions::pairwise_transforms::PairWiseTransform, ::exec(opNum, dx, xShapeInfo, y, yShapeInfo, result, resultShapeInfo, extraParams), LIBND4J_TYPES, LIBND4J_TYPES);
}

////////////////////////////////////////////////////////////////////////
/**
*
* @param opNum
* @param dx
* @param xStride
* @param y
* @param yStride
* @param result
* @param resultStride
* @param extraParams
* @param n
*/
void NativeOpExcutioner::execPairwiseTransform(int opNum, void *dx, Nd4jLong *xShapeInfo, void *y, Nd4jLong *yShapeInfo, void *result, Nd4jLong *resultShapeInfo, void *extraParams, Nd4jLong *xIndexes, Nd4jLong *yIndexes, Nd4jLong *resultIndexes) {
    auto xType = nd4j::ArrayOptions::dataType(xShapeInfo);
    auto yType = nd4j::ArrayOptions::dataType(yShapeInfo);

    BUILD_DOUBLE_SELECTOR(xType, yType, functions::pairwise_transforms::PairWiseTransform, ::exec(opNum, dx, xShapeInfo, y, yShapeInfo, result, resultShapeInfo, extraParams, xIndexes, yIndexes, resultIndexes), LIBND4J_TYPES, LIBND4J_TYPES);
}

////////////////////////////////////////////////////////////////////////
/**
*
* @param opNum
* @param x
* @param xShapeInfo
* @param extraParams
* @param result
* @param resultShapeInfo
*/
void NativeOpExcutioner::execReduce(int opNum, void *x, Nd4jLong *xShapeInfo, void *extraParams, void *result, Nd4jLong *resultShapeInfo, int *dimension, int dimensionLength, Nd4jLong *tadShapeInfo, Nd4jLong *tadOffsets) {
    auto xType = nd4j::ArrayOptions::dataType(xShapeInfo);

    // for LogSumExp reduction we need to have max stored in result
    if (opNum == 19) {
        BUILD_SINGLE_SELECTOR(xType, functions::reduce::ReduceFunction, ::exec(3, x, xShapeInfo, extraParams, result, resultShapeInfo, dimension, dimensionLength, tadShapeInfo, tadOffsets), LIBND4J_TYPES);
    }

    BUILD_SINGLE_SELECTOR(xType, functions::reduce::ReduceFunction, ::exec(opNum, x, xShapeInfo, extraParams, result, resultShapeInfo, dimension, dimensionLength, tadShapeInfo, tadOffsets), LIBND4J_TYPES);
}

////////////////////////////////////////////////////////////////////////
/**
 *
 * @param opNum
 * @param x
 * @param xShapeInfo
 * @param extraParams
 * @return
 */
template<typename T>
T NativeOpExcutioner<T>::execReduceScalar(int opNum, T *x, Nd4jLong *xShapeInfo, T *extraParams) {
    if (opNum == 19) {
        T max = functions::reduce::ReduceFunction<T>::execScalar(3, x, xShapeInfo, extraParams);
        return functions::reduce::ReduceFunction<T>::execScalar(opNum, x, xShapeInfo, &max);
    }

    return functions::reduce::ReduceFunction<T>::execScalar(opNum, x, xShapeInfo, extraParams);
}

////////////////////////////////////////////////////////////////////////
/**
 *
 * @param opNum
 * @param x
 * @param xShapeInfo
 * @param extraParamsVals
 * @param y
 * @param yShapeInfo
 * @param result
 * @param resultShapeInfoBuffer
 * @param dimension
 * @param dimensionLength
 */
template<typename T>
T NativeOpExcutioner<T>::execReduce3Scalar(int opNum, T *x, Nd4jLong *xShapeInfo, T *extraParamsVals, T *y, Nd4jLong *yShapeInfo) {
    return functions::reduce3::Reduce3<T>::execScalar(opNum, x, xShapeInfo, extraParamsVals, y,yShapeInfo);
}

////////////////////////////////////////////////////////////////////////
/**
*
* @param opNum
* @param x
* @param xShapeInfo
* @param extraParamsVals
* @param y
* @param yShapeInfo
* @param result
* @param resultShapeInfo
*/
void NativeOpExcutioner::execReduce3(int opNum, void *x, Nd4jLong *xShapeInfo, void *extraParamsVals, void *y, Nd4jLong *yShapeInfo, void *result, Nd4jLong *resultShapeInfo) {
    auto xType = nd4j::ArrayOptions::dataType(xShapeInfo);
    auto yType = nd4j::ArrayOptions::dataType(yShapeInfo);

    BUILD_DOUBLE_SELECTOR(xType, yType, functions::reduce3::Reduce3, ::exec(opNum, x, xShapeInfo, extraParamsVals, y, yShapeInfo, result, resultShapeInfo, nullptr, 1), LIBND4J_TYPES, LIBND4J_TYPES);

}

////////////////////////////////////////////////////////////////////////
void NativeOpExcutioner::execReduce3All(int opNum, void *x, Nd4jLong *xShapeInfo, void *extraParamsVals, void *y, Nd4jLong *yShapeInfo, void *result, Nd4jLong *resultShapeInfoBuffer, int *dimension, int dimensionLength, Nd4jLong *xTadShapeInfo, Nd4jLong *xOffsets, Nd4jLong *yTadShapeInfo, Nd4jLong *yOffsets) {
    auto xType = nd4j::ArrayOptions::dataType(xShapeInfo);
    auto yType = nd4j::ArrayOptions::dataType(yShapeInfo);

    BUILD_DOUBLE_SELECTOR(xType, yType, functions::reduce3::Reduce3, ::execAll(opNum, x, xShapeInfo, extraParamsVals, y, yShapeInfo, result, resultShapeInfoBuffer, dimension, dimensionLength, xTadShapeInfo, xOffsets, yTadShapeInfo, yOffsets), LIBND4J_TYPES, LIBND4J_TYPES);
}

////////////////////////////////////////////////////////////////////////
void NativeOpExcutioner::execReduce3TAD(int opNum, void *x, Nd4jLong *xShapeInfo, void *extraParamsVals, void *y, Nd4jLong *yShapeInfo, void *result, Nd4jLong *resultShapeInfoBuffer, int *dimension, int dimensionLength, Nd4jLong *tadShapeInfo, Nd4jLong *tadOffsets) {
    auto xType = nd4j::ArrayOptions::dataType(xShapeInfo);
    auto yType = nd4j::ArrayOptions::dataType(yShapeInfo);

    BUILD_DOUBLE_SELECTOR(xType, yType, functions::reduce3::Reduce3, ::exec(opNum, x, xShapeInfo, extraParamsVals, y, yShapeInfo, result, resultShapeInfoBuffer, dimension, dimensionLength, tadShapeInfo, tadOffsets), LIBND4J_TYPES, LIBND4J_TYPES);
}

////////////////////////////////////////////////////////////////////////
/**
*
* @param opNum
* @param x
* @param xStride
* @param result
* @param resultStride
* @param scalar
* @param extraParams
* @param n
*/
template<typename T>
void NativeOpExcutioner<T>::execScalar(int opNum, T *x, Nd4jLong xStride, T *result, Nd4jLong resultStride, T scalar, T *extraParams, Nd4jLong n) {
    functions::scalar::ScalarTransform<T>::transform(opNum, x, xStride, result, resultStride, scalar, extraParams, n);
}

////////////////////////////////////////////////////////////////////////
/**
*
* @param opNum
* @param x
* @param xStride
* @param result
* @param resultStride
* @param scalar
* @param extraParams
* @param n
*/
template<typename T>
void NativeOpExcutioner<T>::execScalar(int opNum, T *x, Nd4jLong *xShapeInfo, T *result, Nd4jLong *resultShapeInfo, T scalar, T *extraParams) {
    functions::scalar::ScalarTransform<T>::transform(opNum, x, xShapeInfo, result, resultShapeInfo, scalar, extraParams);
}

////////////////////////////////////////////////////////////////////////
/**
*
* @param opNum
* @param x
* @param xStride
* @param result
* @param resultStride
* @param scalar
* @param extraParams
* @param n
*/
template<typename T>
void  NativeOpExcutioner<T>::execScalar(int opNum, T *x, Nd4jLong *xShapeInfo, T *result, Nd4jLong *resultShapeInfo, T scalar, T *extraParams, Nd4jLong *xIndexes, Nd4jLong *resultIndexes) {
    functions::scalar::ScalarTransform<T>::transform(opNum, x, xShapeInfo, result, resultShapeInfo, scalar, extraParams, xIndexes, resultIndexes);
}

////////////////////////////////////////////////////////////////////////
template<typename T>
void NativeOpExcutioner<T>::execScalar(int opNum, T *x, Nd4jLong *xShapeInfo, T *extraParams, T *z, Nd4jLong *zShapeInfo, T *scalars, int *dimension, int dimensionLength, Nd4jLong *tadShapeInfo, Nd4jLong *tadOffsets, Nd4jLong *tadShapeInfoZ, Nd4jLong *tadOffsetsZ) {
    functions::scalar::ScalarTransform<T>::transform(opNum, x, xShapeInfo, extraParams, z, zShapeInfo, scalars, dimension, dimensionLength, tadShapeInfo, tadOffsets, tadShapeInfoZ, tadOffsetsZ);
}

////////////////////////////////////////////////////////////////////////
/**
*
* @param opNum
* @param x
* @param xShapeInfo
* @param extraParams
* @param result
* @param resultShapeInfo
*/
template<typename T>
void NativeOpExcutioner<T>::execSummaryStats(int opNum, T *x, Nd4jLong *xShapeInfo, T *extraParams, T *result, Nd4jLong *resultShapeInfo, bool biasCorrected) {
    functions::summarystats::SummaryStatsReduce<T>::exec(opNum, biasCorrected, x, xShapeInfo, extraParams, result, resultShapeInfo, nullptr, 1);
}

////////////////////////////////////////////////////////////////////////
/**
*
* @param opNum
* @param x
* @param xShapeInfo
* @param extraParams
* @param result
* @param resultShapeInfo
*/
template<typename T>
T NativeOpExcutioner<T>::execSummaryStatsScalar(int opNum, T *x, Nd4jLong *xShapeInfo, T *extraParams, bool biasCorrected) {
    return functions::summarystats::SummaryStatsReduce<T>::execScalar(opNum, biasCorrected, x, xShapeInfo, extraParams);
}

////////////////////////////////////////////////////////////////////////
/**
*
* @param opNum
* @param x
* @param xShapeInfo
* @param extraParams
* @param result
* @param resultShapeInfoBuffer
* @param dimension
* @param dimensionLength
*/
template<typename T>
void NativeOpExcutioner<T>::execSummaryStats(int opNum, T *x, Nd4jLong *xShapeInfo, T *extraParams, T *result, Nd4jLong *resultShapeInfoBuffer, int *dimension, int dimensionLength, bool biasCorrected) {
    functions::summarystats::SummaryStatsReduce<T>::exec(opNum, biasCorrected, x, xShapeInfo, extraParams, result, resultShapeInfoBuffer, dimension, dimensionLength);
}

////////////////////////////////////////////////////////////////////////
/**
*
* @param opNum
* @param dx
* @param xStride
* @param result
* @param resultStride
* @param extraParams
* @param n
*/
template<typename T>
void NativeOpExcutioner<T>::execTransform(int opNum, T *dx, Nd4jLong xStride, T *result, Nd4jLong resultStride, T *extraParams, Nd4jLong n) {
    functions::transform::Transform<T>::exec(opNum, dx, xStride, result, resultStride, extraParams, n);
}

////////////////////////////////////////////////////////////////////////
/**
*
* @param opNum
* @param dx
* @param xStride
* @param result
* @param resultStride
* @param extraParams
* @param n
*/
template<typename T>
void NativeOpExcutioner<T>::execTransform(int opNum, T *dx, Nd4jLong *xShapeInfo, T *result, Nd4jLong *resultShapeInfo, T *extraParams, Nd4jLong *tadShapeInfo, Nd4jLong *tadOffsets) {
    functions::transform::Transform<T>::exec(opNum, dx, xShapeInfo, result, resultShapeInfo, extraParams, tadShapeInfo, tadOffsets);
}

////////////////////////////////////////////////////////////////////////
/**
*
* @param opNum
* @param dx
* @param xStride
* @param result
* @param resultStride
* @param extraParams
* @param n
*/
template<typename T>
void NativeOpExcutioner<T>::execTransform(int opNum, T *dx, Nd4jLong *xShapeInfo, T *result, Nd4jLong *resultShapeInfo, T *extraParams, Nd4jLong *xIndexes, Nd4jLong *resultIndexes, Nd4jLong *tadShapeInfo, Nd4jLong *tadOffsets) {
//    functions::transform::Transform<T>::exec(opNum, dx, xShapeInfo, result, resultShapeInfo, extraParams, xIndexes, resultIndexes, tadShapeInfo, tadOffsets);
}


////////////////////////////////////////////////////////////////////////
template<typename T>
void NativeOpExcutioner<T>::execAggregate(int opNum, T **arguments, int numArguments, Nd4jLong **shapeArguments, int numShapeArguments, int *indexArguments, int numIndexArguments, int **intArrays, int numIntArrays, T *realArguments, int numRealArguments) {
    functions::aggregate::AggregatedFunction<T>::exec(opNum, arguments, numArguments, shapeArguments, numShapeArguments, indexArguments, numIndexArguments, intArrays, numIntArrays, realArguments, numRealArguments);
}

////////////////////////////////////////////////////////////////////////
template<typename T>
void NativeOpExcutioner<T>::execRandom(int opNum, Nd4jPointer state, T *z, Nd4jLong *zShapeBuffer, T *extraArguments) {
    functions::random::RandomFunction<T>::execTransform(opNum, state, z, zShapeBuffer, extraArguments);
}

////////////////////////////////////////////////////////////////////////
template<typename T>
void NativeOpExcutioner<T>::execRandom(int opNum, Nd4jPointer state, T *x, Nd4jLong *xShapeBuffer, T *z, Nd4jLong *zShapeBuffer, T *extraArguments) {
    functions::random::RandomFunction<T>::execTransform(opNum, state, x, xShapeBuffer, z, zShapeBuffer, extraArguments);
}

////////////////////////////////////////////////////////////////////////
template<typename T>
void NativeOpExcutioner<T>::execRandom(int opNum, Nd4jPointer state, T *x, Nd4jLong *xShapeBuffer, T *y, Nd4jLong *yShapeBuffer, T *z, Nd4jLong *zShapeBuffer, T *extraArguments) {
    functions::random::RandomFunction<T>::execTransform(opNum, state, x, xShapeBuffer, y, yShapeBuffer, z, zShapeBuffer, extraArguments);
}

template<typename T>
void NativeOpExcutioner<T>::execReduce3(int opNum, T *x, Nd4jLong *xShapeInfo, T *extraParamsVals, T *y, Nd4jLong *yShapeInfo, T *result, Nd4jLong *resultShapeInfoBuffer, int *dimension, int dimensionLength) {
    functions::reduce3::Reduce3<T>::exec(opNum, x, xShapeInfo, extraParamsVals, y, yShapeInfo, result, resultShapeInfoBuffer, dimension, dimensionLength);
}






