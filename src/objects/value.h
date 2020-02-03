#ifndef scute_value_h
#define scute_value_h

#include "common.h"
#include "output.h"
#include "scanner.h"

typedef struct sChunk Chunk;
typedef struct sObj Obj;
typedef struct sObjString ObjString;
typedef struct sObjInstance ObjInstance;
typedef struct sObjChunk ObjChunk;
typedef struct sObjNative ObjNative;
typedef struct sObjColor ObjColor;
typedef struct sObjArray ObjArray;

typedef enum {
	VL_NULL,
	VL_BOOL,
	VL_NUM,
	VL_OBJ,
	VL_CLR,
} VLType;

typedef struct {
	VLType type;
	union {
		bool boolean;
		double number;
		Obj* obj;
	} as;

	int lineIndex;
	int inlineIndex;
} Value;

typedef struct {
	int capacity;
	int count;
	Value * values;
} ValueArray;	

#define BOOL_VAL(value) ((Value){VL_BOOL, {.boolean = value}, -1, -1})
#define NULL_VAL() ((Value){VL_NULL, {.number = 0}, -1, -1})
#define NUM_VAL(value) ((Value){VL_NUM, {.number = value}, -1, -1})
#define OBJ_VAL(value) ((Value){VL_OBJ, {.obj = (Obj*)(value)}, -1, -1})

#define AS_BOOL(value) ((value).as.boolean)
#define AS_NUM(value) ((value).as.number)
#define AS_OBJ(value) ((value).as.obj)

#define IS_BOOL(value) ((value).type == VL_BOOL)
#define IS_NULL(value) ((value).type == VL_NULL)
#define IS_NUM(value) ((value).type == VL_NUM)
#define IS_OBJ(value) ((value).type == VL_OBJ)
#define OBJ_TYPE(value) (AS_OBJ(value)->type)


void printValue(OutType out, Value value);
void printShapeType(OutType out, TKType type);


void initValueArray(ValueArray* array);
void freeValueArray(ValueArray* array);

int pushValueArray(ValueArray* array, Value value);
Value popValueArray(ValueArray* array);
Value getValueArray(ValueArray* array, int index);
void setValueArray(ValueArray* array, int index, Value val);

#endif
