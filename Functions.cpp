////////////////////////////////////////////////////
// Functions.cpp
// Sample functions implementation file for example AmiBroker plug-in
//
// Copyright (C)2001 Tomasz Janeczko, amibroker.com
// All rights reserved.
//
// Last modified: 2001-09-24 TJ
// 
// You may use this code in your own projects provided that:
//
// 1. You are registered user of AmiBroker
// 2. The software you write using it is for personal, noncommercial use only
//
// For commercial use you have to obtain a separate license from Amibroker.com
//
////////////////////////////////////////////////////

#include "stdafx.h"
#include "Plugin.h"

#include "ta_func.h"

// Helper function
int SkipEmptyValues( int nSize, float *Src, float *Dst )
{
	int i;

	for( i = 0; i < nSize && IS_EMPTY( Src[ i ] ); i++ )
	{
		Dst[ i ] = EMPTY_VAL;
	}

	return i;
}


///////////////////////////////////////////
// Each AFL function has the following prototype:
//
// AmiVar FunctionName( int NumArgs, AmiVar *ArgsTable )
//
// You can define as many functions as you want.
// To make them visible you should add them to the function
// table at the bottom of this file
//
///////////////////////////////////////////////


// ExampleMA( array, periods )
// This function demonstrates
// how to calculate 
// simple moving average

//funcXYZ 
// X: in float* s   Y: option int s   Z:out double* s


/*

TA_RetCode TA_FUNCNAME( int    startIdx,
                    int    endIdx,
                    const double inReal[],
                    int           optInTimePeriod, ///* From 2 to 100000 
					int          *outBegIdx,
					int          *outNBElement,
					double        outReal[] );

*/

#define FUNC111(TA)	\
AmiVar TAAB_##TA##( int NumArgs, AmiVar *ArgsTable )		\
{														\
    AmiVar result;										\
	result.type = VAR_ARRAY;							\
    result = gSite.AllocArrayResult();					\
	int nSize = gSite.GetArraySize();					\
	float * f1 = ArgsTable[ 0 ].array;					\
	float i1 = ArgsTable[1].val;						\
														\
	int j = SkipEmptyValues( nSize, f1, result.array );	\
														\
	/* make double array ,later to be converted */		\
	double * res = new double[nSize];					\
														\
	int lookback = TA_##TA##_Lookback(i1);				\
														\
	int startidx = j + lookback;						\
    int endidx = nSize - 1;								\
	int begidx;											\
	int nb;												\
														\
	if ( startidx < endidx) int retCode = ::TA_S_##TA##(startidx, endidx, f1, i1, &begidx, &nb, res + startidx); \
														\
	for(int i=0;i< startidx;i++)	result.array[i]=EMPTY_VAL;				\
	for(int i=startidx;i<nSize ;i++)	result.array[i]= (float) res[i];	\
	delete [] res;										\
    return result;										\
}

/*

TA_RetCode TA_FUNCNAME(int    startIdx,
					int    endIdx,
					const double inReal[],
					int          *outBegIdx,
					int          *outNBElement,
					double        outReal[] );

*/


#define FUNC101(TA)	\
AmiVar TAAB_##TA##(int NumArgs, AmiVar *ArgsTable)		\
{														\
	AmiVar result;										\
	result.type = VAR_ARRAY;							\
	result = gSite.AllocArrayResult();					\
	int nSize = gSite.GetArraySize();					\
	float * f1 = ArgsTable[0].array;						\
														\
	\
	int j = SkipEmptyValues(nSize, f1, result.array);	\
	\
	/* make double array ,later to be converted */		\
	double * res = new double[nSize];					\
	\
	int lookback = TA_##TA##_Lookback();				\
	\
	int startidx = j + lookback;						\
	int endidx = nSize - 1;								\
	int begidx;											\
	int nb;												\
	\
	if ( startidx < endidx) int retCode = ::TA_S_##TA##(startidx, endidx, f1, &begidx, &nb, res + startidx); \
	\
for (int i = 0; i< startidx; i++)	result.array[i] = EMPTY_VAL;				\
for (int i = startidx; i<nSize; i++)	result.array[i] = (float)res[i];	\
	delete[] res;										\
	return result;										\
}

#define FUNC121(TA)	\
	AmiVar TAAB_##TA##(int NumArgs, AmiVar *ArgsTable)		\
{														\
	AmiVar result;										\
	result.type = VAR_ARRAY;							\
	result = gSite.AllocArrayResult();					\
	int nSize = gSite.GetArraySize();					\
	float * f1 = ArgsTable[0].array;					\
	float i1 = ArgsTable[1].val;						\
	float i2 = ArgsTable[2].val;						\
	\
	\
	int j = SkipEmptyValues(nSize, f1, result.array);	\
	\
	/* make double array ,later to be converted */		\
	double * res = new double[nSize];					\
	\
	int lookback = TA_##TA##_Lookback(i1,i2);				\
	\
	int startidx = j + lookback;						\
	int endidx = nSize - 1;								\
	int begidx;											\
	int nb;												\
	\
	if ( startidx < endidx) int retCode = ::TA_S_##TA##(startidx, endidx, f1, i1, i2, &begidx, &nb, res + startidx); \
	\
for (int i = 0; i< startidx; i++)	result.array[i] = EMPTY_VAL;				\
for (int i = startidx; i<nSize; i++)	result.array[i] = (float)res[i];	\
	delete[] res;										\
	return result;										\
}

#define FUNC121EMA(TA)	\
	AmiVar TAAB_##TA##(int NumArgs, AmiVar *ArgsTable)		\
{														\
	AmiVar result;										\
	result.type = VAR_ARRAY;							\
	result = gSite.AllocArrayResult();					\
	int nSize = gSite.GetArraySize();					\
	float * f1 = ArgsTable[0].array;					\
	float i1 = ArgsTable[1].val;						\
	float i2 = ArgsTable[2].val;						\
	\
	\
	int j = SkipEmptyValues(nSize, f1, result.array);	\
	\
	/* make double array ,later to be converted */		\
	double * res = new double[nSize];					\
	\
	int lookback = TA_##TA##_Lookback(i1, i2, ::TA_MAType_EMA);				\
	\
	int startidx = j + lookback;						\
	int endidx = nSize - 1;								\
	int begidx;											\
	int nb;												\
	\
	if ( startidx < endidx) int retCode = ::TA_S_##TA##(startidx, endidx, f1, i1, i2, ::TA_MAType_EMA, &begidx, &nb, res + startidx); \
	\
for (int i = 0; i< startidx; i++)	result.array[i] = EMPTY_VAL;				\
for (int i = startidx; i<nSize; i++)	result.array[i] = (float)res[i];	\
	delete[] res;										\
	return result;										\
}


#define FUNChl11(TA)	\
	AmiVar TAAB_##TA##(int NumArgs, AmiVar *ArgsTable)		\
{														\
	AmiVar result;										\
	result.type = VAR_ARRAY;							\
	result = gSite.AllocArrayResult();					\
	int nSize = gSite.GetArraySize();					\
	float * hi = gSite.GetStockArray(1);				\
	float * lo = gSite.GetStockArray(2);				\
	float i1 = ArgsTable[0].val;							\
	\
	\
	int j1 = SkipEmptyValues(nSize, hi, result.array);	\
	int j2 = SkipEmptyValues(nSize, lo, result.array);	\
	int j = (j1 > j2) ? j1 : j2;						\
	\
	/* make double array ,later to be converted */		\
	double * res = new double[nSize];					\
	\
	int lookback = TA_##TA##_Lookback(i1);				\
	\
	int startidx = j + lookback;						\
	int endidx = nSize - 1;								\
	int begidx;											\
	int nb;												\
	\
	if ( startidx < endidx) int retCode = ::TA_S_##TA##(startidx, endidx, hi, lo, i1, &begidx, &nb, res + startidx); \
	\
for (int i = 0; i< startidx; i++)	result.array[i] = EMPTY_VAL;				\
for (int i = startidx; i<nSize; i++)	result.array[i] = (float)res[i];	\
	delete[] res;										\
	return result;										\
}


#define FUNChl21(TA)	\
	AmiVar TAAB_##TA##(int NumArgs, AmiVar *ArgsTable)		\
{														\
	AmiVar result;										\
	result.type = VAR_ARRAY;							\
	result = gSite.AllocArrayResult();					\
	int nSize = gSite.GetArraySize();					\
	float * hi = gSite.GetStockArray(1);						\
	float * lo = gSite.GetStockArray(2);						\
	float i1 = ArgsTable[0].val;							\
	float i2 = ArgsTable[1].val;							\
	\
	\
	int j1 = SkipEmptyValues(nSize, hi, result.array);	\
	int j2 = SkipEmptyValues(nSize, lo, result.array);	\
	int j = (j1 > j2) ? j1 : j2;						\
	\
	/* make double array ,later to be converted */		\
	double * res = new double[nSize];					\
	\
	int lookback = TA_##TA##_Lookback(i1,i2);				\
	\
	int startidx = j + lookback;						\
	int endidx = nSize - 1;								\
	int begidx;											\
	int nb;												\
	\
	if ( startidx < endidx) int retCode = ::TA_S_##TA##(startidx, endidx, hi, lo, i1, i2, &begidx, &nb, res + startidx); \
	\
for (int i = 0; i< startidx; i++)	result.array[i] = EMPTY_VAL;				\
for (int i = startidx; i<nSize; i++)	result.array[i] = (float)res[i];	\
	delete[] res;										\
	return result;										\
}

#define FUNChlc11(TA)	\
	AmiVar TAAB_##TA##(int NumArgs, AmiVar *ArgsTable)		\
{														\
	AmiVar result;										\
	result.type = VAR_ARRAY;							\
	result = gSite.AllocArrayResult();					\
	int nSize = gSite.GetArraySize();					\
	float * hi = gSite.GetStockArray(1);				\
	float * lo = gSite.GetStockArray(2);				\
	float * c = gSite.GetStockArray(3);					\
	float i1 = ArgsTable[0].val;							\
	\
	int j1 = SkipEmptyValues(nSize, hi, result.array);	\
	int j2 = SkipEmptyValues(nSize, lo, result.array);	\
	int j3 = SkipEmptyValues(nSize, c, result.array);	\
	int j = (j1 > j2) ? j1 : j2;						\
	j = (j3 > j) ? j3 : j;								\
	\
	/* make double array ,later to be converted */		\
	double * res = new double[nSize];					\
	\
	int lookback = TA_##TA##_Lookback(i1);				\
	\
	int startidx = j + lookback;						\
	int endidx = nSize - 1;								\
	int begidx;											\
	int nb;												\
	\
	if ( startidx < endidx) int retCode = ::TA_S_##TA##(startidx, endidx, hi, lo, c, i1, &begidx, &nb, res + startidx); \
	\
for (int i = 0; i< startidx; i++)	result.array[i] = EMPTY_VAL;				\
for (int i = startidx; i<nSize; i++)	result.array[i] = (float)res[i];	\
	delete[] res;										\
	return result;										\
}


#define FUNChlc31(TA)	\
	AmiVar TAAB_##TA##(int NumArgs, AmiVar *ArgsTable)		\
{														\
	AmiVar result;										\
	result.type = VAR_ARRAY;							\
	result = gSite.AllocArrayResult();					\
	int nSize = gSite.GetArraySize();					\
	float * hi = gSite.GetStockArray(1);				\
	float * lo = gSite.GetStockArray(2);				\
	float * c = gSite.GetStockArray(3);				\
	float i1 = ArgsTable[0].val;							\
	float i2 = ArgsTable[1].val;							\
	float i3 = ArgsTable[2].val;							\
	\
	int j1 = SkipEmptyValues(nSize, hi, result.array);	\
	int j2 = SkipEmptyValues(nSize, lo, result.array);	\
	int j3 = SkipEmptyValues(nSize, c, result.array);	\
	int j = (j1 > j2) ? j1 : j2;						\
	j = (j3 > j) ? j3 : j;								\
	\
	/* make double array ,later to be converted */		\
	double * res = new double[nSize];					\
	\
	int lookback = TA_##TA##_Lookback(i1,i2,i3);				\
	\
	int startidx = j + lookback;						\
	int endidx = nSize - 1;								\
	int begidx;											\
	int nb;												\
	\
	if ( startidx < endidx) int retCode = ::TA_S_##TA##(startidx, endidx, hi, lo, c, i1, i2, i3, &begidx, &nb, res + startidx); \
	\
for (int i = 0; i< startidx; i++)	result.array[i] = EMPTY_VAL;				\
for (int i = startidx; i<nSize; i++)	result.array[i] = (float)res[i];	\
	delete[] res;										\
	return result;										\
}

#define FUNChl12_1(TA)	\
	AmiVar TAAB_##TA##_1(int NumArgs, AmiVar *ArgsTable)		\
{														\
	AmiVar result;										\
	result.type = VAR_ARRAY;							\
	result = gSite.AllocArrayResult();					\
	int nSize = gSite.GetArraySize();					\
	float * hi = gSite.GetStockArray(1);				\
	float * lo = gSite.GetStockArray(2);				\
	float i1 = ArgsTable[0].val;							\
	\
	int j1 = SkipEmptyValues(nSize, hi, result.array);	\
	int j2 = SkipEmptyValues(nSize, lo, result.array);	\
	int j = (j1 > j2) ? j1 : j2;						\
	\
	/* make double array ,later to be converted */		\
	double * res = new double[nSize];					\
	double * res1 = new double[nSize];					\
	\
	int lookback = TA_##TA##_Lookback(i1);				\
	\
	int startidx = j + lookback;						\
	int endidx = nSize - 1;								\
	int begidx;											\
	int nb;												\
	\
	if ( startidx < endidx) int retCode = ::TA_S_##TA##(startidx, endidx, hi, lo,  i1, &begidx, &nb, res + startidx, res1 + startidx ); \
	\
for (int i = 0; i< startidx; i++)	result.array[i] = EMPTY_VAL;				\
	/*  FUNC212_1 returns first res    */  \
for (int i = startidx; i<nSize; i++)	result.array[i] = (float)res[i];	\
	delete[] res;										\
	delete[] res1;										\
	return result;										\
}

#define FUNChl12_2(TA)	\
	AmiVar TAAB_##TA##_2(int NumArgs, AmiVar *ArgsTable)		\
{														\
	AmiVar result;										\
	result.type = VAR_ARRAY;							\
	result = gSite.AllocArrayResult();					\
	int nSize = gSite.GetArraySize();					\
	float * hi = gSite.GetStockArray(1);				\
	float * lo = gSite.GetStockArray(2);				\
	float i1 = ArgsTable[0].val;							\
	\
	int j1 = SkipEmptyValues(nSize, hi, result.array);	\
	int j2 = SkipEmptyValues(nSize, lo, result.array);	\
	int j = (j1 > j2) ? j1 : j2;						\
	\
	/* make double array ,later to be converted */		\
	double * res = new double[nSize];					\
	double * res1 = new double[nSize];					\
	\
	int lookback = TA_##TA##_Lookback(i1);				\
	\
	int startidx = j + lookback;						\
	int endidx = nSize - 1;								\
	int begidx;											\
	int nb;												\
	\
	if ( startidx < endidx) int retCode = ::TA_S_##TA##(startidx, endidx, hi, lo, i1, &begidx, &nb, res + startidx, res1 + startidx); \
	\
for (int i = 0; i< startidx; i++)	result.array[i] = EMPTY_VAL;				\
	/*  FUNC212_1 returns first res1    */  \
for (int i = startidx; i<nSize; i++)	result.array[i] = (float)res1[i];	\
	delete[] res;										\
	delete[] res1;										\
	return result;										\
}

#define FUNC102_1(TA)	\
	AmiVar TAAB_##TA##_1(int NumArgs, AmiVar *ArgsTable)		\
{														\
	AmiVar result;										\
	result.type = VAR_ARRAY;							\
	result = gSite.AllocArrayResult();					\
	int nSize = gSite.GetArraySize();					\
	float * f1 = ArgsTable[0].array;					\
	\
	int j = SkipEmptyValues(nSize, f1, result.array);	\
	\
	/* make double array ,later to be converted */		\
	double * res = new double[nSize];					\
	double * res1 = new double[nSize];					\
	\
	int lookback = TA_##TA##_Lookback();				\
	\
	int startidx = j + lookback;						\
	int endidx = nSize - 1;								\
	int begidx;											\
	int nb;												\
	\
	if ( startidx < endidx) int retCode = ::TA_S_##TA##(startidx, endidx, f1, &begidx, &nb, res + startidx, res1 + startidx); \
	\
for (int i = 0; i< startidx; i++)	result.array[i] = EMPTY_VAL;				\
	/*  FUNC212_1 returns first res    */  \
for (int i = startidx; i<nSize; i++)	result.array[i] = (float)res[i];	\
	delete[] res;										\
	delete[] res1;										\
	return result;										\
}

#define FUNC102_2(TA)	\
	AmiVar TAAB_##TA##_2(int NumArgs, AmiVar *ArgsTable)		\
{														\
	AmiVar result;										\
	result.type = VAR_ARRAY;							\
	result = gSite.AllocArrayResult();					\
	int nSize = gSite.GetArraySize();					\
	float * f1 = ArgsTable[0].array;					\
	\
	int j = SkipEmptyValues(nSize, f1, result.array);	\
	\
	/* make double array ,later to be converted */		\
	double * res = new double[nSize];					\
	double * res1 = new double[nSize];					\
	\
	int lookback = TA_##TA##_Lookback();				\
	\
	int startidx = j + lookback;						\
	int endidx = nSize - 1;								\
	int begidx;											\
	int nb;												\
	\
	if ( startidx < endidx) int retCode = ::TA_S_##TA##(startidx, endidx, f1, &begidx, &nb, res + startidx, res1 + startidx ); \
	\
for (int i = 0; i< startidx; i++)	result.array[i] = EMPTY_VAL;				\
	/*  FUNC212_1 returns first res    */  \
for (int i = startidx; i<nSize; i++)	result.array[i] = (float)res1[i];	\
	delete[] res;										\
	delete[] res1;										\
	return result;										\
}

#define FUNCohlc01(TA)	\
	AmiVar TAAB_##TA##(int NumArgs, AmiVar *ArgsTable)		\
{														\
	AmiVar result;										\
	result.type = VAR_ARRAY;							\
	result = gSite.AllocArrayResult();					\
	int nSize = gSite.GetArraySize();					\
	float * o = gSite.GetStockArray(0);				\
	float * hi = gSite.GetStockArray(1);				\
	float * lo = gSite.GetStockArray(2);				\
	float * c = gSite.GetStockArray(3);				\
	\
	\
	int j1 = SkipEmptyValues(nSize, o, result.array);	\
	int j2 = SkipEmptyValues(nSize, hi, result.array);	\
	int j3 = SkipEmptyValues(nSize, lo, result.array);	\
	int j4 = SkipEmptyValues(nSize, c, result.array);	\
	int j = (j1 > j2) ? j1 : j2;						\
	j = (j3 > j) ? j3 : j;								\
	j = (j4 > j) ? j4 : j;								\
	\
	/* make double array ,later to be converted */		\
	double * res = new double[nSize];					\
	\
	int lookback = TA_##TA##_Lookback();				\
	\
	int startidx = j + lookback;						\
	int endidx = nSize - 1;								\
	int begidx;											\
	int nb;												\
	\
	if ( startidx < endidx) int retCode = ::TA_S_##TA##(startidx, endidx, o, hi, lo, c, &begidx, &nb, res + startidx); \
	\
for (int i = 0; i< startidx; i++)	result.array[i] = EMPTY_VAL;				\
for (int i = startidx; i<nSize; i++)	result.array[i] = (float)res[i];	\
	delete[] res;										\
	return result;										\
}

#define FUNChlcv11(TA)	\
	AmiVar TAAB_##TA##(int NumArgs, AmiVar *ArgsTable)		\
{														\
	AmiVar result;										\
	result.type = VAR_ARRAY;							\
	result = gSite.AllocArrayResult();					\
	int nSize = gSite.GetArraySize();					\
	float * hi = gSite.GetStockArray(1);				\
	float * lo = gSite.GetStockArray(2);				\
	float * c = gSite.GetStockArray(3);				\
	float * v = gSite.GetStockArray(4);				\
	float i1 = ArgsTable[0].val;							\
	\
	\
	int j1 = SkipEmptyValues(nSize, hi, result.array);	\
	int j2 = SkipEmptyValues(nSize, lo, result.array);	\
	int j3 = SkipEmptyValues(nSize, c, result.array);	\
	int j4 = SkipEmptyValues(nSize, v, result.array);	\
	int j = (j1 > j2) ? j1 : j2;						\
	j = (j3 > j) ? j3 : j;								\
	j = (j4 > j) ? j4 : j;								\
	\
	/* make double array ,later to be converted */		\
	double * res = new double[nSize];					\
	\
	int lookback = TA_##TA##_Lookback(i1);				\
	\
	int startidx = j + lookback;						\
	int endidx = nSize - 1;								\
	int begidx;											\
	int nb;												\
	\
	if ( startidx < endidx) int retCode = ::TA_S_##TA##(startidx, endidx, hi, lo, c, v, i1, &begidx, &nb, res + startidx); \
	\
for (int i = 0; i< startidx; i++)	result.array[i] = EMPTY_VAL;				\
for (int i = startidx; i<nSize; i++)	result.array[i] = (float)res[i];	\
	delete[] res;										\
	return result;										\
}

#define FUNChlcv01(TA)	\
	AmiVar TAAB_##TA##(int NumArgs, AmiVar *ArgsTable)		\
{														\
	AmiVar result;										\
	result.type = VAR_ARRAY;							\
	result = gSite.AllocArrayResult();					\
	int nSize = gSite.GetArraySize();					\
	float * hi = gSite.GetStockArray(1);				\
	float * lo = gSite.GetStockArray(2);				\
	float * c = gSite.GetStockArray(3);				\
	float * v = gSite.GetStockArray(4);				\
	\
	int j1 = SkipEmptyValues(nSize, hi, result.array);	\
	int j2 = SkipEmptyValues(nSize, lo, result.array);	\
	int j3 = SkipEmptyValues(nSize, c, result.array);	\
	int j4 = SkipEmptyValues(nSize, v, result.array);	\
	int j = (j1 > j2) ? j1 : j2;						\
	j = (j3 > j) ? j3 : j;								\
	j = (j4 > j) ? j4 : j;								\
	\
	/* make double array ,later to be converted */		\
	double * res = new double[nSize];					\
	\
	int lookback = TA_##TA##_Lookback();				\
	\
	int startidx = j + lookback;						\
	int endidx = nSize - 1;								\
	int begidx;											\
	int nb;												\
	\
	if ( startidx < endidx) int retCode = ::TA_S_##TA##(startidx, endidx, hi, lo, c, v, &begidx, &nb, res + startidx); \
	\
for (int i = 0; i< startidx; i++)	result.array[i] = EMPTY_VAL;				\
for (int i = startidx; i<nSize; i++)	result.array[i] = (float)res[i];	\
	delete[] res;										\
	return result;										\
}

#define FUNChlcv11(TA)	\
	AmiVar TAAB_##TA##(int NumArgs, AmiVar *ArgsTable)		\
{														\
	AmiVar result;										\
	result.type = VAR_ARRAY;							\
	result = gSite.AllocArrayResult();					\
	int nSize = gSite.GetArraySize();					\
	float * hi = gSite.GetStockArray(1);				\
	float * lo = gSite.GetStockArray(2);				\
	float * c = gSite.GetStockArray(3);				\
	float * v = gSite.GetStockArray(4);				\
	float i1 = ArgsTable[0].val;							\
	\
	\
	int j1 = SkipEmptyValues(nSize, hi, result.array);	\
	int j2 = SkipEmptyValues(nSize, lo, result.array);	\
	int j3 = SkipEmptyValues(nSize, c, result.array);	\
	int j4 = SkipEmptyValues(nSize, v, result.array);	\
	int j = (j1 > j2) ? j1 : j2;						\
	j = (j3 > j) ? j3 : j;								\
	j = (j4 > j) ? j4 : j;								\
	\
	/* make double array ,later to be converted */		\
	double * res = new double[nSize];					\
	\
	int lookback = TA_##TA##_Lookback(i1);				\
	\
	int startidx = j + lookback;						\
	int endidx = nSize - 1;								\
	int begidx;											\
	int nb;												\
	\
	if ( startidx < endidx) int retCode = ::TA_S_##TA##(startidx, endidx, hi, lo, c, v, i1, &begidx, &nb, res + startidx); \
	\
for (int i = 0; i< startidx; i++)	result.array[i] = EMPTY_VAL;				\
for (int i = startidx; i<nSize; i++)	result.array[i] = (float)res[i];	\
	delete[] res;										\
	return result;										\
}

#define FUNChlcv21(TA)	\
	AmiVar TAAB_##TA##(int NumArgs, AmiVar *ArgsTable)		\
{														\
	AmiVar result;										\
	result.type = VAR_ARRAY;							\
	result = gSite.AllocArrayResult();					\
	int nSize = gSite.GetArraySize();					\
	float * hi = gSite.GetStockArray(1);				\
	float * lo = gSite.GetStockArray(2);				\
	float * c = gSite.GetStockArray(3);				\
	float * v = gSite.GetStockArray(4);				\
	float i1 = ArgsTable[0].val;							\
	float i2 = ArgsTable[1].val;							\
	\
	int j1 = SkipEmptyValues(nSize, hi, result.array);	\
	int j2 = SkipEmptyValues(nSize, lo, result.array);	\
	int j3 = SkipEmptyValues(nSize, c, result.array);	\
	int j4 = SkipEmptyValues(nSize, v, result.array);	\
	int j = (j1 > j2) ? j1 : j2;						\
	j = (j3 > j) ? j3 : j;								\
	j = (j4 > j) ? j4 : j;								\
	\
	/* make double array ,later to be converted */		\
	double * res = new double[nSize];					\
	\
	int lookback = TA_##TA##_Lookback(i1,i2);				\
	\
	int startidx = j + lookback;						\
	int endidx = nSize - 1;								\
	int begidx;											\
	int nb;												\
	\
	if ( startidx < endidx) int retCode = ::TA_S_##TA##(startidx, endidx, hi, lo, c, v, i1, i2, &begidx, &nb, res + startidx); \
	\
for (int i = 0; i< startidx; i++)	result.array[i] = EMPTY_VAL;				\
for (int i = startidx; i<nSize; i++)	result.array[i] = (float)res[i];	\
	delete[] res;										\
	return result;										\
}

#define FUNC1v01(TA)	\
	AmiVar TAAB_##TA##(int NumArgs, AmiVar *ArgsTable)		\
{														\
	AmiVar result;										\
	result.type = VAR_ARRAY;							\
	result = gSite.AllocArrayResult();					\
	int nSize = gSite.GetArraySize();					\
	float * f1 = ArgsTable[0].array; \
	float * v = gSite.GetStockArray(4);				\
	\
	int j1 = SkipEmptyValues(nSize, f1, result.array);	\
	int j2 = SkipEmptyValues(nSize, v, result.array);	\
	int j = (j1 > j2) ? j1 : j2;						\
	\
	/* make double array ,later to be converted */		\
	double * res = new double[nSize];					\
	\
	int lookback = TA_##TA##_Lookback();				\
	\
	int startidx = j + lookback;						\
	int endidx = nSize - 1;								\
	int begidx;											\
	int nb;												\
	\
	if ( startidx < endidx) int retCode = ::TA_S_##TA##(startidx, endidx, f1, v, &begidx, &nb, res + startidx); \
	\
for (int i = 0; i< startidx; i++)	result.array[i] = EMPTY_VAL;				\
for (int i = startidx; i<nSize; i++)	result.array[i] = (float)res[i];	\
	delete[] res;										\
	return result;										\
}


#define FUNCohlc1i1(TA)	\
	AmiVar TAAB_##TA##(int NumArgs, AmiVar *ArgsTable)		\
{														\
	AmiVar result;										\
	result.type = VAR_ARRAY;							\
	result = gSite.AllocArrayResult();					\
	int nSize = gSite.GetArraySize();					\
	float * o = gSite.GetStockArray(0);				\
	float * hi = gSite.GetStockArray(1);				\
	float * lo = gSite.GetStockArray(2);				\
	float * c = gSite.GetStockArray(3);				\
	float i1 = ArgsTable[0].val;							\
	\
	\
	int j1 = SkipEmptyValues(nSize, o, result.array);	\
	int j2 = SkipEmptyValues(nSize, hi, result.array);	\
	int j3 = SkipEmptyValues(nSize, lo, result.array);	\
	int j4 = SkipEmptyValues(nSize, c, result.array);	\
	int j = (j1 > j2) ? j1 : j2;						\
	j = (j3 > j) ? j3 : j;								\
	j = (j4 > j) ? j4 : j;								\
	\
	/* make double array ,later to be converted */		\
	int * res = new int[nSize];					\
	\
	int lookback = TA_##TA##_Lookback(i1);				\
	\
	int startidx = j + lookback;						\
	int endidx = nSize - 1;								\
	int begidx;											\
	int nb;												\
	\
	if ( startidx < endidx) int retCode = ::TA_S_##TA##(startidx, endidx, o, hi, lo, c, i1, &begidx, &nb, res + startidx); \
	\
for (int i = 0; i< startidx; i++)	result.array[i] = EMPTY_VAL;				\
for (int i = startidx; i<nSize; i++)	result.array[i] = (float)res[i];	\
	delete[] res;										\
	return result;										\
}

#define FUNCohlc0i1(TA)	\
	AmiVar TAAB_##TA##(int NumArgs, AmiVar *ArgsTable)		\
{														\
	AmiVar result;										\
	result.type = VAR_ARRAY;							\
	result = gSite.AllocArrayResult();					\
	int nSize = gSite.GetArraySize();					\
	float * o = gSite.GetStockArray(0);				\
	float * hi = gSite.GetStockArray(1);				\
	float * lo = gSite.GetStockArray(2);				\
	float * c = gSite.GetStockArray(3);				\
	\
	\
	int j1 = SkipEmptyValues(nSize, o, result.array);	\
	int j2 = SkipEmptyValues(nSize, hi, result.array);	\
	int j3 = SkipEmptyValues(nSize, lo, result.array);	\
	int j4 = SkipEmptyValues(nSize, c, result.array);	\
	int j = (j1 > j2) ? j1 : j2;						\
	j = (j3 > j) ? j3 : j;								\
	j = (j4 > j) ? j4 : j;								\
	\
	/* make double array ,later to be converted */		\
	int * res = new int[nSize];					\
	\
	int lookback = TA_##TA##_Lookback();				\
	\
	int startidx = j + lookback;						\
	int endidx = nSize - 1;								\
	int begidx;											\
	int nb;												\
	\
	if ( startidx < endidx) int retCode = ::TA_S_##TA##(startidx, endidx, o, hi, lo, c, &begidx, &nb, res + startidx); \
	\
for (int i = 0; i< startidx; i++)	result.array[i] = EMPTY_VAL;				\
for (int i = startidx; i<nSize; i++)	result.array[i] = (float)res[i];	\
	delete[] res;										\
	return result;										\
}





////////////////////////////////actual funcs

//Overlap Studies

//BBANDS               Bollinger Bands

//DEMA                 Double Exponential Moving Average
FUNC111(DEMA)
//EMA                  Exponential Moving Average
FUNC111(EMA)
//HT_TRENDLINE         Hilbert Transform - Instantaneous Trendline
FUNC101(HT_TRENDLINE)
//KAMA                 Kaufman Adaptive Moving Average
FUNC111(KAMA)
//MAMA                 MESA Adaptive Moving Average

//MAVP                 Moving average with variable period

//MIDPOINT             MidPoint over period

//MIDPRICE             Midpoint Price over period

//SAR                  Parabolic SAR
FUNChl21(SAR)
//SAREXT               Parabolic SAR - Extended

//SMA                  Simple Moving Average
FUNC111(SMA)
//T3                   Triple Exponential Moving Average(T3)
FUNC121(T3)
//TEMA                 Triple Exponential Moving Average
FUNC111(TEMA)
//TRIMA                Triangular Moving Average
FUNC111(TRIMA)
//WMA                  Weighted Moving Average
FUNC111(WMA)

//Momentum Indicators

//ADX                  Average Directional Movement Index
FUNChlc11(ADX)
//ADXR                 Average Directional Movement Index Rating
FUNChlc11(ADXR)
//APO                  Absolute Price Oscillator

//AROON                Aroon
FUNChl12_1(AROON)
FUNChl12_2(AROON)

//AROONOSC             Aroon Oscillator
FUNChl11(AROONOSC)

//BOP                  Balance Of Power
FUNCohlc01(BOP)
//CCI                  Commodity Channel Index
FUNChlc11(CCI)
//CMO                  Chande Momentum Oscillator
FUNC111(CMO)
//DX                   Directional Movement Index
FUNChlc11(DX)
//MACD                 Moving Average Convergence / Divergence

//MACDEXT              MACD with controllable MA type

//MACDFIX              Moving Average Convergence / Divergence Fix 12 / 26

//MFI                  Money Flow Index
FUNChlcv11(MFI)
//MINUS_DI             Minus Directional Indicator
//MINUS_DM             Minus Directional Movement
//MOM                  Momentum
FUNC111(MOM)
//PLUS_DI              Plus Directional Indicator
//PLUS_DM              Plus Directional Movement
//PPO                  Percentage Price Oscillator
FUNC121EMA(PPO)
//ROC                  Rate of change : ((price / prevPrice) - 1) * 100
FUNC111(ROC)
//ROCP                 Rate of change Percentage : (price - prevPrice) / prevPrice

//ROCR                 Rate of change ratio : (price / prevPrice)

//ROCR100              Rate of change ratio 100 scale : (price / prevPrice) * 100

//RSI                  Relative Strength Index
FUNC111(RSI)
//STOCH                Stochastic

//STOCHF               Stochastic Fast

//STOCHRSI             Stochastic Relative Strength Index

//TRIX                 1 - day Rate - Of - Change(ROC) of a Triple Smooth EMA
FUNC111(TRIX)
//ULTOSC               Ultimate Oscillator
FUNChlc31(ULTOSC)
//WILLR                Williams' %R
FUNChlc11(WILLR)

//Volume Indicators

//AD                   Chaikin A / D Line
FUNChlcv01(AD)
//ADOSC                Chaikin A / D Oscillator
FUNChlcv21(ADOSC)
//OBV                  On Balance Volume
FUNC1v01(OBV)

//Cycle Indicators

//HT_DCPERIOD          Hilbert Transform - Dominant Cycle Period
FUNC101(HT_DCPERIOD)
//HT_DCPHASE           Hilbert Transform - Dominant Cycle Phase
FUNC101(HT_DCPHASE)
//HT_PHASOR            Hilbert Transform - Phasor Components : InPhase , Quadrature
FUNC102_1(HT_PHASOR)
FUNC102_2(HT_PHASOR)
//HT_SINE              Hilbert Transform - SineWave : Sine , LeadSine
FUNC102_1(HT_SINE)
FUNC102_2(HT_SINE)
//HT_TRENDLINE - Hilbert Transform - Instantaneous Trendline : SEE Overlap Studies
//FUNC101(HT_TRENDLINE) 
//HT_TRENDMODE         Hilbert Transform - Trend vs Cycle Mode
//INT_out FUNC101(HT_TRENDMODE)

//Volatility Indicators

//ATR                  Average True Range
FUNChlc11(ATR)
//NATR                 Normalized Average True Range
FUNChlc11(NATR)
//TRANGE               True Range
//FUNChlc01(TRANGE)

//Pattern Recognition

//CDL2CROWS            Two Crows
FUNCohlc0i1(CDL2CROWS)
//CDL3BLACKCROWS       Three Black Crows
FUNCohlc0i1(CDL3BLACKCROWS)
//CDL3INSIDE           Three Inside Up / Down
FUNCohlc0i1(CDL3INSIDE)
//CDL3LINESTRIKE       Three - Line Strike
FUNCohlc0i1(CDL3LINESTRIKE)
//CDL3OUTSIDE          Three Outside Up / Down
FUNCohlc0i1(CDL3OUTSIDE)
//CDL3STARSINSOUTH     Three Stars In The South
FUNCohlc0i1(CDL3STARSINSOUTH)
//CDL3WHITESOLDIERS    Three Advancing White Soldiers
FUNCohlc0i1(CDL3WHITESOLDIERS)
//CDLABANDONEDBABY     Abandoned Baby
FUNCohlc1i1(CDLABANDONEDBABY)
//CDLADVANCEBLOCK      Advance Block
FUNCohlc0i1(CDLADVANCEBLOCK)
//CDLBELTHOLD          Belt - hold
FUNCohlc0i1(CDLBELTHOLD)
//CDLBREAKAWAY         Breakaway
FUNCohlc0i1(CDLBREAKAWAY)
//CDLCLOSINGMARUBOZU   Closing Marubozu
FUNCohlc0i1(CDLCLOSINGMARUBOZU)
//CDLCONCEALBABYSWALL  Concealing Baby Swallow
FUNCohlc0i1(CDLCONCEALBABYSWALL)
//CDLCOUNTERATTACK     Counterattack
FUNCohlc0i1(CDLCOUNTERATTACK)
//CDLDARKCLOUDCOVER    Dark Cloud Cover
FUNCohlc1i1(CDLDARKCLOUDCOVER)
//CDLDOJI              Doji
FUNCohlc0i1(CDLDOJI)
//CDLDOJISTAR          Doji Star
FUNCohlc0i1(CDLDOJISTAR)
//CDLDRAGONFLYDOJI     Dragonfly Doji
FUNCohlc0i1(CDLDRAGONFLYDOJI)
//CDLENGULFING         Engulfing Pattern
FUNCohlc0i1(CDLENGULFING)
//CDLEVENINGDOJISTAR   Evening Doji Star
FUNCohlc1i1(CDLEVENINGDOJISTAR)
//CDLEVENINGSTAR       Evening Star
FUNCohlc1i1(CDLEVENINGSTAR)
//CDLGAPSIDESIDEWHITE  Up / Down - gap side - by - side white lines
FUNCohlc0i1(CDLGAPSIDESIDEWHITE)
//CDLGRAVESTONEDOJI    Gravestone Doji
FUNCohlc0i1(CDLGRAVESTONEDOJI)
//CDLHAMMER            Hammer
FUNCohlc0i1(CDLHAMMER)
//CDLHANGINGMAN        Hanging Man
FUNCohlc0i1(CDLHANGINGMAN)
//CDLHARAMI            Harami Pattern
FUNCohlc0i1(CDLHARAMI)
//CDLHARAMICROSS       Harami Cross Pattern
FUNCohlc0i1(CDLHARAMICROSS)
//CDLHIGHWAVE          High - Wave Candle
FUNCohlc0i1(CDLHIGHWAVE)
//CDLHIKKAKE           Hikkake Pattern
FUNCohlc0i1(CDLHIKKAKE)
//CDLHIKKAKEMOD        Modified Hikkake Pattern
FUNCohlc0i1(CDLHIKKAKEMOD)
//CDLHOMINGPIGEON      Homing Pigeon
FUNCohlc0i1(CDLHOMINGPIGEON)
//CDLIDENTICAL3CROWS   Identical Three Crows
FUNCohlc0i1(CDLIDENTICAL3CROWS)
//CDLINNECK            In - Neck Pattern
FUNCohlc0i1(CDLINNECK)
//CDLINVERTEDHAMMER    Inverted Hammer
FUNCohlc0i1(CDLINVERTEDHAMMER)
//CDLKICKING           Kicking
FUNCohlc0i1(CDLKICKING)
//CDLKICKINGBYLENGTH   Kicking - bull / bear determined by the longer marubozu
FUNCohlc0i1(CDLKICKINGBYLENGTH)
//CDLLADDERBOTTOM      Ladder Bottom
FUNCohlc0i1(CDLLADDERBOTTOM)
//CDLLONGLEGGEDDOJI    Long Legged Doji
FUNCohlc0i1(CDLLONGLEGGEDDOJI)
//CDLLONGLINE          Long Line Candle
FUNCohlc0i1(CDLLONGLINE)
//CDLMARUBOZU          Marubozu
FUNCohlc0i1(CDLMARUBOZU)
//CDLMATCHINGLOW       Matching Low
FUNCohlc0i1(CDLMATCHINGLOW)
//CDLMATHOLD           Mat Hold
FUNCohlc1i1(CDLMATHOLD)
//CDLMORNINGDOJISTAR   Morning Doji Star
FUNCohlc1i1(CDLMORNINGDOJISTAR)
//CDLMORNINGSTAR       Morning Star
FUNCohlc1i1(CDLMORNINGSTAR)
//CDLONNECK            On - Neck Pattern
FUNCohlc0i1(CDLONNECK)
//CDLPIERCING          Piercing Pattern
FUNCohlc0i1(CDLPIERCING)
//CDLRICKSHAWMAN       Rickshaw Man
FUNCohlc0i1(CDLRICKSHAWMAN)
//CDLRISEFALL3METHODS  Rising / Falling Three Methods
FUNCohlc0i1(CDLRISEFALL3METHODS)
//CDLSEPARATINGLINES   Separating Lines
FUNCohlc0i1(CDLSEPARATINGLINES)
//CDLSHOOTINGSTAR      Shooting Star
FUNCohlc0i1(CDLSHOOTINGSTAR)
//CDLSHORTLINE         Short Line Candle
FUNCohlc0i1(CDLSHORTLINE)
//CDLSPINNINGTOP       Spinning Top
FUNCohlc0i1(CDLSPINNINGTOP)
//CDLSTALLEDPATTERN    Stalled Pattern
FUNCohlc0i1(CDLSTALLEDPATTERN)
//CDLSTICKSANDWICH     Stick Sandwich
FUNCohlc0i1(CDLSTICKSANDWICH)
//CDLTAKURI            Takuri(Dragonfly Doji with very long lower shadow)
FUNCohlc0i1(CDLTAKURI)
//CDLTASUKIGAP         Tasuki Gap
FUNCohlc0i1(CDLTASUKIGAP)
//CDLTHRUSTING         Thrusting Pattern
FUNCohlc0i1(CDLTHRUSTING)
//CDLTRISTAR           Tristar Pattern
FUNCohlc0i1(CDLTRISTAR)
//CDLUNIQUE3RIVER      Unique 3 River
FUNCohlc0i1(CDLUNIQUE3RIVER)
//CDLUPSIDEGAP2CROWS   Upside Gap Two Crows
FUNCohlc0i1(CDLUPSIDEGAP2CROWS)
//CDLXSIDEGAP3METHODS  Upside / Downside Gap Three Methods
FUNCohlc0i1(CDLXSIDEGAP3METHODS)


AmiVar TAAB_StockArrayTest(int NumArgs, AmiVar *ArgsTable)		
{														
	AmiVar result;										
	result.type = VAR_ARRAY;							
	result = gSite.AllocArrayResult();					
	int nSize = gSite.GetArraySize();					
	float f1 = ArgsTable[0].val;												
	
	result.array = gSite.GetStockArray((int)f1);
	
	return result;										
}




/////////////////////////////////////////////
// Function table now follows
//
// You have to specify each function that should be
// visible for AmiBroker.
// Each entry of the table must contain:
// "Function name", { FunctionPtr, <no. of array args>, <no. of string args>, <no. of float args>, <no. of default args>, <pointer to default values table float *>

FunctionTag gFunctionTable[] = {
								
								"TAAB_DEMA", { TAAB_DEMA, 1, 0, 1, 0, NULL },
								"TAAB_EMA", { TAAB_EMA, 1, 0, 1, 0, NULL },
								"TAAB_HT_TRENDLINE", { TAAB_HT_TRENDLINE, 1, 0, 0, 0, NULL },
								"TAAB_KAMA", { TAAB_KAMA, 1, 0, 1, 0, NULL },
								"TAAB_SAR", { TAAB_SAR, 0, 0, 2, 0, NULL },
								"TAAB_SMA", { TAAB_SMA, 1, 0, 1, 0, NULL },
								"TAAB_T3", { TAAB_SMA, 1, 0, 2, 0, NULL },
								"TAAB_TEMA", { TAAB_TEMA, 1, 0, 1, 0, NULL },
								"TAAB_TRIMA", { TAAB_TRIMA, 1, 0, 1, 0, NULL },
								"TAAB_WMA", { TAAB_WMA, 1, 0, 1, 0, NULL },

								"TAAB_ADX", { TAAB_ADX, 0, 0, 1, 0, NULL },
								"TAAB_ADXR", { TAAB_ADXR, 0, 0, 1, 0, NULL },

								"TAAB_AROON_DN", { TAAB_AROON_1, 0, 0, 1, 0, NULL },
								"TAAB_AROON_UP", { TAAB_AROON_2, 0, 0, 1, 0, NULL },
								"TAAB_AROONOSC", { TAAB_AROONOSC, 0, 0, 1, 0, NULL },

								"TAAB_BOP", { TAAB_BOP, 0, 0, 0, 0, NULL },
								"TAAB_CCI", { TAAB_CCI, 0, 0, 1, 0, NULL },
								"TAAB_CMO", { TAAB_CMO, 1, 0, 1, 0, NULL },
								"TAAB_DX", { TAAB_DX, 0, 0, 1, 0, NULL },
								"TAAB_MFI", { TAAB_MFI, 0, 0, 1, 0, NULL },
								"TAAB_MOM", { TAAB_MFI, 1, 0, 1, 0, NULL },
								"TAAB_PPO", { TAAB_PPO, 1, 0, 2, 0, NULL },
								"TAAB_ROC", { TAAB_ROC, 1, 0, 1, 0, NULL },
								"TAAB_RSI", { TAAB_RSI, 1, 0, 1, 0, NULL },
								"TAAB_TRIX", { TAAB_TRIX, 1, 0, 1, 0, NULL },

								"TAAB_ULTOSC", { TAAB_ULTOSC, 0, 0, 3, 0, NULL },
								"TAAB_WILLR", { TAAB_WILLR, 0, 0, 1, 0, NULL },
								//Volume Indicators
								"TAAB_AD", { TAAB_AD, 0, 0, 0, 0, NULL },
								"TAAB_ADOSC", { TAAB_ADOSC, 0, 0, 2, 0, NULL },
								"TAAB_OBV", { TAAB_OBV, 1, 0, 0, 0, NULL },
								//Cycle Indicators
								"TAAB_HT_DCPERIOD", { TAAB_HT_DCPERIOD, 1, 0, 0, 0, NULL },
								"TAAB_HT_DCPHASE", { TAAB_HT_DCPHASE, 1, 0, 0, 0, NULL },
								"TAAB_HT_PHASOR_InPhase", { TAAB_HT_PHASOR_1, 1, 0, 0, 0, NULL },
								"TAAB_HT_PHASOR_Quadrature", { TAAB_HT_PHASOR_2, 1, 0, 0, 0, NULL },
								"TAAB_HT_SINE_Sine", { TAAB_HT_SINE_1, 1, 0, 0, 0, NULL },
								"TAAB_HT_SINE_LeadSine", { TAAB_HT_SINE_2, 1, 0, 0, 0, NULL },
								//HT_TRENDLINE - Hilbert Transform - Instantaneous Trendline : SEE Overlap Studies
								//FUNC101(HT_TRENDLINE) 
								//HT_TRENDMODE         Hilbert Transform - Trend vs Cycle Mode
								//INT_out FUNC101(HT_TRENDMODE)

								//Volatility Indicators
								"TAAB_ATR", { TAAB_ATR, 0, 0, 1, 0, NULL },
								"TAAB_NATR", { TAAB_NATR, 0, 0, 1, 0, NULL },
								//TRANGE               True Range
								//FUNChlc01(TRANGE)

								//Pattern Recognition
								"TAAB_CDL2CROWS", { TAAB_CDL2CROWS, 0, 0, 0, 0, NULL },
								"TAAB_CDL3BLACKCROWS", { TAAB_CDL3BLACKCROWS, 0, 0, 0, 0, NULL },
								"TAAB_CDL3INSIDE", { TAAB_CDL3INSIDE, 0, 0, 0, 0, NULL },
								"TAAB_CDL3LINESTRIKE", { TAAB_CDL3LINESTRIKE, 0, 0, 0, 0, NULL },
								"TAAB_CDL3OUTSIDE", { TAAB_CDL3OUTSIDE, 0, 0, 0, 0, NULL },
								"TAAB_CDL3STARSINSOUTH", { TAAB_CDL3STARSINSOUTH, 0, 0, 0, 0, NULL },
								"TAAB_CDL3WHITESOLDIERS", { TAAB_CDL3WHITESOLDIERS, 0, 0, 0, 0, NULL },
								"TAAB_CDLABANDONEDBABY", { TAAB_CDLABANDONEDBABY, 0, 0, 1, 0, NULL },
								"TAAB_CDLADVANCEBLOCK", { TAAB_CDLADVANCEBLOCK, 0, 0, 0, 0, NULL },
								"TAAB_CDLBELTHOLD", { TAAB_CDLBELTHOLD, 0, 0, 0, 0, NULL },

								"TAAB_CDLBREAKAWAY", { TAAB_CDLBREAKAWAY, 0, 0, 0, 0, NULL },
								"TAAB_CDLCLOSINGMARUBOZU", { TAAB_CDLCLOSINGMARUBOZU, 0, 0, 0, 0, NULL },
								"TAAB_CDLCONCEALBABYSWALL", { TAAB_CDLCONCEALBABYSWALL, 0, 0, 0, 0, NULL },
								"TAAB_CDLCOUNTERATTACK", { TAAB_CDLCOUNTERATTACK, 0, 0, 0, 0, NULL },
								"TAAB_CDLDARKCLOUDCOVER", { TAAB_CDLDARKCLOUDCOVER, 0, 0, 1, 0, NULL },
								"TAAB_CDLDOJI", { TAAB_CDLDOJI, 0, 0, 0, 0, NULL },
								"TAAB_CDLDOJISTAR", { TAAB_CDLDOJISTAR, 0, 0, 0, 0, NULL },
								"TAAB_CDLDRAGONFLYDOJI", { TAAB_CDLDRAGONFLYDOJI, 0, 0, 0, 0, NULL },
								"TAAB_CDLENGULFING", { TAAB_CDLENGULFING, 0, 0, 0, 0, NULL },
								"TAAB_CDLEVENINGDOJISTAR", { TAAB_CDLEVENINGDOJISTAR, 0, 0, 1, 0, NULL },

								"TAAB_CDLEVENINGSTAR", { TAAB_CDLEVENINGSTAR, 0, 0, 1, 0, NULL },
								"TAAB_CDLGAPSIDESIDEWHITE", { TAAB_CDLGAPSIDESIDEWHITE, 0, 0, 0, 0, NULL },
								"TAAB_CDLGRAVESTONEDOJI", { TAAB_CDLGRAVESTONEDOJI, 0, 0, 0, 0, NULL },
								"TAAB_CDLHAMMER", { TAAB_CDLHAMMER, 0, 0, 0, 0, NULL },
								"TAAB_CDLHANGINGMAN", { TAAB_CDLHANGINGMAN, 0, 0, 0, 0, NULL },
								"TAAB_CDLHARAMI", { TAAB_CDLHARAMI, 0, 0, 0, 0, NULL },
								"TAAB_CDLHARAMICROSS", { TAAB_CDLHARAMICROSS, 0, 0, 0, 0, NULL },
								"TAAB_CDLHIGHWAVE", { TAAB_CDLHIGHWAVE, 0, 0, 0, 0, NULL },
								"TAAB_CDLHIKKAKE", { TAAB_CDLHIKKAKE, 0, 0, 0, 0, NULL },
								"TAAB_CDLHIKKAKEMOD", { TAAB_CDLHIKKAKEMOD, 0, 0, 0, 0, NULL },
								
								"TAAB_CDLHOMINGPIGEON", { TAAB_CDLHOMINGPIGEON, 0, 0, 0, 0, NULL },
								"TAAB_CDLIDENTICAL3CROWS", { TAAB_CDLIDENTICAL3CROWS, 0, 0, 0, 0, NULL },
								"TAAB_CDLINNECK", { TAAB_CDLINNECK, 0, 0, 0, 0, NULL },
								"TAAB_CDLINVERTEDHAMMER", { TAAB_CDLINVERTEDHAMMER, 0, 0, 0, 0, NULL },
								"TAAB_CDLKICKING", { TAAB_CDLKICKING, 0, 0, 0, 0, NULL },
								"TAAB_CDLKICKINGBYLENGTH", { TAAB_CDLKICKINGBYLENGTH, 0, 0, 0, 0, NULL },
								"TAAB_CDLLADDERBOTTOM", { TAAB_CDLLADDERBOTTOM, 0, 0, 0, 0, NULL },
								"TAAB_CDLLONGLEGGEDDOJI", { TAAB_CDLLONGLEGGEDDOJI, 0, 0, 0, 0, NULL },
								"TAAB_CDLLONGLINE", { TAAB_CDLLONGLINE, 0, 0, 0, 0, NULL },
								"TAAB_CDLMARUBOZU", { TAAB_CDLMARUBOZU, 0, 0, 0, 0, NULL },

								"TAAB_CDLMATCHINGLOW", { TAAB_CDLMATCHINGLOW, 0, 0, 0, 0, NULL },
								"TAAB_CDLMATHOLD", { TAAB_CDLMATHOLD, 0, 0, 1, 0, NULL },
								"TAAB_CDLMORNINGDOJISTAR", { TAAB_CDLMORNINGDOJISTAR, 0, 0, 1, 0, NULL },
								"TAAB_CDLMORNINGSTAR", { TAAB_CDLMORNINGSTAR, 0, 0, 1, 0, NULL },
								"TAAB_CDLONNECK", { TAAB_CDLONNECK, 0, 0, 0, 0, NULL },
								"TAAB_CDLPIERCING", { TAAB_CDLPIERCING, 0, 0, 0, 0, NULL },
								"TAAB_CDLRICKSHAWMAN", { TAAB_CDLRICKSHAWMAN, 0, 0, 0, 0, NULL },
								"TAAB_CDLRISEFALL3METHODS", { TAAB_CDLRISEFALL3METHODS, 0, 0, 0, 0, NULL },
								"TAAB_CDLSEPARATINGLINES", { TAAB_CDLSEPARATINGLINES, 0, 0, 0, 0, NULL },
								"TAAB_CDLSHOOTINGSTAR", { TAAB_CDLSHOOTINGSTAR, 0, 0, 0, 0, NULL },

								"TAAB_CDLSHORTLINE", { TAAB_CDLSHORTLINE, 0, 0, 0, 0, NULL },
								"TAAB_CDLSPINNINGTOP", { TAAB_CDLSPINNINGTOP, 0, 0, 0, 0, NULL },
								"TAAB_CDLSTALLEDPATTERN", { TAAB_CDLSTALLEDPATTERN, 0, 0, 0, 0, NULL },
								"TAAB_CDLSTICKSANDWICH", { TAAB_CDLSTICKSANDWICH, 0, 0, 0, 0, NULL },
								"TAAB_CDLTAKURI", { TAAB_CDLTAKURI, 0, 0, 0, 0, NULL },
								"TAAB_CDLTASUKIGAP", { TAAB_CDLTASUKIGAP, 0, 0, 0, 0, NULL },
								"TAAB_CDLTHRUSTING", { TAAB_CDLTHRUSTING, 0, 0, 0, 0, NULL },
								"TAAB_CDLTRISTAR", { TAAB_CDLTRISTAR, 0, 0, 0, 0, NULL },
								"TAAB_CDLUNIQUE3RIVER", { TAAB_CDLUNIQUE3RIVER, 0, 0, 0, 0, NULL },
								"TAAB_CDLUPSIDEGAP2CROWS", { TAAB_CDLUPSIDEGAP2CROWS, 0, 0, 0, 0, NULL },

								"TAAB_CDLXSIDEGAP3METHODS", { TAAB_CDLXSIDEGAP3METHODS, 0, 0, 0, 0, NULL },



								"TAAB_StockArrayTest", { TAAB_StockArrayTest, 0, 0, 1, 0, NULL },

								 
};

int gFunctionTableSize = sizeof( gFunctionTable )/sizeof( FunctionTag );

